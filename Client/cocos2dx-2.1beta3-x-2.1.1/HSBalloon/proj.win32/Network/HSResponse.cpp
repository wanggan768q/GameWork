#include "HSResponse.h"
#include "HSBattleScene.h"
#include "HSRankingListScene.h"
#include "HSLog.h"

//static HSResponse* s_hsResponse = NULL;

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
	case API_LogResponse:
		{
			LogResponse* r = (LogResponse*)responseMsg;
			HS_LOG()->ResponseLog(r);
		}
		break;
	case API_RegisterResponse:
		{
			RegisterResponse* r = (RegisterResponse*)responseMsg;
			HSBattleOverLayer* layer = HS_GET_RUN_SCENE_LAYER(HSBattleScene,HSBattleOverLayer);
			HSInputDialogLayer* inputLayer = layer->GetInputLayer();
			inputLayer->ResponseRegister(r);
		}
		break;
	case API_CombatGainsResponse:
		{
			CombatGainsResponse* r = (CombatGainsResponse*)responseMsg;
			if (r->status() == CombatGainsResponse_CombatGainsStatus_CombatGainsStatus_FAIL)
			{
				HS_GAME_CACHE()->AddHistoryScore(HS_GAME_CONFIG_DATA()->gameScore);
			}else{
				for (int i=0;i<HS_GAME_CACHE_DATA()->historyscorelist_size();++i)
				{
					HS_GAME_CACHE()->ClearHistoryScoreList();
				}
			}
		}
		break;
	case  API_SearchRankResponse:
		{
			SearchRankResponse* r = (SearchRankResponse*)responseMsg;
			HSBattleOverLayer* layer = HS_GET_RUN_SCENE_LAYER(HSBattleScene,HSBattleOverLayer);
			layer->ResponseSearchRank(r);
		}
		break;
	default:
		HSMessageBox(responseMsg->GetTypeName() + "   Don't deal with ");
		break;
	}
}
