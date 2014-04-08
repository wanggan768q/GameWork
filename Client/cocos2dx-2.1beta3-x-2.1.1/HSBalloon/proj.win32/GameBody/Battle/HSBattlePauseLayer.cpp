#include "HSBattlePauseLayer.h"
#include "HSBattleScene.h"

//Layer
HSBattlePauseLayer::HSBattlePauseLayer(void)
{
	m_pFirstLine = NULL;
	m_pSecondLine = NULL;
	m_pThirdLine = NULL;
	m_pFourthLine = NULL;
	m_pFifthLine = NULL;
	m_pMaxHighestScoreLable = NULL;
}

HSBattlePauseLayer::~HSBattlePauseLayer(void)
{
}

bool HSBattlePauseLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);

	this->Load();
	//this->setTouchEnabled(true);

	//this->setKeypadEnabled(true);

	return true;
}

void HSBattlePauseLayer::Load()
{
	HSReadUI::ShareReadUI()->ReadUI("Image/BattleLayer/BattlePauseLayer/BattlePauseLayer.data","Image/BattleLayer/BattlePauseLayer/",this);

	int baseZ = 1000;

	m_pHighestScoreFrame = HS_FIND_UI_PANEL_SPRITE("UI_ZuiGaoFen_ZuiGaoKuang","z_ZuiGaoKuang");
	CCSize highestScoreFrameSize = m_pHighestScoreFrame->getContentSize();
	CCSize highestScoreNumPngSize = CCSizeMake(250,30);
	m_pMaxHighestScoreLable = CCLabelAtlas::create("0","Image/GameScore.png",highestScoreNumPngSize.width / 10.f,highestScoreNumPngSize.height,'0');
	m_pMaxHighestScoreLable->setAnchorPoint(ccp(0.5f,0.5f));
	//m_pMaxHighestScoreLable->setAnchorPoint(HS_ANCHOR_U_CENTER);
	m_pMaxHighestScoreLable->setPosition(HS_SizeHalf_Point(m_pHighestScoreFrame->getContentSize()));
	m_pHighestScoreFrame->addChild(m_pMaxHighestScoreLable);

	HSCCSprite* currentRankFrame = HS_FIND_UI_PANEL_SPRITE("UI_PaiMingShuZiTiao_PaiMingShuZiTiao","z_PaiMingShuZiTiao");
	m_pCurrentRank = CCLabelTTF::create("0","",30.f);
	m_pCurrentRank->setPosition(HS_SizeHalf_Point(currentRankFrame->getContentSize()));
	currentRankFrame->addChild(m_pCurrentRank);


	HS_SET_MENU_TARGET("UI_ZanTingKuang_ZanTing",this,HSBattlePauseLayer::CallPlay);

	HS_SET_MENU_TARGET("UI_GuanYu_01",this,HSBattlePauseLayer::CallAboutMenu);

	HS_SET_MENU_TARGET("UI_YinXiao_11",this,HSBattlePauseLayer::CallSoundEffectMenu);

	HS_SET_MENU_TARGET("UI_YinYue_11",this,HSBattlePauseLayer::CallMusicMenu);
	
	bool isPlayMusic = HS_GAME_CACHE_DATA()->isbackgroundmusic();
	bool isPlaySoundEffect= HS_GAME_CACHE_DATA()->issound();

	if (!isPlayMusic)
	{
		CCMenu* musicMenu = HS_FIND_UI_MENU("UI_YinYue_11");
		CCArray* array = musicMenu->getChildren();
		CCObject* obj = array->objectAtIndex(0);
		CCMenuItemToggle* toggle = dynamic_cast<CCMenuItemToggle*>(obj);
		toggle->setSelectedIndex(1);

		HSSoundManage::ShareSoundManage()->SetIsPlayMusic(false);
	}
	if (!isPlaySoundEffect)
	{
		CCMenu* musicMenu = HS_FIND_UI_MENU("UI_YinXiao_11");
		CCArray* array = musicMenu->getChildren();
		CCObject* obj = array->objectAtIndex(0);
		CCMenuItemToggle* toggle = dynamic_cast<CCMenuItemToggle*>(obj);
		toggle->setSelectedIndex(1);
		HSSoundManage::ShareSoundManage()->SetIsPlayEffect(false);
	}

// 	HS_GAME_CACHE()->AddFiveDayScore(200);
// 	HS_GAME_CACHE()->AddFiveDayScore(200);
// 	HS_GAME_CACHE()->AddFiveDayScore(200);
// 	HS_GAME_CACHE()->AddFiveDayScore(200);
// 	HS_GAME_CACHE()->AddFiveDayScore(200);
// 
// 	HS_GAME_CACHE()->AddFiveDayScore(300);
// 	HS_GAME_CACHE()->AddFiveDayScore(200);
// 	HS_GAME_CACHE()->AddFiveDayScore(200);

	ShowTendMap();

	this->schedule(schedule_selector(HSBattlePauseLayer::Updata));
}

