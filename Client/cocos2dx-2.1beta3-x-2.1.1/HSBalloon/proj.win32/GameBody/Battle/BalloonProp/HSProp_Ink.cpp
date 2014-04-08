#include "HSProp_Ink.h"


HSProp_Ink::HSProp_Ink(void)
{
}


HSProp_Ink::~HSProp_Ink(void)
{
}

bool HSProp_Ink::Init( b2World* world )
{
	this->SetPropType(BALLOON_PROPS_Ink);
	m_spxInk = SPX_Manager::CreateSprite("SPX/mozhi.sprite");
	m_spxInk->setVisible(false);
	m_spxInk->SetAction(0,1);
	m_spxInk->setPosition(HSBase::GetTemplateScreenCentre());

	return this->InitWithFile("Image/animal_16.png",world,GetID());
}

bool HSProp_Ink::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) || !m_spxInk)
	{
		return false;
	}

	m_spxInk->setPosition(this->getPosition());
	m_spxInk->setVisible(true);
	m_spxInk->SetAction(0,1,this,callfuncND_selector(HSProp_Ink::CallInkFinish_1),NULL);

	return true;
}

void HSProp_Ink::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_Ink::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	this->TouchBalloonEnd();
}

void HSProp_Ink::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_Ink::AddNodeToParent()
{
	this->getParent()->addChild(m_spxInk,1000);
}

void HSProp_Ink::CallInkFinish_1(CCNode* spxNode,void* pData)
{
	m_spxInk->setVisible(true);
	m_spxInk->SetAction(1);
	CCDelayTime* delayTime = CCDelayTime::create(3.f);
	CCCallFunc* call = CCCallFunc::create(this,callfunc_selector(HSProp_Ink::CallInkFinish_2));
	m_spxInk->runAction(CCSequence::create(delayTime,call,NULL));
}

void HSProp_Ink::CallInkFinish_2()
{
	m_spxInk->setVisible(true);
	m_spxInk->SetAction(2,1,this,callfuncND_selector(HSProp_Ink::CallInkFinish),NULL);
}

void HSProp_Ink::CallInkFinish(CCNode* spxNode,void* pData)
{
	
}
