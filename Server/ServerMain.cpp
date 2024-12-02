#include "ServerMain.h"
#include "Socket.h"

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
#endif
		// Buffer
		WritePrivateProfileString(L"Buffer", L"Size", std::to_wstring(SizePerBuffer).c_str(), configFilePath.c_str());
#ifdef _SERVER_
		WritePrivateProfileString(L"Buffer", L"BlockPerCount", std::to_wstring(SizePerBuffer).c_str(), configFilePath.c_str());
#endif
	}
	
	port = GetPrivateProfileInt(L"Server", L"Port", ServerPort, configFilePath.c_str());
	bufferSize = GetPrivateProfileInt(L"Buffer", L"Size", SizePerBuffer, configFilePath.c_str());
#ifdef _SERVER_
	bufferPoolCount = GetPrivateProfileInt(L"Buffer", L"BlockPerCount", BufferPoolCount, configFilePath.c_str());
#else
	std::wstring serverIp(INET_ADDRSTRLEN, L'\0');
	GetPrivateProfileString(L"Server", L"Ip", L"127.0.0.1", serverIp.data(), INET_ADDRSTRLEN, configFilePath.c_str());
	std::string ip = WStringToString(serverIp);

#endif	


	// TODO - 2 : Create Pools -> Server Only
#ifdef _SERVER_
	BufferPool::GetInstance()->Initialize(bufferSize, bufferPoolCount);

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


	return true;
}
