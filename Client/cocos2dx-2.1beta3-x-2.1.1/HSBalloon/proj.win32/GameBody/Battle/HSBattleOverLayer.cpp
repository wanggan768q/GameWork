#include "HSBattleOverLayer.h"
#include "HSGameSceneJumpManage.h"
#include "HSSocketPool.h"
#include "HSRankingListScene.h"
#include "HSBattleScene.h"
#include "HSGameGuide.h"

//Layer
HSBattleOverLayer::HSBattleOverLayer(void)
{
	m_pNo0 = NULL;
	m_pNo1 = NULL;
	m_pNo2 = NULL;
	m_pNo3 = NULL;
	m_pNo4 = NULL;

	m_pGameScoreIcon = NULL;
	m_pGameGoldIcon  = NULL;
	m_pGameTimeIcon  = NULL;

	m_inputLayer = NULL;

	m_fontName = "华康海报体W12(P)";

	m_RankSceneTime = 0;
	m_isRankSceneTimeStart = false;
}

HSBattleOverLayer::~HSBattleOverLayer(void)
{
}

bool HSBattleOverLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);

	Load();
	//this->setTouchEnabled(true);

	//this->setKeypadEnabled(true);

	return true;
}

void HSBattleOverLayer::Load()
{
	HSReadUI::ShareReadUI()->ReadUI("Image/BattleLayer/BattleOverLayer/BattleOverLayer.data","Image/BattleLayer/BattleOverLayer/",this);

	HS_SET_MENU_TARGET("UI_Sangetubiao_zhujiemian",this,HSBattleOverLayer::CallMenu);
	HS_SET_MENU_TARGET("UI_Sangetubiao_KaiShi",this,HSBattleOverLayer::CallPlay);

	HS_SET_MENU_TARGET("UI_Sangetubiao_PaiHang",this,HSBattleOverLayer::CallRanking);
	//CCMenu* rankMenu = HS_FIND_UI_MENU("UI_Sangetubiao_PaiHang");
	//rankMenu->setVisible(false);


	m_pGameScoreIcon = HS_FIND_UI_PANEL_SPRITE("UI_NengLiang","k_NengLiang");
	m_pGameGoldIcon = HS_FIND_UI_PANEL_SPRITE("UI_JinBi","k_JinBi");
// 	m_pGameTimeIcon = HS_FIND_UI_PANEL_SPRITE("UI_ShiJian","j_ShiJian");		//时间暂时不用
// 	m_pGameTimeIcon->setVisible(false);

	m_pGameScore = CCLabelTTF::create("",m_fontName,30.f);
	m_pGameScore->setAnchorPoint(HS_ANCHOR_U_CENTER);
	m_pGameScoreIcon->addChild(m_pGameScore);

	m_pGameGold = CCLabelTTF::create("",m_fontName,30.f);
	m_pGameGold->setAnchorPoint(HS_ANCHOR_U_CENTER);
	m_pGameGoldIcon->addChild(m_pGameGold);
	
	//Show();

	this->schedule(schedule_selector(HSBattleOverLayer::Updata));
}

void HSBattleOverLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
}

bool HSBattleOverLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSBattleOverLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBattleOverLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSBattleOverLayer::keyBackClicked()
{

}
void HSBattleOverLayer::keyMenuClicked()
{

}

void HSBattleOverLayer::Updata( float dt )
{
	if (m_isRankSceneTimeStart)
	{
		if(m_RankSceneTime > 3.f)
		{
			m_isRankSceneTimeStart = false;

			bool isHasData = HS_GAME_CACHE_DATA()->has_worldrankdata();
			if (isHasData)
			{
				HSRankingListLayer::SetRankData((SearchRankResponse*)&HS_GAME_CACHE_DATA()->worldrankdata().data());
				HS_GO_SCENE(HS_SCENE_RankingList);
			}else{
				HSMessageBox("There is no Internet");
			}

		}else{
			m_RankSceneTime += dt;
		}
	}
	
}

void HSBattleOverLayer::CallPlay( CCObject* obj )
{
	HS_GO_SCENE(HS_SCENE_BattleScene);
}

void HSBattleOverLayer::CallMenu( CCObject* obj )
{
	if (HS_GAME_CACHE()->IsRunGameGuide())
	{
		HSGameGuide::ShaderGameGuide()->Pause();
	}
	HS_GO_SCENE(HS_SCENE_BuyProp);
}

void HSBattleOverLayer::CallRanking( CCObject* obj )
{
	HSRequest::ShareRequest()->SendSearchRankRequest();
	m_isRankSceneTimeStart = true;
}

