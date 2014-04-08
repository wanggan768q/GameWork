/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-13
 *	File base:	HSFigureSprite.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSFigureSprite_H__
#define __HSFigureSprite_H__
#pragma once
#include "HSTool.h"

class HSFigureSprite : public HSCCSprite
{
public:
	HSFigureSprite(void);
	~HSFigureSprite(void);
public:
	static HSFigureSprite* create(int index);
    
	bool Init(int index);
    
    void SetUseing(bool isUse);
    void SetAlreadyBuy(bool isAlreadyBuy);
    
	void UpdataHSFigureSprite(int index,FigureData_FigureBase* base);
    
    void Call_Change(CCObject* obj);
    void Call_Unlock(CCObject* obj);
    
    static void SetLastFigureUnlock();
    static void SetLastFigureChange();
    
private:
    CCSpriteFrame* m_pDefaualSpriteFrame;
    CCSpriteFrame* m_pCarrySpriteFrame;
    
    CCMenu* m_pUnlockMenu;
    CCMenuItemSprite* m_pChangeMenu;
    CCSprite* m_pUse;
    HSGraySprite* m_pFigureFrame;
    CCSprite* m_pLock;
    CCSprite* m_pGoldIcon;
    HSGraySprite* m_pFigure;
    CCSprite* m_pBuyFescribeFrame;
    CCLabelTTF* m_pBuyDescribe;
    CCLabelTTF* m_pPrice;
    
    FigureData_FigureBase* m_pData;
};


#endif /* defined(__HSFigure_H__) */





