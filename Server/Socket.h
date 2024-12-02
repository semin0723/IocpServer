#pragma once
#include "NetDefine.h"

enum class SocketType {
	Listen,
	Client,
	Pool,

};

class Socket
{
public:
	Socket() = default;
	virtual ~Socket();

	// Protocol Default = TCP
	// TODO : Ŭ���̾�Ʈ���� �� �Լ��� ������ ���� �� ��° �Ű������� ���� ��������� �մϴ�.
	bool Initialize(int port, SocketType socketType = SocketType::Listen, const char* serverIp = "127.0.0.1", int protocol = IPPROTO_TCP);
	// accept�� �����ϰ� session�� ������ ���� �� Initialize�Լ��� ����ϸ� �˴ϴ�.
	void Initialize(SOCKET socket, SOCKADDR_IN addr);

	bool Open();
	void Close();

	// Client ����
	bool Connect();

	// Server ����
	bool Bind();
	bool Listen();
	void Open(SOCKET socket);

	// size���� �� ������ ũ�⸦ �־��ָ� �˴ϴ�.
	bool Recv(char*& buf, int size, OVERLAPPED& overlapped);
	// size���� ���� �������� �� ����� �־��ָ� �˴ϴ�.
	bool Send(char*& buf, int size, OVERLAPPED& overlapped);

	SOCKET& GetSocket() { return _socket; }

private:
	SOCKET _socket = INVALID_SOCKET;
	SOCKADDR_IN _socketAddr;
	WSABUF _recvWsa{};
	WSABUF _sendWsa{};

	int _protocol = -1;

	Socket(Socket&) = delete;
	Socket(Socket&&) = delete;
	Socket& operator=(Socket&) = delete;
	Socket&& operator=(Socket&&) = delete;
};

