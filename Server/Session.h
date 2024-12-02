#pragma once
#include "NetDefine.h"

class Socket;

class Session
{
	// �������� �����ϴ� Ŭ���̾�Ʈ�� ���ᰴü.
public:
	Session();
	virtual ~Session();

	bool RecvUpdate();
	bool SendUpdate();



#ifdef _SERVER_
private:
	static SessionID _SID;
	SessionID _sessionId = -1;
public:
	const SessionID GetSessionId() const { return _sessionId; }
#endif
private:
	// socket ��ü has - a�� ��� �ֱ�.
	Socket* _socket = nullptr;
	// �������κ��� ���� �����͸� �����ϱ� ����. 
	// ���⼭ ������ ������ ��Ŷ�� ���� packet queue�� ����.
	StreamBuffer* _recvTempBuffer = nullptr;
	
	// �� ���۴� ������ �̿��� �����͸� �����ϰų� �ޱ� ���� ��ġ.
	int _bufferSize = 0;
	char* _recvBuffer = nullptr;
	char* _sendBuffer = nullptr;

	OVERLAPPED _recvOverlapped;
	OVERLAPPED _sendOverlapped;

	void SaveCompletePacket();
};