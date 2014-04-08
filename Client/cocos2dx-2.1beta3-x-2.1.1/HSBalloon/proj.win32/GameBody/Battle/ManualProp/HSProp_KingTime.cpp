#include "HSProp_KingTime.h"
#include "HSBattleScene.h"


HSProp_KingTime::HSProp_KingTime(void)
{
	m_fSustainTime = 20.f;
	m_spx = NULL;
	this->Load();
}


HSProp_KingTime::~HSProp_KingTime(void)
{
}

bool HSProp_KingTime::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
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
		m_spx->setVisible(true);
		m_spx->SetAction(0,1,this,callfuncND_selector(HSProp_KingTime::CallSpxFinish),NULL);

		CCActionInterval*  actionL = CCBlink::create(m_fSustainTime, 20 * 4);
		CCActionInterval*  actionR = CCBlink::create(m_fSustainTime, 20 * 4);
		CCCallFunc* callFinish = CCCallFunc::create(this,callfunc_selector(HSProp_KingTime::CallKingEffectFinish));
		m_pKingEffect_L->runAction(CCSequence::create(actionL,callFinish,NULL));
		m_pKingEffect_R->runAction(actionR);
		m_pKingEffect_L->setVisible(true);
		m_pKingEffect_R->setVisible(true);

		HS_GAME_CONFIG_MUTABLE_DATA()->isKingEffect = true;
		return true;
	}
	return false;
}

void HSProp_KingTime::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	this->TouchBalloonEnd();
}

void HSProp_KingTime::CallKingEffectFinish()
{
	if (m_pKingEffect_L && m_pKingEffect_R)
	{
		m_pKingEffect_L->setVisible(false);
		m_pKingEffect_R->setVisible(false);
		HS_GAME_CONFIG_MUTABLE_DATA()->isKingEffect = false;
	}
}

void HSProp_KingTime::Load()
{
	m_pKingEffect_L = HS_FIND_UI_PANEL_SPRITE("UI_KingLight_1","KingLight");
	m_pKingEffect_R = HS_FIND_UI_PANEL_SPRITE("UI_KingLight_0","KingLight");
	m_pKingEffect_L->setVisible(false);
	m_pKingEffect_R->setVisible(false);
}

void HSProp_KingTime::AddNodeToParent()
{
	m_spx = SPX_Manager::CreateSprite("SPX/miaozhienci.sprite");
	m_spx->setPosition(HSBase::GetTemplateScreenCentre());
	m_spx->setVisible(false);
	m_spx->SetAction(0,1);
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleLayer* layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));	
	if (layer)
	{
		layer->addChild(m_spx,1000);
	}
}

void HSProp_KingTime::CallSpxFinish( CCNode* spxNode,void* pData )
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleLayer* layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));	
	if (layer)
	{
		layer->GetModalLayer()->setVisible(false);
	}
}
