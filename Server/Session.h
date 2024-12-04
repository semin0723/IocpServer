#pragma once
#include "NetDefine.h"

class Socket;

class Session
{
	// 서버에서 관리하는 클라이언트의 연결객체.
public:
	Session();
	virtual ~Session();

	void Initialize(Socket* socket);

	bool RecvUpdate();
	bool SendUpdate();

	// return 1 : recvOverlapped, return 2 : sendOverlapped.
	int CheckOverlappedStatus(OVERLAPPED* overlapped);

#ifdef _SERVER_
private:
	static SessionID _SID;
	SessionID _sessionId = -1;
public:
	const SessionID GetSessionId() const { return _sessionId; }
#endif
private:
	// socket 객체 has - a로 들고 있기.
	Socket* _socket = nullptr;
	// 소켓으로부터 받은 데이터를 저장하기 위함. 
	// 여기서 생성된 완전한 패킷에 대해 packet queue에 저장.
	StreamBuffer* _recvTempBuffer = nullptr;
	
	// 두 버퍼는 소켓을 이용해 데이터를 전송하거나 받기 위한 위치.
	int _bufferSize = 0;
	char* _recvBuffer = nullptr;
	char* _sendBuffer = nullptr;
	int _sendBufferSize = 0;
	PacketQueue _pendingSend;

	OVERLAPPED _recvOverlapped;
	OVERLAPPED _sendOverlapped;

	void SaveCompletePacket();
};