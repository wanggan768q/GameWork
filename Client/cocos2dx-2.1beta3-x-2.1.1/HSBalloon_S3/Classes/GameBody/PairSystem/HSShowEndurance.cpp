#include "HSShowEndurance.h"

int HSShowEndurance::S_CURRENT_ENDURANCE_COUNT = 0;                                                             //当前体力个数(指完整桃心)
int HSShowEndurance::S_CURRENT_OPERATION_ENDURANCE_INDEX = HSShowEndurance::S_CURRENT_ENDURANCE_COUNT + 1;      //当前操作的体力(指跟计时器挂钩的桃心)
bool HSShowEndurance::S_IS_NEED_REST_TIME = false;
unsigned long long HSShowEndurance::S_LAST_REMAIN = 0;
int HSShowEndurance::S_START_SEC = 0;
bool HSShowEndurance::S_IS_NEED_ADJUST = false;

HSShowEndurance::HSShowEndurance(void)
{
    m_pTimeLabel = NULL;
    m_enduranceCount = 0;
}

HSShowEndurance::~HSShowEndurance(void)
{
    m_enduranceMap.clear();
}

HSShowEndurance* HSShowEndurance::create()
{
    HSShowEndurance* p = new HSShowEndurance;
    if (p && p->init())
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return NULL;
}

