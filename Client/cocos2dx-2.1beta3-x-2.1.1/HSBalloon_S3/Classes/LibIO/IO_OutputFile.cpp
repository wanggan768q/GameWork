#include "IO_OutputFile.h"

IO_OutputFile::IO_OutputFile()
{
	file = NULL;
}

IO_OutputFile::~IO_OutputFile()
{
	Close();
}

bool IO_OutputFile::Open(const wstring& name)
{
	Close();

	string s;
	s.resize(name.length());
	for(size_t i = 0; i < name.length(); ++i) s[i] = (char)name[i];

	file = fopen(s.c_str(), "wb");
	if(file == NULL)
	{
		return false;
	}

	return true;
}

void IO_OutputFile::Close()
{
	if(file != NULL)
	{
		fclose(file);
		file = NULL;
	}
}

void IO_OutputFile::Flush()
{
	fflush(file);
}

int IO_OutputFile::Write(int ch)
{
	char ch1 = ch & 0xff;

	int writeSize = fwrite(&ch1, 1, 1, file);

	return writeSize;
}

int IO_OutputFile::Write(const void* buffer, int size)
{
	if(buffer == NULL || size == 0)
	{
		return 0;
	}

	int ret = fwrite(buffer, 1, size, file);

	return ret;
}

int IO_OutputFile::GetOutputSize()
{
	if(file == NULL)
	{
		return -1;
	}

	int temp = ftell(file);
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, temp, SEEK_SET);

	return size;
}

