#include "IO_OutputBuffer.h"

IO_OutputBuffer::IO_OutputBuffer()
{
	buffer = NULL;
	size = 0;
	position = 0;
	growSize = 0;
	maxSize = 0;
}

IO_OutputBuffer::~IO_OutputBuffer()
{
	Close();
}

bool IO_OutputBuffer::Open(int initSize, int growSize)
{
	Close();

	buffer = new char[initSize];
	if(buffer == NULL)
	{
		return false;
	}

	maxSize = initSize;
	size = 0;
	position = 0;
	growSize = growSize;

	return true;
}

void IO_OutputBuffer::Close()
{
	if(buffer != NULL)
	{
		delete [] buffer;
		buffer = NULL;

		size = 0;
		position = 0;
		growSize = 0;
		maxSize = 0;
	}
}

void* IO_OutputBuffer::GetBase()
{
	return buffer;
}

void* IO_OutputBuffer::GetBuffer()
{
	return buffer + position;
}

int IO_OutputBuffer::Seek(int offset, int origin)
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
		temp = size + offset;
		break;
	}

	if(temp < 0)
	{
		temp = 0;
	}

	if(temp > size)
	{
		temp = size;
	}

	position = temp;

	return position;
}

int IO_OutputBuffer::Write(int ch)
{
	if(position + 1 > maxSize)
	{
		Grow(maxSize * 2);
	}

	buffer[position++] = (char)(ch & 0xff);
	if(position > size)
	{
		++size;
	}

	return 1;
}

int IO_OutputBuffer::Write(const void* buffer, int size)
{
	if(position + size > maxSize)
	{
		Grow(max(maxSize * 2, size));
	}

	memcpy(this->buffer + position, buffer, size);

	position += size;
	this->size += size;

	return size;
}

int IO_OutputBuffer::GetOutputSize()
{
	return size;
}

void IO_OutputBuffer::SetSize(int size)
{
	if(size <= maxSize)
	{
		this->size = size;
	}
}

int IO_OutputBuffer::GetMaxSize()
{
	return maxSize;
}

void IO_OutputBuffer::Grow(int newSize)
{
	if(newSize < 1024 && maxSize < 1024)
	{
		newSize = 1024;
	}

	char* newBuffer = new char[newSize];
	
	memcpy(newBuffer, buffer, size);
	delete [] buffer;
	buffer = newBuffer;
}


