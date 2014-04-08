#include "HSResponse.h"
#include "HSBattleScene.h"
#include "HSLog.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameMainScene.h"
#include "HSGamePairScene.h"
#include "HSGameCoverScene.h"
#include "HSSeniortSystemScene.h"
#include "HSDailyRewardSystemLayer.h"
#include "HSSeniortSystemScene.h"
#include "HSJava.h"
#include "HSAchievemenScene.h"
#include "HSFriendsSystemScene.h"
#include "MobClickCpp.h"
#define HS_GET_RUN_SCENE(__SceneClass__) ((__SceneClass__*)(CCDirector::sharedDirector()->getRunningScene()))
#define HS_GET_RUN_SCENE_LAYER_TAG(__SceneClass__ ,__LayerClass__, __LayerTag__) (__LayerClass__*)((HS_GET_RUN_SCENE(__SceneClass__))->getChildByTag(__LayerTag__));
#define HS_GET_RUN_SCENE_LAYER(__SceneClass__ ,__LayerClass__) (__LayerClass__*)((HS_GET_RUN_SCENE(__SceneClass__))->Get##__LayerClass__());


HSResponse::HSResponse(void)
{
}

HSResponse::~HSResponse(void)
{
}

HSResponse* HSResponse::ShareResponse()
{
	static HSResponse s_hsResponse;
    
	return &s_hsResponse;
}

void HSResponse::Destroy()
{
	
}

