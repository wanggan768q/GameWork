#include "HSGameAdvancedPairLayer.h"
#include "HSGameSceneJumpManage.h"
HSGameAdvancedPairLayer::HSGameAdvancedPairLayer(void)
{

}

HSGameAdvancedPairLayer::~HSGameAdvancedPairLayer(void)
{

}

bool HSGameAdvancedPairLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
	Load();
	//this->setIsTouchEnabled(true);

	//this->setIsKeypadEnabled(true);

	return true;
}

void HSGameAdvancedPairLayer::Load()
{
	HSReadUI::ShareReadUI()->ReadUI("Image/pair/advancedPair/advancedPair.data","Image/pair/advancedPair/",this);
	HS_SET_MENU_TARGET("UI_fh_01",this,HSGameAdvancedPairLayer::CallReturn);
}

void HSGameAdvancedPairLayer::CallReturn(CCObject* obj)
{
	HS_GO_SCENE(HS_SCENE_GameMainScene);
}

void HSGameAdvancedPairLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSGameAdvancedPairLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSGameAdvancedPairLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameAdvancedPairLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameAdvancedPairLayer::keyBackClicked()
{

}
void HSGameAdvancedPairLayer::keyMenuClicked()
{

}


