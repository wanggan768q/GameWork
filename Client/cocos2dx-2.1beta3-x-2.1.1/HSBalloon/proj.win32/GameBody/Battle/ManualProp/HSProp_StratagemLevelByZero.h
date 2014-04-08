/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/02   15:14
 *	File base:	HSProp_StratagemLevelByZero.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_StratagemLevelByZero_H__
#define __HSProp_StratagemLevelByZero_H__
#pragma once
#include "HSUsePropInterface.h"
#include "HSBalloonConfig.h"

class HSProp_StratagemLevelByZero : public HSUsePropInterface
{
public:
	HSProp_StratagemLevelByZero(void);
	~HSProp_StratagemLevelByZero(void);

private:
	SPX_Sprite* m_spxStratagemLevelByZero;

public:
	HS_CREATE_USE_PROP_FUNC(HSProp_StratagemLevelByZero);

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void AddNodeToParent();

	void CallStratagemLevelByZeroFinish(CCNode* spxNode,void* pData);

};

#endif // __HSProp_StratagemLevelByZero_H____

