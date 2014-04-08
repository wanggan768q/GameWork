#include "HSProp_ChangeColorFullScreen.h"
#include "HSBattleScene.h"

HSProp_ChangeColorFullScreen::HSProp_ChangeColorFullScreen(void)
{
}

HSProp_ChangeColorFullScreen::~HSProp_ChangeColorFullScreen(void)
{
}

bool HSProp_ChangeColorFullScreen::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) ) return false;
	
	if(this->TouchBalloonBegin())
	{
		this->ChangerColor();
		return true;	
	}
	return false;
}

void HSProp_ChangeColorFullScreen::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	this->TouchBalloonEnd();
}

void HSProp_ChangeColorFullScreen::ChangerColor()
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleLayer* layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));	
	if (layer)
	{
		HSBalloonFactory factory;
		factory.Reset();
		layer->GetWorld()->QueryAABB(&factory,layer->m_workingAreaQueryAABB);
		std::vector<HSBalloonSprite*>* balloonList = factory.GetSpriteList();
		std::vector<HSBalloonSprite*>::iterator it = balloonList->begin();
		map<BalloonColorType,CCTexture2D*>* colorMap = layer->GetBalloonAllTexture();
		int randomColorType = HSMath::Random(layer->m_iMinColorType,layer->m_iMaxColorType);

		for (;it != balloonList->end();++it)
		{
			HSBalloonSprite* balloon = (*it);
			if (balloon->GetID() < 1000)
			{
				map<BalloonColorType,CCTexture2D*>::const_iterator tempIt = colorMap->find((BalloonColorType)randomColorType);
				if (tempIt != colorMap->end())
				{
					balloon->SetColorType((BalloonColorType)randomColorType);
					balloon->setTexture(tempIt->second);
				}
			}
		}
	}
}
