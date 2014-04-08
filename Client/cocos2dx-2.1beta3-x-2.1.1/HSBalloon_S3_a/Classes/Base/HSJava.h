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
	/* java 调用c++                                                                     */
	/************************************************************************/
	void CallFinishInit(const char*);
	void CallFinishPay(const char*);
	void Callback(const char*);

	/************************************************************************/
	/* c++ 调用java                                                                     */
	/************************************************************************/

	void Init(const char* json);
	void Pay(const char* json);
	void JavaExec(const char* json);
	void KillProcess();

	void ShowToast(const char* text,int dt);
	
};

#endif // __HSJava_H____


