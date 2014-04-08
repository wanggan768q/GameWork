/********************************************************************
 *  Copyright(C) 2012 Ambition_HS ( All rights reserved. )
 *	Created:	2012/11/01   13:17
 *	File base:	HSBattleScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBattleScene_H__
#define __HSBattleScene_H__
#pragma once
#include "HSTool.h"
#include "HSRaycastCallback.h"
#include "HSContacListener.h"
#include "HSBalloonFactory.h"
#include "HSLine.h"
#include "HSPoint.h"
#include "HSPropManager.h"
#include "HSBattleTranscribe.h"
#include "HSPlayerActionManager.h"
#include "HSReadyGoSprite.h"
#include "HSAllPropFastTrackHead.h"

#define HS_GET_BattleLayer() ((dynamic_cast<HSBattleScene*>(CCDirector::sharedDirector()->getRunningScene()))->GetHSBattleLayer())
#define HS_BATTLE_OVERLAYER 200;
//Layer
class HSBattleLayer : public CCLayer,public HSCrossBorderInterface
{
public:
	HSBattleLayer(void);
	~HSBattleLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSBattleLayer);

public:

	typedef struct _HSDropApply
	{
		_HSDropApply()
		{
			count = 0;
			colorType = BALLOON_COLOR_Red;
		}
		~_HSDropApply()
		{
			count = 0;
			colorType = BALLOON_COLOR_Unknow;
		}
		int count;
		BalloonColorType colorType;
	}HSDropApply;

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void draw();
	virtual void onEnterTransitionDidFinish();
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

private:
	//@ Init
	void Load();
	void LoadUI();
	void InitProp();
	void InitPhysics();
    void InitPlayerAction();
	void CreateBalloon();
	void LoadBalloonTexture2D();
	void InitOtherBattleScreen();

	//@ Func
	bool Drop(HSBalloonSprite* s);
	void DestroyBalloon();
	void DestroyLine();
	void SetBalloonColorType(HSBalloonSprite* ps,const BalloonColorType& colorType);
	bool IsGameOver();
	void ClearUserPropInfo();
    
    //@ Prop Function
    void Function_Chameleon();
    void Function_Meidusha();

	//@ Set
	void SetDropCount(int v);

	//@ Draw
	void DrawLine(float dt);
	void DrawLine(HSBalloonSprite* s1,HSBalloonSprite* s2);
	void DrawLine(const CCPoint& p1,const CCPoint& p2);

	//@ Logic
	void Logic(float dt);
	void Logic_Drop(float dt);
    void Logic_LineChange(float dt);


	//@ Updata
	void UpdataWord(float dt);
	void UpdataMoney(float dt);
	void UpdataCombo(float dt);
	void UpdataOtherBattleScreen(const BattleInfo& info);
	void UpdataOtherBattleScreen_UserPropInfo(const BattleInfo& info);
	

public:
	bool DestroyBalloon(HSBalloonSprite* s);

	void AddUserProp(const PropInfo* pPropInfo);

	CCSprite* GetFingerSprite();

	HSBalloonSprite* GetBalloonSprite(int key);

	map<int,HSBalloonSprite*>* GetBalloonMap();

	//@ Effect
	void PlayUserPropEffect(HSPropIconInterface* pIcon);
	void Call_PlayUserPropEffect(CCNode* pNode,void* pData);
	void Call_PlayUserPropEffect(CCNode* pNode);

	void PlayDestroyBalloon5Effect(const CCPoint& pos,int count);
	void Call_PlayDestroyBalloon5Effect(CCNode* pNode);
    void Call_PlayDestroyBalloon5Effect_Bomb(CCNode* pNode,void* pData);

	void PlayUserPropEffect_OtherScreen(const PropInfo* propInfo);
	void Call_PlayUserPropEffect_OtherScreen(CCNode* pNode,void* pData);
	void Call_PlayUserPropEffect_OtherScreen(CCNode* pNode);

	void PlayUserPropEffect_EnergyShield_OtherScreen(const PropInfo* propInfo);
	void Call_PlayUserPropEffect_EnergyShield_OtherScreen(CCNode* pNode);

	void PlayDestroyBalloonEffect(const CCPoint& pos);
	void Call_PlayDestroyBalloonEffect(CCNode* pNode,void* pData);

	void PlayBlueFrameBlink(float duration);
	void PlayRedFrameBlink(float duration);
	void PlayBlinkEffect(CCNode* pNode , float duration);
	void Call_PlayBlinkEffect(CCNode* pNode);
    
    void PlayRewardsEffect(int destroyCount);
    void Call_PlayRewardsEffect(CCNode* pNode);
    
    void PlayWillDieEffecr();
    void CancelPlayWillDieEffecr();
    
    void PlayBeatEffect();

	void PlayGameWinEffect();


	//@ Get
	HSBalloonFactory* GetScreenAllBalloon();
	std::vector<HSBattleLayer::HSDropApply>* GetPetrifactionBalloonNumList();
	std::vector<HSBattleLayer::HSDropApply>* GetDropPetrifactionList();
    std::set<HSBalloonSprite*>* GetDropBalloonList();
    
    //得到闪烁框
    CCSprite* GetWillDieRedFrame();
    CCNode* GetOtherScreen();
    HSPlayerActionManager* GetPlayerActionManager();

	//@ Call
	void Call_GameOver();
    
    
    //@FastProp
    void SetPropWave(HSPropFastTrackInterface* wave);
    HSProp_Wave* GetPropWave();

public:
	//@ Net
	void Send();
	void SendGameOver();
    
    
	void ResponseBattleResult(BattleResultResponse* pMsg);
	void ResponseBattleData(BattleDataResponse* pMsg);
    
protected:
    /*
     *发送战斗数据(屏幕数据)
     */
    virtual void SendBattleData(void* pData);
    /*
     *发送消球数据(Lan 模式 不需要发送)
     */
    virtual void SendDestroyBalloon(void* pData);
    /*
     *发送游戏失败数据
     */
    void SendBattleResultRequest();
    
