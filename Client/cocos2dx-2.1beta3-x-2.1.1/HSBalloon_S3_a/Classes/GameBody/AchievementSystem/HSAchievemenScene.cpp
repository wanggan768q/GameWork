#include "HSAchievemenScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameShopLayer.h"

//Layer
HSAchievemenLayer::HSAchievemenLayer(void)
{
	m_money = 0;
	m_HaveReceiveNum = 0;
	m_pFinishNumTTF = NULL;
}

HSAchievemenLayer::~HSAchievemenLayer(void)
{
}

bool HSAchievemenLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);

	this->Load();
	//this->setIsTouchEnabled(true);

	//this->setIsKeypadEnabled(true);

	return true;
}

void HSAchievemenLayer::Load()
{
	HSReadUI::ShareReadUI()->ReadUI("Image/AchievementSystem/AchievementSystem.data","Image/AchievementSystem/",this);

	CCSprite* pBj = HS_FIND_UI_PANEL_SPRITE("UI_bj","BEIJING");
	CCSprite* pNewBj = CCSprite::createWithTexture(pBj->getTexture());
	pNewBj->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pNewBj);
	HSTool::SetNodeFilldScreen(pNewBj);
	this->removeChild(HS_FIND_UI_PANEL("UI_bj"));

	CCSprite* pMoneyFrame = HS_FIND_UI_PANEL_SPRITE("UI_Jinbidiandikuang","Jinbidiandikuang");
	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
	m_pMoney =  CCLabelAtlas::create("0","Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 11,pMoneyTexture->getPixelsHigh(),'0');
	m_pMoney->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pMoney->setPosition(HS_SizeHalf_Point(pMoneyFrame->getContentSize()));
	pMoneyFrame->addChild(m_pMoney);

	CCSprite* pAchievemenFrame = HS_FIND_UI_PANEL_SPRITE("UI_gerenxinxilanfanwei","gerenxinxilanfanwei");
	m_pAchievemenListView = HSAchievemenListView::create(&HS_GAME_CACHE()->m_AchievementResponse,pAchievemenFrame->getContentSize(),CCSizeMake(520.f,91.f + 30.f),HS_GAME_CACHE()->m_AchievementResponse.achievementlist_size());
	CCPoint pos = CCPointZero;
	pos.x = -pAchievemenFrame->getContentSize().width / 2.f + 20.f;
	pos.y = pAchievemenFrame->getPosition().y - pAchievemenFrame->getContentSize().height / 2.f;
	m_pAchievemenListView->setPosition(pos);
	pAchievemenFrame->getParent()->addChild(m_pAchievemenListView,1000);
	m_pAchievemenListView->reloadData();


	for (int i=0;i<HS_GAME_CACHE()->m_AchievementResponse.achievementlist_size();++i)
	{
		if (HS_GAME_CACHE()->m_AchievementResponse.achievementlist(i).state() == AchievementResponse_AchievemenStateInfo_State_State_Have_Receive)
		{
			m_HaveReceiveNum++;
		}
	}

	CCSprite* pFinishNum = HS_FIND_UI_PANEL_SPRITE("UI_Wanjiamingzikuang","Wanjiamingzikuang");
	m_pFinishNumTTF = CCLabelTTF::create(CCString::createWithFormat("%d / %d",m_HaveReceiveNum,HS_GAME_CACHE()->m_AchievementResponse.achievementlist_size())->getCString(),HS_FONT_HuaKang,36.f);
	m_pFinishNumTTF->setPosition(pFinishNum->getAnchorPointInPoints());
	pFinishNum->addChild(m_pFinishNumTTF);


	HS_SET_MENU_TARGET("UI_fh_01",this,HSAchievemenLayer::Call_Back);
	HS_SET_MENU_TARGET("UI_Goumaijinbianniu_01",this,HSAchievemenLayer::Call_Shop);
	this->schedule(schedule_selector(HSAchievemenLayer::Updata));
}

void HSAchievemenLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSAchievemenLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSAchievemenLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSAchievemenLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSAchievemenLayer::keyBackClicked()
{

}
void HSAchievemenLayer::keyMenuClicked()
{

}

void HSAchievemenLayer::Updata( float dt )
{
	if (m_money != HS_GAME_CACHE()->GetGold())
	{
		m_money = HS_GAME_CACHE()->GetGold();
		m_pMoney->setString(CCString::createWithFormat("%d",m_money)->getCString());
	}

	static int s_haveReceive = 0;
	if (s_haveReceive != m_HaveReceiveNum)
	{
		s_haveReceive = m_HaveReceiveNum;
		m_pFinishNumTTF->setString(CCString::createWithFormat("%d / %d",m_HaveReceiveNum,HS_GAME_CACHE()->m_AchievementResponse.achievementlist_size())->getCString());
	}
}

void HSAchievemenLayer::Call_Back( CCObject* pObj )
{
	HS_GO_SCENE(HS_SCENE_CoverScene);
}

void HSAchievemenLayer::Call_Shop( CCObject* pobj )
{
	HSGameShopLayer::SharedShopLayer()->setVisible(true);
}

int& HSAchievemenLayer::GetHaveReceiveNum()
{
	return m_HaveReceiveNum;
}





//Scene
HSAchievemenScene::HSAchievemenScene(void)
{
	this->hsAchievemenLayer = NULL;
}

HSAchievemenScene::~HSAchievemenScene(void)
{
}

bool HSAchievemenScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->hsAchievemenLayer = HSAchievemenLayer::create();
	this->addChild(this->hsAchievemenLayer,HS_BASE_TAG,HS_BASE_TAG);

	return true;
}