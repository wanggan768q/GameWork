//
//  HSTimerLabel.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 14-3-3.
//
//

#include "HSTimerLabel.h"


HSTimerLabel::HSTimerLabel()
{
    m_time = 0;
    m_H = m_M = m_S = 0;
    
    m_PlansFinshSelectorRec = NULL;
    m_PlansFinshSelector = NULL;
    
    m_PerSecondSelectorRec = NULL;
    m_PerSecondSelector = NULL;
    
    m_DestroySelectorRec = NULL;
    m_DestroySelector = NULL;
    
    m_second = 0;
    m_defaultSecond = 1;
}

HSTimerLabel::~HSTimerLabel()
{
//    if(m_DestroySelectorRec)
//    {
//        (this->m_DestroySelectorRec->*m_DestroySelector)();
//    }
}

HSTimerLabel* HSTimerLabel::create(unsigned long long startTime,int startSec,int defaultSecond)
{
    HSTimerLabel* p = new HSTimerLabel;
    if (p && p->init(startTime,startSec,defaultSecond,"Arial",25))
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    
    return NULL;
}

HSTimerLabel* HSTimerLabel::create(unsigned long long startTime,int startSec,int defaultSecond,const char *fontName,int fontSize)
{
    HSTimerLabel* p = new HSTimerLabel;
    if (p && p->init(startTime,startSec,defaultSecond,fontName,fontSize))
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    
    return NULL;
}

bool HSTimerLabel::init(unsigned long long startTime,int startSec,int defaultSecond,const char *fontName,int fontSize)
{
    m_time = startTime;
    startSec == 0 ? startSec = defaultSecond : 0;
    this->SetDefaultSecond(defaultSecond);
    this->SetSecond(startSec);
    
    this->Format(startSec);
    
    bool isOK = this->initWithString(this->GetTimeToString(), fontName, fontSize, CCSizeZero, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    
    this->schedule(schedule_selector(HSTimerLabel::Updata));
    
    return isOK;
}

void HSTimerLabel::SetSecond(int second)
{
    m_second = second;
    m_lastSecond = 0;
}

void HSTimerLabel::SetDefaultSecond(int defaultSecond)
{
    m_defaultSecond = defaultSecond;
}

void HSTimerLabel::Reset()
{
    m_time = 0;
    
    this->SetSecond(m_defaultSecond);
}

const int& HSTimerLabel::GetDefaultSecond()
{
    return m_defaultSecond;
}

int HSTimerLabel::GetCurrentSecond()
{
    return m_second;
}

unsigned long long HSTimerLabel::GetCurrentTime()
{
    return m_time;
}

float HSTimerLabel::GetPastTimeRatio()
{
    float ratio = 1;
    if(m_defaultSecond > 0)
    {
        ratio = (float)(m_defaultSecond - m_second) / (float)m_defaultSecond;
    }
    return ratio;
}

const char* HSTimerLabel::GetTimeToString()
{
    CCString* pStr = CCString::createWithFormat("%02d:%02d",m_M,m_S);
    return pStr->getCString();
}

void HSTimerLabel::Updata(float dt)
{
    if(!isVisible())
        return;
    
    unsigned long long curTime = HSTime::GetLocalityTimeAccurate() / 1000;
    if(m_time == 0)
    {
        m_time = curTime;
    }else{
        if(m_time < curTime)
        {
            int diff = curTime - m_time;
            m_time = curTime;
            
            if(m_second > 0)
            {
                m_second -= diff;
                
                this->Format(m_second);
                
                if(m_lastSecond != m_second)
                {
                    this->setString(this->GetTimeToString());
                    
                    //每秒的操作
                    if(m_PerSecondSelectorRec)
                    {
                        (this->m_PerSecondSelectorRec->*m_PerSecondSelector)();
                    }
                    m_lastSecond = m_second;
                }
                
                //计划完成之后的操作
                if(m_second <= 0)
                {
                    //m_second = m_defaultSecond;   //重新开始 测试用
                    
                    int count = HSMath::Abs(m_second) / m_defaultSecond;
                    
                    do {
                        if(m_PlansFinshSelectorRec != NULL)
                        {
                            (this->m_PlansFinshSelectorRec->*m_PlansFinshSelector)();
                        }
                        --count;
                    } while (count >= 0);
                    
                }
            }
        }
    }
}

void HSTimerLabel::SetPlansFinshSelector(CCObject* rec,SEL_CallFunc selector)
{
    m_PlansFinshSelectorRec = rec;
    m_PlansFinshSelector = selector;
}

void HSTimerLabel::SetPerSecondSelector(CCObject* rec,SEL_CallFunc selector)
{
    m_PerSecondSelectorRec = rec;
    m_PerSecondSelector = selector;
}

void HSTimerLabel::SetDestroySelector(CCObject* rec,SEL_CallFunc selector)
{
    m_DestroySelectorRec = rec;
    m_DestroySelector = selector;
}

void HSTimerLabel::Format(int second)
{
    m_H = second / 60 / 60;
    m_M = second / 60  - m_H * 60;
    m_S = second - m_M * 60  - m_H * 60;
    
    m_H < 0 ? m_H = 0 : 0;
    m_M < 0 ? m_M = 0 : 0;
    m_S < 0 ? m_S = 0 : 0;
    
    
    CCLog(GetTimeToString());
}
