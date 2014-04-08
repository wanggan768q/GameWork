#include "HSLoadingLayer.h"

static HSLoadingLayer* s_HSLoadingLayer = NULL;

HSLoadingLayer::HSLoadingLayer(void)
{
	m_intervalTime = 0.1f;
}


HSLoadingLayer::~HSLoadingLayer(void)
{
	this->removeAllChildren();
}

bool HSLoadingLayer::init()
{
	this->initWithColor(ccc4(0,0,0,200),HSBase::GetTemplateScreenW(),HSBase::GetTemplateScreenH());

	CCLabelTTF* ttf = CCLabelTTF::create("Loading......","Font/HuaKang.ttf",25.f,HSBase::GetScreenSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	//CCLabelTTF* ttf = CCLabelTTF::create("Loading.....","",30.f);
	CCPoint pos = HSBase::GetTemplateScreenCentre();
	pos.x -= 80.f;
	ttf->setPosition(pos);
	this->addChild(ttf,1000);
	return true;
}

HSLoadingLayer* HSLoadingLayer::ShareLoading()
{
	if (!s_HSLoadingLayer)
	{
		s_HSLoadingLayer = HSLoadingLayer::create();
	}

	return s_HSLoadingLayer;
}

void HSLoadingLayer::SetIntervalTime( float v )
{
	m_intervalTime = v;
}

void HSLoadingLayer::setVisible( bool visible )
{
	if (visible)
	{
		CCDirector::sharedDirector()->setNotificationNode(this);
		CCDirector::sharedDirector()->drawScene();
	}else{
		CCDirector::sharedDirector()->setNotificationNode(NULL);
	}
	CCLayerColor::setVisible(visible);
	if (!visible)
	{
		this->release();
		s_HSLoadingLayer = NULL;
	}
	
}