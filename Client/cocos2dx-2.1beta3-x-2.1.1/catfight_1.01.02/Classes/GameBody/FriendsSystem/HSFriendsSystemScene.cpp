#include "HSFriendsSystemScene.h"
#include "HSGameSceneJumpManage.h"
//Layer
HSFriendsSystemLayer::HSFriendsSystemLayer(void)
{
	m_pFriendsListView = NULL;
	m_pMoney = NULL;
    m_iMoney = 0;
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
    CCSprite* pBackground = HSCCSprite::create("Image/BEIJING.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/FriendsSystem.data","Image/",this);

	CCSprite* pMoneyFrame = HS_FIND_UI_PANEL_SPRITE("UI_Jinbidiandikuang","Jinbidiandikuang");
	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
	m_pMoney =  CCLabelAtlas::create("0","Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 11,pMoneyTexture->getPixelsHigh(),'0');
	m_pMoney->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pMoney->setPosition(HS_SizeHalf_Point(pMoneyFrame->getContentSize()));
	pMoneyFrame->addChild(m_pMoney);


	CCSprite* pFriendFrame = HS_FIND_UI_PANEL_SPRITE("UI_FriendFrame","gerenxinxilanfanwei");
	m_pFriendsListView = HSFriendsListVeiw::create(pFriendFrame->getContentSize(),CCSizeMake(505,100),HS_GAME_CACHE()->m_FriendListResponse.friendlist_size());
	CCPoint pos = CCPointZero;
	pos.x = -pFriendFrame->getContentSize().width / 2.f - 15.f;

	pos.y = pFriendFrame->getPosition().y - pFriendFrame->getContentSize().height / 2.f - 20.f;
	m_pFriendsListView->setPosition(pos);
	pFriendFrame->getParent()->addChild(m_pFriendsListView,1000);
	m_pFriendsListView->reloadData();

	HS_SET_MENU_TARGET("UI_fh_01",this,HSFriendsSystemLayer::Call_Back);

	HS_SET_MENU_TARGET("UI_Goumaijinbianniu_01",this,HSFriendsSystemLayer::Call_Shop);
    
    HS_SET_MENU_TARGET("UI_yaoqinghaoyou", this, HSFriendsSystemLayer::Call_AddressBook);
    
    HS_SET_MENU_TARGET("UI_FriendFrame_youjiananniu", this, HSFriendsSystemLayer::Call_Email);
    
    CCNode* pNode = HS_FIND_UI_PANEL("UI_FriendFrame_youjianjiaobiao");
    if (HS_GAME_CACHE()->m_EmailResponse.emaillist_size() == 0)
    {
        pNode->setVisible(false);
    }
    else
    {
        pNode->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleBy::create(0.7f, 1.3f),                                                                              CCScaleTo::create(1.f, 1.f))));
    }
    

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

void HSFriendsSystemLayer::Updata( float dt )
{
	if (m_iMoney != HS_GAME_CACHE()->GetGold())
	{
		m_iMoney = HS_GAME_CACHE()->GetGold();
        CCString* tempMoney = CCString::createWithFormat("%d",m_iMoney);
		m_pMoney->setString(tempMoney->getCString());
        tempMoney->release();
	}
}

void HSFriendsSystemLayer::Call_AddressBook(CCObject* pObj)
{
    HSRequest::ShareRequest()->SendAddressBookRequest();
}

void HSFriendsSystemLayer::Call_Email(CCObject* pObj)
{
    HSRequest::ShareRequest()->SendEmailRequest();
}

void HSFriendsSystemLayer::ResponseEmail(EmailResponse* pMsg)
{
    HS_GO_SCENE(HS_SCENE_EmailSystemScene);
}

void HSFriendsSystemLayer::ResponseAddressBook(AddressBookResponse* pMsg)
{
    HS_GO_SCENE(HS_SCENE_AddressBookScene);
}

void HSFriendsSystemLayer::Call_Shop( CCObject* pobj )
{
//	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
//
//	HSFriendsSystemScene* pFriendsSystemScene = (HSFriendsSystemScene*)scene;
//
//	if(pFriendsSystemScene->GetHSGameShopLayer()==NULL)
//	{
//		pFriendsSystemScene->SetHSGameShopLayer(HSGameShopLayer::create());
//	}
//	else
//	{
//		pFriendsSystemScene->GetHSGameShopLayer()->setVisible(true);
//	}
	HS_GO_SCENE(HS_SCENE_SHOPSCENE);
}

void HSFriendsSystemLayer::Call_Back( CCObject* pObj )
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
