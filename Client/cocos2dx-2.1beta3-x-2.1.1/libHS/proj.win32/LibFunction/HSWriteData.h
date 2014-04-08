/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/30   18:47
 *	File base:	HSWriteData.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSWriteData_H__
#define __HSWriteData_H__
#pragma once
#include "HSBase.h"
#include "HSFileData.h"


class HSWriteData
{
public:
	HSWriteData(const char* zrFileName);
	~HSWriteData(void);

private:
	FILE* m_pFile;

public:

	bool Open(const char* zrFileName);

	int WriteByte(char v);

	void WriteUByte(unsigned char v);

	void WriteShort(short v);

	void WriteUShort(unsigned short v);

	void WriteInt(int v);

	void WriteUint(unsigned int v);

	void WriteFloat(float v);

	void WriteInt64(long long v);

	void WriteUInt64(unsigned long long v);

	bool WriteIntArrayWithLengthInt(int* buf,int size);

	bool WriteStringArrayWithLengthInt(std::string* buf,int size);

	bool WriteUTF8(const char* s);

	int Write(const void* pBuf,int size);

};
#endif // __HSWriteData_H____



