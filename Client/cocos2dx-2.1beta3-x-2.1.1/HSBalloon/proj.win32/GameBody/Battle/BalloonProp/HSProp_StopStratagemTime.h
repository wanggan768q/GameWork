/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/30   9:44
 *	File base:	HSProp_StopStratagemTime.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_StopStratagemTime_H__
#define __HSProp_StopStratagemTime_H__
#pragma once
#include "HSPropSpriteInterface.h"

class HSProp_StopStratagemTime : public HSPropSpriteInterface
{
public:
	HSProp_StopStratagemTime(void);
	~HSProp_StopStratagemTime(void);

private:
	SPX_Sprite* m_spxStopStratagemTime;
	const static int M_STOPTIME = 10;
	float m_fPastTime;
	bool m_isPauseUpdate;

public:
	HS_CREATE_PROP_FUNC(HSProp_StopStratagemTime);

	virtual bool Init( b2World* world );

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent );

	virtual void AddNodeToParent();

	virtual void Updata( float dt );

	void CallSpxStopStratagemTimeAction_1(CCNode* node,void* data);

	void CallSpxStopStratagemTimeActionFinish(CCNode* node,void* data);

};
#endif // __HSProp_StopStratagemTime_H____


