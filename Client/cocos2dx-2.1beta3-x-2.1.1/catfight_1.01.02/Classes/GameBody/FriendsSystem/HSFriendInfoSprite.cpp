#include "HSFriendInfoSprite.h"
#include "HSReadPlist.h"
#include "HSShareLayer.h"


HSFriendInfoSprite::HSFriendInfoSprite(void)
{
	m_pTrophyTexture_0 = NULL;
	m_pTrophyTexture_1 = NULL;
	m_pTrophyTexture_2 = NULL;
	m_pState_0 = NULL;
	m_pState_1 = NULL;
	m_pState_2 = NULL;
	m_pName = NULL;
	m_pMoney = NULL;
	m_pGameScore = NULL;
	m_pRanking = NULL;
	m_HeadIcon = NULL;
}

HSFriendInfoSprite::~HSFriendInfoSprite(void)
{
}

HSFriendInfoSprite* HSFriendInfoSprite::create()
{
	HSFriendInfoSprite* pSprite = new HSFriendInfoSprite();
	if(pSprite && pSprite->Init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool HSFriendInfoSprite::Init()
{
	m_pTrophyTexture_0 = HS_RP_GetSpriteFrame("Image/Jinjiangbei.png");
	m_pTrophyTexture_1 = HS_RP_GetSpriteFrame("Image/Yinjiangbei.png");
	m_pTrophyTexture_2 = HS_RP_GetSpriteFrame("Image/Tongjiangbei.png");
    
//	m_pState_0 = HS_RP_GetSpriteFrame("Image/Zaixian.png");
//	m_pState_1 = HS_RP_GetSpriteFrame("Image/Zanli.png");
//	m_pState_2 = HS_RP_GetSpriteFrame("Image/Lixian.png");
    
	this->initWithFile("Image/Haoyoujiemiandilan.png");
	this->setAnchorPoint(HS_ANCHOR_LD);
	//this->setPosition(ccp(0,this->getAnchorPointInPoints().y + 20.f));
	//m_pFriendFrame = CCSprite::create("Image/FriendsSystem/Haoyoujiemiandilan.png");
	//m_pFriendFrame->setAnchorPoint(HS_ANCHOR_L_CENTER);
	//m_pFriendFrame->setPosition(ccp(0,m_pFriendFrame->getAnchorPointInPoints().y));
	//@
//	CCSprite* pFenXian = HSCCSprite::create("Image/FengeXian.png");
//	pFenXian->setPosition(ccp(284,45));
//	this->addChild(pFenXian);
	//@
	m_pHeadFrame = HSCCSprite::create("Image/Touxiangkuang.png");
	m_pHeadFrame->setPosition(ccp(140,45));
	this->addChild(m_pHeadFrame);
	//@
	m_pTrophy = HSCCSprite::create(m_pTrophyTexture_0);
	m_pTrophy->setPosition(ccp(48,45));
	this->addChild(m_pTrophy);
    
//	m_pState = HSCCSprite::create(m_pState_0);
//	m_pState->setPosition(ccp(172,24));
//	this->addChild(m_pState);
    
	m_pNameFrame = HSCCSprite::create("Image/Mingziditu.png");
	m_pNameFrame->setPosition(ccp(275,67));
	this->addChild(m_pNameFrame);
    
	m_pMoneyFrame = HSCCSprite::create("Image/Jinbidiandikuang.png");
	m_pMoneyFrame->setPosition(ccp(304,24));
	this->addChild(m_pMoneyFrame);
    

    CCNode* pItem_01 = HSCCSprite::create("Image/zengsonganniu.png");
    CCNode* pItem_02 = HSCCSprite::create("Image/zengsonganniu.png");
	CCMenuItemSprite* m_pMenuItem = CCMenuItemSprite::create(pItem_01,pItem_02,this,menu_selector(HSFriendInfoSprite::Call_SendEmail));
	m_pMenuItem->setPosition(ccp(467,45));
	m_pSendEmailMenu = CCMenu::create(m_pMenuItem,NULL);
	m_pSendEmailMenu->setPosition(CCPointZero);
	this->addChild(m_pSendEmailMenu);
    
    
	return true;
}

void HSFriendInfoSprite::UpdataPlayerInfo(int index, FriendListResponse_PlayerInfo* pPlayerInfo )
{
    m_pFirendInfo = pPlayerInfo;
    
    m_pTrophy->setVisible(true);
	switch (index)
    {
        case 0:
        {
            m_pTrophy->setDisplayFrame(m_pTrophyTexture_0);
        }
            break;
        case 1:
        {
            m_pTrophy->setDisplayFrame(m_pTrophyTexture_1);
        }
            break;
        case 2:
        {
            m_pTrophy->setDisplayFrame(m_pTrophyTexture_2);
        }
            break;
        default:
        {
            m_pTrophy->setVisible(false);
            if (!m_pRanking)
            {
                m_pRanking = CCLabelTTF::create(CCString::createWithFormat("%d",index)->getCString(),HS_FONT_HuaKang,25.f);
                m_pRanking->setPosition(m_pTrophy->getPosition());
                this->addChild(m_pRanking);
            }else{
                m_pRanking->setString(CCString::createWithFormat("%d",index)->getCString());
            }
            
        }
            break;
    }
    
    if (!pPlayerInfo->isallowgive())
    {
        m_pSendEmailMenu->setVisible(false);
    }
	
	if (!m_HeadIcon)
	{
		m_HeadIcon = HSCCSprite::create(CCString::createWithFormat("Image/%d.png",pPlayerInfo->headicon())->getCString());
		m_HeadIcon->setPosition(m_pHeadFrame->getAnchorPointInPoints());
		m_pHeadFrame->addChild(m_HeadIcon);
	}
    
	if (!m_pName)
	{
		m_pName = CCLabelTTF::create(pPlayerInfo->friendnickname().c_str(),"",25.f,m_pNameFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
		m_pName->setPosition(m_pNameFrame->getAnchorPointInPoints());
		m_pNameFrame->addChild(m_pName);
	}
    
//	switch (pPlayerInfo->state())
//	{
//        case FriendListResponse_PlayerInfo_State_State_Online:
//		{
//			m_pState->setDisplayFrame(m_pState_0);
//		}
//            break;
//        case FriendListResponse_PlayerInfo_State_State_Battle:
//		{
//			m_pState->setDisplayFrame(m_pState_1);
//		}
//            break;
//        case FriendListResponse_PlayerInfo_State_State_Offline:
//		{
//			m_pState->setDisplayFrame(m_pState_2);
//		}
//            break;
//        default:
//            break;
//	}
    
	if (!m_pGameScore)
    {
        m_pGameScore = CCLabelTTF::create(CCString::createWithFormat("%d",pPlayerInfo->gamescore())->getCString(),HS_FONT_HuaKang,36.f,m_pMoneyFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
        m_pGameScore->setPosition(ccpAdd(m_pMoneyFrame->getAnchorPointInPoints(),ccp(20.f,0.f)));
        m_pMoneyFrame->addChild(m_pGameScore);
    }
    
}

void HSFriendInfoSprite::Call_SendEmail( CCObject* pObj )
{
    m_pFirendInfo->set_isallowgive(false);
    
    CCMenuItem* pItem = dynamic_cast<CCMenuItem*>(pObj);
    pItem->setVisible(false);
    
    HSRequest::ShareRequest()->SendSendEmail(m_pFirendInfo->game_uuid());
    
    CCString* wbStr = CCString::createWithFormat(L("Email"),m_pFirendInfo->friendname().c_str());
    
    HSJson* pJson = HSJson::CreateWithWriter();
    Json::Value jsonData;
    jsonData["JNI_ID"] = 2002;
    jsonData["WEIBO_TEXT"] = wbStr->getCString();
    jsonData["WEIBO_TYPE"] = HS_GAME_CACHE()->GetLoginType();
    
    HSShareData shareData;
    shareData.shareText = L("SendGift");
    shareData.wbText = pJson->Writer(jsonData);
    shareData.feedbackText = L("SendGift_Feedback");
    
    CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
    HSShareLayer* pShareLayer = HSShareLayer::create(shareData);
    pScene->addChild(pShareLayer,10000);
    
    
    pJson->release();
    wbStr->release();
}

















