/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/22   14:41
 *	File base:	HSEffect_SickMucus.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSEffect_SickMucus_H__
#define __HSEffect_SickMucus_H__
#pragma once
#include "HSTool.h"
#endif // __HSEffect_SickMucus_H____
class HSEffect_SickMucusLayer:public CCLayer
{
public:
	HSEffect_SickMucusLayer(void);
	~HSEffect_SickMucusLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSEffect_SickMucusLayer);
private:
	void Load();
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
	//@logic
public:
	void Close();
	void Shake();
public:
	CCSprite* m_psick7;
};