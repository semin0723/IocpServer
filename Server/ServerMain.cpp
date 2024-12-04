#include "ServerMain.h"
#include "Socket.h"
#include "Session.h"
#include "PacketDispatcher.h"

bool ServerMain::Initialize()
{
	printf("Start Initializing...\n");
	// TODO - 1 : Check Config -> Server, Client 분류에 따라 불러오는 config 파일이 달라짐.
	// 파일명 : Config.ini 로 동일.

	int port, bufferPoolCount, bufferSize;

	std::wstring configFilePath = L"./Config.ini";

	std::wstring platform(L"NoData");
	GetPrivateProfileString(L"Platform", L"Type", L"NoData", platform.data(), platform.size() + 1, configFilePath.c_str());

	if (platform == L"NoData") {
		// Data가 없기 때문에 초기 설정값을 출력해줘야 합니다.
		
		// Platform
#ifdef _SERVER_
		WritePrivateProfileString(L"Platform", L"Type", L"Server", configFilePath.c_str());
#else
		WritePrivateProfileString(L"Platform", L"Type", L"Client", configFilePath.c_str());
#endif
		// Server
		WritePrivateProfileString(L"Server", L"Port", std::to_wstring(ServerPort).c_str(), configFilePath.c_str());
#ifndef _SERVER_
		WritePrivateProfileString(L"Server", L"Ip", L"127.0.0.1", configFilePath.c_str());
#else
		WritePrivateProfileString(L"Server", L"ThreadCount", std::to_wstring(ThreadCount).c_str(), configFilePath.c_str());
#endif
		// Buffer
		WritePrivateProfileString(L"Buffer", L"Size", std::to_wstring(SizePerBuffer).c_str(), configFilePath.c_str());
#ifdef _SERVER_
		WritePrivateProfileString(L"Buffer", L"BufferPoolSize", std::to_wstring(BufferPoolCount).c_str(), configFilePath.c_str());
		WritePrivateProfileString(L"Pool", L"PacketPool", std::to_wstring(PacketPoolCount).c_str(), configFilePath.c_str());
#else
		WritePrivateProfileString(L"Buffer", L"BufferPoolSize", std::to_wstring(3).c_str(), configFilePath.c_str());
#endif
	}
	
	port = GetPrivateProfileInt(L"Server", L"Port", ServerPort, configFilePath.c_str());
	bufferSize = GetPrivateProfileInt(L"Buffer", L"Size", SizePerBuffer, configFilePath.c_str());
	bufferPoolCount = GetPrivateProfileInt(L"Buffer", L"BufferPoolSize", BufferPoolCount, configFilePath.c_str());
#ifdef _SERVER_
	int threadCount = GetPrivateProfileInt(L"Server", L"ThreadCount", ThreadCount, configFilePath.c_str());
	int packetExpandSize = GetPrivateProfileInt(L"Pool", L"PacketPool", PacketPoolCount, configFilePath.c_str());
#else
	std::wstring serverIp(INET_ADDRSTRLEN, L'\0');
	GetPrivateProfileString(L"Server", L"Ip", L"127.0.0.1", serverIp.data(), INET_ADDRSTRLEN, configFilePath.c_str());
	std::string ip = WStringToString(serverIp);
	int threadCount = 1;
#endif	

	std::string convertedStr = WStringToString(platform);
	std::cout << "Target Platform : " << convertedStr << "\n";

	printf("Server Port : %d\n", port);
	printf("Buffer Size : %d\n", bufferSize);
#ifdef _SERVER_
	printf("Buffer Pool Size : %d\n", bufferPoolCount);
	printf("PacketPool expand Size : %d\n", packetExpandSize);
#endif
	printf("Thread Count : %d\n", threadCount);
	printf("Config Setting Complete\n");

	// TODO - 2 : Create Pools
	// TODO - 2 : BufferPool -> client : count = 3, server : custom
	BufferPool::GetInstance()->Initialize(bufferSize, bufferPoolCount);
	printf("BufferPool Initialize Completed\n");

#ifdef _SERVER_
	PacketPool::GetInstance()->Initialize(packetExpandSize);
	printf("PacketPool Initialize Completed\n");

#endif

	// TODO - 3 : Initialize Packet Dispatcher
	PacketDispatcher::GetInstance()->Initialize();

	// TODO - 4 : Listen Socket Open -> Server Only
	// TODO - 4 : Create Connect Socket -> Client Only
	// TODO - 4 : Server Connect -> Client Only

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return false;
	}

	printf("WSAStartUp Complete\n");

	bool res = true;
	_socket = new Socket();

