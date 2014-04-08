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
#include "PropInfo.pb.h"
#include "HSWriteData.h"
#include "HSReadData.h"
#include "HSLanguage.h"
#include "HSJni.h"
#include "HSLog.h"

USING_NS_CC_EXT;
using namespace message;


#include "HSGameMacros.h"
#include "HSGameCache.h"

#include "HSLoadingLayer.h"

class HSTool : public HSToolBase
{
private:
	HSTool(void);;
	~HSTool(void);

private:
	std::map<std::string,std::string> m_configurationMap;
public:
	static HSTool* ShareHSTool();

	void Destroy();

	virtual void Release();

	void ReadConfiguration();

	std::string FindConfiguration(const std::string& key);

	const char* GetUUID();

	const char* GetSystemVersions();

	const char* GetNetType();

	const char* GetOperator();

	const char* GetCountryInfo();

	const char* GetCityInfo();
	/************************************************************************/
	/* 购买的公共方法                                                                     */
	/************************************************************************/
	void Buy(int id,int money,const char* title,const char*describ);
};

#endif // __HSTool_H__
