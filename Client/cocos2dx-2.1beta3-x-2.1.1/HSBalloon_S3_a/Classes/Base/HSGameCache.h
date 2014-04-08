/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/04   12:29
 *	File base:	HSGameCache.h
 *	Author:		Ambition
 *	
 *	Purpose:	Cache Data
*********************************************************************/
#ifndef __HSGameCache_H__
#define __HSGameCache_H__
#pragma once
#include "HSBase.h"
#include "PropInfoData.pb.h"
#include "GameCacheData.pb.h"
#define HS_GAME_CACHE_FILE_NAME "GameCacheData.data"
#include "HSAllMessageHead.h"
#define HS_GAME_CACHE()								HSGameCache::ShareGameCache()

#define HS_GAME_CACHE_DATA()						HS_GAME_CACHE()->GetGameCacheData()
#define HS_MUTABLE_GAME_CACHE_DATA()				HS_GAME_CACHE()->GetMutableGameCacheData()

#define HS_TARGET_SELF()            HS_GAME_CACHE_DATA()->userinfo()
#define HS_MUTABLE_TARGET_SELF()    HS_MUTABLE_GAME_CACHE_DATA()->mutable_userinfo()
#define HS_TARGET_TARGET()          HS_GAME_CACHE()->m_pTargetInfoResponse->target()
#define HS_MUTABLE_TARGET_TARGET()  HS_GAME_CACHE()->m_pTargetInfoResponse->mutable_target()
#define HS_IsRunGameGuide()			HS_GAME_CACHE_DATA()->isrungameguide()


typedef std::map<int,const message::PropInfo*> PROP_MAP;

class HSGameCache
{
public:
	HSGameCache(void);
	~HSGameCache(void);
private:
	bool m_isLogin;

	//@游戏缓存
	message::GameCacheData* m_pGameCacheData;
	//@加载的游戏道具数据
	message::PropInfoData* m_pPropInfoData;

	PROP_MAP m_propInfoMap;

public:
	/************************************************************************/
	/* 临时的保存的名字，发送注册请求后，把注册的名字保存到此处，如果注册成功，把他保存到GameCache中                                                                     */
	/************************************************************************/
	const char* m_pTempName;
	TargetInfoResponse* m_pTargetInfoResponse;
	BattleResultResponse* m_pBattleResult;
	//@战斗时带入的道具数据
	std::vector<const message::PropInfo*> m_pFightingProp;

	//@SendUseBuffRequest 缓存
	UseBuffRequest* m_pUseBuffRequest;

	NetAddress m_NetAddress;

	RoomDataResponse m_RoomDataResponse;

	DailyRewardSystemData m_DailyRewardSystemData;

	UserInfoUpdateRequest_UpdateType m_UserInfoUpdateRequest_UpdateType;

	FriendInfoResponse m_FriendInfoResponse;

	AchievementResponse m_AchievementResponse;

	
	bool m_refrushUserInfo;

private:
	void ReadPropInfoData();
public:

	static HSGameCache* ShareGameCache();
	//@道具
	const message::PropInfoData* GetPropInfoData();

	const char* GetEffectResName(const int& id);

	const message::PropInfo* GetPropInfo(const int& id);
	//@游戏缓存
	const message::GameCacheData* GetGameCacheData();
 
	message::GameCacheData* GetMutableGameCacheData();

	void Destroy();

	bool Save();

	bool Read();

	bool AddGold(int money);

	int GetGold();

	void CopyUser(const UserBasicInfo& user);

	const message::PropInfo* GetPropData(int id);

	bool IsRegister();

	bool IsLogin();

	void SetIsLogin(bool b);

public:
	//@network
	void ResponseNotifyChangeBuff(NotifyChangeBuff*);
	void ResponseUseBuff(UseBuffResponse*);
	void ResponseSearchUserInfo(SearchUserInfoResponse*);

};


#endif // __HSGameCache_H____
