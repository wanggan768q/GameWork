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
#include "CCPhysicsSprite.h"
USING_NS_CC_EXT;
#include "HSBalloonConfig.h"

typedef enum _BallonColorType
{
	BALLON_COLOR_BLUE = 0x0c,//蓝色
	BALLON_COLOR_BROWN,//棕色
	BALLON_COLOR_GREEN,//绿色
	BALLON_COLOR_ORANGE,//橙色
	BALLON_COLOR_PURPLE,//紫色
}BallonColorType;


class HSBallonSprite : public CCPhysicsSprite, public CCTargetedTouchDelegate  
{
public:
	HSBallonSprite(void);
	~HSBallonSprite(void);

protected:

	b2World* m_pWorld;
	GLESDebugDraw* m_debugDraw;

	BallonTestInfo* m_pBallonTestInfo;

	int m_id;
	BallonColorType m_BallonColorType;
	
private:
	b2Body* createBody(b2World* world );

public:

	static HSBallonSprite* create(const char* fileName,b2World* world,int id);

	bool InitWithFile(const char* fileName,b2World* world,int id);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	inline void SetB2Draw(GLESDebugDraw* debugDraw){m_debugDraw = debugDraw;}

	virtual void onEnter();

	virtual void onExit();

	CCRect TextureRect();

	bool ContainsTouchLocation(CCTouch* touch);

	virtual void draw();

	void ActivateCollisions();

	void DeactivateCollisions();

	inline int GetID(){return m_id;};

	void SetColorType(BallonColorType type);
};

#endif // __HSBallonSprite_H____

