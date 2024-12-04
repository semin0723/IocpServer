#include "Session.h"
#include "Socket.h"
#include "PacketDispatcher.h"

#ifdef _SERVER_
SessionID Session::_SID = 0;
#endif

Session::Session() 
#ifdef _SERVER_
	: _sessionId(++_SID)
#endif
{
	_recvTempBuffer = new StreamBuffer();
	BufferPool::GetInstance()->AllocBuffer(_recvBuffer);
	BufferPool::GetInstance()->AllocBuffer(_sendBuffer);
	_bufferSize = BufferPool::GetInstance()->GetBufferSize();
}

Session::~Session()
{
	delete _recvTempBuffer;
	BufferPool::GetInstance()->ReleaseBuffer(_recvBuffer);
	BufferPool::GetInstance()->ReleaseBuffer(_sendBuffer);
	
	delete _socket;
}

void Session::Initialize(Socket* socket)
{
	_socket = socket;
}

bool Session::RecvUpdate()
{
	_recvTempBuffer->Write(_recvBuffer, _recvOverlapped.InternalHigh);
	SaveCompletePacket();

	bool res = _socket->Recv(_recvBuffer, _bufferSize, _recvOverlapped);
	if (res == false) {
		return false;
	}

	return true;
}

bool Session::SendUpdate()
{
	if (_pendingSend.empty()) {
#ifdef _SERVER_
		PacketDispatcher::GetInstance()->SwapSendPacketQueue(_pendingSend, _sessionId);
#else
		PacketDispatcher::GetInstance()->SwapSendPacketQueue(_pendingSend);
#endif
	}



	if (_pendingSend.empty()) {
		return true;
	}

	while (!_pendingSend.empty()) {
		int packetSize = _pendingSend.front()->_header._packetSize;
		if (_sendBufferSize + packetSize <= _bufferSize) {
			memcpy(_sendBuffer, PtrCast(char*, _pendingSend.front().get()), packetSize);
			_sendBufferSize += packetSize;
#ifdef _SERVER_
			PacketPool::GetInstance()->ReleasePacket(_pendingSend.front());
#endif
			_pendingSend.pop();
		}
		else {
			break;
		}
	}

	bool res = _socket->Send(_sendBuffer, _sendBufferSize, _sendOverlapped);
	if (res == false) {
		return false;
	}

	printf("before clear bufferSize : %d\n", _sendBufferSize);
	_sendBufferSize -= _sendOverlapped.InternalHigh;
	printf("after clear bufferSize : %d\n", _sendBufferSize);

	return true;
}

int Session::CheckOverlappedStatus(OVERLAPPED* overlapped)
{
	if (overlapped == &_recvOverlapped) {
		return 1;
	}
	else {
		return 2;
	}
}

void Session::SaveCompletePacket()
{
	// TODO : 데이터를 넣을 Packet박스를 Pool에게서 얻어와야 합니다.

	PacketHeader header;
	bool res = true;
	while (res = _recvTempBuffer->Peek(PtrCast(char*, &header), PacketHeaderSize)) {
		
		//if (res == false) {
		//	return;
		//}

		std::unique_ptr<Packet> packet;
	#ifdef _SERVER_
		PacketPool::GetInstance()->AllocPacket(packet);
	#else
		packet = std::make_unique<Packet>();
	#endif
		res = _recvTempBuffer->Read(PtrCast(char*, packet.get()), header._packetSize);

		PacketDispatcher::GetInstance()->SaveRecvPacket(packet);
	}
}

