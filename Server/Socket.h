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
	bool Initialize(int port, SocketType socketType = SocketType::Listen, const char* serverIp = "127.0.0.1", int protocol = IPPROTO_TCP);
	// accept를 진행하고 session을 생성할 때는 이 Initialize함수를 사용하면 됩니다.
	void Initialize(SOCKET socket, SOCKADDR_IN addr);

	bool Open();
	void Close();

	// Client 전용
	bool Connect();

	// Server 전용
	bool Bind();
	bool Listen();
	void Open(SOCKET socket);

	// size에는 총 버퍼의 크기를 넣어주면 됩니다.
	bool Recv(char*& buf, int size, OVERLAPPED& overlapped);
	// size에는 보낼 데이터의 총 사이즈를 넣어주면 됩니다.
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

