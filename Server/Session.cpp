#include "Session.h"

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
}

Session::~Session()
{
	delete _recvTempBuffer;
	BufferPool::GetInstance()->ReleaseBuffer(_recvBuffer);
	BufferPool::GetInstance()->ReleaseBuffer(_sendBuffer);
}

bool Session::RecvUpdate()
{
	return false;
}

bool Session::SendUpdate()
{

	return false;
}

