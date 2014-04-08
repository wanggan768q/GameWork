#include "HSAchievemenScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameShopScene.h"
#include "HSShareLayer.h"
#include "HSGlobal.h"
//Layer
HSAchievemenLayer::HSAchievemenLayer(void)
{
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
    
    CCSprite* pBackground = HSCCSprite::create("Image/Tongyongbeijing.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
    
	HSReadUI::ShareReadUI()->ReadUI("Image/AchievementSystem.data","Image/",this);

	CCSprite* pAchievemenFrame = HS_FIND_UI_PANEL_SPRITE("UI_Tongyongfanwei","Yaoqinghaoyoulanfanwei");
	m_pAchievemenListView = HSAchievemenListView::create(&HS_GAME_CACHE()->m_AchievementResponse,pAchievemenFrame->getContentSize(),CCSizeMake(568,96),HS_GAME_CACHE()->m_AchievementResponse.achievementlist_size());
	CCPoint pos = CCPointZero;
	
	pos.y = pAchievemenFrame->getPosition().y - pAchievemenFrame->getContentSize().height / 2.f;
	m_pAchievemenListView->setPosition(pos);
	pAchievemenFrame->getParent()->addChild(m_pAchievemenListView,1000);
	m_pAchievemenListView->reloadData();

    //返回
	HS_SET_MENU_TARGET("UI_Tongyongguanbi", this, HSAchievemenLayer::Call_Back);
		
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

}

void HSAchievemenLayer::Call_Back( CCObject* pObj )
{
	HS_GO_SCENE(HS_SCENE_StartGameScene);
}

void HSAchievemenLayer::Call_Shop( CCObject* pobj )
{
	HS_GO_SCENE(HS_SCENE_ShopScene);
}

void HSAchievemenLayer::ResponseReceiveAchievementReward(ReceiveAchievementRewardResponse* pMsg)
{
    HS_GAME_CACHE()->AddGold(pMsg->addgoldnumber());
    
    if (!HSAchievemenSrpite::S_ReceiveAchievementReward)
    {
        return;
    }
    CCString* pWbStr = CCString::createWithFormat(L("achievement"),HS_GAME_CACHE()->m_gameName.c_str(),HSAchievemenSrpite::S_ReceiveAchievementReward->name().c_str(),HS_GAME_CACHE()->m_gameDownload.c_str());
    CCString* pShareStr = CCString::createWithFormat(L("Exploit"),HSAchievemenSrpite::S_ReceiveAchievementReward->name().c_str());
    
    HSJson* pJson = HSJson::CreateWithWriter();
    Json::Value jsonData;
    jsonData["JNI_ID"] = 2002;
    jsonData["WEIBO_TEXT"] = pWbStr->getCString();
    jsonData["WEIBO_TYPE"] = HS_GAME_CACHE()->GetLoginType();
    
    HSShareData shareData;
    shareData.shareText = pShareStr->getCString();
    shareData.wbText = pJson->Writer(jsonData);
    shareData.money = pMsg->addgoldnumber();
    shareData.feedbackText = L("Exploit_Feedback");
    
    HSShareLayer* pShareLayer = HSShareLayer::create(shareData);
    this->getParent()->addChild(pShareLayer,10000);
    
    
    pWbStr->release();
    pShareStr->release();
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
