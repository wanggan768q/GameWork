/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-6
 *	File base:	HSReadyPropItem.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSReadyPropItem_H__
#define __HSReadyPropItem_H__
#pragma once
#include "HSTool.h"

class HSReadyPropItem : public CCNode
{
public:
	HSReadyPropItem(void);
	~HSReadyPropItem(void);
public:
    static HSReadyPropItem* create(const PropInfo& propInfo,int index);
    
	virtual bool init(const PropInfo& propInfo,int index);
    
    void Call(CCObject* obj);
    
private:
    bool IsAlreadyCarry();
    
private:
    const PropInfo* m_propInfo;
    CCMenuItemToggle* m_pToggle;
    
    HSCCSprite* m_pJiaoBiao;
    HSCCSprite* m_pSuo;
    
    bool m_isNeedCarry;
};




#endif /* defined(__HSReadyPropItem_H__) */





