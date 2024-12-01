#include "ServerMain.h"

void ServerMain::Initialize()
{
	// TODO - 1 : Check Config -> Server, Client �з��� ���� �ҷ����� config ������ �޶���.
	// ���ϸ� : Config.ini �� ����.

	int port, bufferPoolCount, bufferSize;

	std::wstring configFilePath = L"./Config.ini";

	std::wstring platform(L"NoData");
	GetPrivateProfileString(L"Platform", L"Type", L"NoData", platform.data(), platform.size() + 1, configFilePath.c_str());

	if (platform == L"NoData") {
		// Data�� ���� ������ �ʱ� �������� �������� �մϴ�.
		
		// Platform
#ifdef _SERVER_
		WritePrivateProfileString(L"Platform", L"Type", L"Server", configFilePath.c_str());
#else
		WritePrivateProfileString(L"Platform", L"Type", L"Client", configFilePath.c_str());
#endif
		// Server
		WritePrivateProfileString(L"Server", L"Port", std::to_wstring(ServerPort).c_str(), configFilePath.c_str());
#ifndef _SERVER_
		WritePrivateProfileString(L"Server", L"Ip", L"255.255.255.255", configFilePath.c_str());
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
#endif	


	// TODO - 2 : Create Pools -> Server Only
#ifdef _SERVER_
	BufferPool::GetInstance()->Initialize(bufferSize, bufferPoolCount);

#endif

	// TODO - 3 : Listen Socket Open -> Server Only
	// TODO - 3 : Create Connect Socket -> Client Only
	// TODO - 3 : Server Connect -> Client Only
#ifdef _SERVER_

#else

#endif


}
