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
#include "HSGameGuideRaycastCallback.h"
#include "HSContacListener.h"
#include "HSBalloonFactory.h"
#include "HSLine.h"
#include "HSPoint.h"
#include "HSPropManager.h"
#include "HSBattleTranscribe.h"

#define HS_GET_BattleLayer() ((dynamic_cast<HSBattleScene*>(CCDirector::sharedDirector()->getRunningScene()))->GetHSBattleLayer())

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

	typedef struct _HSPetrifaction
	{
		_HSPetrifaction()
		{
			count = 0;
			colorType = BALLOON_COLOR_Unknow;
		}
		~_HSPetrifaction()
		{
			count = 0;
			colorType = BALLOON_COLOR_Unknow;
		}
		int count;
		BalloonColorType colorType;
	}HSPetrifaction;

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

	//@ Set
	void SetDropCount(int v);

	//@ Draw
	void DrawLine(float dt);
	void DrawLine(HSBalloonSprite* s1,HSBalloonSprite* s2);
	void DrawLine(const CCPoint& p1,const CCPoint& p2);

	//@ Logic
	void Logic(float dt);
	void Logic_Drop(float dt);
	void Logic_GameGuide(float dt);


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

	void PlayDestroyBalloon5Effect(const CCPoint& pos);
	void Call_PlayDestroyBalloon5Effect(CCNode* pNode);

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

	void PlayGameWinEffect();


	//@ Get
	HSBalloonFactory* GetScreenAllBalloon();
	std::vector<HSBattleLayer::HSPetrifaction>* GetPetrifactionBalloonNumList();	//自己屏幕所产生的石化气球
	std::vector<HSBattleLayer::HSPetrifaction>* GetDropPetrifactionList();			//目标产生的石化气球将要掉落到自己屏幕上

	//@ Call
	void Call_GameOver();

public:
	//@ Net
	void Send();
	void SendGameOver();
	void ResponseBattleResult(BattleResultResponse* pMsg);
	void ResponseBattleData(BattleDataResponse* pMsg);

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

	//@ Game
	CCNode* m_pSelfBattleScreec;
	bool m_isPauseGame;
	bool m_isGameOver;
	int m_dropCount;
	int m_dripIndex;
	std::set<HSBalloonSprite*> m_notDropBalloonList;		// 没掉落的气球
	std::set<HSBalloonSprite*> m_dropBalloonList;			// 已经掉落的气球
	float m_dropIntervalMinTime;							// 掉落间隔时间控制
	float m_dropIntervalMaxTime;							// 同上
	float m_dropIntervalTime;
	float m_gameTime;										// 游戏持续的时间
	BalloonColorType minColorType ;
	BalloonColorType maxColorType ;
	std::vector<BalloonColorType> m_colorTypePool;			//颜色池子
	map<int,HSBalloonSprite*> m_balloonMap;							//所有气球 map 表

	float m_LinearVelocityMinY;
	float m_LinearVelocityMaxY;

	std::vector<HSLine*> m_lineList;
	std::vector<HSPoint*> m_pointList;
	int m_drawLineCount;

	b2AABB m_workArea;

	std::vector<HSPetrifaction> m_PetrifactionBalloonNumList;
	HSPetrifaction m_dropPetrifaction;
	std::vector<HSPetrifaction> m_dropPetrifactionList;

	std::vector<const PropInfo*> m_userPropList;

	CCSprite* m_pBlueFrame;
	CCSprite* m_pRedFrame;

	CCSprite* m_pComboFrame;
	CCLabelAtlas* m_pComboNumber;
	CCLabelAtlas* m_pMoney;
	int m_lastMoney;

	//@ //新手引导
	CCSprite* m_pFinger;
	bool m_isInitFinish;
	bool m_isAllowRunGameGuide_1014;
	


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












