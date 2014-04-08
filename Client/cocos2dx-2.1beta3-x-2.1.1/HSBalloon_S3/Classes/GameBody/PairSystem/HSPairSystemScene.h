/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-4
 *	File base:	HSPairSystem.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSPairSystemScene_H__
#define __HSPairSystemScene_H__
#pragma once
#include "HSTool.h"
#include "HSShowGlobal.h"
#include "HSShowEndurance.h"
#include "HSReadyProp.h"

//Layer
class HSPairSystemLayer : public CCLayer
{
public:
	HSPairSystemLayer(void);
	~HSPairSystemLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSPairSystemLayer);
    
private:
	void Load();
    
    void ShowSlefInfo();
    void ShowTargetInfo();
    
    void SetIsAllowReady(bool b);
    
public:
    void Call_Ready(CCObject* obj);
    void Call_BuyGold(CCObject* obj);
    void Call_BuyEndurance(CCObject* obj);
    void Call_Cancel(CCObject* obj);
    
    void Call_SendFightingRequest();
    
public:
    //进入战斗服务器
    void ResponseFighting(FightingResponse* pMsg);    
    //服务器通知 目标准备
    void ResponseBattleReady(BattleReadyResponse* pMsg);
    //服务器通知 开始战斗
    void ResponseStartBattle(NotifyStartBattle* pMsg);
    //自动主动离开 或者 被动离开
    void ResponsePlayerDisengage(PlayerDisengageResponse* pMsg);
    //配对成功
	void ResponseTargetInfo(TargetInfoResponse* pMsg);
    
    
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
    
public:
    static int S_CURRENT_ROOM_ID;
    static bool S_IS_CREATE_BATTLE_SERVER;
private:
    HSShowEndurance* m_pShowEndurance;
    HSCCSprite* m_pSelfReady,   *m_pTargetReady;
    CCNode* m_pTargetPanel;
    CCNode* m_pTargetPanelLoding;
    
    //目标属性
    HSCCSprite* m_pTIcon;
    HSCCSprite* m_pTFigure;
    CCLabelTTF* m_pTName;
    CCLabelTTF* m_pTSuccessionwincount;
    CCLabelTTF* m_pTWinAndLose;
    
};




//Scene
class HSPairSystemScene : public CCScene
{
public:
	HSPairSystemScene(void);
	~HSPairSystemScene(void);
private:
	HSPairSystemLayer* m_pHSPairSystemLayer;
    
public:
	virtual bool init();
	CREATE_FUNC(HSPairSystemScene);
    
	inline HSPairSystemLayer* GetHSPairSystemLayer(){return this->m_pHSPairSystemLayer;};
    
};






#endif /* defined(__HSPairSystemScene_H__) */





