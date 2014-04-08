#include "HSGameSceneJumpManage.h"
#include "HSGameMainScene.h"
#include "HSBattleScene.h"
#include "HSGameCoverScene.h"
#include "HSGamePairScene.h"
#include "HSFriendsSystemScene.h"
#include "HSAchievemenScene.h"
#include "HSSeniortSystemScene.h"
#include "HSAddressBookScene.h"
#include "HSEmailSystemScene.h"
#include "HSLogoScene.h"
#include "HSGameShopScene.h"

static HSGameSceneJumpManage* s_pGameSceneJumpManage = NULL;

HSGameSceneJumpManage::HSGameSceneJumpManage(void)
{
	this->m_gameSceneId = HS_SCENE_GameMainScene;
	this->m_LastgameSceneId = HS_SCENE_UNKOWN;
	this->currentScene = NULL;
	this->isFristRun = true;
	HSBase::SetMaxImageSize(CCSizeMake(640,960));
}

HSGameSceneJumpManage::~HSGameSceneJumpManage(void)
{
}

HSGameSceneJumpManage* HSGameSceneJumpManage::SharedGameSceneJumpManage()
{
	if (s_pGameSceneJumpManage == NULL)
	{
		s_pGameSceneJumpManage = new HSGameSceneJumpManage;
	}
	return s_pGameSceneJumpManage;
}

void HSGameSceneJumpManage::Destroy()
{
	CC_SAFE_DELETE(s_pGameSceneJumpManage);
}

void HSGameSceneJumpManage::RunScene( GameSceneID scene )
{
	//scene = HS_SCENE_GameMainScene;
	HSReadUI::ShareReadUI()->Destroy();
	this->m_LastgameSceneId = this->m_gameSceneId;
	this->m_gameSceneId = scene;
	switch(scene)
	{
        case HS_SCENE_CoverScene:
            this->currentScene = HSGameCoverScene::create();
            break;
        case HS_SCENE_GameMainScene:
            this->currentScene = HSGameMainScene::create();
            break;
        case HS_SCENE_GamePairScene:
            this->currentScene = HSGamePairScene::create();
            break;
        case HS_SCENE_BattleScene:
            this->currentScene = HSBattleScene::create();
            break;
        case HS_SCENE_FriendsSystemScene:
            this->currentScene = HSFriendsSystemScene::create();
            break;
        case HS_SCENE_AchievemenScene:
            this->currentScene = HSAchievemenScene::create();
            break;
        case HS_SCENE_SeniortSystemScene:
            this->currentScene = HSSeniortSystemScene::create();
            break;
        case HS_SCENE_AddressBookScene:
            this->currentScene = HSAddressBookScene::create();
            break;
        case HS_SCENE_EmailSystemScene:
            this->currentScene = HSEmailSystemScene::create();
            break;
        case HS_SCENE_LOGOSCENE:
        	this->currentScene = HSLogoScene::create();
        	break;
        case HS_SCENE_SHOPSCENE:
        	this->currentScene = HSGameShopScene::create();
        	break;
        default:
            HSMessageBox("invalid gameScene!");
            break;
	}
    
	if (this->isFristRun)
	{
		this->isFristRun = false;
		CCDirector::sharedDirector()->runWithScene(this->currentScene);
	}
	else
	{
		CCDirector::sharedDirector()->replaceScene(this->currentScene);
		//CCDirector::sharedDirector()
	}
}
