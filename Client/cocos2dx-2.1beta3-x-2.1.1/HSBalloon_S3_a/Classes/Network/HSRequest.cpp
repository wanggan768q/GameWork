#include "HSRequest.h"

HSRequest::HSRequest(void)
{
}

HSRequest::~HSRequest(void)
{
}

HSRequest* HSRequest::ShareRequest()
{
	static HSRequest s_hsRequest;
	return &s_hsRequest;
}

void HSRequest::Destroy()
{

}

void HSRequest::SendRegisterRequest()
{
	HS_GAME_CACHE()->m_pTempName = "";

	RegisterRequest* r = RegisterRequest::default_instance().New();
	r->set_username(HS_GAME_CACHE()->m_pTempName);
	r->set_usericonid(6000);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendLoginRequest()
{
	LoginRequest* r = LoginRequest::default_instance().New();
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendFightingRequest()
{
	FightingRequest* r = FightingRequest::default_instance().New();
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendTargetInfoRequest( int roomID )
{
	TargetInfoRequest* r = TargetInfoRequest::default_instance().New();
	r->set_roomid(roomID);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendBattleReadyRequest(const char* did,BattleReadyRequest_TYPE_ACTION type)
{
	BattleReadyRequest* r = BattleReadyRequest::default_instance().New();
	r->set_did(did);
	r->set_type(type);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendPlayerDisengageRequest(const char* did)
{
	PlayerDisengageRequest* r = PlayerDisengageRequest::default_instance().New();
	r->set_did(did);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendBattleRequest( BattleDataRequest* pBattleDataRequest )
{
	BattleDataRequest* r = BattleDataRequest::default_instance().New();
	r->CopyFrom(*pBattleDataRequest);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendBattleResultRequest( const char* did,const BattleResultRequest_GameStatus& status )
{
	BattleResultRequest* r = BattleResultRequest::default_instance().New();
	r->set_did(did);
	r->set_status(status);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendUseBuffRequest(const char* did,const char* targetId,int propid)
{
	UseBuffRequest* r = UseBuffRequest::default_instance().New();
	r->set_did(did);
	r->set_targetuid(targetId);
	r->set_propid(propid);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendHeartbeatGameRequest()
{
	GamePingRequest* r = GamePingRequest::default_instance().New();
	r->mutable_gamepingrequest();
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendHeartbeatBattleRequest()
{
	BattlePingRequest* r = BattlePingRequest::default_instance().New();
	r->mutable_battlepingrequest();
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendFriendInfoRequest()
{
	FightingRequest* r = FightingRequest::default_instance().New();
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendSearchUserInfoRequest(const char* did /*= NULL*/)
{
	SearchUserInfoRequest* r = SearchUserInfoRequest::default_instance().New();
	if(did)
	{
		r->set_did(did);
	}
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendDestroyBalloonRequest( const DestroyBalloonRequest& msg )
{
	DestroyBalloonRequest* r = DestroyBalloonRequest::default_instance().New();
	r->CopyFrom(msg);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendAddFriendRequest( const std::string& firendUUID )
{
	AddFriendRequest* r = AddFriendRequest::default_instance().New();
	r->set_frienduuid(firendUUID);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendRoomDataRequest()
{
	RoomDataRequest* r = RoomDataRequest::default_instance().New();
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendClaimedDailyRewardRequest( int dayID )
{
	ClaimedDailyRewardRequest* r = ClaimedDailyRewardRequest::default_instance().New();
	r->set_dayid(dayID);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendUserInfoUpdateRequest_Name( const char* name )
{
	HS_GAME_CACHE()->m_UserInfoUpdateRequest_UpdateType = UserInfoUpdateRequest_UpdateType_User_Name;
	UserInfoUpdateRequest* r = UserInfoUpdateRequest::default_instance().New();
	r->set_type(UserInfoUpdateRequest_UpdateType_User_Name);
	r->set_name(name);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendUserInfoUpdateRequest_IconId( int iconID )
{
	HS_GAME_CACHE()->m_UserInfoUpdateRequest_UpdateType = UserInfoUpdateRequest_UpdateType_User_IconId;
	UserInfoUpdateRequest* r = UserInfoUpdateRequest::default_instance().New();
	r->set_type(UserInfoUpdateRequest_UpdateType_User_IconId);
	r->set_iconid(iconID);
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendExitAdvancedRequest()
{
	ExitAdvancedRequest* r = ExitAdvancedRequest::default_instance().New();
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendUsePropRequest( unsigned int proID,message::UsePropRequest::OperateType type,const char* did /*= NULL*/)
{
	UsePropRequest* r = UsePropRequest::default_instance().New();
	r->set_type(type);
	r->set_usepropid(proID);
	if(did)
	{
		r->set_did(did);
	}
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendAchievementRequest()
{
	AchievementRequest* r = AchievementRequest::default_instance().New();
	HS_FILTER_REQUEST(r);
}

void HSRequest::SendReceiveAchievementRewardRequest( int achievementID )
{
	ReceiveAchievementRewardRequest* r = ReceiveAchievementRewardRequest::default_instance().New();
	r->set_achievementid(achievementID);
	HS_FILTER_REQUEST(r);
}

