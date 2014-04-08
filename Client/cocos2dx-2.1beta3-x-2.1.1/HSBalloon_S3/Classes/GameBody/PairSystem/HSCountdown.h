/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-20
 *	File base:	HSCountdown.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSCountdown_H__
#define __HSCountdown_H__
#pragma once
#include "HSThread.h"

class HSCountdown : public HSThread
{
public:
	HSCountdown(void);
	~HSCountdown(void);
public:
    static HSCountdown* create();
    
	virtual bool init();
    
    virtual void Run();
};




#endif /* defined(__HSCountdown_H__) */





