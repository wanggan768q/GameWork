#include "HSGameCoverScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSGameCache.h"
#include "HSLog.h"
#include "HSFadeIn.h"
#include "HSGamePairScene.h"
#include <algorithm> 
#include "HSGameGuide.h"
#include "HSInputDialogLayer.h"
#include "HSDailyRewardSystemLayer.h"
#include "HSJava.h"

float HSGameCoverLayer::s_LoginListerTime = 0.f;
//Layer
HSGameCoverLayer::HSGameCoverLayer(void)
{
	this->townBackground = NULL;
	m_changing = false;
	m_CurIndex =0;
	m_curMoney =0;
	m_pGameFrisbee = NULL;
	m_CurrentSelectMenuID = SelectMenuID_UnKnow;
	m_backSate = BackSate_Invain;
	m_isRunGameGuide_1016 = true;
}

HSGameCoverLayer::~HSGameCoverLayer(void)
{
	m_pBack1 = NULL;
	m_pBack2 = NULL;
	m_pPanle = NULL;
}

bool HSGameCoverLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	HSTool::SetLayerScale(this);
	this->Load();
	//this->setTouchEnabled(true);
	//this->setKeypadEnabled(true);
	
	return true;
}

void HSGameCoverLayer::Load()
{
	//HSReadUI::ShareReadUI()->ReadUI("Image/main/normalBack/normalback.data","Image/main/normalBack/",this);
	HSReadUI::ShareReadUI()->ReadUI("Image/main/main.data","Image/main/",this);

	m_pPanle = HS_FIND_UI_PANEL("UI_HEbinggaojiduchangxin");
	HS_SET_MENU_TARGET("UI_HEbinggaojiduchangxin_Youshanglahuan_01",this,HSGameCoverLayer::CallChange);
	HS_SET_MENU_TARGET("UI_HEbinggaojiduchangxin_Kaishiyouxi_01",this,HSGameCoverLayer::CallStartPair);
	HS_SET_MENU_TARGET("UI_HEbinggaojiduchangxin_Xinxi_01",this,HSGameCoverLayer::CallPlayerInfo);

	HS_SET_MENU_TARGET("UI_HEbinggaojiduchangxin_Shangcheng_01",this,HSGameCoverLayer::CallShop);

	HS_SET_MENU_TARGET("UI_HEbinggaojiduchangxin_Xitongtuibiao_01",this,HSGameCoverLayer::CallSeting);
	HS_SET_MENU_TARGET("UI_HEbinggaojiduchangxin_Chengjiu_01",this,HSGameCoverLayer::Call_AchievementSystem);
	HS_SET_MENU_TARGET("UI_HEbinggaojiduchangxin_Goumaijinbianniu_01",this,HSGameCoverLayer::CallShop);

	HSCCSprite* gameGoldFrame = HS_FIND_UI_PANEL_SPRITE("UI_HEbinggaojiduchangxin_Jinbidiandikuang","Jinbidiandikuang");
	CCSize gameGoldFrameSize = gameGoldFrame->getContentSize();

	CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/moneyNumber.png");
	m_pGameGold = CCLabelAtlas::create("0","Image/moneyNumber.png",pMoneyTexture->getPixelsWide() / 11,pMoneyTexture->getPixelsHigh(),'0');
	m_pGameGold->setAnchorPoint(HS_ANCHOR_L_CENTER);
	//m_pGameGold->setPosition(ccp(gameGoldFrameSize.width-pMoneyTexture->getPixelsWide() / 10,gameGoldFrameSize.height/2));
	m_pGameGold->setPosition(ccp(0,gameGoldFrame->getAnchorPointInPoints().y));
	//m_pGameGold->setScaleX(0.5f);
	gameGoldFrame->addChild(m_pGameGold);
	
	m_pGameFrisbee = HSGameFrisbee::create();
	this->addChild(m_pGameFrisbee);


	CCSprite* pGold = HS_FIND_UI_PANEL_SPRITE("UI_qiehuananniu","qiehuananniu");
	pGold->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleBy::create(0.8f, 0.85f),
		CCScaleTo::create(0.1f, 1))));

	if (!HS_IsRunGameGuide() && HS_ONLINE)
	{
		CCDelayTime* pDelayTime = CCDelayTime::create(0.f);
		CCCallFunc* pLoginCall = CCCallFunc::create(this,callfunc_selector(HSGameCoverLayer::Call_First_Login));
		this->runAction(CCSequence::create(pDelayTime,pLoginCall,NULL));		
	}else{
		this->runAction(CCSequence::create(CCCallFunc::create(this,callfunc_selector(HSGameCoverLayer::Call_GameGuide)),NULL));
	}
	this->runAction(CCSequence::create(CCCallFunc::create(this,callfunc_selector( HSGameCoverLayer::Call_Lister)),NULL));
	this->schedule(schedule_selector(HSGameCoverLayer::Update));


}

void HSGameCoverLayer::CallChange(CCObject* obj)
{
	if(!m_changing)
	{
		m_changing = true;

		CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

		HSGameCoverScene* mainScene =dynamic_cast<HSGameCoverScene*>(scene);

		if(m_CurIndex == 0)//向上
		{
			CCSequence* up1 = GetMoveUpSequence();
			CCSequence* up2 = GetMoveUpSequence();

			if(mainScene)
			{
				mainScene->GetHSCoverBackNormalLayer()->runAction(up1);
				mainScene->GetHSCoverBackSeniorLayer()->runAction(up2);
				mainScene->GetHSCoverBackSeniorLayer()->setVisible(true);
			}

			m_CurIndex =1;

		}
		else//向下
		{
			CCSequence* down1 = GetMoveDownSequnce();
			CCSequence* down2 = GetMoveDownSequnce();

			if(mainScene)
			{
				mainScene->GetHSCoverBackNormalLayer()->runAction(down1);
				mainScene->GetHSCoverBackSeniorLayer()->runAction(down2);
			}
			m_CurIndex =0;
		}
		CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSGameCoverLayer::ChangeFinish));
		HSFadeIn* changeFade = HSFadeIn::create(0.5f);
		m_pPanle->runAction(CCSequence::create(changeFade,pCallFunc,NULL));
		//m_pPanle->setVisible(false);

		/**
		CCFadeIn* startFade = CCFadeIn::create(0.5f);
		m_pStart->runAction(startFade);*/
	}
}

