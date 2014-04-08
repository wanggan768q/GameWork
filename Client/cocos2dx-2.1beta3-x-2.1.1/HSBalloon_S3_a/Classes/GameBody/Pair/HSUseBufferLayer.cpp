#include "HSUseBufferLayer.h"
HSUseBufferLayer::HSUseBufferLayer(void)
{
}

HSUseBufferLayer::~HSUseBufferLayer(void)
{
}

bool HSUseBufferLayer::init()
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

void HSUseBufferLayer::Load()
{
	//HSReadUI::ShareReadUI()->ReadUI("Image/pair/useBuffer/useBuffer.data","Image/pair/useBuffer/",this);
	//HS_SET_MENU_TARGET("UI_Guanbianniu_01",this,HSUseBufferLayer::Close);
}

void HSUseBufferLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSUseBufferLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(this->isVisible())
	{
		return true;
	}
	return false;
}

void HSUseBufferLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSUseBufferLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSUseBufferLayer::keyBackClicked()
{

}
void HSUseBufferLayer::keyMenuClicked()
{

}


