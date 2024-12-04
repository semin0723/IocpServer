#pragma once
#include <string>
#include <memory>

struct Packet;

void MergePacket(std::unique_ptr<Packet>& packet, std::string& message);
std::string WStringToString(std::wstring& data);