/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/03/13   10:54
 *	File base:	HSBallonSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBallonSprite_H__
#define __HSBallonSprite_H__
#pragma once
#include "HSTool.h"
#include "HSBox2dShapeCache.h"
#include "cocos-ext.h"
#include "GLES-Render.h"
USING_NS_CC_EXT;
#include "HSBalloonConfig.h"
#include "HSObjectPool.h"




class HSBalloonSprite : public CCPhysicsSprite, public CCTargetedTouchDelegate  
{
public:	
	HSBalloonSprite(void);
	~HSBalloonSprite(void);

protected:

	b2World* m_pWorld;
	GLESDebugDraw* m_debugDraw;

	BalloonTestInfo* m_pBallonTestInfo;

	int m_id;
	BalloonColorType m_BallonColorType;

	float m_fScale;


	bool m_isOnlyAddParticle;	//是否只添加一次

	bool m_isTouchEndOver;		//是否在触摸结束消失( 特殊 皇冠气球) 默认为false 在SPX动画结束后消失 


	CCParticleSystemQuad* m_pParticle1;
	CCParticleSystemQuad* m_pParticle2;
	CCParticleSystemQuad* m_pParticle3;
	CCParticleSystemQuad* m_pParticle4;

	static HSBalloonSprite* s_TouchBalloon;

	HSObjectPool<HSBalloonSprite*>* m_gcPool;
	bool m_isLister;

	SPX_Sprite* m_spxShield;

	bool m_isTouchEnabled;

public:
	float m_fY;
	
	
private:	
	b2Body* createBody(b2World* world );

public:

	static HSBalloonSprite* create(const char* fileName,b2World* world,int id);
	static HSBalloonSprite* create(CCTexture2D* texture,b2World* world,int id);

	virtual bool InitWithFile(const char* fileName,b2World* world,int id);
	bool InitWithTexture(CCTexture2D* texture,b2World* world,int id);

	void SetTouchEnabled(bool b);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);


	void TouchBalloonBegin();
	void TouchBalloonEnd();	//静默死亡

	virtual CCAffineTransform nodeToParentTransform();

	inline void SetB2Draw(GLESDebugDraw* debugDraw){m_debugDraw = debugDraw;}

	virtual void onEnter();

	virtual void onExit();

	CCRect TextureRect();

	bool ContainsTouchLocation(CCTouch* touch);

	virtual void draw();

	void ActivateCollisions();

	void DeactivateCollisions();

	void SetID(int id);
	int GetID();;

	void SetColorType(BalloonColorType type);

	BalloonColorType GetColorType();

	void Update(float dt);

	void SetIsTouchEndOver(bool b);	

	void SetGcPool(HSObjectPool<HSBalloonSprite*>* gcPool);

	static HSBalloonSprite* GetTouchBaloon();
	static void SetTouchBaloon(HSBalloonSprite* balloon);

	void AddShield();

	void SetIsLiester(bool b);

	void Rest();


	void CallSpxShieldAction_1(CCNode* spxNode,void* pData);

	void CallSpxShieldAction_2(CCNode* spxNode,void* pData);

};

#endif // __HSBallonSprite_H____

