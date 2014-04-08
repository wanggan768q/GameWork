/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/04   16:56
 *	File base:	HSChangeColorEffect.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSChangeColorEffect_H__
#define __HSChangeColorEffect_H__
#pragma once
#include "HSBase.h"
#include "SPX_Sprite.h"
#include "HSObjectPool.h"
#include "HSBalloonSprite.h"

class HSChangeColorEffect : public CCNode
{
private:
	HSChangeColorEffect(void);
public:
	~HSChangeColorEffect(void);

private:
	SPX_Sprite* m_pSpx;
	HSObjectPool<HSChangeColorEffect*>* m_gcPool;

	BalloonColorType m_WillChangeColorType;
	CCTexture2D* m_pWillChanggeTexture;
	HSBalloonSprite* m_pWillChangeBalloon;
public:
	static HSChangeColorEffect* create();

	bool Init();

	void SetGcPool(HSObjectPool<HSChangeColorEffect*>* gc);

	void Updata(float dt);

	void PlayEffectBegin(HSBalloonSprite* balloon,const BalloonColorType& type,CCTexture2D* pTexture);

	void PlayEffectEnd(CCNode* spxNode,void* data);
};

#endif // __HSChangeColorEffect_H____

