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
	// �������� ���� ��Ŷ�� �����ϰ�, Ȯ����Ŷ�� �޾��� ��,
	// ��� ����� ������ ���� ���� �� �� ȣ���ؾ� �մϴ�.
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