#include "HSWriteData.h"


HSWriteData::HSWriteData(const char* zrFileName)
{
	m_pFile = NULL;
	Open(zrFileName);
}


HSWriteData::~HSWriteData(void)
{
	if (m_pFile)
	{
		fclose(m_pFile);
		m_pFile = 0;
	}
}

int HSWriteData::WriteByte( char v )
{
	HSAssert(m_pFile,"");
	return fwrite(&v,sizeof(char),1,m_pFile);
}

void HSWriteData::WriteUByte( unsigned char v )
{
	HSAssert(m_pFile,"");
	fwrite(&v,sizeof(unsigned char),1,m_pFile);
}

void HSWriteData::WriteShort( short v )
{
	HSAssert(m_pFile,"");
	int ch1 = (v >> 8) & 0xff;
	int ch2 = v & 0xff;
	WriteByte(ch1);
	WriteByte(ch2);
}

void HSWriteData::WriteUShort( unsigned short v )
{
	HSAssert(m_pFile,"");
	int ch1 = (v >> 8) & 0xff;
	int ch2 = v & 0xff;
	WriteByte(ch1);
	WriteByte(ch2);
}

void HSWriteData::WriteInt( int v )
{
	HSAssert(m_pFile,"");
	int ch1 = (v >> 24) & 0xff;
	int ch2 = (v >> 16) & 0xff;
	int ch3 = (v >> 8) & 0xff;
	int ch4 = v & 0xff;

	WriteByte(ch1);
	WriteByte(ch2);
	WriteByte(ch3);
	WriteByte(ch4);
}

void HSWriteData::WriteUint( unsigned int v )
{
	HSAssert(m_pFile,"");
	int ch1 = (v >> 24) & 0xff;
	int ch2 = (v >> 16) & 0xff;
	int ch3 = (v >> 8) & 0xff;
	int ch4 = v & 0xff;

	WriteByte(ch1);
	WriteByte(ch2);
	WriteByte(ch3);
	WriteByte(ch4);
}

void HSWriteData::WriteFloat( float v )
{
	int vv = (int)(v * 100.f);
	HSAssert(m_pFile,"");
	WriteInt(vv);
}

bool HSWriteData::WriteIntArrayWithLengthInt( int* buf,int size )
{
	HSAssert(m_pFile,"");
	for (int i=0;i<size;++i)
	{
		WriteInt(buf[i]);
	}
	return true;
}

bool HSWriteData::WriteStringArrayWithLengthInt( std::string* buf,int size )
{
	HSAssert(m_pFile,"");
	int index = 0;
	for (int i=0;i<size;++i)
	{
		std::string data = buf[i];
		if (WriteUTF8(data.c_str()))
		{
			++index;
		}
		
	}
	return index == size ? true : false;
}

bool HSWriteData::WriteUTF8( const char* s )
{
	std::string str = s;

	wstring text = HSBase::GetWstringWithString(str);

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

	this->Write(&utf[0],index);


	return true;
}

bool HSWriteData::Open( const char* zrFileName )
{
	HS_fopen(m_pFile,zrFileName,"w+");
	if (m_pFile)
	{
		return true;
	}
	return false;
}

int HSWriteData::Write( const void* pBuf,int size )
{
	char* bytes = (char*)pBuf;
	int writeSize;

	for(writeSize = 0; writeSize < size; ++writeSize)
	{
		char ch = bytes[writeSize] & 0xff;

		if(WriteByte(ch) != 1)
		{
			break;
		}
	}
	return writeSize;
}

void HSWriteData::WriteInt64(long long v)
{
	HSAssert(m_pFile,"");
	int ch1 = (v >> 56) & 0xff;
	int ch2 = (v >> 48) & 0xff;
	int ch3 = (v >> 40) & 0xff;
	int ch4 = (v >> 32) & 0xff;
	int ch5 = (v >> 24) & 0xff;
	int ch6 = (v >> 16) & 0xff;
	int ch7 = (v >> 8) & 0xff;
	int ch8 = v & 0xff;

	WriteByte(ch1);
	WriteByte(ch2);
	WriteByte(ch3);
	WriteByte(ch4);
	WriteByte(ch5);
	WriteByte(ch6);
	WriteByte(ch7);
	WriteByte(ch8);
}

void HSWriteData::WriteUInt64( unsigned long long v )
{
	HSAssert(m_pFile,"");

	int ch1 = (v >> 56) & 0xff;
	int ch2 = (v >> 48) & 0xff;
	int ch3 = (v >> 40) & 0xff;
	int ch4 = (v >> 32) & 0xff;
	int ch5 = (v >> 24) & 0xff;
	int ch6 = (v >> 16) & 0xff;
	int ch7 = (v >> 8) & 0xff;
	int ch8 = v & 0xff;

	WriteByte(ch1);
	WriteByte(ch2);
	WriteByte(ch3);
	WriteByte(ch4);
	WriteByte(ch5);
	WriteByte(ch6);
	WriteByte(ch7);
	WriteByte(ch8);
}
