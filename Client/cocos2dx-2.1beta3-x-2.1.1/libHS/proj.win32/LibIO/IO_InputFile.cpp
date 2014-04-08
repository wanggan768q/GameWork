#include "IO_InputFile.h"

IO_InputFile::IO_InputFile()
{
	file = NULL;
}

IO_InputFile::~IO_InputFile()
{
	Close();
}

bool IO_InputFile::Open(const wstring& name)
{
	Close();

	string s;
	s.resize(name.length());
	for(size_t i = 0; i < name.length(); ++i) s[i] = (char)name[i];
	file = fopen(s.c_str(), "rb");
	if(file == NULL)
	{
		return false;
	}

	return true;
}

void IO_InputFile::Close()
{
	if(file != NULL)
	{
		fclose(file);
		file = NULL;
	}
}

int IO_InputFile::Read()
{
	char ch;
	if(fread(&ch, 1, 1, file) == 1)
	{
		return ch & 0xff;
	}

	return -1;
}

int IO_InputFile::Read(void* buffer, int size)
{
	if(buffer == NULL || size == 0)
	{
		return 0;
	}

	int ret = fread(buffer, 1, size, file);

	return ret;
}

int IO_InputFile::Seek(int offset, int origin)
{
	fseek(file, offset, origin);

	return GetPosition();
}

int IO_InputFile::GetPosition()
{
	int position = ftell(file);

	return position;
}

int IO_InputFile::GetInputSize()
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


