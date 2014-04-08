#include "HSBalloonFactory.h"

HSBalloonFactory::HSBalloonFactory(void)
{
}


HSBalloonFactory::~HSBalloonFactory(void)
{
	this->Reset();
}

bool HSBalloonFactory::ReportFixture( b2Fixture* fixture )
{
	b2Body* body = fixture->GetBody();
	if (body != NULL)
	{
		HSBalloonSprite* sprite = (HSBalloonSprite*)body->GetUserData();
		if (sprite != NULL)
		{
			m_balloonSpriteList.insert(sprite);
		}
	}
	return true;
	
}

void HSBalloonFactory::Reset()
{
	m_balloonSpriteList.clear();
}

std::set<HSBalloonSprite*>* HSBalloonFactory::GetSpriteList()
{
	return &m_balloonSpriteList;
}