void HSBattlePauseLayer::CallAboutMenu( CCObject* obj )
{
}

void HSBattlePauseLayer::CallMusicMenu( CCObject* obj )
{
	HSSoundManage::ShareSoundManage()->PlayerEffect("botton");

	bool isPlayMusic = HS_GAME_CACHE_DATA()->isbackgroundmusic();
	HS_GAME_CACHE()->SetIsOpenBackgroundMusic(!isPlayMusic);

	HSSoundManage::ShareSoundManage()->SetIsPlayMusic(!isPlayMusic);
}

void HSBattlePauseLayer::CallSoundEffectMenu( CCObject* obj )
{
	HSSoundManage::ShareSoundManage()->PlayerEffect("botton");

	bool isPlaySoundEffect= HS_GAME_CACHE_DATA()->issound();
	HS_GAME_CACHE()->SetIsOpenIsSound(!isPlaySoundEffect);
	HSSoundManage::ShareSoundManage()->SetIsPlayEffect(!isPlaySoundEffect);
}

void HSBattlePauseLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , false);
}

bool HSBattlePauseLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSBattlePauseLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBattlePauseLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBattlePauseLayer::keyBackClicked()
{

}
void HSBattlePauseLayer::keyMenuClicked()
{

}

void HSBattlePauseLayer::ShowTendMap()
{
	CCNode* first = HS_FIND_UI_PANEL("UI_DeFenQuShiZu_QuYuTouMingKuang0");
	CCNode* second = HS_FIND_UI_PANEL("UI_DeFenQuShiZu_QuYuTouMingKuang1");
	CCNode* third = HS_FIND_UI_PANEL("UI_DeFenQuShiZu_QuYuTouMingKuang2");
	CCNode* fourth = HS_FIND_UI_PANEL("UI_DeFenQuShiZu_QuYuTouMingKuang3");
	CCNode* fifth = HS_FIND_UI_PANEL("UI_DeFenQuShiZu_QuYuTouMingKuang4");

	HSCCSprite* panel = HS_FIND_UI_PANEL_SPRITE("UI_DeFenQuShiZu_QuYuTouMingKuang0","z_QuYuTouMingKuang");

	if (m_pFirstLine == NULL)
	{

		m_pFirstLine = CCSprite::create("Image/BattleLayer/BattlePauseLayer/z_DeFenXian.png");
		m_pSecondLine = CCSprite::create("Image/BattleLayer/BattlePauseLayer/z_DeFenXian.png");
		m_pThirdLine = CCSprite::create("Image/BattleLayer/BattlePauseLayer/z_DeFenXian.png");
		m_pFourthLine = CCSprite::create("Image/BattleLayer/BattlePauseLayer/z_DeFenXian.png");
		m_pFifthLine = CCSprite::create("Image/BattleLayer/BattlePauseLayer/z_DeFenXian.png");

		m_pFirstLine->getTexture()->setAntiAliasTexParameters();
		m_pSecondLine->getTexture()->setAntiAliasTexParameters();
		m_pThirdLine->getTexture()->setAntiAliasTexParameters();
		m_pFourthLine->getTexture()->setAntiAliasTexParameters();
		m_pFifthLine->getTexture()->setAntiAliasTexParameters();

		m_pFirstLine->setAnchorPoint(HS_ANCHOR_LD);
		m_pSecondLine->setAnchorPoint(HS_ANCHOR_LD);
		m_pThirdLine->setAnchorPoint(HS_ANCHOR_LD);
		m_pFourthLine->setAnchorPoint(HS_ANCHOR_LD);
		m_pFifthLine->setAnchorPoint(HS_ANCHOR_LD);


		m_pFirstLine->setPosition(first->getPosition());
		m_pSecondLine->setPosition(second->getPosition());
		m_pThirdLine->setPosition(third->getPosition());
		m_pFourthLine->setPosition(fourth->getPosition());
		m_pFifthLine->setPosition(fifth->getPosition());

		m_pFirstLine->setVisible(false);
		m_pSecondLine->setVisible(false);
		m_pThirdLine->setVisible(false);
		m_pFourthLine->setVisible(false);
		m_pFifthLine->setVisible(false);

		m_pFirstLinePoint = CCSprite::create("Image/BattleLayer/BattlePauseLayer/z_DeFenDian.png");
		m_pSecondLinePoint = CCSprite::create("Image/BattleLayer/BattlePauseLayer/z_DeFenDian.png");
		m_pThirdLinePoint = CCSprite::create("Image/BattleLayer/BattlePauseLayer/z_DeFenDian.png");
		m_pFourthLinePoint = CCSprite::create("Image/BattleLayer/BattlePauseLayer/z_DeFenDian.png");
		m_pFifthLinePoint = CCSprite::create("Image/BattleLayer/BattlePauseLayer/z_DeFenDian.png");

		m_pFirstLinePoint->setVisible(false);
		m_pSecondLinePoint->setVisible(false);
		m_pThirdLinePoint->setVisible(false);
		m_pFourthLinePoint->setVisible(false);
		m_pFifthLinePoint->setVisible(false);

		CCNode* p = first->getParent();
		p->addChild(m_pFirstLine,1000);
		p->addChild(m_pSecondLine,1000);
		p->addChild(m_pThirdLine,1000);
		p->addChild(m_pFourthLine,1000);
		p->addChild(m_pFifthLine,1000);

		p->addChild(m_pFirstLinePoint,1000);
		p->addChild(m_pSecondLinePoint,1000);
		p->addChild(m_pThirdLinePoint,1000);
		p->addChild(m_pFourthLinePoint,1000);
		p->addChild(m_pFifthLinePoint,1000);
	}else{
		return;
	}
	GameCacheData* gameCacheData = HS_MUTABLE_GAME_CACHE_DATA();
	unsigned long long maxScore = 0;
	int dayCount = gameCacheData->fivedayscorelist_size();
	for (int i=0;i<dayCount;++i)
	{
		maxScore < gameCacheData->fivedayscorelist(i).score() ? maxScore = gameCacheData->fivedayscorelist(i).score() : 0;
	}

	float unitH = (float)(maxScore + 0) / (panel->getTexture()->getPixelsHigh() - 25.f);

	//
	for (int i=0;i<dayCount;++i)
	{
		float h = (float)gameCacheData->fivedayscorelist(i).score() / unitH;

		CCPoint pos = CCPointZero;
		
		CCNode* pLine = NULL;
		CCNode* pLinePoint = NULL;
		switch ( i )
		{
		case 0:
			{
				pLine = m_pFirstLine;
				pLinePoint = m_pFirstLinePoint;
			}
			break;
		case 1:
			{
				pLine = m_pSecondLine;
				pLinePoint = m_pSecondLinePoint;
			}
			break;
		case 2:
			{
				pLine = m_pThirdLine;
				pLinePoint = m_pThirdLinePoint;
			}
			break;
		case 3:
			{
				pLine = m_pFourthLine;
				pLinePoint = m_pFourthLinePoint;
			}
			break;
		case 4:
			{
				pLine = m_pFifthLine;
				pLinePoint = m_pFifthLinePoint;
			}
			break;
		default:
			break;
		}

		if (pLine == NULL)
		{
			break;
		}
		pos = pLine->getPosition();

		pos.x += panel->getTexture()->getPixelsWide() / 2.f;
		pos.y -= panel->getTexture()->getPixelsHigh();

		pos.y += h;
		if (i != dayCount - 1)
		{
			pLine->setVisible(true);
		}
		pLine->setPosition(pos);

		pos.y += pLinePoint->getContentSize().height / 2.f;
		pLinePoint->setPosition(pos);
		pLinePoint->setVisible(true);
		
	}

	// Line.1
	float scaleX = HSMath::Sqrt(m_pFirstLine->getPosition(),m_pSecondLine->getPosition()) / m_pFirstLine->getContentSize().width;
	float rotation = HSMath::Angle(m_pFirstLine->getPosition(),m_pSecondLine->getPosition());
	m_pFirstLine->setScaleX(scaleX);
	m_pFirstLine->setRotation(rotation);

	// Line.2
	scaleX = HSMath::Sqrt(m_pSecondLine->getPosition(),m_pThirdLine->getPosition()) / m_pSecondLine->getContentSize().width;
	rotation = HSMath::Angle(m_pSecondLine->getPosition(),m_pThirdLine->getPosition());
	m_pSecondLine->setScaleX(scaleX);
	m_pSecondLine->setRotation(rotation);

	// Line.3
	scaleX = HSMath::Sqrt(m_pThirdLine->getPosition(),m_pFourthLine->getPosition()) / m_pThirdLine->getContentSize().width;
	rotation = HSMath::Angle(m_pThirdLine->getPosition(),m_pFourthLine->getPosition());
	m_pThirdLine->setScaleX(scaleX);
	m_pThirdLine->setRotation(rotation);

	// Line.4
	scaleX = HSMath::Sqrt(m_pFourthLine->getPosition(),m_pFifthLine->getPosition()) / m_pFourthLine->getContentSize().width;
	rotation = HSMath::Angle(m_pFourthLine->getPosition(),m_pFifthLine->getPosition());
	m_pFourthLine->setScaleX(scaleX);
	m_pFourthLine->setRotation(rotation);

	// Line.5
	m_pFifthLine->setVisible(false);

}