bool HSShowEndurance::init()
{
    for (int i=0; i<HSShowEndurance::S_C_ENDURANCE_COUNT; ++i)
    {
        CCString* pPanel = CCString::createWithFormat("UI_Benfangxinxiban_Naili_%d",i);
        
        HSCCSprite* pSprite = HS_FIND_UI_PANEL_SPRITE(pPanel->getCString(),"Naili_1");
        pSprite->setVisible(false);
        
        CCProgressTimer* pProgress = CCProgressTimer::create(pSprite);
        pProgress->setType(kCCProgressTimerTypeBar);
        pProgress->setPosition(pSprite->getPosition());
        pProgress->setMidpoint(ccp(0.5,0));
        pProgress->setBarChangeRate(ccp(0,1));
        i < HSShowEndurance::S_CURRENT_ENDURANCE_COUNT  ? pProgress->setPercentage(100) : pProgress->setPercentage(0);
        pSprite->getParent()->addChild(pProgress,2000);
        m_enduranceMap.insert(pair<int, CCProgressTimer*>(i + 1,pProgress));
        
        CC_SAFE_RELEASE_NULL(pPanel);
    }
    
    HSCCSprite* pSprite = HS_FIND_UI_PANEL_SPRITE("UI_Benfangxinxiban_Nailijishiqi","Pipeinailidiban");
    
    m_pMaxLabel = CCLabelTTF::create("MAX", HS_FONT_HuaKang, 25, pSprite->getContentSize(), kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
    m_pMaxLabel->setAnchorPoint(HS_ANCHOR_CENTER);
    m_pMaxLabel->setPosition(pSprite->getAnchorPointInPoints());
    m_pMaxLabel->setVisible(false);
    pSprite->addChild(m_pMaxLabel);
    
    this->CreateTimeLabel();
    
    this->schedule(schedule_selector(HSShowEndurance::Updata));
    
	return true;
}

void HSShowEndurance::CreateTimeLabel()
{
    HSCCSprite* pSprite = HS_FIND_UI_PANEL_SPRITE("UI_Benfangxinxiban_Nailijishiqi","Pipeinailidiban");
    CCLog("重新记录：%d",HSShowEndurance::S_START_SEC);
    m_pTimeLabel = HSTimerLabel::create(HSShowEndurance::S_LAST_REMAIN,HSShowEndurance::S_START_SEC,HSShowEndurance::S_C_MAX_SEC );
    m_pTimeLabel->SetPlansFinshSelector(this, callfunc_selector(HSShowEndurance::Call_PlansFinshSelector));
    m_pTimeLabel->SetPerSecondSelector(this, callfunc_selector(HSShowEndurance::Call_PerSecondSelector));
    m_pTimeLabel->SetDestroySelector(this, callfunc_selector(HSShowEndurance::Call_DestroySelector));
    m_pTimeLabel->setPosition(pSprite->getAnchorPointInPoints());
    if(HSShowEndurance::S_CURRENT_ENDURANCE_COUNT < HSShowEndurance::S_C_ENDURANCE_COUNT)
    {
        m_pTimeLabel->setVisible(true);
    }else{
        m_pTimeLabel->setVisible(false);
    }
    
    pSprite->addChild(m_pTimeLabel);
    
    HSShowEndurance::S_START_SEC = 0;
}

void HSShowEndurance::Call_PlansFinshSelector()
{
    CCLog("倒计时一轮完成");
    if(HSShowEndurance::S_CURRENT_ENDURANCE_COUNT < 5)
    {
        //增加体力
        HSShowEndurance::AddEndurance();
    }
}

void HSShowEndurance::Call_PerSecondSelector()
{
    map<int,CCProgressTimer*>::iterator it;
    it = m_enduranceMap.find(HSShowEndurance::S_CURRENT_OPERATION_ENDURANCE_INDEX);
    
    if(it != m_enduranceMap.end())
    {
        it->second->setPercentage(m_pTimeLabel->GetPastTimeRatio() * 100.f);
        
        for (int i = HSShowEndurance::S_CURRENT_OPERATION_ENDURANCE_INDEX - 1; i > 0; --i)
        {
            it = m_enduranceMap.find(i);
            if(it != m_enduranceMap.end())
            {
                it->second->setPercentage(100.f);
            }
        }
        for(int i = HSShowEndurance::S_CURRENT_OPERATION_ENDURANCE_INDEX + 1;i <= HSShowEndurance::S_C_ENDURANCE_COUNT;++i)
        {
            it = m_enduranceMap.find(i);
            if(it != m_enduranceMap.end())
            {
                it->second->setPercentage(0);
            }
        }
    }else{
        HSAssert(false, "操作的体力不存在");
    }
}

void HSShowEndurance::Call_DestroySelector()
{
    HSShowEndurance::S_LAST_REMAIN = 0;
    HSShowEndurance::S_START_SEC = m_pTimeLabel->GetCurrentSecond();
    CCLog("最后记录：%d",HSShowEndurance::S_START_SEC);
}

void HSShowEndurance::AddEndurance()
{
    HSShowEndurance::S_CURRENT_ENDURANCE_COUNT += 1;
    
    if(HSShowEndurance::S_CURRENT_ENDURANCE_COUNT > HSShowEndurance::S_C_ENDURANCE_COUNT)
    {
        HSShowEndurance::S_IS_NEED_REST_TIME = false;
        HSShowEndurance::S_CURRENT_ENDURANCE_COUNT = HSShowEndurance::S_C_ENDURANCE_COUNT;
    }else{
        HSShowEndurance::S_IS_NEED_REST_TIME = true;
    }
    
    HSShowEndurance::S_CURRENT_OPERATION_ENDURANCE_INDEX = HSShowEndurance::S_CURRENT_ENDURANCE_COUNT + 1;
}

void HSShowEndurance::SubEndurance()
{
    HSShowEndurance::S_CURRENT_ENDURANCE_COUNT -= 1;
    
    HSShowEndurance::S_CURRENT_ENDURANCE_COUNT < 0 ? HSShowEndurance::S_CURRENT_ENDURANCE_COUNT = 0 : 0;
    
    HSShowEndurance::S_CURRENT_OPERATION_ENDURANCE_INDEX = HSShowEndurance::S_CURRENT_ENDURANCE_COUNT + 1;
    
    //HSShowEndurance::S_IS_NEED_REST_TIME = true;
}

void HSShowEndurance::Updata(float dt)
{
    //    if(HSShowEndurance::S_IS_NEED_ADJUST)
    //    {
    //        HSShowEndurance::S_IS_NEED_ADJUST = false;
    //        if(m_pTimeLabel)
    //        {
    //            m_pTimeLabel->SetSecond(HSShowEndurance::S_START_SEC);
    //        }
    //    }
    
    if(HSShowEndurance::S_CURRENT_ENDURANCE_COUNT > HSShowEndurance::S_C_ENDURANCE_COUNT)
    {
        m_pTimeLabel->setVisible(false);
        if(m_enduranceCount != HSShowEndurance::S_CURRENT_ENDURANCE_COUNT)
        {
            m_enduranceCount = HSShowEndurance::S_CURRENT_ENDURANCE_COUNT;
            
            //            for_each(m_enduranceMap.begin(), m_enduranceMap.end(), [](pair<int,CCProgressTimer*> it)
            //                     {
            //                         it.second->setPercentage(100);
            //                     });
            if(m_enduranceCount - 5 == 0)
            {
                m_pMaxLabel->setString("MAX");
                m_pMaxLabel->setVisible(true);
            }else{
                CCString* pStr = CCString::createWithFormat("+%d",m_enduranceCount - 5);
                m_pMaxLabel->setString(pStr->getCString());
                m_pMaxLabel->setVisible(true);
                CC_SAFE_RELEASE_NULL(pStr);
            }
        }
        return;
    }
    
    if(HSShowEndurance::S_CURRENT_ENDURANCE_COUNT == HSShowEndurance::S_C_ENDURANCE_COUNT)
    {
        //CCLog("体力满了");
        if(m_pTimeLabel->isVisible())
        {
            m_pTimeLabel->setVisible(false);
            m_pTimeLabel->Reset();
            m_pMaxLabel->setString("MAX");
            
        }
        
        //并且 切换成 MAX
        m_pMaxLabel->setVisible(true);
    }else{
        if(HSShowEndurance::S_IS_NEED_REST_TIME == true)
        {
            HSShowEndurance::S_IS_NEED_REST_TIME = false;
            
            m_pMaxLabel->setString("MAX");
            //取消 MAX
            m_pMaxLabel->setVisible(false);
            
            m_pTimeLabel->setVisible(true);
            m_pTimeLabel->Reset();
        }
        
    }
}