CCSequence* HSGameCoverLayer::GetMoveUpSequence()
{
	CCActionInterval*  actionDownStart = CCMoveBy::create(0.1f, ccp(0.f,-32.f));
	CCActionInterval*  actionUP = CCMoveBy::create(0.3f, ccp(0.f,HSBase::GetTemplateScreenH()+2*HSToolBase::GetOffsetY()+64.f+32.f));
	CCActionInterval*  actionDownEnd = CCMoveBy::create(0.1f, ccp(0.f,-32.f));
	CCSequence* sequence =CCSequence::create(actionDownStart, actionUP,actionDownEnd,NULL);
	return sequence;
}

CCSequence* HSGameCoverLayer::GetMoveDownSequnce()
{
	CCActionInterval*  actionDownStart = CCMoveBy::create(0.1f, ccp(0.f,32.f));
	CCActionInterval*  actionUP = CCMoveBy::create(0.3f, ccp(0.f,-HSBase::GetTemplateScreenH()-2*HSToolBase::GetOffsetY()-64.f-32.f));
	CCActionInterval*  actionDownEnd = CCMoveBy::create(0.1f, ccp(0.f,32.f));
	CCSequence* sequence =CCSequence::create(actionDownStart, actionUP,actionDownEnd,NULL);
	return sequence;
}

void HSGameCoverLayer::ChangeFinish()
{
	m_changing = false;
	
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

	HSGameCoverScene* coverScene =dynamic_cast<HSGameCoverScene*>(scene);

	if(coverScene != NULL)
	{
		if(m_CurIndex == 0)
		{
			coverScene->GetHSCoverBackSeniorLayer()->StopDown();
			coverScene->GetHSCoverBackNormalLayer()->m_p_normal->BeginDown();
		}
		else if(m_CurIndex = 1 )
		{
			coverScene->GetHSCoverBackSeniorLayer()->BeginDown();
			coverScene->GetHSCoverBackNormalLayer()->m_p_normal->StopDown();
		}
	}
}

void HSGameCoverLayer::CallStartPair(CCObject* obj)
{
	//HSGamePairScene::s_areaType = area_normal;
	if(m_CurIndex ==0)
	{
		HSGamePairScene::s_areaType = area_normal;
	}
	else
	{
		HSGamePairScene::s_areaType = area_advanced;
	}
	HSGamePairScene::s_status = status_pair;

	m_CurrentSelectMenuID = SelectMenuID_Start;

	if (!HS_IsRunGameGuide())
	{
		this->RequestFighting();
		HSLoadingLayer::ShareLoading()->setVisible(true);
	}else{
		CCMenuItem* pItem = dynamic_cast<CCMenuItem*>(obj);
		pItem->setEnabled(false);
		HS_GO_SCENE(HS_SCENE_GamePairScene);
	}
}

void HSGameCoverLayer::CallPlayerInfo(CCObject* obj)
{
	if (!HS_GAME_CACHE()->IsLogin())
	{
		return;
	}
// 	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
// 	HSGameCoverScene* coverScene = (HSGameCoverScene*)scene;
// 	if(coverScene->GetHSGamePlayerInfoLayer()==NULL)
// 	{
// 		coverScene->SetHSGamePlayerInfoLayer(HSGamePlayerInfoLayer::create());
// 	}
// 	else
// 	{
// 		coverScene->GetHSGamePlayerInfoLayer()->setVisible(true);
// 	}
	HSGamePlayerInfoLayer::SharedPlayerInfoLayer()->setVisible(true);
}

void HSGameCoverLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
}

bool HSGameCoverLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSGameCoverLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameCoverLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HSGameCoverLayer::keyBackClicked()
{
	switch (m_backSate)
	{
	case HSGameCoverLayer::BackSate_Invain:
		{
			m_backSate = BackSate_Await;
			this->runAction(CCSequence::create(CCDelayTime::create(5.f),CCCallFunc::create(this,callfunc_selector(HSGameCoverLayer::ChangeBackSata)),NULL));
			HSJava::ShaderJava()->ShowToast(L("exit"),5);
		}
		break;
	case HSGameCoverLayer::BackSate_Await:
		{
			m_backSate = BackSate_Take;
			HSJava::ShaderJava()->KillProcess();
		}
		break;
	case HSGameCoverLayer::BackSate_Take:
		{
			m_backSate = BackSate_Invain;
		}
		break;
	default:
		break;
	}
}
void HSGameCoverLayer::keyMenuClicked()
{
	
}

void HSGameCoverLayer::ChangeBackSata()
{
	m_backSate = BackSate_Invain;
}



void HSGameCoverLayer::Update(float dt)
{
	if (m_curMoney !=HS_GAME_CACHE()->GetGold())
	{
		m_curMoney =HS_GAME_CACHE()->GetGold();
		m_pGameGold->setString(CCString::createWithFormat("%d",m_curMoney)->getCString());
	}
}

