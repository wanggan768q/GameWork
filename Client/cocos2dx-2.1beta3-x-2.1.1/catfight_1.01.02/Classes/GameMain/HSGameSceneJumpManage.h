/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/09/20   13:30
 *	File base:	HSGameSceneJumpManage.h
 *	Author:		Ambition
 *	
 *	Purpose:	��Ϸ�����л�������
*********************************************************************/
#ifndef __HSGameSceneJumpManage_H__
#define __HSGameSceneJumpManage_H__
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "HSReadPlist.h"

#define HS_GO_SCENE(__ID__) HSGameSceneJumpManage::SharedGameSceneJumpManage()->RunScene(__ID__)

#ifdef __cplusplus
extern "C"{
	typedef enum{
		HS_SCENE_UNKOWN = 0x001,
		HS_SCENE_CoverScene,
		HS_SCENE_GameMainScene,
		HS_SCENE_GamePairScene,
		HS_SCENE_BattleScene,
		HS_SCENE_FriendsSystemScene,
		HS_SCENE_AchievemenScene,
		HS_SCENE_SeniortSystemScene,
        HS_SCENE_AddressBookScene,
        HS_SCENE_EmailSystemScene,
        HS_SCENE_LOGOSCENE,
        HS_SCENE_SHOPSCENE,
	}GameSceneID;
}
#endif

class HSGameSceneJumpManage
{
public:
	HSGameSceneJumpManage(void);
	~HSGameSceneJumpManage(void);
protected:
	GameSceneID m_gameSceneId;
	GameSceneID m_LastgameSceneId;
	CCScene* currentScene;
	bool isFristRun;
public:
	inline GameSceneID GetGameSceneID(){return m_gameSceneId;};

	inline GameSceneID GetLastGameSceneID(){return m_LastgameSceneId;};

	void RunScene(GameSceneID scene);

	static HSGameSceneJumpManage* SharedGameSceneJumpManage();
	
	void Destroy();
};

#endif // __HSGameSceneJumpManage_H__

