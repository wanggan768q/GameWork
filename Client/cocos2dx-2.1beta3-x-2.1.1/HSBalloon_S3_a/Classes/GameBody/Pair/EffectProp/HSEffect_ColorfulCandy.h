/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/22   17:37
 *	File base:	HSEffect_ColorfulCandy.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSEffect_ColorfulCandy_H__
#define __HSEffect_ColorfulCandy_H__
#pragma once
#include "HSTool.h"
#endif // __HSEffect_ColorfulCandy_H____
class HSEffect_ColorfulCandyLayer:public CCLayer
{
public:
	HSEffect_ColorfulCandyLayer(void);
	~HSEffect_ColorfulCandyLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSEffect_ColorfulCandyLayer);
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
private:
	static int CandyCount;
};