/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/23   13:41
 *	File base:	HSChannelManager.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSChannelManager_H__
#define __HSChannelManager_H__
#pragma once
#include "HSBase.h"
#include "HSMath.h"
#include "HSJni.h"
#include "HSChannel.pb.h"
using namespace message;

typedef enum
{
	HS_CHANNEL_TYPE_Unknow,
	HS_CHANNEL_TYPE_Tom = 10002,
}HSChannelType;

class HSChannelManager
{
public:
	HSChannelManager(void);
	~HSChannelManager(void);

private:
	const static HSChannelType MIN_CHANNEL_TYPE = HS_CHANNEL_TYPE_Tom;
	const static HSChannelType MAX_CHANNEL_TYPE = HS_CHANNEL_TYPE_Tom;

	HSChannelType m_currentChannel;
public:

	static HSChannelManager* ShaderChannelManager();

	bool CheckChannelType(const char* typeID);

	void Buy( Channel* pMsg );


};

#endif // __HSChannelManager_H____


