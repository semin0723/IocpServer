#ifndef _PACKETPOOL_
#define _PACKETPOOL_

#include "../../NetDefine.h"
#include "../../Pattern.h"

class PacketPool
{
	DeclSingleton(PacketPool)
	
	using Packets = std::deque<std::unique_ptr<Packet>>;
public:
	PacketPool() = default;
	~PacketPool();

	void Initialize(int packetCount);

	void AllocPacket(std::unique_ptr<Packet>& packet);
	void ReleasePacket(std::unique_ptr<Packet>& packet);
private:
	Packets _packetPool;
	std::mutex _mutex;

	int _curPoolSize = 0;
	int _expandPacketCount = 100;

	void ExpendPool();
};

#endif