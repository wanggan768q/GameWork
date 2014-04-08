#include "IO_OutputTextStream.h"
#include "IO_CharEncoder.h"

IO_OutputTextStream::IO_OutputTextStream()
{
	stream = NULL;
	encode = IO_ENCODE_DEFAULT;
}

IO_OutputTextStream::~IO_OutputTextStream()
{

}

bool IO_OutputTextStream::Open(IO_OutputDataStream* stream, int encode)
{
	if(stream == NULL)
	{
		return false;
	}

	switch(encode)
	{
	case IO_ENCODE_ASCII:
		break;
	case IO_ENCODE_UNICODE:
		if(stream->Write(0xff) == 0) return false;
		if(stream->Write(0xfe) == 0) return false;
		break;
	case IO_ENCODE_UNICODE_BIG_ENDIAN:
		if(stream->Write(0xfe) == 0) return false;
		if(stream->Write(0xff) == 0) return false;
		break;
	case IO_ENCODE_UTF8:
		if(stream->Write(0xef) == 0) return false;
		if(stream->Write(0xbb) == 0) return false;
		if(stream->Write(0xbf) == 0) return false;
		break;
	default:
		return false;
	}

	this->stream = stream;
	this->encode = encode;

	return true;
}

void IO_OutputTextStream::Close()
{
	stream = NULL;
	encode = IO_ENCODE_DEFAULT;
}

int IO_OutputTextStream::GetEncode()
{
	return encode;
}

int IO_OutputTextStream::Write(int ch)
{
	if(stream != NULL)
	{
		return stream->Write(ch);
	}

	return -1;
}

int IO_OutputTextStream::Write(const void* buffer, int size)
{
	if(stream != NULL)
	{
		return stream->Write(buffer, size);
	}

	return -1;
}

int IO_OutputTextStream::GetOutputSize()
{
	if(stream == NULL)
	{
		return -1;
	}

	return stream->GetOutputSize();
}

void IO_OutputTextStream::WriteChar(wchar_t data)
{
	if(!IO_CharEncoder::WriteChar(stream, encode, data))
	{
		IOMessageBox("IO_OutputTextStream @ WriteChar throw IO_ERROR_ENCODE");
	}
}

void IO_OutputTextStream::WriteChars(const wchar_t* buffer, int size)
{
	for(int i = 0; i < size; ++i)
	{
		if(!IO_CharEncoder::WriteChar(stream, encode, buffer[i]))
		{
			IOMessageBox("IO_OutputTextStream @ WriteChar throw IO_ERROR_ENCODE");
		}
	}
}

void IO_OutputTextStream::WriteLine(const wstring& text)
{
	WriteChars(&text[0], text.length());
	WriteChar('\n');
}
