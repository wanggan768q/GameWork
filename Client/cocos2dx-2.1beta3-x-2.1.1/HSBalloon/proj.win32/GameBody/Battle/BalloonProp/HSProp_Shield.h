/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/31   13:38
 *	File base:	HSProp_Shield.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_Shield_H__
#define __HSProp_Shield_H__
#pragma once
#include "HSPropSpriteInterface.h"
#include "HSBalloonFactory.h"

class HSProp_Shield : public HSPropSpriteInterface
{
public:
	HSProp_Shield(void);
	~HSProp_Shield(void);
public:
	HS_CREATE_PROP_FUNC(HSProp_Shield);

	virtual bool Init( b2World* world );

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent );

	virtual void AddNodeToParent();

	void AddShieldToBalloon();

};
#endif // __HSProp_Shield_H____


