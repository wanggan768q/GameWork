/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/20   16:51
 *	File base:	HSBattleOverLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBattleOverLayer_H__
#define __HSBattleOverLayer_H__
#pragma once
#include "HSTool.h"
class HSEffectItemSprite;
#endif // __HSBattleOverLayer_H____
class HSBattleOverLayer:public CCLayer
{
public:
	HSBattleOverLayer(void);
	~HSBattleOverLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSBattleOverLayer);
	void SetIsWin(bool win);
private:
	std::vector<HSEffectItemSprite*> m_EffectItemSpriteArray;
	std::vector<CCParticleSystemQuad*> m_activeParticleArray;
public:
	void Load();
	void Call_Continue(CCObject* obj);
	void Return();
	void Update(float dt);

	CCPoint GetRandomPosition();
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
private:
	bool  m_iswin;
	float m_interval;
	float m_count;
};