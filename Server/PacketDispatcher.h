#pragma once
#include "NetDefine.h"
#include "Pattern.h"

using SendQueue = std::unordered_map<SessionID, PacketQueue>;

class PacketDispatcher
{
	DeclSingleton(PacketDispatcher)
public:
	PacketDispatcher();
	~PacketDispatcher();

	void Initialize() {}

	void SaveRecvPacket(std::unique_ptr<Packet>& packet);
	void SwapRecvPacketQueue(PacketQueue& queue);


#ifdef _SERVER_
	void SaveSendPacket(std::unique_ptr<Packet>& packet, SessionID sid);
	void SwapSendPacketQueue(PacketQueue& queue, SessionID sid);
	void SessionCreated(SessionID sid);
#else
	void SaveSendPacket(std::unique_ptr<Packet>& packet);
	void SwapSendPacketQueue(PacketQueue& queue);
#endif
private:
	PacketQueue _recievedPacket;
#ifdef _SERVER_
	SendQueue _pendingSendPacket;
#else
	PacketQueue _pendingSendPacket;
#endif
	std::mutex _recvMutex;
	std::mutex _sendMutex;
};

