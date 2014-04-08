#include "IO_InputDataStream.h"
#include "IO_CharDecoder.h"

IO_InputDataStream::IO_InputDataStream()
{
	stream = NULL;
}

IO_InputDataStream::~IO_InputDataStream()
{
	Close();
}

bool IO_InputDataStream::Open(IO_InputStream* stream)
{
	if(stream == NULL)
	{
		return false;
	}

	this->stream = stream;

	return true;
}

void IO_InputDataStream::Close()
{
	stream = NULL;
}

int IO_InputDataStream::Read()
{
	if(stream == NULL)
	{
		IOMessageBox("IO_InputDataStream @ Read throw -1");
		return -1;
	}

	return stream->Read();
}

int IO_InputDataStream::Read(void* buffer, int size)
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->Read(buffer, size);
}

int IO_InputDataStream::Seek(int offset, int origin)
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->Seek(offset, origin);
}

int IO_InputDataStream::GetPosition()
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->GetPosition();
}

int IO_InputDataStream::GetInputSize()
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->GetInputSize();
}

char IO_InputDataStream::ReadByte()
{
	int ch = Read();
	if(ch == -1)
	{
		return 0;
	}

	return (char)ch;
}

short IO_InputDataStream::ReadShort()
{
	int ch1 = Read();
	int ch2 = Read();

	if(ch1 == -1 || ch2 == -1)
	{
		IOMessageBox("IO_InputDataStream @ ReadShort throw -1");
		return -1;
	}

	return (short)((ch1 << 8) | ch2);
}

int IO_InputDataStream::ReadInt()
{
	int ch1 = Read();
	int ch2 = Read();
	int ch3 = Read();
	int ch4 = Read();

	if(ch1 == -1 || ch2 == -1 || ch3 == -1 || ch4 == -1)
	{
		IOMessageBox("IO_InputDataStream @ ReadInt throw -1");
		return -1;
	}

	return ((ch1 << 24) | (ch2 << 16) | (ch3 << 8) | ch4);
}

int64 IO_InputDataStream::ReadInt64()
{
	return ((int64)(ReadInt()) << 32) + (ReadInt() & 0xffffffffL);
}

wstring IO_InputDataStream::ReadString(int encode/* = IO_ENCODE_UTF8*/)
{
	wstring text;

	if(encode == IO_ENCODE_ASCII)
	{
		if(!IO_CharDecoder::ReadASCII(this, text))
		{
			IOMessageBox("IO_InputDataStream @ ReadString @ ReadASCII is NULL ");
			return wstring();
		}

		return text;
	}
	else if(encode == IO_ENCODE_UNICODE)
	{
		if(!IO_CharDecoder::ReadUNICODE(this, text))
		{
			IOMessageBox("IO_InputDataStream @ ReadString @ ReadUNICODE is NULL ");
			return wstring();
		}

		return text;
	}
	else if(encode == IO_ENCODE_UNICODE_BIG_ENDIAN)
	{
		if(!IO_CharDecoder::ReadBigEndianUNICODE(this, text))
		{
			IOMessageBox("IO_InputDataStream @ ReadString @ ReadBigEndianUNICODE is NULL ");
			return wstring();
		}

		return text;
	}
	else if(encode == IO_ENCODE_UTF8)
	{
		if(!IO_CharDecoder::ReadUTF8(this, text))
		{
			IOMessageBox("IO_InputDataStream @ ReadString @ ReadUTF8 is NULL ");
			return wstring();
		}

		return text;
	}

	IOMessageBox("IO_InputDataStream @ ReadString is NULL ");
	return wstring();
}

void IO_InputDataStream::ReadFull(void* buffer, int size)
{
	if(Read(buffer, size) != size)
	{
		IOMessageBox("IO_InputDataStream @ ReadFull is Error ");
		return ;
	}
}
