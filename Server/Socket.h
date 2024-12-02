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

	bool Open();
	void Close();

	// Client ����
	bool Connect();

	// Server ����
	bool Bind();
	bool Listen();
	void Open(SOCKET socket);


	bool Recv(char*& buf, int size);
	bool Send(char*& buf, int size);

private:
	SOCKET _socket = INVALID_SOCKET;
	SOCKADDR_IN _socketAddr;
	WSABUF _recvWsa{};
	WSABUF _sendWsa{};

	int _protocol = -1;

	OVERLAPPED _recvOverlapped;
	OVERLAPPED _sendOverlapped;

	Socket(Socket&) = delete;
	Socket(Socket&&) = delete;
	Socket& operator=(Socket&) = delete;
	Socket&& operator=(Socket&&) = delete;
};

