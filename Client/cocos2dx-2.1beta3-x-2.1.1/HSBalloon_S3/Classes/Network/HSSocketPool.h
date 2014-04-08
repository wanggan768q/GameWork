/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/10/19   17:50
 *	File base:	HSSocketPool.h
 *	Author:		Ambition
 *	
 *	Purpose:	���ӳ�
*********************************************************************/
#ifndef __HSSocketPool_H__
#define __HSSocketPool_H__
#pragma once
#include "HSSocket.h"
#include <map>
using namespace std;

class HSSocket;

typedef enum
{
	S_D_Login = 0x1efc,
	S_D_Logic,
	S_L_Battle,
}HSSeverID;

class HSSocketPool : public CCObject 
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

	float m_fPingTimeD;
	float m_fPingTimeL;
	const static float s_pingMaxD;
	const static float s_pingMaxL;

public:
	static HSSocketPool* ShareSocketPool();

	void Destroy();

	void AddSocket(HSSeverID tag,const char* ip,const char* port,HSSocketType type);

	HSSocket* GetSocketWithTag(int hsSeverID);
    
    bool Remove(HSSeverID tag);

	void Updata(float dt);

	void SetPingShortLink(bool b);

	void SetPingLongLink(bool b);

	void PingShortLink(float dt);

	void PingLongLink(float dt);

	inline void ClearPingShortCounter(){m_fPingTimeD = 0.f;};

	inline void ClearPingLongCounter(){m_fPingTimeL = 0.f;};

};

#endif // __HSSocketPool_H____
