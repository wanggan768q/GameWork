#include "HSReadData.h"


HSReadData::HSReadData(const char* zrFileName,HSReadDataMode mode/* = ReadDataMode_CToC*/)
{
	this->m_pFileData = NULL;
	this->index = 0;
	this->m_readMode = mode;
	this->Open(zrFileName);
}

HSReadData::~HSReadData(void)
{
	CC_SAFE_DELETE(this->m_pFileData);
}

void HSReadData::Open(const char* zrFileName)
{
	if (this->m_pFileData)
	{
		CC_SAFE_DELETE(this->m_pFileData);
	}
	this->index = 0;
	this->m_pFileData = new HSFileData(zrFileName,"rb");
}

int  HSReadData::ToUnit(int value)
{
	return value >> 12;
}

char  HSReadData::ReadByte()
{
	int b1 = Fgetc();
	b1 &= 0xff;
	if (b1 == -1)
	{
		HSMessageBox("HSReadData @ ReadByte  throw -1 ");
		return -1;
	}
	int value = b1 & 0xff;
	//CCLog("ReadByte : %d",b1);
	return (char) value;
}

int  HSReadData::ReadUByte()
{
	int b1 = Fgetc();
	b1 &= 0xff;
	if (b1 == -1)
	{
		HSMessageBox("HSReadData @ ReadUByte  throw -1 ");
		return -1;
	}
	//CCLog("ReadUByte : %d",b1);
	return b1;
}

short  HSReadData::ReadShort()
{
	int b1 = Fgetc();
	int b2 = Fgetc();
	b1 &= 0xff;
	b2 &= 0xff;
	if (b1 == -1 || b2 == -1)
	{
		HSMessageBox("HSReadData @ ReadShort  throw -1 ");
		return -1;
	}
	int value = (b1 << 8) | (b2 << 0);
	//CCLog("ReadShort : %d",value);
	return (short) value;
}

int HSReadData::ReadUShort()
{
	int b1 = Fgetc();
	int b2 = Fgetc();
	b1 &= 0xff;
	b2 &= 0xff;
	if (b1 == -1 || b2 == -1)
	{
		HSMessageBox("HSReadData @ ReadUShort  throw -1 ");
		return -1;
	}
	int value = (b1 << 8) | (b2 << 0);
	//CCLog("ReadUShort : %d",value);
	return value;
}

int  HSReadData::ReadInt()
{
	int b1 = Fgetc();
	int b2 = Fgetc();
	int b3 = Fgetc();
	int b4 = Fgetc();
	b1 &= 0xff;
	b2 &= 0xff;
	b3 &= 0xff;
	b4 &= 0xff;
	if (b1 == -1 || b2 == -1 || b3 == -1 || b4 == -1)
	{
		HSMessageBox("HSReadData @ ReadInt  throw -1 ");
		return -1;
	}
	int value = (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4 << 0);
	//CCLog("ReadInt : %d",value);
	return value;
}

float HSReadData::ReadFloat()
{
	int i = ReadInt();
	float f = (float)i / 100.f;
	return f;
}

int HSReadData::Fgetc()
{
	if (this->index >= this->m_pFileData->GetSize())
	{
		return -1;
	}

	int v = (this->m_pFileData->GetBuffer())[this->index];
	this->index++;
	return v;
}

int* HSReadData::ReadIntArrayWithLengthShort()
{
	short length = this->ReadShort();
	int* array = new int[length];
	for (int i = 0; i < length; ++i)
	{
		array[i] = this->ReadInt();
	}
	return array;
}

int* HSReadData::ReadIntArrayWithLengthInt()
{
	int length = this->ReadInt();
	int* array = new int[length];
	for (int i = 0; i < length; ++i)
	{
		array[i] = this->ReadInt();
	}
	return array;
}

short* HSReadData::ReadShortArrayWithLengthShort()
{
	short length = this->ReadShort();
	short* array = new short[length];
	for (int i = 0; i < length; ++i)
	{
		array[i] = this->ReadShort();
	}
	return array;
}

short* HSReadData::ReadShortArrayWithLengthInt()
{
	int length = this->ReadInt();
	short* array = new short[length];
	for (int i = 0; i < length; ++i)
	{
		array[i] = this->ReadShort();
	}
	return array;
}

