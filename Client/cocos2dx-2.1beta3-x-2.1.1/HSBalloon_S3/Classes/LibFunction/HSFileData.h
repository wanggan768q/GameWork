/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/01/30   13:35
 *	File base:	HSFileData.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSFileData_H__
#define __HSFileData_H__
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;
#include "HSMacros.h"

#if WIN32
#include <direct.h>
#include <io.h>
#else
#include <stdarg.h>
#include <sys/stat.h>
#endif

#ifdef WIN32
#define HS_ACCESS _access
#define MKDIR( __dir__ ) _mkdir((__dir__))
#else
#define HS_ACCESS(__FileName__,__Mode__) 1
#define MKDIR(__dir__) mkdir((__dir__),S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)
#endif


/**
*	1.存在BUG还没有修改在析构函数									[2/06/2013 Ambition]
*	2.增加了读取模式,在Android下用 READ_MODE_COCOS2DX 模式读取文件  [6/26/2013 Ambition]
*/

typedef enum
{
	READ_MODE_COCOS2DX = 0x01,
	READ_MODE_FOPEN,
}HSReadModeType;

class HSFileData
{
public:
	HSFileData(const char* pszFileName, const char* pszMode,HSReadModeType readMode = READ_MODE_COCOS2DX);
	~HSFileData(void);

private:
	unsigned char* m_pBuffer;
	unsigned long  m_uSize;
	HSReadModeType m_readMode;
	FILE *m_pFile;

public:
	static bool CreateDirectoryWithName(const char* directory);

	bool Reset(const char* pszFileName, const char* pszMode);

	inline unsigned char* GetBuffer(){ return this->m_pBuffer; }

	inline unsigned long GetSize(){ return this->m_uSize; }

	inline HSReadModeType GetReadModeType(){ return this->m_readMode; }

	HSFileData& operator+=(const HSFileData& hsFileData);

	void ReadWithFopen(const char* pszFileName, const char* pszMode);

	void ReadWithCocos2dx(const char* pszFileName, const char* pszMode);

};



#endif // __HSFileData_H____
