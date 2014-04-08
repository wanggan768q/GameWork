/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-31
 *	File base:	HSGameGuideSystemScene.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSGameGuideSystemScene_H__
#define __HSGameGuideSystemScene_H__
#pragma once
#include "HSTool.h"

//Layer
class HSGameGuideSystemLayer : public CCLayer
{
public:
	HSGameGuideSystemLayer(void);
	~HSGameGuideSystemLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSGameGuideSystemLayer);
    
private:
	void Load();
    void Updata(float dt);
    void Call_IntervalTime();
    
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
    
    
private:
    vector<CCSprite*> m_guides;
    int m_index;
    int m_isAllowTouch;

};




//Scene
class HSGameGuideSystemScene : public CCScene
{
public:
	HSGameGuideSystemScene(void);
	~HSGameGuideSystemScene(void);
private:
	HSGameGuideSystemLayer* m_pHSGameGuideSystemLayer;
    
public:
	virtual bool init();
	CREATE_FUNC(HSGameGuideSystemScene);
    
	inline HSGameGuideSystemLayer* GetHSGameGuideSystemLayer(){return this->m_pHSGameGuideSystemLayer;};
    
};






#endif /* defined(__HSGameGuideSystemScene_H__) */





