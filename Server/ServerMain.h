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
	// 서버에서 종료 패킷을 전송하고, 확인패킷을 받았을 때,
	// 모든 연결된 세션이 연결 종료 된 후 호출해야 합니다.
	void ReleaseThread();

#ifdef _SERVER_
	void SendUpdate(SessionID sid);
#else
	void SendUpdate();
#endif
private:
	Socket* _socket = nullptr;

	void CreateIOThread(HANDLE completionPort);
#ifdef _SERVER_
	SessionMap _sessionMap;
	std::mutex _mutex;
	void CreateAcceptThread(HANDLE completionPort);
#else
	Session* _session = nullptr;
#endif
	CompletionPortList _completionPortList;

};

#endif