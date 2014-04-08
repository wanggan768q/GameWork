/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/09/20   13:28
 *	File base:	HSGameMainScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	Game Main
*********************************************************************/
#ifndef __HSGameMainScene_H__
#define __HSGameMainScene_H__
#pragma once
#include "HSTool.h"

class HSGameMainLayer:public CCLayer
{
public:
	HSGameMainLayer(void);
	~HSGameMainLayer(void);

private:
	CCSprite* townBackground;
public:
	virtual bool init(); 
	CREATE_FUNC(HSGameMainLayer);
private:
	void Load();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	void CallBuyPropScene(CCObject* obj);

	void CallMusicMenu(CCObject* obj);

	void CallSoundEffectMenu(CCObject* obj);

	void CallAboutMenu(CCObject* obj);

	void CallRankingMenu(CCObject* obj);

	void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
	
};



class HSGameMainScene:public CCScene
{
public:
	HSGameMainScene(void);
	~HSGameMainScene(void);

public:
	HSGameMainLayer* hsGameMainLayer;

public:
	virtual bool init();
	CREATE_FUNC(HSGameMainScene);
	
	HSGameMainLayer* GetHSGameMainLayer();
};

#endif // __HSGameMainScene_H__