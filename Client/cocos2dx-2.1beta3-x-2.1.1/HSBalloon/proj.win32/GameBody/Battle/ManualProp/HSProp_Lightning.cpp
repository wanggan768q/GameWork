#include "HSProp_Lightning.h"
#include "HSBattleScene.h"

HSProp_Lightning::HSProp_Lightning(void)
{
	m_isLister = false;	
}


HSProp_Lightning::~HSProp_Lightning(void)
{
}

bool HSProp_Lightning::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) ) return false;

	if(this->TouchBalloonBegin())
	{
		m_isLister = true;
		HS_GAME_CONFIG_MUTABLE_DATA()->lastBalloonColorType = BALLOON_COLOR_UNKNOW;
		return false;
	}
	return true;
}

void HSProp_Lightning::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	this->TouchBalloonEnd();
}

void HSProp_Lightning::QueryAABB()
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleLayer* layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));
	if (layer)
	{
		m_factory.Reset();
		layer->GetWorld()->QueryAABB(&m_factory,layer->m_workingAreaQueryAABB);
		std::vector<HSBalloonSprite*>* balloonList = m_factory.GetSpriteList();
		std::vector<HSBalloonSprite*>::iterator it = balloonList->begin();
		for (;it!= balloonList->end();++it)
		{
			HSBalloonSprite* sprite = (*it);
			if (sprite->GetColorType() == HS_GAME_CONFIG_DATA()->lastBalloonColorType)
			{
				m_workingAreaSprites.push_back(sprite);
			}
		}

		{
			int count = (int)m_workingAreaSprites.size();
			HSBalloonSprite* temp = NULL;
			for(int i=0;i<count;i++)
			{
				for(int j=0;j<count-i-1;j++)
				{
					if(m_workingAreaSprites[j]->m_fY > m_workingAreaSprites[j+1]->m_fY)
					{
						temp = m_workingAreaSprites[j];
						m_workingAreaSprites[j] = m_workingAreaSprites[j+1];
						m_workingAreaSprites[j+1] = temp;
					}
				}
			}
			HS_GAME_CONFIG_MUTABLE_DATA()->stratagemRollBackStepCount = count;
			layer->LayerShakeEffect();
		}
	}
}

void HSProp_Lightning::Lihgtning()
{
	double curTime = HSTime::GetLocalityTime();
	static double tempNextTime = 0;
	if (curTime < tempNextTime)
	{
		return;
	}
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleLayer* Layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));	
	if (Layer)
	{
		if ((int)m_workingAreaSprites.size() > 0)
		{
			HSBalloonSprite* balloonSprite = this->m_workingAreaSprites[0] ;
			if (balloonSprite != NULL)
			{
				balloonSprite->ccTouchBegan(NULL,NULL);	
				CCNode* node = HS_FIND_UI_PANEL("UI_JiGuanZu");
				CCPoint pos = node->getPosition();
				pos.x += node->getContentSize().width / 2.f;
				pos.y -= node->getContentSize().height / 2.f;

				Layer->PlaySoulEffect(balloonSprite,ccc4f(0,0,255,0),pos);
				Layer->PlayTouchBalloonEffect(balloonSprite->getPosition());
				Layer->PlayLightEffect(balloonSprite);

				balloonSprite->ccTouchEnded(NULL,NULL);
				this->m_workingAreaSprites.erase(m_workingAreaSprites.begin());
			}
			tempNextTime = curTime + HSMath::Random(50.f,200.f);
			HS_GAME_CONFIG_MUTABLE_DATA()->dribbleCount++;
			HS_GAME_CONFIG()->SetLaseTime();
			HS_GAME_CONFIG_MUTABLE_DATA()->gameScore += (int)m_workingAreaSprites.size() * 4 * 11;
		}else{
			Layer->SetIsPauseWorld(false);
		}
	}
}

void HSProp_Lightning::Updata( float dt )
{
	if (m_isLister && HS_GAME_CONFIG_DATA()->lastBalloonColorType != BALLOON_COLOR_UNKNOW)
	{
		this->QueryAABB();
		m_isLister = false;
	}
	this->Lihgtning();
}

