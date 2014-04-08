#include "HSBufferProp_GoldErupt.h"
#include "HSBattleScene.h"
#include "HSProp_Money.h"
#include "HSBattleScene.h"


HSBufferProp_GoldErupt::HSBufferProp_GoldErupt(void)
{
	m_pSpxGoldErupt = NULL;
	m_isRunLogicRun = false;
	m_isBeginTime = true;
}


HSBufferProp_GoldErupt::~HSBufferProp_GoldErupt(void)
{
}

bool HSBufferProp_GoldErupt::init()
{
	return true;
}

bool HSBufferProp_GoldErupt::LogicBegin( float dt )
{
	HSBattleScene* scene = dynamic_cast<HSBattleScene*>( CCDirector::sharedDirector()->getRunningScene());
	if (!scene)
	{
		return false;
	}
	HSBattleLayer* layer = scene->GetHSBattleLayer();
	if (!layer)
	{
		return false;
	}

	if (!m_pSpxGoldErupt)
	{
		HS_GAME_CONFIG_MUTABLE_DATA()->dribbleCount = 0;
		this->setContentSize(HSBase::GetTemplateScreenSize());
		m_pSpxGoldErupt = SPX_Manager::CreateSprite("SPX/jinqian.sprite");
		m_pSpxGoldErupt->setPosition(ccp(HSBase::GetTemplateScreenW() / 2.f,HSBase::GetTemplateScreenH() / 2.f));
		layer->addChild(m_pSpxGoldErupt,910);
		m_pSpxGoldErupt->setVisible(true);
		m_pSpxGoldErupt->SetAction(0,1,this,callfuncND_selector(HSBufferProp_GoldErupt::CallGoldErupt),NULL);
	
		CCSprite* pGoldHeap = CCSprite::create("Image/goldHeap.png");
		pGoldHeap->setAnchorPoint(HS_ANCHOR_U_CENTER);
		pGoldHeap->setPosition(ccp(HSBase::GetTemplateScreenW() / 2.f,0.f));
		layer->addChild(pGoldHeap,1000);
		layer->SetGoldHeapSprite(pGoldHeap);
	}

	return m_isRunLogicRun;
}

bool HSBufferProp_GoldErupt::LogicEnd( float dt )
{
	if (m_isBeginTime)
	{
		m_isBeginTime = false;

		HSBattleScene* scene = dynamic_cast<HSBattleScene*>( CCDirector::sharedDirector()->getRunningScene());
		if (!scene)
		{
			return false;
		}
		HSBattleLayer* layer = scene->GetHSBattleLayer();
		if (!layer)
		{
			return false;
		}

		layer->PlayTimeTimeWillOver(this->GetDurationTime());
	}

	return false;
}

bool HSBufferProp_GoldErupt::LogicCountDown(float dt)
{
	
	return false;
}

void HSBufferProp_GoldErupt::CallGoldErupt( CCNode* pSpx, void* pData)
{
	HSBattleScene* scene = dynamic_cast<HSBattleScene*>( CCDirector::sharedDirector()->getRunningScene());
	if (!scene)
	{
		return;
	}
	HSBattleLayer* layer = scene->GetHSBattleLayer();
	if (!layer)
	{
		return;
	}

	HSBalloonFactory* pBalloonFactory = layer->QueryFullScreenBalloon();
	std::vector<HSBalloonSprite*>* pBalloonList = pBalloonFactory->GetSpriteList();
	std::vector<HSBalloonSprite*>::iterator it = pBalloonList->begin();

	for (;it!=pBalloonList->end();++it)
	{
		HSBalloonSprite* pBalloon = (*it);
		pBalloon->setVisible(false);

		b2Body* pBalloonBody = pBalloon->getB2Body();

		HSProp_Money* pMoney = HSProp_Money::create(layer->GetWorld());
		b2Body* pMoneyBody = pMoney->getB2Body();
		pMoney->setPosition(pBalloon->getPosition());

		b2Vec2 vMoneyPos = pMoneyBody->GetPosition();
		float angle = pBalloonBody->GetAngle();

		pMoneyBody->SetTransform(vMoneyPos,angle);

		layer->addChild(pMoney,900);
	}
	m_isRunLogicRun = true;
}
