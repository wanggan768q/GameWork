#include "IO_CircularBuffer.h"

IO_CircularBuffer::IO_CircularBuffer()
{
	buffer = NULL;
	maxSize = 0;
	available = 0;
	readPosition = 0;
	writePosition = 0;
}

IO_CircularBuffer::~IO_CircularBuffer()
{
	Close();
}

bool IO_CircularBuffer::Open(int initSize)
{
	Close();

	buffer = new char[initSize];
	if(buffer == NULL)
	{
		return false;
	}

	maxSize = initSize;
	available = 0;
	readPosition = 0;
	writePosition = 0;

	return true;
}

void IO_CircularBuffer::Close()
{
	if(buffer != NULL)
	{
		delete buffer;
		buffer = NULL;

		maxSize = 0;
		available = 0;
		readPosition = 0;
		writePosition = 0;
	}
}

int IO_CircularBuffer::Read()
{
	if(available == 0) 
	{
		return -1;
	}

	int ch = buffer[readPosition] & 0xff;
	readPosition = (readPosition + 1) %  maxSize;

	--available;

	return ch;
}

int IO_CircularBuffer::Read(void* buffer, int size)
{
	if(available == 0) 
	{
		return -1;
	}

	int readSize = min(size, available);
	char* bytes = (char*)buffer;

	if(readPosition + readSize >= maxSize)
	{
		int rightSize = maxSize - readPosition - 1;

		memcpy(bytes, this->buffer + readPosition, rightSize);
		memcpy(bytes + rightSize, this->buffer, readSize - rightSize);

		readPosition = readSize - rightSize;
	}
	else
	{
		memcpy(bytes, this->buffer + readPosition, readSize);
		readPosition += readSize;
	}

	available -= readSize;

	return readSize;
}

int IO_CircularBuffer::PeekRead()
{
	if(available == 0) 
	{
		return -1;
	}

	int ch = buffer[readPosition] & 0xff;

	return ch;
}

int IO_CircularBuffer::PeekRead(void* buffer, int size)
{
	if(available == 0) 
	{
		return -1;
	}

	int readSize = min(size, available);
	char* bytes = (char*)buffer;

	if(readPosition + readSize >= maxSize)
	{
		int rightSize = maxSize - readPosition - 1;

		memcpy(bytes, this->buffer + readPosition, rightSize);
		memcpy(bytes + rightSize, buffer, readSize - rightSize);
	}
	else
	{
		memcpy(bytes, this->buffer + readPosition, readSize);
	}

	return readSize;
}

int IO_CircularBuffer::Skip(int size)
{
	int s = min(available, size);

	readPosition = (readPosition + s) %  maxSize;
	available -= s;

	return 0;
}

int IO_CircularBuffer::Write(int ch)
{
	if(available == maxSize)
	{
		return -1;
	}

	buffer[writePosition] = (char) ch;
	writePosition = (writePosition + 1) %  maxSize;

	++available;

	return 1;
}

int IO_CircularBuffer::Write(const void* buffer, int size)
{
	if(available == maxSize)
	{
		return -1;
	}

	int writeSize = min(size, maxSize - available);
	char* bytes = (char*)buffer;

	if(writePosition + writeSize >= maxSize)
	{
		int rightSize = maxSize - writePosition - 1;

		memcpy(this->buffer + writePosition, bytes, rightSize);
		memcpy(this->buffer, bytes + rightSize, writeSize - rightSize);

		writePosition = writeSize - rightSize;
	}
	else
	{
		memcpy(this->buffer + writePosition, bytes, writeSize);
		writePosition += writeSize;
	}

	available += writeSize;

	return writeSize;
}

