/********************************************************************
 *  Copyright(C) 2014 Ambition ( All rights reserved. )
 *	Created:	2014/03/03   10:50
 *	File base:	HSTimerLabel.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSTimerLabel_H__
#define __HSTimerLabel_H__
#pragma once

#include "HSTime.h"
#include "HSMath.h"

/*
 g_Label = HSTimerLabel::create(60);
 g_Label->setPosition(HSBase::GetTemplateScreenCentre());
 g_Label->SetPlansFinshSelector(this, callfunc_selector(HSGameMainLayer::Test_01));
 g_Label->SetPerSecondSelector(this, callfunc_selector(HSGameMainLayer::Test_02));
 this->addChild(g_Label,99999999999);
 
 g_test = CCProgressTimer::create(HSCCSprite::create("Image/test.png"));;
 g_test->setType(kCCProgressTimerTypeBar);
 g_test->setPosition(ccp(320,400));
 g_test->setMidpoint(ccp(0.5,0));
 g_test->setBarChangeRate(ccp(0,1));
 
 this->addChild(g_test,99999999999);
 */
class HSTimerLabel : public CCLabelTTF
{
public:
    HSTimerLabel();
    ~HSTimerLabel();
public:
    
    static HSTimerLabel* create(unsigned long long startTime,int startSec,int defaultSecond);
    
    static HSTimerLabel* create(unsigned long long startTime,int startSec,int defaultSecond,const char *fontName,int fontSize);
    
    bool init(unsigned long long startTime,int defaultSecond,int startSec,const char *fontName,int fontSize);
    
    void SetSecond(int second);
    
    void SetDefaultSecond(int defaultSecond);
    
    void Reset();
    
    const int& GetDefaultSecond();
    
    int GetCurrentSecond();
    
    unsigned long long GetCurrentTime();
    
    float GetPastTimeRatio();
    
    const char* GetTimeToString();
    
    void Updata(float dt);
    
    
    virtual void SetPlansFinshSelector(CCObject* rec,SEL_CallFunc selector);
    
    virtual void SetPerSecondSelector(CCObject* rec,SEL_CallFunc selector);
    
    virtual void SetDestroySelector(CCObject* rec,SEL_CallFunc selector);
private:
    void Format(int second);
    
private:
    int m_defaultSecond,m_second,m_lastSecond;
    
    int m_H,m_M,m_S; //时 分 秒
    
    unsigned long long m_time;
    
    CCObject* m_PlansFinshSelectorRec;
    SEL_CallFunc m_PlansFinshSelector;
    
    CCObject* m_PerSecondSelectorRec;
    SEL_CallFunc m_PerSecondSelector;
    
    CCObject* m_DestroySelectorRec;
    SEL_CallFunc m_DestroySelector;
    
};

#endif /* defined(__HSTimerLabel_H__) */
