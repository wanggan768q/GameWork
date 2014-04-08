/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/16   10:25
 *	File base:	HSGameAdvancedPairLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGameAdvancedPairLayer_H__
#define __HSGameAdvancedPairLayer_H__
#pragma once
#include "HSTool.h"
class HSGameAdvancedPairLayer:public CCLayer
{
public:
	HSGameAdvancedPairLayer(void);
	~HSGameAdvancedPairLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSGameAdvancedPairLayer);

private:
	void Load();
	void CallReturn(CCObject* obj);
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
};
#endif // __HSGameAdvancedPairLayer_H____


