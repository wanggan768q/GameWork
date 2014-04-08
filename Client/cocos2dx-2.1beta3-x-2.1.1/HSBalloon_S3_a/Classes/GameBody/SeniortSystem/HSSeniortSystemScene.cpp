#include "HSSeniortSystemScene.h"
#include "HSGameSceneJumpManage.h"

//Layer
HSSeniortSystemLayer::HSSeniortSystemLayer(void)
{
	
}

HSSeniortSystemLayer::~HSSeniortSystemLayer(void)
{
}

bool HSSeniortSystemLayer::init()
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

void HSSeniortSystemLayer::Load()
{
	CCSprite* pBackground = CCSprite::create("Image/SelectChannel/xuanzepindaodiban.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);

	HSReadUI::ShareReadUI()->ReadUI("Image/SelectChannel/SelectChannel.data","Image/SelectChannel/",this);

	HS_SET_MENU_TARGET("UI_fh_01",this,HSSeniortSystemLayer::CallBack);
	HS_SET_MENU_TARGET("UI_Goumaijinbianniu_01",this,HSSeniortSystemLayer::CallShop);

	CCSprite* pMoneyFrame = HS_FIND_UI_PANEL_SPRITE("UI_Jinbidiandikuang","Jinbidiandikuang");
	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
	m_pMoney =  CCLabelAtlas::create("0","Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 11,pMoneyTexture->getPixelsHigh(),'0');
	m_pMoney->setAnchorPoint(HS_ANCHOR_CENTER);
	m_pMoney->setPosition(HS_SizeHalf_Point(pMoneyFrame->getContentSize()));
	pMoneyFrame->addChild(m_pMoney);

	CCNode *pNode = CCNode::create();
	pNode->setContentSize(CCSizeMake(544,862));
	//pNode->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pNode,2000);
	HSRoomListView* pRoomListView = HSRoomListView::create(CCSizeMake(544,862),CCSizeMake(544,250),HS_GAME_CACHE()->m_RoomDataResponse.roomlist_size());
	pRoomListView->setPosition(ccp(45,0));
	pNode->addChild(pRoomListView);
	pRoomListView->reloadData();
// 	HSRoomListView* pRoomListView = HSRoomListView::create(CCSizeMake(544,862),CCSizeMake(544,187),HS_GAME_CACHE()->m_RoomDataResponse.roomlist_size());
// 	pRoomListView->setPosition(ccp(45,0));
// 	this->addChild(pRoomListView);
// 	pRoomListView->reloadData();
	
	this->schedule(schedule_selector(HSSeniortSystemLayer::Updata));
}

void HSSeniortSystemLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSSeniortSystemLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSSeniortSystemLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSSeniortSystemLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSSeniortSystemLayer::keyBackClicked()
{

}
void HSSeniortSystemLayer::keyMenuClicked()
{

}

void HSSeniortSystemLayer::ResponseFighting( FightingResponse*r )
{
	FightingResponse_RequestStatus status = r->status();
	if(status ==FightingResponse_RequestStatus_SUCCESS)
	{
		NetAddress address= r->address();
		std::string ip = address.ip();
		int port = address.port();
		HSSocketPool::ShareSocketPool()->AddSocket(S_L_Battle,ip.c_str(),CCString::createWithFormat("%d",port)->getCString(),HSSocket_Type_SOCKET);
		HSSocketPool::ShareSocketPool()->SetPingShortLink(true);
	}
	else if(status ==FightingResponse_RequestStatus_FAIL)
	{
		HSMessageBox("Response::Fighting Fail");
	}
}

void HSSeniortSystemLayer::ResponseTargetInfo( TargetInfoResponse*r )
{
	HS_GAME_CACHE()->m_pTargetInfoResponse->CopyFrom(*r);

	HS_GAME_CACHE()->CopyUser(r->self());

	HSSocketPool::ShareSocketPool()->SetPingShortLink(false);
	HSSocketPool::ShareSocketPool()->SetPingLongLink(true);

	if(HS_GAME_CACHE()->m_pTargetInfoResponse->status()== TargetInfoResponse_FindStatus_SUCCESS)
	{
		HSLoadingLayer::ShareLoading()->setVisible(false);
		CCLOG("did=%s",HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str());
		HS_GO_SCENE(HS_SCENE_GamePairScene);
	}
	else
	{
		HSMessageBox("HSSeniortSystemLayer::ResponseTargetInfo Response::TargetInfo fail");
	}
}

void HSSeniortSystemLayer::CallShop( CCObject* pObj )
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

	HSSeniortSystemScene* pSeniortSystemScene = (HSSeniortSystemScene*)scene;

	if(pSeniortSystemScene->GetHSGameShopLayer()==NULL)
	{
		pSeniortSystemScene->SetHSGameShopLayer(HSGameShopLayer::create());
	}
	else
	{
		pSeniortSystemScene->GetHSGameShopLayer()->setVisible(true);
	}
}

void HSSeniortSystemLayer::CallBack( CCObject* pObj )
{
	if (HS_ONLINE)
	{
		HSRequest::ShareRequest()->SendExitAdvancedRequest();
	}else{
		HS_GO_SCENE(HS_SCENE_CoverScene);
	}
}

void HSSeniortSystemLayer::ResponseExitAdvanced(ExitAdvancedResponse* r)
{
	HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
	HSSocketPool::ShareSocketPool()->SetPingShortLink(true);
	HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle)->Closed();
	HS_MUTABLE_TARGET_TARGET()->Clear();
	HS_GO_SCENE(HS_SCENE_CoverScene);
}

void HSSeniortSystemLayer::Updata( float dt )
{
	static int money = 0;
	if (money != HS_GAME_CACHE()->GetGold())
	{
		money = HS_GAME_CACHE()->GetGold();
		m_pMoney->setString(CCString::createWithFormat("%d",money)->getCString());
	}
}




//Scene
HSSeniortSystemScene::HSSeniortSystemScene(void)
{
	this->hsSeniortSystemLayer = NULL;
}

HSSeniortSystemScene::~HSSeniortSystemScene(void)
{
}

bool HSSeniortSystemScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	this->hsSeniortSystemLayer = HSSeniortSystemLayer::create();
	this->addChild(this->hsSeniortSystemLayer,HS_BASE_TAG,HS_BASE_TAG);

	return true;
}