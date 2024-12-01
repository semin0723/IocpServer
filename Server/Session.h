#pragma once
#include "NetDefine.h"

class Socket;

class Session
{
	// Server <-> Client���̿� ����� �ϴ� ��ü.
	// Client���鿡�� Session�� ������ �صθ� �˾Ƽ� ������ �����带 ������ ������ ����� �õ���.

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
	// socket ��ü has - a�� ��� �ֱ�.
	Socket* _socket = nullptr;
	// �������κ��� ���� �����͸� �����ϱ� ����. 
	// ���⼭ ������ ������ ��Ŷ�� ���� packet queue�� ����.
	StreamBuffer* _recvTempBuffer = nullptr;
	
	// �� ���۴� ������ �̿��� �����͸� �����ϰų� �ޱ� ���� ��ġ.
	char* _recvBuffer = nullptr;
	char* _sendBuffer = nullptr;

};