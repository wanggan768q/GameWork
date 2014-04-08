/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
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
#include "HSBalloonSprite.h"
#include "HSBalloonFactory.h"
#include "HSStratagemManager.h"
#include "HSComboManager.h"
#include "HSObjectPool.h"
#include "HSTouchBalloonEffect.h"
#include "HSSoulEffect.h"
#include "HSPropBalloonList.h"
#include "HSUsePropManager.h"
#include "HSContacListener.h"
#include "HSChangeColorEffect.h"
#include "HSLightEffect.h"

#include "HSBattlePauseLayer.h"
#include "HSBattleOverLayer.h"

#include "HSBufferPropManager.h"


#define HS_CREATE_PROP_BALLOON(__Type__) \
{ \
	__Type__* prop = __Type__::create(m_pWorld); \
	prop->setPosition(ccp(480,-320)); \
	this->addChild(prop,900); \
	m_propBalloonList.push_back(prop); \
	m_allBalloonSpriteList.push_back(prop); \
}

//Layer
class HSBattleLayer:public CCLayer
{
public:
	HSBattleLayer(void);
	~HSBattleLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSBattleLayer);

	static const int MAX_RHYTHM = 6;
	static const int MAX_STEP = 3;

	int m_iMinColorType;
	int m_iMaxColorType;

	map<BalloonColorType,CCTexture2D*> m_balloonColorMap;

	/**工作区AABB*/
	b2AABB m_workingAreaQueryAABB;

protected:
	b2World* m_pWorld;
	HSContacListener* m_pContacListener;
	/**判断输赢工作区*/
	b2AABB m_gameOverQueryAABB;
	HSBalloonFactory* m_pBalloonFactory;
	
	GLESDebugDraw* m_debugDraw;
	

	b2Vec2 bottomX;
	b2Vec2 bottomY;

	b2Vec2 topX;
	b2Vec2 topY; 

	b2Vec2 leftX;
	b2Vec2 leftY;

	b2Vec2 rightX; 
	b2Vec2 rightY ;

	b2Vec2 worldVectorl;
	
	static int s_rhythm[MAX_RHYTHM];
	int m_iRhythmIndex;
	int m_iCurrterStepIndex;

	float m_fLinearVelocityY ;

	static const BalloonColorType m_SMINCOLORTYPE = BALLOON_COLOR_BLUE;
	static const BalloonColorType m_SMAXCOLORTYPE = BALLOON_COLOR_PURPLE;

	double m_dNextFlyTime;

	bool m_bIsPause;
	
	list<CCPoint> m_lightningPostions;
	int m_lightningPostionsSize;
	std::vector<HSBalloonSprite*> m_workingAreaSprites;
	std::vector<HSBalloonSprite*> m_allBalloonSpriteList;

	std::vector<CCPoint> m_lightningTracks;
	/**闪电效果的速度*/
	float m_fLightningMoveSpeed;
	CCPoint m_lightningLastPos;
	CCPoint m_lightningCurrentPos;

	bool m_bIsPauseWorld;

	static CCPoint SCREEN_BESIDES;

	HSStratagemManager* m_pStratagemManager;	//当前场景上的机关

	CCProgressTimer* m_pEnergyFrameProgress;
	CCProgressTimer* m_pStratagemProgress;

	CCLabelAtlas* m_pGameGold;	//金币字
	CCLabelAtlas* m_pGameScore;	//得分字

	//保存已经生成好的气球
	HSObjectPool<HSBalloonSprite*> m_liveBalloonList;
	int m_iBalloonIdIndex;
	//保存道具气球
	std::vector<HSPropSpriteInterface*> m_propBalloonList;
	//效果
	HSObjectPool<HSTouchBalloonEffect*> m_touchBaloonEffectList;
	//魂魄
	HSObjectPool<HSSoulEffect*> m_soulEffectList;
	//表色动画效果
	HSObjectPool<HSChangeColorEffect*> m_changeColorEffect;
	//闪电效果
	HSObjectPool<HSLightEffect*> m_lightEffect;

	struct HSBlock
	{
		HSBlock()
		{
			pos = CCPointZero;
			pBalloon = NULL;
		}
		~HSBlock()
		{
			pos = CCPointZero;
			pBalloon = NULL;
		}
		CCPoint pos;
		HSBalloonSprite* pBalloon;
	};
	//
	std::vector<HSBlock> m_vPosArray;
	int m_iMaxPosArraySize;
	std::vector<HSBalloonSprite*> m_vListerBalloonPosY;

	int m_iFlyBalloonCount;

	HSBalloonSprite* m_lastTouchBalloon;

	int m_iGcInterval;

	SPX_Sprite* m_spxHighScore;
	bool m_isListerHigh;	//是否监听显示最高分

	HSCCSprite* m_pEnergyhigHlightedFrame;
	CCParticleSystemQuad* m_pEnergyHead;
	SPX_Sprite* m_pSpxEnergyFull;		//能量满

	bool m_isFreeEnergy;

	HSComboManager* m_pComboManager;

	bool m_isEnergyProgressFull;

	CCLayerColor* m_pMaskLayer;

	CCLabelAtlas* m_pGameTimeLabel;
	SPX_Sprite* m_pSpxClock;
	int m_iGameTime;
	float m_fDt;

	SPX_Sprite* m_pSpxReadyGo;

	bool m_isPlayReadyGo;

	CCSprite* m_pSpriteSuperman;
	bool m_isPlaySuperman;

	SPX_Sprite* m_pSpxTimeUp;

	HSBufferPropManager* m_pBufferPropManager;

	bool m_IsAllowRunBuffer;

	CCSprite* m_pGoldHeap;

	//@ GameGuide M
	int m_iComboIndex;
	float m_fGameGuideTime;
	bool m_isStep_Six;

	bool m_isStep_Nine;
	bool m_isStep_Ten;

	bool m_isStep_Eleven;


