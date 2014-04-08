/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
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
#include "HSObjectPool.h"
#include "HSBox2dTool.h"
#include "HSCrossBorderInterface.h"

typedef enum _BalloonColorType
{
	//@ Color
	BALLOON_COLOR_Unknow = 0,
	BALLOON_COLOR_Blue,//蓝色
	BALLOON_COLOR_Purple,//紫色
	BALLOON_COLOR_Yellow,//黄色 
	BALLOON_COLOR_Red,//红色
	BALLOON_COLOR_Green,//绿色

	//@ Type
	BALLOON_COLOR_Petrifaction, //石化
	BALLOON_COLOR_Chameleon,	//变色龙
	BALLOON_COLOR_Camouflage,	//迷彩
	

}BalloonColorType;

#define HS_MIN_BalloonColorType BALLOON_COLOR_Blue
#define HS_MAX_BalloonColorType BALLOON_COLOR_Green


typedef struct
{
	CCTexture2D* base;
	CCTexture2D* luminous;
}BalloonTexture2D;


class HSBalloonSprite : public CCPhysicsSprite, public CCTargetedTouchDelegate  
{
public:	
	HSBalloonSprite(void);
	~HSBalloonSprite(void);

public:
	float m_fY;
	
	
private:	
	b2Body* CreateBody(b2World* world );
	
	void PlayDestroyBalloonEffect();
	void Call_PlayDestroyBalloonEffect(CCNode* pNode,void* pData);

	void NotificationBattleLayerRecycle();

public:
	virtual bool InitWithFile(const char* fileName,b2World* world,int id);
	virtual bool InitWithTexture(CCTexture2D* texture,b2World* world,int id);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual CCAffineTransform nodeToParentTransform();
	virtual void onEnter();
	virtual void onExit();
	virtual void draw();
	virtual void setScale(float fScale);
	virtual void setScaleX(float fScaleX);
	virtual void setScaleY(float fScaleY);
	virtual float getScale();
	virtual float getScaleX();
	virtual float getScaleY();
	void setScalePhysics(float fScale);
	
public:

	static HSBalloonSprite* create(const char* fileName,b2World* world,int id);
	static HSBalloonSprite* create(CCTexture2D* texture,b2World* world,int id);

	static void SetTouchObject(HSBalloonSprite* ps);
	static HSBalloonSprite* GetTouchObject();

	void SetTouchEnabled( bool b );

	void TouchBalloonBegin();
	void TouchBalloonEnd();	//静默死亡

	void SetB2Draw(GLESDebugDraw* debugDraw);

	CCRect TextureRect();

	bool ContainsTouchLocation(CCTouch* touch);	

	void ActivateCollisions();

	void DeactivateCollisions();

	void SetID(int id);
	int  GetID();

	void SetColorType(BalloonColorType type,float petrifactionTime = 0.f);
	BalloonColorType GetColorType();

	void Update(float dt);
	
	void SetGcPool(HSObjectPool<HSBalloonSprite*>* gcPool);
	
	void SetIsLiester(bool b);

	void Rest();

	void SetLuminous(bool b);

	void SetLuminousTexture2D(CCTexture2D* pTexture);

	void CallRemovePetrifactionEffect_FirstTwoSeconds();
	void CallRemovePetrifactionEffect_LastTwoSeconds();

	static std::map<BalloonColorType,BalloonTexture2D>* GetBalloonColorMap();

	void SetWillChangeColorType(BalloonColorType willColorType);

	void SetCrossBorderLister(HSCrossBorderInterface* pCross);

	void Call_BALLOON_COLOR_Chameleon();

	void Destroy();

private:
	b2World* m_pWorld;
	GLESDebugDraw* m_debugDraw;

	BalloonColorType m_BallonColorType;
	int m_id;
	float m_fScale;

	HSObjectPool<HSBalloonSprite*>* m_gcPool;
	bool m_isLister;
	bool m_isTouchEnabled;

	CCTexture2D* m_pLuminousTexture;
	CCTexture2D* m_pBaseTexture;
	bool m_isLuminous;

	static HSBalloonSprite* m_pTouchObject;

	SPX_Sprite* m_spxCamouflage;
	bool m_isCamouflage;

	SPX_Sprite* m_spxChameleon;

	static std::map<BalloonColorType,BalloonTexture2D> m_balloonColorMap;	//气球纹理 (等待释放内存)

	BalloonColorType m_lastColorType;
	BalloonColorType m_willChangeColorType;

	HSCrossBorderInterface* m_pCrossBorderInterface;

	CCPoint m_destroyPos;

};

#endif // __HSBallonSprite_H____

