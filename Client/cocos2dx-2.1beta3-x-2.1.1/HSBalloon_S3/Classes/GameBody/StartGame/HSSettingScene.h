/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-11
 *	File base:	HSSetting.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSSettingScene_H__
#define __HSSettingScene_H__
#pragma once
#include "HSTool.h"

//Layer
class HSSettingLayer : public CCLayer
{
public:
	HSSettingLayer(void);
	~HSSettingLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSSettingLayer);
    
private:
	void Load();
    void Call_Sound(CCObject* obj);
    void Call_Music(CCObject* pbj);
    void Call_Logout(CCObject* pbj);
    void Call_AboutInfo(CCObject* pbj);
    void Call_Course(CCObject* pbj);
    void Call_MoreGame(CCObject* pbj);
    void Call_Back(CCObject* pbj);
    
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
};




//Scene
class HSSettingScene : public CCScene
{
public:
	HSSettingScene(void);
	~HSSettingScene(void);
private:
	HSSettingLayer* m_pHSSettingLayer;
    
public:
	virtual bool init();
	CREATE_FUNC(HSSettingScene);
    
	inline HSSettingLayer* GetHSSettingLayer(){return this->m_pHSSettingLayer;};
    
};






#endif /* defined(__HSSettingScene_H__) */





