/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-6
 *	File base:	HSReadyProp.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSReadyProp_H__
#define __HSReadyProp_H__
#pragma once
#include "HSTool.h"
#include "HSReadyPropItem.h"

class HSReadyProp : public CCNode
{
public:
	HSReadyProp(void);
	~HSReadyProp(void);
public:
    static HSReadyProp* create();
    
	virtual bool init();
};




#endif /* defined(__HSReadyProp_H__) */





