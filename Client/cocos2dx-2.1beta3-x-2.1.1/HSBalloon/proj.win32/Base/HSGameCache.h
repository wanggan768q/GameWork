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
#include "HSTool.h"
#include "GameCacheData.pb.h"
#include "HSBase.h"
#include "HSTime.h"
#include "HSMath.h"
#include "HSWriteData.h"
#include "HSReadData.h"
#include "PropInfoData.pb.h"
using namespace message;
//class PropInfoData;
#define HS_GAME_CACHE_FILE_NAME "GameCacheData.data"

#define HS_GAME_CACHE()								HSGameCache::ShareGameCache()
#define HS_GAME_CACHE_DATA()						HS_GAME_CACHE()->GetGameCacheData()
#define HS_MUTABLE_GAME_CACHE_DATA()				HS_GAME_CACHE()->GetMutableGameCacheData()
#define HS_GAME_CACHE_DATA_PROPDATA()               HS_GAME_CACHE_DATA()->propcachedata()
#define HS_MUTABLE_GAME_CACHE_DTAT_MUTABLE_PROPDATA()       HS_MUTABLE_GAME_CACHE_DATA()->mutable_propcachedata()
#define HS_GAME_CACHE_PROPINFODATA()                HS_GAME_CACHE()->GetPropInfoData()

class HSGameCache
{
public:
	HSGameCache(void);
	~HSGameCache(void);

private:
	message::GameCacheData* m_pGameCacheData;
	message::PropInfo* m_pUseBufferPropData;
	message::PropInfoData* m_pPropInfoData;

public:

	static HSGameCache* ShareGameCache();

	const message::GameCacheData* GetGameCacheData();

	message::GameCacheData* GetMutableGameCacheData();

	const message::PropInfoData* GetPropInfoData();

	void Destroy();

	bool AddGold( int useNum);

	void SetGold(int num);

	int GetGold();

	/**
	* 1.没有网络的情况下使用
	* 1.发送游戏得分失败的情况使用
	*/
	void AddHistoryScore( unsigned int score );

	int AddHistoryFiveHighestScore(unsigned int score);

	void AddFiveDayScore( unsigned int score );

	void ClearHistoryScoreList();

	void AddUseProp(const message::PropInfo& info,int postion);

	int GetHistoryScore();

	bool IsPropSlotLock(int index);

	void SetIsPropSlotLock(bool b,int index);

	bool IsLevelLock(int index);
	
	void SetIsLevelLock(int index,bool b);

	int GetPropNumber(int index);

	void SetPropNumber(int index,int number);

	void SetPropUseFrequency(const int& index,const int& frequcency);

	int GetPropUseFrequency(const int& index);

	int GetPropUseFrequencyByLevel(const int& level);

	void SetPropLevel(const int& index,const int& level);

	const int GetPropLevel(const int& index);

	void SetPropIndex(const int& index);

	const int GetPropIndex();

	void SetLastTime(const long long& time);

	const long long GetLastTime();

	int GetUseBackgroundID();

	void SetUseBackgroundID(unsigned int id);

	bool Save();

	bool Read();

	void AddBoughtBackgroundID(unsigned int id);

	void SetIsOpenBackgroundMusic(bool b);

	void SetIsOpenIsSound(bool b);

	void SetWorldRankData(SearchRankResponse* pMsg);

	void SetWeekRankData(SearchWeeklyScoreResponse* pMsg);

	void SetUserInfo(const char* pName,const std::string& uid);

	void SetIsSendDeviceInfo(bool b);

	void SetUseBufferPropData(const PropInfo* pBufferProp);

	const PropInfo* GetUseBufferPropData();

	bool IsRunGameGuide();

	void SetIsRunGameGuide(bool b);
};


#endif // __HSGameCache_H____
