#include "HSAddressBookScene.h"
#include "HSGameSceneJumpManage.h"
//Layer
HSAddressBookLayer::HSAddressBookLayer(void)
{
	m_pFriendsListView = NULL;
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
    CCSprite* pBackground = HSCCSprite::create("Image/Tongyongbeijing.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/AddressBook.data","Image/",this);

	HS_SET_MENU_TARGET("UI_Tongyongguanbi", this, HSAddressBookLayer::Call_Back);

	CCSprite* pAddressBookFrame = HS_FIND_UI_PANEL_SPRITE("UI_Tongyongfanweilan","Xingxianggenghuanfanwei");
	m_pFriendsListView = HSAddressBookListVeiw::create(pAddressBookFrame->getContentSize(),CCSizeMake(568,96),HS_GAME_CACHE()->m_AddressBookResponse.namelist_size());
	CCPoint pos = CCPointZero;
	pos.y = pAddressBookFrame->getPosition().y - pAddressBookFrame->getContentSize().height / 2.f;
	m_pFriendsListView->setPosition(pos);
	pAddressBookFrame->getParent()->addChild(m_pFriendsListView,1000);
	m_pFriendsListView->reloadData();

	

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
}

void HSAddressBookLayer::Call_Back( CCObject* pObj )
{
	HS_GO_SCENE(HS_SCENE_StartGameScene);
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