void HSResponse::HandleFactory( int commandId,google::protobuf::Message* responseMsg )
{
    //isRecvPlayerDisengageResponse = false;
    
	switch(commandId)
	{
        case API_ErrorMessageInfo:
		{
			ErrorMessageInfo* r = (ErrorMessageInfo*)responseMsg;
			switch (r->level())
			{
                case ErrorMessageInfo_ErrorLevel_LEVEL_VIEW:
				{
					HSMessageBox(r->description().c_str());
				}
                    break;
                case ErrorMessageInfo_ErrorLevel_LEVEL_NONE:
				{
					CCLog(CCString::createWithFormat("\nSever error: [ %s ] \n",r->description().c_str())->getCString());
				}
                    break;
			}
            
            this->HandleError(r->id());
		}
            break;
        case API_RegisterResponse:
		{
			RegisterResponse* r = (RegisterResponse*)responseMsg;
			HSGameMainLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGameMainScene,HSGameMainLayer);
			layer->ResponseRegister(r);
		}
            break;
        case API_LoginResponse:
		{
			MobClickCpp::endEvent("HSLoginTime");
			LoginResponse* r = (LoginResponse*)responseMsg;
			HSGameMainLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGameMainScene,HSGameMainLayer);
			layer->ResponseLogin(r);
		}
            break;
        case API_FightingResponse:
		{
			FightingResponse* r = (FightingResponse*)responseMsg;
            
			CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
			HSGameCoverScene* pHSGameCoverScene = dynamic_cast<HSGameCoverScene*>(pScene);
			if (pHSGameCoverScene)
			{
				HSGameCoverLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGameCoverScene,HSGameCoverLayer);
				layer->ResponseFighting(r);
				break;
			}
			HSSeniortSystemScene* pHSeniortSystemScene = dynamic_cast<HSSeniortSystemScene*>(pScene);
			if (pHSeniortSystemScene)
			{
				HSSeniortSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSSeniortSystemScene,HSSeniortSystemLayer);
				layer->ResponseFighting(r);
				break;
			}
		}
            break;
        case API_TargetInfoResponse:
		{
			eventDict dict;


			dict["roomId"] =HSMath::ItoA(HS_GAME_CACHE()->m_roomId).c_str();

			MobClickCpp::event("HSPair",&dict);

			MobClickCpp::endEventWithAttributes("HSPairTime","roomId");


			//如果成功配对了，就要清楚这个变量，因为有可能上次被踢的数据还保存着
			HS_GAME_CACHE()->m_isInRoom = true;
			TargetInfoResponse* r = (TargetInfoResponse*)responseMsg;
			HS_GAME_CACHE()->CopyUser(r->self());
			CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
			HSGameCoverScene* pHSGameCoverScene = dynamic_cast<HSGameCoverScene*>(pScene);
			if (pHSGameCoverScene)
			{
				HSGameCoverLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGameCoverScene,HSGameCoverLayer);
				layer->ResponseTargetInfo(r);
				break;
			}
			HSSeniortSystemScene* pHSeniortSystemScene = dynamic_cast<HSSeniortSystemScene*>(pScene);
			if (pHSeniortSystemScene)
			{
				HSSeniortSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSSeniortSystemScene,HSSeniortSystemLayer);
				layer->ResponseTargetInfo(r);
				break;
			}
			HSGamePairScene* pHSGamePairScene = dynamic_cast<HSGamePairScene*>(pScene);
			if (pHSGamePairScene)
			{
				HSGamePairLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGamePairScene,HSGamePairLayer);
				layer->ResponseTargetInfo(r);
				break;
			}
		}
            break;
        case API_BattleReadyResponse:
		{
			BattleReadyResponse* r = (BattleReadyResponse*)responseMsg;
			HSGamePairLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGamePairScene,HSGamePairLayer);
			layer->ResponseBattleReady(r);
		}
            break;
        case API_StartBattle:
		{
			NotifyStartBattle* r = (NotifyStartBattle*)responseMsg;
			HSGamePairLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGamePairScene,HSGamePairLayer);
			layer->ResponseStartBattle(r);
			HS_GAME_CACHE()->m_isInBattle = true;
		}
            break;
        case API_PlayerDisengageResponse:
		{

			HS_GAME_CACHE()->m_isInRoom = false;

			PlayerDisengageResponse* r = (PlayerDisengageResponse*)responseMsg;
			CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
			HSGamePairScene* pHSGamePairScene = dynamic_cast<HSGamePairScene*>(pScene);
			if (pHSGamePairScene)
			{
				HSGamePairLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGamePairScene,HSGamePairLayer);
				layer->ResponsePlayerDisengage(r);
			}
			else
			{
				HS_MUTABLE_TARGET_TARGET()->Clear();
				HS_GAME_CACHE()->m_pTargetInfoResponse->set_dungoenid("");
			}
            CCLog("服务器告诉 离开");
		}
            break;
        case API_KickOutDungoen:
		{
			NotifyKickedOutDungoen* r = (NotifyKickedOutDungoen*)responseMsg;
			HSLoadingLayer::ShareLoading()->setVisible(false);
			if(r->did() == HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid())
			{
				HS_GO_SCENE(HS_SCENE_CoverScene);
				HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle)->Closed(Close_Nomal);
				HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
				if(r->cause()==NotifyKickedOutDungoen_KickedOutCause_Gold_Coin_Shortage)//金钱不足
				{
					HSJava::ShaderJava()->Pay(HS_GAME_CACHE()->roomGold-HS_GAME_CACHE()->GetGold());
				}
				HS_GAME_CACHE()->m_isInRoom = false;
				HS_GAME_CACHE()->m_isInBattle = false;
			}
			else
			{
				CCLog("被提出的房间ID错误 id=%s,myid=%s",r->did().c_str(),HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str());
			}
		}
        break;
        case API_BattleDataResponse:
		{
			BattleDataResponse* r = (BattleDataResponse*)responseMsg;
			CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
			HSBattleScene* pHSBattleScene = dynamic_cast<HSBattleScene*>(pScene);
			if (pHSBattleScene)
			{
				HSBattleLayer* layer = HS_GET_RUN_SCENE_LAYER(HSBattleScene,HSBattleLayer);
				layer->ResponseBattleData(r);
			}
		}
            break;
        case API_BattleResultResponse:
		{
			HS_GAME_CACHE()->m_playCount+=1;

			if(HS_GAME_CACHE()->m_playCount ==1)
			{
				MobClickCpp::event("HSPlay1");
			}
			else if(HS_GAME_CACHE()->m_playCount ==5)
			{
				MobClickCpp::event("HSPlay5");
			}
			else if(HS_GAME_CACHE()->m_playCount ==15)
			{
				MobClickCpp::event("HSPlay15");
			}

			HS_GAME_CACHE()->m_isInBattle = false;
			CCLOG("isInOverLayer = true");
			HS_GAME_CACHE()->m_isInOverLayer = true;
			BattleResultResponse* r = (BattleResultResponse*)responseMsg;
			HSBattleLayer* layer = HS_GET_RUN_SCENE_LAYER(HSBattleScene,HSBattleLayer);
			layer->ResponseBattleResult(r);
		}
            break;
        case API_UseBuffResponse:
		{
			UseBuffResponse* r = (UseBuffResponse*)responseMsg;
			HS_GAME_CACHE()->ResponseUseBuff(r);
		}
            break;
        case API_NotifyChangeBuff:
		{
			NotifyChangeBuff* r = (NotifyChangeBuff*)responseMsg;
			HS_GAME_CACHE()->ResponseNotifyChangeBuff(r);
		}
            break;
        case API_HeartbeatBattleResponse:
		{
			//HeartbeatResponse* r = (HeartbeatResponse*)responseMsg;
			CCLog("Ping: Battle");
		}
            break;
        case API_HeartbeatGameResponse:
		{
			//HeartbeatResponse* r = (HeartbeatResponse*)responseMsg;
			CCLog("Ping: Logic");
		}
            break;
        case API_FriendListResponse:
		{
            FriendListResponse* r = (FriendListResponse*)responseMsg;
//            FriendListResponse_PlayerInfo* pSelfInfo = r->add_friendlist();
//            pSelfInfo->set_game_uuid(HS_GAME_CACHE_DATA()->uid());
//            pSelfInfo->set_friendname(HS_TARGET_SELF().name());
//            pSelfInfo->set_gamescore(HS_GAME_CACHE()->GetSelfGameScore());
//            pSelfInfo->set_headicon(HS_TARGET_SELF().iconid());
//            pSelfInfo->set_isallowgive(false);
//            pSelfInfo->set_state(FriendListResponse_PlayerInfo_State_State_Online);
//            pSelfInfo->set_friendnickname(HS_TARGET_SELF().name());
            
            for (int i=0; i<r->friendlist_size(); ++i)
            {
                FriendListResponse_PlayerInfo* p1 = r->mutable_friendlist(i);
                CC_BREAK_IF( (++i) >= r->friendlist_size());
                FriendListResponse_PlayerInfo* p2 = r->mutable_friendlist(i);
                if (p1->gamescore() < p2->gamescore())
                {
                    r->mutable_friendlist()->SwapElements(i - 1, i);
                }
            }
            HS_GAME_CACHE()->m_FriendListResponse.Clear();
            HS_GAME_CACHE()->m_FriendListResponse.CopyFrom(*r);
		}
            break;
        case API_AddFriendResponse:
		{
#if WIN32
			throw std::exception("API_AddFriendResponse");
#endif
		}
		break;
	case API_SearchUserInfoResponse:
		{
			SearchUserInfoResponse* r = (SearchUserInfoResponse*)responseMsg;
			HS_GAME_CACHE()->CopyUser(r->userinfo());
		}
            break;
        case API_UsePropResponse:
		{
			UsePropResponse* r = (UsePropResponse*)responseMsg;
			if (r->state() == UsePropResponse_State_State_Succeed)
			{
				HS_MUTABLE_TARGET_SELF()->set_golds(r->golds());

				if(HS_GAME_CACHE()->m_refrushUserInfo)
				{
					HS_GAME_CACHE()->m_refrushUserInfo = false;
					HSRequest::ShareRequest()->SendSearchUserInfoRequest();
				}
			}
			else if(r->state()==UsePropResponse_State_State_NOMONEY)
			{
				HSJava::ShaderJava()->ShowToast("user prop fail",0);
			}
			else if(r->state()==UsePropResponse_State_State_NOMONEY)
			{
				HSJava::ShaderJava()->ShowToast("user prop fail case:not enouth money ",0);
			}
		}
            break;
            
        case API_DestroyBalloonResponse:
		{
#if WIN32
			throw std::exception("API_DestroyBalloonResponse");
#endif
		}
            break;
            
        case API_RoomDataResponse:
		{
			RoomDataResponse* r=(RoomDataResponse*)responseMsg;
			HS_GAME_CACHE()->m_RoomDataResponse.Clear();
			HS_GAME_CACHE()->m_RoomDataResponse.CopyFrom(*r);
			HS_GO_SCENE(HS_SCENE_SeniortSystemScene);
		}
            break;
            
        case API_ClaimedDailyRewardResponse:
		{
			ClaimedDailyRewardResponse* r=(ClaimedDailyRewardResponse*)responseMsg;
            
			if(r->state()==ClaimedDailyRewardResponse::GetState_Success)
			{
				HS_GAME_CACHE()->AddGold(r->addgoldnumber());

				HSJava::ShaderJava()->ShowToast(CCString::createWithFormat(L("Daily_Gift"),r->addgoldnumber())->getCString(),1);
			}
			else
			{
				//HSJava::ShaderJava()->ShowToast("DailyReward fail",1);
			}
		}
        break;
            
        case API_UserInfoUpdateResponse:
		{
			UserInfoUpdateResponse* r = (UserInfoUpdateResponse*)responseMsg;
			switch (HS_GAME_CACHE()->m_UserInfoUpdateRequest_UpdateType)
			{
                case UserInfoUpdateRequest_UpdateType_User_Name:
				{
					HS_MUTABLE_GAME_CACHE_DATA()->set_issendnickname(true);
				}
                    break;
                case UserInfoUpdateRequest_UpdateType_User_IconId:
				{
					if(r->state()==UserInfoUpdateResponse_UpdateState_OK)
					{
						HSRequest::ShareRequest()->SendSearchUserInfoRequest();
					}
					else if(r->state() ==UserInfoUpdateResponse_UpdateState_FAIL)
					{
                        
					}
					else if(r->state() ==UserInfoUpdateResponse_UpdateState_NOMONEY)//金钱不够
					{
						HSJava::ShaderJava()->Pay(HS_GAME_CACHE()->GetPropInfoData()->headlist(HS_GAME_CACHE()->changeheadIndex).gold()-HS_GAME_CACHE()->GetGold()  );
					}
					HS_GAME_CACHE()->changeheadIndex = 0;
				}
                    break;
                default:
                    break;
			}
		}
            break;
        case API_ExitAdvancedResponse:
		{
			ExitAdvancedResponse* r = (ExitAdvancedResponse*)responseMsg;
			HSSeniortSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSSeniortSystemScene,HSSeniortSystemLayer);
			layer->ResponseExitAdvanced(r);
		}
            break;
        case API_AchievementResponse:
		{
			AchievementResponse* r = (AchievementResponse*)responseMsg;
			HSGameCoverLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGameCoverScene,HSGameCoverLayer);
			layer->ResponseAchievement(r);
		}
            break;
        case API_ReceiveAchievementRewardResponse:
		{
			ReceiveAchievementRewardResponse* r = (ReceiveAchievementRewardResponse*)responseMsg;
            HSAchievemenLayer* layer = HS_GET_RUN_SCENE_LAYER(HSAchievemenScene,HSAchievemenLayer);
			layer->ResponseReceiveAchievementReward(r);
		}
		break;
		case API_RechargeResponse:
			{
				NotifyRecharge* r = (NotifyRecharge*)responseMsg;

				HS_MUTABLE_TARGET_SELF()->set_golds(r->totalgolds());

				//HS_GAME_CACHE()->AddGold(r->totalgolds());
			}
		break;
        case API_SendEmailResponse:
        {
            //SendEmailResponse* r = (SendEmailResponse*)responseMsg;
            CCLog("Send Email OK");
        }
            break;
        case API_EmailResponse:
        {
            EmailResponse* r = (EmailResponse*)responseMsg;
            //EmailResponse_EmailInfo* rIn = r->add_emaillist();
            //rIn->set_email_id(32113);
            //rIn->set_givepalyername("ad");
            
			HS_GAME_CACHE()->m_EmailResponse.Clear();
            HS_GAME_CACHE()->m_EmailResponse.CopyFrom(*r);
            
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
			HSFriendsSystemScene* pFriendScene = dynamic_cast<HSFriendsSystemScene*>(pScene);
			if (pFriendScene)
            {
                HSFriendsSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSFriendsSystemScene,HSFriendsSystemLayer);
                layer->ResponseEmail(r);
            }
        }
            break;
        case API_OpenEmailResponse:
        {
            OpenEmailResponse* r = (OpenEmailResponse*)responseMsg;
            HS_MUTABLE_TARGET_SELF()->set_golds(r->gold());
            CCLog("Open Email OK");
        }
            break;
            
        case API_AddressBookResponse:
        {
            AddressBookResponse* r = (AddressBookResponse*)responseMsg;
            HS_GAME_CACHE()->m_AddressBookResponse.Clear();
            HS_GAME_CACHE()->m_AddressBookResponse.CopyFrom(*r);
            HSFriendsSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSFriendsSystemScene,HSFriendsSystemLayer);
            layer->ResponseAddressBook(r);
        }
            break;
        default:
		if (responseMsg)
		{
			HSMessageBox(responseMsg->GetTypeName() + "   Don't deal with ");
		}
            
            break;
	}
    
}



















