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
		HSBalloonSprite* spriteA = (HSBalloonSprite*)bodyA->GetUserData();
		HSBalloonSprite* spriteB = (HSBalloonSprite*)bodyB->GetUserData();

		if (spriteA != NULL && spriteB != NULL)
		{
			if (bodyA->GetType() == b2_dynamicBody && bodyB->GetType() == b2_dynamicBody)
			{
				CCPoint pointA = spriteA->getPosition();
				CCPoint pointB = spriteB->getPosition();
				CCTexture2D* texture = spriteA->getTexture();
				float w = texture->getPixelsWide();
				float h = texture->getPixelsHigh();
				float minY = -(h / 2.f);

				CCRect areaA = CCRectMake(pointA.x - w / 2.f,pointA.y - h / 2.f,w,h);
				CCRect areaB = CCRectMake(pointB.x - w / 2.f,pointB.y - h / 2.f,w,h);
				
				if (areaA.intersectsRect(areaB) && pointA.y < minY && pointB.y < minY)
				{
					//spriteA->setVisible(false);
					//spriteA->SetIsLiester(true);
					spriteA->getB2Body()->ApplyForceToCenter(b2Vec2(0,0.5f));
					//spriteA->setColor(ccc3(255,0,0));
					//spriteB->setColor(ccc3(255,255,0));
				}
			}
		}
	}
}

void HSContacListener::EndContact( b2Contact* contact )
{
	
}
