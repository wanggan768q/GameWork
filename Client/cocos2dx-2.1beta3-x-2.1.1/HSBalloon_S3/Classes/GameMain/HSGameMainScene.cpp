#include "HSGameMainScene.h"
#include "HSGameSceneJumpManage.h"
#include "HSDailyRewardSystemLayer.h"
#include "HSJava.h"
#include "MobClickCpp.h"
#include "HSGlobal.h"
#include "HSLanActionManager.h"



HSGameMainLayer::HSGameMainLayer(void)
{
    m_isSearchRoomFinsh = false;
}

HSGameMainLayer::~HSGameMainLayer(void)
{
}

bool HSGameMainLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
    
	HSTool::SetLayerScale(this);
	this->Load();
    //this->setKeypadEnabled(true);
    
	return true;
}

void HSGameMainLayer::Load()
{
	HS_GAME_CACHE();
    
	HSCCSprite* m_pb= HSCCSprite::create("Image/Fengmianbeijing.png");
	m_pb->setPosition(HSBase::GetTemplateScreenCentre());
	HSToolBase::SetNodeFilldScreen(m_pb);
	this->addChild(m_pb);
    
	HSReadUI::ShareReadUI()->ReadUI("Image/GameMainScene.data","Image/",this);
    
    int loginType = HSJava::ShaderJava()->CheckUser();
    if (loginType != 99 && loginType != 0)
    {
        CCMenu* pFastLogin = HS_FIND_UI_MENU("UI_Kuaisudenglu");
        pFastLogin->setVisible(false);
    }else{
        HS_SET_MENU_TARGET("UI_Kuaisudenglu", this, HSGameMainLayer::Call_LoginType);
    }
    
    HS_SET_MENU_TARGET("UI_Weibodenglu", this, HSGameMainLayer::Call_Login);
    HS_SET_MENU_TARGET("UI_Wifidenglu", this, HSGameMainLayer::Call_LAN);
    
	
    
//	CCSprite* versionName = HS_FIND_UI_PANEL_SPRITE("UI_Banbenhao","Mingziditu");
//    
//	CCString* verStr = HSJava::ShaderJava()->GetVersionName();
//	CCLabelTTF* version = CCLabelTTF::create(verStr->getCString(),HS_FONT_HuaKang,25.f,versionName->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
//	version->setPosition(ccp(versionName->getContentSize().width/2,versionName->getContentSize().height/2));
//	versionName->addChild(version);
//	verStr->release();
    
	HS_Play_Music("back_01");
    
	this->schedule(schedule_selector(HSGameMainLayer::Update));
    
	MobClickCpp::event("HSActivate");
    
    // #174
    HS_GAME_CACHE()->m_pBattleResult->Clear();
    
    //Lan
    this->schedule(schedule_selector(HSGameMainLayer::ListerSearchRoomFinish));
    this->scheduleOnce(schedule_selector(HSGameMainLayer::ListerOnce), 0);
    
    HSLanActionManager::ShareLanActionManager()->Destroy();
    
    //流星
    {
        CCSprite* p1 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_0","Fengmianliuxing_0");
        CCSprite* p2 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_2","Fengmianliuxing_0");
        CCSprite* p3 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_6","Fengmianliuxing_0");
        CCSprite* p4 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_12","Fengmianliuxing_0");
        CCSprite* p5 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_8","Fengmianliuxing_0");
        CCSprite* p6 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_10","Fengmianliuxing_0");
        CCSprite* p7 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_4","Fengmianliuxing_0");
        
        CCSprite* p8 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_1","Fengmianliuxing_1");
        CCSprite* p9 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_3","Fengmianliuxing_1");
        CCSprite* p10 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_5","Fengmianliuxing_1");
        CCSprite* p11 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_7","Fengmianliuxing_1");
        CCSprite* p12 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_9","Fengmianliuxing_1");
        CCSprite* p13 = HS_FIND_UI_PANEL_SPRITE("UI_Liuxingyu_Liuxing_11","Fengmianliuxing_1");
        
        p1->setOpacity(0);
        p2->setOpacity(0);
        p3->setOpacity(0);
        p4->setOpacity(0);
        p5->setOpacity(0);
        p6->setOpacity(0);
        p7->setOpacity(0);
        p8->setOpacity(0);
        p9->setOpacity(0);
        p10->setOpacity(0);
        p11->setOpacity(0);
        p12->setOpacity(0);
        p13->setOpacity(0);
        
        vector<CCNode*> v,v1;
        v.push_back(p1);
        v.push_back(p2);
        v.push_back(p3);
        v.push_back(p4);
        v.push_back(p5);
        v.push_back(p6);
        v.push_back(p7);
        v1.push_back(p8);
        v1.push_back(p9);
        v1.push_back(p10);
        v1.push_back(p11);
        v1.push_back(p12);
        v1.push_back(p13);
        
        
        for_each(v.begin(), v.end(), [](CCNode* p)
                 {
                     CCMoveTo* a5 = CCMoveTo::create(0.0001f, p->getPosition());
                     
                     CCFadeIn* a1 = CCFadeIn::create(0.1f);
                     CCMoveBy* a2 = CCMoveBy::create(HSMath::Random(0.5f, 1.f), ccp(-193,-249));
                     
                     CCSpawn* a3 = CCSpawn::create(a1,a2,NULL);
                     CCFadeOut* a4 = CCFadeOut::create(0.1);
                     
                     CCDelayTime* a6 = CCDelayTime::create(HSMath::Random(2, 5));
                     CCDelayTime* a7 = CCDelayTime::create(HSMath::Random(2, 5));
                     CCSequence* pSeq = CCSequence::create(a7,a3,a4,a5,a6,NULL);
                     CCRepeatForever* forever = CCRepeatForever::create(pSeq);
                     
                     p->runAction(forever);
                 });
        
        for_each(v1.begin(), v1.end(), [](CCNode* p)
                 {
                     
                     CCMoveTo* a5 = CCMoveTo::create(0.0001f, p->getPosition());
                     
                     CCFadeIn* a1 = CCFadeIn::create(0.1f);
                     CCMoveBy* a2 = CCMoveBy::create(HSMath::Random(0.5f, 1.f), ccp(-181,-233));
                     CCSpawn* a3 = CCSpawn::create(a1,a2,NULL);
                     CCFadeOut* a4 = CCFadeOut::create(0.1);
                     
                     CCDelayTime* a6 = CCDelayTime::create(HSMath::Random(2, 5));
                     CCDelayTime* a7 = CCDelayTime::create(HSMath::Random(2, 5));
                     CCSequence* pSeq = CCSequence::create(a7,a3,a4,a5,a6,NULL);
                     CCRepeatForever* forever = CCRepeatForever::create(pSeq);
                     
                     p->runAction(forever);
                 });
        
    }
}

