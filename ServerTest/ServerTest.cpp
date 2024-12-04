#include <iostream>
#include "../Server/ServerMain.h"
#include "../Server/PacketDispatcher.h"


int main()
{
    ServerMain* server = new ServerMain();
    server->Initialize();
    TimeSystem* time = TimeSystem::GetInstance();
    PacketDispatcher* dispatcher = PacketDispatcher::GetInstance();
    time->Initialize();

    double throttling = 0.16667;
    double interval = 0.0;

    PacketQueue recvPackets;

    while (true) {
        time->Update();
        interval += time->GetDeltaTime();
        if (interval >= throttling) {
            interval -= throttling;
            if (recvPackets.empty()) {
                dispatcher->SwapRecvPacketQueue(recvPackets);
                //printf("PacketDispatcher Swaped\n");
            }

            while (!recvPackets.empty()) {
                std::unique_ptr<Packet> packet = std::move(recvPackets.front());
                recvPackets.pop();
                if (packet.get()->_header._packetId == (short)PID::Int) {
                    TestPacket::TestInt msg;
                    msg.ParseFromArray(packet.get()->_data, packet.get()->_header._packetSize - PacketHeaderSize);

                    printf("Packet Read. Packet Type : Int, Packet Data : %d\n", msg.value());
                }

                PacketPool::GetInstance()->ReleasePacket(packet);
            }

        }
    }
}