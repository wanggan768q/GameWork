/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/29   15:43
 *	File base:	HSProp_Bomb.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_Bomb_H__
#define __HSProp_Bomb_H__
#pragma once
#include "hspropspriteinterface.h"
#include "HSBalloonFactory.h"

class HSProp_Bomb : public HSPropSpriteInterface
{
public:
	HSProp_Bomb(void);
	~HSProp_Bomb(void);

private:
	SPX_Sprite* m_spxBomb;

public:
	HS_CREATE_PROP_FUNC(HSProp_Bomb);

	virtual bool Init(b2World* world);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual void AddNodeToParent();

	virtual void Updata(float dt);

	void CallBombFinish(CCNode* spxNode,void* pData);
};

#endif // __HSProp_Bomb_H____

