/********************************************************************
  *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/24   15:39
 *	File base:	HSJava.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSJava_H__
#define __HSJava_H__
#pragma once
#include "HSBase.h"
#include "HSJni.h"
class HSJava
{
public:
	HSJava(void);
	~HSJava(void);

public:

	static HSJava* ShaderJava();

	void CallBuy( int propID );

	/************************************************************************/
	/* java ����c++                                                                     */
	/************************************************************************/
	void CallFinishInit(const char*);
	void CallFinishPay(const char*);
	void Callback(const char*);

	/************************************************************************/
	/* c++ ����java                                                                     */
	/************************************************************************/

	void Init(const char* json);
	void Pay(int money);
	CCString*  JavaExec(const char* json);
    
#if HSIos
    CCString* Exec(const char* json);
#endif
    
    
	void KillProcess();
	int  CheckUser();
	void NotifyVersionCode(int newVersionCode);

	int  GetVersion();
	CCString* GetVersionName();

	int  GetChannel();

	void ShowToast(const char* text,int dt);

	void OpenURL(const char* text);



public:
	long long m_lastTime;
};

#endif // __HSJava_H____


