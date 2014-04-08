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
#define HS_GAME_CACHE_FILE_NAME_LAN "GameCacheDataLan.data"
#include "HSAllMessageHead.h"
#define HS_GAME_CACHE()								HSGameCache::ShareGameCache()

#define HS_GAME_CACHE_DATA()						HS_GAME_CACHE()->GetGameCacheData()
#define HS_MUTABLE_GAME_CACHE_DATA()				HS_GAME_CACHE()->GetMutableGameCacheData()

#define HS_GAME_CACHE_DATA_LAN()                    HS_GAME_CACHE_DATA()->lancachedata()
#define HS_MUTABLE_GAME_CACHE_DATA_LAN()            HS_MUTABLE_GAME_CACHE_DATA()->mutable_lancachedata()

#define HS_TARGET_SELF()            HS_GAME_CACHE_DATA()->userinfo()
#define HS_MUTABLE_TARGET_SELF()    HS_MUTABLE_GAME_CACHE_DATA()->mutable_userinfo()
#define HS_TARGET_TARGET()          HS_GAME_CACHE()->m_pTargetInfoResponse->target()
#define HS_MUTABLE_TARGET_TARGET()  HS_GAME_CACHE()->m_pTargetInfoResponse->mutable_target()

//#define HS_IsRunGameGuide()			HS_GAME_CACHE_DATA()->isrungameguide()
#define HS_IsLanMode()              (0 == strcmp(HS_GAME_CACHE()->GetLoginType(),"LAN")) ? true : false


typedef std::map<int,const message::PropInfo*> PROP_MAP;
typedef std::map<int,const message::BuyGold*> BUYGOLD_MAP;

class HSGameCache
{
public:
	HSGameCache(void);
	~HSGameCache(void);
private:
	bool m_isLogin;


	message::GameCacheData* m_pGameCacheData;

	message::PropInfoData* m_pPropInfoData;

	PROP_MAP m_propInfoMap;

	BUYGOLD_MAP m_buygoldMap;
    
    std::string m_loginType;
    
    //形象数据
    map<int,FigureData_FigureBase*> m_FigureMap;
    vector<FigureData_FigureBase*> m_vFigureData;
    
public:

	const char* m_pTempName;

	TargetInfoResponse* m_pTargetInfoResponse;

	BattleResultResponse* m_pBattleResult;

	std::vector<const message::PropInfo*> m_pFightingProp;

	UseBuffRequest* m_pUseBuffRequest;

	NetAddress m_NetAddress;

	RoomDataResponse m_RoomDataResponse;

	DailyRewardSystemData m_DailyRewardSystemData;

	UserInfoUpdateRequest_UpdateType m_UserInfoUpdateRequest_UpdateType;

	FriendListResponse m_FriendListResponse;    //好友列表

	AchievementResponse m_AchievementResponse;  //成就列表
    
    AddressBookResponse m_AddressBookResponse;  //通讯录列表
    
    EmailResponse m_EmailResponse;              //邮件列表
	
	bool m_refrushUserInfo;

	//记录seniorRoomId;当进入高级场金钱不够时用这个变量缓存房间id,收到服务器的金钱不够时处理，处理后清除这个缓存
		//更安全的写法是凡是服务器因金钱不够返回errormessage id= 1002时，在发包的地方都要把这个变量清 -1
	int roomGold;
	//保存进入的房间id号
	int m_roomId;
	//记录更换头像时的头像ID
	int changeheadIndex;

	bool m_isInRoom;

	bool m_isInBattle;

	bool m_isInOverLayer;
    
	std::string m_gameName;

	std::string m_gameDownload;

	std::string m_versionName;
    
    string m_lastTargetUUID;

	//用来标记是否注册成功,友盟统计要用
	bool m_isRegistSuccess;
	//注册成功后进行对战的局数
	int m_playCount;
    
#pragma region __局域网对战数据__
    
    LanSearchRoomResponse m_LanRoomList;
    
    LanSyncUserInfoNotice m_LanTargetInfo;
    
    bool m_isJoinRoomSucceed;

#pragma endregion __局域网对战数据__

    //是否开启战斗中快速道具开关
    bool m_isOpenFastProp;
    
    
    
private:
	void ReadPropInfoData();
public:

	static HSGameCache* ShareGameCache();

	const message::PropInfoData* GetPropInfoData();

	const char* GetEffectResName(const int& id);

	const message::PropInfo* GetPropInfo(const int& id);

	const message::GameCacheData* GetGameCacheData();
 
	message::GameCacheData* GetMutableGameCacheData();

	void Destroy();

	bool Save();

	bool Read();
    
    bool ReadLan();

	bool AddGold(int money);

	int GetGold();

	const message::BuyGold* GetReasonableChargeId(const int& money);

	int GetChargeNumber(const int& total,const int& money);

	void CopyUser(const UserBasicInfo& user);

	const message::PropInfo* GetPropData(int id);

	bool IsRegister();

	bool IsLogin();

	void SetIsLogin(bool b);
    
    int GetSelfGameScore();
    
    void SetLoginType(const char* type);
    
    const char* GetLoginType();
    
    
    void ReadFigureData();
    vector<FigureData_FigureBase*>* GetFigureList();
    FigureData_FigureLevelTable* GetFigureLevelTable(int id,int level);
    FigureData_FigureProperty* GetFigureProperty(int id);
    FigureData_FigureBase* GetFigureBase(int id);

public:
	//@network
	void ResponseNotifyChangeBuff(NotifyChangeBuff*);
	void ResponseUseBuff(UseBuffResponse*);
	void ResponseSearchUserInfo(SearchUserInfoResponse*);

};


#endif // __HSGameCache_H____

