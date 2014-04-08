#include "HSEffect_BlackInk.h"
HSEffect_BlackInkLayer::HSEffect_BlackInkLayer(void)
{
}

HSEffect_BlackInkLayer::~HSEffect_BlackInkLayer(void)
{
}

bool HSEffect_BlackInkLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
	Load();
	this->setTouchEnabled(true);

	//this->setIsKeypadEnabled(true);

	return true;
}

void HSEffect_BlackInkLayer::Load()
{
	m_spx = SPX_Manager::CreateSprite("SPX/maomaomozhi.sprite");
	m_spx->setPosition(HSBase::GetTemplateScreenCentre());
	m_spx->setVisible(true);
	//m_spx->SetAction(0,0);
	this->addChild(m_spx);
	m_spx->SetAction(0,1,this,callfuncND_selector(HSEffect_BlackInkLayer::Remove),NULL);
	CCDirector::sharedDirector()->getRunningScene()->addChild(this,10000);
}

void HSEffect_BlackInkLayer::Remove(CCNode* spxNode,void* pData)
{
	CCDirector::sharedDirector()->getRunningScene()->removeChild(this,true);
}

void HSEffect_BlackInkLayer::registerWithTouchDispatcher()
{
	/**
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);*/
}

bool HSEffect_BlackInkLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(this->isVisible())
	{
		return true;
	}
	return false;
}

void HSEffect_BlackInkLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSEffect_BlackInkLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSEffect_BlackInkLayer::keyBackClicked()
{

}
void HSEffect_BlackInkLayer::keyMenuClicked()
{

}
