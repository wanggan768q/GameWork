#include "HSGameSceneJumpManage.h"
#include "HSGameMainScene.h"
#include "HSBattleScene.h"
#include "HSRankingListScene.h"
#include "HSBuyPropScene.h"

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
	case HS_SCENE_GameMainScene:
		this->currentScene = HSGameMainScene::create();
		break;
	case HS_SCENE_BattleScene:
		this->currentScene = HSBattleScene::create();
		break;
	case HS_SCENE_RankingList:
		this->currentScene = HSRankingListScene::create();
		break;
	case HS_SCENE_BuyProp:
		this->currentScene = HSBuyPropScene::create();
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
