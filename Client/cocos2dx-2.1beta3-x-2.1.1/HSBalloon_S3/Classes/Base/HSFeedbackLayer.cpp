//
//  HSFeedbackLayer.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-15.
//
//

#include "HSFeedbackLayer.h"

HSFeedbackLayer::HSFeedbackLayer()
{
    
}

HSFeedbackLayer::~HSFeedbackLayer()
{
    
}

HSFeedbackLayer* HSFeedbackLayer::create(const char* pText,CCNode* pShareLayer /*= NULL*/,GameSceneID sceneID /*= HS_SCENE_UNKOWN*/)
{
    HSFeedbackLayer* pFeedback = new HSFeedbackLayer;
    if(pFeedback && pFeedback->init(pText,pShareLayer,sceneID))
    {
        pFeedback->autorelease();
        return pFeedback;
    }
    CC_SAFE_DELETE(pFeedback);
    return NULL;
}

bool HSFeedbackLayer::init(const char* pText,CCNode* pShareLayer,GameSceneID sceneID)
{
    m_goSceneID = sceneID;
    m_pShareLayer = pShareLayer;
    
    HSTool::SetLayerScale(this);
    
    CCSprite* pBackground = HSCCSprite::create("Image/BEIJING.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
    CCSprite* pFenXaingDiBan = HSCCSprite::create("Image/Fankuidiban.png");
    pFenXaingDiBan->setPosition(ccp(320,630));
    this->addChild(pFenXaingDiBan);
    
    CCNode* pItem_03 = HSCCSprite::create("Image/Fenxiangfanhui_01.png");
    CCNode* pItem_04 = HSCCSprite::create("Image/Fenxiangfanhui_02.png");
    CCMenuItemSprite* pBackItem = CCMenuItemSprite::create(pItem_03, pItem_04,this,menu_selector(HSFeedbackLayer::Call_Back));
    pBackItem->setPosition(ccp(320,250));
    CCMenu* pBackMenu = CCMenu::create(pBackItem,NULL);
    pBackMenu->setPosition(CCPointZero);
    this->addChild(pBackMenu);
    
        
    
    CCNode* pTextFrame = HSCCSprite::create("Image/Fankuiwenbenkuang.png");
    pTextFrame->setPosition(ccp(320,530));
    this->addChild(pTextFrame);
    CCLabelTTF* pTTF = CCLabelTTF::create(pText, HS_FONT_HuaKang, 36.f,pTextFrame->getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
    pTTF->setPosition(pTextFrame->getAnchorPointInPoints());
    pTTF->setColor(ccBLACK);
    pTextFrame->addChild(pTTF);
    
    this->setTouchEnabled(true);
    return true;
}

void HSFeedbackLayer::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -128 , true);
}

bool HSFeedbackLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void HSFeedbackLayer::Call_Back(cocos2d::CCObject *pObj)
{
    //GameSceneID current = HSGameSceneJumpManage::SharedGameSceneJumpManage()->GetGameSceneID();
    if (m_goSceneID != HS_SCENE_UNKOWN )
    {
        HS_GO_SCENE(m_goSceneID);
    }else{
        if (m_pShareLayer)
        {
            m_pShareLayer->removeFromParent();
        }
        this->removeFromParent();
    }
}











