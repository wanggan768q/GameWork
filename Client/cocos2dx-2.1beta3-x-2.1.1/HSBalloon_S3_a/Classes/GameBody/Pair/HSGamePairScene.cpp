#include "HSGamePairScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameSelectPropLayer.h"
#include "HSEffect_BlackInk.h"
#include "HSEffect_SickMucus.h"
#include "HSEffect_ColorfulCandy.h"
#include "HSGameDialogLayer.h"
#include "HSGameGuide.h"
#include "HSGameShopLayer.h"

HSAreaType HSGamePairScene::s_areaType;
HSStatus HSGamePairScene::s_status;
int HSGamePairLayer::s_CURRENT_ROOM_ID = 0;

HSGamePairLayer::HSGamePairLayer(void)
{
	m_readyTime = 60;
	//m_readyTime =5;
	m_curMoney = 0;
	m_count=0; 
	m_pGameReadTime = NULL;

	//@ui
	m_pSelfMark = NULL;
	m_pTargetMark = NULL;
	m_pDialog = NULL;
	m_pSelfWinCountTTF = NULL;
	m_pTargetWinCountTTF = NULL;
	m_pSelfLevelTTF = NULL;
	m_pBufferInfoTTF = NULL;


	m_pInfo1Self = NULL;
	m_pInfo2Self = NULL;
	m_pInfo3Self = NULL;
	m_pInfo1Enemy = NULL;
	m_pInfo2Enemy = NULL;
	m_pInfo3Enemy = NULL;

	m_ready = false;
}

HSGamePairLayer::~HSGamePairLayer(void)
{
	m_pGameGold = NULL;
	HSRequest::ShareRequest()->SendSearchUserInfoRequest();	 
}

bool HSGamePairLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
	Load();
	this->setTouchEnabled(true);

	this->setKeypadEnabled(true);

	return true;
}

