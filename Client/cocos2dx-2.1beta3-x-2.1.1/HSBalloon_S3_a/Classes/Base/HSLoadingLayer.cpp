#include "HSLoadingLayer.h"

static HSLoadingLayer* s_HSLoadingLayer = NULL;

HSLoadingLayer::HSLoadingLayer(void)
{
	m_pProgressTimeer = NULL;
	m_pTipsTTF = NULL;
}

HSLoadingLayer::~HSLoadingLayer(void)
{
	CC_SAFE_RELEASE_NULL(s_HSLoadingLayer);
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
	CCLayerColor* pMaskLayer = CCLayerColor::create(ccc4(0,0,0,200),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());
	pMaskLayer->setAnchorPoint(HS_ANCHOR_CENTER);
	HSToolBase::SetNodeFilldScreen(pMaskLayer);
	this->addChild(pMaskLayer);

	CCSprite* pLoadingSprite = CCSprite::create("Image/LODADING.png");
	//pLoadingSprite->setPosition(ccp(HSBase::GetTemplateScreenW() / 2.f,pLoadingSprite->getContentSize().height));
	pLoadingSprite->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pLoadingSprite);

	CCSprite* pMaskSprite = CCSprite::create("Image/LODADINGzhezhao.png");
	pMaskSprite->setOpacity(255-153);

	m_pProgressTimeer = CCProgressTimer::create(pMaskSprite);
	m_pProgressTimeer->setType(kCCProgressTimerTypeBar);
	m_pProgressTimeer->setMidpoint(ccp(0,0));
	m_pProgressTimeer->setBarChangeRate(ccp(1, 0));
	m_pProgressTimeer->setPosition(pLoadingSprite->getPosition());
	this->addChild(m_pProgressTimeer);
	m_pProgressTimeer->setReverseProgress(true);
	

	CCString* pTipsStr = CCString::createWithFormat("tips_%d",HSMath::Random(0,19));
	m_pTipsTTF = CCLabelTTF::create(L(pTipsStr->getCString()),HS_FONT_HuaKang,30.f,CCSizeMake(500,960),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	//m_pTipsTTF->setPosition(HSBase::GetTemplateScreenCentre());
	m_pTipsTTF->setPosition(ccp(HSBase::GetTemplateScreenW() / 2.f,pLoadingSprite->getContentSize().height));
	this->addChild(m_pTipsTTF);
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

void HSLoadingLayer::setVisible( bool visible )
{
	#define HS_Loadong_Tag 0x75698

	CCLayer::setVisible(visible);

	if (visible)
	{
		CCProgressFromTo* pFromTo = CCProgressFromTo::create(15.f,0,100);
		CCRepeatForever* pForever = CCRepeatForever::create(pFromTo);
		m_pProgressTimeer->runAction(pForever);

		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
		if (!pScene->getChildByTag(HS_Loadong_Tag))
		{
			pScene->addChild(this,HS_Loadong_Tag,HS_Loadong_Tag);
		}	
	}
	else
	{
		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
		if (pScene->getChildByTag(HS_Loadong_Tag))
		{
			pScene->removeChildByTag(HS_Loadong_Tag);
		}
	}
}

void HSLoadingLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSLoadingLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (!isVisible())
	{
		return false;
	}
	return true;
}

void HSLoadingLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSLoadingLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSLoadingLayer::keyBackClicked()
{

}

void HSLoadingLayer::keyMenuClicked()
{

}
