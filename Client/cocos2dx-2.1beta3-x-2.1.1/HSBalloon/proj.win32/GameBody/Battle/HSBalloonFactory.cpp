#include "HSBalloonFactory.h"

HSBalloonFactory::HSBalloonFactory(void)
{
}


HSBalloonFactory::~HSBalloonFactory(void)
{
}

bool HSBalloonFactory::ReportFixture( b2Fixture* fixture )
{
	b2Body* body = fixture->GetBody();
	if (body != NULL)
	{
		HSBalloonSprite* sprite = (HSBalloonSprite*)body->GetUserData();
		if (sprite != NULL)
		{
			//CCLog("ReportFixtureCount: %d ",(int)m_balloonSpriteList.size());
			std::vector<HSBalloonSprite*>::iterator it = m_balloonSpriteList.begin();
			for (;it!=m_balloonSpriteList.end();++it)
			{
				if (sprite->GetID() == (*it)->GetID())
				{
					//因为一个装置可能是由多个形状组成的，但是每个形状里面的数据又是一样的
					//怕导致重复,就判断下2个真实数据是否一致，确保取出来的 精灵对象是唯一的
					//CCLog("The Same : %d",sprite->GetID());
					return true;
				}
			}
			m_balloonSpriteList.push_back(sprite);
		}
	}
	return true;
	
}

void HSBalloonFactory::Reset()
{
	m_balloonSpriteList.clear();
}

std::vector<HSBalloonSprite*>* HSBalloonFactory::GetSpriteList()
{
	return &m_balloonSpriteList;
}