void HSGameCoverLayer::RequestFighting()
{
	if(HS_ONLINE)
	{
		if (!HS_GAME_CACHE()->IsRegister())
		{
			HSRequest::ShareRequest()->SendRegisterRequest();
		}else if(!HS_GAME_CACHE()->IsLogin()){
			HSRequest::ShareRequest()->SendLoginRequest();
		}else{
			HSRequest::ShareRequest()->SendFightingRequest();
		}
	}
	else
	{
		HS_GO_SCENE(HS_SCENE_GamePairScene);
	}
}

void HSGameCoverLayer::ResponseFighting(FightingResponse*r)
{
	FightingResponse_RequestStatus status = r->status();
	if(status ==FightingResponse_RequestStatus_SUCCESS)
	{
		NetAddress address= r->address();
		std::string ip = address.ip();
		int port = address.port();
		HSSocketPool::ShareSocketPool()->AddSocket(S_L_Battle,ip.c_str(),CCString::createWithFormat("%d",port)->getCString(),HSSocket_Type_SOCKET);

		//while (!HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle)->IsConnectSucceed());

		switch (HSGamePairScene::s_areaType)
		{
		case area_normal:
			HSRequest::ShareRequest()->SendTargetInfoRequest(0);
			HSGamePairLayer::s_CURRENT_ROOM_ID = 0;
			break;
		case area_advanced:
			HSRequest::ShareRequest()->SendRoomDataRequest();
			break;
		default:
			break;
		}
	}
	else if(status ==FightingResponse_RequestStatus_FAIL)
	{
		HSMessageBox("Response::Fighting Fail");
	}

	HSSocketPool::ShareSocketPool()->SetPingShortLink(true);
}


void HSGameCoverLayer::ResponseTargetInfo(TargetInfoResponse* responseMsg)
{
	HS_GAME_CACHE()->m_pTargetInfoResponse->CopyFrom(*responseMsg);

	//HS_MUTABLE_TARGET_SELF()->CopyFrom(*(responseMsg->mutable_self()));
	HS_GAME_CACHE()->CopyUser(responseMsg->self());

	if(HS_GAME_CACHE()->m_pTargetInfoResponse->status()== TargetInfoResponse_FindStatus_SUCCESS)
	{
		HSSocketPool::ShareSocketPool()->SetPingShortLink(false);
		HSSocketPool::ShareSocketPool()->SetPingLongLink(true);
		HSLoadingLayer::ShareLoading()->setVisible(false);
		
		CCLOG("did=%s",HS_GAME_CACHE()->m_pTargetInfoResponse->dungoenid().c_str());
		HS_GO_SCENE(HS_SCENE_GamePairScene);
	}else{
		HSMessageBox("Response::TargetInfo fail");
	}
}

void HSGameCoverLayer::CallShop( CCObject* pobj )
{
	if (!HS_GAME_CACHE()->IsLogin())
	{
		return;
	}
	m_CurrentSelectMenuID = SelectMenuID_Shop;
	if (HS_GAME_CACHE()->IsLogin())
	{
		HSGameShopLayer::SharedShopLayer()->setVisible(true);
	}
}

void HSGameCoverLayer::CallSeting( CCObject* obj )
{
	if (m_pGameFrisbee->GetSate())
	{
		m_pGameFrisbee->Show();
	}
	else
	{
		m_pGameFrisbee->Hide();
	}
}

void HSGameCoverLayer::CallFriend(CCObject* obj)
{
	m_CurrentSelectMenuID = SelectMenuID_Friend;
	if(HS_ONLINE)
	{
		if (!HS_GAME_CACHE()->IsRegister())
		{
			HSRequest::ShareRequest()->SendRegisterRequest();
		}else if(HS_GAME_CACHE()->IsLogin()){
			HSRequest::ShareRequest()->SendFriendInfoRequest();
		}
	}
	
}

void HSGameCoverLayer::ResponseLogin( LoginResponse* r )
{
	if(r->status() == LoginResponse_LoginStatus_LoginStatus_SUCCESS)
	{
		//HS_GAME_CACHE()->m_NetAddress = r->address();
		NetAddress address = r->address();
		std::string ip = address.ip();
		int port = address.port();
		HSSocketPool::ShareSocketPool()->AddSocket(S_D_Logic,ip.c_str(),CCString::createWithFormat("%d",port)->getCString(),HSSocket_Type_HTTP);
		//sendFightingRequest
		//HSRequest::ShareRequest()->SendFightingRequest();

		HSRequest::ShareRequest()->SendSearchUserInfoRequest();
		HSRequest::ShareRequest()->SendAchievementRequest();

		//HS_GO_SCENE(HS_SCENE_CoverScene);


		if (r->has_dailyrewarddata())
		{
			HS_GAME_CACHE()->m_DailyRewardSystemData.Clear();
			HS_GAME_CACHE()->m_DailyRewardSystemData.CopyFrom(r->dailyrewarddata());
			HSDailyRewardSystemLayer::ShaderDailyRewardSystemLayer()->setVisible(true);
		}
		HS_GAME_CACHE()->SetIsLogin(true);
		if (m_CurrentSelectMenuID == SelectMenuID_Start)
		{
			HSRequest::ShareRequest()->SendFightingRequest();
		}else if(m_CurrentSelectMenuID == SelectMenuID_Friend){
			HSRequest::ShareRequest()->SendFriendInfoRequest();
		}

		if (!HS_GAME_CACHE_DATA()->issendnickname())
		{
			HSRequest::ShareRequest()->SendUserInfoUpdateRequest_Name(HS_GAME_CACHE_DATA()->nickname().c_str());
		}		
	}
	else if(r->status() == LoginResponse_LoginStatus_LoginStatus_FAIL)
	{
		HSMessageBox("Response::Login Fail");
	}
}

