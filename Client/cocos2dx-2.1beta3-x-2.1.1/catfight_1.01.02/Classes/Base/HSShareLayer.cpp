//
//  HSShare.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-13.
//
//

#include "HSShareLayer.h"
#include "HSGameCache.h"
#include "HSJava.h"
#include "HSFeedbackLayer.h"
#include "MobClickCpp.h"
HSShareLayer::HSShareLayer()
{
    
}

HSShareLayer::~HSShareLayer()
{
    
}

HSShareLayer* HSShareLayer::create(const HSShareData& shareData)
{
    HSShareLayer* pShare = new HSShareLayer;
    if(pShare && pShare->init(shareData))
    {
        pShare->autorelease();
        return pShare;
    }
    CC_SAFE_DELETE(pShare);
    return NULL;
}

bool HSShareLayer::init(const HSShareData& shareData)
{
    HSTool::SetLayerScale(this);
    m_shareData = shareData;
    
    CCSprite* pBackground = HSCCSprite::create("Image/BEIJING.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
    
    CCSprite* pFenXaingDiBan = HSCCSprite::create("Image/fenxiangdiban.png");
    pFenXaingDiBan->setPosition(ccp(320,630));
    this->addChild(pFenXaingDiBan);
    
    CCNode* pItem_01 = HSCCSprite::create("Image/xuanyao_01.png");
    CCNode* pItem_02 = HSCCSprite::create("Image/xuanyao_02.png");
    CCMenuItemSprite* pSendWeiBoItem = CCMenuItemSprite::create(pItem_01, pItem_02,this,menu_selector(HSShareLayer::Call_SendWeiBo));
    pSendWeiBoItem->setPosition(ccp(468,220));
    CCMenu* pSendWeiBoMenu = CCMenu::create(pSendWeiBoItem,NULL);
    pSendWeiBoMenu->setPosition(CCPointZero);
    this->addChild(pSendWeiBoMenu);
    
    CCNode* pItem_03 = HSCCSprite::create("Image/xiacizaishuo_01.png");
    CCNode* pItem_04 = HSCCSprite::create("Image/xiacizaishuo_02.png");
    CCMenuItemSprite* pBackItem = CCMenuItemSprite::create(pItem_03, pItem_04,this,menu_selector(HSShareLayer::Call_Back));
    pBackItem->setPosition(ccp(170,220));
    CCMenu* pBackMenu = CCMenu::create(pBackItem,NULL);
    pBackMenu->setPosition(CCPointZero);
    this->addChild(pBackMenu);
    

    CCNode* pTextFrame = HSCCSprite::create("Image/fenxiangwenzidiban.png");
    pTextFrame->setPosition(ccp(320,480));
    this->addChild(pTextFrame);
    CCLabelTTF* pTTF = CCLabelTTF::create(shareData.shareText.c_str(), HS_FONT_HuaKang, 25.f,pTextFrame->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
    pTTF->setPosition(pTextFrame->getAnchorPointInPoints());
    pTTF->setColor(ccBLACK);
    pTextFrame->addChild(pTTF);
    
    if (m_shareData.money != 0)
    {
        CCNode* pLingDangXiao = HSCCSprite::create("Image/Lingdangxiao.png");
        pLingDangXiao->setPosition(ccp(214,360));
        this->addChild(pLingDangXiao);
        CCNode* pMoneyFrame = HSCCSprite::create("Image/fenxiangwenzidiban.png");
        pMoneyFrame->setPosition(ccp(320,360));
        this->addChild(pMoneyFrame);
        CCString* pAddMoney = CCString::createWithFormat(":%d",m_shareData.money);
        CCTexture2D* pMoneyTexture = CCTextureCache::sharedTextureCache()->addImage("Image/fenxiangjiemianshuzi.png");
        CCLabelAtlas* pMoney =  CCLabelAtlas::create(pAddMoney->getCString(),"Image/fenxiangjiemianshuzi.png",pMoneyTexture->getPixelsWide() / 11.f,pMoneyTexture->getPixelsHigh(),'0');
        pMoney->setAnchorPoint(HS_ANCHOR_CENTER);
        pMoney->setPosition(pMoneyFrame->getAnchorPointInPoints());
        pMoneyFrame->addChild(pMoney);
        
        pAddMoney->release();
    }

    this->setTouchEnabled(true);
    return true;
}

void HSShareLayer::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSShareLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void HSShareLayer::Call_SendWeiBo(cocos2d::CCObject *pObj)
{
	eventDict dict;
	dict["type"] ="pureShared";
	MobClickCpp::event("HSShared",&dict);

    HSJava::ShaderJava()->JavaExec(m_shareData.wbText.c_str());
    
    if (0 != strcmp(HS_GAME_CACHE()->GetLoginType(), "99"))
    {
        CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
        HSFeedbackLayer* pFeedback = HSFeedbackLayer::create(m_shareData.feedbackText.c_str(),this,m_shareData.goSceneID);
        pScene->addChild(pFeedback,200000);
    }
    
}

void HSShareLayer::Call_Back(cocos2d::CCObject *pObj)
{
    //GameSceneID current = HSGameSceneJumpManage::SharedGameSceneJumpManage()->GetGameSceneID();
    if (m_shareData.goSceneID != HS_SCENE_UNKOWN )
    {
        HS_GO_SCENE(m_shareData.goSceneID);
    }else{
        this->removeFromParent();
    }
}
























