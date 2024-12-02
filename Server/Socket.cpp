#include "Socket.h"

Socket::~Socket()
{
    Close();
}

bool Socket::Initialize(int port, SocketType socketType, const char* serverIp, int protocol)
{
    _protocol = protocol;
    bool res = true;

    if (socketType != SocketType::Pool) {
        res = Open();
        if (res == false) {
            return false;
        }
    }

    _socketAddr.sin_family = AF_INET;
    _socketAddr.sin_port = htons(port);
#ifdef _SERVER_
    _socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
#else
    if (inet_pton(AF_INET, serverIp, &(_socketAddr.sin_addr)) != 1) {
        return false;
    }
#endif

    return true;
}

void Socket::Close()
{
    if (_socket != INVALID_SOCKET) {
        closesocket(_socket);
    }
}

bool Socket::Recv(char*& buf, int size)
{
    _recvWsa.buf = buf;
    _recvWsa.len = size;

    DWORD flg = 0;
    DWORD recvByte = 0;

    int res = WSARecv(_socket, &_recvWsa, 1, &recvByte, &flg, &_recvOverlapped, NULL);

    if (res < 0) {
        if (GetLastError() != WSA_IO_PENDING) {
            return false;
        }
    }

    return true;
}

bool Socket::Send(char*& buf, int size)
{
    _sendWsa.buf = buf;
    _sendWsa.len = size;

    DWORD sendByte = 0;
    int res = WSASend(_socket, &_sendWsa, 1, &sendByte, 0, &_sendOverlapped, NULL);

    if (res < 0) {
        if (GetLastError() != WSA_IO_PENDING) {
            return false;
        }
    }

    return true;
}

bool Socket::Open()
{
    _socket = WSASocket(AF_INET, SOCK_STREAM, _protocol, NULL, NULL, WSA_FLAG_OVERLAPPED);
    if (_socket == INVALID_SOCKET) {
        return false;
    }

    return true;
}

bool Socket::Connect()
{
    int result = WSAConnect(_socket, PtrCast(SOCKADDR*, &_socketAddr), sizeof(SOCKADDR_IN), 0, 0, 0, 0);
    if (result == SOCKET_ERROR) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            return false;
        }
    }
    return true;
}

void Socket::Open(SOCKET socket)
{
    _socket = socket;
}

bool Socket::Bind()
{
    int result = bind(_socket, PtrCast(SOCKADDR*, &_socketAddr), sizeof(SOCKADDR_IN));
    if (result == SOCKET_ERROR) {
        return false;
    }
    return true;
}

bool Socket::Listen()
{
    int result = listen(_socket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        return false;
    }
    return true;
}