void HSGameCoverLayer::ResponseRegister( RegisterResponse* r )
{
	if(r->status()==RegisterResponse_RegisterStatus_RegisterStatus_SUCCESS)//如果注册成功了要继续发起登录请求
	{
		HS_MUTABLE_TARGET_SELF()->set_name(HS_GAME_CACHE()->m_pTempName);
		HS_GAME_CACHE()->Save();
		HSRequest::ShareRequest()->SendLoginRequest();
	}
	else if(r->status()==RegisterResponse_RegisterStatus_RegisterStatus_FAIL)
	{
		HSMessageBox("Response::Register Fail");
	}
}

void HSGameCoverLayer::ResponseFriendInfo( FriendInfoResponse* r )
{
	HS_GAME_CACHE()->m_FriendInfoResponse.Clear();
	HS_GAME_CACHE()->m_FriendInfoResponse.CopyFrom(*r);
	HS_GO_SCENE(HS_SCENE_FriendsSystemScene);
}

void HSGameCoverLayer::Call_First_Login()
{
	if (!HS_ONLINE)
	{
		HS_GO_SCENE(HS_SCENE_GamePairScene);
		return;
	}
	if (HSMath::EqualsWithFloat(0.f,s_LoginListerTime))
	{
		s_LoginListerTime = 50000.f;
	}
	this->Call_Loop_Login();
	CCDelayTime* pDelayTime = CCDelayTime::create(s_LoginListerTime);
	CCCallFunc* pLoginCall = CCCallFunc::create(this,callfunc_selector(HSGameCoverLayer::Call_Loop_Login));
	this->runAction(CCRepeatForever::create(CCSequence::create(pDelayTime,pLoginCall,NULL)));
}

void HSGameCoverLayer::Call_Loop_Login()
{
	if (HS_GAME_CACHE()->IsLogin())
	{
		return;
	}
	if (HS_GAME_CACHE()->IsRegister())
	{
		HSRequest::ShareRequest()->SendLoginRequest();
		HSLoadingLayer::ShareLoading()->setVisible(true);
	}else{
		HSRequest::ShareRequest()->SendRegisterRequest();
	}		
}

void HSGameCoverLayer::Call_Lister()
{
	if (HSGamePairScene::s_areaType == area_advanced)
	{
		m_changing = false;
		this->CallChange(NULL);
	}
}

void HSGameCoverLayer::Call_AchievementSystem( CCObject* pObj )
{
	if (HS_GAME_CACHE()->m_AchievementResponse.achievementlist_size() > 0)
	{
		HS_GO_SCENE(HS_SCENE_AchievemenScene);
	}
	
	//HSRequest::ShareRequest()->SendAchievementRequest();
	//HSLoadingLayer::ShareLoading()->setVisible(true);
}

void HSGameCoverLayer::ResponseAchievement( AchievementResponse* r )
{
	HS_GAME_CACHE()->m_AchievementResponse.Clear();
	HS_GAME_CACHE()->m_AchievementResponse.CopyFrom(*r);
	HSLoadingLayer::ShareLoading()->setVisible(false);
	//HSLoadingLayer::ShareLoading()->setVisible(false);
// 	if (HS_GAME_CACHE()->m_AchievementResponse.achievementlist_size() > 0)
// 	{
// 		HS_GO_SCENE(HS_SCENE_AchievemenScene);
// 	}

}

void HSGameCoverLayer::Call_GameGuide()
{
	if (HS_IsRunGameGuide())
	{
		int currentStepID = HSGameGuide::ShaderGameGuide()->GetCurrentStepID();
		if (m_isRunGameGuide_1016 && currentStepID == 1016)
		{
			m_isRunGameGuide_1016 = false;
			if (HS_GAME_CACHE_DATA()->nickname() == "")
			{
				HSInputDialogLayer* pInputDialogLayer = HSInputDialogLayer::create();
				this->getParent()->addChild(pInputDialogLayer,0x987567);
			}else{
				if (HS_IsRunGameGuide())
				{
					HS_MUTABLE_GAME_CACHE_DATA()->set_isrungameguide(false);
				}
				HS_GAME_CACHE()->Save();
				HSGameGuide::ShaderGameGuide()->Destroy();
			}
		}else{
			HSGameGuide::ShaderGameGuide()->Resume(this->getParent());
		}
	}
}




















float HSCoverNormalLayer::m_maxcatblack1 = 5.5f;
float HSCoverNormalLayer::m_maxcatblack2 = 7.f;

float HSCoverNormalLayer::m_downMinCount = 2.5f;
float HSCoverNormalLayer::m_downMaxCount = 4.f;

float HSCoverNormalLayer::m_cat1MinX = -70.f;  //120.f;
float HSCoverNormalLayer::m_cat1MaxX = 120.f;//260.f;

float HSCoverNormalLayer::m_cat2MinX = -100.f;//380.f;
float HSCoverNormalLayer::m_cat2MaxX = 100.f;//520.f;
//HSCoverBackNormalLayer
HSCoverNormalLayer::HSCoverNormalLayer(void)
{
	normal_backGround = NULL;
	m_p_main_cloud1 = NULL;
	m_p_main_cloud1s = NULL;


	m_p_main_cloud2 = NULL;
	m_p_main_cloud2s = NULL;



	m_p_main_cloud3 = NULL;
	m_p_main_cloud3s = NULL;


	m_p_main_cloud4 = NULL;
	m_p_main_cloud4s = NULL;


	m_p_main_cloud5 = NULL;
	m_p_main_cloud5s = NULL;

	m_p_main_catblack1 = NULL;
 
	m_p_main_catblack2 = NULL;

	m_catblack1count =0;
	m_catblack2count =0;
	 
	m_down = false;
}

