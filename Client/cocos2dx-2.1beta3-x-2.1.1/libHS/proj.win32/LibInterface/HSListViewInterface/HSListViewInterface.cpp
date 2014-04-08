#include "HSListViewInterface.h"

HS_namespace_HSListViewControl_Begin

HSListViewInterface::HSListViewInterface(const CCSize& frameSize,const CCSize& itemSize,int onceCount):HSItemDataInterface(itemSize,onceCount)
{
	this->initWithViewSize(frameSize);
	this->setDataSource(this);
	this->setDirection(kCCScrollViewDirectionVertical);
	this->setDelegate(this);
	this->setVerticalFillOrder(kCCTableViewFillTopDown);
}


HSListViewInterface::~HSListViewInterface(void)
{
}

void HSListViewInterface::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

HS_namespace_HSListViewControl_End