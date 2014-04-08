#include "HSResponse.h"
#include "HSBattleScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameMainScene.h"
#include "HSDailyRewardSystemLayer.h"
#include "HSJava.h"
#include "HSAchievemenScene.h"
#include "MobClickCpp.h"

//New
#include "HSPairSystemScene.h"
#include "HSFigureSystemScene.h"
#include "HSChangeFigureScene.h"
#include "HSShowEndurance.h"
#include "HSStartGameScene.h"


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
					HSMessageBox("ErrorMessage: [ %s ]",r->description().c_str());
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
            
            //			CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            //			HSGameCoverScene* pHSGameCoverScene = dynamic_cast<HSGameCoverScene*>(pScene);
            //			if (pHSGameCoverScene)
            //			{
            //				HSGameCoverLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGameCoverScene,HSGameCoverLayer);
            //				layer->ResponseFighting(r);
            //				break;
            //			}
            //			HSSeniortSystemScene* pHSeniortSystemScene = dynamic_cast<HSSeniortSystemScene*>(pScene);
            //			if (pHSeniortSystemScene)
            //			{
            //				HSSeniortSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSSeniortSystemScene,HSSeniortSystemLayer);
            //				layer->ResponseFighting(r);
            //				break;
            //			}
            
            
            HSPairSystemLayer* l = HS_GET_RUN_SCENE_LAYER(HSPairSystemScene,HSPairSystemLayer);
            if(l)
            {
                l->ResponseFighting(r);
            }
		}
            break;
        case API_TargetInfoResponse:
		{
			eventDict dict;
            
            
			dict["roomId"] =HSMath::ItoA(HS_GAME_CACHE()->m_roomId).c_str();
            
			MobClickCpp::event("HSPair",&dict);
            
			MobClickCpp::endEventWithAttributes("HSPairTime","roomId");
            
            TargetInfoResponse* r = (TargetInfoResponse*)responseMsg;
            
			HS_GAME_CACHE()->m_pTargetInfoResponse->CopyFrom(*r);
            
            HS_GAME_CACHE()->CopyUser(r->self());
            
            HSPairSystemLayer* l = HS_GET_RUN_SCENE_LAYER(HSPairSystemScene,HSPairSystemLayer);
            if(l)
            {
                l->ResponseTargetInfo(r);
            }
            
            //			//如果成功配对了，就要清楚这个变量，因为有可能上次被踢的数据还保存着
            //			HS_GAME_CACHE()->m_isInRoom = true;
            //			TargetInfoResponse* r = (TargetInfoResponse*)responseMsg;
            //			HS_GAME_CACHE()->CopyUser(r->self());
            //			CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            //			HSGameCoverScene* pHSGameCoverScene = dynamic_cast<HSGameCoverScene*>(pScene);
            //			if (pHSGameCoverScene)
            //			{
            //				HSGameCoverLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGameCoverScene,HSGameCoverLayer);
            //				layer->ResponseTargetInfo(r);
            //				break;
            //			}
            //			HSSeniortSystemScene* pHSeniortSystemScene = dynamic_cast<HSSeniortSystemScene*>(pScene);
            //			if (pHSeniortSystemScene)
            //			{
            //				HSSeniortSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSSeniortSystemScene,HSSeniortSystemLayer);
            //				layer->ResponseTargetInfo(r);
            //				break;
            //			}
            //			HSGamePairScene* pHSGamePairScene = dynamic_cast<HSGamePairScene*>(pScene);
            //			if (pHSGamePairScene)
            //			{
            //				HSGamePairLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGamePairScene,HSGamePairLayer);
            //				layer->ResponseTargetInfo(r);
            //				break;
            //			}
		}
            break;
        case API_BattleReadyResponse:
		{
			BattleReadyResponse* r = (BattleReadyResponse*)responseMsg;
            //			HSGamePairLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGamePairScene,HSGamePairLayer);
            //			layer->ResponseBattleReady(r);
            HSPairSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSPairSystemScene,HSPairSystemLayer);
			layer->ResponseBattleReady(r);
		}
            break;
        case API_StartBattle:
		{
			NotifyStartBattle* r = (NotifyStartBattle*)responseMsg;
            //			HSGamePairLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGamePairScene,HSGamePairLayer);
            //			layer->ResponseStartBattle(r);
            //			HS_GAME_CACHE()->m_isInBattle = true;
            HSPairSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSPairSystemScene,HSPairSystemLayer);
			layer->ResponseStartBattle(r);
			HS_GAME_CACHE()->m_isInBattle = true;
		}
            break;
        case API_PlayerDisengageResponse:
		{
            
			HS_GAME_CACHE()->m_isInRoom = false;
            
			PlayerDisengageResponse* r = (PlayerDisengageResponse*)responseMsg;
			CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
			HSPairSystemScene* pHSPairSystemScene= dynamic_cast<HSPairSystemScene*>(pScene);
			if (pHSPairSystemScene)
			{
				HSPairSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSPairSystemScene,HSPairSystemLayer);
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
				
				HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle)->Closed(Close_Nomal);
				HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
                
                switch (r->cause())
                {
                    case NotifyKickedOutDungoen_KickedOutCause_Gold_Coin_Shortage:  //金钱不足
                    {
                        //HSJava::ShaderJava()->Pay(HS_GAME_CACHE()->roomGold - HS_GAME_CACHE()->GetGold());
                        HSMessageBox("金钱不足");
                    }
                        break;
                    case NotifyKickedOutDungoen_KickedOutCause_Strength_Not_Enough:  //体力不足
                    {
                        //HSJava::ShaderJava()->Pay(HS_GAME_CACHE()->roomGold - HS_GAME_CACHE()->GetGold());
                        HSMessageBox("体力不足");
                    }
                        break;
                    case NotifyKickedOutDungoen_KickedOutCause_Time_Out:  //超时
                    {
                        //HSJava::ShaderJava()->Pay(HS_GAME_CACHE()->roomGold-HS_GAME_CACHE()->GetGold());
                        CCLog("超时 被踢");
                    }
                        break;
                    default:
                        break;
                }
				HS_GO_SCENE(HS_SCENE_StartGameScene);
                HS_GAME_CACHE()->m_pTargetInfoResponse->Clear();
				HS_GAME_CACHE()->m_isInRoom = false;
				HS_GAME_CACHE()->m_isInBattle = false;
			}
			else
			{
				CCLog("被提出的房间ID错误: id= %s \n myid = %s \n",r->did().c_str(),HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str());
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
			HS_GAME_CACHE()->m_isInOverLayer = true;
			BattleResultResponse* r = (BattleResultResponse*)responseMsg;
			HSBattleLayer* layer = HS_GET_RUN_SCENE_LAYER(HSBattleScene,HSBattleLayer);
			layer->ResponseBattleResult(r);
            
            //HSRequest::ShareRequest()->SendSearchStrengthRequest();
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
            FriendListResponse_PlayerInfo* pSelfInfo = r->add_friendlist();
            pSelfInfo->set_game_uuid(HS_GAME_CACHE_DATA()->uid());
            pSelfInfo->set_friendname(HS_TARGET_SELF().name());
            pSelfInfo->set_gamescore(HS_GAME_CACHE()->GetSelfGameScore());
            pSelfInfo->set_headicon(HS_TARGET_SELF().iconid());
            pSelfInfo->set_isallowgive(false);
            pSelfInfo->set_state(FriendListResponse_PlayerInfo_State_State_Online);
            pSelfInfo->set_friendnickname(HS_TARGET_SELF().name());
            
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
            
            CCLog("FriendCount: %d",r->friendlist_size());
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
            CCLog("获取高级场房间列表 响应");
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
                case UserInfoUpdateRequest_UpdateType_User_Figure:
                {
                    ChangeFigureResponse* change = ChangeFigureResponse::default_instance().New();
                    
                    if(r->state()==UserInfoUpdateResponse_UpdateState_OK)
					{
						HSRequest::ShareRequest()->SendSearchUserInfoRequest();
                        change->set_state(ChangeFigureResponse_ChangeState_SUCCESS);
					}
					else if(r->state() ==UserInfoUpdateResponse_UpdateState_FAIL)
					{
                        change->set_state(ChangeFigureResponse_ChangeState_FAIL);
					}
					else if(r->state() == UserInfoUpdateResponse_UpdateState_NOMONEY)//金钱不够
					{
						HSJava::ShaderJava()->Pay(HS_GAME_CACHE()->GetPropInfoData()->headlist(HS_GAME_CACHE()->changeheadIndex).gold()-HS_GAME_CACHE()->GetGold()  );
					}
                    HSChangeFigureLayer* layer = HS_GET_RUN_SCENE_LAYER(HSChangeFigureScene,HSChangeFigureLayer);
                    layer->ResponseChangeFigure(change);
                    CC_SAFE_DELETE(change);
                }
                    break;
                default:
                    break;
			}
		}
            break;
        case API_ExitAdvancedResponse:
		{
			//ExitAdvancedResponse* r = (ExitAdvancedResponse*)responseMsg;
            
            CCLog("退出高级场 响应");
		}
            break;
        case API_AchievementResponse:
		{
			AchievementResponse* r = (AchievementResponse*)responseMsg;
            HS_GAME_CACHE()->m_AchievementResponse.CopyFrom(*r);
            CCLog("成就 响应 %d",r->achievementlist_size());
		}
            break;
        case API_ReceiveAchievementRewardResponse:
		{
			ReceiveAchievementRewardResponse* r = (ReceiveAchievementRewardResponse*)responseMsg;
            HSAchievemenLayer* layer = HS_GET_RUN_SCENE_LAYER(HSAchievemenScene,HSAchievemenLayer);
			layer->ResponseReceiveAchievementReward(r);
		}
            break;
		case API_RechargeResponse:  //充值
        {
            NotifyRecharge* r = (NotifyRecharge*)responseMsg;
            
            HS_MUTABLE_TARGET_SELF()->set_golds(r->totalgolds());
            
            if(HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid() != "")
            {
                HSRequest::ShareRequest()->SendNotifyUserUpdateRequest();
            }
            
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
        }
            break;
        case API_GameSearchStrengthResponse:
        {
            GameSearchStrengthResponse* r = (GameSearchStrengthResponse*)responseMsg;
            
            HSShowEndurance::S_LAST_REMAIN = 0;
            HSShowEndurance::S_CURRENT_ENDURANCE_COUNT = r->strength();
            HSShowEndurance::S_CURRENT_OPERATION_ENDURANCE_INDEX = HSShowEndurance::S_CURRENT_ENDURANCE_COUNT + 1;
            HSShowEndurance::S_START_SEC = r->seconds() % HSShowEndurance::S_C_MAX_SEC;
            
            CCLog("数据库体力值: %d     -  剩余秒: %d",r->strength(),HSShowEndurance::S_START_SEC);
            
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            HSGameMainScene* pHSGameMainScene = dynamic_cast<HSGameMainScene*>(pScene);
            if (pHSGameMainScene)
            {
                HSGameMainLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGameMainScene,HSGameMainLayer);
                if(layer)
                {
                    layer->ResponseSearchStrength(r);
                }
            }
            
        }
            break;
        case API_MatchSearchStrengthResponse:
        {
            MatchSearchStrengthResponse* r = (MatchSearchStrengthResponse*)responseMsg;
            
            HSShowEndurance::S_LAST_REMAIN = 0;
            HSShowEndurance::S_CURRENT_ENDURANCE_COUNT = r->strength();
            HSShowEndurance::S_CURRENT_OPERATION_ENDURANCE_INDEX = HSShowEndurance::S_CURRENT_ENDURANCE_COUNT + 1;
            HSShowEndurance::S_START_SEC = r->seconds() % HSShowEndurance::S_C_MAX_SEC;
            
            CCLog("数据库体力值: %d     -  剩余秒: %d",r->strength(),HSShowEndurance::S_START_SEC);
        }
            break;
        case API_GameUpgradeFigureLevelResponse:
        {
            GameUpgradeFigureLevelResponse* r = (GameUpgradeFigureLevelResponse*)responseMsg;
            
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            HSFigureSystemScene* pHSFigureSystemScene = dynamic_cast<HSFigureSystemScene*>(pScene);
            if(pHSFigureSystemScene)
            {
                HSFigureSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSFigureSystemScene,HSFigureSystemLayer);
                if(layer)
                {
                    layer->ResponseGameUpgradeFigureLevel(r);
                }
            }
			
        }
            break;
        case API_GameBuyFigureResponse:
        {
            GameBuyFigureResponse* r = (GameBuyFigureResponse*)responseMsg;
            
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            HSChangeFigureScene* pHSChangeFigureScene = dynamic_cast<HSChangeFigureScene*>(pScene);
            if(pHSChangeFigureScene)
            {
                HSChangeFigureLayer* layer = HS_GET_RUN_SCENE_LAYER(HSChangeFigureScene,HSChangeFigureLayer);
                layer->ResponseGameBuyFigure(r);
            }
            
        }
            break;
        case API_MatchBuyFigureResponse:
        {
            //MatchBuyFigureResponse* r = (MatchBuyFigureResponse*)responseMsg;
            CCLog("");
        }
            break;
        case API_MatchUpgradeFigureLevelResponse:
        {
            MatchUpgradeFigureLevelResponse* r = (MatchUpgradeFigureLevelResponse*)responseMsg;
            GameUpgradeFigureLevelResponse* upgrade = GameUpgradeFigureLevelResponse::default_instance().New();
            
            switch (r->status()) {
                case message::MatchUpgradeFigureLevelResponse_Status_SUCCESS:
                {
                    upgrade->set_status(GameUpgradeFigureLevelResponse_Status_SUCCESS);
                }
                    break;
                case message::MatchUpgradeFigureLevelResponse_Status_FAIL:
                {
                    HSMessageBox("升级形象 失败");
                    upgrade->set_status(GameUpgradeFigureLevelResponse_Status_FAIL);
                }
                    break;
                case message::MatchUpgradeFigureLevelResponse_Status_NOMONEY:
                {
                    HSMessageBox("升级形象 金币不足");
                    upgrade->set_status(GameUpgradeFigureLevelResponse_Status_NOMONEY);
                }
                    break;
                    
                default:
                    break;
            }
            
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            HSFigureSystemScene* pHSFigureSystemScene = dynamic_cast<HSFigureSystemScene*>(pScene);
            if(pHSFigureSystemScene)
            {
                HSFigureSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSFigureSystemScene,HSFigureSystemLayer);
                if(layer)
                {
                    layer->ResponseGameUpgradeFigureLevel(upgrade);
                }
            }
            
            
            CC_SAFE_DELETE(upgrade);

        }
            break;
        case API_ChangeFigureResponse:
        {
            //战斗中更换形象
            ChangeFigureResponse* r = (ChangeFigureResponse*)responseMsg;
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            HSChangeFigureScene* pHSChangeFigureScene = dynamic_cast<HSChangeFigureScene*>(pScene);
            if(pHSChangeFigureScene)
            {
                HSChangeFigureLayer* layer = HS_GET_RUN_SCENE_LAYER(HSChangeFigureScene,HSChangeFigureLayer);
                layer->ResponseChangeFigure(r);
            }
        }
            break;
        case API_NotifyUserUpdateResponse:
        {
            NotifyUserUpdateResponse* r = (NotifyUserUpdateResponse*)responseMsg;
        }
            break;
        case API_ValidateStrengthResponse:
        {
            ValidateStrengthResponse* r = (ValidateStrengthResponse*)responseMsg;
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
			HSStartGameScene* pHSStartGameScene = dynamic_cast<HSStartGameScene*>(pScene);
            HSFigureSystemScene* pHSFigureSystemScene = dynamic_cast<HSFigureSystemScene*>(pScene);
			if (pHSStartGameScene)
            {
                HSStartGameLayer* layer = HS_GET_RUN_SCENE_LAYER(HSStartGameScene,HSStartGameLayer);
                layer->ResponseValidateStrength(r);
            }else if(pHSFigureSystemScene)
            {
                HSFigureSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSFigureSystemScene,HSFigureSystemLayer);
                layer->ResponseValidateStrength(r);
            }
            if(r->result() == ValidateStrengthResponse_RESULT_TYPE_NOT)
            {
                HSMessageBox("体力不足");
                //HSRequest::ShareRequest()->SendSearchStrengthRequest();
            }
        }
            break;
        default:
        {
            if (responseMsg)
            {
                HSMessageBox("[ %s ] Don't deal with ",responseMsg->GetTypeName().c_str());
            }
        }
            break;
	}
    
}















void HSResponse::HandleError(int id)
{
	CCLog("ErrorMessage id= %d", id);
    
    switch (id)
    {
        case 2002:  //  副本不存在
        {
        	if(HS_GAME_CACHE()->m_isInRoom)
        	{
        		if(HS_GAME_CACHE()->m_isInBattle)
        		{
        			//quit
                    HS_GO_SCENE(HS_SCENE_StartGameScene);
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
						HS_GO_SCENE(HS_SCENE_StartGameScene);
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
        			HS_GO_SCENE(HS_SCENE_StartGameScene);
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
            
        case 2008: //用户已经下线
        {
            HSSocketPool::ShareSocketPool()->SetPingShortLink(false);
            HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
            
            HS_GO_SCENE(HS_SCENE_GameMainScene);
        }
            break;
            
        default:
            break;
    }
}

