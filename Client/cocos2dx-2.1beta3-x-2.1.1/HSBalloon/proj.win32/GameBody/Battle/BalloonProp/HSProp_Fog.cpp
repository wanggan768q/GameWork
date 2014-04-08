#include "HSProp_Fog.h"


HSProp_Fog::HSProp_Fog(void)
{
	m_pFogSprite = NULL;
	m_fPastTime = 0.f;
	m_isPauseUpdate = true;
}

HSProp_Fog::~HSProp_Fog(void)
{
}

bool HSProp_Fog::Init( b2World* world )
{
	this->SetPropType(BALLOON_PROPS_Fog);

	return this->InitWithFile("Image/animal_9.png",world,GetID());
}

bool HSProp_Fog::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) )
	{
		return false;
	}
	this->TouchBalloonBegin();

	m_pFogSprite->setPosition(this->getPosition());
	m_pFogSprite->setVisible(true);
	CCActionInterval*  appear = CCFadeIn::create(5.f);
	m_pFogSprite->runAction(appear);

	m_isPauseUpdate = false;

	return true;
}

void HSProp_Fog::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_Fog::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	this->TouchBalloonEnd();
}

void HSProp_Fog::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_Fog::AddNodeToParent()
{
	CCNode* parent = this->getParent();
	if (parent)
	{
		this->m_pFogSprite = CCSprite::create("Image/BattleLayer/fog.png");
		this->m_pFogSprite->setVisible(false);
		parent->addChild(m_pFogSprite,950);
	}
}

void HSProp_Fog::Updata( float dt )
{
	HSPropSpriteInterface::Updata(dt);

	if (m_isPauseUpdate)
	{		
		return;
	}

	if ((int)m_fPastTime >= M_SWAITTIME)
	{
		CCActionInterval*  disappear = CCFadeOut::create(5.f);
		m_pFogSprite->runAction(disappear);

		m_isPauseUpdate = true;
		m_fPastTime = 0.f;
	}else{
		m_fPastTime += dt;
	}
}
