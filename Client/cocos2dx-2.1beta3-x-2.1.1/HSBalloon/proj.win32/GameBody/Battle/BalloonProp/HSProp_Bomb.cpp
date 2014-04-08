#include "HSProp_Bomb.h"


HSProp_Bomb::HSProp_Bomb(void)
{
}


HSProp_Bomb::~HSProp_Bomb(void)
{
}

bool HSProp_Bomb::Init( b2World* world )
{
	this->SetPropType(BALLOON_PROPS_Bomb);

	m_spxBomb = SPX_Manager::CreateSprite("SPX/zhadan.sprite");
	m_spxBomb->setVisible(false);
	m_spxBomb->SetAction(0,1);

	return this->InitWithFile("Image/animal_10.png",world,GetID());
}

bool HSProp_Bomb::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) )
	{
		return false;
	}

	HSBalloonFactory factory;
	b2AABB aabb;
	aabb.lowerBound.Set(HS_VALUE_B2V(0),HS_VALUE_B2V(100));
	aabb.upperBound.Set(HS_VALUE_B2V(HSBase::GetScreenWidth()),HS_VALUE_B2V(HSBase::GetScreenHeight()));

	factory.Reset();
	m_pWorld->QueryAABB(&factory,aabb);

	CCPoint center = this->getPosition();
	float side = this->getTextureRect().size.width ;
	CCRect area = CCRectMake(center.x - side,center.y - side,side * 3.f,side * 3.f);
	std::vector<HSBalloonSprite*>* balloonList = factory.GetSpriteList();
	std::vector<HSBalloonSprite*>::iterator it = balloonList->begin();

	for (;it != balloonList->end();++it)
	{
		HSBalloonSprite* balloon = (*it);
		if (balloon->GetID() < 1000 && balloon->GetID() != this->GetID())
		{
			CCPoint in = balloon->getPosition();
			if (area.containsPoint(in))
			{
				HS_GAME_CONFIG_MUTABLE_DATA()->gameScore++;
				balloon->TouchBalloonEnd();
			}
		}
	}

	this->setVisible(false);
	this->TouchBalloonBegin();

	return true;
}

void HSProp_Bomb::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSProp_Bomb::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	HSSoundManage::ShareSoundManage()->PlayerEffect("bomb");
	m_spxBomb->setPosition(this->getPosition());
	m_spxBomb->setVisible(true);
	m_spxBomb->SetAction(0,1,this,callfuncND_selector( HSProp_Bomb::CallBombFinish),NULL);
}

void HSProp_Bomb::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSProp_Bomb::AddNodeToParent()
{	
	this->getParent()->addChild(m_spxBomb,1000);
}

void HSProp_Bomb::Updata( float dt )
{
	HSPropSpriteInterface::Updata(dt);
}

void HSProp_Bomb::CallBombFinish( CCNode* spxNode,void* pData )
{
	this->TouchBalloonEnd();
}



