/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/29   18:42
 *	File base:	HSProp_Fog.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_Fog_H__
#define __HSProp_Fog_H__
#pragma once
#include "HSPropSpriteInterface.h"

class HSProp_Fog : public HSPropSpriteInterface
{
public:
	HSProp_Fog(void);
	~HSProp_Fog(void);

private:
	CCSprite* m_pFogSprite;

	const static int M_SWAITTIME = 10;

	float m_fPastTime;
	bool m_isPauseUpdate;
public:
	HS_CREATE_PROP_FUNC(HSProp_Fog);

	virtual bool Init( b2World* world );

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent );

	virtual void AddNodeToParent();

	virtual void Updata( float dt );

};
#endif // __HSProp_Fog_H____


