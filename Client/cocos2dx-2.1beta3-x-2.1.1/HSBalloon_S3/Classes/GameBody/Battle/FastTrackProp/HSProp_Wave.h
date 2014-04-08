/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-24
 *	File base:	HSProp_Wave.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSProp_Wave_H__
#define __HSProp_Wave_H__
#pragma once
#include "HSPropFastTrackInterface.h"

class HSProp_Wave : public HSPropFastTrackInterface
{
public:
	HSProp_Wave(void);
	~HSProp_Wave(void);
public:
    static HSProp_Wave* create();
    
	virtual bool init();
    
    virtual void Function();
};




#endif /* defined(__HSProp_Wave_H__) */





