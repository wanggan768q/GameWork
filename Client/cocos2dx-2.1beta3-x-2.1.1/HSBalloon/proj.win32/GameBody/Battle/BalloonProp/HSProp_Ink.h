/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/07   14:34
 *	File base:	HSProp_Ink.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_Ink_H__
#define __HSProp_Ink_H__
#pragma once
#include "hspropspriteinterface.h"

class HSProp_Ink : public HSPropSpriteInterface
{
public:
	HSProp_Ink(void);
	~HSProp_Ink(void);

private:
	SPX_Sprite* m_spxInk;

public:
	HS_CREATE_PROP_FUNC(HSProp_Ink);

	virtual bool Init( b2World* world );

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent );

	virtual void AddNodeToParent();

	void CallInkFinish_1(CCNode* spxNode,void* pData);

	void CallInkFinish_2();

	void CallInkFinish(CCNode* spxNode,void* pData);


};

#endif // __HSProp_Ink_H____


