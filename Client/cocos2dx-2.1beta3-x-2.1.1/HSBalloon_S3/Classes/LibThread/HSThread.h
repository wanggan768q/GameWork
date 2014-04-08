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
#include "HSBase.h"

#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#include <io.h>
#include <shlwapi.h>
#include <process.h>
#pragma comment(lib, "shlwapi")
#pragma warning(disable:4996)
#else
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <semaphore.h>
#endif


#ifdef WIN32
static unsigned int WINAPI  ThreadProc(LPVOID lpParam);
#else
static void * ThreadProc(void * pParam);
#endif

class HSThread
{
public:
	HSThread();
	virtual ~HSThread();
    
public:
	bool Start();
	bool Wait();
    
	virtual void Run() = 0;
    
	inline unsigned long long GetThreadID() {return m_hThreadID;};
    
private:
	unsigned long long m_hThreadID;
};


#endif // __HSThread_H____

