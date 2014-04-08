#include "HSProp_King.h"


HSProp_King::HSProp_King(void)
{
	this->SetMaxTouchCount(5);
	m_iKingTouchIndex = this->GetMaxTouchCount();
	m_fSustainTime = 5.f;
}

HSProp_King::~HSProp_King(void)
{
}

bool HSProp_King::Init( b2World* world )
{
	this->SetPropType(BALLOON_PROPS_King);
	return this->InitWithFile("Image/animal_6.png",world,GetID());
}

bool HSProp_King::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) )
	{
		return false;
	}
	this->TouchBalloonBegin();
	m_iKingTouchIndex--;
	return true;
}

void HSProp_King::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_King::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_iKingTouchIndex == 0)
	{
		CCActionInterval*  actionL = CCBlink::create(m_fSustainTime, 20);
		CCActionInterval*  actionR = CCBlink::create(m_fSustainTime, 20);
		CCCallFunc* callFinish = CCCallFunc::create(this,callfunc_selector(HSProp_King::CallKingEffectFinish));
		m_pKingEffect_L->runAction(CCSequence::create(actionL,callFinish,NULL));
		m_pKingEffect_R->runAction(actionR);
		m_pKingEffect_L->setVisible(true);
		m_pKingEffect_R->setVisible(true);

		HS_GAME_CONFIG_MUTABLE_DATA()->isKingEffect = true;
		HS_GAME_CONFIG_MUTABLE_DATA()->isKingDeath = true;

		this->TouchBalloonEnd();
		m_iKingTouchIndex = this->GetMaxTouchCount();
	}else{
		m_fScale = 1.f;
	}
}

void HSProp_King::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_King::AddNodeToParent()
{
	CCSize Combo_King_Num_PngSize = CCSizeMake(1000,137);
	const char* num = CCString::createWithFormat("%d",this->GetMaxTouchCount())->getCString();
	m_pKingTouchLabel = CCLabelAtlas::create(num,"Image/Combo/Combo_King_Num.png",Combo_King_Num_PngSize.width / 10,Combo_King_Num_PngSize.height,'0');
	m_pKingTouchLabel->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pKingTouchLabel->setPosition(ccp(this->getContentSize().width / 2.f,this->getContentSize().height / 2.f));
	m_pKingTouchLabel->setScale(0.6f);
	this->addChild(m_pKingTouchLabel);

	m_pKingEffect_L = HS_FIND_UI_PANEL_SPRITE("UI_KingLight_1","KingLight");
	m_pKingEffect_R = HS_FIND_UI_PANEL_SPRITE("UI_KingLight_0","KingLight");
	m_pKingEffect_L->setVisible(false);
	m_pKingEffect_R->setVisible(false);
}

void HSProp_King::CallKingEffectFinish()
{
	if (m_pKingEffect_L && m_pKingEffect_R)
	{
		m_pKingEffect_L->setVisible(false);
		m_pKingEffect_R->setVisible(false);
		HS_GAME_CONFIG_MUTABLE_DATA()->isKingEffect = false;
	}
}

void HSProp_King::Updata( float dt )
{
	HSPropSpriteInterface::Updata(dt);

	m_pKingTouchLabel->setString(CCString::createWithFormat("%d",m_iKingTouchIndex)->getCString());
}
