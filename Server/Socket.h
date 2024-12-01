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
	// TODO : 클라이언트에서 이 함수를 실행할 때는 두 번째 매개변수의 값을 변경해줘야 합니다.
	bool Initialize(int port, int protocol = IPPROTO_TCP, SocketType socketType = SocketType::Listen);

	bool Open();
	void Close();

	// Client 전용
	bool Connect();

	// Server 전용
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

