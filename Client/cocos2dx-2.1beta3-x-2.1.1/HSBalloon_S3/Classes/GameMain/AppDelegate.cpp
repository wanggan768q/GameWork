#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "HSGameSceneJumpManage.h"
#include "HSTool.h"
#include "HSJson.h"
#include "HSJava.h"
#include "HSReadPlist.h"
using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
    m_isLoadPngFinish = false;
}

AppDelegate::~AppDelegate()
{    
    SimpleAudioEngine::end();
    HSTool::ShareHSTool()->Release();
    HSTool::ShareHSTool()->Destroy();
    
    std::map<std::string, CCImage*>::iterator   it = m_ImageMap.begin();
    while (it != m_ImageMap.end())
    {
        CCImage* pImage = it->second;
        CC_SAFE_DELETE(pImage);
        ++it;
    }
    
    
}

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

    std::string umengchannel = HSMath::ItoA(HSJava::ShaderJava()->GetChannel());

    CCLog("umengchannel %s",umengchannel.c_str());

    MobClickCpp::setLogEnabled(true);

    MobClickCpp::startWithAppkey("52400f9f56240b084609cf50", /*umengchannel.c_str()*/"200000");



    this->AddSocket();
    /**
     HSJson* pJson = HSJson::CreateWithWriter();
     Json::Value data;
     data["LandScape"] = Json::Value(false);
     data["JNI_ID"] = Json::Value(1000);
     
     HSJava::ShaderJava()->JavaExec(pJson->Writer(data).c_str());*/
    //HSJava::ShaderJava()->JavaExec("12344");
    //HSJava::ShaderJava()->KillProcess();
    //CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(AppDelegate::Updata), this, 0.f, false);
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(AppDelegate::Lister_LoadPngFinish), this, 0.f, false);
    

		HS_GO_SCENE(HS_SCENE_LOGOSCENE);
	//}

    this->Start();
    //	Run();
    //	Lister_LoadPngFinish(0.f);
    
    //HS_Play_Music("back_01");//effect_03 back_01
    //HSSoundManage::ShareSoundManage()->SetMusicVolume(100);

    //HS_GO_SCENE(HS_SCENE_GameMainScene);
    //HS_GO_SCENE(HS_SCENE_SeniortSystemScene);
    //HS_GO_SCENE(HS_SCENE_FriendsSystemScene);
    //HS_GO_SCENE(HS_SCENE_AchievemenScene);
    //HS_GO_SCENE(HS_SCENE_GameMainScene);
    //HS_GO_SCENE(HS_SCENE_BattleScene);
    //scheduleOnce(schedule_selector(AppDelegate::Activate),0.1f);
    //CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(AppDelegate::Activate),this,0.1,false);
    //__android_log_print(ANDROID_LOG_INFO, "cocos2d-x debug info",  "12345=========");
    //CCLog("1111");
    
    return true;
}

//void AppDelegate::Activate(float dt)
//{
//
//	MobClickCpp::event("HSActivate");
//
//	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(AppDelegate::Activate),this);
//}

void AppDelegate::AddSocket()
{
    HSTool::ShareHSTool()->AddDefaultSocket();
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCLOG("applicationDidEnterBackground");

    CCDirector::sharedDirector()->stopAnimation();
    
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

    MobClickCpp::applicationDidEnterBackground();
}

void AppDelegate::applicationWillEnterForeground()
{

	CCLOG("applicationWillEnterForeground");

    CCDirector::sharedDirector()->startAnimation();
    
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

    MobClickCpp::applicationWillEnterForeground();

}
#define HS_RES_MAX_COUNT 17
void AppDelegate::Run()
{
    m_isLoadPngFinish = true;
    return;
    CCLog("====================================");
    CCLog(HSTime::GetTime());
    for (int i=0; i<HS_RES_MAX_COUNT; ++i)
    {
        CCString* sPng = CCString::createWithFormat("Image/Image%d.png",i);
        std::string pngName = sPng->getCString();
        
        std::string fullpath = sPng->getCString();
        //CCLog("加载: %s ",fullpath.c_str());
        fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fullpath.c_str());
        
        CCImage* pImage = new CCImage;
        pImage->initWithImageFile(fullpath.c_str());
        m_ImageMap.insert(pair<std::string, CCImage*>(pngName,pImage));
        
        //sPng->release();
    }
    CCLog(HSTime::GetTime());
    CCLog("====================================");
    m_isLoadPngFinish = true;
}

void AppDelegate::Updata( float dt )
{
    HSSocketPool::ShareSocketPool()->Updata(dt);
}

void AppDelegate::Lister_LoadPngFinish(float dt)
{
    if (m_isLoadPngFinish)
    {
        m_isLoadPngFinish = false;
        CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
        
//        for (int i=0; i<HS_RES_MAX_COUNT; ++i)
//        {
//            CCString* sPlist = CCString::createWithFormat("Image/Image%d.plist",i);
//            CCString* sPng = CCString::createWithFormat("Image/Image%d.png",i);
//            std::string pngFileName = sPng->getCString();
//            
//            std::map<string, CCImage*>::iterator it = m_ImageMap.find(pngFileName);
//            if (it == m_ImageMap.end())
//            {
//                HSMessageBox(sPlist->getCString());
//            }
//            CCImage* pImage = it->second;
//            
//            HSReadPlist::ShareReadPlist()->Open(sPlist->getCString(), pImage);
//            
//            sPlist->release();
//            CC_SAFE_DELETE(pImage);
//        }
        m_ImageMap.clear();
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(AppDelegate::Updata), this, 0.1f, false);
        //      CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(AppDelegate::Updata), this, 3.f, false);
        HS_GO_SCENE(HS_SCENE_GameMainScene);
    }
}










