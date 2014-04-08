/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/09/20   10:35
 *	File base:	HSTime.h
 *	Author:		Ambition
 *	
 *	Purpose:	时间戳(精确到毫秒)
*********************************************************************/
#ifndef __HSTime_H__
#define __HSTime_H__
#pragma once
#include <time.h>
#include <sys/timeb.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>

#include "cocos2d.h"
using namespace cocos2d;

class HSTime
{
private:
	HSTime(void);
	~HSTime(void);

private:
	static unsigned long long TimeSeed;
	static unsigned long long CT;

private:
	static void SetCurrentTimeStamp();


public:	
	
	static void SetServerTimeSeed(unsigned long long timeSeed);
	
	static unsigned long long GetImitateTimeSeed();
	
	static unsigned long long GetLocalityTime();
	
	static unsigned long long GetLocalityTimeAccurate();

	static int GetYear();

	static int GetMonth();

	static int GetToday();

	static int GetHour();

	static int GetMinute();

	static int GetSec();

	static const char* GetTime();

	static struct tm* GetTM();

	
};
#endif // __HSTime_H__



