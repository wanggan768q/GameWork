#include "HSSettingScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSAboutLayer.h"
//Layer
HSSettingLayer::HSSettingLayer(void)
{
}

HSSettingLayer::~HSSettingLayer(void)
{
}

bool HSSettingLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	HSTool::SetLayerScale(this);
    Load();
	//this->setIsTouchEnabled(true);
    
	//this->setIsKeypadEnabled(true);
    
	return true;
}

void HSSettingLayer::Load()
{
    CCSprite* pBackground = HSCCSprite::create("Image/Tongyongbeijing.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/Setting.data","Image/",this);
    
    //背景音乐
    HS_SET_MENU_TARGET("UI_Shezhijiemian_Kaiguandiban_0_Kaiguan", this, HSSettingLayer::Call_Music);
    //音效
    HS_SET_MENU_TARGET("UI_Shezhijiemian_Kaiguandiban_1_Kaiguan", this, HSSettingLayer::Call_Sound);
    //教程
    HS_SET_MENU_TARGET("UI_Shezhijiemian_Kaiguandiban_3_Chakan", this, HSSettingLayer::Call_Course);
    //关于
    HS_SET_MENU_TARGET("UI_Shezhijiemian_Kaiguandiban_4_Chakan", this, HSSettingLayer::Call_AboutInfo);
    //注销
    HS_SET_MENU_TARGET("UI_Shezhijiemian_Zhuxiaodenglu", this, HSSettingLayer::Call_Logout);
    //更多游戏
    HS_SET_MENU_TARGET("UI_Shezhijiemian_Gengduoyouxi", this, HSSettingLayer::Call_MoreGame);
    //关闭
    HS_SET_MENU_TARGET("UI_Shezhiguanbi", this, HSSettingLayer::Call_Back);
    
    CCArray* arraySound = HS_FIND_UI_MENUITEM_ARRAY_Not_Remove_of_Parent("UI_Shezhijiemian_Kaiguandiban_1_Kaiguan");
    
    CCObject* objSound = arraySound->objectAtIndex(0);
    
    CCMenuItemToggle* toggleSound = dynamic_cast<CCMenuItemToggle*>(objSound);
    
    if(toggleSound)
    {
        if(HS_GAME_CACHE_DATA()->issound())
        {
            toggleSound->setSelectedIndex(0);
        }
        else
        {
            toggleSound->setSelectedIndex(1);
        }
    }
    
    CCArray* arrayMusic = HS_FIND_UI_MENUITEM_ARRAY_Not_Remove_of_Parent("UI_Shezhijiemian_Kaiguandiban_0_Kaiguan");
    
    CCObject* objMusic = arrayMusic->objectAtIndex(0);
    
    CCMenuItemToggle* toggleMusic = dynamic_cast<CCMenuItemToggle*>(objMusic);
    
    if(toggleMusic)
    {
        if(HS_GAME_CACHE_DATA()->isbackgroundmusic())
        {
            toggleMusic->setSelectedIndex(0);
        }
        else
        {
            toggleMusic->setSelectedIndex(1);
        }
    }
}

void HSSettingLayer::Call_Sound(CCObject* obj)
{
    CCLog("声效");
	bool isPlaySoundEffect= HS_GAME_CACHE_DATA()->issound();
	HS_MUTABLE_GAME_CACHE_DATA()->set_issound(!isPlaySoundEffect);
	HS_GAME_CACHE()->Save();
	HSSoundManage::ShareSoundManage()->SetIsPlayEffect(!isPlaySoundEffect);
    
    HS_Play_Sound("UI_button");
}

void HSSettingLayer::Call_Music(CCObject* pbj)
{
    CCLog("背景音乐");
    HS_Play_Sound("UI_button");    
	bool isPlayMusic = HS_GAME_CACHE_DATA()->isbackgroundmusic();
	HS_MUTABLE_GAME_CACHE_DATA()->set_isbackgroundmusic(!isPlayMusic);
	HS_GAME_CACHE()->Save();
	HSSoundManage::ShareSoundManage()->SetIsPlayMusic(!isPlayMusic);
}

void HSSettingLayer::Call_Logout(CCObject* pbj)
{
    CCLog("注销");
    HS_Play_Sound("UI_button");
    HS_GO_SCENE(HS_SCENE_GameMainScene);
}

void HSSettingLayer::Call_AboutInfo(CCObject* pbj)
{
    CCLog("关于");
    HS_Play_Sound("UI_button");
    HSAboutLayer::ShareHSAboutLayer()->setVisible(true);
}
void HSSettingLayer::Call_Course(CCObject* pbj)
{
    CCLog("教程");
    HS_Play_Sound("UI_button");
}

void HSSettingLayer::Call_MoreGame(CCObject* pbj)
{
    CCLog("更多游戏");
    HS_Play_Sound("UI_button");
}

void HSSettingLayer::Call_Back(CCObject* pbj)
{
    CCLog("返回");
    HS_GO_SCENE(HS_SCENE_StartGameScene);
}

void HSSettingLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSSettingLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSSettingLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSSettingLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSSettingLayer::keyBackClicked()
{
    
}
void HSSettingLayer::keyMenuClicked()
{
    
}




















//Scene
HSSettingScene::HSSettingScene(void)
{
	this->m_pHSSettingLayer = NULL;
}

HSSettingScene::~HSSettingScene(void)
{
}

bool HSSettingScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
    
	this->m_pHSSettingLayer = HSSettingLayer::create();
	this->addChild(this->m_pHSSettingLayer,HS_BASE_TAG,HS_BASE_TAG);
    
	return true;
}


