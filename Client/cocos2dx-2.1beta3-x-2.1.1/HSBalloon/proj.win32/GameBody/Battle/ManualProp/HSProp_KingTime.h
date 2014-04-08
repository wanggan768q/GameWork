/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/02   14:16
 *	File base:	HSProp_KingTime.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_KingTime_H__
#define __HSProp_KingTime_H__
#pragma once
#include "HSUsePropInterface.h"
#include "HSBalloonConfig.h"

class HSProp_KingTime : public HSUsePropInterface
{
public:
	HSProp_KingTime(void);
	~HSProp_KingTime(void);

private:
	CCSprite* m_pKingEffect_L;
	CCSprite* m_pKingEffect_R;

	float m_fSustainTime;

	SPX_Sprite* m_spx;

public:
	HS_CREATE_USE_PROP_FUNC(HSProp_KingTime);

	void Load();

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	void CallKingEffectFinish();

	virtual void AddNodeToParent();

	void CallSpxFinish(CCNode* spxNode,void* pData);

};
#endif // __HSProp_KingTime_H____


