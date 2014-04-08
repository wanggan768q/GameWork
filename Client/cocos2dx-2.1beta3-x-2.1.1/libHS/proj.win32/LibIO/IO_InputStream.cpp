#include "IO_InputStream.h"

int IO_InputStream::Read(void* buffer, int size)
{
	char* bytes = (char*)buffer;
	int readSize;

	for(readSize = 0; readSize < size; ++readSize)
	{
		int ch = Read();
		if(ch == -1)
		{
			break;
		}

		bytes[readSize] = (char)(ch & 0xff);
	}

	return readSize;
}

int IO_InputStream::PeekRead()
{
	int ch = Read();
	if(ch == -1)
	{
		return -1;
	}

	Seek(-1, IO_SEEK_CURRENT);

	return ch;
}

int IO_InputStream::PeekRead(void* buffer, int size)
{
	int readSize = Read(buffer, size);
	if(readSize == 0)
	{
		return 0;
	}

	Seek(-readSize, IO_SEEK_CURRENT);

	return readSize;
}

