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
// TODO : 클라이언트에서는 주석을 걸어주세요.
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
// TODO : 설정의 기본 값입니다. 이후 빌드될 때 ini파일로 설정값이 출력이 됩니다.
// TODO : 수치를 변경하고자 할 때는 ini파일을 이용하여 설정해야 합니다.
// .ini파일이 존재하지 않으면 여기에 설정된 기본값으로 설정됩니다.
static constexpr int ServerPort = 6060;
static constexpr int PacketHeaderSize = 4;
static constexpr int BufferPoolCount = 512;
static constexpr int SizePerBuffer = 8192; // 8kb
static constexpr int ThreadCount = 4;
static constexpr int PacketPoolCount = 500;

// =========== PacketHeader ==============
enum class PID : short {
	// TODO : 패킷의 유형을 구분하기 위한 ID를 추가하면 됩니다.
	// TODO : 전달할 메시지의 유형 전부 작성해주셔야 합니다.
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