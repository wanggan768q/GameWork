/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/30   14:56
 *	File base:	HSProp_SubStratagemLevel.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_SubStratagemLevel_H__
#define __HSProp_SubStratagemLevel_H__
#pragma once
#include "HSPropSpriteInterface.h"

class HSProp_SubStratagemLevel : public HSPropSpriteInterface
{
public:
	HSProp_SubStratagemLevel(void);
	~HSProp_SubStratagemLevel(void);

private:
	SPX_Sprite* m_spxSubStratagemLevel;

public:
	HS_CREATE_PROP_FUNC(HSProp_SubStratagemLevel);

	virtual bool Init( b2World* world );

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent );

	virtual void AddNodeToParent();

	void CallSubStratagemLevelFinish(CCNode* spxNode,void* pData);
};
#endif // __HSProp_SubStratagemLevel_H____


