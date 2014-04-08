/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/23   9:35
 *	File base:	HSSoulEffect.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSSoulEffect_H__
#define __HSSoulEffect_H__
#pragma once
#include "HSBase.h"
#include "HSObjectPool.h"
#include "HSReadUI.h"
#include "HSBalloonConfig.h"

class HSSoulEffect : public CCNode
{
public:
	HSSoulEffect(void);
	~HSSoulEffect(void);

private:
	CCParticleSystemQuad* m_pSoul;
	CCPointArray* m_pPointArray;
	HSObjectPool<HSSoulEffect*>* m_pSoulEffectPool;
	float m_fTension;

	bool m_isLister;

	ccColor4F m_defaultColor;

public:
	static HSSoulEffect* create(CCLayer* layer);

	bool Init(CCLayer* layer);

	void SetSoulColor(const ccColor4F& color);

	void SetTrack(CCPointArray* track);

	void SetTension(float tension);

	void SetGcPool(HSObjectPool<HSSoulEffect*>* pool);

	void Play();

	void CallFinish();

	void Updata(float dt);
};


#endif // __HSSoulEffect_H____
