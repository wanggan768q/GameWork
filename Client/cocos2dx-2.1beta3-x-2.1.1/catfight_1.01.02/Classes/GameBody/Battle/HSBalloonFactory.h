/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/03/25   11:12
 *	File base:	HSBattonFactory.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBattonFactory_H__
#define __HSBattonFactory_H__
#pragma once
#include "HSBalloonSprite.h"

class HSBalloonFactory : public b2QueryCallback
{
public:
	HSBalloonFactory(void);
	~HSBalloonFactory(void);

protected:
	std::set<HSBalloonSprite*> m_balloonSpriteList;
public:

	void Reset();

	std::set<HSBalloonSprite*>* GetSpriteList();

	virtual bool ReportFixture(b2Fixture* fixture);
};

#endif // __HSBattonFactory_H____

