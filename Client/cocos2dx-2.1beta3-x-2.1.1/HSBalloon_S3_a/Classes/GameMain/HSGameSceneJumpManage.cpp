#include "HSGameSceneJumpManage.h"
#include "HSGameMainScene.h"
#include "HSBattleScene.h"
#include "HSGameCoverScene.h"
#include "HSGamePairScene.h"
#include "HSFriendsSystemScene.h"
#include "HSAchievemenScene.h"
#include "HSSeniortSystemScene.h"

static HSGameSceneJumpManage* s_pGameSceneJumpManage = NULL;

HSGameSceneJumpManage::HSGameSceneJumpManage(void)
{
	this->gameSceneId = HS_SCENE_GameMainScene;
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
	this->gameSceneId = scene;	
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
