#pragma once
#include <string>

struct Packet;

void MergePacket(Packet& packet, std::string& message);
std::string WStringToString(std::wstring& data);