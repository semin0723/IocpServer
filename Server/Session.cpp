#include "Session.h"
#include "Socket.h"

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
}

bool Session::RecvUpdate()
{
	_recvTempBuffer->Write(_recvBuffer, _recvOverlapped.InternalHigh);


	bool res = _socket->Recv(_recvBuffer, _bufferSize, _recvOverlapped);
	if (res == false) {
		return false;
	}

	return true;
}

bool Session::SendUpdate()
{
	bool res = _socket->Send(_sendBuffer, _bufferSize, _sendOverlapped);
	if (res == false) {
		return false;
	}


	return true;
}

void Session::SaveCompletePacket()
{
	// TODO : 데이터를 넣을 Packet박스를 Pool에게서 얻어와야 합니다.
}