HSCoverNormalLayer::~HSCoverNormalLayer(void)
{
	normal_backGround = NULL;
	m_p_main_cloud1 = NULL;
	m_p_main_cloud1s = NULL;

	m_p_main_cloud2 = NULL;
	m_p_main_cloud2s = NULL;

	m_p_main_cloud3 = NULL;
	m_p_main_cloud3s = NULL;

	m_p_main_cloud4 = NULL;
	m_p_main_cloud4s = NULL;

	m_p_main_cloud5 = NULL;
	m_p_main_cloud5s = NULL;

	m_p_main_catblack1 = NULL;
	m_p_main_catblack2 = NULL;
}

bool HSCoverNormalLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	HSTool::SetLayerScale(this);
	this->Load();
	return true;
}

void HSCoverNormalLayer::Load()
{
	HSReadUI::ShareReadUI()->ReadUI("Image/main/normalBack/normalback.data","Image/main/normalBack/",this);


	CCNode* pcloud1Frame = HS_FIND_UI_PANEL("UI_main_cloud1");
	m_p_main_cloud1 = HS_FIND_UI_PANEL_SPRITE("UI_main_cloud1","main_cloud1");
	pcloud1Frame->setPositionY(pcloud1Frame->getPositionY()-HSToolBase::GetOffsetY());
	m_cloud1Position = m_p_main_cloud1->getPosition();

	m_p_main_cloud1s = CCSprite::createWithTexture(m_p_main_cloud1->getTexture());
	m_p_main_cloud1s->setPosition(ccp(m_cloud1Position.x+HSBase::GetTemplateScreenW(),m_cloud1Position.y));
	pcloud1Frame->addChild(m_p_main_cloud1s);

	m_p_main_cloud1->setTag(10);
	m_p_main_cloud1s->setTag(11);

	CallCloudFinish(m_p_main_cloud1);
	CallCloudFinish(m_p_main_cloud1s);

	CCNode* pcloud2Frame = HS_FIND_UI_PANEL("UI_main_cloud2");
	m_p_main_cloud2 = HS_FIND_UI_PANEL_SPRITE("UI_main_cloud2","main_cloud2");
	pcloud2Frame->setPositionY(pcloud2Frame->getPositionY()-HSToolBase::GetOffsetY());
	m_cloud2Postion = m_p_main_cloud2->getPosition();

	m_p_main_cloud2s = CCSprite::createWithTexture(m_p_main_cloud2->getTexture());
	m_p_main_cloud2s->setPosition(ccp(m_cloud2Postion.x+HSBase::GetTemplateScreenW(),m_cloud2Postion.y));
	pcloud2Frame->addChild(m_p_main_cloud2s);

	m_p_main_cloud2->setTag(20);
	m_p_main_cloud2s->setTag(21);

	CallCloudFinish(m_p_main_cloud2);
	CallCloudFinish(m_p_main_cloud2s);


	CCNode* pcloud3Frame = HS_FIND_UI_PANEL("UI_main_cloud3");
	m_p_main_cloud3 = HS_FIND_UI_PANEL_SPRITE("UI_main_cloud3","main_cloud3");
	pcloud3Frame->setPositionY(pcloud3Frame->getPositionY()-HSToolBase::GetOffsetY());
	m_cloud3Postion = m_p_main_cloud3->getPosition();

	m_p_main_cloud3s = CCSprite::createWithTexture(m_p_main_cloud3->getTexture());
	m_p_main_cloud3s->setPosition(ccp(m_cloud3Postion.x+HSBase::GetTemplateScreenW(),m_cloud3Postion.y));
	pcloud3Frame->addChild(m_p_main_cloud3s);

	m_p_main_cloud3->setTag(30);
	m_p_main_cloud3s->setTag(31);
	CallCloudFinish(m_p_main_cloud3);
	CallCloudFinish(m_p_main_cloud3s);


	CCNode* pcloud4Frame = HS_FIND_UI_PANEL("UI_main_cloud4");
	m_p_main_cloud4 = HS_FIND_UI_PANEL_SPRITE("UI_main_cloud4","main_cloud4");
	pcloud4Frame->setPositionY(pcloud4Frame->getPositionY()-HSToolBase::GetOffsetY());
	m_cloud4Postion = m_p_main_cloud4->getPosition();

	m_p_main_cloud4s = CCSprite::createWithTexture(m_p_main_cloud4->getTexture());
	m_p_main_cloud4s->setPosition(ccp(m_cloud4Postion.x+HSBase::GetTemplateScreenW(),m_cloud4Postion.y));
	pcloud4Frame->addChild(m_p_main_cloud4s);

	m_p_main_cloud4->setTag(40);
	m_p_main_cloud4s->setTag(41);
	CallCloudFinish(m_p_main_cloud4);
	CallCloudFinish(m_p_main_cloud4s);


	CCNode* pcloud5Frame = HS_FIND_UI_PANEL("UI_main_cloud5");
	m_p_main_cloud5 = HS_FIND_UI_PANEL_SPRITE("UI_main_cloud5","main_cloud5");
	pcloud5Frame->setPositionY(pcloud5Frame->getPositionY()-HSToolBase::GetOffsetY());
	m_cloud5Postion = m_p_main_cloud5->getPosition();

	m_p_main_cloud5s = CCSprite::createWithTexture(m_p_main_cloud5->getTexture());
	m_p_main_cloud5s->setPosition(ccp(m_cloud5Postion.x+HSBase::GetTemplateScreenW(),m_cloud5Postion.y));
	pcloud5Frame->addChild(m_p_main_cloud5s);

	m_p_main_cloud5->setTag(50);
	m_p_main_cloud5s->setTag(51);
	CallCloudFinish(m_p_main_cloud5);
	CallCloudFinish(m_p_main_cloud5s);

	m_p_main_catblack1 = HS_FIND_UI_PANEL_SPRITE("UI_main_catblack1","main_catblack1");
	m_p_main_catblack1->getParent()->setPosition(ccpAdd(m_p_main_catblack1->getParent()->getPosition(),ccp(0.f,HSToolBase::GetOffsetY())));
	m_main_catblack1Position = m_p_main_catblack1->getPosition();
	m_p_main_catblack2 = HS_FIND_UI_PANEL_SPRITE("UI_main_catblack2","main_catblack2");
	m_p_main_catblack2->getParent()->setPosition(ccpAdd(m_p_main_catblack2->getParent()->getPosition(),ccp(0.f,HSToolBase::GetOffsetY())));
	m_main_catblack2Position = m_p_main_catblack2->getPosition();


	this->BeginDown();
	this->schedule(schedule_selector(HSCoverNormalLayer::Update));
}

