#include "HSGameSceneJumpManage.h"
#include "HSGameMainScene.h"
#include "HSBattleScene.h"
#include "HSAchievemenScene.h"
#include "HSAddressBookScene.h"
#include "HSEmailSystemScene.h"
#include "HSLanRoomListScene.h"
#include "HSGameShopScene.h"
#include "HSLogoScene.h"

//new
#include "HSPairSystemScene.h"
#include "HSStartGameScene.h"
#include "HSSettingScene.h"
#include "HSFigureSystemScene.h"
#include "HSChangeFigureScene.h"
#include "HSGameGuideSystemScene.h"

static HSGameSceneJumpManage* s_pGameSceneJumpManage = NULL;

HSGameSceneJumpManage::HSGameSceneJumpManage(void)
{
	this->currentGameSceneID = HS_SCENE_GameMainScene;
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
	//scene = HS_SCENE_GamePairScene;
	HSReadUI::ShareReadUI()->Destroy();
    this->previousGameSceneID = currentGameSceneID;
	this->currentGameSceneID = scene;
	switch(scene)
	{
        case HS_SCENE_GameGuideSystemScene:
            this->currentScene = HSGameGuideSystemScene::create();
            break;
        case HS_SCENE_GameMainScene:
            this->currentScene = HSGameMainScene::create();
            break;
        case HS_SCENE_StartGameScene:
            this->currentScene = HSStartGameScene::create();
            break;
        case HS_SCENE_SettingScene:
            this->currentScene = HSSettingScene::create();
            break;
        case HS_SCENE_PairSystemScene:
            this->currentScene = HSPairSystemScene::create();
            break;
        case HS_SCENE_FigureSystemScene:
            this->currentScene = HSFigureSystemScene::create();
            break;
        case HS_SCENE_ChangeFigureScene:
            this->currentScene = HSChangeFigureScene::create();
            break;
            
            
            
        case HS_SCENE_BattleScene:
            this->currentScene = HSBattleScene::create();
            break;
        case HS_SCENE_AchievemenScene:
            this->currentScene = HSAchievemenScene::create();
            break;
        case HS_SCENE_AddressBookScene:
            this->currentScene = HSAddressBookScene::create();
            break;
        case HS_SCENE_EmailSystemScene:
            this->currentScene = HSEmailSystemScene::create();
            break;
        case HS_SCENE_ShopScene:
        	this->currentScene = HSGameShopScene::create();
        	break;
        case HS_SCENE_LanRoomListScene:
            this->currentScene = HSLanRoomListScene::create();
            break;
        case HS_SCENE_LOGOSCENE:
        	this->currentScene = HSLogoScene::create();
        	break;
        default:
            HSMessageBox("invalid gameScene!");
            break;
	}
    
	if (this->isFristRun)
	{
		this->isFristRun = false;
		CCDirector::sharedDirector()->runWithScene(this->currentScene);
	}else{
		CCDirector::sharedDirector()->replaceScene(this->currentScene);
	}
}

//void HSGameSceneJumpManage::RunScene( GameSceneID scene )
//{
//	//scene = HS_SCENE_GamePairScene;
//	HSReadUI::ShareReadUI()->Destroy();
//    this->previousGameSceneID = currentGameSceneID;
//	this->currentGameSceneID = scene;
//	switch(scene)
//	{
//        case HS_SCENE_CoverScene:
//            this->currentScene = HSGameCoverScene::create();
//            break;
//        case HS_SCENE_GameMainScene:
//            //this->currentScene = HSGameMainScene::create();
//            this->currentScene = HSStartGameScene::create();
//            break;
//        case HS_SCENE_GamePairScene:
//            //this->currentScene = HSGamePairScene::create();
//            this->currentScene = HSPairSystemScene::create();
//            
//            break;
//        case HS_SCENE_BattleScene:
//            this->currentScene = HSBattleScene::create();
//            break;
//        case HS_SCENE_FriendsSystemScene:
//            this->currentScene = HSFriendsSystemScene::create();
//            break;
//        case HS_SCENE_AchievemenScene:
//            this->currentScene = HSAchievemenScene::create();
//            break;
//        case HS_SCENE_SeniortSystemScene:
//            this->currentScene = HSSeniortSystemScene::create();
//            break;
//        case HS_SCENE_AddressBookScene:
//            this->currentScene = HSAddressBookScene::create();
//            break;
//        case HS_SCENE_EmailSystemScene:
//            this->currentScene = HSEmailSystemScene::create();
//            break;
//        case HS_SCENE_PlayerInfoScene:
//        	this->currentScene = HSGamePlayerInfoScene::create();
//        	break;
//        case HS_SCENE_ShopScene:
//        	this->currentScene = HSGameShopScene::create();
//        	break;
//        case HS_SCENE_LanRoomListScene:
//            this->currentScene = HSLanRoomListScene::create();
//            break;
//        case HS_SCENE_LOGOSCENE:
//        	this->currentScene = HSLogoScene::create();
//        	break;
//        default:
//            HSMessageBox("invalid gameScene!");
//            break;
//	}
//    
//	if (this->isFristRun)
//	{
//		this->isFristRun = false;
//		CCDirector::sharedDirector()->runWithScene(this->currentScene);
//	}else{
//		CCDirector::sharedDirector()->replaceScene(this->currentScene);
//	}
//}