void HSBattlePauseLayer::Updata( float dt )
{
	
}

void HSBattlePauseLayer::CallPlay( CCObject* obj )
{
	this->setVisible(false);

	HSBattleScene* pScene = dynamic_cast<HSBattleScene*>(CCDirector::sharedDirector()->getRunningScene());
	if (pScene)
	{
		pScene->GetHSBattleLayer()->Resume();
	}
}

void HSBattlePauseLayer::ResponseSearchRank( SearchRankResponse* pMsg )
{
	CCString* str = CCString::createWithFormat("%d",pMsg->selfrank());
	m_pCurrentRank->setString(str->getCString());
	m_pCurrentRank->setPosition(HS_SizeHalf_Point(m_pCurrentRank->getContentSize()));
}

void HSBattlePauseLayer::setVisible( bool visible )
{
	if (visible)
	{
		if (m_pMaxHighestScoreLable)
		{
			int maxHighestScore = HS_GAME_CACHE_DATA()->maxhighestscore();
			CCString* str = CCString::createWithFormat("%d",maxHighestScore);
			m_pMaxHighestScoreLable->setString(str->getCString());
			CCPoint pos = HS_SizeHalf_Point(m_pHighestScoreFrame->getContentSize());
			m_pMaxHighestScoreLable->setPosition(pos);
		}

		this->ShowTendMap();
	}
	CCLayer::setVisible(visible);
}
