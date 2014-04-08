/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/16   20:18
 *	File base:	HSBufferProp_GoldErupt.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBufferProp_GoldErupt_H__
#define __HSBufferProp_GoldErupt_H__
#pragma once
#include "HSBufferPropInterface.h"

class HSBufferProp_GoldErupt : public HSBufferPropInterface
{
public:
	HSBufferProp_GoldErupt(void);
	~HSBufferProp_GoldErupt(void);

private:
	SPX_Sprite* m_pSpxGoldErupt;
	bool m_isRunLogicRun;
	bool m_isBeginTime;
public:
	CREATE_FUNC(HSBufferProp_GoldErupt);

	bool init();

	virtual bool LogicBegin( float dt );

	virtual bool LogicEnd( float dt );

	virtual bool LogicCountDown(float dt);

	void CallGoldErupt(CCNode* pSpx, void* pData);

};

#endif // __HSBufferProp_GoldErupt_H____


