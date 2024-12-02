#ifndef _SERVERMAIN_
#define _SERVERMAIN_

#include "NetDefine.h"

class Socket;
class Session;

using CompletionPortList = std::deque<HANDLE>;
using SessionMap = std::unordered_map<SessionID, Session*>;

// Server, Client �������� ���������� �κ�.
// �� Ŭ������ ��������ν� ���� - Ŭ���̾�Ʈ ������ ����� ������.
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