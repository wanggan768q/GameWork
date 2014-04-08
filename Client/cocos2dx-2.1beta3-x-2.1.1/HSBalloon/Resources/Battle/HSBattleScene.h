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
#include "HSBallonSprite.h"
#include "HSBattonFactory.h"

//Layer
class HSBattleLayer:public CCLayer
{
public:
	HSBattleLayer(void);
	~HSBattleLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSBattleLayer);

protected:
	b2World* m_pWorld;
	b2AABB m_queryAABB;
	
	GLESDebugDraw* m_debugDraw;
	vector<HSBallonSprite*> m_ballonList;

	b2Vec2 bottomX;
	b2Vec2 bottomY;

	b2Vec2 topX; 
	b2Vec2 topY; 

	b2Vec2 leftX;
	b2Vec2 leftY;

	b2Vec2 rightX; 
	b2Vec2 rightY ;

	b2Vec2 worldVectorl;


	CCLabelTTF* balloonNumber_;
	CCLabelTTF* linearVelocity;
	CCLabelTTF* linearDamping_;
	CCLabelTTF* restitution___;
	CCLabelTTF* density_______;
	CCLabelTTF* friction______;

	BallonTestInfo* m_pBallonTestInfo;

private:
	void Load();

	void InitPhysics();
	
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void draw();

public:
	void Update(float dt);

	void MenuEvent(CCObject* sender);

	void BalloonNumberAdd(CCObject* obj);
	void BalloonNumberSub(CCObject* obj);

	void LinearVelocityAdd(CCObject* obj);
	void LinearVelocitySub(CCObject* obj);

	void LinearDampingAdd(CCObject* obj);
	void LinearDampingSub(CCObject* obj);

	void RestitutionAdd(CCObject* obj);
	void RestitutionSub(CCObject* obj);

	void DensityAdd(CCObject* obj);
	void DensitySub(CCObject* obj);

	void FrictionAdd(CCObject* obj);
	void FrictionSub(CCObject* obj);

	void SaveConfig(CCObject* obj);
	void RestConfig(CCObject* obj);
	void DefaultConfig(CCObject* obj);

public:
	void ResponseBattleEnter(message::BattleEnterResponse* response);
};




//Scene
class HSBattleScene:public CCScene
{
public:
	HSBattleScene(void);
	~HSBattleScene(void);
private:
	HSBattleLayer* hsBattleLayer;

public:
	virtual bool init();
	CREATE_FUNC(HSBattleScene);
	inline HSBattleLayer* GetHSBattleLayer(){return this->hsBattleLayer;};

};
#endif // __HSBattleScene_H____