void HSCoverNormalLayer::CallCloudFinish(CCNode* node)
{
	CCSprite* pSprite = NULL;
	float time = 0;
	if(node->getTag()==10)
	{
		pSprite= m_p_main_cloud1;
		pSprite->setPositionX(m_cloud1Position.x);
		time=8.f;
	}
	else if(node->getTag()==11)
	{
		pSprite= m_p_main_cloud1s;
		pSprite->setPositionX(m_cloud1Position.x+HSBase::GetTemplateScreenW());
		time=8.f;
	}
	if(node->getTag()==20)
	{
		pSprite = m_p_main_cloud2;
		pSprite->setPositionX(m_cloud2Postion.x);
		time = 10.f;
	}
	else if(node->getTag()==21)
	{
		pSprite = m_p_main_cloud2s;
		pSprite->setPositionX(m_cloud2Postion.x+HSBase::GetTemplateScreenW());
		time = 10.f;
	}
	else if(node->getTag()==30)
	{
		pSprite = m_p_main_cloud3;
		pSprite->setPositionX(m_cloud3Postion.x);
		time = 12.f;
	}
	else if(node->getTag()== 31)
	{
		pSprite = m_p_main_cloud3s;
		pSprite->setPositionX(m_cloud3Postion.x+HSBase::GetTemplateScreenW());
		time = 12.f;
	}
	else if(node->getTag() == 40)
	{
		pSprite = m_p_main_cloud4;
		pSprite->setPositionX(m_cloud4Postion.x);
		time = 15.f;
	}
	else if(node->getTag() == 41)
	{
		pSprite = m_p_main_cloud4s;
		pSprite->setPositionX(m_cloud4Postion.x+HSBase::GetTemplateScreenW());
		time= 15.f;
	}
	else if(node->getTag() == 50)
	{
		pSprite = m_p_main_cloud5;
		pSprite->setPositionX(m_cloud5Postion.x);
		time = 20.f;
	}
	else if(node->getTag()== 51)
	{
		pSprite = m_p_main_cloud5s;
		pSprite->setPositionX(m_cloud5Postion.x+HSBase::GetTemplateScreenW());
		time = 20.f;
	}

	CCActionInterval* action = CCMoveBy::create(time,ccp(-HSBase::GetTemplateScreenW(),0.f));
	CCCallFuncN* pCall = CCCallFuncN::create(this,callfuncN_selector(HSCoverNormalLayer::CallCloudFinish));
	pSprite->runAction(CCSequence::create(action,pCall,NULL));
}

void HSCoverNormalLayer::Update(float dt)
{

	if(m_down)
	{
		m_catblack1count+= dt;
		m_catblack2count+=dt;

		if(m_catblack1count>m_maxcatblack1)
		{
			m_catblack1count = 0;
			float x = HSMath::Random(m_cat1MinX,m_cat1MaxX);
			m_p_main_catblack1->setPosition(ccp(x,m_main_catblack1Position.y));

			float downCount = HSMath::Random(m_downMinCount,m_downMaxCount);

			CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(HSCoverNormalLayer::CallCatDownShake));
			CCMoveBy* move = CCMoveBy::create(downCount,ccp(0.f,-HSBase::GetTemplateScreenH()*1.7f));
			CCSequence* action = CCSequence::create(move,func,NULL);
			m_p_main_catblack1->runAction(action);
			m_p_main_catblack1->setRotation(HSMath::Random(0.f,270.f));
			m_p_main_catblack1->runAction(CCRepeatForever::create(CCRotateBy::create(0.1f,20.f)));
		}

		if(m_catblack2count>m_maxcatblack2)
		{
			m_catblack2count = 0;
			float x = HSMath::Random(m_cat2MinX,m_cat2MaxX);
			m_p_main_catblack2->setPosition(ccp(x,m_main_catblack2Position.y));
			//m_p_main_catblack2->setPosition(m_main_catblack2Position);
			float downCount = HSMath::Random(m_downMinCount,m_downMaxCount);
			CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(HSCoverNormalLayer::CallCatDownShake));
			CCMoveBy* move = CCMoveBy::create(downCount,ccp(0.f,-HSBase::GetTemplateScreenH()*1.7f));
			CCSequence* action = CCSequence::create(move,func,NULL);
			m_p_main_catblack2->runAction(action);
			m_p_main_catblack2->setRotation(HSMath::Random(0.f,270.f));
			m_p_main_catblack2->runAction(CCRepeatForever::create(CCRotateBy::create(0.1f,20.f)));
		}
	}
}

