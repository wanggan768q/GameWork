#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "HSGameSceneJumpManage.h"
#include "HSTool.h"
#include "HSLog.h"
#include "HSJson.h"
#include "HSJava.h"
using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
	HS_LOG()->SendUserLog(LogRequest_ActionType_Logout);

	SimpleAudioEngine::end();
	HSTool::ShareHSTool()->Release();
	HSTool::ShareHSTool()->Destroy();

	
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	// turn on display FPS
	pDirector->setDisplayStats(true);
	pDirector->setProjection(kCCDirectorProjection2D);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);
	//pDirector->sharedDirector()->getOpenGLView()->set


//     // create a scene. it's an autorelease object
//     CCScene *pScene = HelloWorld::scene();
//     // run
//     pDirector->runWithScene(pScene);

	//////////////////////////////////////////////////////////////////////////
	//CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	//CCSize designSize = CCSizeMake(480, 320);
	//if (screenSize.height > 320)
	//{
	//	CCSize resourceSize = CCSizeMake(960, 640);
	//	CCFileUtils::sharedFileUtils()->setResourceDirectory("HD");
	//	pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
	//}
	//CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
	//CCEGLView::sharedOpenGLView()->setDesignResolutionSize(screenSize.width, screenSize.height, kResolutionNoBorder);
	//////////////////////////////////////////////////////////////////////////
	CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone");
	HSTool::ShareHSTool();
	this->AddSocket();

	HSJson* pJson = HSJson::CreateWithWriter();
	Json::Value data;
	data["LandScape"] = false;
	HSJava::ShaderJava()->Init(pJson->Writer(data).c_str());

	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(AppDelegate::Updata), this, 0.f, false);

    //HS_Play_Music("back_01");//effect_03 back_01
    //HSSoundManage::ShareSoundManage()->SetMusicVolume(100);
    
	HS_GO_SCENE(HS_SCENE_GameMainScene);
	//HS_GO_SCENE(HS_SCENE_SeniortSystemScene);
	//HS_GO_SCENE(HS_SCENE_FriendsSystemScene);
	//HS_GO_SCENE(HS_SCENE_AchievemenScene);
	//HS_GO_SCENE(HS_SCENE_GameMainScene);
	//HS_GO_SCENE(HS_SCENE_BattleScene);
	
	return true;
}


void AppDelegate::AddSocket()
{
	HSTool::ShareHSTool();

	if (!HS_ONLINE)
	{
		return;
	}

	std::string ip = HSTool::ShareHSTool()->FindConfiguration("ServerIp");
	std::string port = HSTool::ShareHSTool()->FindConfiguration("ServerPort");
	std::string ServerType = HSTool::ShareHSTool()->FindConfiguration("ServerType");

	HSSocketType type ;
	if (ServerType == "HS_SOCKET_TYPE_ONCE")
	{
		type = HSSocket_Type_HTTP;
	}
	else if(ServerType == "HS_SOCKET_TYPE_KEEP")
	{
		type = HSSocket_Type_SOCKET;
	}
	else
	{
		HSMessageBox("Configuration file server type error");
		return;
	}
	HSSocketPool::ShareSocketPool()->AddSocket(S_D_Login,ip.c_str(),port.c_str(),type);
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->stopAnimation();

	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->startAnimation();

	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::Updata( float dt )
{
	HSSocketPool::ShareSocketPool()->Updata(dt);
}
