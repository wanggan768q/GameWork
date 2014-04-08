/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/21   11:28
 *	File base:	HSEffectItemSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSEffectItemSprite_H__
#define __HSEffectItemSprite_H__
#pragma once
#include "HSTool.h"
#endif // __HSEffectItemSprite_H____
class HSEffectItemSprite : public HSGraySprite,public CCTargetedTouchDelegate
{
public:
	HSEffectItemSprite();  
	~HSEffectItemSprite();
public:
	PropInfo m_propInfo;
	CCSprite* m_pLockSprite;
	bool lock;
 
public:
	static HSEffectItemSprite* create(const message::PropInfo propInfo ,int index);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();
	bool Init(const message::PropInfo propInfo,int index);

};