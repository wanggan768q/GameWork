/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/09/21   16:19
 *	File base:	HSReadData.h
 *	Author:		Ambition
 *	
 *	Purpose:	读取zr数据包
*********************************************************************/
#ifndef __HSReadData_H__
#define __HSReadData_H__
#pragma once
#include "HSBase.h"

/**
*	1.修改内存泄漏问题														[6/27/2013 Ambition]
*/

typedef enum 
{
	HS_ReadDataMode_JaveToC = 0x09,
	HS_ReadDataMode_CToC,
}HSReadDataMode;

class HSReadData
{
public:
	HSReadData(const char* zrFileName,HSReadDataMode mode/* = ReadDataMode_CToC*/);
	~HSReadData(void);

private:
	HSFileData* m_pFileData;
	unsigned long index;
	HSReadDataMode m_readMode;

public:
	int ToUnit(int value);

	char ReadByte();

	int ReadUByte();

	short ReadShort();

	int ReadUShort();

	int ReadInt();

	float ReadFloat();

	long long ReadInt64();

	unsigned long long ReadUInt64();

	int* ReadIntArrayWithLengthShort();

	int* ReadIntArrayWithLengthInt();

	short* ReadShortArrayWithLengthShort();

	short* ReadShortArrayWithLengthInt();

	string* ReadStringArrayWithLengthShort();

	string* ReadStringArrayWithLengthInt();

	string ReadUTF8();

	void Read(void* pOutData,int readSize);
private:
	void Open(const char* zrFileName);

	int Fgetc();

	string ReadJavaUTF8();

};

#endif // __HSReadData_H__
