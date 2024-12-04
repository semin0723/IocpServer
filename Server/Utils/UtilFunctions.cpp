#include "UtilFunctions.h"
#include "../NetDefine.h"

void MergePacket(std::unique_ptr<Packet>& packet, std::string& message)
{
    memcpy(packet->_data, message.c_str(), message.size());
    packet->_header._packetSize = PacketHeaderSize + message.size();
}

std::string WStringToString(std::wstring& data)
{
    int byteSize = WideCharToMultiByte(CP_UTF8, 0, data.c_str(), data.size(), nullptr, 0, nullptr, nullptr);
    std::string ret(byteSize, 0);

    WideCharToMultiByte(CP_UTF8, 0, data.c_str(), data.size(), ret.data(), byteSize, nullptr, nullptr);

    return ret;
}