private:
	void Load();

	void InitPhysics();

	void LogicOfLihgtning(float dt);

	void LogicOfGameGuide_Six(float dt);

	void LogicOfGameGuide_Nine(float dt);

	void LogicOfGameGuide_Ten(float dt);

	void LogicOfGameGuide_Eleven();

	void Logic();

	void Logic_1();

	void LogicOfResponseTouchBalloon();

	void LogicWithListerEnergyFunn();

	void LogicOfTouchBalloon();

	void LogicOfHighestScore();

	void LogicOfStratagem(float dt);

	bool IsFlyBalloon(float dt);

	bool IsFlyBalloon_1(float dt);

	void RemoveWorkingAreaOneBody();

	void DrawLinhgtningPostion();

	void QueryAABB(BalloonGameData* pGameData);

	void DrawUI(BalloonGameData* pGameData , float dt);

	void UseProp(CCObject* obj);

	void LogicWithGCBalloon(float dt);

	void CreatePosArray();

	bool Fly(HSBalloonSprite* balloon);

	bool Fly_1(HSBalloonSprite* pBalloon);

	bool Fly();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void draw();
	virtual void onEnterTransitionDidFinish();

	bool IsGameOver();

	bool IsAllowRunBuffer();

	//@ Call Buffer
	bool CallGoldErptEnd();

	//@ Function
	void AddOneFlyBalloon();

	HSBalloonFactory* QueryFullScreenBalloon();

	//@ Call
	void CallGameOver(CCObject* obj);

	void CallRestart(CCObject* obj);

	void CallGameTime(CCNode* spxNode,void* pData);

	void CallEnergyFull(CCNode* spxNode,void* pData);

	void CallPlayReadyGoFinish(CCNode* spxNode,void* pData);

	void CallGameStart();

	void CallSupermanFinish();

	void CallTimeupFinish(CCNode* pSpx,void* pData);

	void RunBattleOverLayer();

	//@ Creat
	void CreateTouchBalloonEffect();

	void CreateBalloon();

	void CreatSoulEffect();

	void CreatChangeColorEffect();

	void CreatLightEffect();

	void CallPasue(CCObject* obj);

	void ListenStratagem();

	static bool compare( const HSBalloonSprite* s1,const HSBalloonSprite* s2);

	void Pause();

	void Resume();



	//@ Effect
	void PlaySoulEffect(HSBalloonSprite* balloon);

	void PlaySoulEffect(HSBalloonSprite* balloon,const ccColor4F& color,const CCPoint& destPos);

	void PlayTouchBalloonEffect(const CCPoint& pos);

	void PlayChangeColorEffect(HSBalloonSprite* balloon,const BalloonColorType& type, CCTexture2D* pTexture);

	void PlayLightEffect(HSBalloonSprite* balloon);

	void PlayTimeTimeWillOver(float durationTime);
	void CallPlayTimeTimeWillOverEnd();

	void PlaySupermanEffect();

	void PlayGoldHeapEffect();
	void CallPlayGoldHeapEffectEnd();

	void LayerShakeEffect();
	

	//@ Get
	CCLayerColor* GetModalLayer();

	map<BalloonColorType,CCTexture2D*>* GetBalloonAllTexture();

	b2World* GetWorld();

	HSStratagemManager* GetStragemManager();

	//@ Set
	void SetIsPause(bool b);

	void SetIsPauseWorld(bool b);

	void SetPosArraySize(int count);

	void SetGoldHeapSprite(CCSprite* s);

public:
	void Updata(float dt);

};




//Scene
class HSBattleScene:public CCScene
{
public:
	HSBattleScene(void);
	~HSBattleScene(void);
private:
	HSBattleLayer* hsBattleLayer;
	HSBattlePauseLayer* hsBattlePauseLayer;
	HSBattleOverLayer* hsBattleOverLayer;

public:
	virtual bool init();
	CREATE_FUNC(HSBattleScene);

	inline HSBattleLayer* GetHSBattleLayer(){return this->hsBattleLayer;};

	inline HSBattlePauseLayer* GetHSBattlePauseLayer(){return this->hsBattlePauseLayer;};

	inline HSBattleOverLayer* GetHSBattleOverLayer(){return this->hsBattleOverLayer;};

};
#endif // __HSBattleScene_H____
