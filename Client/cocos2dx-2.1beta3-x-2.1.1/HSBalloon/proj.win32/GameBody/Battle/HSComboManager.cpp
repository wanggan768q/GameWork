#include "HSComboManager.h"


HSComboManager::HSComboManager(void)
{
	m_iLastDribbleCount = 0;
	m_isShowCombo = false;
}


HSComboManager::~HSComboManager(void)
{
}

HSComboManager* HSComboManager::create()
{
	HSComboManager* manager = new HSComboManager;
	if (manager && manager->Init())
	{
		manager->autorelease();
		return manager;
	}
	CC_SAFE_DELETE(manager);
	return NULL;
}

bool HSComboManager::Init()
{

	m_pCombo_5_or_10 = CCSprite::create("Image/Combo/Combo_5_or_10.png");
	m_pCombo_King = CCSprite::create("Image/Combo/Combo_King.png");
	m_pCombo_Normal = CCSprite::create("Image/Combo/Combo_Normal.png");

	m_pCombo_5_or_10->setVisible(false);
	m_pCombo_King->setVisible(false);
	m_pCombo_Normal->setVisible(false);

	m_Combo_5_or_10_Num_PngSize = CCSizeMake(800,110);
	m_Combo_King_Num_PngSize = CCSizeMake(1000,137);
	m_Combo_Normal_PngSize = CCSizeMake(640,86);

	m_pCombo_5_or_10_Num = CCLabelAtlas::create("99","Image/Combo/Combo_5_or_10_Num.png",m_Combo_5_or_10_Num_PngSize.width / 10,m_Combo_5_or_10_Num_PngSize.height,'0');
	m_pCombo_King_Num = CCLabelAtlas::create("0","Image/Combo/Combo_King_Num.png",m_Combo_King_Num_PngSize.width / 10,m_Combo_King_Num_PngSize.height,'0');
	m_pCombo_Normal_Num = CCLabelAtlas::create("0","Image/Combo/Combo_Normal_Num.png",m_Combo_Normal_PngSize.width / 10,m_Combo_Normal_PngSize.height,'0');

	m_pCombo_5_or_10_Num->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pCombo_King_Num->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pCombo_Normal_Num->setAnchorPoint(HS_ANCHOR_CENTER);

	m_pCombo_5_or_10_Num->setVisible(false);
	m_pCombo_King_Num->setVisible(false);
	m_pCombo_Normal_Num->setVisible(false);

	this->addChild(m_pCombo_5_or_10);
	this->addChild(m_pCombo_King);
	this->addChild(m_pCombo_Normal);

	this->addChild(m_pCombo_5_or_10_Num);
	this->addChild(m_pCombo_King_Num);
	this->addChild(m_pCombo_Normal_Num);

	this->schedule(schedule_selector(HSComboManager::Update));
	
	return true;
}

void HSComboManager::Update( float dt )
{
	float comboW = 0.f;
	float numW = 0.f;
	float sumW = 0.f;
	float comboX = 0.f;
	float numX = 0.f;

	CCSprite* comboNode = NULL;
	CCLabelAtlas* comboNumNode = NULL;
	CCSize numPngSize = CCSizeZero;

	if (HS_GAME_CONFIG_DATA()->dribbleCount == 0)
	{
		m_pCombo_5_or_10->setVisible(false);
		m_pCombo_5_or_10_Num->setVisible(false);

		m_pCombo_Normal->setVisible(false);
		m_pCombo_Normal_Num->setVisible(false);

		m_pCombo_King->setVisible(false);
		m_pCombo_King_Num->setVisible(false);

		m_iLastDribbleCount = 0;

		m_isShowCombo = false;
		return;
	}

	m_isShowCombo = true;

	if (HS_GAME_CONFIG_DATA()->isKingEffect == true)
	{
		comboNode = m_pCombo_King;
		comboNumNode = m_pCombo_King_Num;

		numPngSize = m_Combo_King_Num_PngSize;

		m_pCombo_5_or_10->setVisible(false);
		m_pCombo_5_or_10_Num->setVisible(false);

		m_pCombo_Normal->setVisible(false);
		m_pCombo_Normal_Num->setVisible(false);

	}else if (HS_GAME_CONFIG_DATA()->dribbleCount % 5 == 0){

		comboNode = m_pCombo_5_or_10;
		comboNumNode = m_pCombo_5_or_10_Num;

		numPngSize = m_Combo_5_or_10_Num_PngSize;

		m_pCombo_King->setVisible(false);
		m_pCombo_King_Num->setVisible(false);

		m_pCombo_Normal->setVisible(false);
		m_pCombo_Normal_Num->setVisible(false);

	}else if (HS_GAME_CONFIG_DATA()->dribbleCount % 5 != 0){

		comboNode = m_pCombo_Normal;
		comboNumNode = m_pCombo_Normal_Num;

		numPngSize = m_Combo_Normal_PngSize;

		m_pCombo_King->setVisible(false);
		m_pCombo_King_Num->setVisible(false);

		m_pCombo_5_or_10->setVisible(false);
		m_pCombo_5_or_10_Num->setVisible(false);
	}

	comboNode->setVisible(true);
	comboNumNode->setVisible(true);

	comboNumNode->setString(CCString::createWithFormat("%d",HS_GAME_CONFIG_DATA()->dribbleCount + 2)->getCString());

	comboW = comboNode->getContentSize().width;
	numW = comboNumNode->getContentSize().width ;
	sumW = comboW + numW;
	comboX = sumW / 2.f - comboW;
	numX = comboX + comboW / 2.f + numPngSize.width / 10.f;

	comboNode->setPositionX(comboX);

	comboNumNode->setPositionX(numX);

	if (m_iLastDribbleCount != HS_GAME_CONFIG_DATA()->dribbleCount + 2)
	{
		m_iLastDribbleCount = HS_GAME_CONFIG_DATA()->dribbleCount + 2;
		CCActionInterval*  actionBy = CCScaleTo::create(0.1f, 1.4f);
		CCActionInterval*  actionBy2 = CCScaleTo::create(0.1f, 1.f);
		this->runAction(CCSequence::create(actionBy, actionBy2, NULL));
	}
	
}

bool HSComboManager::GetIsShowCombo() const
{
	return m_isShowCombo;
}

int HSComboManager::GetComboCount()
{
	return m_iLastDribbleCount;
}
