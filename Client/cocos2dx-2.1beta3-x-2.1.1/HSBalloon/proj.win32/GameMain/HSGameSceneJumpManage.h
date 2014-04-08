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

#define HS_GO_SCENE(__ID__) HSGameSceneJumpManage::SharedGameSceneJumpManage()->RunScene(__ID__)

#ifdef __cplusplus
extern "C"{
	typedef enum{
		HS_SCENE_UNKOWN = 0x001,
		HS_SCENE_GameMainScene,
		HS_SCENE_BattleScene,
		HS_SCENE_RankingList,
		HS_SCENE_BuyProp,
	}GameSceneID;
}
#endif


class HSGameSceneJumpManage
{
public:
	HSGameSceneJumpManage(void);
	~HSGameSceneJumpManage(void);

protected:
	GameSceneID gameSceneId;
	CCScene* currentScene;
	bool isFristRun;
public:
	GameSceneID GetGameSceneID();

	void RunScene(GameSceneID scene);

	static HSGameSceneJumpManage* SharedGameSceneJumpManage();
	
	void Destroy();

};

#endif // __HSGameSceneJumpManage_H__