void HSGameMainLayer::ListerOnce(float dt)
{
    if (HSGameSceneJumpManage::SharedGameSceneJumpManage()->GetPreviousGameSceneID() == HS_SCENE_LanRoomListScene)
    {
        HSJava::ShaderJava()->StopSearchingShareCircle();
        //HS_ShowLoading();
        //HSLoadingLayer::ShareLoading()->SetTime(5);
    }
}

void HSGameMainLayer::Call_LAN(CCObject* pobj)
{
    HS_GO_SCENE(HS_SCENE_GameGuideSystemScene);
    //HS_GO_SCENE(HS_SCENE_StartGameScene);
    //    /* 调用LAN SDK */
    //    HS_GAME_CACHE()->ReadLan();
    //    HS_GAME_CACHE()->SetLoginType("LAN");
    //
    //    HSJava::ShaderJava()->GetPhoneModel()->release();
    //    //HSSocketPool::ShareSocketPool()->Destroy();
}

void HSGameMainLayer::Call_LoginType(CCObject* pObj)
{
    HS_GAME_CACHE()->SetIsLogin(true);
    
	HS_GAME_CACHE()->SetLoginType("99");
    
    this->Call_Login(NULL);
}

void HSGameMainLayer::Call_Login(CCObject* pObj)
{
    eventDict dict;
    
    if(pObj == NULL)
    {
        dict["logintype"] = "99";
    }
    else
    {
        dict["logintype"] = HS_Find_Configure("ChannelID").c_str();
        HS_GAME_CACHE()->SetLoginType(HS_Find_Configure("ChannelID").c_str());
    }
    
    if(HS_GAME_CACHE_DATA()->uid() == "0")
    {
        dict["regist"] ="regist";
    }
    
    MobClickCpp::event("HSClickLogin",&dict);
    
    //#if !HSAndroid
    //    HS_MUTABLE_GAME_CACHE_DATA()->set_uid("1427EBB36383FEF5819D128EF613FE0D");
    //    HS_MUTABLE_GAME_CACHE_DATA()->set_weibo_id("C1FB68517E3556F80DBB5CB3AF8CDFC7");
    //#endif
    HS_ShowLoading();
    
    HSLoadingLayer::ShareLoading()->SetTipsUp(L("Loading_Login"));
    
    if (HS_GAME_CACHE_DATA()->uid() == "0")
    {
        HSRequest::ShareRequest()->SendRegisterRequest();
    }
    else
    {
    	eventDict dict;
        
    	if(pObj == NULL)
		{
			dict["logintype"] = "99";
		}
		else
		{
			dict["logintype"] = HS_Find_Configure("ChannelID").c_str();
		}
        
    	MobClickCpp::beginEventWithAttributes("HSThirdPartTime","hs",&dict);
        
        this->MicroblogLogin();
    }
}

