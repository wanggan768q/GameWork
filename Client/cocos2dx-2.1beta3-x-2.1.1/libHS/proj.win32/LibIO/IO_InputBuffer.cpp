#include "IO_InputBuffer.h"

IO_InputBuffer::IO_InputBuffer()
{
	buffer = NULL;
	maxSize = 0;
	position = 0;
}

IO_InputBuffer::~IO_InputBuffer()
{
	Close();
}

bool IO_InputBuffer::Open(const void* buffer, int size)
{
	if(buffer == NULL)
	{
		return false;
	}

	Close();

	this->buffer = (char*)buffer;
	this->maxSize = size;
	this->position = 0;

	return true;
}

void IO_InputBuffer::Close()
{
	buffer = NULL;
	maxSize = 0;
	position = 0;
}

void* IO_InputBuffer::GetBase()
{
	return buffer;
}

void* IO_InputBuffer::GetBuffer()
{
	return buffer + position;
}

int IO_InputBuffer::Read()
{
	if(position < maxSize)
	{
		return buffer[position++] & 0xff;
	}

	return -1;
}

int IO_InputBuffer::Read(void* buffer, int size)
{
	if(position < maxSize)
	{
		int minSize = min(size, maxSize - position);

		memcpy(buffer, this->buffer + position, minSize);

		position += minSize;

		return minSize;
	}

	return 0;
}

int IO_InputBuffer::Seek(int offset, int origin)
{
	int temp;

	switch(origin)
	{
	case IO_SEEK_BEGIN:
		temp = offset;
		break;
	case IO_SEEK_CURRENT:
		temp = position + offset;
		break;
	case IO_SEEK_END:
		temp = maxSize + offset;
		break;
	}

	if(temp < 0)
	{
		temp = 0;
	}

	if(temp > maxSize)
	{
		temp = maxSize;
	}

	position = temp;

	return position;
}

int IO_InputBuffer::GetPosition()
{
	return position;
}

int IO_InputBuffer::GetInputSize()
{
	return maxSize;
}


