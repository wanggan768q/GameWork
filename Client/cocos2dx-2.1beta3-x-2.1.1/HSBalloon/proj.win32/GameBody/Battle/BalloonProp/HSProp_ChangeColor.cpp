#include "HSProp_ChangeColor.h"
#include "HSBattleScene.h"

HSProp_ChangeColor::HSProp_ChangeColor(void)
{
}


HSProp_ChangeColor::~HSProp_ChangeColor(void)
{
}

bool HSProp_ChangeColor::Init( b2World* world )
{
	this->SetPropType(BALLOON_PROPS_ChangeColor);
	return this->InitWithFile("Image/animal_14.png",world,GetID());
}

bool HSProp_ChangeColor::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) )
	{
		return false;
	}	
	this->ChangerColor();

	this->TouchBalloonBegin();
	return true;
}

void HSProp_ChangeColor::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_ChangeColor::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	this->TouchBalloonEnd();
}

void HSProp_ChangeColor::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_ChangeColor::AddNodeToParent()
{
	
}

void HSProp_ChangeColor::ChangerColor()
{
	this->SetListerArea();
	HSBalloonFactory factory;

	factory.Reset();
	m_pWorld->QueryAABB(&factory,m_listerArea);

	CCPoint center = this->getPosition();
	float side = this->getTextureRect().size.width ;
	CCRect area = CCRectMake(center.x - side,center.y - side,side * 3.f,side * 3.f);
	std::vector<HSBalloonSprite*>* balloonList = factory.GetSpriteList();
	std::vector<HSBalloonSprite*>::iterator it = balloonList->begin();

	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleLayer* layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));
	if (layer)
	{
		map<BalloonColorType,CCTexture2D*>* colorMap = layer->GetBalloonAllTexture();
		int randomColorType = HSMath::Random(layer->m_iMinColorType,layer->m_iMaxColorType);
		for (;it != balloonList->end();++it)
		{
			HSBalloonSprite* balloon = (*it);
			if (balloon->GetID() != this->GetID())
			{
				if (balloon->GetID() < 1000)
				{
					CCPoint in = balloon->getPosition();
					if (area.containsPoint(in))
					{
						map<BalloonColorType,CCTexture2D*>::const_iterator tempIt = colorMap->find((BalloonColorType)randomColorType);
						
						
						if (tempIt != colorMap->end())
						{
							//balloon->SetColorType((BalloonColorType)randomColorType);
							//balloon->setTexture(tempIt->second);
							layer->PlayChangeColorEffect(balloon,(BalloonColorType)randomColorType,tempIt->second);
						}
					}
				}
			}
		}
	}
}

void HSProp_ChangeColor::SetListerArea()
{
	m_listerArea.lowerBound.Set(HS_VALUE_B2V(0),HS_VALUE_B2V(100));
	m_listerArea.upperBound.Set(HS_VALUE_B2V(HSBase::GetTemplateScreenW()),HS_VALUE_B2V(HSBase::GetTemplateScreenH()));
}
