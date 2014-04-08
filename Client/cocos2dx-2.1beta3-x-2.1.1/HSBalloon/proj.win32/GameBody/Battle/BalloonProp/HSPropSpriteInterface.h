/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/29   15:15
 *	File base:	HSPropSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSPropSpriteInterface_H__
#define __HSPropSpriteInterface_H__
#pragma once
#include "HSBalloonSprite.h"
#include "HSObjectPool.h"

#ifndef HS_CREATE_PROP_FUNC
#define HS_CREATE_PROP_FUNC(__TYPE__) \
	static __TYPE__* create(b2World* world) \
	{ \
		__TYPE__ *pRet = new __TYPE__(); \
		if (pRet && pRet->Init(world)) \
		{ \
			pRet->autorelease(); \
			return pRet; \
		} \
		else \
		{ \
			delete pRet; \
			pRet = NULL; \
			return NULL; \
		} \
}
#endif // !HS_CREATE_PROP_FUNC



class HSPropSpriteInterface : public HSBalloonSprite
{
public:
	HSPropSpriteInterface(void);
	virtual ~HSPropSpriteInterface(void);

private:
	BalloonPropsType m_type;
	int m_iMaxTouchCount;		//µã»÷´ÎÊý
	static int m_iDefaultID;

	bool m_isListerFristUpdata;

public:

	virtual void SetIsListerFristUpdata(bool b);

	virtual bool GetIsListerFristUpdata();

	virtual void SetPropType(BalloonPropsType type);

	virtual BalloonPropsType GetPropType();

	virtual void SetMaxTouchCount(int count);

	virtual int GetMaxTouchCount();

	virtual bool Init(b2World* world) = 0;

// 	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) = 0;
// 	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) = 0;
// 	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) = 0;
// 	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) = 0;

	virtual void AddNodeToParent() = 0;

	virtual void Updata(float dt);

};
#endif // __HSPropSpriteInterface_H__


