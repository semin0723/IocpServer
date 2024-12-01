#ifndef _SERVERMAIN_
#define _SERVERMAIN_

#include "NetDefine.h"

// Server, Client 공통으로 가져가야할 부분.
// 이 클래스를 사용함으로써 서버 - 클라이언트 사이의 통신을 수행함.
class ServerMain
{
public:
	ServerMain() = default;
	~ServerMain() = default;

	void Initialize();

private:
	
};

#endif