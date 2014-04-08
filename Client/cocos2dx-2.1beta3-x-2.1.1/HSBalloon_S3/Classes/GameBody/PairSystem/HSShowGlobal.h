/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-5
 *	File base:	HSShowGlobal.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSShowGlobal_H__
#define __HSShowGlobal_H__
#pragma once
#include "HSTool.h"


class HSShowGlobal : public CCNode
{
public:
	HSShowGlobal(void);
	~HSShowGlobal(void);
public:
    static HSShowGlobal* create();
    
	virtual bool init();
    
    void Call_BuyGold(CCObject* obj);
    
    void Updata(float dt);
    
private:
    CCLabelAtlas* m_pGameGold;
    int m_curMoney;
};




#endif /* defined(__HSShowGlobal_H__) */





