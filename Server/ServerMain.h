#ifndef _SERVERMAIN_
#define _SERVERMAIN_

#include "NetDefine.h"

class Socket;

// Server, Client �������� ���������� �κ�.
// �� Ŭ������ ��������ν� ���� - Ŭ���̾�Ʈ ������ ����� ������.
class ServerMain
{
public:
	ServerMain() = default;
	~ServerMain() = default;

	bool Initialize();

private:
	Socket* _socket = nullptr;
};

#endif