void HSCoverNormalLayer::CallCatDownShake()
{
	//CCPoint postion = m_p_main_backGround->getPosition();
	if(m_down)
	{
		CCActionInterval* move1 = CCMoveBy::create(0.05f,ccp(0.f,-2.f));
		CCActionInterval* move2 = CCMoveBy::create(0.1f,ccp(0.f,-2.f));
		CCActionInterval* move3 = CCMoveBy::create(0.1f,ccp(0.f,6.f));
		CCActionInterval* move4 = CCMoveBy::create(0.2f,ccp(0.f,-2.f));

		CCSequence* actionMove = CCSequence::create(move1,move2,move3,move4,NULL);

		CCScaleBy* scale1 = CCScaleBy::create(0.15f,1.f);
		CCScaleBy* scale2 = CCScaleBy::create(0.2f,1.02f);
		CCScaleBy* scale3 = CCScaleBy::create(0.1f,0.98f);

		CCSequence* actionScale = CCSequence::create(scale1,scale2,scale3,NULL);

		CCSpawn* spawn = CCSpawn::create(actionMove,actionScale,NULL);


		CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

		HSGameCoverScene* mainScene =dynamic_cast<HSGameCoverScene*>(scene);

		if(mainScene)
		{
			mainScene->GetHSCoverBackNormalLayer()->m_p_normal_backGround->runAction(spawn);
		}
	}
}

void HSCoverNormalLayer::BeginDown()
{
	m_down = true;
	m_catblack1count = 0;
	m_catblack2count =0;
}

void HSCoverNormalLayer::StopDown()
{
	m_down = false;
}

//HSCoverBacknormalLayer

HSCoverBacknormalLayer::HSCoverBacknormalLayer(void)
{
	m_p_normal_backGround = NULL;
	m_p_normal = NULL;
}

HSCoverBacknormalLayer::~HSCoverBacknormalLayer(void)
{
	m_p_normal_backGround = NULL;
	m_p_normal = NULL;
}

bool HSCoverBacknormalLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//HSTool::SetLayerScale(this);
	this->Load();
	return true;
}

void HSCoverBacknormalLayer::Load()
{
	m_p_normal_backGround = CCSprite::create("Image/main/normalBack/main_backGround.png");

	m_p_normal_backGround->setPosition(HSBase::GetScreenCentre());

	HSToolBase::SetNodeFilldScreen(m_p_normal_backGround);

	this->addChild(m_p_normal_backGround);

	m_p_normal = HSCoverNormalLayer::create();
	this->addChild(m_p_normal);

	
 }


float HSCoverBackSeniorLayer::m_maxcatblack1 = 5.5f;
float HSCoverBackSeniorLayer::m_maxcatblack2 = 7.f;

float HSCoverBackSeniorLayer::m_downMinCount = 2.5f;
float HSCoverBackSeniorLayer::m_downMaxCount = 4.f;

float HSCoverBackSeniorLayer::m_cat1MinX = 120.f;  //120.f;
float HSCoverBackSeniorLayer::m_cat1MaxX = 260.f;//260.f;

float HSCoverBackSeniorLayer::m_cat2MinX = 380.f;//380.f;
float HSCoverBackSeniorLayer::m_cat2MaxX = 520.f;//520.f;
//HSCoverBackSeniorLayer
HSCoverBackSeniorLayer::HSCoverBackSeniorLayer(void)
{
	m_p_senior_backGround = NULL;
	m_p_senior_foreground = NULL;
	m_p_senior_catblack1 = NULL;
	m_p_senior_catblack2 = NULL;

	m_senior_catblack1count = 0;
	m_senior_catblack2count = 0;

	m_down = false;
}

HSCoverBackSeniorLayer::~HSCoverBackSeniorLayer(void)
{
	m_p_senior_backGround = NULL;
	m_p_senior_foreground = NULL;

	m_p_senior_catblack1 = NULL;
	m_p_senior_catblack2 = NULL;
}

bool HSCoverBackSeniorLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//HSTool::SetLayerScale(this);
	this->Load();
	return true;
}

void HSCoverBackSeniorLayer::Load()
{
	m_p_senior_foreground = CCSprite::create("Image/main/seniorBack/seniorforeground.png");

	m_p_senior_backGround = CCSprite::create("Image/main/seniorBack/seniorbackground.png");

	m_p_senior_catblack1 = CCSprite::create("Image/main/seniorBack/main_catblack1.png");

	m_p_senior_catblack2 = CCSprite::create("Image/main/seniorBack/main_catblack2.png");

	m_p_senior_catblack1->setPosition(ccp(0.f,HSBase::GetTemplateScreenH()+HSToolBase::GetOffsetY()));

	m_p_senior_catblack2->setPosition(ccp(0.f,HSBase::GetTemplateScreenH()+HSToolBase::GetOffsetY()));

	m_p_senior_foreground->setPosition(HSBase::GetScreenCentre());

	m_p_senior_backGround->setPosition(HSBase::GetScreenCentre());

	HSToolBase::SetNodeFilldScreen(m_p_senior_foreground);

	HSToolBase::SetNodeFilldScreen(m_p_senior_backGround);

	this->addChild(m_p_senior_backGround);

	this->addChild(m_p_senior_catblack1);

	this->addChild(m_p_senior_catblack2);

	this->addChild(m_p_senior_foreground);

	this->schedule(schedule_selector(HSCoverBackSeniorLayer::Update));
}

void HSCoverBackSeniorLayer::visit()
{
// 	glEnable(GL_SCISSOR_TEST); // 开启显示指定区域
// 	// 在这里只写上固定值，在特性环境下，以便快速看效果，实际的值，需要根据实际情况算得
// 	glScissor(0, 100.f, HSBase::GetTemplateScreenW(), HSBase::GetTemplateScreenH()); // 只显示当前窗口的区域
//  
// 	CCLayer::visit(); // 调用下面的方法
// 	glDisable(GL_SCISSOR_TEST); // 禁用

	CCLayer::visit(); // 调用下面的方法
}

