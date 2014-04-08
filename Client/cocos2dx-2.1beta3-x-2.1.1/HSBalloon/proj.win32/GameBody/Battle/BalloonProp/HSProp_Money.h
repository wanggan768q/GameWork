/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/29   17:23
 *	File base:	HSProp_Money.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_Money_H__
#define __HSProp_Money_H__
#pragma once
#include "HSPropSpriteInterface.h"

class HSProp_Money : public HSPropSpriteInterface
{
public:
	HSProp_Money(void);
	~HSProp_Money(void);

private:
	SPX_Sprite* m_spxMoney;

public:
	HS_CREATE_PROP_FUNC(HSProp_Money);

	virtual bool Init(b2World* world);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual void AddNodeToParent();

	void CallMoneyFinish(CCNode* spxNode,void* pData);
};

#endif // __HSProp_Money_H____

