/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/30   19:04
 *	File base:	HSProp_ChangeColor.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_ChangeColor_H__
#define __HSProp_ChangeColor_H__
#pragma once
#include "HSPropSpriteInterface.h"

class HSProp_ChangeColor : public HSPropSpriteInterface
{
public:
	HSProp_ChangeColor(void);
	~HSProp_ChangeColor(void);

public:
	b2AABB m_listerArea;

public:
	HS_CREATE_PROP_FUNC(HSProp_ChangeColor);

	virtual bool Init( b2World* world );

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	void ChangerColor();

	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent );

	virtual void AddNodeToParent();


	virtual void SetListerArea();

};
#endif // __HSProp_ChangeColor_H____


