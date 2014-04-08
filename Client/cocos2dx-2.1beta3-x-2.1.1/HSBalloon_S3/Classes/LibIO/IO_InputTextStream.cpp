#include "IO_InputTextStream.h"
#include "IO_CharDecoder.h"

IO_InputTextStream::IO_InputTextStream()
{
	stream = NULL;
	encode = IO_ENCODE_DEFAULT;
}

IO_InputTextStream::~IO_InputTextStream()
{
	Close();
}

bool IO_InputTextStream::Open(IO_InputDataStream* stream, int encode)
{
	if(stream == NULL)
	{
		return false;
	}

	if(encode == IO_ENCODE_DEFAULT)
	{
		if(stream->GetInputSize() <= 1)
		{
			encode = IO_ENCODE_ASCII;
		}
		else
		{
			unsigned char bom[2];
			if(stream->PeekRead(bom, 2) != 2)
			{
				return false;
			}

			if(bom[0] == 0xff && bom[1] == 0xfe)
			{
				encode = IO_ENCODE_UNICODE;
				stream->Skip(2);
			}
			else if(bom[0] == 0xfe && bom[1] == 0xff)
			{
				encode = IO_ENCODE_UNICODE_BIG_ENDIAN;
				stream->Skip(2);
			}
			else if(bom[0] == 0xef && bom[1] == 0xbb)
			{
				stream->Skip(2);
				if(stream->Read() != 0xbf)
				{
					return false;
				}

				encode = IO_ENCODE_UTF8;
			}
			else
			{
				encode = IO_ENCODE_ASCII;
			}
		}
	}

	this->stream = stream;
	this->encode = encode;

	return true;
}

void IO_InputTextStream::Close()
{
	stream = NULL;
	encode = IO_ENCODE_DEFAULT;
}

int IO_InputTextStream::GetEncode()
{
	return encode;
}

int IO_InputTextStream::Read()
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->Read();
}

int IO_InputTextStream::Read(void* buffer, int size)
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->Read(buffer, size);
}

int IO_InputTextStream::Seek(int offset, int origin)
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->Seek(offset, origin);
}

int IO_InputTextStream::GetPosition()
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->GetPosition();
}

int IO_InputTextStream::GetInputSize()
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->GetInputSize();
}

wchar_t IO_InputTextStream::ReadChar()
{
	wchar_t ch;
	if(!IO_CharDecoder::ReadChar(stream, encode, ch))
	{
		IOMessageBox("IO_InputTextStream @ ReadChar throw IO_ERROR_ENCODE");
	}

	return ch;
}

int IO_InputTextStream::ReadChars(wchar_t* buffer, int size)
{
	int readSize;

	for(readSize = 0; readSize < size; ++readSize)
	{
		buffer[readSize] = ReadChar();
	}

	return readSize;
}

wstring IO_InputTextStream::ReadLine()
{
	wstring line;

	for(size_t length = 0; true; ++length)
	{
		wchar_t ch = ReadChar();

		if(ch == '\n')
		{
			break;
		}

		if(length >= line.max_size())
		{
			line.resize(line.max_size() * 2);
		}

		line[length++] = ch;
	}

	return line;
}
