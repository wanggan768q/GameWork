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
		}
		break;
	case API_RegisterResponse:
		{
			RegisterResponse* r = (RegisterResponse*)responseMsg;
			HSGameCoverLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGameCoverScene,HSGameCoverLayer);
			layer->ResponseRegister(r);
		}
		break;
	case API_LoginResponse:
		{
			LoginResponse* r = (LoginResponse*)responseMsg;
			HSGameCoverLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGameCoverScene,HSGameCoverLayer);
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
			if (pHSGameCoverScene)
			{
				HSSeniortSystemLayer* layer = HS_GET_RUN_SCENE_LAYER(HSSeniortSystemScene,HSSeniortSystemLayer);
				layer->ResponseFighting(r);
				break;
			}
		}
		break;
	case API_TargetInfoResponse:
		{
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
		}
		break;
	case API_PlayerDisengageResponse:
		{
			PlayerDisengageResponse* r = (PlayerDisengageResponse*)responseMsg;
			CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
			HSGamePairScene* pHSGamePairScene = dynamic_cast<HSGamePairScene*>(pScene);
			if (pHSGamePairScene)
			{
				HSGamePairLayer* layer = HS_GET_RUN_SCENE_LAYER(HSGamePairScene,HSGamePairLayer);
				layer->ResponsePlayerDisengage(r);
			}else{
				HS_MUTABLE_TARGET_TARGET()->Clear();
			}
		}
		break;
	case API_KickOutDungoen:
		{
			//临时写到这里，等以后写好dialog以后就不用了
			HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle)->Closed();
			HS_GO_SCENE(HS_SCENE_CoverScene);
			HSSocketPool::ShareSocketPool()->SetPingLongLink(false);
			HSSocketPool::ShareSocketPool()->SetPingShortLink(true);
			//HSMessageBox("Fighting Server timeout return GameMainScene");
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
	case API_FriendInfoResponse:
		{
#if WIN32
			throw std::exception("API_FriendInfoResponse");
#endif
		}
		break;
	case API_AddFriendResponse:
		{
			#if WIN32
			throw std::exception("API_AddFriendResponse");
			#endif
		}
		break;
	case API_DeleteFriendResponse:
		{
			#if WIN32
			throw std::exception("API_DeleteFriendResponse");
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
			HS_GAME_CACHE()->AddGold(r->addgoldnumber());
		}
		break;

	case API_UserInfoUpdateResponse:
		{
			switch (HS_GAME_CACHE()->m_UserInfoUpdateRequest_UpdateType)
			{
			case UserInfoUpdateRequest_UpdateType_User_Name:
				{
					HS_MUTABLE_GAME_CACHE_DATA()->set_issendnickname(true);
				}
				break;
			case UserInfoUpdateRequest_UpdateType_User_IconId:
				{
					//HS_MUTABLE_GAME_CACHE_DATA()->userinfo().set_iconid()
					HSRequest::ShareRequest()->SendSearchUserInfoRequest();
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
			HS_GAME_CACHE()->AddGold(r->addgoldnumber());
		}
		break;
	default:
		HSMessageBox(responseMsg->GetTypeName() + "   Don't deal with ");
		break;
	}

}
