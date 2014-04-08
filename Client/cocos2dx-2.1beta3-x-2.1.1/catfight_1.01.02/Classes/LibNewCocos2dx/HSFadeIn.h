/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/08/13   14:37
 *	File base:	HSFadeIn.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSFadeIn_H__
#define __HSFadeIn_H__
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class HSFadeIn : public CCFadeIn
{
public:
	HSFadeIn(void);
	~HSFadeIn(void);

public:
	 static HSFadeIn* create(float d);

	 virtual void update(float time);

	 void update(float time,CCObject* pTarget);
};

#endif // __HSFadeIn_H____

