/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/02   11:17
 *	File base:	HSUsePropManager.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSUsePropManager_H__
#define __HSUsePropManager_H__
#pragma once
#include "HSPropBalloonList.h"

class HSUsePropManager : public CCNode
{
public:
	HSUsePropManager(void);
	~HSUsePropManager(void);

public:

	static HSUsePropManager* create();

	bool Init();
};

#endif // __HSUsePropManager_H____


