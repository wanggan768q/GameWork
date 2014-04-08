#include "HSGameMainScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameCache.h"
#include "HSLog.h"
#include "HSChannel.pb.h"
#include "HSChannelManager.h"
//Layer
HSGameMainLayer::HSGameMainLayer(void)
{
	this->townBackground = NULL;
}

HSGameMainLayer::~HSGameMainLayer(void)
{
	
}

bool HSGameMainLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	HSTool::SetLayerScale(this);
	this->Load();
	//this->setTouchEnabled(true);
	//this->setKeypadEnabled(true);
	return true;
}

void HSGameMainLayer::Load()
{
	HS_GAME_CACHE();
	HSReadUI::ShareReadUI()->ReadUI("Image/Play/Play.data","Image/Play/",this);
	//HSReadUI::ShareReadUI()->ReadUI("Image/BattleLayer/BattleLayer.data","Image/BattleLayer/",this);

	HSSoundManage::ShareSoundManage()->PlayMusic("menu");

	HS_SET_MENU_TARGET("UI_MenuPlay",this,HSGameMainLayer::CallBuyPropScene);
	//音乐开关
	HS_SET_MENU_TARGET("UI_YinYue_11",this,HSGameMainLayer::CallMusicMenu);
	//音效开关
	HS_SET_MENU_TARGET("UI_YinXiao_11",this,HSGameMainLayer::CallSoundEffectMenu);
	//排行榜
	HS_SET_MENU_TARGET("UI_PaiHang_01",this,HSGameMainLayer::CallRankingMenu);
	//关于
	HS_SET_MENU_TARGET("UI_GuanYu_01",this,HSGameMainLayer::CallAboutMenu);

	bool isPlayMusic = HS_GAME_CACHE_DATA()->isbackgroundmusic();
	bool isPlaySoundEffect= HS_GAME_CACHE_DATA()->issound();

	if (!isPlayMusic)
	{
		CCMenu* musicMenu = HS_FIND_UI_MENU("UI_YinYue_11");
		CCArray* array = musicMenu->getChildren();
		CCObject* obj = array->objectAtIndex(0);
		CCMenuItemToggle* toggle = dynamic_cast<CCMenuItemToggle*>(obj);
		toggle->setSelectedIndex(1);

		HSSoundManage::ShareSoundManage()->SetIsPlayMusic(false);
	}
	if (!isPlaySoundEffect)
	{
		CCMenu* musicMenu = HS_FIND_UI_MENU("UI_YinXiao_11");
		CCArray* array = musicMenu->getChildren();
		CCObject* obj = array->objectAtIndex(0);
		CCMenuItemToggle* toggle = dynamic_cast<CCMenuItemToggle*>(obj);
		toggle->setSelectedIndex(1);
		HSSoundManage::ShareSoundManage()->SetIsPlayEffect(false);
	}

	HS_LOG()->SendUserLog(LogRequest_ActionType_Login);


	
	/**
	Channel* channel = message::Channel::default_instance().New();
	
	Channel_Tom* tom = channel->mutable_tom();
	tom->set_gamemoney(100);
	tom->set_propid(1000);
	tom->set_title("购买金币");
	tom->set_describe("这里是购买金币");
	 
	HSChannelManager::ShaderChannelManager()->Buy(channel);*/
	/**
	CCLabelTTF* pp = CCLabelTTF::create(HSTime::GetTime(),"",20.f);
	pp->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pp,1000000);*/

}

void HSGameMainLayer::CallBuyPropScene(CCObject* obj)
{
	HSSoundManage::ShareSoundManage()->PlayerEffect("botton");
	HS_GO_SCENE(HS_SCENE_BuyProp);
}

void HSGameMainLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
}

bool HSGameMainLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	HS_GO_SCENE(HS_SCENE_BattleScene);
	return true;
}

void HSGameMainLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameMainLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameMainLayer::keyBackClicked()
{

}
void HSGameMainLayer::keyMenuClicked()
{

}

void HSGameMainLayer::onHttpRequestCompleted( cocos2d::CCNode *sender, void *data )
{
	/*****/
}

void HSGameMainLayer::CallMusicMenu( CCObject* obj )
{
	HSSoundManage::ShareSoundManage()->PlayerEffect("botton");

	bool isPlayMusic = HS_GAME_CACHE_DATA()->isbackgroundmusic();
	HS_GAME_CACHE()->SetIsOpenBackgroundMusic(!isPlayMusic);

	HSSoundManage::ShareSoundManage()->SetIsPlayMusic(!isPlayMusic);
}

void HSGameMainLayer::CallSoundEffectMenu( CCObject* obj )
{
	HSSoundManage::ShareSoundManage()->PlayerEffect("botton");

	bool isPlaySoundEffect= HS_GAME_CACHE_DATA()->issound();
	HS_GAME_CACHE()->SetIsOpenIsSound(!isPlaySoundEffect);
	HSSoundManage::ShareSoundManage()->SetIsPlayEffect(!isPlaySoundEffect);
}

void HSGameMainLayer::CallAboutMenu( CCObject* obj )
{
}

void HSGameMainLayer::CallRankingMenu( CCObject* obj )
{
	HS_GO_SCENE(HS_SCENE_RankingList);
}


//Scene
HSGameMainScene::HSGameMainScene(void)
{
	this->hsGameMainLayer = NULL;
}

HSGameMainScene::~HSGameMainScene(void)
{
}

bool HSGameMainScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
	this->hsGameMainLayer = HSGameMainLayer::create();
	this->addChild(this->hsGameMainLayer,HS_BASE_TAG,HS_BASE_TAG);

	

	return true;
}