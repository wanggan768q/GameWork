/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/12/06   11:07
 *	File base:	HSBase.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBase_H__
#define __HSBase_H__
#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include <locale.h>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <set>
#include "HSMacros.h"
#include "HSFileData.h"
#include "HSGraySprite.h"
#include "HSModalDialogInterface.h"
#include "HSListViewInterface.h"
#include "HSCCSprite.h"
#include "HSTexture2D.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
HS_namespace_Using_HSListViewControl;

#ifdef WIN32
#include <Windows.h>
#include "iconv.h"
#pragma comment(lib,"libiconv.lib")
#endif

#ifdef WIN32
#if _DEBUG
#pragma comment(lib,"libs/Debug/2012/libprotobuf.lib")
#else
#pragma comment(lib,"libs/Release/2012/libprotobuf.lib")
#endif
#endif

#define HS_MAX_IMAGE_W HSBase::GetMaxImageW()
#define HS_MAX_IMAGE_H HSBase::GetMaxImageH()

#define HS_MAX_LEN (16*1024+1)

#define HSMessageBox(__strMsg__, ... ) \
{ \
	CCLog("HSMessageBox:-------------------------------------------%s (%d)",__FUNCTION__,__LINE__); \
    CCString* tipInfo = CCString::createWithFormat(__strMsg__,##__VA_ARGS__); \
	CCLog("HSMessageBox: error: - %s - %s (%d)",tipInfo->getCString(),__FUNCTION__,__LINE__); \
	CCLog("HSMessageBox:-------------------------------------------%s (%d)",__FUNCTION__,__LINE__); \
	HSBase::HSMessageBox_(string(tipInfo->getCString())); \
    CC_SAFE_RELEASE_NULL(tipInfo); \
}

#define HSLocalPoint(pTouch,pNode) HSBase::GetLocationPoint(pTouch,pNode)

#define HS_SCREEN_WIDTH HSBase::GetScreenWidth()
#define HS_SCREEN_HEIGHT HSBase::GetScreenHeight()

#if WIN32
#define HS_GBK_TO_UTF8(str) HSBase::GBKToUTF8(std::string(str),"GBK","UTF-8")
#define HS_UTF8_TO_GBK(str) HSBase::GBKToUTF8(std::string(str),"UTF-8","GBK")
#else
#define HS_GBK_TO_UTF8(str) std::string(str).c_str()
#define HS_UTF8_TO_GBK(str) std::string(str).c_str()
#endif



class HSBase
{
public:
	HSBase(void);
	~HSBase(void);

public:
	static CCSize m_MaxImageSize;
public:
	//static void HSMessageBox_(string strMsg,const char* strTitle = " HSDebug ");
    static void HSMessageBox_(string strMsg,const char* strTitle = "");

	static CCPoint GetLocationPoint(CCTouch *pTouch,CCNode* node);

	static string GetStringWithWstring(const wstring& ws);

	static wstring GetWstringWithString(const std::string& s);

	static const char* GBKToUTF8(string& gbkStr,const char* toCode="utf-8",const char* fromCode="gbk");

	//µ√µΩutf8◊÷∑˚¥Æµƒ≥§∂»
	static int Strlen_utf8(string str);

	static CCSize GetScreenSize();
	static CCPoint GetScreenOrigin();
	static float GetScreenWidth();
	static float GetScreenHeight();
	static CCPoint GetScreenCentre();
	

	static void GetAllLineInfo(unsigned char* buf,unsigned long bufSize,vector<string>* out);
	static void GetDictionary_Key_V(vector<string>* pAllLineInfo,map<string,string>* out);
	static void GetDictionary_Key_V__WithFile(const char* fileName,map<string,string>* out);

	static void SetMaxImageSize(CCSize size);
	static float GetMaxImageW();
	static float GetMaxImageH();
	static CCSize GetTemplateScreenSize();
	static CCPoint GetTemplateScreenCentre();
	static float GetTemplateScreenW();
	static float GetTemplateScreenH();

};


#endif // __HSBase_H____
