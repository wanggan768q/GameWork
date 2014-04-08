#include "HSProp_StopStratagemTime.h"


HSProp_StopStratagemTime::HSProp_StopStratagemTime(void)
{
	m_fPastTime = 0.f;
	m_isPauseUpdate = true;
}


HSProp_StopStratagemTime::~HSProp_StopStratagemTime(void)
{
}

bool HSProp_StopStratagemTime::Init( b2World* world )
{
	this->SetPropType(BALLOON_PROPS_StopStratagemTime);
	return this->InitWithFile("Image/animal_11.png",world,GetID());
}

bool HSProp_StopStratagemTime::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) )
	{
		return false;
	}
	HS_GAME_CONFIG_MUTABLE_DATA()->m_isPauseStratagemTime = true;
	m_spxStopStratagemTime->setVisible(true);
	m_spxStopStratagemTime->SetAction(0,1,this,callfuncND_selector(HSProp_StopStratagemTime::CallSpxStopStratagemTimeAction_1),NULL);

	m_isPauseUpdate = false;

	this->TouchBalloonBegin();
	return true;
}

void HSProp_StopStratagemTime::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSProp_StopStratagemTime::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	this->TouchBalloonEnd();
}

void HSProp_StopStratagemTime::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSProp_StopStratagemTime::AddNodeToParent()
{
	CCNode* spxParent = HS_FIND_UI_PANEL("UI_JiGuanZu");
	m_spxStopStratagemTime = SPX_Manager::CreateSprite("SPX/StopStratagemTime.sprite");
	m_spxStopStratagemTime->setVisible(false);
	CCPoint pos;
	pos.x += spxParent->getContentSize().width;
	pos.y -= spxParent->getContentSize().height / 2.f;
	m_spxStopStratagemTime->setPosition(pos);
	//m_spxStopStratagemTime->setScale(0.7f);
	spxParent->addChild(m_spxStopStratagemTime,2000);
}

void HSProp_StopStratagemTime::Updata( float dt )
{
	HSPropSpriteInterface::Updata(dt);

	if (m_isPauseUpdate)
	{
		return;
	}

	if ((int)m_fPastTime >= M_STOPTIME)
	{
		m_spxStopStratagemTime->setVisible(true);
		m_spxStopStratagemTime->SetAction(2,1,this,callfuncND_selector(HSProp_StopStratagemTime::CallSpxStopStratagemTimeActionFinish),NULL);

		m_isPauseUpdate = true;
		m_fPastTime = 0.f;
	}else{
		m_fPastTime += dt;
	}
}

void HSProp_StopStratagemTime::CallSpxStopStratagemTimeAction_1( CCNode* node,void* data )
{
	m_spxStopStratagemTime->setVisible(true);
	m_spxStopStratagemTime->SetAction(1);
}

void HSProp_StopStratagemTime::CallSpxStopStratagemTimeActionFinish( CCNode* node,void* data )
{
	HS_GAME_CONFIG_MUTABLE_DATA()->m_isPauseStratagemTime = false;
	m_spxStopStratagemTime->setVisible(false);
	m_spxStopStratagemTime->SetAction(0);
}
