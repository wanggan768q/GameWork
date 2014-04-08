/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/09/25   14:55
 *	File base:	HSFilter.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSFilter_H__
#define __HSFilter_H__
#pragma once
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include "HSDataCache.h"
#include "HSSocketPool.h"
#include "HSAllMessageHead.h"
#include <string>
#include "HSResponse.h"
#include "HSMath.h"
#include "HSBase.h"
#include "HSGameCache.h"
using namespace std;

#ifdef WIN32
	#if _DEBUG
		#pragma comment(lib,"libs/Debug/2012/libprotobuf.lib")
	#else
		#pragma comment(lib,"libs/Release/2012/libprotobuf.lib")
	#endif
#endif
#define BASE 65521L

#define HS_FILTER_LOG 1

class HSFilter
{
public:
	HSFilter(void);
	~HSFilter(void);
private:
	typedef struct _HSFilterData
	{
		_HSFilterData()
		{
			pMsg = NULL;
			commandId = 0;
		}
		~_HSFilterData()
		{
			CC_SAFE_DELETE(pMsg);
			commandId = 0;
		}
		google::protobuf::Message* pMsg;
		int commandId;
	}HSFilterData;

	message::MessageInfo* m_hsMsg;
	map<string,int> m_MessageListMap;
	queue<HSFilterData*> m_FilterDaraQueue;
public:

	static HSFilter* ShareFilter();

	void Destroy();

	bool CreaterMessage(google::protobuf::Message* msg);

	void CreaterMessage(char* data,int lenth);

	::google::protobuf::Message* CreaterMessage(int ID);

	unsigned long long Adler32(unsigned char* buf, int len);

	void SetIsShowLog(bool b);

	inline bool GetIsShowLog(){return HS_FILTER_LOG;}

	bool SendDistribution(int commandID,const std::string& data,const std::string &describe);

	void Distribution();

private:
	void RegisterAllMessage();
	void RegisterMessage(int requestID,int responseID,std::string messageName);	
};


#endif // __HSFilter_H__
