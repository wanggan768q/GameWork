#include "HSProp_AddStratagemLevel.h"
#include "HSBattleScene.h"

HSProp_AddStratagemLevel::HSProp_AddStratagemLevel(void)
{
	m_spxAddStratagemLevel = NULL;
}


HSProp_AddStratagemLevel::~HSProp_AddStratagemLevel(void)
{
}

bool HSProp_AddStratagemLevel::Init( b2World* world )
{
	this->SetPropType(BALLOON_PROPS_AddStratagemLevel);

	m_spxAddStratagemLevel = SPX_Manager::CreateSprite("SPX/jiguanjiang.sprite");
	m_spxAddStratagemLevel->setVisible(false);
	m_spxAddStratagemLevel->SetAction(0,1);
	m_spxAddStratagemLevel->setPosition(HSBase::GetTemplateScreenCentre());

	return this->InitWithFile("Image/animal_13.png",world,GetID());
}

bool HSProp_AddStratagemLevel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if ( !ContainsTouchLocation(pTouch) )
	{
		return false;
	}

// 	int time = HS_GAME_CONFIG_MUTABLE_DATA()->stratagemCurSec;
// 	if (time >= 0)
// 	{
// 		while (time > 0 && time % HS_GAME_CONFIG_DATA()->stratagemEachCycleSec != 0)
// 		{
// 			time--;
// 		}
// 		HS_GAME_CONFIG_MUTABLE_DATA()->isRunStratagem = true;
// 		HS_GAME_CONFIG_MUTABLE_DATA()->stratagemCurSec = time;
// 	}

	this->TouchBalloonBegin();
	this->setVisible(false);
	return true;
}

void HSProp_AddStratagemLevel::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_AddStratagemLevel::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleLayer* layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));
	if (layer)
	{
		layer->GetModalLayer()->setVisible(true);
	}
	m_spxAddStratagemLevel->setVisible(true);
	m_spxAddStratagemLevel->SetAction(0,1,this,callfuncND_selector( HSProp_AddStratagemLevel::CallAddStratagemLevelFinish),NULL);
	
}

void HSProp_AddStratagemLevel::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	
}

void HSProp_AddStratagemLevel::AddNodeToParent()
{
	this->getParent()->addChild(m_spxAddStratagemLevel,1000);
}

void HSProp_AddStratagemLevel::CallAddStratagemLevelFinish( CCNode* spxNode,void* pData )
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSBattleLayer* layer = dynamic_cast<HSBattleLayer*>((dynamic_cast<HSBattleScene*>(scene))->getChildByTag(HS_BASE_TAG));	
	if (layer)
	{
		layer->GetModalLayer()->setVisible(false);
	}
	HS_GAME_CONFIG()->AddStratagemTime(-HS_GAME_CONFIG_DATA()->stratagemEachCycleSec);
	this->TouchBalloonEnd();
}