void HSResponse::HandleError(int id)
{
	CCLog("ErrorMessage id= %d", id);
    
    switch (id)
    {
    	//HS_GAME_CACHE()->m_isInRoom =true;

        case 2002:  //  副本不存在
        {
        	if(HS_GAME_CACHE()->m_isInRoom)
        	{
        		if(HS_GAME_CACHE()->m_isInBattle)
        		{
        			//quit
        			HS_GO_SCENE(HS_SCENE_CoverScene);
					HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle)->Closed(Close_Active);
					HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
					CCLOG("处理异常: 副本不存在 inroom inbattle");
        		}
        		else
        		{
        			if(HS_GAME_CACHE()->m_isInOverLayer)
        			{
        				CCLOG("处理异常: 副本不存在 inroom notInbattle inOverLayer 什么也不做");
        			}
        			else
        			{
        				HS_GO_SCENE(HS_SCENE_CoverScene);
						HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle)->Closed(Close_Active);
						HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
						CCLOG("处理异常: 副本不存在 inroom notInbattle =============");
        			}

        		}
        	}
        	else
        	{
        		if(HS_GAME_CACHE()->m_isInBattle)
				{
        			HS_GO_SCENE(HS_SCENE_CoverScene);
        			HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle)->Closed(Close_Active);
					HSSocketPool::ShareSocketPool()->SetPingLongLink(false);

					CCLOG("处理异常: 副本不存在 not inroom inbattle");
				}
				else//不在房间，也不在战斗中，这种情况不要处理
				{
					CCLog("not inromm not inbattle，这种情况不要处理");
				}
        	}
        }
            break;
            
        case 1002://需要跳转计费(普通计费)xia
        {
            //			int sd = 0;
            //			if(HS_GAME_CACHE()->seniorRoomId !=-1)
            //			{
            //				sd = HS_GAME_CACHE()->seniorRoomId;
            //				HS_GAME_CACHE()->seniorRoomId =-1;
            //			}
            //			else
            //			{
            //				Json::Value jsonData;
            //				jsonData["JNI_ID"] = Json::Value(1001);
            //				jsonData["PAY_UID"] = Json::Value(HS_GAME_CACHE_DATA()->uid().c_str());
            //				jsonData["goodID"] =HS_GAME_CACHE()->GetPropInfoData()->buygoldlist(sd).id();
            //				jsonData["size"] = 1;
            //				jsonData["total"] = HS_GAME_CACHE()->GetPropInfoData()->buygoldlist(sd).money() * 100;
            //				HSJson* pJson = HSJson::CreateWithWriter();
            //				std::string data = pJson->Writer(jsonData);
            //				HSJava::ShaderJava()->JavaExec(data.c_str());
            //			}
        }
            break;
        default:
            break;
    }
}

