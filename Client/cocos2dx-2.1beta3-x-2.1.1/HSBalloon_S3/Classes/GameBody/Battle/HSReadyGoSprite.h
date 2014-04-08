/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-27
 *	File base:	HSReadyGoSprite.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSReadyGoSprite_H__
#define __HSReadyGoSprite_H__
#pragma once
#include "HSTool.h"

class HSReadyGoSprite : public CCNode
{
public:
	HSReadyGoSprite(void);
	~HSReadyGoSprite(void);
public:
    static HSReadyGoSprite* create();
    
	virtual bool init();
    
    void FirstRun(float dt);
    
    void Call_01();
    void Call_02();
    void Call_03();
    void Call_04();
    void Call_05();
    void Call_06();
    
    
private:
    CCSprite* m_ps,*m_pt,*m_psShadow,*m_ptShadow,*m_pvs;
};




#endif /* defined(__HSReadyGoSprite_H__) */





