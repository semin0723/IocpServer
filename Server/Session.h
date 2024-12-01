#pragma once
#include "NetDefine.h"

class Socket;

class Session
{
	// Server <-> Client사이에 통신을 하는 객체.
	// Client측면에서 Session은 생성만 해두면 알아서 별도의 스레드를 생성해 서버와 통신을 시도함.

public:
	Session();
	virtual ~Session();

	bool RecvUpdate();
	bool SendUpdate();

private:
#ifdef _SERVER_
	static SessionID _SID;
	SessionID _sessionId = -1;
	const SessionID GetSessionId() const { return _sessionId; }
#endif
	// socket 객체 has - a로 들고 있기.
	Socket* _socket = nullptr;
	// 소켓으로부터 받은 데이터를 저장하기 위함. 
	// 여기서 생성된 완전한 패킷에 대해 packet queue에 저장.
	StreamBuffer* _recvTempBuffer = nullptr;
	
	// 두 버퍼는 소켓을 이용해 데이터를 전송하거나 받기 위한 위치.
	char* _recvBuffer = nullptr;
	char* _sendBuffer = nullptr;

};