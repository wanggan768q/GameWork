#include "HSEffect_ColorfulCandy.h"
int HSEffect_ColorfulCandyLayer::CandyCount = 35;
HSEffect_ColorfulCandyLayer::HSEffect_ColorfulCandyLayer(void)
{

}

HSEffect_ColorfulCandyLayer::~HSEffect_ColorfulCandyLayer(void)
{
}

bool HSEffect_ColorfulCandyLayer::init()
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

void HSEffect_ColorfulCandyLayer::Load()
{
	
	for(int i =0; i < CandyCount; i++)
	{
		float x = CCRANDOM_0_1()* 580+30;
		
		float scale = CCRANDOM_0_1();

		float y = scale*960*3+960;
		int index = HSMath::Random(1,8);
		CCSprite* candy = CCSprite::create(CCString::createWithFormat("Image/effect/ColorfulCandy/candy%d.png",index)->getCString());
		candy->setPosition(ccp(x,y));

		CCActionInterval*  action = CCMoveTo::create(6,ccp(candy->getPositionX(), HSMath::Random(0.f,-960.f)));
		if(i ==0)//用第一个做结束条件
		{
			CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSEffect_ColorfulCandyLayer::Close));
			candy->runAction(CCSequence::create(action,pCallFunc,NULL));
		}
		else
		{
			candy->runAction(action);
		}

		float scaleRandom = HSMath::Random(0.5f,0.7f);

		candy->setScale(scaleRandom);
		this->addChild(candy);
	}
	//CCSequence::create()

	CCDirector::sharedDirector()->getRunningScene()->addChild(this,10000);
}

void HSEffect_ColorfulCandyLayer::Close()
{
	CCDirector::sharedDirector()->getRunningScene()->removeChild(this,true);
}


void HSEffect_ColorfulCandyLayer::registerWithTouchDispatcher()
{
	/**
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);*/
}

bool HSEffect_ColorfulCandyLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(this->isVisible())
	{
		return true;
	}
	return false;
}

void HSEffect_ColorfulCandyLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSEffect_ColorfulCandyLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSEffect_ColorfulCandyLayer::keyBackClicked()
{

}
void HSEffect_ColorfulCandyLayer::keyMenuClicked()
{

}
