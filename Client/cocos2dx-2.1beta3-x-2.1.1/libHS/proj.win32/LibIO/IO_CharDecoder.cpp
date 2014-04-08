#include "IO_CharDecoder.h"

bool IO_CharDecoder::ReadASCII(IO_InputDataStream* stream, wstring& text)
{
	if(stream == NULL)
	{
		return false;
	}

	size_t length = 0;

	text.resize(IO_CHAR_BUFFER_SIZE);

	while(true)
	{
		wchar_t ch = stream->ReadByte();

		if(length >= text.max_size())
		{
			text.resize(text.max_size() * 2);
		}

		if(ch == 0)
		{
			break;
		}

		if(ch == '\r')
		{
			stream->Skip(1);
		}

		if(ch == '\n')
		{
			break;
		}

		text[length++] = (wchar_t)ch;
	}

	return true;
}

bool IO_CharDecoder::ReadUTF8(IO_InputDataStream* stream, wstring& text)
{
	if(stream == NULL)
	{
		return false;
	}

	int utflen = stream->ReadShort() & 0xffff;
	vector<char> bytes(utflen);	

	stream->ReadFull(&bytes[0], utflen);
	text.resize(utflen);

	int ch1, ch2, ch3;
	int length = 0;
	int index = 0;

	while(length < utflen)
	{
		ch1 = (int) bytes[length] & 0xff;
		switch(ch1 >> 4)
		{
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
			/* 0xxxxxxx*/
			length++;
			text[index++] = (wchar_t)ch1;
			break;
		case 12: case 13:
			/* 110x xxxx   10xx xxxx*/
			length += 2;
			if(length > utflen)
			{
				return false;
			}

			ch2 = (int)bytes[length - 1];
			if((ch2 & 0xC0) != 0x80)
			{
				return false;
			}

			text[index++] = (wchar_t)(((ch1 & 0x1F) << 6) | (ch2 & 0x3F));
			break;
		case 14:
			/* 1110 xxxx  10xx xxxx  10xx xxxx */
			length += 3;
			if(length > utflen)
			{
				return false;
			}

			ch2 = (int)bytes[length - 2];
			ch3 = (int)bytes[length - 1];

			if(((ch2 & 0xC0) != 0x80) || ((ch3 & 0xC0) != 0x80))
			{
				return false;
			}

			text[index++] = (wchar_t)(((ch1 & 0x0F) << 12) | ((ch2 & 0x3F) << 6) | ((ch3 & 0x3F) << 0));
			break;
		default:
			/* 10xx xxxx,  1111 xxxx */
			return false;
		}
	}

	return true;
}

bool IO_CharDecoder::ReadUNICODE(IO_InputDataStream* stream, wstring& text)
{
	if(stream == NULL)
	{
		return false;
	}

	size_t length = 0;

	text.resize(IO_CHAR_BUFFER_SIZE);

	while(true)
	{
		int ch1 = stream->ReadByte() & 0xff;
		int ch2 = stream->ReadByte() & 0xff;
		int ch = ch1 | (ch2 << 8);

		if(length >= text.max_size())
		{
			text.resize(text.max_size() * 2);
		}

		if(ch == 0)
		{
			break;
		}

		if(ch == '\r')
		{
			stream->Skip(2);
		}

		if(ch == '\n')
		{
			break;
		}

		text[length++] = (wchar_t)ch;
	}

	return true;
}

bool IO_CharDecoder::ReadBigEndianUNICODE(IO_InputDataStream* stream, wstring& text)
{
	if(stream == NULL)
	{
		return false;
	}

	size_t length = 0;

	text.resize(IO_CHAR_BUFFER_SIZE);

	while(true)
	{
		wchar_t ch = stream->ReadShort();

		if(length >= text.max_size())
		{
			text.resize(text.max_size() * 2);
		}

		if(ch == 0)
		{
			break;
		}

		if(ch == '\r')
		{
			stream->Skip(2);
		}

		if(ch == '\n')
		{
			break;
		}

		text[length++] = (wchar_t)ch;
	}

	return true;
}

bool IO_CharDecoder::ReadChar(IO_InputDataStream* stream, int encode, wchar_t& ch)
{
	if(stream == NULL)
	{
		return false;
	}

	if(encode == IO_ENCODE_ASCII)
	{
		ch = stream->ReadByte();

		if(ch == '\r')
		{
			if(stream->PeekRead() == '\n')
			{
				stream->Skip(1);
			}
			ch = '\n';
		}

		return true;
	}
	else if(encode == IO_ENCODE_UNICODE)
	{
		int ch1 = stream->ReadByte() & 0xff;
		int ch2 = stream->ReadByte() & 0xff;
		ch = (wchar_t)(ch1 | (ch2 << 8));

		if(ch == '\r')
		{
			char buf[2];
			if(stream->PeekRead(buf, 2) == 2)
			{
				if(buf[0] == '\n' && buf[1] == 0x00)
				{
					stream->Skip(2);
				}
			}
			ch = '\n';
		}

		return true;
	}
	else if(encode == IO_ENCODE_UNICODE_BIG_ENDIAN)
	{
		ch = stream->ReadShort();

		if(ch == '\r')
		{
			char buf[2];
			if(stream->PeekRead(buf, 2) == 2)
			{
				if(buf[0] == 0x00 && buf[1] == '\n')
				{
					stream->Skip(2);
				}
			}

			ch = '\n';
		}

		return true;
	}
	else if(encode == IO_ENCODE_UTF8)
	{
		int ch1, ch2, ch3;
	
		ch1 = stream->ReadByte() & 0xff;

		switch(ch1 >> 4)
		{
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
			/* 0xxxxxxx*/

			ch = (wchar_t)ch1;

			if(ch == '\r')
			{
				if(stream->PeekRead() == '\n')
				{
					stream->Skip(1);
				}
				ch = '\n';
			}
			break;
		case 12: case 13:
			/* 110x xxxx   10xx xxxx*/
			ch2 = stream->ReadByte() & 0xff;

			if ((ch2 & 0xC0) != 0x80)
			{
				return false;
			}

			ch = (wchar_t)(((ch1 & 0x1F) << 6) | (ch2 & 0x3F));
			break;
		case 14:
			/* 1110 xxxx  10xx xxxx  10xx xxxx */
			ch2 = stream->ReadByte() & 0xff;
			ch3 = stream->ReadByte() & 0xff;

			if (((ch2 & 0xC0) != 0x80) || ((ch3 & 0xC0) != 0x80))
			{
				return false;
			}

			ch = (wchar_t)(((ch1 & 0x0F) << 12) | ((ch2 & 0x3F) << 6) | ((ch3 & 0x3F) << 0));
			break;
		default:
			/* 10xx xxxx,  1111 xxxx */
			return false;
		}
	}

	return false;
}
