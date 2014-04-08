/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/10/19   17:50
 *	File base:	HSSocketPool.h
 *	Author:		Ambition
 *	
 *	Purpose:	Á´½Ó³Ø
*********************************************************************/
#ifndef __HSSocketPool_H__
#define __HSSocketPool_H__
#pragma once
#include "HSSocket.h"
#include <map>
using namespace std;

class HSSocket;

#define DEFAULT_SOCKET 0x1efc

class HSSocketPool
{
private:
	HSSocketPool(void);
public:
	~HSSocketPool(void);

private:
	typedef struct
	{
		const char* ip;
		const char* port;
		int type;
	}HSSocketInfo;
	map<int,HSSocket*> m_socketList;

public:
	static HSSocketPool* ShareSocketPool();

	void Destroy();

	void AddSocket(int tag,const char* ip,const char* port,int type);

	HSSocket* GetSocketWithTag(int tag);

	void Updata();

};

#endif // __HSSocketPool_H____
