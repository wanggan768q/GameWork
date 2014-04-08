/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/04   16:57
 *	File base:	HSLightEffect.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSLightEffect_H__
#define __HSLightEffect_H__
#pragma once
#include "HSBase.h"
#include "SPX_Sprite.h"
#include "HSObjectPool.h"
#include "HSBalloonSprite.h"

class HSLightEffect : public CCNode
{
private:
	HSLightEffect(void);
public:
	~HSLightEffect(void);
public:
	SPX_Sprite* m_pSpx;
	HSObjectPool<HSLightEffect*>* m_gcPool;
	bool m_isLister;

public:
	static HSLightEffect* create();

	bool Init();

	void SetGcPool(HSObjectPool<HSLightEffect*>* gc);

	void Updata(float dt);

	void PlayEffectBegin(HSBalloonSprite* balloon);

	void PlayEffectEnd(CCNode* spxNode,void* data);
};

#endif // __HSLightEffect_H____


