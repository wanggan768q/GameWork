/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/21   16:43
 *	File base:	HSEffect_BlackInk.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSEffect_BlackInk_H__
#define __HSEffect_BlackInk_H__
#pragma once
#include "HSTool.h"
#endif // __HSEffect_BlackInk_H____
class HSEffect_BlackInkLayer:public CCLayer
{
public:
	HSEffect_BlackInkLayer(void);
	~HSEffect_BlackInkLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSEffect_BlackInkLayer);
private:
	void Load();
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
private:
	void Remove(CCNode* spxNode,void* pData);
public:
	SPX_Sprite* m_spx;
};