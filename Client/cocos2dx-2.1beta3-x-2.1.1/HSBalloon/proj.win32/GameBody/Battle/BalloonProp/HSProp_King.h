/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/30   16:01
 *	File base:	HSProp_King.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_King_H__
#define __HSProp_King_H__
#pragma once
#include "HSPropSpriteInterface.h"

class HSProp_King : public HSPropSpriteInterface
{
public:
	HSProp_King(void);
	~HSProp_King(void);

private:
	CCSprite* m_pKingEffect_L;
	CCSprite* m_pKingEffect_R;
	CCLabelAtlas* m_pKingTouchLabel;
	int m_iKingTouchIndex;
	float m_fSustainTime;

public:
	HS_CREATE_PROP_FUNC(HSProp_King);

	virtual bool Init( b2World* world );

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent );

	virtual void AddNodeToParent();

	void CallKingEffectFinish();

	virtual void Updata( float dt );

};

#endif // __HSProp_King_H____


