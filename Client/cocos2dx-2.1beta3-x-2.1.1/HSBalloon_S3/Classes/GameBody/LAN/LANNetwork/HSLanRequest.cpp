//
//  HSLanRequest.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-12-12.
//
//

#include "HSLanRequest.h"
#include "HSJava.h"
#include "HSJson.h"
#include "HSLanFilter.h"
#include "HSLanActionManager.h"

#define HS_LAN_FILTER_REQUEST(request) HSLanFilter::SharedLanFilter()->CreaterMessage((::google::protobuf::Message*)request)

static HSLanRequest* s_HSLanRequest = NULL;

HSLanRequest::HSLanRequest()
{
    
}
HSLanRequest::~HSLanRequest()
{
    
}

HSLanRequest* HSLanRequest::ShareLanRequest()
{
    if (!s_HSLanRequest)
    {
        s_HSLanRequest = new HSLanRequest;
    }
    return s_HSLanRequest;
}

void HSLanRequest::SendLanCreateRoom( const char* userName )
{
    //设置自己为房主
    HS_MUTABLE_GAME_CACHE_DATA_LAN()->set_type(0);
    
    HS_GAME_CACHE()->m_isJoinRoomSucceed = true;
    HSJson* pJson = HSJson::CreateWithWriter();
    HSJsonValue v;
    v["JNI_ID"] = 3000;
    v["JNI_EGG_USER_NAME"] = userName;
    v["JNI_EGG_ROOM_MAXNUM"] = 2;
    
    HSJava::ShaderJava()->JavaExec(pJson->Writer(v).c_str());
    
    pJson->release();
    
    HSLanActionManager::ShareLanActionManager()->AddAction(Lan_Action_CreateRoom);
    
}

void HSLanRequest::SendRecoverWifi()
{
    HSJson* pJson = HSJson::CreateWithWriter();
    HSJsonValue v;
    v["JNI_ID"] = 3009;
    HSJava::ShaderJava()->JavaExec(pJson->Writer(v).c_str());
    
    HSLanActionManager::ShareLanActionManager()->AddAction(Lan_Action_RestoreWIFI);
}

void HSLanRequest::SendLanSearchRoomRequest()
{
    HSMessageBox("SendLanSearchRoomRequest");
    HSJson* pJson = HSJson::CreateWithWriter();
    HSJsonValue v;
    v["JNI_ID"] = 3001;
    v["JNI_EGG_SEARCH_TYPE"] = 0;
    
    HSJava::ShaderJava()->JavaExec(pJson->Writer(v).c_str());
    
    pJson->release();
    
    HSLanActionManager::ShareLanActionManager()->AddAction(Lan_Action_SearchRoom);
}

void HSLanRequest::SendLanJoinRoomRequest(const char* userName, const char* roomName,const char* ssid)
{
    HS_GAME_CACHE()->m_isJoinRoomSucceed = true;
    
    HSJson* pJson = HSJson::CreateWithWriter();
    HSJsonValue v;
    v["JNI_ID"] = 3002;
    v["JNI_EGG_USER_NAME"] = userName;
    v["JNI_EGG_ROOM_NAME"] = roomName;
    v["JNI_EGG_SSID"] = ssid;
    
    HSJava::ShaderJava()->JavaExec(pJson->Writer(v).c_str());
    
    pJson->release();
    
    HSLanActionManager::ShareLanActionManager()->AddAction(Lan_Action_JoinRoom);
}

void HSLanRequest::SendLanSyncUserInfoNotice()
{
	CCLOG("SendLanSyncUserInfoNotice");
    LanSyncUserInfoNotice* pSelfData = LanSyncUserInfoNotice::default_instance().New();
    
    pSelfData->set_uuid(HS_GAME_CACHE_DATA_LAN().uuid());
    pSelfData->mutable_userinfo()->CopyFrom(HS_GAME_CACHE_DATA_LAN());
    
    HS_LAN_FILTER_REQUEST(pSelfData);
}

void HSLanRequest::SendLanStartBattleNotify()
{
    LanStartBattleNotify* p = LanStartBattleNotify::default_instance().New();
    p->set_type(LanStartBattleNotify_NotifyType_START);
    
    HS_LAN_FILTER_REQUEST(p);
}

void HSLanRequest::SendLanBattleDataNotice(LanBattleDataNotice* pData)
{
    LanBattleDataNotice* p = LanBattleDataNotice::default_instance().New();
    p->CopyFrom(*pData);
    
    HS_LAN_FILTER_REQUEST(p);
}

void HSLanRequest::SendLanBattleReadyNotice(const LanBattleReadyNotice_TYPE_ACTION& action)
{
    LanBattleReadyNotice* p = LanBattleReadyNotice::default_instance().New();
    p->set_uuid(HS_GAME_CACHE_DATA_LAN().uuid());
    p->set_type(action);
    
    HS_LAN_FILTER_REQUEST(p);
}

void HSLanRequest::SendLanBattleResultNotice(const LanBattleResultNotice_GameStatus& value,const LanUserInfoData& userInfo)
{
    LanBattleResultNotice* p = LanBattleResultNotice::default_instance().New();
    p->set_uuid(HS_GAME_CACHE_DATA_LAN().uuid());
    p->set_status(value);
    p->mutable_userinfo()->CopyFrom(userInfo);
    
    HS_LAN_FILTER_REQUEST(p);
}

void HSLanRequest::SendLanQuitRoomNotice()
{
    LanQuitRoomNotice* p = LanQuitRoomNotice::default_instance().New();
    p->set_uuid(HS_GAME_CACHE_DATA_LAN().uuid());
    
    HS_LAN_FILTER_REQUEST(p);
    
    HSLanActionManager::ShareLanActionManager()->AddAction(Lan_Action_QuitRoom);
}

void HSLanRequest::SendUseBuffRequest(const char* did,const char* targetId,int propid)
{
	UseBuffRequest* r = UseBuffRequest::default_instance().New();
	r->set_did(did);
	r->set_targetuid(targetId);
	r->set_propid(propid);
    
	HS_LAN_FILTER_REQUEST(r);
}























