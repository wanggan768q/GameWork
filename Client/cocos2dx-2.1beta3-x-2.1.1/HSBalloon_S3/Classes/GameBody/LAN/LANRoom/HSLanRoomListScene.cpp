#include "HSLanRoomListScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSJava.h"
#include "HSLoadingLayer.h"
#include "HSGlobal.h"
#include "HSLanActionManager.h"
//Layer
HSLanRoomListLayer::HSLanRoomListLayer(void)
{
	m_pRoomListView = NULL;
    m_isCreateRoomSuccessful = false;
    m_isListerIsAllowBack = false;
}

HSLanRoomListLayer::~HSLanRoomListLayer(void)
{
    
}

bool HSLanRoomListLayer::init()
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

void HSLanRoomListLayer::Load()
{
    CCSprite* pBackground = HSCCSprite::create("Image/BEIJING.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);

	HSGlobal::ShaderGlobal()->AddCloud(this);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/RoomListLan.data","Image/",this);
    

    HS_SET_MENU_TARGET("UI_Fanhuianniu", this, HSLanRoomListLayer::Call_Back);
    HS_SET_MENU_TARGET("UI_Chuangjianfangjian", this, HSLanRoomListLayer::Call_CreateRoom);
    HS_SET_MENU_TARGET("UI_Shuaxin", this, HSLanRoomListLayer::Call_Refresh);
    pRefreshMenu = HS_FIND_UI_MENU("UI_Shuaxin");
    pRefreshMenu->setVisible(false);
    
    
    CCSprite* pRadarItem = HS_FIND_UI_PANEL_SPRITE("UI_Leida", "Leidasaomiao");
    CCRotateBy* pRotate = CCRotateBy::create(3.f, -360.f);
    pRadarItem->runAction(CCRepeatForever::create(pRotate));
    Call_PlayRefreshEffect();
    
    //@ 头像 名称
    CCSprite* pHeadFrame = HS_FIND_UI_PANEL_SPRITE("UI_Wanjiaxinxi", "Touxiangdikuang");
    CCSprite* pNameFrame = HS_FIND_UI_PANEL_SPRITE("UI_Wanjiaxinxi", "Wanjiamingzikuang");
    CCSprite* pHead = HSCCSprite::create("Image/6000.png");
    pHead->setPosition(pHeadFrame->getAnchorPointInPoints());
    pHeadFrame->addChild(pHead);
    CCLabelTTF* pName = CCLabelTTF::create(HS_GAME_CACHE_DATA_LAN().name().c_str(),HS_FONT_HuaKang, 25.f,pNameFrame->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
    pName->setPosition(pNameFrame->getAnchorPointInPoints());
    pNameFrame->addChild(pName);
    
    UserBasicInfo* pTarget = HS_MUTABLE_TARGET_TARGET();
    pTarget->Clear();
    
    this->schedule(schedule_selector(HSLanRoomListLayer::ListerTargetJoinRoom), 0);
    this->schedule(schedule_selector(HSLanRoomListLayer::ListerCreateRoomSuccessful));
    this->schedule(schedule_selector(HSLanRoomListLayer::Updata));
    this->scheduleOnce(schedule_selector(HSLanRoomListLayer::ListerOnce), 0);
    this->schedule(schedule_selector(HSLanRoomListLayer::ListerTargetUserInfo), 0);
    
    this->Call_Refresh();
}

void HSLanRoomListLayer::Updata(float dt)
{
    CCNode* pTemp = HS_FIND_UI_PANEL("UI_Meiyoufangjian");
    if (pTemp)
    {
//        if (!pRefreshMenu->isVisible())
//        {
//            pTemp->setVisible(false);
//            return;
//        }
        if(HS_GAME_CACHE()->m_LanRoomList.roomlist_size() > 0)
        {
            pTemp->setVisible(false);
        }else{
//            if(m_pRoomListView)
//            {
//                m_pRoomListView->removeFromParent();
//            }
            pTemp->setVisible(true);
        }
    }
    
}

void HSLanRoomListLayer::ListerOnce(float dt)
{
    //if (HSGameSceneJumpManage::SharedGameSceneJumpManage()->GetPreviousGameSceneID() == HS_SCENE_GameMainScene)
    //{
    //    this->Call_Refresh();
    //}
}

void HSLanRoomListLayer::PlayRefreshEffect()
{
//    CCNode* pRadar = HS_FIND_UI_PANEL("UI_Leida");
//    pRadar->setVisible(true);
    
    //pRefreshMenu->setVisible(false);
}

void HSLanRoomListLayer::Call_PlayRefreshEffect()
{
    CCNode* pRadar = HS_FIND_UI_PANEL("UI_Leida");
    pRadar->setVisible(false);
    
    //pRefreshMenu->setVisible(true);
}

void HSLanRoomListLayer::DisConnectIsSucceed(bool b)
{
    if(b)
    {
        CCDelayTime* pDelay = CCDelayTime::create(10.f);
        CCCallFunc* pCallRefresh = CCCallFunc::create(this, callfunc_selector(HSLanRoomListLayer::Call_Refresh));
        this->runAction(CCSequence::create(pDelay,pCallRefresh,NULL));
    }else{
        HS_HideLoading();
    }
}

void HSLanRoomListLayer::Call_Refresh()
{
    this->Call_Refresh(NULL);
}

void HSLanRoomListLayer::Call_Refresh(CCObject* pObj)
{
    this->PlayRefreshEffect();
    if(m_pRoomListView)
    {
        m_pRoomListView->removeFromParent();
    }
    HS_GAME_CACHE()->m_LanRoomList.Clear();
    
    
    HSLanRequest::ShareLanRequest()->SendLanSearchRoomRequest();
    
}

void HSLanRoomListLayer::ListerTargetJoinRoom(float dt)
{
    UserBasicInfo* pTarget = HS_MUTABLE_TARGET_TARGET();
    if (pTarget->has_uid())
    {
        this->unschedule(schedule_selector(HSLanRoomListLayer::ListerTargetJoinRoom));
        
        HS_GO_SCENE(HS_SCENE_LanRoomListScene);
        
    }
}

void HSLanRoomListLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSLanRoomListLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSLanRoomListLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSLanRoomListLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSLanRoomListLayer::keyBackClicked()
{
    
}
void HSLanRoomListLayer::keyMenuClicked()
{
    
}

void HSLanRoomListLayer::Call_Back( CCObject* pObj )
{
    HS_GAME_CACHE()->m_LanRoomList.Clear();
    HSLanRequest::ShareLanRequest()->SendRecoverWifi();
    
    HS_ShowLoading();
    
    if(!m_isListerIsAllowBack)
    {
        m_isListerIsAllowBack = true;
        this->schedule(schedule_selector(HSLanRoomListLayer::ListerIsAllowBack));
    }
    
	//HS_GO_SCENE(HS_SCENE_GameMainScene);
}

void HSLanRoomListLayer::ListerIsAllowBack(float dt)
{
    if (HSLanActionManager::ShareLanActionManager()->m_RestoreWIFI == Lan_Action_Status_Success)
    {
        m_isListerIsAllowBack = false;
        this->unschedule(schedule_selector(HSLanRoomListLayer::ListerIsAllowBack));
        HS_GO_SCENE(HS_SCENE_GameMainScene);
    }
}

void HSLanRoomListLayer::Call_CreateRoom(CCObject* pObj)
{
    
    HSLanRequest::ShareLanRequest()->SendLanCreateRoom(HS_GAME_CACHE_DATA_LAN().name().c_str());
    HS_GO_SCENE(HS_SCENE_PairSystemScene);
}

void HSLanRoomListLayer::ResponseLanCreateRoom(LanCreateRoomResponse* pMsg)
{
    CCLog("HSLanRoomListLayer::ResponseLanCreateRoom");
//    HS_HideLoading();
//    HS_MUTABLE_TARGET_TARGET()->Clear();
//    if(pMsg->jni_egg_result() == 0)
//    {
//        //设置自己为房主
//        HS_MUTABLE_GAME_CACHE_DATA_LAN()->set_type(0);
//        //去配对界面
//        m_isCreateRoomSuccessful = true;
//        
//    }else{
//        HSMessageBox("创建房间失败");
//    }
}

void HSLanRoomListLayer::ResponseLanJoinRoom(LanJoinRoomResponse* pMsg)
{
    CCLog("HSLanRoomListLayer::ResponseLanJoinRoom");
    
    if(pMsg->jni_egg_result() != 0)
    {
        HSJava::ShaderJava()->ShowToast("加入房间失败");
        this->Call_Refresh(NULL);
        return;
    }
    
    //发送自己的数据
    //设置自己为房间成员
    HS_MUTABLE_GAME_CACHE_DATA_LAN()->set_type(1);
    HSLanRequest::ShareLanRequest()->SendLanSyncUserInfoNotice();
}


void HSLanRoomListLayer::ResponseLanSyncUserInfoNotice(LanSyncUserInfoNotice* pMsg)
{
    /**
     同步用户信息
     */
//    HS_HideLoading();
//    HS_GAME_CACHE()->m_LanTargetInfo.Clear();
//    HS_GAME_CACHE()->m_LanTargetInfo.CopyFrom(*pMsg);
//    
//    
//    CCLog("同步用户信息 OK ");
//    HS_GO_SCENE(HS_SCENE_GamePairScene);
}

void HSLanRoomListLayer::ListerTargetUserInfo(float dt)
{
    if(HS_GAME_CACHE()->m_LanTargetInfo.has_userinfo())
    {
        this->unschedule(schedule_selector(HSLanRoomListLayer::ListerTargetUserInfo));
        HS_GO_SCENE(HS_SCENE_PairSystemScene);
    }
}


void HSLanRoomListLayer::ListerCreateRoomSuccessful(float dt)
{
    if (m_isCreateRoomSuccessful)
    {
        m_isCreateRoomSuccessful = false;
        HS_GO_SCENE(HS_SCENE_PairSystemScene);
    }
}

void HSLanRoomListLayer::ResponseLanSearchRoom(LanSearchRoomResponse* pMsg)
{
    HS_GAME_CACHE()->m_LanRoomList.Clear();
    HS_GAME_CACHE()->m_LanRoomList.CopyFrom(*pMsg);
    
    this->Call_PlayRefreshEffect();
    HSMessageBox("%d",HS_GAME_CACHE()->m_LanRoomList.roomlist_size());
    CCSprite* pRoomListFrame = HS_FIND_UI_PANEL_SPRITE("UI_Wifiliebiaofanwei","Wifiliebiaofanwei");
	m_pRoomListView = HSLanRoomListVeiw::create(pRoomListFrame->getContentSize(),CCSizeMake(546,76),HS_GAME_CACHE()->m_LanRoomList.roomlist_size());
	pRoomListFrame->addChild(m_pRoomListView,1000);
	m_pRoomListView->reloadData();
    
    HS_HideLoading();
    
}
















//Scene
HSLanRoomListScene::HSLanRoomListScene(void)
{
	this->hsRoomListLayer = NULL;
}

HSLanRoomListScene::~HSLanRoomListScene(void)
{
}

bool HSLanRoomListScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
    
	this->hsRoomListLayer = HSLanRoomListLayer::create();
	this->addChild(this->hsRoomListLayer,HS_BASE_TAG,HS_BASE_TAG);
    
	return true;
}
