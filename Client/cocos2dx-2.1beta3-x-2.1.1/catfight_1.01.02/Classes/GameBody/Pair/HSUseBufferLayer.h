/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/19   19:06
 *	File base:	HSUseBufferLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSUseBufferLayer_H__
#define __HSUseBufferLayer_H__
#pragma once
#include "HSTool.h"
class HSUseBufferLayer:public CCLayer
{
public:
	HSUseBufferLayer(void);
	~HSUseBufferLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSUseBufferLayer);

private:
	void Load();
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
};
#endif // __HSUseBufferLayer_H____



