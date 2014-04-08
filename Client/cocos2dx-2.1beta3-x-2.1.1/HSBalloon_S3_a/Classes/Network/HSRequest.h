/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/10/22   11:13
 *	File base:	HSRequest.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSRequest_H__
#define __HSRequest_H__
#pragma once
#include "HSFilter.h"

#define HS_FILTER_REQUEST(request) HSFilter::ShareFilter()->CreaterMessage((::google::protobuf::Message*)request)

class HSRequest
{
private:
	HSRequest(void);
public:
	~HSRequest(void);

public:
	static HSRequest* ShareRequest();
	void Destroy();

public:
	void SendRegisterRequest();

	void SendLoginRequest();

	void SendFightingRequest();

	void SendTargetInfoRequest(int roomID);
	void SendBattleReadyRequest(const char* did,BattleReadyRequest_TYPE_ACTION type);

	void SendPlayerDisengageRequest(const char* did);

	void SendBattleRequest(BattleDataRequest* pBattleDataRequest);

	void SendBattleResultRequest(const char* did,const BattleResultRequest_GameStatus& status);

	void SendUseBuffRequest(const char* did,const char* targetId,int propid);

	void SendHeartbeatGameRequest();

	void SendHeartbeatBattleRequest();

	void SendFriendInfoRequest();

	void SendSearchUserInfoRequest(const char* did = NULL);

	void SendDestroyBalloonRequest(const DestroyBalloonRequest& msg);

	void SendAddFriendRequest(const std::string& firendUUID);

	void SendRoomDataRequest();

	void SendClaimedDailyRewardRequest(int dayID);

	void SendUserInfoUpdateRequest_Name(const char* name);

	void SendUserInfoUpdateRequest_IconId(int iconID);

	void SendExitAdvancedRequest();

	void SendUsePropRequest(unsigned int proID,message::UsePropRequest::OperateType,const char* did = NULL);

	void SendAchievementRequest();

	void SendReceiveAchievementRewardRequest(int achievementID);
};


#endif // __HSRequest_H____
