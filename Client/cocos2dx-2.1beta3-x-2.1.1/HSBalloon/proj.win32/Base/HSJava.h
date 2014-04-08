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

	void CallBuy( const void* pData,int size );

	void CallBuy( int propID );
};

#endif // __HSJava_H____