#ifdef _SERVER_
	_socket->Initialize(port);
	if (res == false) {
		return false;
	}
	printf("Socket Initialize Complete\n");

	res = _socket->Bind();
	if (res == false) {
		return false;
	}
	printf("Socket Bind Complete\n");

	res = _socket->Listen();
	if (res == false) {
		return false;
	}
	printf("Socket Start Listening\n");

#else
	res = _socket->Initialize(port, SocketType::Client, ip.c_str());
	if (res == false) {
		return false;
	}

	res = _socket->Connect();
	if (res == false) {
		return false;
	}

#endif

	// TODO - 4 : CreateCompletionPort
	// Server : custom thread count, Client : 1 thread
	// Client : 서버와 통신하기 위한 세션 생성.
	HANDLE completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, threadCount);
	_completionPortList.push_back(completionPort);

	printf("CompletionPort Created.\n");

#ifdef _SERVER_
	CreateAcceptThread(completionPort);
	printf("Accept Thread Created.\n");
#else
	_session = new Session();
	_session->Initialize(_socket);

	HANDLE handle = CreateIoCompletionPort((HANDLE)_socket->GetSocket(), completionPort, (ULONG_PTR)_session, 0);
#endif
	for (int i = 0; i < threadCount; i++) {
		CreateIOThread(completionPort);
	}
	printf("IOThread Created\n");

	printf("Initialize Completed\n");

	return true;
}

void ServerMain::Finalize()
{
	// TODO : 현재 연결돼있는 모든 세션에 대해 종료 패킷을 전송해야 합니다.

}

void ServerMain::ReleaseThread()
{

}
#ifdef _SERVER_
void ServerMain::SendUpdate(SessionID sid)
{
	_sessionMap[sid]->SendUpdate();
}
#else
void ServerMain::SendUpdate()
{
	_session->SendUpdate();
}
#endif
#ifdef _SERVER_
void ServerMain::CreateAcceptThread(HANDLE completionPort)
{
	auto acceptWork = [this](HANDLE completionPort) {
		SOCKADDR_IN clientAddr;
		int len = sizeof(clientAddr);

		while (true) {
			SOCKET client = accept(_socket->GetSocket(), PtrCast(SOCKADDR*, &clientAddr), &len);
			if (client == INVALID_SOCKET) {
				int error = WSAGetLastError();
				if (error == WSAENOTSOCK || error == WSAEINTR) {
					std::cout << "Server Socket Closed\n";
					break;
				}
				continue;
			}
			// TODO : CreateSession.
			Socket* socket = new Socket();
			socket->Initialize(client, clientAddr);

			Session* newSession = new Session();
			newSession->Initialize(socket);

			HANDLE handle = CreateIoCompletionPort((HANDLE)client, completionPort, (ULONG_PTR)newSession, 0);
			if (handle == nullptr) {
				printf("Invalid Handle. [Location : CreateAcceptThread]\n");
			}
			newSession->RecvUpdate();
			{
				Lock lock(_mutex);
				_sessionMap.insert({ newSession->GetSessionId(), newSession });
			}
			PacketDispatcher::GetInstance()->SessionCreated(newSession->GetSessionId());

			printf("Session Created\n");
		}
	};
	std::thread acceptThread(acceptWork, completionPort);
	acceptThread.detach();
}
#endif

void ServerMain::CreateIOThread(HANDLE completionPort)
{
	auto IOWork = [this](HANDLE completionPort) {
		DWORD byteTransferred;
		ULONG_PTR completionKey;
		OVERLAPPED* overlapped;
		while (true) {
			bool res = true;

			res = GetQueuedCompletionStatus(completionPort, &byteTransferred, &completionKey, &overlapped, INFINITE);

			printf("byteTransferred %d\n", byteTransferred);

			if (overlapped == nullptr) {
				continue;
			}
			if (overlapped->Internal < 0) {
				printf("<<Error>> Code : %d\n", WSAGetLastError());
			}
			if (static_cast<DWORD>(overlapped->Internal) == STATUS_PENDING) {
				printf("작업이 완료되지 않았습니다.\n");
			}

			Session* session = (Session*)completionKey;
#ifdef _SERVER_
			if (res == false && byteTransferred == 0) {
				// 클라이언트에서 closesocket 호출
				int error = WSAGetLastError();

				SessionID id = session->GetSessionId();
				if (_sessionMap.find(id) != _sessionMap.end()) {
					delete _sessionMap[id];
					_sessionMap.erase(id);

					printf("Session Deleted\n");
				}
				continue;
			}
#endif
			int status = session->CheckOverlappedStatus(overlapped);

			if (status == 1) {
				session->RecvUpdate();
			}
			else {
				session->SendUpdate();
			}


		}
	};

	std::thread ioThread(IOWork, completionPort);
	ioThread.detach();
}
