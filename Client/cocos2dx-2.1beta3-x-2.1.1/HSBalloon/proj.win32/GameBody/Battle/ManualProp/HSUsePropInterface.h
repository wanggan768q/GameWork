/********************************************************************
*  Copyright(C) 2013 Zrong ( All rights reserved. )
*	Created:	2013/05/08   10:38
*	File base:	HSUsePropInterface.h
*	Author:		Ambition
*	
*	Purpose:	
*********************************************************************/
#ifndef __HSUsePropInterface_H__
#define __HSUsePropInterface_H__
#pragma once
#include "HSTool.h"

#ifndef HS_CREATE_USE_PROP_FUNC
#define HS_CREATE_USE_PROP_FUNC(__TYPE__) \
static __TYPE__* create(const message::PropInfo* propInfo) \
{ \
	__TYPE__ *pRet = new __TYPE__(); \
	if (pRet && pRet->Init(propInfo)) \
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
#endif /* HS_CREATE_USE_PROP_FUNC */

class HSUsePropInterface : public HSCCSprite ,public CCTargetedTouchDelegate
{
public:
	HSUsePropInterface(void);
	~HSUsePropInterface(void);

private:
	bool m_isListerFristUpdata;
	SPX_Sprite* m_spxUseProp;
	CCProgressTimer* m_CD_Progress;
	
public:
	const message::PropInfo* m_propInfo;
	int m_propIndex;
public:

	virtual bool Init(const message::PropInfo* propInfo);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();

	virtual void onExit();

	message::PropInfo_PropType GetPropType();

	virtual bool ContainsTouchLocation( CCTouch* touch );

	bool TouchBalloonBegin();

	void TouchBalloonEnd();

	void Call_ProgressEnd();

	void Call_Effect(CCNode* pSpx,void* pData);

	virtual void AddNodeToParent() ;

	virtual void Updata(float dt);
};

#endif // __HSUsePropInterface_H__
