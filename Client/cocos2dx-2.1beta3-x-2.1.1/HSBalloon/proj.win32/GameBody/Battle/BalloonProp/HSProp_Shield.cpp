#include "HSProp_Shield.h"


HSProp_Shield::HSProp_Shield(void)
{
}


HSProp_Shield::~HSProp_Shield(void)
{
}

bool HSProp_Shield::Init( b2World* world )
{
	this->SetPropType(BALLOON_PROPS_Shield);

	return this->InitWithFile("Image/animal_15.png",world,GetID());
}

bool HSProp_Shield::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) )
	{
		return false;
	}
	AddShieldToBalloon();

	this->TouchBalloonBegin();

	return true;
}

void HSProp_Shield::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_Shield::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	this->TouchBalloonEnd();
}

void HSProp_Shield::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_Shield::AddNodeToParent()
{
	
}

void HSProp_Shield::AddShieldToBalloon()
{
	b2AABB aabb;
	aabb.lowerBound.Set(HS_VALUE_B2V(0),HS_VALUE_B2V(100));
	aabb.upperBound.Set(HS_VALUE_B2V(HSBase::GetScreenWidth()),HS_VALUE_B2V(HSBase::GetScreenHeight()));
	HSBalloonFactory factory;

	factory.Reset();
	m_pWorld->QueryAABB(&factory,aabb);

	std::vector<HSBalloonSprite*>* balloonList = factory.GetSpriteList();
	std::vector<HSBalloonSprite*>::iterator it = balloonList->begin();

	for (;it != balloonList->end();++it)
	{
		HSBalloonSprite* balloon = (*it);
		if (balloon->GetID() != this->GetID())
		{
			if (balloon->GetID() < 1000)
			{
				balloon->AddShield();
			}
		}
	}
}
