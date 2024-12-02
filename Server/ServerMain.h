#ifndef _SERVERMAIN_
#define _SERVERMAIN_

#include "NetDefine.h"

class Socket;
class Session;

using CompletionPortList = std::deque<HANDLE>;
using SessionMap = std::unordered_map<SessionID, Session*>;

// Server, Client 공통으로 가져가야할 부분.
// 이 클래스를 사용함으로써 서버 - 클라이언트 사이의 통신을 수행함.
class ServerMain
{
public:
	ServerMain() = default;
	~ServerMain() = default;

	bool Initialize();
	void Finalize();
private:
	Socket* _socket = nullptr;

	void CreateAcceptThread(HANDLE completionPort);
	void CreateIOThread(HANDLE completionPort);
#ifdef _SERVER_
	SessionMap _sessionMap;
	std::mutex _mutex;
	CompletionPortList _completionPortList;
#endif
};

#endif