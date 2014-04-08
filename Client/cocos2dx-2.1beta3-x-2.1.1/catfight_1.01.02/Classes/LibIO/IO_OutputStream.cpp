#include "IO_OutputStream.h"

int IO_OutputStream::Write(const void* buffer, int size)
{
	char* bytes = (char*)buffer;
	int writeSize;

	for(writeSize = 0; writeSize < size; ++writeSize)
	{
		int ch = bytes[writeSize] & 0xff;

		if(Write(ch) != 1)
		{
			break;
		}
	}

	return writeSize;
}
