/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/03   9:53
 *	File base:	HSLanRoomListScene.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSLanRoomListScene_H__
#define __HSLanRoomListScene_H__
#pragma once
#include "HSTool.h"
#include "HSLanRoomListVeiw.h"

//Layer
class HSLanRoomListLayer : public CCLayer
{
public:
	HSLanRoomListLayer(void);
	~HSLanRoomListLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSLanRoomListLayer);
    
private:
	void Load();
    
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
    
    void Updata(float dt);
    
    void ListerTargetJoinRoom(float dt);
    void ListerCreateRoomSuccessful(float dt);
    void ListerOnce(float dt);
    void ListerTargetUserInfo(float dt);
    
    void ListerIsAllowBack(float dt);
    
    
	void Call_Back(CCObject* pObj);
    void Call_CreateRoom(CCObject* pObj);
    void Call_Refresh(CCObject* pObj);
    void Call_Refresh();
    
    void PlayRefreshEffect();
    void Call_PlayRefreshEffect();
    
    void DisConnectIsSucceed(bool b);
    
    void ResponseLanCreateRoom(LanCreateRoomResponse* pMsg);
    void ResponseLanJoinRoom(LanJoinRoomResponse* pMsg);
    
    void ResponseLanSyncUserInfoNotice(LanSyncUserInfoNotice* pMsg);
    void ResponseLanSearchRoom(LanSearchRoomResponse* pMsg);
    
    
    
private:
	HSLanRoomListVeiw* m_pRoomListView;
    
    CCMenu* pRefreshMenu;
    
    bool m_isCreateRoomSuccessful;
    
    bool m_isListerIsAllowBack;
};




//Scene
class HSLanRoomListScene:public CCScene
{
public:
	HSLanRoomListScene(void);
	~HSLanRoomListScene(void);
private:
	HSLanRoomListLayer* hsRoomListLayer;
    
public:
	virtual bool init();
	CREATE_FUNC(HSLanRoomListScene);
    
	inline HSLanRoomListLayer* GetHSLanRoomListLayer(){return this->hsRoomListLayer;};
    
};
#endif // __HSLanRoomListScene_H____




