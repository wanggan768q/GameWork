/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/24   16:13
 *	File base:	HSLoadingLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSLoadingLayer_H__
#define __HSLoadingLayer_H__
#pragma once
#include "HSTool.h"

//Layer
class HSLoadingLayer:public CCLayer
{
public:
	HSLoadingLayer(void);
	~HSLoadingLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSLoadingLayer);

	static HSLoadingLayer* ShareLoading();

private:
	void Load();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
	virtual void setVisible(bool visible);

private:
	CCProgressTimer* m_pProgressTimeer;
	CCLabelTTF* m_pTipsTTF;
};

#endif // __HSLoadingLayer_H____