void HSBattleOverLayer::Show( int index,int reviseIndex ,unsigned int score)
{
	CCString* lineId = CCString::createWithFormat("UI_Defen_Blue%d",index);
	HSCCSprite* lineFrame = HS_FIND_UI_PANEL_SPRITE(lineId->getCString(),"j_Blue");

	CCString* info = CCString::createWithFormat("    No.%d                 %d",index + 1,score);

	CCLabelTTF* pTTF = NULL;

	//const char* fontName = "Marker Felt";
	//const char* m_fontName = "华康海报体W12(P)";
	const float fontSize = 30.f;

	switch (index)
	{
	case 0:
		{
			if (!m_pNo0)
			{
				m_pNo0 = CCLabelTTF::create(info->getCString(),m_fontName,fontSize);
				lineFrame->addChild(m_pNo0);
			}
			pTTF = m_pNo0;
		}
		break;
	case 1:
		{
			if (!m_pNo1)
			{
				m_pNo1 = CCLabelTTF::create(info->getCString(),m_fontName,fontSize);
				lineFrame->addChild(m_pNo1);
			}
			pTTF = m_pNo1;
		}
		break;
	case 2:
		{
			if (!m_pNo2)
			{
				m_pNo2 = CCLabelTTF::create(info->getCString(),m_fontName,fontSize);
				lineFrame->addChild(m_pNo2);
			}
			pTTF = m_pNo2;
		}
		break;
	case 3:
		{
			if (!m_pNo3)
			{
				m_pNo3 = CCLabelTTF::create(info->getCString(),m_fontName,fontSize);
				lineFrame->addChild(m_pNo3);
			}
			pTTF = m_pNo3;
		}
		break;
	case 4:
		{
			if (!m_pNo4)
			{
				m_pNo4 = CCLabelTTF::create(info->getCString(),m_fontName,fontSize);
				lineFrame->addChild(m_pNo4);
			}
			pTTF = m_pNo4;
		}
		break;
	default:
		break;
	}

	pTTF->setString(info->getCString());
	CCPoint pos = HS_SizeHalf_Point(pTTF->getContentSize());
	pos.y += lineFrame->getContentSize().height / 2.f;
	pTTF->setAnchorPoint(HS_ANCHOR_U_CENTER);
	pTTF->setPosition(pos);

	if (reviseIndex == index)
	{
		pTTF->setColor(ccc3(0,255,0));
	}
	
}

void HSBattleOverLayer::Show()
{

	if (HS_GAME_CACHE_DATA()->historyfivehighestscorelist_size() == 0)
	{
		HS_GAME_CACHE()->AddHistoryFiveHighestScore(0);
		HS_GAME_CACHE()->AddHistoryFiveHighestScore(0);
		HS_GAME_CACHE()->AddHistoryFiveHighestScore(0);
		HS_GAME_CACHE()->AddHistoryFiveHighestScore(0);
		HS_GAME_CACHE()->AddHistoryFiveHighestScore(0);
	}

	int reviseIndex = HS_GAME_CACHE()->AddHistoryFiveHighestScore(HS_GAME_CONFIG_DATA()->gameScore);


	int count = HS_GAME_CACHE_DATA()->historyfivehighestscorelist_size();
	for (int i = 0;i<count;++i)
	{
		unsigned int score =  HS_GAME_CACHE_DATA()->historyfivehighestscorelist(i);
		this->Show(i,reviseIndex,score);
	}

	if (m_pGameScore)
	{
		CCPoint pos = CCPointZero;
		CCString* score = CCString::createWithFormat("%d",HS_GAME_CONFIG_DATA()->gameScore);
		m_pGameScore->setString(score->getCString());
		pos = HS_SizeHalf_Point(m_pGameScore->getContentSize());
		pos.x += m_pGameScoreIcon->getContentSize().width * 2.f;
		pos.y += m_pGameScoreIcon->getContentSize().height / 2.f;
		m_pGameScore->setPosition(pos);
	}
	if (m_pGameGold)
	{
		CCPoint pos = CCPointZero;
		CCString* gold = CCString::createWithFormat("%d",HS_GAME_CACHE_DATA()->gold());
		m_pGameGold->setString(gold->getCString());
		pos = HS_SizeHalf_Point(m_pGameGold->getContentSize());
		pos.x += m_pGameGoldIcon->getContentSize().width * 2.f;
		pos.y += m_pGameGoldIcon->getContentSize().height / 2.f;
		m_pGameGold->setPosition(pos);
	}
}

void HSBattleOverLayer::setVisible( bool visible )
{
	
	int gameScore = HS_GAME_CONFIG_DATA()->gameScore;
	
	if (visible)
	{
		if (HS_GAME_CACHE_DATA()->uuid() == "")
		{
			
			if (HSSocketPool::ShareSocketPool()->GetSocketWithTag(DEFAULT_SOCKET)->GetSocketStart() == HS_SOCKET_START_CONNECTED && !HS_GAME_CACHE()->IsRunGameGuide())
			{
				CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
				
				if (scene)
				{
					this->m_inputLayer = HSInputDialogLayer::create();
					scene->addChild(m_inputLayer,1010);
				}
			
			}else{
				
				HS_GAME_CACHE()->AddHistoryScore(gameScore);
			}
			
		}else{
			
			if (HSSocketPool::ShareSocketPool()->GetSocketWithTag(DEFAULT_SOCKET)->GetSocketStart() == HS_SOCKET_START_CONNECTED)
			{
				for (int i=0;i<HS_GAME_CACHE_DATA()->historyscorelist_size();++i)
				{
					gameScore += HS_GAME_CACHE_DATA()->historyscorelist(i);
				}

				HSRequest::ShareRequest()->SendCombatGainsRequest(gameScore);
			}
		}
		
		this->Show();
		
	}
	
	CCLayer::setVisible(visible);
	
}

HSInputDialogLayer* HSBattleOverLayer::GetInputLayer()
{
	return m_inputLayer;
}

void HSBattleOverLayer::ResponseSearchRank( SearchRankResponse* pMsg )
{
	//缓存世界排行榜数据
	HS_GAME_CACHE()->SetWorldRankData(pMsg);

	HSRankingListLayer::SetRankData(pMsg);
	HS_GO_SCENE(HS_SCENE_RankingList);
}

void HSBattleOverLayer::LogicOfGameGuide()
{
	if (!HS_GAME_CACHE()->IsRunGameGuide())
	{
		return;
	}
	CCNode* pScene = CCDirector::sharedDirector()->getRunningScene();
	HSGameGuide::ShaderGameGuide()->Resume(pScene);
	HSGameGuide::ShaderGameGuide()->RuntPrevious();

}
