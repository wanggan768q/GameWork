/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/09/17   13:54
 *	File base:	HSTool.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSTool_H__
#define __HSTool_H__
#pragma once
#include "HSToolBase.h"
#include "HSSocketPool.h"
#include "HSRequest.h"
#include "cocos-ext.h"
#include "HSWriteData.h"
#include "HSReadData.h"
#include "HSLanguage.h"
#include "HSJni.h"
#include "HSGameMacros.h"
#include "HSGameMacros.h"
#include "HSGameCache.h"
#include "HSLoadingLayer.h"
USING_NS_CC_EXT;
using namespace message;

#include "HSLanRequest.h"


#define HS_ONLINE HSTool::ShareHSTool()->IsOnline()

#ifndef HS_FONT
#define HS_FONT
#if WIN32
#define HS_FONT_HuaKang "����������W12(P)"
#else
//"iphone/Font/HuaKang.ttf"
#define HS_FONT_HuaKang "Arial"
#endif
#endif

#define HS_Find_Configure(__Key__) HSTool::ShareHSTool()->FindConfiguration(__Key__)



class HSTool : public HSToolBase
{
private:
	HSTool(void);;
	~HSTool(void);

private:
	std::map<std::string,std::string> m_configurationMap;
public:
	static HSTool* ShareHSTool();

	void Init();

	void Destroy();

	virtual void Release();

	void ReadConfiguration();

	std::string FindConfiguration(const std::string& key);

	bool IsOnline();

	const char* GetUUID();

	const char* GetSystemVersions();

	const char* GetNetType();

	const char* GetOperator();

	const char* GetCountryInfo();

	const char* GetCityInfo();

	void SendLog(const void* pData,int size);
    
    void AddDefaultSocket();
};

#endif // __HSTool_H__
