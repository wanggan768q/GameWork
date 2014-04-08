#include "HSPropFastTrackInterface.h"
#include "HSBattleScene.h"
#include "HSJava.h"

HSPropFastTrackInterface::HSPropFastTrackInterface(void)
{
    m_time = 3;
}

HSPropFastTrackInterface::~HSPropFastTrackInterface(void)
{
}

CCNode* HSPropFastTrackInterface::GetDialog()
{
    CCNode* pFrame = HSCCSprite::create("Image/Wave_inf.png");
    pFrame->setPosition(ccp(329,681));
    m_pTime = CCLabelAtlas::create("3", "Image/Daojishi.png", 138 / 3, 54, '1');
    m_pTime->setPosition(ccp(398,51));
    pFrame->addChild(m_pTime);
    
    this->schedule(schedule_selector(HSPropFastTrackInterface::UpdataTime) , 1);
    
    return pFrame;
}

void HSPropFastTrackInterface::Call_Sure(CCObject* obj)
{
    //计费点
    this->Buy(200);
    
    Function();
    
    this->Destroy();
}

void HSPropFastTrackInterface::Buy(int gold)
{
    HSJava::ShaderJava()->Pay(200);
}

void HSPropFastTrackInterface::Destroy()
{
    this->setVisible(false);
    this->unscheduleAllSelectors();
    this->removeFromParent();
    
    HSBattleLayer* pBattleLayer = HS_GET_BattleLayer();

    if(pBattleLayer)
    {
        pBattleLayer->SetPropWave(NULL);
    }
}

void HSPropFastTrackInterface::UpdataTime(float dt)
{
    if(m_time == 1)
    {
        this->Destroy();
        HSBattleLayer* pBattleLayer = HS_GET_BattleLayer();
        if(pBattleLayer)
        {
            pBattleLayer->SetPropWave(NULL);
        }
        return;
    }else{
        CCString* time = CCString::createWithFormat("%d",--m_time);
        m_pTime->setString(time->getCString());
    }
    
}