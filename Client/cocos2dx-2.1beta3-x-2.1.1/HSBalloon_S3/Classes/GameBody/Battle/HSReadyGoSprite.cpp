#include "HSReadyGoSprite.h"
#include "HSGameCache.h"

HSReadyGoSprite::HSReadyGoSprite(void)
{
    m_ps = m_pt = m_psShadow = m_ptShadow = m_pvs = NULL;
}

HSReadyGoSprite::~HSReadyGoSprite(void)
{
}

HSReadyGoSprite* HSReadyGoSprite::create()
{
    HSReadyGoSprite* p = new HSReadyGoSprite;
    if (p && p->init())
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_DELETE(p);
    return NULL;
}

bool HSReadyGoSprite::init()
{
    CCString* sFileName = CCString::createWithFormat("Image/%d_START.png",HS_TARGET_SELF().figureid());
    CCString* tFileName = CCString::createWithFormat("Image/%d_T_START.png",HS_TARGET_TARGET().figureid());
    
    m_psShadow = HSCCSprite::create("Image/Tongyongyingzi_0.png");
    m_ptShadow = HSCCSprite::create("Image/Tongyongyingzi_1.png");
    m_psShadow->setPosition(ccp(-152,330));
    m_ptShadow->setPosition(ccp(640,461));
    this->addChild(m_psShadow);
    this->addChild(m_ptShadow);
    
    m_ps = HSCCSprite::create(sFileName->getCString());
    m_pt = HSCCSprite::create(tFileName->getCString());
    m_ps->setAnchorPoint(HS_ANCHOR_D_CENTER);
    m_pt->setAnchorPoint(HS_ANCHOR_D_CENTER);
    m_ps->setPosition(ccp(-148,308));
    m_pt->setPosition(ccp(640,447));
    this->addChild(m_ps);
    this->addChild(m_pt);
    
    m_ps->setOpacity(0);
    m_pt->setOpacity(0);
    m_psShadow->setOpacity(0);
    m_ptShadow->setOpacity(0);
    
    m_pvs = HSCCSprite::create("Image/PipeiVS.png");
    m_pvs->setPosition(ccp(300,443));
    m_pvs->setScale(0);
    this->addChild(m_pvs);
    
    this->scheduleOnce(schedule_selector(HSReadyGoSprite::FirstRun), 0);
    
    return true;
}

void HSReadyGoSprite::FirstRun(float dt)
{
    CCLayerColor* pMaskLayer = CCLayerColor::create(ccc4(0, 0, 0, 200),
                                                    HSBase::GetTemplateScreenW() + 10.f, HSBase::GetTemplateScreenH());
	pMaskLayer->setAnchorPoint(HS_ANCHOR_CENTER);
	this->getParent()->addChild(pMaskLayer,2500,2500);
    pMaskLayer->setPosition(ccp(-2.f,0));
    HSToolBase::SetNodeFilldScreen(pMaskLayer);
    
    
    CCMoveTo* psMove = CCMoveTo::create(0.5, ccp(148,308));
    CCMoveTo* tsMove = CCMoveTo::create(0.5, ccp(500,447));
    CCMoveTo* psShadowMove = CCMoveTo::create(0.5, ccp(144,330));
    CCMoveTo* ptShadowMove = CCMoveTo::create(0.5, ccp(500,461));
    
    CCFadeIn* a1 = CCFadeIn::create(0.2);
    CCFadeIn* a2 = CCFadeIn::create(0.2);
    CCFadeIn* a3 = CCFadeIn::create(0.2);
    CCFadeIn* a4 = CCFadeIn::create(0.2);
    
    CCSpawn* s1 = CCSpawn::create(psMove,a1,NULL);
    CCSpawn* s2 = CCSpawn::create(tsMove,a2,NULL);
    CCSpawn* s3 = CCSpawn::create(psShadowMove,a3,NULL);
    CCSpawn* s4 = CCSpawn::create(ptShadowMove,a4,NULL);
    
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(HSReadyGoSprite::Call_01));
    CCSequence* pSeq = CCSequence::create(s4,call,NULL);
    
    m_ps->runAction(s1);
    m_pt->runAction(s2);
    m_psShadow->runAction(s3);
    m_ptShadow->runAction(pSeq);
    
}

