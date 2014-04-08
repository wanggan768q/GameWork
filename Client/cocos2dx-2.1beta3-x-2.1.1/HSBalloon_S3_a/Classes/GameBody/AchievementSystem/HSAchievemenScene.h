/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/05   17:14
 *	File base:	HSAchievemenScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSAchievemenScene_H__
#define __HSAchievemenScene_H__
#pragma once
#include "HSAchievemenLsitView.h"

//Layer
class HSAchievemenLayer:public CCLayer
{
public:
	HSAchievemenLayer(void);
	~HSAchievemenLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSAchievemenLayer);

private:
	void Load();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	int& GetHaveReceiveNum();

	void Call_Back(CCObject* pObj);
	void Call_Shop(CCObject* pobj);

	void Updata(float dt);

private:
	HSAchievemenListView* m_pAchievemenListView;
	CCLabelAtlas* m_pMoney;
	int m_money;
	int m_HaveReceiveNum;
	CCLabelTTF* m_pFinishNumTTF;
};




//Scene
class HSAchievemenScene:public CCScene
{
public:
	HSAchievemenScene(void);
	~HSAchievemenScene(void);
private:
	HSAchievemenLayer* hsAchievemenLayer;

public:
	virtual bool init();
	CREATE_FUNC(HSAchievemenScene);

	inline HSAchievemenLayer* GetHSAchievemenLayer(){return this->hsAchievemenLayer;};

};
#endif // __HSAchievemenScene_H____
