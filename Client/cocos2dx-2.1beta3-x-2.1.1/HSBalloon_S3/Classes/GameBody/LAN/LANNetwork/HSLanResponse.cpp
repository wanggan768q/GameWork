//
//  HSLanResponse.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-12-12.
//
//

#include "HSLanResponse.h"
#include "HSLanRequest.h"
#include "HSLanRoomListScene.h"
#include "HSBattleScene.h"

static HSLanResponse* s_HSLanResponse = NULL;

HSLanResponse* HSLanResponse::ShareLanResponse()
{
    if (!s_HSLanResponse) {
        s_HSLanResponse = new HSLanResponse;
    }
    return s_HSLanResponse;
}

void HSLanResponse::HandleFactory(int commandId,google::protobuf::Message* responseMsg)
{
    CCLOG("HSLanResponse : %d ",commandId);
    
    switch (commandId)
    {
            
        case API_LAN_LanSyncUserInfoNotice:
        {
            LanSyncUserInfoNotice* pMsg = (LanSyncUserInfoNotice*)responseMsg;
            
            // 0 房主 1 成员 2群众
//            if (HS_GAME_CACHE_DATA_LAN().type() == 0)
//            {
//                CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
//                HSGamePairScene* pHSGamePairScene = dynamic_cast<HSGamePairScene*>(pScene);
//                HSLanGamePariLayer* pLayer = (HSLanGamePariLayer*)pHSGamePairScene->GetHSGamePairLayer();
//                pLayer->ResLanSyncUserInfoNotice(pMsg);
//            }else{
//                CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
//                HSLanRoomListScene* pHSLanRoomListScene = dynamic_cast<HSLanRoomListScene*>(pScene);
//                HSLanRoomListLayer* pLayer = (HSLanRoomListLayer*)pHSLanRoomListScene->GetHSLanRoomListLayer();
//                pLayer->ResponseLanSyncUserInfoNotice(pMsg);
//            }
            
            HS_GAME_CACHE()->m_LanTargetInfo.Clear();
            HS_GAME_CACHE()->m_LanTargetInfo.CopyFrom(*pMsg);
            
//            UserBasicInfo* pTarget = HS_MUTABLE_TARGET_TARGET();
//            pTarget->Clear();
//            
//            pTarget->set_uid(pMsg->uuid());
//            pTarget->set_name(pMsg->userinfo().name());
//            pTarget->set_level(99);
//            //optional uint32 style = 4;//用户头像当前状态
//            pTarget->set_wincount(pMsg->userinfo().wincount());
//            pTarget->set_losecount(pMsg->userinfo().losecount());
//            float winRate = (float)pTarget->wincount() / (float)(pTarget->wincount() + pTarget->losecount());
//            pTarget->set_winrate(winRate);
            
        }
            break;
            
        case API_LAN_LanBattleReadyNotice:
        {
            LanBattleReadyNotice* pMsg = (LanBattleReadyNotice*)responseMsg;
            
//            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
//			HSGamePairScene* pHSGamePairScene = dynamic_cast<HSGamePairScene*>(pScene);
//            HSLanGamePariLayer* pLayer = (HSLanGamePariLayer*)pHSGamePairScene->GetHSGamePairLayer();
//            
//            pLayer->ResLanBattleReadyNotice(pMsg);
            
            
        }
            break;
        case API_LAN_LanBattleDataNotice:
        {
            LanBattleDataNotice* pLanBattleDataNotice = (LanBattleDataNotice*)responseMsg;
            
            if (pLanBattleDataNotice->IsInitialized())
            {
                CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
                HSBattleScene* pHSBattleScene = dynamic_cast<HSBattleScene*>(pScene);
                if(!pHSBattleScene)
                {
                    break;
                }
                HSBattleLayer* pLayer = pHSBattleScene->GetHSBattleLayer();
                
                BattleDataResponse battleData = BattleDataResponse::default_instance();
                battleData.mutable_battleinfo()->CopyFrom(pLanBattleDataNotice->battleinfo());
                pLayer->ResponseBattleData(&battleData);
                
                CCLog("成功处理完战斗数据");
            }else{
                CCLog("非法数据 API_LAN_LanBattleDataNotice ");
            }
            
            
        }
            break;
            
        case API_LAN_LanStartBattleNotify:
        {
            LanStartBattleNotify* pMsg = (LanStartBattleNotify*)responseMsg;
            
//            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
//			HSGamePairScene* pHSGamePairScene = dynamic_cast<HSGamePairScene*>(pScene);
//            HSLanGamePariLayer* pLayer = (HSLanGamePariLayer*)pHSGamePairScene->GetHSGamePairLayer();
//            
//            pLayer->ResLanStartBattleNotify(pMsg);
        }
            break;
            
        case API_LAN_LanBattleResultNotice:
        {
            LanBattleResultNotice* pLanBattleResultNotice = (LanBattleResultNotice*)responseMsg;
            
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
			HSBattleScene* pHSBattleScene = dynamic_cast<HSBattleScene*>(pScene);
            HSBattleLayer* pLayer = pHSBattleScene->GetHSBattleLayer();
            
            pLayer->ResLanBattleResultNotice(pLanBattleResultNotice);
            
        }
            break;
            
        case API_LAN_LanQuitRoomNotice:
        {
            //LanQuitRoomNotice* pLanQuitRoomNotice = (LanQuitRoomNotice*)responseMsg;
            
//            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
//            HSGamePairScene* pHSGamePairScene = dynamic_cast<HSGamePairScene*>(pScene);
//            HSBattleScene* pHSBattleScene = dynamic_cast<HSBattleScene*>(pScene);
//            if(pHSGamePairScene)
//            {
//                HSLanGamePariLayer* pLayer = (HSLanGamePariLayer*)pHSGamePairScene->GetHSGamePairLayer();
//                
//                pLayer->ResLanQuitRoomNotice(pLanQuitRoomNotice);
//            }else if(pHSBattleScene){
//                UserBasicInfo* pTarget = HS_MUTABLE_TARGET_TARGET();
//                pTarget->Clear();
//                HS_GAME_CACHE()->m_LanTargetInfo.Clear();
//            }
            
        }
            break;
            
        case API_LAN_LanUseBufferNotice:
        {
            UseBuffResponse* r = (UseBuffResponse*)responseMsg;
			HS_GAME_CACHE()->ResponseUseBuff(r);
        }
            break;
            
        default:
            break;
    }
}




