void HSCoverBackSeniorLayer::Update(float dt)
{
	if(m_down)
	{
		m_senior_catblack1count+= dt;
		m_senior_catblack2count+=dt;

		if(m_senior_catblack1count>m_maxcatblack1)
		{
			m_senior_catblack1count = 0;
			float x = HSMath::Random(m_cat1MinX,m_cat1MaxX);
			m_p_senior_catblack1->setPosition(ccp(x,HSBase::GetTemplateScreenH()+HSToolBase::GetOffsetY()));

			float downCount = HSMath::Random(m_downMinCount,m_downMaxCount);

			CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(HSCoverBackSeniorLayer::CallCatDownShake));
			CCMoveBy* move = CCMoveBy::create(downCount,ccp(0.f,-HSBase::GetTemplateScreenH()*1.7f));
			CCSequence* action = CCSequence::create(move,func,NULL);
			m_p_senior_catblack1->runAction(action);
			m_p_senior_catblack1->setRotation(HSMath::Random(0.f,270.f));
			m_p_senior_catblack1->runAction(CCRepeatForever::create(CCRotateBy::create(0.1f,20.f)));
			m_p_senior_catblack1->setVisible(true);
		}

		if(m_senior_catblack2count>m_maxcatblack2)
		{
			m_senior_catblack2count = 0;
			float x = HSMath::Random(m_cat2MinX,m_cat2MaxX);
			m_p_senior_catblack2->setPosition(ccp(x,HSBase::GetTemplateScreenH()+HSToolBase::GetOffsetY()));
			//m_p_main_catblack2->setPosition(m_main_catblack2Position);
			float downCount = HSMath::Random(m_downMinCount,m_downMaxCount);
			CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(HSCoverBackSeniorLayer::CallCatDownShake));
			CCMoveBy* move = CCMoveBy::create(downCount,ccp(0.f,-HSBase::GetTemplateScreenH()*1.7f));
			CCSequence* action = CCSequence::create(move,func,NULL);
			m_p_senior_catblack2->runAction(action);
			m_p_senior_catblack2->setRotation(HSMath::Random(0.f,270.f));
			m_p_senior_catblack2->runAction(CCRepeatForever::create(CCRotateBy::create(0.1f,20.f)));
			m_p_senior_catblack2->setVisible(true);
		}
	}
	
}

void HSCoverBackSeniorLayer::BeginDown()
{
	m_down = true;
	m_senior_catblack1count = 0;
	m_senior_catblack2count =0;
	m_p_senior_catblack1->setVisible(false);
	m_p_senior_catblack2->setVisible(false);
	this->setVisible(true);
}

void HSCoverBackSeniorLayer::StopDown()
{
	m_down = false;
	m_p_senior_catblack1->setVisible(false);
	m_p_senior_catblack2->setVisible(false);
	this->setVisible(false);
}

void HSCoverBackSeniorLayer::CallCatDownShake()
{
	if(m_down)
	{
		CCActionInterval* move1 = CCMoveBy::create(0.05f,ccp(0.f,-2.f));
		CCActionInterval* move2 = CCMoveBy::create(0.1f,ccp(0.f,-2.f));
		CCActionInterval* move3 = CCMoveBy::create(0.1f,ccp(0.f,6.f));
		CCActionInterval* move4 = CCMoveBy::create(0.2f,ccp(0.f,-2.f));

		CCSequence* actionMove = CCSequence::create(move1,move2,move3,move4,NULL);

		CCScaleBy* scale1 = CCScaleBy::create(0.15f,1.f);
		CCScaleBy* scale2 = CCScaleBy::create(0.2f,1.02f);
		CCScaleBy* scale3 = CCScaleBy::create(0.1f,0.98f);

		CCSequence* actionScale = CCSequence::create(scale1,scale2,scale3,NULL);

		CCSpawn* spawn = CCSpawn::create(actionMove,actionScale,NULL);


		CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

		HSGameCoverScene* mainScene =dynamic_cast<HSGameCoverScene*>(scene);

		if(mainScene)
		{
			mainScene->GetHSCoverBackSeniorLayer()->m_p_senior_backGround->runAction(spawn);
		}
	}
	
}


//Scene
HSGameCoverScene::HSGameCoverScene(void)
{
	this->hsGameCoverLayer = NULL;
	/*this->hsGamePlayerInfoLayer = NULL;*/
	/*this->hsGameShopLayer = NULL;*/
	
}

HSGameCoverScene::~HSGameCoverScene(void)
{
	this->hsGameCoverLayer = NULL;
	/*this->hsGamePlayerInfoLayer = NULL;*/
	/*this->hsGameShopLayer = NULL;*/
}

bool HSGameCoverScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	normalLayer = HSCoverBacknormalLayer::create();
	this->addChild(normalLayer);
	normalLayer->m_p_normal->BeginDown();


	seniorLayer = HSCoverBackSeniorLayer::create();
	seniorLayer->StopDown();
	seniorLayer->setPosition(ccpAdd(seniorLayer->getPosition(),ccp(0.f,-HSBase::GetTemplateScreenH()-2*HSToolBase::GetOffsetY()-32.f)));
	seniorLayer->setVisible(false);
	this->addChild(seniorLayer);



	this->hsGameCoverLayer = HSGameCoverLayer::create();
	this->addChild(this->hsGameCoverLayer,HS_BASE_TAG,HS_BASE_TAG);

	

	return true;
}