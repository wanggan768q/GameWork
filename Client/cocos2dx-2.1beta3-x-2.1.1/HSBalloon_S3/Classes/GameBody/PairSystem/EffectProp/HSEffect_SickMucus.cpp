#include "HSEffect_SickMucus.h"
#include "HSPairSystemScene.h"

HSEffect_SickMucusLayer::HSEffect_SickMucusLayer(void)
{
	m_psick7=NULL;
}

HSEffect_SickMucusLayer::~HSEffect_SickMucusLayer(void)
{
}

bool HSEffect_SickMucusLayer::init()
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

void HSEffect_SickMucusLayer::Load()
{
	CCSprite* sick1 = HSCCSprite::create("Image/sick1.png");
	CCSprite* sick2 = HSCCSprite::create("Image/sick2.png");
	CCSprite* sick3 = HSCCSprite::create("Image/sick3.png");
	CCSprite* sick4 = HSCCSprite::create("Image/sick4.png");
	CCSprite* sick5 = HSCCSprite::create("Image/sick2.png");
	CCSprite* sick6 = HSCCSprite::create("Image/sick3.png");
	m_psick7 = HSCCSprite::create("Image/sick4.png");

	sick1->setPosition(ccp(300,500));
	sick2->setPosition(ccp(300,200));
	sick3->setPosition(ccp(100,500));
	sick4->setPosition(ccp(533,600));
	sick5->setPosition(ccp(200,100));
	sick6->setPosition(ccp(400,200));
	m_psick7->setPosition(ccp(345,444));

	sick1->setScale(0.1f);
	sick2->setScale(0.1f);
	sick3->setScale(0.1f);
	sick4->setScale(0.1f);
	sick5->setScale(0.1f);
	sick6->setScale(0.1f);
	m_psick7->setScale(0.1f);

 	CCActionInterval*  action5 = CCScaleTo::create(0.1f, 0.3f);
 	CCActionInterval*  action6 = CCScaleTo::create(0.2f, 0.8f);
	CCActionInterval*  action7 = CCScaleTo::create(1.f,0.8f);
	CCActionInterval*  action8 = CCScaleTo::create(1.5f, 1.f);
	CCSequence* p1 = CCSequence::create(action5,action6,action7,action8,NULL);
	CCSequence* p2 = (CCSequence*)p1->copy()->autorelease();
	CCSequence* p3 = (CCSequence*)p1->copy()->autorelease();
	CCSequence* p4 = (CCSequence*)p1->copy()->autorelease();
	CCSequence* p5 = (CCSequence*)p1->copy()->autorelease();
	CCSequence* p6 = (CCSequence*)p1->copy()->autorelease();
	
	CCFadeTo* fade1 = CCFadeTo::create(1.3f,255.f);
	CCFadeTo* fade2 = CCFadeTo::create(1.5f,1.f);
	CCSequence* f1 = CCSequence::create(fade1,fade2,NULL);
	CCSequence* f2 = (CCSequence*)f1->copy()->autorelease();
	CCSequence* f3 = (CCSequence*)f1->copy()->autorelease();
	CCSequence* f4 = (CCSequence*)f1->copy()->autorelease();
	CCSequence* f5 = (CCSequence*)f1->copy()->autorelease();
	CCSequence* f6 = (CCSequence*)f1->copy()->autorelease();

	sick1->runAction(p1);
	sick1->runAction(f1);
	this->addChild(sick1);

	sick2->runAction(p2);
	sick2->runAction(f2);
	this->addChild(sick2);

	sick3->runAction(p3);
	sick3->runAction(f3);
	this->addChild(sick3);

	sick4->runAction(p4);
	sick4->runAction(f4);
	this->addChild(sick4);

	sick5->runAction(p5);
	sick5->runAction(f5);
	this->addChild(sick5);

	sick6->runAction(p6);
	sick6->runAction(f6);
	this->addChild(sick6);

	//CCActionInterval*  action11 = CCScaleTo::create(0.026f, 0.2f);
	//CCActionInterval*  action12 = CCScaleTo::create(0.026f, 0.3f);
	//CCActionInterval*  action13 = CCScaleTo::create(0.026f, 0.4f);
	//CCActionInterval*  action14 = CCScaleTo::create(0.026f, 0.5f);
 	CCActionInterval*  action15 = CCScaleTo::create(0.1f, 0.3f);
 	CCActionInterval*  action16 = CCScaleTo::create(0.2f, 0.8f);
	//CCActionInterval*  action17 = CCScaleTo::create(1.f, 0.8f);

	//CCActionInterval*  action18 = CCScaleTo::create(1.5f, 1.f);
	CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSEffect_SickMucusLayer::Shake));
	CCSequence* p7 = CCSequence::create(action15,action16,pCallFunc,NULL);
	CCSequence* f7 = (CCSequence*)f1->copy()->autorelease();
	m_psick7->runAction(p7);
	m_psick7->runAction(f7);
	this->addChild(m_psick7);

	CCDirector::sharedDirector()->getRunningScene()->addChild(this,10000);
}

void HSEffect_SickMucusLayer::Close()
{
	CCDirector::sharedDirector()->getRunningScene()->removeChild(this,true);
}

void HSEffect_SickMucusLayer::Shake()
{
	CCActionInterval*  action18 = CCScaleTo::create(1.f, 1.f);
	CCActionInterval*  action17 = CCScaleTo::create(1.f, 0.8f);
	CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSEffect_SickMucusLayer::Close));
	CCSequence* p7 = CCSequence::create(action17,action18,pCallFunc,NULL);
	 
	m_psick7->runAction(p7);

	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

    HSPairSystemScene* pairScene = dynamic_cast<HSPairSystemScene*>(scene);
    if(pairScene)
    {
        CCPoint position =pairScene->getPosition();
        
        CCMoveTo* left1 = CCMoveTo::create(0.05f,ccp(position.x+5,position.y));
        CCMoveTo* right1 = CCMoveTo::create(0.05f,ccp(position.x-5,position.y));
        CCMoveTo* top1 = CCMoveTo::create(0.05f,ccp(position.x,position.y+5));
        CCMoveTo* rom1 = CCMoveTo::create(0.05f,ccp(position.x,position.y-5));
        CCFiniteTimeAction* action3 = CCSequence::create(left1,right1,top1,rom1,NULL);
        pairScene->runAction(action3);
    }
}


void HSEffect_SickMucusLayer::registerWithTouchDispatcher() 
{
	/**
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);*/
}

bool HSEffect_SickMucusLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(this->isVisible())
	{
		return true;
	}
	return false;
}

void HSEffect_SickMucusLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSEffect_SickMucusLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSEffect_SickMucusLayer::keyBackClicked()
{

}
void HSEffect_SickMucusLayer::keyMenuClicked()
{

}
