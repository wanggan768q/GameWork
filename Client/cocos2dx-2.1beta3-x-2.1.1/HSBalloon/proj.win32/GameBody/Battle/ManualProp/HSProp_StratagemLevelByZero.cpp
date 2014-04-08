#include "HSProp_StratagemLevelByZero.h"
#include "HSBattleScene.h"

HSProp_StratagemLevelByZero::HSProp_StratagemLevelByZero(void)
{
	m_spxStratagemLevelByZero = NULL;
}


HSProp_StratagemLevelByZero::~HSProp_StratagemLevelByZero(void)
{
}

bool HSProp_StratagemLevelByZero::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) ) return false;

	if(this->TouchBalloonBegin())
	{
		CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
		HSBattleLayer* layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));	
		if (layer)
		{
			layer->GetModalLayer()->setVisible(true);
		}
		m_spxStratagemLevelByZero->setVisible(true);
		m_spxStratagemLevelByZero->SetAction(0,1,this,callfuncND_selector(HSProp_StratagemLevelByZero::CallStratagemLevelByZeroFinish),NULL);
		return false;
	}
	return true;
}

void HSProp_StratagemLevelByZero::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	this->TouchBalloonEnd();
}

void HSProp_StratagemLevelByZero::AddNodeToParent()
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleLayer* layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));
	if (layer)
	{
		m_spxStratagemLevelByZero = SPX_Manager::CreateSprite("SPX/suoyoushangsheng.sprite");
		m_spxStratagemLevelByZero->setVisible(false);
		m_spxStratagemLevelByZero->SetAction(0,1);
		m_spxStratagemLevelByZero->setPosition(HSBase::GetTemplateScreenCentre());
		layer->addChild(m_spxStratagemLevelByZero,1000);
	}
}

void HSProp_StratagemLevelByZero::CallStratagemLevelByZeroFinish( CCNode* spxNode,void* pData )
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleLayer* layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));	
	if (layer)
	{
		layer->GetModalLayer()->setVisible(false);
		for (int i=0;i< HS_GAME_CONFIG_DATA()->stratagemMaxCycleCount;++i)
		{
			if(layer->GetStragemManager())
			{
				layer->GetStragemManager()->Up();
			}
			
		}
	}
	HS_GAME_CONFIG()->ResetStratagemTime();
}
