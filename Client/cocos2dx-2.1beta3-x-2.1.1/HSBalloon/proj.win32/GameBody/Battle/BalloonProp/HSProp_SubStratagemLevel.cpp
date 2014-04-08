#include "HSProp_SubStratagemLevel.h"
#include "HSBattleScene.h"

HSProp_SubStratagemLevel::HSProp_SubStratagemLevel(void)
{
}


HSProp_SubStratagemLevel::~HSProp_SubStratagemLevel(void)
{
}

bool HSProp_SubStratagemLevel::Init( b2World* world )
{
	this->SetPropType(BALLOON_PROPS_SubStratagemLevel);
	m_spxSubStratagemLevel = SPX_Manager::CreateSprite("SPX/jiguanshang.sprite");
	m_spxSubStratagemLevel->setVisible(false);
	m_spxSubStratagemLevel->SetAction(0,1);
	m_spxSubStratagemLevel->setPosition(HSBase::GetTemplateScreenCentre());
	
	return this->InitWithFile("Image/animal_12.png",world,GetID());
}

bool HSProp_SubStratagemLevel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) )
	{
		return false;
	}

// 	int time = HS_GAME_CONFIG_DATA()->stratagemCurSec;
// 	int maxTime = HS_GAME_CONFIG_DATA()->stratagemEachCycleSec * HS_GAME_CONFIG_DATA()->stratagemMaxCycleCount;
// 	if (time > maxTime - HS_GAME_CONFIG_DATA()->stratagemEachCycleSec)
// 	{
// 		time = maxTime - 1;
// 		HS_GAME_CONFIG_MUTABLE_DATA()->stratagemCurSec = time;
// 	}else{
// 		HS_GAME_CONFIG_MUTABLE_DATA()->isRunStratagem = true;
// 		HS_GAME_CONFIG_MUTABLE_DATA()->stratagemRollBackStep = HS_GAME_CONFIG_DATA()->stratagemEachCycleSec / 3;
// 	}
	

	this->TouchBalloonBegin();
	this->setVisible(false);
	return true;
}

void HSProp_SubStratagemLevel::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSProp_SubStratagemLevel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleLayer* layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));	
	if (layer)
	{
		layer->GetModalLayer()->setVisible(true);
	}

	m_spxSubStratagemLevel->setVisible(true);
	m_spxSubStratagemLevel->SetAction(0,1,this,callfuncND_selector( HSProp_SubStratagemLevel::CallSubStratagemLevelFinish),NULL);
}

void HSProp_SubStratagemLevel::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_SubStratagemLevel::AddNodeToParent()
{
	this->getParent()->addChild(m_spxSubStratagemLevel,1000);
}

void HSProp_SubStratagemLevel::CallSubStratagemLevelFinish( CCNode* spxNode,void* pData )
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleLayer* layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));	
	if (layer)
	{
		layer->GetModalLayer()->setVisible(false);
	}
	HS_GAME_CONFIG()->AddStratagemTime(HS_GAME_CONFIG_DATA()->stratagemEachCycleSec);
	this->TouchBalloonEnd();
}
