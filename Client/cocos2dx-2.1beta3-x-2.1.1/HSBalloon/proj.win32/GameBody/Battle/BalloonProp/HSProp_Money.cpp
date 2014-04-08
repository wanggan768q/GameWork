#include "HSProp_Money.h"


HSProp_Money::HSProp_Money(void)
{
}


HSProp_Money::~HSProp_Money(void)
{
}

bool HSProp_Money::Init( b2World* world )
{
	this->SetPropType(BALLOON_PROPS_Money);

	m_spxMoney = SPX_Manager::CreateSprite("SPX/jinbi.sprite");
	m_spxMoney->setVisible(false);
	m_spxMoney->SetAction(0,1);

	return this->InitWithFile("Image/animal_7.png",world,GetID());
}

bool HSProp_Money::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) )
	{
		return false;
	}
	int money = HSMath::Random(1,5);
	HS_GAME_CACHE()->AddGold(money);
	HS_GAME_CONFIG_MUTABLE_DATA()->isMoneyEffect = true;
	this->TouchBalloonBegin();

	this->setVisible(false);
	

	return true;
}

void HSProp_Money::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSProp_Money::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	m_spxMoney->setPosition(this->getPosition());
	m_spxMoney->setVisible(true);
	m_spxMoney->SetAction(0,1,this,callfuncND_selector( HSProp_Money::CallMoneyFinish),NULL);
}

void HSProp_Money::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSProp_Money::AddNodeToParent()
{
	this->getParent()->addChild(m_spxMoney,1000);
}

void HSProp_Money::CallMoneyFinish( CCNode* spxNode,void* pData )
{
	this->TouchBalloonEnd();
}
