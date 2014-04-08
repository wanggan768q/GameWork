#include "IO_OutputDataStream.h"
#include "IO_CharEncoder.h"

IO_OutputDataStream::IO_OutputDataStream()
{
	stream = NULL;
}

IO_OutputDataStream::~IO_OutputDataStream()
{

}

bool IO_OutputDataStream::Open(IO_OutputStream* stream)
{
	if(stream == NULL)
	{
		return false;
	}

	this->stream = stream;

	return true;
}

void IO_OutputDataStream::Close()
{
	stream = NULL;
}

int IO_OutputDataStream::Write(int ch)
{
	if(stream != NULL)
	{
		return stream->Write(ch);
	}

	return -1;
}

int IO_OutputDataStream::Write(const void* buffer, int size)
{
	if(stream != NULL)
	{
		return stream->Write(buffer, size);
	}

	return -1;
}

int IO_OutputDataStream::GetOutputSize()
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->GetOutputSize();
}

void IO_OutputDataStream::WriteByte(char data)
{
	if(stream != NULL)
	{
		int ch = data & 0xff;
		if(stream->Write(ch) != 1)
		{
			IOMessageBox("IO_OutputDataStream @ WriteByte throw IO_ERROR_OVERFLOW");
		}
	}
}

void IO_OutputDataStream::WriteShort(short data)
{
	if(stream != NULL)
	{
		int ch1 = (data >> 8) & 0xff;
		int ch2 = data & 0xff;

		if(stream->Write(ch1) != 1 || stream->Write(ch2) != 1)
		{
			IOMessageBox("IO_OutputDataStream @ WriteShort throw IO_ERROR_OVERFLOW");
		}
	}
}

void IO_OutputDataStream::WriteInt(int data)
{
	if(stream != NULL)
	{
		int ch1 = (data >> 24) & 0xff;
		int ch2 = (data >> 16) & 0xff;
		int ch3 = (data >> 8) & 0xff;
		int ch4 = data & 0xff;

		if(stream->Write(ch1) != 1 || stream->Write(ch2) != 1 || stream->Write(ch3) != 1 || stream->Write(ch4) != 1)
		{
			IOMessageBox("IO_OutputDataStream @ WriteInt throw IO_ERROR_OVERFLOW");
		}
	}
}

void IO_OutputDataStream::WriteInt64(int64 data)
{
	int ch1 = (data >> 56) & 0xff;
	int ch2 = (data >> 48) & 0xff;
	int ch3 = (data >> 40) & 0xff;
	int ch4 = (data >> 32) & 0xff;
	int ch5 = (data >> 24) & 0xff;
	int ch6 = (data >> 16) & 0xff;
	int ch7 = (data >> 8) & 0xff;
	int ch8 = data & 0xff;

	if(stream->Write(ch1) != 1 || stream->Write(ch2) != 1 || 
		stream->Write(ch3) != 1 || stream->Write(ch4) != 1 ||
		stream->Write(ch5) != 1 || stream->Write(ch6) != 1 || 
		stream->Write(ch7) != 1 || stream->Write(ch8) != 1)
	{
		IOMessageBox("IO_OutputDataStream @ WriteInt64 throw IO_ERROR_OVERFLOW");
	}
}

void IO_OutputDataStream::WriteString(const wstring& text, int encode/* = IO_ENCODE_UTF8*/)
{
	if(encode == IO_ENCODE_ASCII)
	{
		if(!IO_CharEncoder::WriteASCII(this, text))
		{
			IOMessageBox("IO_OutputDataStream @ WriteString throw IO_ERROR_ENCODE");
		}
	}
	else if(encode == IO_ENCODE_UNICODE)
	{
		if(!IO_CharEncoder::WriteUNICODE(this, text))
		{
			IOMessageBox("IO_OutputDataStream @ WriteString throw IO_ERROR_ENCODE");
		}
	}
	else if(encode == IO_ENCODE_UNICODE_BIG_ENDIAN)
	{
		if(!IO_CharEncoder::WriteBigEndianUNICODE(this, text))
		{
			IOMessageBox("IO_OutputDataStream @ WriteString throw IO_ERROR_ENCODE");
		}
	}
	else if(encode == IO_ENCODE_UTF8)
	{
		if(!IO_CharEncoder::WriteUTF8(this, text))
		{
			IOMessageBox("IO_OutputDataStream @ WriteString throw IO_ERROR_ENCODE");
		}
	}
	else
	{
		IOMessageBox("IO_OutputDataStream @ WriteString throw IO_ERROR_ENCODE");
	}
}

void IO_OutputDataStream::WriteFull(const void* buffer, int size)
{
	if(Write(buffer, size) != size)
	{
		IOMessageBox("IO_OutputDataStream @ WriteFull throw IO_ERROR_OVERFLOW");
	}
}
