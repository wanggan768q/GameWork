/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-5
 *	File base:	HSShowEndurance.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSShowEndurance_H__
#define __HSShowEndurance_H__
#pragma once
#include "HSTool.h"
#include "HSTimerLabel.h"
#include "HSLock.h"

class HSShowEndurance : public CCNode
{
public:
	HSShowEndurance(void);
	~HSShowEndurance(void);
public:
    static HSShowEndurance* create();
    
    static void AddEndurance();
    
    static void SubEndurance();
    
	virtual bool init();
    
    void CreateTimeLabel();
    
    void Updata(float dt);
    
    void Call_PlansFinshSelector();
    
    void Call_PerSecondSelector();
    
    void Call_DestroySelector();
    
public:
    static const int S_C_MAX_SEC = 600;                 //最大秒数
    static const int S_C_ENDURANCE_COUNT = 5;           //最大体力值
    static int S_CURRENT_ENDURANCE_COUNT;               //当前体力个数(指完整桃心)
    static int S_CURRENT_OPERATION_ENDURANCE_INDEX;     //当前操作的体力(指跟计时器挂钩的桃心) 当前体力 +1 大于 5 代表体力满了
    static unsigned long long S_LAST_REMAIN;            //上次停止的时间戳
    static int S_START_SEC;                             //开始秒数(指的是单个体力的秒 不能大于 60)
    static bool S_IS_NEED_REST_TIME;                    //是否需要重置计时器
    static bool S_IS_NEED_ADJUST;                       //是否需要矫正
    
private:
    map<int,CCProgressTimer*> m_enduranceMap;
    HSTimerLabel* m_pTimeLabel;
    CCLabelTTF* m_pMaxLabel;
    int m_enduranceCount;
};




#endif /* defined(__HSShowEndurance_H__) */





