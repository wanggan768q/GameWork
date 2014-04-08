/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/25   11:51
 *	File base:	HSDailyRewardSystemLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSDailyRewardSystemLayer_H__
#define __HSDailyRewardSystemLayer_H__
#pragma once
#include "HSTool.h"

//Layer
class HSDailyRewardSystemLayer:public CCLayer
{
public:
	HSDailyRewardSystemLayer(void);
	~HSDailyRewardSystemLayer(void);

private:
	int m_AllowClaimedDayID;
public:
	virtual bool init(); 
	CREATE_FUNC(HSDailyRewardSystemLayer);

private:
	void Load();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	void Call_Claimed(CCObject* pObj);
};

#endif // __HSDailyRewardSystemLayer_H____
