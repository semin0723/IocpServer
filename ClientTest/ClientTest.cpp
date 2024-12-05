#include <iostream>
#include "../Server/ServerMain.h"
#include "../Server/PacketDispatcher.h"

int main()
{
	ServerMain* client = new ServerMain();
	client->Initialize();

	while (true) {
		int num;
		std::cin >> num;

		for (int i = 0; i < 1000000; i++) {
			std::unique_ptr<Packet> packet = std::make_unique<Packet>();
			packet->_header._packetId = (short)PID::Int;
			TestPacket::TestInt msg;
			msg.set_value(num);

			std::string serializedMsg = msg.SerializeAsString();
			MergePacket(packet, serializedMsg);

			PacketDispatcher::GetInstance()->SaveSendPacket(packet);
			client->SendUpdate();
			num++;
		}



	}
}