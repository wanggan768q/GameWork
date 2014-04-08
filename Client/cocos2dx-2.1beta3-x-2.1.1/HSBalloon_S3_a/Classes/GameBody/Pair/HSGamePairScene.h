/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/13   15:06
 *	File base:	HSGamePairScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGamePairScene_H__
#define __HSGamePairScene_H__
#pragma once
#include "HSTool.h"
#include "HSGameAdvancedPairLayer.h"
#include "HSGameSelectPropLayer.h"
#include "HSUseBufferLayer.h"
#include "HSBattleOverLayer.h"
#include "HSGameDialogLayer.h"

class HSGamePairLayer:public CCLayer
{
public:
	HSGamePairLayer(void);
	~HSGamePairLayer(void);
private:
	CCLabelAtlas* m_pGameReadTime;
	int m_readyTime;
	CCLabelAtlas* m_pGameGold;
	int m_curMoney;
	int m_count;
	CCLabelTTF* m_pSelfWinCountTTF;
	CCLabelTTF* m_pTargetWinCountTTF;
	CCLabelTTF* m_pSelfLevelTTF;
	CCLabelTTF* m_pBufferInfoTTF;

	CCLabelTTF* m_pInfo1Self;
	CCLabelTTF* m_pInfo2Self;
	CCLabelTTF* m_pInfo3Self ;
	CCLabelTTF* m_pInfo1Enemy;
	CCLabelTTF* m_pInfo2Enemy;
	CCLabelTTF* m_pInfo3Enemy;

	//@ui
public:
	CCSprite* m_pSelfMark;
	CCSprite* m_pTargetMark;
	HSGameDialogLayer* m_pDialog;
	static int s_CURRENT_ROOM_ID;
public:
	//@logic
	bool m_ready;
public:
	virtual bool init(); 
	CREATE_FUNC(HSGamePairLayer);
private:
	void Load();
	void Move();
	void MoveFinish();
	void VSShade();

	void ShowPairInfo();
	void ShowAgainInfo();
	void ShowHead();
	
	void CountReadyTime(float t);
	void CallReturn(CCObject* obj);
	void CallAddFriend(CCObject* pobj);
	void Return();
	void ShowSelectPropLayer(CCObject* obj);
	void HideSelectPropLayer();

	void Call_ListerTarget();
	void Call_Shop(CCObject* obj);

	//@update
	void UpdateMask(std::string uid,PropInfo_EffectPropType type);
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
	void Update(float dt);

	
	//@logic
public:
	void Call_StartGame(CCObject*);
	void Shake();

	//@update
public:
	void UpdateEffect();
	//@network
public:
	void RequestBattleReady();
	void ResponseBattleReady(BattleReadyResponse*);
	void ResponseStartBattle(NotifyStartBattle*);
	void RequestPlayerDisengage();
	void ResponsePlayerDisengage(PlayerDisengageResponse*);
	void ResponseTargetInfo(TargetInfoResponse*r);
};
typedef enum 
{
	area_normal =1,
	area_advanced
} HSAreaType;
typedef enum 
{
	status_pair = 1,
	status_again
} HSStatus;
//Scene
class HSGamePairScene:public CCScene
{
public:
	HSGamePairScene(void);
	~HSGamePairScene(void);
private:
	HSGamePairLayer* hsGamePairLayer;
	HSGameAdvancedPairLayer* hsGameAdvancedPairLayer;
	HSGameSelectPropLayer* hsGameSelectPropLayer;
	HSUseBufferLayer* hsUseBufferLayer;
	HSBattleOverLayer* hsBattleOverLayer;
public:
	static HSAreaType s_areaType;
	static HSStatus s_status;
public:
	virtual bool init();
	CREATE_FUNC(HSGamePairScene);
	inline HSGamePairLayer* GetHSGamePairLayer(){return this->hsGamePairLayer;};
	inline HSGameAdvancedPairLayer* GetHSGameAdvancePairLayer(){return this->hsGameAdvancedPairLayer;};
	inline HSGameSelectPropLayer* GetHSGameSelectPropLayer(){return this->hsGameSelectPropLayer;};
	inline void SetHSGameSelectPropLayer(HSGameSelectPropLayer* hsGameSelectPropLayer)
	{
		this->hsGameSelectPropLayer = hsGameSelectPropLayer;
		this->addChild(hsGameSelectPropLayer,HS_BASE_TAG + 1,HS_BASE_TAG + 1);
	};
	inline HSUseBufferLayer* GetHSUseBufferLayer(){return this->hsUseBufferLayer;};
	inline void SetHSUseBufferLayer(HSUseBufferLayer* hsUseBufferLayer)
	{
		this->hsUseBufferLayer = hsUseBufferLayer;
		this->addChild(hsUseBufferLayer,HS_BASE_TAG,HS_BASE_TAG);
	}
	inline HSBattleOverLayer* GetHSBattleOverLayer(){return this->hsBattleOverLayer;};
	inline void SetHSBattleOverLayer(HSBattleOverLayer* hsBattleOverLayer)
	{
		this->hsBattleOverLayer = hsBattleOverLayer;
		this->addChild(hsBattleOverLayer,HS_BASE_TAG,HS_BASE_TAG);
	}

};

#endif // __HSGamePairScene_H____

