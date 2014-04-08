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
#include "HSReadPlist.h"
using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
    m_isLoadPngFinish = false;
}

AppDelegate::~AppDelegate()
{
    HS_LOG()->SendUserLog(LogRequest_ActionType_Logout);
    
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
    
    //CCDirector::sharedDirector()

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

    MobClickCpp::startWithAppkey("52400f9f56240b084609cf50", umengchannel.c_str());

    this->AddSocket();

    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(AppDelegate::Lister_LoadPngFinish), this, 0.f, false);
    
//    if(HSJava::ShaderJava()->GetChannel() == 10004)//联通
//    {
    HS_GO_SCENE(HS_SCENE_LOGOSCENE);
//    }

    this->Start();

    return true;
}



void AppDelegate::AddSocket()
{
    HSTool::ShareHSTool();
    
    if (!HS_ONLINE)
    {
        return;
    }
    
    std::string ip = HS_Find_Configure("ServerIp");
    std::string port = HS_Find_Configure("ServerPort");
    std::string ServerType = HS_Find_Configure("ServerType");
    
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
    
    CCLog("Add Socket -----------------------------------------------------------");
    HSSocketPool::ShareSocketPool()->AddSocket(S_D_Login,ip.c_str(),port.c_str(),type);
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

    MobClickCpp::applicationDidEnterBackground();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

    MobClickCpp::applicationWillEnterForeground();


    //CCDirector::sharedDirector()->end();
    //Director::getInstance()->end();
}

void AppDelegate::Run()
{
    CCLog("====================================");
    CCLog(HSTime::GetTime());
    for (int i=0; i<16; ++i)
    {
        CCString* sPng = CCString::createWithFormat("Image/Image%d.png",i);
        std::string pngName = sPng->getCString();
        
        std::string fullpath = sPng->getCString();
        CCLog("加载: %s ",fullpath.c_str());
        fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fullpath.c_str());
        
        CCImage* pImage = new CCImage;
        pImage->initWithImageFile(fullpath.c_str());
        m_ImageMap.insert(pair<std::string, CCImage*>(pngName,pImage));
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
        
        for (int i=0; i<16; ++i)
        {
            CCString* sPlist = CCString::createWithFormat("Image/Image%d.plist",i);
            CCString* sPng = CCString::createWithFormat("Image/Image%d.png",i);
            std::string pngFileName = sPng->getCString();
            
            std::map<string, CCImage*>::iterator it = m_ImageMap.find(pngFileName);
            if (it == m_ImageMap.end())
            {
                HSMessageBox(sPlist->getCString());
            }
            CCImage* pImage = it->second;
            
            HSReadPlist::ShareReadPlist()->Open(sPlist->getCString(), pImage);
            
            sPlist->release();
            CC_SAFE_DELETE(pImage);
        }
        m_ImageMap.clear();
#ifndef WIN32
        //        sigset_t signal_mask;
        //        sigemptyset (&signal_mask);
        //        sigaddset (&signal_mask, SIGPIPE);
        //        int rc = pthread_sigmask (SIG_BLOCK, &signal_mask, NULL);
        //        if (rc != 0) {
        //        	printf("block sigpipe error\n");
        //        }
#endif
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(AppDelegate::Updata), this, 0.1f, false);
        HS_GO_SCENE(HS_SCENE_GameMainScene);
    }
}










