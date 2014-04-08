/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
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

class HSBattleOverLayer : public CCLayer
{
public:
	HSBattleOverLayer(void);
	~HSBattleOverLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSBattleOverLayer);
    
private:
	void Load();
    
    void Updata(float dt);
    
public:
    void SetIsWin(bool win);
    void Call_Back(CCObject* obj);
    void Return();
    static void SetTargetFingureID(int id);
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
private:
	bool  m_iswin;
    CCLabelTTF* m_pName;
    CCLabelTTF* m_pLianSheng;
    CCLabelTTF* m_pJinbi;
    CCLabelTTF* m_pZhanJi;
    CCSprite* m_pSelfFigure;
    CCSprite* m_pTargetFigure;
    static int S_TARGET_FINGURE_ID;
};
#endif // __HSBattleOverLayer_H____