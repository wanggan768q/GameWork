/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/30   14:08
 *	File base:	HSProp_AddStratagemLevel.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_AddStratagemLevel_H__
#define __HSProp_AddStratagemLevel_H__
#pragma once
#include "HSPropSpriteInterface.h"

class HSProp_AddStratagemLevel : public HSPropSpriteInterface
{
public:
	HSProp_AddStratagemLevel(void);
	~HSProp_AddStratagemLevel(void);

private:
	SPX_Sprite* m_spxAddStratagemLevel;

public:
	HS_CREATE_PROP_FUNC(HSProp_AddStratagemLevel);

	virtual bool Init( b2World* world );

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent );

	virtual void AddNodeToParent();

	void CallAddStratagemLevelFinish(CCNode* spxNode,void* pData);

};

#endif // __HSProp_AddStratagemLevel_H____

