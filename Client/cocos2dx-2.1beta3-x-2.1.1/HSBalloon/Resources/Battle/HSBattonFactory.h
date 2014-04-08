/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/03/25   11:12
 *	File base:	HSBattonFactory.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBattonFactory_H__
#define __HSBattonFactory_H__
#pragma once
#include "HSBallonSprite.h"

class HSBattonFactory : public b2QueryCallback
{
public:
	HSBattonFactory(void);
	~HSBattonFactory(void);

	virtual bool ReportFixture(b2Fixture* fixture); 
};

#endif // __HSBattonFactory_H____

