#include "HSContacListener.h"

HSContacListener::HSContacListener(void)
{
}


HSContacListener::~HSContacListener(void)
{
}

void HSContacListener::BeginContact( b2Contact* contact )
{
	bool touch = contact->IsTouching();
	if (touch)
	{
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();
		HSBalloonSprite* sA = (HSBalloonSprite*)bodyA->GetUserData();
		HSBalloonSprite* sB = (HSBalloonSprite*)bodyB->GetUserData();

		if (sA != NULL && sB != NULL)
		{
			if (bodyA->GetType() == b2_dynamicBody && bodyB->GetType() == b2_dynamicBody)
			{
				CCPoint pA = sA->getPosition();
				CCPoint pB = sB->getPosition();
				//CCTexture2D* texture = sA->getTexture();
				float w = sA->getContentSize().width;
				float h = sA->getContentSize().height;

				CCRect areaA = CCRectMake(pA.x - w / 2.f,pA.y - h / 2.f,w,h);
				CCRect areaB = CCRectMake(pB.x - w / 2.f,pB.y - h / 2.f,w,h);
				
				if (areaA.intersectsRect(areaB))
				{
					m_willRestBalloonList.push_back(HSOverlapBalloon(sA,sB));
				}
			}
		}
	}
}

void HSContacListener::EndContact( b2Contact* contact )
{
	
}

const std::vector<HSOverlapBalloon>* HSContacListener::GetWillRestBalloonList()
{
	return &m_willRestBalloonList;
}

void HSContacListener::Logic( float dt )
{
	
}




//////////////////////////////////////////////////////////////////////////

HSOverlapBalloon::HSOverlapBalloon( HSBalloonSprite* pReferenObject,HSBalloonSprite* pWillChangeObect )
{
	m_pReferenObject = pReferenObject;
	m_pWillChangeObect = pWillChangeObect;
}

HSOverlapBalloon::~HSOverlapBalloon()
{
	m_pReferenObject = NULL;
	m_pWillChangeObect = NULL;
}

HSBalloonSprite* HSOverlapBalloon::GetReferenObject()
{
	return m_pReferenObject;
}

HSBalloonSprite* HSOverlapBalloon::GetWillChangeObect()
{
	return m_pWillChangeObect;
}

void HSOverlapBalloon::Handle()
{

}
