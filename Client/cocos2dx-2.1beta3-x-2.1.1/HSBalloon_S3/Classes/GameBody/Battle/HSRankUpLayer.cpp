//
//  HSRankUp.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-11-13.
//
//

#include "HSRankUpLayer.h"
#include "HSGameCache.h"
#include "HSJava.h"
#include "HSFeedbackLayer.h"
#include "MobClickCpp.h"
HSRankUpLayer::HSRankUpLayer()
{
    m_pFriendInfo = NULL;
    m_selfGameScore = 0;
}

HSRankUpLayer::~HSRankUpLayer()
{
    
}

bool HSRankUpLayer::init()
{
    if (!CCLayer::init())
	{
		return false;
	}
    
    int selfRankNum = 0;
    int frinedRankNUm = 0;
    
    //计算排名逻辑
    {
        m_selfGameScore = HS_GAME_CACHE()->GetSelfGameScore();
        
        for (int i=0; i<HS_GAME_CACHE()->m_FriendListResponse.friendlist_size(); ++i)
        {
            m_pFriendInfo = HS_GAME_CACHE()->m_FriendListResponse.mutable_friendlist(i);
            if (m_pFriendInfo->gamescore() < m_selfGameScore)
            {
                selfRankNum = i + 1;
                frinedRankNUm = selfRankNum + 1;
                break;
            }
        }
    }
	
	HSTool::SetLayerScale(this);
    
    CCSprite* pBackground = HSCCSprite::create("Image/BEIJING.png");
	pBackground->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pBackground);
	HSTool::SetNodeFilldScreen(pBackground);
    
    CCSprite* pFenXiang = HSCCSprite::create("Image/Fenxiangbeijing.png");
	pFenXiang->setPosition(HSBase::GetTemplateScreenCentre());
	this->addChild(pFenXiang);
    
    HSReadUI::ShareReadUI()->ReadUI("Image/RankUp.data","Image/",this);
    HS_SET_MENU_TARGET("UI_gaosuta", this,HSRankUpLayer::Call_SendWeiBo);
    HS_SET_MENU_TARGET("UI_fanhuianniu", this,HSRankUpLayer::Call_Back);
    
    m_pSun = HS_FIND_UI_PANEL_SPRITE("UI_guangxiao", "Fenxiangguangxiao");
    m_pSun->setVisible(false);
    
    m_pStar = HS_FIND_UI_PANEL_SPRITE("UI_xingguangxiaoguo", "Fenxiangxingxing");
    m_pStar->setVisible(false);
    
    m_pRankUP = HS_FIND_UI_PANEL_SPRITE("UI_paimingshangshengle", "Paimingshangshengle");
    m_pRankUP->setVisible(false);
    
    HS_FIND_UI_MENU("UI_gaosuta")->setVisible(false);
    HS_FIND_UI_MENU("UI_fanhuianniu")->setVisible(false);
    
    
    ccBezierConfig bezierConfig_01;
    bezierConfig_01.controlPoint_1 = ccp(85,581);
    bezierConfig_01.controlPoint_2 = ccp(12,621);
    bezierConfig_01.endPosition = ccp(54,661);
    
    ccBezierConfig bezierConfig_02;
    bezierConfig_02.controlPoint_1 = ccp(294,661);
    bezierConfig_02.controlPoint_2 = ccp(367,621);
    bezierConfig_02.endPosition = ccp(345,581);
    
    CCActionInterval * action_01 = CCBezierTo::create(1.f, bezierConfig_01);
    CCActionInterval * action_02 = CCBezierTo::create(1.f, bezierConfig_02);
    
    CCNode* pSelf = HS_FIND_UI_PANEL("UI_zijiban");
    CCNode* pFriend = HS_FIND_UI_PANEL("UI_duifangban");
    CCCallFunc* pCallFunc = CCCallFunc::create(this,callfunc_selector(HSRankUpLayer::Call_Up));
    pSelf->runAction(CCSequence::create(action_01,pCallFunc,NULL));
    pFriend->runAction(CCSequence::create(action_02,NULL));
    
    CCNode* pSelfRankNumFrame = HS_FIND_UI_PANEL_SPRITE("UI_zijiban","mingcishuzidikuang");
    CCNode* pFriendRankNumFrame = HS_FIND_UI_PANEL_SPRITE("UI_duifangban","mingcishuzidikuang");
    
    
    
    
    CCString* pSelfRankNumStr = CCString::createWithFormat("%d",selfRankNum);
    CCString* pFriendRankNumStr = CCString::createWithFormat("%d",frinedRankNUm);
    
    
    CCTexture2D* pRankNumTexture = CCTextureCache::sharedTextureCache()->addImage("Image/ComboNumber.png");
    CCLabelAtlas* pSelfRankNum = CCLabelAtlas::create(pSelfRankNumStr->getCString(),"Image/ComboNumber.png",pRankNumTexture->getPixelsWide() / 10,pRankNumTexture->getPixelsHigh(),'0');
    pSelfRankNum->setPosition(pSelfRankNumFrame->getAnchorPoint());
    pSelfRankNumFrame->addChild(pSelfRankNum);
    
    CCLabelAtlas* pFriendRankNum = CCLabelAtlas::create(pFriendRankNumStr->getCString(),"Image/ComboNumber.png",pRankNumTexture->getPixelsWide() / 10,pRankNumTexture->getPixelsHigh(),'0');
    pFriendRankNum->setPosition(pFriendRankNumFrame->getAnchorPoint());
    pFriendRankNumFrame->addChild(pFriendRankNum);
    
    pSelfRankNumStr->release();
    pFriendRankNumStr->release();
    
    
    //头像
    CCNode* pSelfHeadFrame = HS_FIND_UI_PANEL_SPRITE("UI_zijiban", "touxiangdikuang");
    CCNode* pFriendHeadFrame = HS_FIND_UI_PANEL_SPRITE("UI_duifangban", "touxiangdikuang");
    CCString* pSelfHeadName = CCString::createWithFormat("Image/%d.png",HS_TARGET_SELF().iconid());
    CCString* pFrinedHeadName = CCString::createWithFormat("Image/%d.png",m_pFriendInfo->headicon());
    CCSprite* pSelfHeadSprite = HSCCSprite::create(pSelfHeadName->getCString());
    CCSprite* pFriendHeadSprite = HSCCSprite::create(pFrinedHeadName->getCString());
    pSelfHeadSprite->setPosition(pSelfHeadFrame->getAnchorPointInPoints());
    pFriendHeadSprite->setPosition(pFriendHeadFrame->getAnchorPointInPoints());
    pSelfHeadFrame->addChild(pSelfHeadSprite);
    pFriendHeadFrame->addChild(pFriendHeadSprite);
    
    pSelfHeadName->release();
    pFrinedHeadName->release();
    //名字
    CCNode* pSelfNameFrame = HS_FIND_UI_PANEL_SPRITE("UI_zijiban", "Mingziditu");
    CCNode* pFriendNameFrame = HS_FIND_UI_PANEL_SPRITE("UI_duifangban", "Mingziditu");
    
    CCLabelTTF* pSelfNameSprite = CCLabelTTF::create(HS_TARGET_SELF().name().c_str(), HS_FONT_HuaKang, 25.f);
    CCLabelTTF* pFriendNameSprite = CCLabelTTF::create(m_pFriendInfo->friendnickname().c_str(), HS_FONT_HuaKang, 25.f);
    pSelfNameSprite->setPosition(pSelfNameFrame->getAnchorPointInPoints());
    pFriendNameSprite->setPosition(pFriendNameFrame->getAnchorPointInPoints());
    pSelfNameFrame->addChild(pSelfNameSprite);
    pFriendNameFrame->addChild(pFriendNameSprite);
    
    //分数
    CCNode* pSelfGameScoreFrame = HS_FIND_UI_PANEL_SPRITE("UI_zijiban", "fenshudikuang");
    CCNode* pFriendGameScoreFrame = HS_FIND_UI_PANEL_SPRITE("UI_duifangban", "fenshudikuang");
    CCString* pSelfGameScoreStr = CCString::createWithFormat("%d",m_selfGameScore);
    CCString* pFriendGameScoreStr = CCString::createWithFormat("%d",m_pFriendInfo->gamescore());
    CCLabelTTF* pSelfGameScoreSprite = CCLabelTTF::create(pSelfGameScoreStr->getCString(), HS_FONT_HuaKang, 25.f);
    CCLabelTTF* pFriendGameScoreSprite = CCLabelTTF::create(pFriendGameScoreStr->getCString(), HS_FONT_HuaKang, 25.f);
    pSelfGameScoreSprite->setPosition(pSelfGameScoreFrame->getAnchorPointInPoints());
    pFriendGameScoreSprite->setPosition(pFriendGameScoreFrame->getAnchorPointInPoints());
    pSelfGameScoreFrame->addChild(pSelfGameScoreSprite);
    pFriendGameScoreFrame->addChild(pFriendGameScoreSprite);
    
    pFriendGameScoreStr->release();
    pSelfGameScoreStr->release();
    
    return true;
}

