#ifndef _NETDEFINE_
#define _NETDEFINE_

#include <ws2tcpip.h>
#include <WinSock2.h>
#include <mswsock.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

#include <thread>
#include <mutex>
#include <string>
#include <memory>
#include <map>
#include <queue>
#include <algorithm>
#include <iostream>

// ============= Defines =================
// TODO : Ŭ���̾�Ʈ������ �ּ��� �ɾ��ּ���.
#define _SERVER_

// ================ UTILS ================
#include "Utils/TimeSystem.h"
#include "Utils/StreamBuffer.h"
#include "Utils/UtilFunctions.h"
#include "Utils/Pools/BufferPool.h"
#include "Utils/Pools/PacketPool.h"


// ======== ProtoBuffer Includes =========
#include "ProtoBuf/testPacket.pb.h"


// ============ TypeSetting ==============
using ULL = unsigned long long;
using PacketQueue = std::queue<std::unique_ptr<Packet>>;
using Lock = std::lock_guard<std::mutex>;
using SessionID = ULL;

// =============== Macros ================
#define PtrCast(type, data) reinterpret_cast<type>(data)

// =========== Const Data ================
// TODO : ������ �⺻ ���Դϴ�. ���� ����� �� ini���Ϸ� �������� ����� �˴ϴ�.
// TODO : ��ġ�� �����ϰ��� �� ���� ini������ �̿��Ͽ� �����ؾ� �մϴ�.
// .ini������ �������� ������ ���⿡ ������ �⺻������ �����˴ϴ�.
static constexpr int ServerPort = 6060;
static constexpr int PacketHeaderSize = 4;
static constexpr int BufferPoolCount = 512;
static constexpr int SizePerBuffer = 8192; // 8kb
static constexpr int ThreadCount = 4;
static constexpr int PacketPoolCount = 500;

// =========== PacketHeader ==============
enum class PID : short {
	// TODO : ��Ŷ�� ������ �����ϱ� ���� ID�� �߰��ϸ� �˴ϴ�.
	// TODO : ������ �޽����� ���� ���� �ۼ����ּž� �մϴ�.
	Default = 0,
	

};

#pragma pack(push, 1)
struct PacketHeader {
	short _packetId;
	short _packetSize;

};
struct Packet {
	static const int DataSize = 256;
	PacketHeader _header;
	char _data[DataSize];
};
#pragma pack(pop)




#endif