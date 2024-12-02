#include "ServerMain.h"
#include "Socket.h"
#include "Session.h"

bool ServerMain::Initialize()
{
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
		WritePrivateProfileString(L"Buffer", L"BlockPerCount", std::to_wstring(SizePerBuffer).c_str(), configFilePath.c_str());
		WritePrivateProfileString(L"Pool", L"PacketPool", std::to_wstring(PacketPoolCount).c_str(), configFilePath.c_str());
#endif
	}
	
	port = GetPrivateProfileInt(L"Server", L"Port", ServerPort, configFilePath.c_str());
	bufferSize = GetPrivateProfileInt(L"Buffer", L"Size", SizePerBuffer, configFilePath.c_str());
#ifdef _SERVER_
	bufferPoolCount = GetPrivateProfileInt(L"Buffer", L"BlockPerCount", BufferPoolCount, configFilePath.c_str());
	int threadCount = GetPrivateProfileInt(L"Server", L"ThreadCount", ThreadCount, configFilePath.c_str());
	int packetExpandSize = GetPrivateProfileInt(L"Pool", L"PacketPool", PacketPoolCount, configFilePath.c_str());
#else
	std::wstring serverIp(INET_ADDRSTRLEN, L'\0');
	GetPrivateProfileString(L"Server", L"Ip", L"127.0.0.1", serverIp.data(), INET_ADDRSTRLEN, configFilePath.c_str());
	std::string ip = WStringToString(serverIp);
	int threadCount = 1;
#endif	


	// TODO - 2 : Create Pools -> Server Only
#ifdef _SERVER_
	BufferPool::GetInstance()->Initialize(bufferSize, bufferPoolCount);
	PacketPool::GetInstance()->Initialize(packetExpandSize);

#endif

	// TODO - 3 : Listen Socket Open -> Server Only
	// TODO - 3 : Create Connect Socket -> Client Only
	// TODO - 3 : Server Connect -> Client Only

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return false;
	}

	bool res = true;
	_socket = new Socket();

#ifdef _SERVER_
	_socket->Initialize(port);
	if (res == false) {
		return false;
	}

	res = _socket->Bind();
	if (res == false) {
		return false;
	}

	res = _socket->Listen();
	if (res == false) {
		return false;
	}

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
	HANDLE completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, threadCount);
	_completionPortList.push_back(completionPort);



	return true;
}

void ServerMain::Finalize()
{
	// TODO : 현재 연결돼있는 모든 세션에 대해 종료 패킷을 전송해야 합니다.

}

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
		}
		
	};
	std::thread acceptThread(acceptWork, completionPort);
	acceptThread.detach();
}

void ServerMain::CreateIOThread(HANDLE completionPort)
{
	auto IOWork = [this](HANDLE completionPort) {
		DWORD byteTransferred;
		ULONG_PTR completionKey;
		OVERLAPPED* overlapped;
		while (true) {
			bool res = true;

			res = GetQueuedCompletionStatus(completionPort, &byteTransferred, &completionKey, &overlapped, INFINITE);

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
			if (res == false && byteTransferred == 0) {
				// 클라이언트에서 closesocket 호출
				int error = WSAGetLastError();

				SessionID id = session->GetSessionId();
				if (_sessionMap.find(id) != _sessionMap.end()) {
					delete _sessionMap[id];
					_sessionMap.erase(id);
				}
				continue;
			}

		}
	};
}