void HSGamePairLayer::Load()
{
	CCSprite* pBackground = CCSprite::create("Image/pair/normalPair/BEIJING.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);

	HSReadUI::ShareReadUI()->ReadUI("Image/pair/normalPair/normalPair.data","Image/pair/normalPair/",this);
	HS_SET_MENU_TARGET("UI_fh_01",this,HSGamePairLayer::CallReturn);

	HS_SET_MENU_TARGET("UI_Daojuanniu_01",this,HSGamePairLayer::ShowSelectPropLayer);
	HS_SET_MENU_TARGET("UI_Goumaijinbianniu_01",this,HSGamePairLayer::Call_Shop);

	//@ ¡¨ §¥Œ ˝
	int selfSuccessionWinCount = HS_TARGET_SELF().successionwincount();
	int targetSuccessionWinCount = HS_TARGET_TARGET().successionwincount();
	if (selfSuccessionWinCount > 1)
	{
		CCSprite* pSelfWinCountFrame = HS_FIND_UI_PANEL_SPRITE("UI_liansheng1","Shuzidiandikuang");
		m_pSelfWinCountTTF = CCLabelTTF::create(CCString::createWithFormat("%d",selfSuccessionWinCount)->getCString(),HS_FONT_HuaKang,25.f,CCSizeZero,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		m_pSelfWinCountTTF->setAnchorPoint(HS_ANCHOR_R_CENTER);
		m_pSelfWinCountTTF->setPosition(ccp(pSelfWinCountFrame->getContentSize().width - m_pSelfWinCountTTF->getFontSize() / 2.f,pSelfWinCountFrame->getContentSize().height / 2.f));
		pSelfWinCountFrame->addChild(m_pSelfWinCountTTF);
	}
	if (targetSuccessionWinCount > 1)
	{
		CCSprite* pTargetWinCountFrame = HS_FIND_UI_PANEL_SPRITE("UI_liansheng2","Shuzidiandikuang");
		m_pTargetWinCountTTF = CCLabelTTF::create(CCString::createWithFormat("%d",targetSuccessionWinCount)->getCString(),HS_FONT_HuaKang,25.f,CCSizeZero,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		m_pTargetWinCountTTF->setAnchorPoint(HS_ANCHOR_R_CENTER);
		m_pTargetWinCountTTF->setPosition(ccp(pTargetWinCountFrame->getContentSize().width - m_pTargetWinCountTTF->getFontSize() / 2.f,pTargetWinCountFrame->getContentSize().height / 2.f));
		pTargetWinCountFrame->addChild(m_pTargetWinCountTTF);
	}

	//@ µ»º∂
	CCSprite* pLevelFrame = HS_FIND_UI_PANEL_SPRITE("UI_dengjijingyan","Shuzidiandikuang");
	m_pSelfLevelTTF = CCLabelTTF::create(CCString::createWithFormat("Lv.%d",HS_TARGET_SELF().level())->getCString(),HS_FONT_HuaKang,36.f,CCSizeZero,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	m_pSelfLevelTTF->setAnchorPoint(HS_ANCHOR_L_CENTER);
	m_pSelfLevelTTF->setPosition(ccp(0.f,pLevelFrame->getContentSize().height/2.f));
	pLevelFrame->addChild(m_pSelfLevelTTF);

	//@ æ≠—È
	CCSprite* pExperienceFrame = HS_FIND_UI_PANEL_SPRITE("UI_dengjijingyan","jingyantiaozhuose");
	pExperienceFrame->setVisible(false);
	HSCCSprite* pExperienceSprite = HSCCSprite::create(pExperienceFrame->getTexture());
	CCProgressTimer* pEnergyFrameProgress = CCProgressTimer::create(pExperienceSprite);
	pEnergyFrameProgress->setType(kCCProgressTimerTypeBar);
	pEnergyFrameProgress->setMidpoint(ccp(0,0));
	pEnergyFrameProgress->setBarChangeRate(ccp(1, 0));
	pEnergyFrameProgress->setPosition(pExperienceFrame->getPosition());
	pExperienceFrame->getParent()->addChild(pEnergyFrameProgress);
	HSAssert(HS_TARGET_SELF().experience() <= HS_TARGET_SELF().maxexperience(),"experience > maxexperience");
	float progress = (float)HS_TARGET_SELF().experience() / (float)HS_TARGET_SELF().maxexperience() * 100.f;
	pEnergyFrameProgress->setPercentage(progress);


	this->Move();

	if(HSGamePairScene::s_status==status_pair)
	{
		ShowPairInfo();
	}
	else if(HSGamePairScene::s_status==status_again)
	{
		ShowAgainInfo();
	}

	HSCCSprite* gameGoldFrame = HS_FIND_UI_PANEL_SPRITE("UI_Jinbidiandikuang","Jinbidiandikuang");
	CCSize gameGoldFrameSize = gameGoldFrame->getContentSize();
	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
	m_pGameGold = CCLabelAtlas::create("0","Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 11,pMoneyTexture->getPixelsHigh(),'0');
	m_pGameGold->setAnchorPoint(HS_ANCHOR_R_CENTER);
	m_pGameGold->setPosition(ccp(gameGoldFrameSize.width,gameGoldFrameSize.height/2));
	/*m_pGameGold->setScaleX(0.7f);*/
	gameGoldFrame->addChild(m_pGameGold);

	HSCCSprite* readyTimeFrame = HS_FIND_UI_PANEL_SPRITE("UI_Shuzidiandikuang","Shuzidiandikuang");
	CCSize readyTimeFrameSize = readyTimeFrame->getContentSize();
	CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
	m_pGameReadTime = CCLabelAtlas::create("60","Image/moneyNumber.png",pTexture->getPixelsWide() / 11,pTexture->getPixelsHigh(),'0');
	m_pGameReadTime->setPosition(ccp(0,0));
	//m_pGameReadTime->setScaleX(0.7f);
	readyTimeFrame->addChild(m_pGameReadTime);

	
	//CCMenu* duifangtouxiangFrame = HS_FIND_UI_MENU("UI_DUIFANGTOUXIANG_01");
	HS_SET_MENU_TARGET("UI_DUIFANGTOUXIANG_01",this,HSGamePairLayer::CallAddFriend);

	//duifangtouxiangFrame->setVisible(false);

	this->schedule(schedule_selector(HSGamePairLayer::CountReadyTime), 1.f);
	this->schedule(schedule_selector(HSGamePairLayer::Update));
	
	//HS_GAME_CACHE()->m_pFightingProp.clear();



	this->runAction(CCSequence::create(CCCallFunc::create(this,callfunc_selector(HSGamePairLayer::Call_ListerTarget)),NULL));
}

void HSGamePairLayer::Move()
{

	CCNode* selfPanel = HS_FIND_UI_PANEL("UI_Hebingx1");

	CCPoint position =  selfPanel->getPosition();

	selfPanel->setPosition(HSBase::GetTemplateScreenW(),position.y);

	CCActionInterval* action = CCMoveTo::create(0.3f, ccp(position.x,position.y));

	selfPanel->runAction(action);

	CCNode* enemyPanel = HS_FIND_UI_PANEL("UI_Hebingx2");

	CCPoint enemyPosition =  enemyPanel->getPosition();

	enemyPanel->setPosition(-enemyPanel->getContentSize().width,enemyPosition.y);

	CCActionInterval* enemyAction = CCMoveTo::create(0.3f, ccp(enemyPosition.x,enemyPosition.y));
	CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSGamePairLayer::MoveFinish));
	enemyPanel->runAction(CCSequence::create(enemyAction,pCallFunc,NULL));
}

void HSGamePairLayer::MoveFinish()
{
	HS_Play_Sound("hit_effect");

	VSShade();
}
void HSGamePairLayer::VSShade()
{
	//vsΩ•±‰¥Ûœ˚ ß
	CCActionInterval*  actionBy = CCScaleBy::create(0.5f, 2.0f, 2.0f);
	CCFadeTo* fadeTo = CCFadeTo::create(0.5f,0.f);

	CCNode* vsPanel = HS_FIND_UI_PANEL("UI_Vsduizhan");
	CCSprite* vs = CCSprite::create("Image/pair/normalPair/Vsduizhan.png");
	vs->setPosition(ccp(vs->getContentSize().width/2,-vs->getContentSize().height/2));
	vsPanel->addChild(vs,10000);

	vs->runAction(actionBy);
	vs->runAction(fadeTo);
}

void HSGamePairLayer::CountReadyTime(float t)
{
	if(HS_IsRunGameGuide())
	{
		return;
	}

	this->m_readyTime-=1;
	if (m_pGameReadTime)
	{
		m_pGameReadTime->setString(CCString::createWithFormat("%d",m_readyTime)->getCString());
		m_pGameReadTime->setPosition(ccp(0.f,0.f));
	}
	
	if(m_readyTime<=0)
	{
		unschedule(schedule_selector(HSGamePairLayer::CountReadyTime));
		//Return();
	}
}

void HSGamePairLayer::ShowPairInfo()
{
	ShowHead();

	//@selfInfo
	//@winrate
	HSCCSprite* info1FrameSelf = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx1_Shujutiaofanzhuan1","Shujutiaofanzhuan1");
	info1FrameSelf->removeAllChildren();
	CCLabelTTF* info1Self = CCLabelTTF::create(CCString::createWithFormat( L("winRate"),(int)(HS_TARGET_SELF().winrate() * 100.f))->getCString(),HS_FONT_HuaKang,25.f,info1FrameSelf->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	info1Self->setAnchorPoint(HS_ANCHOR_L_CENTER);
	info1Self->setPosition(ccp(0.f,info1FrameSelf->getContentSize().height/2.f));
	info1FrameSelf->addChild(info1Self);
	//@loseCount
	HSCCSprite* info2FrameSelf = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx1_Shujutiaofanzhuan2","Shujutiaofanzhuan2");
	info2FrameSelf->removeAllChildren();
	CCLabelTTF* info2Self = CCLabelTTF::create(CCString::createWithFormat(L("loseNumber"),HS_TARGET_SELF().losecount())->getCString(),HS_FONT_HuaKang,25.f,info2FrameSelf->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	info2Self->setAnchorPoint(HS_ANCHOR_L_CENTER);
	info2Self->setPosition(ccp(0.f,info2FrameSelf->getContentSize().height/2.f));
	info2FrameSelf->addChild(info2Self);
	//@winCount
	HSCCSprite* info3FrameSelf = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx1_Shujutiaofanzhuan3","Shujutiaofanzhuan3");
	info3FrameSelf->removeAllChildren();
	CCLabelTTF* info3Self = CCLabelTTF::create(CCString::createWithFormat(L("winNumber"),HS_TARGET_SELF().wincount())->getCString(),HS_FONT_HuaKang,25.f,info3FrameSelf->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	info3Self->setAnchorPoint(HS_ANCHOR_L_CENTER);
	info3Self->setPosition(ccp(0.f,info3FrameSelf->getContentSize().height/2.f));
	info3FrameSelf->addChild(info3Self);

	

	//@targetInfo
	//@winCount
	HSCCSprite* info1FrameEnemy = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx2_Shujutiao3","Shujutiao3");
	info1FrameEnemy->removeAllChildren();
	CCLabelTTF* info1Enemy = CCLabelTTF::create(CCString::createWithFormat( L("winNumber"),HS_TARGET_TARGET().wincount())->getCString(),HS_FONT_HuaKang,25.f,info1FrameEnemy->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	info1Enemy->setAnchorPoint(HS_ANCHOR_R_CENTER);
	info1Enemy->setPosition(ccp(info1FrameEnemy->getContentSize().width-30.f,info1FrameEnemy->getContentSize().height/2.f));
	info1FrameEnemy->addChild(info1Enemy);
	//@loseCount
	HSCCSprite* info2FrameEnemy = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx2_Shujutiao2","Shujutiao2");
	info2FrameEnemy->removeAllChildren();
	CCLabelTTF* info2Enemy = CCLabelTTF::create(CCString::createWithFormat( L("loseNumber"),HS_TARGET_TARGET().losecount())->getCString(),HS_FONT_HuaKang,25.f,info2FrameEnemy->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	info2Enemy->setAnchorPoint(HS_ANCHOR_R_CENTER);
	info2Enemy->setPosition(ccp(info2FrameEnemy->getContentSize().width-30.f,info2FrameEnemy->getContentSize().height/2.f));
	info2FrameEnemy->addChild(info2Enemy);
	//@winrate
	HSCCSprite* info3FrameEnemy = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx2_Shujutiao1","Shujutiao1");
	info3FrameEnemy->removeAllChildren();
	CCLabelTTF* info3Enemy = CCLabelTTF::create(CCString::createWithFormat( L("winRate"),(int)(HS_TARGET_TARGET().winrate() * 100.f))->getCString(),HS_FONT_HuaKang,25.f,info3FrameEnemy->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	info3Enemy->setAnchorPoint(HS_ANCHOR_R_CENTER);
	info3Enemy->setPosition(ccp(info3FrameEnemy->getContentSize().width-30.f,info3FrameEnemy->getContentSize().height/2.f));
	info3FrameEnemy->addChild(info3Enemy);
	//@win or lose
	HSCCSprite* winSelf = HS_FIND_UI_PANEL_SPRITE("UI_win","WIN");
	int selfSuccessionWinCount = HS_TARGET_SELF().successionwincount();
	if (selfSuccessionWinCount == 0)
	{
		winSelf->setVisible(false);
	}
	
	HSCCSprite* loseSelf = HS_FIND_UI_PANEL_SPRITE("UI_lose","Lose");
	loseSelf->setVisible(false);
	HSCCSprite* winEnemy = HS_FIND_UI_PANEL_SPRITE("UI_win1","WIN");
	winEnemy->setVisible(false);
	HSCCSprite* loseEnemy = HS_FIND_UI_PANEL_SPRITE("UI_lose1","Lose");
	loseEnemy->setVisible(false);
	//@start or again
	
	CCMenu* menuStart = HS_FIND_UI_MENU("UI_ZHUNBEI_11");
	CCMenu* menuAgain = HS_FIND_UI_MENU("UI_ZAILAIYIJU_11");

	menuStart->setVisible(true);
	menuAgain->setVisible(false);

	HS_SET_MENU_TARGET("UI_ZHUNBEI_11",this,HSGamePairLayer::Call_StartGame);
}

void HSGamePairLayer::ShowAgainInfo()
{
	ShowHead();
	//@selfInfo
	//@◊‘º∫ æ≠—È
	HSCCSprite* info1FrameSelf = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx1_Shujutiaofanzhuan1","Shujutiaofanzhuan1");
	if (!m_pInfo1Self)
	{
		m_pInfo1Self = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,info1FrameSelf->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		info1FrameSelf->addChild(m_pInfo1Self);
	}
	m_pInfo1Self->setString(CCString::createWithFormat( L("get experience"),HS_GAME_CACHE()->m_pBattleResult->selfinfo().bureauexperience())->getCString());
	m_pInfo1Self->setAnchorPoint(HS_ANCHOR_L_CENTER);
	m_pInfo1Self->setPosition(ccp(0.f,info1FrameSelf->getContentSize().height/2.f));
	
	//@◊‘º∫  §¬ 
	HSCCSprite* info2FrameSelf = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx1_Shujutiaofanzhuan2","Shujutiaofanzhuan2");
	if (!m_pInfo2Self)
	{
		m_pInfo2Self = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,info2FrameSelf->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		info2FrameSelf->addChild(m_pInfo2Self);
	}
	if (HS_GAME_CACHE()->m_pBattleResult)
	{
		int incomGolds = HS_GAME_CACHE()->m_pBattleResult->selfinfo().incomgolds();
		if (incomGolds > 0)
		{
			m_pInfo2Self->setString(CCString::createWithFormat(L("incomGolds_Win"),HS_GAME_CACHE()->m_pBattleResult->selfinfo().incomgolds())->getCString());
			CCActionInterval*  scale1 = CCScaleBy::create(0.2f, 1.5f, 1.5f);
			CCActionInterval*  scale2 = scale1->reverse();
			m_pInfo2Self->runAction(CCSequence::create(scale1,scale2,NULL));
		}else if(incomGolds < 0){
			m_pInfo2Self->setString(CCString::createWithFormat(L("incomGolds_Lose"),HS_GAME_CACHE()->m_pBattleResult->selfinfo().incomgolds())->getCString());
			CCActionInterval*  scale1 = CCScaleBy::create(0.2f, 1.5f, 1.5f);
			CCActionInterval*  scale2 = scale1->reverse();
			m_pInfo2Self->runAction(CCSequence::create(scale1,scale2,NULL));
		}else{
			m_pInfo2Self->setString(CCString::createWithFormat(L("winRate"),(int)(HS_TARGET_SELF().winrate() * 100.f))->getCString());
		}
		HS_GAME_CACHE()->m_pBattleResult->mutable_selfinfo()->set_incomgolds(0);
	}
	
	m_pInfo2Self->setAnchorPoint(HS_ANCHOR_L_CENTER);
	m_pInfo2Self->setPosition(ccp(0.f,info2FrameSelf->getContentSize().height/2.f));
	
	//@ §¿˚¥Œ ˝
	HSCCSprite* info3FrameSelf = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx1_Shujutiaofanzhuan3","Shujutiaofanzhuan3");
	if (!m_pInfo3Self)
	{
		m_pInfo3Self = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,info3FrameSelf->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		info3FrameSelf->addChild(m_pInfo3Self);		
	}
	m_pInfo3Self->setString(CCString::createWithFormat(L("winNumber"),HS_TARGET_SELF().wincount())->getCString());
	m_pInfo3Self->setAnchorPoint(HS_ANCHOR_L_CENTER);
	m_pInfo3Self->setPosition(ccp(0.f,info3FrameSelf->getContentSize().height/2.f));
	

	//@targetInfo
	//@ §¿˚¥Œ ˝
	HSCCSprite* info1FrameEnemy = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx2_Shujutiao3","Shujutiao3");
	if (!m_pInfo1Enemy)
	{
		m_pInfo1Enemy = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,info1FrameEnemy->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		info1FrameEnemy->addChild(m_pInfo1Enemy);
	}
	m_pInfo1Enemy->setString(CCString::createWithFormat(L("winNumber"),HS_TARGET_SELF().wincount())->getCString());
	m_pInfo1Enemy->setAnchorPoint(HS_ANCHOR_R_CENTER);
	m_pInfo1Enemy->setPosition(ccp(info1FrameEnemy->getContentSize().width-30.f,info1FrameEnemy->getContentSize().height/2.f));
	
	//@ §¬ 
	HSCCSprite* info2FrameEnemy = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx2_Shujutiao2","Shujutiao2");
	if (!m_pInfo2Enemy)
	{
		m_pInfo2Enemy = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,info2FrameEnemy->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		info2FrameEnemy->addChild(m_pInfo2Enemy);
	}
	if (HS_GAME_CACHE()->m_pBattleResult)
	{
		int incomGolds = HS_GAME_CACHE()->m_pBattleResult->tageterinfo().incomgolds();
		if (incomGolds > 0)
		{
			m_pInfo2Enemy->setString(CCString::createWithFormat(L("incomGolds_Win"),incomGolds)->getCString());
			CCActionInterval*  scale1 = CCScaleBy::create(0.2f, 1.5f, 1.5f);
			CCActionInterval*  scale2 = scale1->reverse();
			m_pInfo2Enemy->runAction(CCSequence::create(scale1,scale2,NULL));
		}else if(incomGolds < 0){
			m_pInfo2Enemy->setString(CCString::createWithFormat(L("incomGolds_Lose"),incomGolds)->getCString());
			CCActionInterval*  scale1 = CCScaleBy::create(0.2f, 1.5f, 1.5f);
			CCActionInterval*  scale2 = scale1->reverse();
			m_pInfo2Enemy->runAction(CCSequence::create(scale1,scale2,NULL));
		}else{
			m_pInfo2Enemy->setString(CCString::createWithFormat( L("winRate"),(int)(HS_TARGET_TARGET().winrate() * 100.f))->getCString());
		}
		HS_GAME_CACHE()->m_pBattleResult->mutable_tageterinfo()->set_incomgolds(0);
	}
	
	m_pInfo2Enemy->setAnchorPoint(HS_ANCHOR_R_CENTER);
	m_pInfo2Enemy->setPosition(ccp(info2FrameEnemy->getContentSize().width-30.f,info2FrameEnemy->getContentSize().height/2.f));
	
	//@æ≠—È
	HSCCSprite* info3FrameEnemy = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx2_Shujutiao1","Shujutiao1");
	if (!m_pInfo3Enemy)
	{
		m_pInfo3Enemy = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,info3FrameEnemy->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		info3FrameEnemy->addChild(m_pInfo3Enemy);
	}
	m_pInfo3Enemy->setString(CCString::createWithFormat( L("get experience"),HS_GAME_CACHE()->m_pBattleResult->tageterinfo().bureauexperience())->getCString());
	m_pInfo3Enemy->setAnchorPoint(HS_ANCHOR_R_CENTER);
	m_pInfo3Enemy->setPosition(ccp(info3FrameEnemy->getContentSize().width-30.f,info3FrameEnemy->getContentSize().height/2.f));
	
	//@win or lose
	
	HSCCSprite* winSelf = HS_FIND_UI_PANEL_SPRITE("UI_win","WIN");
	HSCCSprite* loseSelf = HS_FIND_UI_PANEL_SPRITE("UI_lose","Lose");
	winSelf->setVisible(false);
	loseSelf->setVisible(false);

	HSCCSprite* winEnemy = HS_FIND_UI_PANEL_SPRITE("UI_win1","WIN");
	HSCCSprite* loseEnemy = HS_FIND_UI_PANEL_SPRITE("UI_lose1","Lose");
	winEnemy->setVisible(false);
	loseEnemy->setVisible(false);

	if(HS_GAME_CACHE()->m_pBattleResult->result() == BattleResultResponse_PlayerMatchResult_WIN)
	{
		winSelf->setVisible(true);
		loseEnemy->setVisible(false);
	}
	else
	{
		loseSelf->setVisible(false);
		winEnemy->setVisible(true);
	}
	
	
	//@start or again
	CCMenu* menuStart = HS_FIND_UI_MENU("UI_ZHUNBEI_11");
	CCMenu* menuAgain = HS_FIND_UI_MENU("UI_ZAILAIYIJU_11");
	menuStart->setVisible(false);
	menuAgain->setVisible(true);
	HS_SET_MENU_TARGET("UI_ZAILAIYIJU_11",this,HSGamePairLayer::Call_StartGame);
}

void HSGamePairLayer::ShowHead()
{
	//@selfInfo
	//@head
	HSCCSprite* headFrameSelf = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx1_Touxiangkuang","Touxiangkuang");

	const char* selfPath = CCString::createWithFormat("Image/head/%d.png",HS_TARGET_SELF().iconid())->getCString();

	CCSprite* headSelf = CCSprite::create(selfPath);

	headSelf->setAnchorPoint(HS_ANCHOR_CENTER);
	headSelf->setPosition(HS_SizeHalf_Point(headFrameSelf->getContentSize()));

	headFrameSelf->addChild(headSelf,10000);


	m_pSelfMark = CCSprite::create("Image/mask/mask_sickMucus.png");
	m_pSelfMark->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pSelfMark->setPosition(HS_SizeHalf_Point(headFrameSelf->getContentSize()));
	headFrameSelf->addChild(m_pSelfMark,10000);
	m_pSelfMark->setVisible(false);

	//@mask
	/**
	const char* localNameSelf = HS_GAME_CACHE()->GetEffectResName(HS_TARGET_SELF().effect().propid());

	m_pSelfMark = CCSprite::create(CCString::createWithFormat("Image/mask/mask_%s",localNameSelf==NULL?"sickMucus.png":localNameSelf)->getCString());

	m_pSelfMark->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pSelfMark->setPosition(HS_SizeHalf_Point(headFrameSelf->getContentSize()));
	headFrameSelf->addChild(m_pSelfMark,10000);

	if(localNameSelf== NULL)
	{
		m_pSelfMark->setVisible(false);
	}

	//ø™∆Ù◊‘º∫µƒ»´∆¡effect–ßπ˚
	switch (HS_TARGET_SELF().effect().propid())
	{
	case message::PropInfo_EffectPropType_Effect_Unkonw:
		break;
	case message::PropInfo_EffectPropType_Effect_ColorfulCandy:
		HSEffect_ColorfulCandyLayer::create();
		m_pSelfMark->setVisible(false);
		break;
	case message::PropInfo_EffectPropType_Effect_SickMucus:
		HSEffect_SickMucusLayer::create();
		break;
	case message::PropInfo_EffectPropType_Effect_BlackInk:
		HSEffect_BlackInkLayer::create();
		break;
	default:
		break;
	}*/

	//@name
	CCSprite* nameFrameSelf = HS_FIND_UI_PANEL_SPRITE("UI_Mingziditu","Mingziditu");
	CCLabelTTF* nameSelf = CCLabelTTF::create(HS_TARGET_SELF().name().c_str(),HS_FONT_HuaKang,25.f,nameFrameSelf->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	nameSelf->setPosition(ccp(nameFrameSelf->getContentSize().width/2,nameFrameSelf->getContentSize().height/2)); 
	nameFrameSelf->addChild(nameSelf);


	//@targetInfo
	//@head
	HSCCSprite* headFrameEnemy = HS_FIND_UI_PANEL_SPRITE("UI_Hebingx2_Touxiangkuang","Touxiangkuang");

	const char* EnemyPath = CCString::createWithFormat("Image/head/%d.png",HS_TARGET_TARGET().iconid())->getCString();
	CCSprite* headEnemy = CCSprite::create(EnemyPath);
	
	headEnemy->setAnchorPoint(HS_ANCHOR_CENTER);
	headEnemy->setPosition(HS_SizeHalf_Point(headFrameSelf->getContentSize()));
	
	headFrameEnemy->addChild(headEnemy,10000);


	m_pTargetMark = CCSprite::create("Image/mask/mask_sickMucus.png");
	m_pTargetMark->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pTargetMark->setPosition(HS_SizeHalf_Point(headFrameSelf->getContentSize()));
	headFrameEnemy->addChild(m_pTargetMark,10000);
	m_pTargetMark->setVisible(false);

	//@mask
	/**
	const char* localNameTarget = HS_GAME_CACHE()->GetEffectResName(HS_TARGET_TARGET().effect().propid());

	m_pTargetMark = CCSprite::create(CCString::createWithFormat("Image/mask/mask_%s",localNameTarget==NULL?"sickMucus.png":localNameTarget)->getCString());

	m_pTargetMark->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pTargetMark->setPosition(HS_SizeHalf_Point(headFrameSelf->getContentSize()));

	headFrameEnemy->addChild(m_pTargetMark,10000);

	if(localNameTarget== NULL)
	{
		m_pTargetMark->setVisible(false);
	}

	switch (HS_TARGET_TARGET().effect().propid())
	{
	case message::PropInfo_EffectPropType_Effect_Unkonw:
		break;
	case message::PropInfo_EffectPropType_Effect_ColorfulCandy:
		m_pSelfMark->setVisible(false);
		break;
	case message::PropInfo_EffectPropType_Effect_SickMucus:
		break;
	case message::PropInfo_EffectPropType_Effect_BlackInk:
		break;
	default:
		break;
	}*/
	//@name
	CCSprite* nameFrameEnemy = HS_FIND_UI_PANEL_SPRITE("UI_Mingziditu1","Mingziditu");
	
	CCLabelTTF* nameEnemy = CCLabelTTF::create(HS_TARGET_TARGET().name().c_str(),HS_FONT_HuaKang,25.f,nameFrameEnemy->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	
	nameEnemy->setPosition(ccp(nameFrameEnemy->getContentSize().width/2,nameFrameEnemy->getContentSize().height/2)); 
	
	nameFrameEnemy->addChild(nameEnemy);
}

void HSGamePairLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSGamePairLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSGamePairLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGamePairLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGamePairLayer::keyBackClicked()
{
	this->CallReturn(NULL);
}
void HSGamePairLayer::keyMenuClicked()
{

}

void HSGamePairLayer::Update(float dt)
{
	if (m_curMoney != HS_GAME_CACHE()->GetGold())
	{
		m_curMoney = HS_GAME_CACHE()->GetGold();
		m_pGameGold->setString(CCString::createWithFormat("%d",m_curMoney)->getCString());
// 		CCSize gameGoldPngSize = CCSizeMake(320.f,45.f);
// 		m_pGameGold->setPosition(ccp(0.f,0.f));
	}

	UpdateEffect();
}

void HSGamePairLayer::CallReturn(CCObject* obj)
{
	if (HS_IsRunGameGuide())
	{
		HSGameGuide::ShaderGameGuide()->Pause();
		HS_GO_SCENE(HS_SCENE_CoverScene);
		return;
	}
	Return();
}

void HSGamePairLayer::CallAddFriend(CCObject* pobj)
{
	CCNode* pNode = dynamic_cast<CCNode*>(pobj);
	if (pNode)
	{
		pNode->setVisible(false);
		HSRequest::ShareRequest()->SendAddFriendRequest(HS_TARGET_TARGET().uid());
	}
}

void HSGamePairLayer::Return()
{
	if(HS_ONLINE)
	{
		RequestPlayerDisengage();
	}
	else
	{
		HS_GO_SCENE(HS_SCENE_CoverScene);
	}
}

void HSGamePairLayer::ShowSelectPropLayer(CCObject* obj)
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	HSGamePairScene* pairScene = (HSGamePairScene*)scene;
	pairScene->GetHSGameSelectPropLayer()->setVisible(true);
// 	if (!HS_IsRunGameGuide())
// 	{
// 		HSGameSelectPropLayer* layer = pairScene->GetHSGameSelectPropLayer();
// 		if(layer ==NULL)
// 		{
// 			layer = HSGameSelectPropLayer::create();
// 
// 			pairScene->SetHSGameSelectPropLayer(layer);
// 		}
// 		else
// 		{
// 			layer->setVisible(true);
// 		}
// 	}else{
// 		pairScene->GetHSGameSelectPropLayer()->setVisible(true);
// 	}
	
	
	/**
	HSUseBufferLayer* layer = pairScene->GetHSUseBufferLayer();
	if(layer ==NULL)
	{
		layer = HSUseBufferLayer::create();

		pairScene->SetHSUseBufferLayer(layer);
	}
	else
	{
		layer->setVisible(true);
	}*/
	
	/**
	HSBattleOverLayer* layer = pairScene->GetHSBattleOverLayer();
	if(layer == NULL)
	{
		layer = HSBattleOverLayer::create();
		layer->SetIsWin(true);

		pairScene->SetHSBattleOverLayer(layer);
	}
	else
	{
		layer->setVisible(true);
	}*/
	
	 /**
	int yu = m_count%3;
	if(yu==0)
	{
		HSEffect_ColorfulCandyLayer::create();
	}
	else if(yu == 1)
	{
		HSEffect_SickMucusLayer::create();
	}
	else if(yu ==2)
	{
		HSEffect_BlackInkLayer::create();
	}
	
	m_count+=1;*/
	
	//HSEffect_ColorfulCandyLayer::create();
	 //Shake();
	//HSGameDialogLayer* pdialog = HSGameDialogLayer::create();
	//this->addChild(pdialog,10000);
}

void HSGamePairLayer::HideSelectPropLayer()
{
	
}

void HSGamePairLayer::Call_StartGame(CCObject* obj)
{
	if (HS_IsRunGameGuide())
	{
		CCMenuItem* pItem = dynamic_cast<CCMenuItem*>(obj);
		pItem->setEnabled(false);
		HS_GO_SCENE(HS_SCENE_BattleScene);
		return;
	}
	if(!HS_ONLINE)
	{
		HS_GO_SCENE(HS_SCENE_BattleScene);
		return;
	}

	if(m_ready)//»°œ˚◊º±∏
	{

		RequestBattleReady();


		m_ready = false;

		if(m_pDialog)
		{
			m_pDialog->setVisible(false);
		}
	}
	else
	{

		RequestBattleReady();

		if(m_pDialog==NULL)
		{
			m_pDialog = HSGameDialogLayer::create(TYPE_NONO);
			m_pDialog->SetText(L("readyInfo"));
			CCDirector::sharedDirector()->getRunningScene()->addChild(m_pDialog,10000);
		}
		else
		{
			m_pDialog->setVisible(true);
		}
	 
		
		m_ready =true;
	}
	
}

void HSGamePairLayer::Shake()
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	
	HSGamePairScene* pairScene = (HSGamePairScene*)scene;

	CCPoint position =pairScene->getPosition();

	CCMoveTo* left1 = CCMoveTo::create(0.05f,ccp(position.x+5,position.y));
	CCMoveTo* right1 = CCMoveTo::create(0.05f,ccp(position.x-5,position.y));
	CCMoveTo* top1 = CCMoveTo::create(0.05f,ccp(position.x,position.y+5));
	CCMoveTo* rom1 = CCMoveTo::create(0.05f,ccp(position.x,position.y-5));
	CCFiniteTimeAction* action3 = CCSequence::create(left1,right1,top1,rom1,NULL);
	pairScene->runAction(action3);
}

void HSGamePairLayer::UpdateEffect()
{
	if(HS_TARGET_SELF().effect().refrash())
	{
		HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_refrash(false);

		const PropInfo* pProp = HS_GAME_CACHE()->GetPropInfo(HS_TARGET_SELF().effect().propid());

		if(pProp== NULL)
		{
			m_pSelfMark->setVisible(false);
		}
		else
		{
			std::string bufferName =pProp->name();
			CCTexture2D* pNewTexture= NULL;
			switch (pProp->effectproptype())
			{
			case message::PropInfo_EffectPropType_Effect_Unkonw:
				m_pSelfMark->setVisible(false);
				break;
			case message::PropInfo_EffectPropType_Effect_ColorfulCandy:
				m_pSelfMark->setVisible(false);
				HSEffect_ColorfulCandyLayer::create();
				break;
			case message::PropInfo_EffectPropType_Effect_SickMucus:
				HSEffect_SickMucusLayer::create();
				pNewTexture = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("Image/mask/mask_%s",pProp->localname().c_str())->getCString());
				//…Ë÷√◊‘º∫Õ∑œÒ…œµƒ√…∞Ê
				m_pSelfMark->setTexture(pNewTexture);
				m_pSelfMark->setVisible(true);
				//ø™∆Ù◊‘º∫µƒ»´∆¡effect–ßπ˚
				break;
			case message::PropInfo_EffectPropType_Effect_BlackInk:
				HSEffect_BlackInkLayer::create();
				m_pSelfMark->setVisible(false);
				/**
				pNewTexture = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("Image/mask/mask_%s",pProp->localname().c_str())->getCString());
				//…Ë÷√◊‘º∫Õ∑œÒ…œµƒ√…∞Ê
				m_pSelfMark->setTexture(pNewTexture);
				m_pSelfMark->setVisible(true);*/
				//ø™∆Ù◊‘º∫µƒ»´∆¡effect–ßπ˚
				break;
			default:
				break;
			}

			//@ BufferÀµ√˜øÚ
			CCSprite* pBufferInfoFrame = HS_FIND_UI_PANEL_SPRITE("UI_hengfuwenbenkuang","Shuomingdaditu");
			
			CCString* pBufferInfo = CCString::createWithFormat(L("UseBufferInfo2"),HS_TARGET_TARGET().name().c_str(),bufferName.c_str());
			m_pBufferInfoTTF = CCLabelTTF::create(pBufferInfo->getCString(),HS_FONT_HuaKang,36.f,pBufferInfoFrame->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentTop);
			m_pBufferInfoTTF->setAnchorPoint(HS_ANCHOR_CENTER);
			m_pBufferInfoTTF->setPosition(m_pBufferInfoTTF->getAnchorPointInPoints());
			pBufferInfoFrame->addChild(m_pBufferInfoTTF);
			 
		}
	}

	if(HS_TARGET_TARGET().effect().refrash())
	{
		HS_MUTABLE_TARGET_TARGET()->mutable_effect()->set_refrash(false);

		const PropInfo* pProp = HS_GAME_CACHE()->GetPropInfo(HS_TARGET_TARGET().effect().propid());

		if(pProp == NULL)
		{
			m_pTargetMark->setVisible(false);
		}
		else
		{
			std::string bufferName =pProp->name();
			CCTexture2D* pNewTexture= NULL;
			switch (pProp->effectproptype())
			{
			case message::PropInfo_EffectPropType_Effect_Unkonw:
				m_pTargetMark->setVisible(false);
				break;
			case message::PropInfo_EffectPropType_Effect_SickMucus:
				HSEffect_SickMucusLayer::create();
				pNewTexture = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("Image/mask/mask_%s",pProp->localname().c_str())->getCString());
				m_pTargetMark->setTexture(pNewTexture);
				m_pTargetMark->setVisible(true);
				break;
			case message::PropInfo_EffectPropType_Effect_ColorfulCandy:
				m_pTargetMark->setVisible(false);
				HSEffect_ColorfulCandyLayer::create();
				break;
			case message::PropInfo_EffectPropType_Effect_BlackInk:
				HSEffect_BlackInkLayer::create();
				m_pTargetMark->setVisible(false);
				break;
			default:
				break;
			}

			CCSprite* pBufferInfoFrame = HS_FIND_UI_PANEL_SPRITE("UI_hengfuwenbenkuang","Shuomingdaditu");

			CCString* pBufferInfo = CCString::createWithFormat(L("UseBufferInfo1"),HS_TARGET_TARGET().name().c_str(),bufferName.c_str());
			m_pBufferInfoTTF = CCLabelTTF::create(pBufferInfo->getCString(),HS_FONT_HuaKang,36.f,pBufferInfoFrame->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentTop);
			m_pBufferInfoTTF->setAnchorPoint(HS_ANCHOR_CENTER);
			m_pBufferInfoTTF->setPosition(m_pBufferInfoTTF->getAnchorPointInPoints());
			pBufferInfoFrame->addChild(m_pBufferInfoTTF);
		}

		
	}
}

void HSGamePairLayer::RequestBattleReady()
{
	HSRequest::ShareRequest()->SendBattleReadyRequest(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str(),m_ready?BattleReadyRequest_TYPE_ACTION_ACTION_CANCLE:BattleReadyRequest_TYPE_ACTION_ACTION_READY);
}

void HSGamePairLayer::ResponseBattleReady(BattleReadyResponse* responseMsg)
{
	BattleReadyResponse* r = (BattleReadyResponse*)responseMsg;

	if(r->status()==BattleReadyResponse_BattleReadyStatus_OK)
	{
		CCLOG("response HSGamePairLayer::ResponseBattleReady ->BattleReady succces");
	}
	else
	{
		HSMessageBox("Response::BattleReady Fail");
	}
}

void HSGamePairLayer::ResponseStartBattle(NotifyStartBattle* responseMsg)
{
	NotifyStartBattle* r = (NotifyStartBattle*)responseMsg;

	if(r->type()==NotifyStartBattle_NotifyType_START)
	{
		CCLOG("response HSGamePairLayer::ResponseStartBattle ->StartBattle succces");
		HS_GO_SCENE(HS_SCENE_BattleScene);
	}
	else
	{
		 HSMessageBox("Response::StartBattle Fail");
	}
}

void HSGamePairLayer::RequestPlayerDisengage()
{
	HSRequest::ShareRequest()->SendPlayerDisengageRequest(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str());
}

void HSGamePairLayer::ResponsePlayerDisengage(PlayerDisengageResponse* responseMsg)
{
	PlayerDisengageResponse* r = (PlayerDisengageResponse*)responseMsg;

	if(r->status()==PlayerDisengageResponse_DisengageStatus_INITIATIVE)
	{
		HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle)->Closed();
        //HSSocketPool::ShareSocketPool()->Remove(S_L_Battle);
		HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
		HSSocketPool::ShareSocketPool()->SetPingShortLink(true);
		HS_GO_SCENE(HS_SCENE_CoverScene);
	}
	else if(r->status()==PlayerDisengageResponse_DisengageStatus_REACTIVE)
	{
		HS_MUTABLE_TARGET_TARGET()->Clear();
		m_ready = false;

		if(m_pDialog)
		{
			m_pDialog->setVisible(false);
		}
		CCArray* pReadyArray = HS_FIND_UI_MENUITEM_ARRAY_Not_Remove_of_Parent( "UI_ZHUNBEI_11" );
		CCArray* pAgainReadyArray = HS_FIND_UI_MENUITEM_ARRAY_Not_Remove_of_Parent( "UI_ZAILAIYIJU_11" );
		CCObject* pObj = NULL;
		CCARRAY_FOREACH(pReadyArray,pObj)
		{
			CCMenuItemToggle* pItem = dynamic_cast<CCMenuItemToggle*>(pObj);
			if (pItem)
			{
				pItem->setSelectedIndex(0);
			}
		}
		CCARRAY_FOREACH(pAgainReadyArray,pObj)
		{
			CCMenuItemToggle* pItem = dynamic_cast<CCMenuItemToggle*>(pObj);
			if (pItem)
			{
				pItem->setSelectedIndex(0);
			}
		}

		this->runAction(CCSequence::create(CCCallFunc::create(this,callfunc_selector(HSGamePairLayer::Call_ListerTarget)),NULL));
	}
}

void HSGamePairLayer::ResponseTargetInfo( TargetInfoResponse*r )
{
	HS_GAME_CACHE()->m_pTargetInfoResponse->CopyFrom(*r);
	HS_GAME_CACHE()->CopyUser(r->self());

	if(HS_GAME_CACHE()->m_pTargetInfoResponse->status()== TargetInfoResponse_FindStatus_SUCCESS)
	{
		ShowPairInfo();
		this->schedule(schedule_selector(HSGamePairLayer::CountReadyTime), 1.f);
		HSLoadingLayer::ShareLoading()->setVisible(false);
	}else{
		HSMessageBox("Response::TargetInfo fail");
	}
}

void HSGamePairLayer::Call_ListerTarget()
{
	if (!HS_ONLINE)
	{
		return;
	}
	if (HS_IsRunGameGuide())
	{
		return;
	}
	if (!HS_MUTABLE_TARGET_TARGET()->has_uid())
	{
		HSRequest::ShareRequest()->SendTargetInfoRequest(HSGamePairLayer::s_CURRENT_ROOM_ID);
		HSLoadingLayer::ShareLoading()->setVisible(true); 
		this->unschedule(schedule_selector(HSGamePairLayer::CountReadyTime));
		m_readyTime = 60;
	}
}

void HSGamePairLayer::Call_Shop(CCObject* obj)
{
	HSGameShopLayer::SharedShopLayer()->setVisible(true);
}

//scene
HSGamePairScene::HSGamePairScene(void)
{
	this->hsGamePairLayer = NULL;
	this->hsGameAdvancedPairLayer = NULL;
	this->hsGameSelectPropLayer = NULL;
	this->hsUseBufferLayer = NULL;
	this->hsBattleOverLayer = NULL;
}

HSGamePairScene::~HSGamePairScene(void)
{
	this->hsGamePairLayer = NULL;
	this->hsGameAdvancedPairLayer = NULL;
	this->hsGameSelectPropLayer = NULL;
	this->hsUseBufferLayer = NULL;
	this->hsBattleOverLayer = NULL;
}

bool HSGamePairScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->hsGamePairLayer = HSGamePairLayer::create();
	this->addChild(this->hsGamePairLayer,HS_BASE_TAG,HS_BASE_TAG);


// 	if(s_areaType == area_normal)
// 	{
// 		this->hsGamePairLayer = HSGamePairLayer::create();
// 
// 		this->addChild(this->hsGamePairLayer,HS_BASE_TAG,HS_BASE_TAG);
// 	}
// 	else if(s_areaType== area_advanced)
// 	{
// 		this->hsGameAdvancedPairLayer = HSGameAdvancedPairLayer::create();
// 		this->addChild(this->hsGameAdvancedPairLayer,HS_BASE_TAG,HS_BASE_TAG);
// 	}

	if (HS_IsRunGameGuide())
	{
		HSGameGuide::ShaderGameGuide()->Resume(this);
	}

	HSGameSelectPropLayer* layer = this->GetHSGameSelectPropLayer();
	if(layer == NULL)
	{
		layer = HSGameSelectPropLayer::create();
		layer->setVisible(false);
		this->SetHSGameSelectPropLayer(layer);
	}

	return true;
}



