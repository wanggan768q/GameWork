#include "HSLoadingLayer.h"

static HSLoadingLayer* s_HSLoadingLayer = NULL;

HSLoadingLayer::HSLoadingLayer(void)
{
    m_pSpxLoading = NULL;
	m_pProgressTimeer = NULL;
	m_pTipsTTF = NULL;
	m_pTipsTTFUp = NULL;
	m_pTipsUp = NULL;
	m_time = 30;
}

HSLoadingLayer::~HSLoadingLayer(void)
{
	//CC_SAFE_RELEASE_NULL(s_HSLoadingLayer);
}

bool HSLoadingLayer::init()
{
	if (!CCLayer::init())
    {
		return false;
	}
	HSTool::SetLayerScale(this);
	Load();
	this->setTouchEnabled(true);
	return true;
}

void HSLoadingLayer::Load()
{
	CCLayerColor* pMaskLayer = CCLayerColor::create(ccc4(0, 0, 0, 200),
                                                    HSBase::GetTemplateScreenW() + 10.f, HSBase::GetTemplateScreenH());
	pMaskLayer->setAnchorPoint(HS_ANCHOR_CENTER);
	this->addChild(pMaskLayer);
    pMaskLayer->setPosition(ccp(-2.f,0));
    HSToolBase::SetNodeFilldScreen(pMaskLayer);
    
	//	void *bigmem=malloc(1048576*5);
    /**
	CCSprite* pLoadingSprite = HSCCSprite::create("Image/LODADING.png");
	pLoadingSprite->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pLoadingSprite);*/
    
	/**
	CCSprite* pMaskSprite = HSCCSprite::create("Image/LODADINGzhezhao.png");
	pMaskSprite->setOpacity(255 - 153);
    
	m_pProgressTimeer = CCProgressTimer::create(pMaskSprite);
	m_pProgressTimeer->setType(kCCProgressTimerTypeBar);
	m_pProgressTimeer->setMidpoint(ccp(0,0));
	m_pProgressTimeer->setBarChangeRate(ccp(1, 0));
	m_pProgressTimeer->setPosition(pLoadingSprite->getPosition());
	this->addChild(m_pProgressTimeer);
	m_pProgressTimeer->setReverseProgress(true);
    */
	if (1)
    {

		m_pTipsTTFUp = CCLabelTTF::create("",HS_FONT_HuaKang, 38.f, CCSizeMake(500,960),
		                                        kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
		m_pTipsTTFUp->setPosition(ccp(320.f,800.f));

		this->addChild(m_pTipsTTFUp);

		CCString* pTipsStr = CCString::createWithFormat("tips_%d",
                                                        HSMath::Random(0, 19));

		m_pTipsTTF = CCLabelTTF::create(L(pTipsStr->getCString()),
                                        HS_FONT_HuaKang, 32.f, CCSizeMake(500,960),
                                        kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
		//m_pTipsTTF->setPosition(HSBase::GetTemplateScreenCentre());
		m_pTipsTTF->setPosition(
                                /*ccp(HSBase::GetTemplateScreenW() / 2.f,pLoadingSprite->getContentSize().height)*/ccp(320.f,180.f));
		this->addChild(m_pTipsTTF);

		//m_pTipsTTF->getString();
	}
    
//	m_backSprite = HSCCSprite::create("Image/lodingback.png");
//	m_backSprite->setPosition(ccp(320.f,340.f));
//	this->addChild(m_backSprite);
    m_pSpxLoading = SPX_Manager::CreateSprite("SPX/cat.sprite");
    m_pSpxLoading->setPosition(ccp(320.f,306.f));
    m_pSpxLoading->SetAction(0);
    this->addChild(m_pSpxLoading);
    
    this->setVisible(false);
}

void HSLoadingLayer::SetTipsUp(const char* tipsUp)
{
	this->m_pTipsUp = tipsUp;
}

void HSLoadingLayer::SetTime(int time)
{
	this->m_time = time;
}

void HSLoadingLayer::Updata(float dt) {
	if (!isVisible()) {
		return;
	}

	if(m_pTipsUp!=NULL)
	{
		if(!(m_pTipsTTFUp->getString()==m_pTipsUp))
		{
			m_pTipsTTFUp->setString(m_pTipsUp);
		}
	}

	if (m_time == 0) {
		setVisible(false);
	} else {
		m_time -= 1;
	}
}

HSLoadingLayer* HSLoadingLayer::ShareLoading()
{
	if (!s_HSLoadingLayer)
    {
		s_HSLoadingLayer = HSLoadingLayer::create();
		s_HSLoadingLayer->retain();
	}
    
	return s_HSLoadingLayer;
}

void HSLoadingLayer::setVisible(bool visible)
{
#define HS_Loadong_Tag 0x75698
    
	if (visible)
    {
        if(!this->isVisible())
        {
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            if (pScene && !pScene->getChildByTag(HS_Loadong_Tag))
            {
                this->schedule(schedule_selector(HSLoadingLayer::Updata), 1.f);
                m_time = 15;
                pScene->addChild(this, HS_Loadong_Tag, HS_Loadong_Tag);
            }
        }
	}
	else
	{
		this->SetTipsUp("");
		this->m_pTipsTTFUp->setString("");
        this->removeFromParent();
        
	}
	CCLayer::setVisible(visible);
}

void HSLoadingLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool HSLoadingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isVisible()) {
		return false;
	}
	return true;
}

void HSLoadingLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void HSLoadingLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void HSLoadingLayer::keyBackClicked()
{
    
}

void HSLoadingLayer::keyMenuClicked()
{
    
}