void HSRankUpLayer::Call_Up()
{
    m_pSun->setVisible(true);
    m_pStar->setVisible(true);
    m_pRankUP->setVisible(true);
    
    CCRotateBy* pRotate = CCRotateBy::create(20.f, 360.f);
    m_pSun->runAction(CCRepeatForever::create(CCSequence::create(pRotate,NULL)));
    
    HS_FIND_UI_MENU("UI_gaosuta")->setVisible(true);
    HS_FIND_UI_MENU("UI_fanhuianniu")->setVisible(true);
}

void HSRankUpLayer::Call_SendWeiBo(cocos2d::CCObject *pObj)
{
	eventDict dict;
	dict["type"] ="RankUpShared";
	MobClickCpp::event("HSShared",&dict);

    CCString* pText = CCString::createWithFormat(L("Score"),m_pFriendInfo->friendname().c_str(),m_selfGameScore);
    
    HSJson* pJson = HSJson::CreateWithWriter();
    Json::Value jsonData;
    jsonData["JNI_ID"] = 2002;
    jsonData["WEIBO_TEXT"] = pText->getCString();
    jsonData["WEIBO_TYPE"] = HS_GAME_CACHE()->GetLoginType();
    
    HSJava::ShaderJava()->JavaExec(pJson->Writer(jsonData).c_str());
    
    pText->release();
    pJson->release();
    
    if (0 != strcmp(HS_GAME_CACHE()->GetLoginType(), "99"))
    {
        CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
        pScene->addChild(HSFeedbackLayer::create(L("SendGift_Feedback"),this),100000);
    }
    
}

void HSRankUpLayer::Call_Back(cocos2d::CCObject *pObj)
{
    this->removeFromParent();
}
























