#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "HSGameSceneJumpManage.h"
#include "HSTool.h"
#include "HSLog.h"

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
#include "HSJni.h"
bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	// turn on display FPS
	//pDirector->setDisplayStats(true);
	pDirector->setProjection(kCCDirectorProjection2D);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);
	//pDirector->sharedDirector()->getOpenGLView()->set


//     // create a scene. it's an autorelease object
//     CCScene *pScene = HelloWorld::scene();
//     // run
//     pDirector->runWithScene(pScene);

	//////////////////////////////////////////////////////////////////////////
	CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	CCSize designSize = CCSizeMake(480, 320);
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

	this->AddSocket();

	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(AppDelegate::Updata), this, 0.f, false);

	HSSoundManage::ShareSoundManage()->Load("music/BackgroundMusic.txt","music/Effect.txt");

	HSLanguage::ShaderLanguage()->Read("Data/LanguageData.data","Chinese");// Chinese English
	

	HSJni jni;


	HS_GO_SCENE(HS_SCENE_GameMainScene);
	
	return true;
}


void AppDelegate::AddSocket()
{
	HSTool::ShareHSTool();
	std::map<std::string,std::string> out;
	
	HSBase::GetDictionary_Key_V__WithFile("configuration.data",&out);

	std::string ip = HSTool::ShareHSTool()->FindConfiguration("ServerIp");
	std::string port = HSTool::ShareHSTool()->FindConfiguration("ServerPort");
	std::string ServerType = HSTool::ShareHSTool()->FindConfiguration("ServerType");

	int type = 0;
	if (ServerType == "HS_SOCKET_TYPE_ONCE")
	{
		type = HS_SOCKET_TYPE_ONCE;
	}else if(ServerType == "HS_SOCKET_TYPE_KEEP"){
		type = HS_SOCKET_TYPE_KEEP;
	}else{
		HSMessageBox("Configuration file server type error");
		return;
	}
	HSSocketPool::ShareSocketPool()->AddSocket(DEFAULT_SOCKET,ip.c_str(),port.c_str(),type);


	
	//HSSocketPool::ShareSocketPool()->AddSocket(DEFAULT_SOCKET,"118.244.193.136",5050,HS_SOCKET_TYPE_ONCE);

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
	HSSocketPool::ShareSocketPool()->Updata();
}