void HSGameMainLayer::Update(float dt)
{
	
}

void HSGameMainLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
}

bool HSGameMainLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HSGameMainLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void HSGameMainLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    //HS_GO_SCENE(HS_SCENE_CoverScene);
}

void HSGameMainLayer::keyBackClicked()
{
    
}

void HSGameMainLayer::keyMenuClicked()
{
    
}

void HSGameMainLayer::MicroblogLogin()
{
    //#if HSAndroid
	HSLoadingLayer::ShareLoading()->SetTime(5);
    std::string ChannelID = HS_Find_Configure("ChannelID");
    HSJson* pJson = HSJson::CreateWithWriter();
    Json::Value data;
    data["JNI_ID"] = Json::Value(2000);
    data["WEIBO_TYPE"] = HS_GAME_CACHE()->GetLoginType();
    data["WEIBO_GAME_APPID"] = Json::Value(HS_Find_Configure("APPID"));
    data["WEIBO_GAME_UID"] = Json::Value(HS_GAME_CACHE_DATA()->uid());
    std::string jsonData = pJson->Writer(data);
    
    HSJava::ShaderJava()->JavaExec(jsonData.c_str());
    pJson->release();
    //#else
    //    HSRequest::ShareRequest()->SendLoginRequest(HS_GAME_CACHE_DATA()->weibo_id().c_str());
    //#endif
    
}

void HSGameMainLayer::ResponseRegister( RegisterResponse* r )
{
    
	eventDict dict;
    
    
	if(0 == strcmp("99", HS_GAME_CACHE()->GetLoginType()))
	{
		dict["logintype"] = "99";
	}
	else
	{
		dict["logintype"] = HS_Find_Configure("ChannelID").c_str();
	}
    
	CCLog("ResponseRegister");
    
	if(r->status() == RegisterResponse_RegisterStatus_RegisterStatus_SUCCESS)
	{
		dict["status"] = "success";
		MobClickCpp::event("HSRegist",&dict);
		HS_MUTABLE_TARGET_SELF()->set_name(HS_GAME_CACHE()->m_pTempName);
		HS_GAME_CACHE()->Save();
        HS_GAME_CACHE()->m_isRegistSuccess = true;
        
        
        eventDict dictt;
        
        if (0 == strcmp("99", HS_GAME_CACHE()->GetLoginType()))
		{
        	dictt["logintype"] = "99";
		}
		else
		{
			dictt["logintype"] = HS_Find_Configure("ChannelID").c_str();
		}
        
        MobClickCpp::beginEventWithAttributes("HSThirdPartRegistTime","hs",&dictt);
        
        
        this->MicroblogLogin();
        
	}
	else if(r->status()==RegisterResponse_RegisterStatus_RegisterStatus_FAIL)
	{
		dict["status"] = "fail";
		MobClickCpp::event("HSRegist",&dict);
        
		if(r->has_version())
		{
			int newVersion = r->version();
            
			HSJava::ShaderJava()->NotifyVersionCode(newVersion);
		}
        
		HSJava::ShaderJava()->ShowToast("Response::Register Fail",0);
        
	}
    
    
}

