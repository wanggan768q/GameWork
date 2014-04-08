#include "HSFriendsSystemScene.h"
#include "HSGameSceneJumpManage.h"
//Layer
HSFriendsSystemLayer::HSFriendsSystemLayer(void)
{
	m_pFriendsListView = NULL;
	m_pEnemyListView = NULL;
	m_pMoney = NULL;
}

HSFriendsSystemLayer::~HSFriendsSystemLayer(void)
{
}

bool HSFriendsSystemLayer::init()
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

void HSFriendsSystemLayer::Load()
{
	HSReadUI::ShareReadUI()->ReadUI("Image/FriendsSystem/FriendsSystem.data","Image/FriendsSystem/",this);

	CCSprite* pMoneyFrame = HS_FIND_UI_PANEL_SPRITE("UI_Jinbidiandikuang","Jinbidiandikuang");
	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
	m_pMoney =  CCLabelAtlas::create("0","Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 10,pMoneyTexture->getPixelsHigh(),'0');
	m_pMoney->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pMoney->setPosition(HS_SizeHalf_Point(pMoneyFrame->getContentSize()));
	pMoneyFrame->addChild(m_pMoney);


	CCSprite* pFriendFrame = HS_FIND_UI_PANEL_SPRITE("UI_FriendFrame","FriendFrame");
	m_pFriendsListView = HSFriendsListVeiw::create(&HS_GAME_CACHE()->m_FriendInfoResponse.friendlist(),pFriendFrame->getContentSize(),CCSizeMake(505,100));
	CCPoint pos = CCPointZero;
	pos.x = -pFriendFrame->getContentSize().width / 2.f - 15.f;

	pos.y = pFriendFrame->getPosition().y - pFriendFrame->getContentSize().height / 2.f - 20.f;
	m_pFriendsListView->setPosition(pos);
	pFriendFrame->getParent()->addChild(m_pFriendsListView,1000);
	m_pFriendsListView->reloadData();

	m_pEnemyListView = HSFriendsListVeiw::create(&HS_GAME_CACHE()->m_FriendInfoResponse.enemylist(),pFriendFrame->getContentSize(),CCSizeMake(505,100));
	pos.x = -pFriendFrame->getContentSize().width / 2.f - 15.f;
	pos.y = pFriendFrame->getPosition().y - pFriendFrame->getContentSize().height / 2.f - 20.f;
	m_pEnemyListView->setPosition(pos);
	pFriendFrame->getParent()->addChild(m_pEnemyListView,1000);
	m_pEnemyListView->reloadData();
	m_pEnemyListView->setVisible(false);

	HS_SET_MENU_TARGET("UI_haoyoubiaoqian",this,HSFriendsSystemLayer::CallFriend);
	HS_SET_MENU_TARGET("UI_choujiabiaoqian",this,HSFriendsSystemLayer::CallEnemy);
	HS_SET_MENU_TARGET("UI_fh_01",this,HSFriendsSystemLayer::CallBack);

	HS_SET_MENU_TARGET("UI_Goumaijinbianniu_01",this,HSFriendsSystemLayer::CallShop);


	CCArray* pFriendArray = HS_FIND_UI_MENUITEM_ARRAY_Remove_of_Parent("UI_haoyoubiaoqian");
	CCArray* pEnemyArray = HS_FIND_UI_MENUITEM_ARRAY_Remove_of_Parent("UI_choujiabiaoqian");

	HSTableMenu* pMenu = HSTableMenu::create();
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,100000);

	CCObject* pItem = NULL;
	CCARRAY_FOREACH(pFriendArray,pItem)
	{
		CCMenuItem* pItemMenu = dynamic_cast<CCMenuItem*>(pItem);
		if (pItemMenu)
		{
			pMenu->AddItem(pItemMenu);
		}
	}
	pItem = NULL;
	CCARRAY_FOREACH(pEnemyArray,pItem)
	{
		CCMenuItem* pItemMenu = dynamic_cast<CCMenuItem*>(pItem);
		if (pItemMenu)
		{
			pMenu->AddItem(pItemMenu);
		}
	}
	pMenu->SetSelect(0);

	this->schedule(schedule_selector(HSFriendsSystemLayer::Updata));
}

void HSFriendsSystemLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSFriendsSystemLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSFriendsSystemLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSFriendsSystemLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSFriendsSystemLayer::keyBackClicked()
{

}
void HSFriendsSystemLayer::keyMenuClicked()
{

}

void HSFriendsSystemLayer::CallFriend( CCObject* pObj )
{
	if (m_pEnemyListView)
	{
		m_pEnemyListView->setVisible(false);
	}
	if (m_pFriendsListView)
	{
		m_pFriendsListView->setVisible(true);
	}
}

void HSFriendsSystemLayer::CallEnemy( CCObject* pObj )
{
	if (m_pFriendsListView)
	{
		m_pFriendsListView->setVisible(false);
	}
	if (m_pEnemyListView)
	{
		m_pEnemyListView->setVisible(true);
	}
}

void HSFriendsSystemLayer::Updata( float dt )
{
	static int money = 0;
	if (money != HS_GAME_CACHE()->GetGold())
	{
		money = HS_GAME_CACHE()->GetGold();
		m_pMoney->setString(CCString::createWithFormat("%d",money)->getCString());
	}
}

void HSFriendsSystemLayer::CallShop( CCObject* pobj )
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

	HSFriendsSystemScene* pFriendsSystemScene = (HSFriendsSystemScene*)scene;

	if(pFriendsSystemScene->GetHSGameShopLayer()==NULL)
	{
		pFriendsSystemScene->SetHSGameShopLayer(HSGameShopLayer::create());
	}
	else
	{
		pFriendsSystemScene->GetHSGameShopLayer()->setVisible(true);
	}
}

void HSFriendsSystemLayer::CallBack( CCObject* pObj )
{
	HS_GO_SCENE(HS_SCENE_CoverScene);
}





//Scene
HSFriendsSystemScene::HSFriendsSystemScene(void)
{
	this->hsFriendsSystemLayer = NULL;
	this->hsGameShopLayer = NULL;
}

HSFriendsSystemScene::~HSFriendsSystemScene(void)
{
}

bool HSFriendsSystemScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->hsFriendsSystemLayer = HSFriendsSystemLayer::create();
	this->addChild(this->hsFriendsSystemLayer,HS_BASE_TAG,HS_BASE_TAG);

	return true;
}