string HSReadData::ReadUTF8()
{
	if (m_readMode == HS_ReadDataMode_JaveToC)
	{
		//return ReadJavaUTF8();
	}


	int utflen = ReadShort() & 0xffff;
	wstring str;
	str.resize(utflen);
	vector<char> bytes;
	bytes.resize(utflen);
	for (int i=0;i<utflen;++i)
	{
		bytes[i] = this->ReadUByte();
	}

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
			str[index++] = (wchar_t)ch1;
			break;
		case 12: case 13:
			/* 110x xxxx   10xx xxxx*/
			length += 2;
			if(length > utflen)
			{
				return "Error code -1";
			}

			ch2 = (int)bytes[length - 1];
			if((ch2 & 0xC0) != 0x80)
			{
				return "Error code -1";
			}

			str[index++] = (wchar_t)(((ch1 & 0x1F) << 6) | (ch2 & 0x3F));
			break;
		case 14:
			/* 1110 xxxx  10xx xxxx  10xx xxxx */
			length += 3;
			if(length > utflen)
			{
				return "Error code -1";
			}

			ch2 = (int)bytes[length - 2];
			ch3 = (int)bytes[length - 1];

			if(((ch2 & 0xC0) != 0x80) || ((ch3 & 0xC0) != 0x80))
			{
				return "Error code -1";
			}
			str[index++] = (wchar_t)(((ch1 & 0x0F) << 12) | ((ch2 & 0x3F) << 6) | ((ch3 & 0x3F) << 0));
			break;
		default:
			/* 10xx xxxx,  1111 xxxx */
			return "Error code -1";
		}
	}
	string text = HSBase::GetStringWithWstring(str);
	
	return text;
}

string* HSReadData::ReadStringArrayWithLengthShort()
{
	int length = this->ReadShort();
	string* array = new string[length];
	for (int i = 0; i < length; ++i)
	{
		array[i] = this->ReadUTF8();
	}
	return array;
}

string* HSReadData::ReadStringArrayWithLengthInt()
{
	short length = this->ReadInt();
	string* array = new string[length];
	for (int i = 0; i < length; ++i)
	{
		array[i] = this->ReadUTF8();
	}
	return array;
}

long long HSReadData::ReadInt64()
{
	long long ch1 = Fgetc() & 0xff;
	long long ch2 = Fgetc() & 0xff;
	long long ch3 = Fgetc() & 0xff;
	long long ch4 = Fgetc() & 0xff;
	long long ch5 = Fgetc() & 0xff;
	long long ch6 = Fgetc() & 0xff;
	long long ch7 = Fgetc() & 0xff;
	long long ch8 = Fgetc() & 0xff;

	long long v = (ch1 << 56) | (ch2 << 48) | (ch3 << 48) | (ch4 << 32) | (ch5 << 24) | (ch6 << 16) | (ch7 << 8) | (ch8 << 0);
	return v;
}

unsigned long long HSReadData::ReadUInt64()
{
	long long ch1 = Fgetc() & 0xff;
	long long ch2 = Fgetc() & 0xff;
	long long ch3 = Fgetc() & 0xff;
	long long ch4 = Fgetc() & 0xff;
	long long ch5 = Fgetc() & 0xff;
	long long ch6 = Fgetc() & 0xff;
	long long ch7 = Fgetc() & 0xff;
	long long ch8 = Fgetc() & 0xff;

	unsigned long long v = (ch1 << 56) | (ch2 << 48) | (ch3 << 48) | (ch4 << 32) | (ch5 << 24) | (ch6 << 16) | (ch7 << 8) | (ch8 << 0);
	return v;
}

void HSReadData::Read( void* pOutData,int readSize )
{
	HSAssert(pOutData,"");
	
	memcpy(pOutData,this->m_pFileData->GetBuffer() + this->index - 1,readSize);
}

std::string HSReadData::ReadJavaUTF8()
{
	int lenth = ReadInt();
	std::string str = "";
	for (int i=0;i<lenth;++i)
	{
		str.append(1,ReadByte());
	}
	return str;
}