public:
    void ResLanBattleResultNotice(LanBattleResultNotice* pMsg);
    

public:
	void Updata(float dt);

	virtual void HandleCross( CCObject* pObj );

private:

	typedef enum
	{
		HS_Touch_Begin,
		HS_Touch_Move,
		HS_Touch_End,
	}HSTouchState;

	

	//@ Physics
	b2World* m_pWorld;
	GLESDebugDraw* m_pDebugDraw;
	HSContacListener* m_pContacListener;
	b2Vec2 m_bottomX;
	b2Vec2 m_bottomY;
	b2Vec2 m_topX;
	b2Vec2 m_topY; 
	b2Vec2 m_leftX;
	b2Vec2 m_leftY;
	b2Vec2 m_rightX; 
	b2Vec2 m_rightY;
	b2Vec2 m_worldVectorl;
	CCSize m_offsetTop;
	CCSize m_offsetBottom;
	CCSize m_offsetLeft;
	CCSize m_offsetRight;
	bool m_isPauseWorld;

	//@ Raycast
	CCPoint m_beginPos,m_endPos;
	HSRaycastCallback* m_pRaycast;
	


	//@ Prop
	HSPropManager* m_pHSPropManager;
    HSPropFastTrackInterface* m_pPropWave;

	//@ Game
	CCNode* m_pSelfBattleScreec;
	bool m_isPauseGame;
	bool m_isGameOver;
	int m_dropCount;
	int m_dripIndex;
	std::set<HSBalloonSprite*> m_notDropBalloonList;		// 没有掉落的球
	std::set<HSBalloonSprite*> m_dropBalloonList;			// 已经掉落的球
	float m_dropIntervalMinTime;							// 掉落最小间隔时间
	float m_dropIntervalMaxTime;							// 掉落最大间隔时间
	float m_dropIntervalTime;
	float m_gameTime;										// 最小颜色类型
	BalloonColorType minColorType ;
	BalloonColorType maxColorType ;
	std::vector<BalloonColorType> m_colorTypePool;			//颜色类型池
	map<int,HSBalloonSprite*> m_balloonMap;                 //球MAP

	float m_LinearVelocityMinY;
	float m_LinearVelocityMaxY;

	std::vector<HSLine*> m_lineList;
	std::vector<HSPoint*> m_pointList;
	int m_drawLineCount;

	b2AABB m_workArea;

	std::vector<HSDropApply> m_PetrifactionBalloonNumList;
	HSDropApply m_dropPetrifaction;
    HSDropApply m_dropCamouflage;
	std::vector<HSDropApply> m_dropPetrifactionList;

	std::vector<const PropInfo*> m_userPropList;

	CCSprite* m_pBlueFrame;
	CCSprite* m_pRedFrame;

	CCSprite* m_pComboFrame;
	CCLabelAtlas* m_pComboNumber;
	CCLabelAtlas* m_pMoney;
	int m_lastMoney;
    float m_sendScreenInfoIntervalTime;

	CCSprite* m_pFinger;
	bool m_isInitFinish;
	bool m_isAllowRunGameGuide_1014;
    
    SPX_Sprite* m_pBombSpx;
    
    HSPlayerActionManager* m_pPlayerActionManager;
    CCSprite* m_pWillEffect;
	


	//@ Other Battle Screen
	CCNode* m_pOtherBattleScreen;
	long long m_lastTimestamp;
	std::vector<CCSprite*> m_OtherScreenBalloonList;


	//@
	HSBattleTranscribe* m_pBattleTranscribe;
	
};



#include "HSBattleOverLayer.h"
//Scene
class HSBattleScene:public CCScene
{
public:
	HSBattleScene(void);
	~HSBattleScene(void);
private:
	HSBattleLayer* hsBattleLayer;
	HSBattleOverLayer* hsBattleOverLayer;
public:
	virtual bool init();
	CREATE_FUNC(HSBattleScene);

	HSBattleLayer* GetHSBattleLayer();;
	HSBattleOverLayer* GetHSBattleOverLayer();;
	void SetHSBattleOverLayer(HSBattleOverLayer* hsBattleOverLayer);
};
#endif // __HSBattleScene_H____












