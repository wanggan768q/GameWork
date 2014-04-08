/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/15   15:58
 *	File base:	HSTouchBalloonEffect.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSTouchBalloonEffect_H__
#define __HSTouchBalloonEffect_H__
#pragma once
#include "HSBase.h"
#include "HSObjectPool.h"
#include "HSBalloonConfig.h"

class HSTouchBalloonEffect : public CCNode
{
public:
	HSTouchBalloonEffect(void);
	~HSTouchBalloonEffect(void);

private:
	CCParticleSystemQuad* m_pParticle1;

	bool m_isLister;

	HSObjectPool<HSTouchBalloonEffect*>* m_gcPool;

public:
	static HSTouchBalloonEffect* create();

	bool Init();


	void PlayEffectBegin(CCPoint pos);


	void PlayEffectEnd();

	void Update(float dt);

	void SetIsLister(bool b);

	void SetGcPool(HSObjectPool<HSTouchBalloonEffect*>* gcPool);


};

#endif // __HSTouchBalloonEffect_H____


