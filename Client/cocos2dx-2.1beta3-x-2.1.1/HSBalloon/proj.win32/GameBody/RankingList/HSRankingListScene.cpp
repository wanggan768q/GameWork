#include "HSRankingListScene.h"
#include "HSGameSceneJumpManage.h"

SearchRankResponse HSRankingListLayer::m_pRankData;
//Layer
HSRankingListLayer::HSRankingListLayer(void)
{
	m_dt = 0.f;
}

HSRankingListLayer::~HSRankingListLayer(void)
{
	
}

bool HSRankingListLayer::init()
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

void HSRankingListLayer::Load()
{

	HSReadUI::ShareReadUI()->ReadUI("Image/RankingList/RankingList.data","Image/RankingList/",this);

	HS_SET_MENU_TARGET("UI_ZhuJieMian_01",this,HSRankingListLayer::CallMenu);

	this->ShowRank();

}

void HSRankingListLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
}

bool HSRankingListLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSRankingListLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSRankingListLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSRankingListLayer::keyBackClicked()
{

}
void HSRankingListLayer::keyMenuClicked()
{

}

void HSRankingListLayer::ShowRank()
{
	SearchRankResponse* pMsg = &m_pRankData;

	HSCCSprite* worldRankFrame = HS_FIND_UI_PANEL_SPRITE("UI_TouMingKuang","s_TouMingKuang");

	m_pWorldRank = HSRankListView::Create(worldRankFrame->getContentSize(),RankSprite_Bule,worldRankFrame,pMsg);
	this->addChild(m_pWorldRank,1000);
	m_pWorldRank->reloadData();

	HSCCSprite* selfRankFrame = HS_FIND_UI_PANEL_SPRITE("UI_TouMingKuang2","s_TouMingKuang2");
	m_pSelfRank = HSRankListView::Create(selfRankFrame->getContentSize(),RankSprite_Red,selfRankFrame,pMsg);
	this->addChild(m_pSelfRank,1000);
	m_pSelfRank->reloadData();
}

void HSRankingListLayer::CallMenu( CCObject* obj )
{
	HS_GO_SCENE(HS_SCENE_BuyProp);
}

void HSRankingListLayer::Updata( float dt )
{

}

void HSRankingListLayer::SetRankData( SearchRankResponse* pMsg )
{
	m_pRankData.Clear();
	m_pRankData.CopyFrom(*pMsg);
}





//Scene
HSRankingListScene::HSRankingListScene(void)
{
	this->hsRankingListLayer = NULL;
}

HSRankingListScene::~HSRankingListScene(void)
{
}

bool HSRankingListScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->hsRankingListLayer = HSRankingListLayer::create();
	this->addChild(this->hsRankingListLayer,HS_BASE_TAG,HS_BASE_TAG);

	return true;
}