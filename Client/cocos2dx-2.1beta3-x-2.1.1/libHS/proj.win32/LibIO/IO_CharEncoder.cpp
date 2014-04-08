#include "IO_CharEncoder.h"

bool IO_CharEncoder::WriteASCII(IO_OutputDataStream* stream, const wstring& text)
{
	if(stream == NULL)
	{
		return false;
	}

	string ascii;
	ascii.resize(text.length());

	for(size_t i = 0; i < text.length(); ++i)
	{
		ascii[i] = (char)text[i];
	}

	stream->WriteFull(&ascii[0], ascii.length());

	return true;
}

bool IO_CharEncoder::WriteUTF8(IO_OutputDataStream* stream, const wstring& text)
{
	if(stream == NULL)
	{
		return false;
	}

	wchar_t ch;

	int utflen = 0;
	for(size_t i = 0; i < text.length(); ++i)
	{
		ch = text[i];

		if((ch >= 0x0001) && (ch <= 0x007F))
		{
			utflen++;
		}
		else if(ch > 0x07FF)
		{
			utflen += 3;
		}
		else
		{
			utflen += 2;
		}
	}

	if(utflen > 65535)
	{
		return false;
	}

	string utf;
	utf.resize(utflen + 2);

	int index = 0;

	utf[index++] = (char)((utflen >> 8) & 0xFF);
	utf[index++] = (char)((utflen >> 0) & 0xFF);

	for (size_t i = 0; i < text.length(); i++)
	{
		ch = text[i];

		if((ch >= 0x0001) && (ch <= 0x007F))
		{
			utf[index++] = (char) ch;
		}
		else if(ch > 0x07FF)
		{
			utf[index++] = (char) (0xE0 | ((ch >> 12) & 0x0F));
			utf[index++] = (char) (0x80 | ((ch >>  6) & 0x3F));
			utf[index++] = (char) (0x80 | ((ch >>  0) & 0x3F));
		}
		else
		{
			utf[index++] = (char) (0xC0 | ((ch >>  6) & 0x1F));
			utf[index++] = (char) (0x80 | ((ch >>  0) & 0x3F));
		}
	}

	stream->WriteFull(&utf[0], index);

	return true;
}

bool IO_CharEncoder::WriteUNICODE(IO_OutputDataStream* stream, const wstring& text)
{
	if(stream == NULL)
	{
		return false;
	}

	for(size_t i = 0; i < text.length(); ++i)
	{
		wchar_t ch = text[i];

		int ch1 = (ch >> 8) & 0xff;
		int ch2 = ch & 0xff;

		stream->WriteByte(ch1);
		stream->WriteByte(ch2);
	}

	return true;
}

bool IO_CharEncoder::WriteBigEndianUNICODE(IO_OutputDataStream* stream, const wstring& text)
{
	if(stream == NULL)
	{
		return false;
	}

	stream->WriteFull(&text[0], text.length() * 2);

	return true;
}

bool IO_CharEncoder::WriteChar(IO_OutputDataStream* stream, int encode, wchar_t ch)
{
	if(stream == NULL)
	{
		return false;
	}

	if(encode == IO_ENCODE_ASCII)
	{
		if(ch == '\n')
		{
			stream->WriteByte('\r');
		}

		stream->WriteByte((char)ch);

		return true;
	}
	else if(encode == IO_ENCODE_UNICODE)
	{
		if(ch == '\n')
		{
			stream->WriteByte('\r');
			stream->WriteByte(0);
		}

		stream->WriteByte((char)ch);
		stream->WriteByte((char)(ch >> 8));

		return true;
	}
	else if(encode == IO_ENCODE_UNICODE_BIG_ENDIAN)
	{
		if(ch == '\n')
		{
			stream->WriteByte(0);
			stream->WriteByte('\r');
		}

		stream->WriteByte((char)(ch >> 8));
		stream->WriteByte((char)ch);

		return true;
	}
	else if(encode == IO_ENCODE_UTF8)
	{
		if((ch >= 0x0001) && (ch <= 0x007F))
		{
			if(ch == '\n')
			{
				stream->WriteByte('\r');
			}

			stream->WriteByte((char)ch);
		}
		else if (ch > 0x07FF)
		{
			stream->WriteByte((char) (0xE0 | ((ch >> 12) & 0x0F)));
			stream->WriteByte((char) (0x80 | ((ch >>  6) & 0x3F)));
			stream->WriteByte((char) (0x80 | ((ch >>  0) & 0x3F)));
		}
		else
		{
			stream->WriteByte((char) (0xC0 | ((ch >>  6) & 0x1F)));
			stream->WriteByte((char) (0x80 | ((ch >>  0) & 0x3F)));
		}

		return true;
	}

	return false;
}
