//
//  HSLanRequest.h
//  HSBalloon_S3
//
//  Created by Ambition on 13-12-12.
//
//

#ifndef __HSBalloon_S3__HSLanRequest__
#define __HSBalloon_S3__HSLanRequest__
#pragma once
#include "HSRequest.h"


class HSLanRequest : public HSRequest
{
public:
    HSLanRequest();
    ~HSLanRequest();
    
public:
	static HSLanRequest* ShareLanRequest();
    
    
    
#pragma mark - SendJsonData
    
    void SendLanCreateRoom( const char* userName );
    
    void SendLanSearchRoomRequest();
    
    void SendLanJoinRoomRequest(const char* userName, const char* roomName,const char* ssid);
    
    
    
    
    
#pragma mark - SendGameData
    
    void SendLanSyncUserInfoNotice();
    
    void SendLanStartBattleNotify();
    
    void SendLanBattleDataNotice(LanBattleDataNotice* pData);
    
    void SendLanBattleReadyNotice(const LanBattleReadyNotice_TYPE_ACTION& action);
    
    void SendLanBattleResultNotice(const LanBattleResultNotice_GameStatus& value,const LanUserInfoData& userInfo);
    
    void SendLanQuitRoomNotice();
    
    void SendRecoverWifi();
    
    void SendUseBuffRequest(const char* did,const char* targetId,int propid);
};














#endif /* defined(__HSBalloon_S3__HSLanRequest__) */