void HSGameMainLayer::ResponseLogin( LoginResponse* r )
{
	eventDict dict;
	if (0 == strcmp("99", HS_GAME_CACHE()->GetLoginType()))
	{
		dict["logintype"] = "99";
	}
	else
	{
		dict["logintype"] = HS_Find_Configure("ChannelID").c_str();
	}
    
	if(r->status() == LoginResponse_LoginStatus_LoginStatus_SUCCESS)
	{
		dict["status"] = "success";
	}
	else if(r->status() == LoginResponse_LoginStatus_LoginStatus_FAIL)
	{
		dict["status"] = "fail";
	}
    
	if(HS_GAME_CACHE()->m_isRegistSuccess)//说明刚刚成功注册
	{
		MobClickCpp::event("HSLoginRegist",&dict);
	}
	else
	{
		MobClickCpp::event("HSLogin",&dict);
	}
    
    
    
    
    
	if(r->status() == LoginResponse_LoginStatus_LoginStatus_SUCCESS)
	{
		NetAddress address = r->address();
		std::string ip = address.ip();
		int port = address.port();
        
        
		HS_GAME_CACHE()->m_gameName = r->gamename();
        
		HS_GAME_CACHE()->m_gameDownload = r->gamedownload();
        
		CCLog("gameName(%s)gameDownload(%s)",HS_GAME_CACHE()->m_gameName.c_str(),HS_GAME_CACHE()->m_gameDownload.c_str());
        
		if(r->has_olduid())
		{
            CCLog("oldUid --------->%s",r->olduid().c_str());
            HS_MUTABLE_GAME_CACHE_DATA()->set_uid(r->olduid());
            HS_GAME_CACHE()->Save();
		}
        
		HSSocketPool::ShareSocketPool()->AddSocket( S_D_Logic,ip.c_str(), CCString::createWithFormat("%d",port)->getCString(), HSSocket_Type_HTTP);
        
        HSRequest::ShareRequest()->SendGameSearchStrengthRequest();
        
		HSRequest::ShareRequest()->SendSearchUserInfoRequest();
        
		HSRequest::ShareRequest()->SendAchievementRequest();
        
        HSRequest::ShareRequest()->SendFriendListRequest();
        
        HSRequest::ShareRequest()->SendEmailRequest();
        
		if (r->has_dailyrewarddata())
		{
			HS_GAME_CACHE()->m_DailyRewardSystemData.Clear();
			HS_GAME_CACHE()->m_DailyRewardSystemData.CopyFrom(r->dailyrewarddata());
		}
		HS_GAME_CACHE()->SetIsLogin(true);
        
        HS_HideLoading();
        
        //HS_GO_SCENE(HS_SCENE_CoverScene);
        //HS_GO_SCENE(HS_SCENE_StartGameScene);
        
        HSSocketPool::ShareSocketPool()->SetPingShortLink(true);
        
	}
	else if(r->status() == LoginResponse_LoginStatus_LoginStatus_FAIL)
	{
		if(r->has_version())
		{
			int newVersion = r->version();
            
			HSJava::ShaderJava()->NotifyVersionCode(newVersion);
		}
		HSJava::ShaderJava()->ShowToast("登陆失败",0);
        HS_GO_SCENE(HS_SCENE_GameMainScene);
		//HSMessageBox("Response::Login Fail");
	}
}

void HSGameMainLayer::ResponseSearchStrength(GameSearchStrengthResponse* pMsg)
{
    HS_GO_SCENE(HS_SCENE_StartGameScene);
}

//void HSGameMainLayer::ResponseLanSearchRoom(LanSearchRoomResponse* pMsg)
//{
//    HS_HideLoading();
//
//    HS_GAME_CACHE()->m_LanRoomList.Clear();
//    HS_GAME_CACHE()->m_LanRoomList.CopyFrom(*pMsg);
//
//    m_isSearchRoomFinsh = true;
//}

void HSGameMainLayer::ListerSearchRoomFinish(float dt)
{
    if (m_isSearchRoomFinsh)
    {
        m_isSearchRoomFinsh = false;
        
        HS_GO_SCENE(HS_SCENE_LanRoomListScene);
    }
}















//#include "HSGameGuide.h"

HSGameMainScene::HSGameMainScene(void)
{
	this->hsGameMainLayer = NULL;
}

HSGameMainScene::~HSGameMainScene(void)
{
}

bool HSGameMainScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
    
	this->hsGameMainLayer = HSGameMainLayer::create();
	this->addChild(this->hsGameMainLayer,HS_BASE_TAG,HS_BASE_TAG);
    
    //this->addChild(HSGameGuide::create(),10000);
    
	return true;
}

