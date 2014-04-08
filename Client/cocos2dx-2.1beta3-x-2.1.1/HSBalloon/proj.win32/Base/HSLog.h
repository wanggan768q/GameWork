/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/10   20:30
 *	File base:	HSLog.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSLog_H__
#define __HSLog_H__
#pragma once
#include "cocos2d.h"
#include "GameLog.pb.h"

using namespace cocos2d;
using namespace message;

#define HS_LOG_FILE_NAME "Log.data"

#define HS_LOG() HSLog::ShareLog()
#define HS_LOG_DATA() HS_LOG()->GetLogData()
#define HS_MUTAABLE_LOG_DATA() HS_LOG()->GetMutableLogData()


class HSLog
{
public:
	HSLog(void);
	~HSLog(void);

private:
	LogRequest* m_pLog;
	LogRequest_UserLog* m_pLastUserLog;
	LogRequest::GoodsLog* m_plastGoodLog;
	int m_iChannel;

private:

	void SendActivateLog();

	void SendRegisterLog();

	void SendLoginLog();

	void SendLogoutLog();

	void SendLogoff();

	void SendLog();

public:
	static HSLog* ShareLog();

	const LogRequest* GetLogData();

	LogRequest* GetMutableLogData();

	void Destroy();

	bool Save();

	bool Read();

	void ResponseLog(LogResponse* pMsg);

	void SendDeviceInfo();

	void SendUserLog(LogRequest_ActionType sendType);

	void SendBuyGoodLog(LogRequest_BuyType sendType,int goodId,int goodNumber,LogRequest_BuyState buystate);

	LogRequest_UserLog* GetLastUserLog();

	void SendChannelID(int id);


};

#endif // __HSLog_H____

