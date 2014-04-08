#include "HSAddressBookScene.h"
#include "HSGameSceneJumpManage.h"
//Layer
HSAddressBookLayer::HSAddressBookLayer(void)
{
	m_pFriendsListView = NULL;
	m_pMoney = NULL;
    m_iMoney = 0;
}

HSAddressBookLayer::~HSAddressBookLayer(void)
{
}

bool HSAddressBookLayer::init()
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

void HSAddressBookLayer::Load()
{
    CCSprite* pBackground = HSCCSprite::create("Image/BEIJING.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/AddressBook.data","Image/",this);

	CCSprite* pMoneyFrame = HS_FIND_UI_PANEL_SPRITE("UI_Jinbidiandikuang","Jinbidiandikuang");
	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
	m_pMoney =  CCLabelAtlas::create("0","Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 11,pMoneyTexture->getPixelsHigh(),'0');
	m_pMoney->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pMoney->setPosition(HS_SizeHalf_Point(pMoneyFrame->getContentSize()));
	pMoneyFrame->addChild(m_pMoney);


	CCSprite* pAddressBookFrame = HS_FIND_UI_PANEL_SPRITE("UI_FriendFrame","gerenxinxilanfanwei");
	m_pFriendsListView = HSAddressBookListVeiw::create(pAddressBookFrame->getContentSize(),CCSizeMake(505,100),HS_GAME_CACHE()->m_AddressBookResponse.namelist_size());
	CCPoint pos = CCPointZero;
	pos.x = -pAddressBookFrame->getContentSize().width / 2.f - 15.f;

	pos.y = pAddressBookFrame->getPosition().y - pAddressBookFrame->getContentSize().height / 2.f - 20.f;
	m_pFriendsListView->setPosition(pos);
	pAddressBookFrame->getParent()->addChild(m_pFriendsListView,1000);
	m_pFriendsListView->reloadData();

	HS_SET_MENU_TARGET("UI_fh_01",this,HSAddressBookLayer::Call_Back);

	HS_SET_MENU_TARGET("UI_Goumaijinbianniu_01",this,HSAddressBookLayer::Call_Shop);

	this->schedule(schedule_selector(HSAddressBookLayer::Updata));
}

void HSAddressBookLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSAddressBookLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSAddressBookLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSAddressBookLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSAddressBookLayer::keyBackClicked()
{

}
void HSAddressBookLayer::keyMenuClicked()
{

}

void HSAddressBookLayer::Updata( float dt )
{
	if (m_iMoney != HS_GAME_CACHE()->GetGold())
	{
		m_iMoney = HS_GAME_CACHE()->GetGold();
        CCString* temp = CCString::createWithFormat("%d",m_iMoney);
		m_pMoney->setString(temp->getCString());
        temp->release();
	}
}

void HSAddressBookLayer::Call_Shop( CCObject* pobj )
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

	HSAddressBookScene* pFriendsSystemScene = (HSAddressBookScene*)scene;

	if(pFriendsSystemScene->GetHSGameShopLayer()==NULL)
	{
		pFriendsSystemScene->SetHSGameShopLayer(HSGameShopLayer::create());
	}
	else
	{
		pFriendsSystemScene->GetHSGameShopLayer()->setVisible(true);
	}
}

void HSAddressBookLayer::Call_Back( CCObject* pObj )
{
	HS_GO_SCENE(HS_SCENE_FriendsSystemScene);
}





//Scene
HSAddressBookScene::HSAddressBookScene(void)
{
	this->hsAddressBookLayer = NULL;
	this->hsGameShopLayer = NULL;
}

HSAddressBookScene::~HSAddressBookScene(void)
{
}

bool HSAddressBookScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->hsAddressBookLayer = HSAddressBookLayer::create();
	this->addChild(this->hsAddressBookLayer,HS_BASE_TAG,HS_BASE_TAG);

	return true;
}










