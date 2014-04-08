#include "HSLogoScene.h"
#include "HSJava.h"


HSLogoLayer::HSLogoLayer()
{

}

HSLogoLayer::~HSLogoLayer()
{

}

bool HSLogoLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	//HSTool::SetLayerScale(this);
	Load();
	//this->setTouchEnabled(true);
	return true;
	//return true;
}

void HSLogoLayer::Load()
{
	 if(HSJava::ShaderJava()->GetChannel() == 10004)//联通
	 {
			CCSprite* logo = HSCCSprite::create("Image/LOGO.png");
			logo->setPosition(HSBase::GetTemplateScreenCentre());
			this->addChild(logo);
	 }
	 else
	 {
		 CCSprite* m_p_backgournd = HSCCSprite::create("Image/LOGO.png");
		 m_p_backgournd->setPosition(ccp(HSBase::GetScreenWidth() / 2.f-1.f,HSBase::GetScreenHeight() / 2.f));
		 HSTool::SetNodeFilldScreen(m_p_backgournd);
		 this->addChild(m_p_backgournd);
	 }
}

void HSLogoLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSLogoLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSLogoLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSLogoLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSLogoLayer::keyBackClicked()
{

}
void HSLogoLayer::keyMenuClicked()
{

}


HSLogoScene::HSLogoScene()
{
	hsLogoLayer = NULL;
}

HSLogoScene::~HSLogoScene()
{

}

bool HSLogoScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->hsLogoLayer = HSLogoLayer::create();

	this->addChild(this->hsLogoLayer,HS_BASE_TAG,HS_BASE_TAG);

	return true;
}
