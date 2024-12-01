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

	void SaveRecvPacket(std::unique_ptr<Packet>& packet);
	void SaveSendPacket(std::unique_ptr<Packet>& packet, SessionID sid);

	void SwapRecvPacketQueue(PacketQueue& queue);
	void SwapSendPacketQueue(PacketQueue& queue, SessionID sid);
#ifdef _SERVER_
	void SessionCreated(SessionID sid);
#endif
private:
	PacketQueue _recievedPacket;
	SendQueue _pendingSendPacket;
	std::mutex _recvMutex;
	std::mutex _sendMutex;
};

