#include "PacketPool.h"

ImplSingleton(PacketPool)

PacketPool::~PacketPool()
{
	_packetPool.clear();
}

void PacketPool::Initialize(int packetCount)
{
	_expandPacketCount = packetCount;
	ExpendPool();
}

void PacketPool::AllocPacket(std::unique_ptr<Packet>& packet)
{
	Lock lock(_mutex);
	packet = std::move(_packetPool.front());
	_packetPool.pop_front();
	_curPoolSize--;

	if (_curPoolSize < (_expandPacketCount / 2)) {
		ExpendPool();
	}
}

void PacketPool::ReleasePacket(std::unique_ptr<Packet>& packet)
{
	Lock lock(_mutex);
	_packetPool.emplace_back(std::move(packet));
}

void PacketPool::ExpendPool()
{
	for (int i = 0; i < _expandPacketCount; i++) {
		_packetPool.emplace_back(std::make_unique<Packet>());
	}
	_curPoolSize += _expandPacketCount;
}
