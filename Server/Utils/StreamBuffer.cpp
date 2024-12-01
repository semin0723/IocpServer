#include "StreamBuffer.h"
#include <memory>
#include "Pools/BufferPool.h"

StreamBuffer::StreamBuffer()
{
	BufferPool::GetInstance()->AllocBuffer(_buffer);
	_bufferSize = BufferPool::GetInstance()->GetBufferSize();
}

StreamBuffer::~StreamBuffer()
{
	BufferPool::GetInstance()->ReleaseBuffer(_buffer);
}

int StreamBuffer::Size() const
{
	return _dataSize;
}

int StreamBuffer::Space() const
{
	return _bufferSize - Size();
}

bool StreamBuffer::Empty()
{
	return _dataSize == 0;
}

bool StreamBuffer::Full()
{
	return _dataSize == _bufferSize;
}

bool StreamBuffer::Peek(char* buffer, int len) const
{
	// TODO: buffer�� ������ ���̰� ����ϸ� �Ѱ��ְ�, �����ϸ� ��ŵ�մϴ�.
	if (len > Size()) return false;

	if (_readIdx < _writeIdx) {
		memcpy(buffer, &_buffer[_readIdx], len);
	}
	else {
		if (_readIdx + len < _bufferSize) {
			memcpy(buffer, &_buffer[_readIdx], len);
		}
		else {
			int back = _bufferSize - _readIdx;
			int front = len - back;
			memcpy(buffer, &_buffer[_readIdx], back);
			memcpy(&buffer[back], _buffer, front);
		}
	}
	return true;
}

int StreamBuffer::Read(char* buffer, int len)
{
	// TODO: size�� ����ϸ� size��ŭ �а� size�� ��ȯ�մϴ�. ������ �� ���� ������ ��ŭ�� ��ȯ�մϴ�.
	// TODO: ������� �� �������� �ʽ��ϴ�.
	if (Empty()) return 0;

	int readLen = (std::min)(len, Size());
	if (_readIdx < _writeIdx) {
		memcpy(buffer, &_buffer[_readIdx], readLen);
		//_readIdx += readLen;
	}
	else {
		if (_readIdx + readLen < _bufferSize) {
			memcpy(buffer, &_buffer[_readIdx], readLen);
			//_readIdx = (_readIdx + readLen) % _bufferSize;
		}
		else {
			int back = _bufferSize - _readIdx;
			int front = readLen - back;
			memcpy(buffer, &_buffer[_readIdx], back);
			memcpy(&buffer[back], _buffer, front);
			//_readIdx = front;
		}
	}

	_readIdx = (_readIdx + readLen) % _bufferSize;
	_dataSize -= readLen;

	return readLen;
}

int StreamBuffer::Write(const char* data, int len)
{
	// TODO: ������ �����ϸ� ���� ������ŭ ����, �� ���̸� ��ȯ�մϴ�. ������ �������� �ʽ��ϴ�.
	if (Full()) return 0;
	int writeSpace = Space();
	int writeLen = (std::min)(len, writeSpace);

	if (_writeIdx < _readIdx) {
		memcpy(&_buffer[_writeIdx], data, writeLen);
		//_writeIdx += writeLen;
	}
	else {
		if (_writeIdx + writeLen < _bufferSize) {
			memcpy(&_buffer[_writeIdx], data, writeLen);
			//_writeIdx = (_writeIdx + writeLen) % _bufferSize;
		}
		else {
			int back = _bufferSize - _writeIdx;
			int front = writeLen - back;
			memcpy(&_buffer[_writeIdx], data, back);
			memcpy(_buffer, &data[back], front);
			//_writeIdx = front;
		}
	}
	_writeIdx = (_writeIdx + writeLen) % _bufferSize;
	_dataSize += writeLen;

	return writeLen;
}

void StreamBuffer::BufferClear()
{
	_readIdx = _writeIdx = 0;
	_dataSize = 0;
	memset(_buffer, 0, sizeof(_buffer));
}