void HSReadyGoSprite::Call_01()
{
    CCScaleTo* a1 = CCScaleTo::create(0.3, 1);
    CCDelayTime* a2 = CCDelayTime::create(0.5);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(HSReadyGoSprite::Call_02));
    CCSequence* pSeq = CCSequence::create(a1,a2,call,NULL);
    m_pvs->runAction(pSeq);
}

void HSReadyGoSprite::Call_02()
{
    CCScaleTo* a1 = CCScaleTo::create(0.1, 1.1,0.8);
    CCScaleTo* a2 = CCScaleTo::create(0.1, 1.1,0.8);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(HSReadyGoSprite::Call_03));
    CCSequence* pSeq = CCSequence::create(a2,call,NULL);
    
    m_ps->runAction(a1);
    m_pt->runAction(pSeq);
}

void HSReadyGoSprite::Call_03()
{
    CCMoveTo* a1 = CCMoveTo::create(0.025, ccp(144,308));
    CCMoveTo* a2 = CCMoveTo::create(0.025, ccp(498,447));
    
    CCMoveTo* a3 = CCMoveTo::create(0.025, ccp(152,308));
    CCMoveTo* a4 = CCMoveTo::create(0.025, ccp(502,447));
    
    CCMoveTo* a5 = CCMoveTo::create(0.025, ccp(144,308));
    CCMoveTo* a6 = CCMoveTo::create(0.025, ccp(498,447));
    
    CCMoveTo* a7 = CCMoveTo::create(0.025, ccp(152,308));
    CCMoveTo* a8 = CCMoveTo::create(0.025, ccp(502,447));
    
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(HSReadyGoSprite::Call_04));
    CCSequence* pSeq1 = CCSequence::create(a1,a3,a5,a7,NULL);
    CCSequence* pSeq2 = CCSequence::create(a2,a4,a6,a8,call,NULL);
    
    m_ps->runAction(pSeq1);
    m_pt->runAction(pSeq2);
}

void HSReadyGoSprite::Call_04()
{
    CCMoveTo* a1 = CCMoveTo::create(0.5, ccp(152,1500));
    CCMoveTo* a2 = CCMoveTo::create(0.5, ccp(502,1500));
    
    CCFadeOut* a3 = CCFadeOut::create(0.5);
    CCFadeOut* a4 = CCFadeOut::create(0.5);
    
    CCScaleTo* a5 = CCScaleTo::create(0.2, 0.7,1.5);
    CCScaleTo* a6 = CCScaleTo::create(0.2, 0.7,1.5);
    
    CCSpawn* b1 = CCSpawn::create(a1,a3,a5,NULL);
    CCSpawn* b2 = CCSpawn::create(a2,a4,a6,NULL);
   
    m_ps->runAction(b1);
    m_pt->runAction(b2);
    
    
    CCScaleTo* c1 = CCScaleTo::create(0.5, 0);
    CCScaleTo* c2 = CCScaleTo::create(0.5, 0);
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(HSReadyGoSprite::Call_05));
    
    CCSequence* pSeq1 = CCSequence::create(c2,call,NULL);
    m_psShadow->runAction(c1);
    m_ptShadow->runAction(pSeq1);
}

void HSReadyGoSprite::Call_05()
{
    CCFadeOut* a1 = CCFadeOut::create(0.2);
    CCScaleTo* a2 = CCScaleTo::create(0.2, 3);
    CCSpawn* s1 = CCSpawn::create(a1,a2,NULL);
    
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(HSReadyGoSprite::Call_06));
    
    CCSequence* pSeq1 = CCSequence::create(s1,call,NULL);
    m_pvs->runAction(pSeq1);
}

void HSReadyGoSprite::Call_06()
{
    CCNode* p = this->getParent()->getChildByTag(2500);
    if(p)
    {
        p->removeFromParent();
    }
    
    this->removeFromParent();
    
}
















