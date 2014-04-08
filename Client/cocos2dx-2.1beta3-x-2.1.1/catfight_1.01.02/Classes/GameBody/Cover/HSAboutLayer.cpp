#include "HSAboutLayer.h"
#include "HSJava.h"
static HSAboutLayer* s_hsAboutLayer = NULL;
HSAboutLayer::HSAboutLayer()
{

}

HSAboutLayer::~HSAboutLayer()
{
	CC_SAFE_RELEASE_NULL(s_hsAboutLayer);
}

bool HSAboutLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
	Load();
	this->setTouchEnabled(true);

	//this->setKeypadEnabled(true);

	return true;
}

HSAboutLayer* HSAboutLayer::ShareHSAboutLayer()
{
	CCLog("ShareHSAboutLayer");
	if(!s_hsAboutLayer)
	{
		s_hsAboutLayer = HSAboutLayer::create();
		s_hsAboutLayer->retain();
	}

	return s_hsAboutLayer;
}

void HSAboutLayer::Load()
{
	CCSprite* m_p_background = HSCCSprite::create("Image/Guanyubeijing.png");

	m_p_background->setPosition(ccp(HSBase::GetTemplateScreenW() / 2.f-1.f,HSBase::GetTemplateScreenH() / 2.f));

	this->addChild(m_p_background);

	HSTool::SetNodeFilldScreen(m_p_background);


	HSReadUI::ShareReadUI()->ReadUI("Image/HSAbout.data","Image/",this);
	HS_SET_MENU_TARGET("UI_Fanhuianniu",this,HSAboutLayer::CallReturn_About);

	if(HSJava::ShaderJava()->GetChannel() == 10004)//联通
	{
		HS_SET_MENU_TARGET("UI_Gengduoyouxi",this,HSAboutLayer::CallMore_About);
	}
	else
	{
		CCNode* pMore = HS_FIND_UI_MENU("UI_Gengduoyouxi");
		pMore->setVisible(false);
	}
}

void HSAboutLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSAboutLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSAboutLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSAboutLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSAboutLayer::keyBackClicked()
{

}
void HSAboutLayer::keyMenuClicked()
{

}

void HSAboutLayer::setVisible(bool visible)
{
	#define HS_About_tag  0x75701
	if(visible)
	{
		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();

		if (!pScene->getChildByTag(HS_About_tag))
		{
			pScene->addChild(this,100,HS_About_tag);
		}
	}
	else
	{
		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
		if (pScene->getChildByTag(HS_About_tag))
		{
			pScene->removeChildByTag(HS_About_tag);
		}
	}
}

void HSAboutLayer::CallReturn_About()
{
	this->setVisible(false);
}

void HSAboutLayer::CallMore_About()
{
	HSJava::ShaderJava()->OpenURL("http://game.wo.com.cn");
}

