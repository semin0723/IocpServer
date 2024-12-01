#include "PacketDispatcher.h"

ImplSingleton(PacketDispatcher)

PacketDispatcher::PacketDispatcher()
{
}

PacketDispatcher::~PacketDispatcher()
{
}

void PacketDispatcher::SaveRecvPacket(std::unique_ptr<Packet>& packet)
{
	Lock lock(_recvMutex);
	_recievedPacket.push(std::move(packet));
}

void PacketDispatcher::SaveSendPacket(std::unique_ptr<Packet>& packet, SessionID sid)
{
	Lock lock(_sendMutex);
	_pendingSendPacket[sid].push(std::move(packet));
}

void PacketDispatcher::SwapRecvPacketQueue(PacketQueue& queue)
{
	Lock lock(_recvMutex);
	std::swap(queue, _recievedPacket);
}

void PacketDispatcher::SwapSendPacketQueue(PacketQueue& queue, SessionID sid)
{
	Lock lock(_sendMutex);
	std::swap(queue, _pendingSendPacket[sid]);
}

void PacketDispatcher::SessionCreated(SessionID sid)
{
	_pendingSendPacket.insert({ sid, PacketQueue() });
}
