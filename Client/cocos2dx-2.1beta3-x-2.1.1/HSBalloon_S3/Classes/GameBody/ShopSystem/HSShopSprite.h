/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/09/12   10:31
 *	File base:	HSShopSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSShopSprite_H__
#define __HSShopSprite_H__
#pragma once
#include "HSTool.h"
#include "HSJson.h"

class HSShopSprite:public HSCCSprite
{
public:
	HSShopSprite(void);
	~HSShopSprite(void);
public:
	static HSShopSprite* create(const CCSize& size,const message::BuyGold&);
	bool Init(const CCSize& size,const message::BuyGold&);
public:
	//@update
	void UpdateShopInfo(const message::BuyGold&);

public:
	//@Logic
	void CallBuy(CCObject* pSender);
public:
	//@UI
	CCSprite* m_pIcon;
	CCLabelTTF* m_pDescrib;
	CCLabelTTF* m_pSale;
    CCLabelTTF* m_pName;
	CCMenu* m_pBuy;
	message::BuyGold m_BuyGold;
	//@data
};

#endif // __HSShopSprite_H____

