#include "BufferPool.h"

ImplSingleton(BufferPool)

BufferPool::~BufferPool()
{
	for (auto& block : _memoryChunk) {
		free(block._memoryBlock);
		free(block._memoryUseFlag);
	}
}

void BufferPool::Initialize(int sizePerBuffer, int bufferCount)
{
	_sizePerBuffer = sizePerBuffer;
	_bufferCount = bufferCount;

	CreateMemoryBlock();
}

void BufferPool::AllocBuffer(char*& buf)
{
	LockGuard lock(_mtx);
	
	for (auto it = _memoryChunk.begin(); it != _memoryChunk.end(); it++) {
		if ((*it)._useCount == _bufferCount) {
			continue;
		}
		for (int i = 0; i < _bufferCount; i++) {
			if ((*it)._memoryUseFlag[i] == false) {
				(*it)._memoryUseFlag[i] = true;
				buf = &(*it)._memoryBlock[i * _sizePerBuffer];
				(*it)._useCount += 1;
				return;
			}
		}
	}
	CreateMemoryBlock();
	buf = _memoryChunk.back()._memoryBlock;
}

void BufferPool::ReleaseBuffer(char*& buf)
{
	LockGuard lock(_mtx);

	for (auto it = _memoryChunk.begin(); it != _memoryChunk.end(); it++) {
		if ((*it)._useCount == 0) {
			continue;
		}
		for (int i = 0; i < _bufferCount; i++) {
			char* ptr = &(*it)._memoryBlock[i * _sizePerBuffer];
			if (ptr == buf) {
				(*it)._memoryUseFlag[i] = false;
				buf = nullptr;
				(*it)._useCount -= 1;
				return;
			}
		}
	}
}

void BufferPool::CreateMemoryBlock()
{
	size_t blockSize = sizeof(char) * _sizePerBuffer * _bufferCount;
	char* memoryBlock = (char*)malloc(blockSize);
	bool* memoryUseFlag = (bool*)malloc(sizeof(bool) * _bufferCount);
	memset(memoryBlock, 0, blockSize);
	memset(memoryUseFlag, 0, sizeof(bool) * _bufferCount);

	_memoryChunk.emplace_back(memoryBlock, memoryUseFlag);
}
