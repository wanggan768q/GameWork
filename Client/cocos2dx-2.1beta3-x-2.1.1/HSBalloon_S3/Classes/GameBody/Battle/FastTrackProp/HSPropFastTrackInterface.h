/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-24
 *	File base:	HSPropFastTrackInterface.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSPropFastTrackInterface_H__
#define __HSPropFastTrackInterface_H__
#pragma once
#include "HSTool.h"


class HSPropFastTrackInterface : public CCNode
{
public:
	HSPropFastTrackInterface(void);
	~HSPropFastTrackInterface(void);
public:
    
	virtual bool init() = 0;
    
    virtual void Function() = 0;
    
    virtual void Call_Sure(CCObject* obj);
    
    virtual CCNode* GetDialog();
    
    void Buy(int gold);
private:
    void Destroy();
    void UpdataTime(float dt);
private:
    CCLabelAtlas* m_pTime;
    int m_time;
};




#endif /* defined(__HSPropFastTrackInterface_H__) */





