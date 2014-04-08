/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/10   14:17
 *	File base:	HSThread.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSThread_H__
#define __HSThread_H__
#pragma once
#include "cocos2d.h"
#include <pthread.h>
using namespace cocos2d;

typedef  void* (*Start_thread)(void *);
#define HS_StartThread(__thread__) (Start_thread)(&__thread__)

class HSThread
{
public:
	HSThread();
	~HSThread(void);

public:
	static HSThread* create(Start_thread startThread, void* arg);

	bool init(Start_thread startThread,void* arg);

	bool Start();

	void Stop();

	void Wait();

	void* GetParameter();

private:
	pthread_t m_pid;
	void* m_pArg;
	Start_thread m_startThread;
};

#endif // __HSThread_H____

