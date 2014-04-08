/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/10/11   11:03
 *	File base:	HSDataCache.h
 *	Author:		Ambition
 *	
 *	Purpose:	本地数据缓存
*********************************************************************/
#ifndef __HSDataCache_H__
#define __HSDataCache_H__
#pragma once
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include "cocos2d.h"
using namespace cocos2d;

class HSDataCache
{
private:
	HSDataCache(void);
public:
	~HSDataCache(void);

public: 
	static HSDataCache* ShareDataCache();

	void Destroy();
	
	void AddCacheData(int commmandId,google::protobuf::Message* msg);
};
#endif // __HSDataCache_H__

