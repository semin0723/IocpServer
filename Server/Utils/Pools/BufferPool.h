#ifndef _BUFFERPOOL_
#define _BUFFERPOOL_

#include <memory>
#include <list>
#include <mutex>
#include "../../Pattern.h"

class BufferPool {
	struct MemoryBlock {
		char* _memoryBlock = nullptr;
		bool* _memoryUseFlag = nullptr;
		unsigned long long _useCount = 0;
	};
	using MemoryChunk = std::list<MemoryBlock>;
	using LockGuard = std::lock_guard<std::mutex>;

	DeclSingleton(BufferPool)

public:
	BufferPool() = default;
	~BufferPool();

	// TODO : Server Initial할 때 같이 해줘야 합니다.
	void Initialize(int sizePerBuffer, int bufferCount);

	void AllocBuffer(char*& buf);
	void ReleaseBuffer(char*& buf);

	const int GetBufferSize() const { return _sizePerBuffer; }

private:
	int _sizePerBuffer = 0;
	int _bufferCount = 0;
	MemoryChunk _memoryChunk;
	std::mutex _mtx;

	void CreateMemoryBlock();
	
private:
	
	BufferPool(BufferPool&) = delete;
	BufferPool(BufferPool&&) = delete;
	BufferPool& operator=(BufferPool&) = delete;
	BufferPool&& operator=(BufferPool&&) = delete;
};

#endif