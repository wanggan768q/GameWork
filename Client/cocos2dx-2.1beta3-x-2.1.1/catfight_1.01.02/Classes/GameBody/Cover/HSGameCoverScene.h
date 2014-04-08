/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/09/20   13:28
 *	File base:	HSGameCoverScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	Game Main
*********************************************************************/
#ifndef __HSGameCoverScene_H__
#define __HSGameCoverScene_H__
#pragma once
#include "HSTool.h"
#include "HSGamePlayerInfoLayer.h"
#include "HSGameShopScene.h"
#include "HSGameFrisbee.h"


class HSCoverNormalLayer:public CCLayer
{
public:
	HSCoverNormalLayer(void);
	~HSCoverNormalLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSCoverNormalLayer);
private:
	void Load();
public:
	void Update(float dt);
	void BeginDown();
	void StopDown();
public:
	void CallCloudFinish(CCNode*);
	void CallCatDownShake();
public:
	CCSprite* normal_backGround;

	CCSprite* m_p_main_cloud1;
	CCSprite* m_p_main_cloud1s;
	CCPoint m_cloud1Position;

	CCSprite* m_p_main_cloud2;
	CCSprite* m_p_main_cloud2s;
	CCPoint m_cloud2Postion;


	CCSprite* m_p_main_cloud3;
	CCSprite* m_p_main_cloud3s;
	CCPoint m_cloud3Postion;

	CCSprite* m_p_main_cloud4;
	CCSprite* m_p_main_cloud4s;
	CCPoint m_cloud4Postion;

	CCSprite* m_p_main_cloud5;
	CCSprite* m_p_main_cloud5s;
	CCPoint m_cloud5Postion;

	CCSprite* m_p_main_catblack1;
	CCPoint m_main_catblack1Position;
	CCSprite* m_p_main_catblack2;
	CCPoint m_main_catblack2Position;

	

	//@logic
	float m_catblack1count;
	float m_catblack2count;

	bool  m_down;
public:
	static float m_maxcatblack1;
	static float m_maxcatblack2;

	static float m_downMaxCount;
	static float m_downMinCount;

	static float m_cat1MinX;
	static float m_cat1MaxX;

	static float m_cat2MinX;
	static float m_cat2MaxX;
};


class HSCoverBacknormalLayer:public CCLayer
{
public:
	HSCoverBacknormalLayer(void);
	~HSCoverBacknormalLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSCoverBacknormalLayer);
private:
	void Load();
public:
	CCSprite* m_p_normal_backGround;
	HSCoverNormalLayer* m_p_normal;
	
};

class HSCoverBackSeniorLayer:public CCLayer
{
public:
	HSCoverBackSeniorLayer(void);
	~HSCoverBackSeniorLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSCoverBackSeniorLayer);
private:
	void Load();
public:
	void Update(float dt);
	void BeginDown();
	void StopDown();
	void CallCatDownShake();

public:
	CCSprite* m_p_senior_backGround;
	CCSprite* m_p_senior_foreground;

	CCSprite* m_p_senior_catblack1;
	CCPoint m_senior_catblack1Position;
	CCSprite* m_p_senior_catblack2;
	CCPoint m_senior_catblack2Position;

	//@logic
	float m_senior_catblack1count;
	float m_senior_catblack2count;
	bool  m_down;
public:
	static float m_maxcatblack1;
	static float m_maxcatblack2;

	static float m_downMaxCount;
	static float m_downMinCount;

	static float m_cat1MinX;
	static float m_cat1MaxX;

	static float m_cat2MinX;
	static float m_cat2MaxX;
};

class HSGameCoverLayer:public CCLayer
{
public:
	HSGameCoverLayer(void);
	~HSGameCoverLayer(void);

private:
	CCSprite* townBackground;
	CCSprite* m_pBack1;
	CCSprite* m_pBack2;
	

	CCNode* m_pPanle;
	int m_CurIndex;
	bool m_changing;
	int m_curMoney;
	CCLabelAtlas* m_pGameGold;
	HSGameFrisbee* m_pGameFrisbee;

	bool m_isRunGameGuide_1016;
	
	enum BackSate
	{
		BackSate_Invain = 0,
		BackSate_Await,
		BackSate_Take,
	};
	BackSate m_backSate;

	enum SelectMenuID
	{
		SelectMenuID_UnKnow,
		SelectMenuID_Start,
		SelectMenuID_Friend,
		SelectMenuID_Shop,
		SelectMenuID_PlayInfo,
	};
	SelectMenuID m_CurrentSelectMenuID;
	static float s_LoginListerTime;
public:
	virtual bool init(); 
	CREATE_FUNC(HSGameCoverLayer);
	
private:
	void Load();
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	void ChangeBackSata();
	
	void Update(float dt);
	//@net
public:
	bool RequestFighting();
	void ResponseFighting(FightingResponse*r);
	void ResponseTargetInfo(TargetInfoResponse*r);
	
	void ResponseFriendList(FriendListResponse* r);
	void ResponseAchievement(AchievementResponse* r);
private:
	//@logic
	void CallChange(CCObject* obj);
	void CallStartPair(CCObject* obj);
	void ChangeFinish();
	void CallPlayerInfo(CCObject* obj);
	void CallShop(CCObject* pobj);
	void CallSeting(CCObject* obj);
	void CallFriend(CCObject*);
	void Call_AchievementSystem(CCObject* pObj);

	void Call_First_Login();
	void Call_Loop_Login();
	void Call_Lister();

public:
	void Call_GameGuide();
private:
	//@Get
	CCSequence* GetMoveUpSequence();
	CCSequence* GetMoveDownSequnce();
private:
	//UI
	 
};



class HSGameCoverScene:public CCScene
{
public:
	HSGameCoverScene(void);
	~HSGameCoverScene(void);

public:

	HSCoverBacknormalLayer* normalLayer;
	HSCoverBackSeniorLayer* seniorLayer;
	HSGameCoverLayer* hsGameCoverLayer;
	//HSGamePlayerInfoLayer* hsGamePlayerInfoLayer;
	//HSGameShopLayer* hsGameShopLayer;
	

public:
	virtual bool init();
	CREATE_FUNC(HSGameCoverScene);
	
	inline HSGameCoverLayer* GetHSGameCoverLayer(){return this->hsGameCoverLayer;};
	inline HSCoverBacknormalLayer* GetHSCoverBackNormalLayer(){return this->normalLayer;};
	inline HSCoverBackSeniorLayer* GetHSCoverBackSeniorLayer(){return this->seniorLayer;};

// 	inline void SetHSGamePlayerInfoLayer(HSGamePlayerInfoLayer* layer)
// 	{
// 		this->hsGamePlayerInfoLayer = layer;
// 		this->addChild(layer,HS_BASE_TAG,HS_BASE_TAG);
// 	}
// 	inline HSGamePlayerInfoLayer* GetHSGamePlayerInfoLayer(){return this->hsGamePlayerInfoLayer;};

// 	inline void SetHSGameShopLayer(HSGameShopLayer* layer)
// 	{
// 		this->hsGameShopLayer = layer;
// 
// 		this->addChild(layer,HS_BASE_TAG,HS_BASE_TAG);
// 	}
// 
// 	inline HSGameShopLayer* GetHSGameShopLayer(){return this->hsGameShopLayer;};
};

#endif // __HSGameMainScene_H__
