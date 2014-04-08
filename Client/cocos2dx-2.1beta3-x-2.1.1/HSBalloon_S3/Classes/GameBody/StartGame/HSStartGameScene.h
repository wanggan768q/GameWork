/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-7
 *	File base:	HSStartGame.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSStartGameScene_H__
#define __HSStartGameScene_H__
#pragma once
#include "HSTool.h"
#include "HSShowEndurance.h"
#include "HSShowGlobal.h"
#include "HSFriendsListVeiw.h"

//Layer
class HSStartGameLayer : public CCLayer
{
public:
	HSStartGameLayer(void);
	~HSStartGameLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSStartGameLayer);
    
private:
	void Load();
    
    void UpdataPlayerIcon();
    
    void UpdataFriend();
    
    void UpdataEmail();
    
    void Updata(float dt);
    void First(float dt);
    
    void Call_BuyGold(CCObject* obj);
    void Call_BuyEndurance(CCObject* obj);
    void Call_PlayerInfo(CCObject* obj);
    void Call_Setting(CCObject* obj);
    void Call_AddressBook(CCObject* obj);
    void Call_OpenEmail(CCObject* obj);
    void Call_StartGame(CCObject* obj);
    void Call_Achievemen(CCObject* obj);
    
public:    
    void ResponseValidateStrength(ValidateStrengthResponse* pMsg);
    
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
    
public:
    
    static bool S_IS_SHOW_DIALOG;
private:
    HSShowEndurance* m_pShowEndurance;
    HSFriendsListVeiw* m_pFriendsListView;
    CCSprite* m_pPlayerICON;
};




//Scene
class HSStartGameScene : public CCScene
{
public:
	HSStartGameScene(void);
	~HSStartGameScene(void);
private:
	HSStartGameLayer* m_pHSStartGameLayer;
    
public:
	virtual bool init();
	CREATE_FUNC(HSStartGameScene);
    
	inline HSStartGameLayer* GetHSStartGameLayer(){return this->m_pHSStartGameLayer;};
    
};






#endif /* defined(__HSStartGameScene_H__) */





