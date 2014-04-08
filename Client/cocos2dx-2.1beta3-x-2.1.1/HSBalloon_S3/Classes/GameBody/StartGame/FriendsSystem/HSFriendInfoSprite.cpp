#include "HSFriendInfoSprite.h"
#include "HSReadPlist.h"
#include "HSShareLayer.h"
#include "HSGameCache.h"


HSFriendInfoSprite::HSFriendInfoSprite(void)
{
	m_pTrophyTexture_0 = NULL;
	m_pTrophyTexture_1 = NULL;
	m_pTrophyTexture_2 = NULL;
	m_pName = NULL;
	m_pMoney = NULL;
	m_pGameScore = NULL;
	m_pRanking = NULL;
	m_HeadIcon = NULL;
    m_pTrophy = NULL;
    m_pGameScoreFrame = NULL;
    m_pNameFrame = NULL;
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

HSFriendInfoSprite* HSFriendInfoSprite::createWithDefault()
{
    HSFriendInfoSprite* pSprite = new HSFriendInfoSprite();
	if(pSprite && pSprite->InitWithDefault())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool HSFriendInfoSprite::Init()
{
	m_pTrophyTexture_0 = HS_RP_GetSpriteFrame("Image/Kaishipaiming1.png");
	m_pTrophyTexture_1 = HS_RP_GetSpriteFrame("Image/Kaishipaiming2.png");
	m_pTrophyTexture_2 = HS_RP_GetSpriteFrame("Image/Kaishipaiming3.png");
    
	this->initWithFile("Image/Kaishihaoyoulandiban.png");
	this->setAnchorPoint(HS_ANCHOR_LD);
    
    m_pGameScoreFrame = HSCCSprite::create("Image/Kaishifenshu.png");
    m_pGameScoreFrame->setPosition(ccp(346,51));
    this->addChild(m_pGameScoreFrame);
    
    m_pNameFrame = HSCCSprite::create("Image/Kaishixingming.png");
    m_pNameFrame->setPosition(ccp(346,77));
    this->addChild(m_pNameFrame);
    
	return true;
}

bool HSFriendInfoSprite::InitWithDefault()
{
    this->initWithFile("Image/Kaishitianjiahaoyoulan.png");
    this->setAnchorPoint(HS_ANCHOR_LD);
    CCMenuItemImage* item = CCMenuItemImage::create("Image/Kaishitianjiahaoyoulan.png", "Image/Kaishitianjiahaoyoulan.png", this, menu_selector(HSFriendInfoSprite::Call_AddFriend));
    item->setPosition(HS_SizeHalf_Point(this->getContentSize()));
    CCMenu* pMenu = CCMenu::create(item,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
    
    return true;
}

void HSFriendInfoSprite::Call_AddFriend(CCObject* obj)
{
    CCMenuItem* item = dynamic_cast<CCMenuItem*>(obj);
    item->setEnabled(false);
    
    HS_GO_SCENE(HS_SCENE_AddressBookScene);
}

void HSFriendInfoSprite::UpdataPlayerInfo(int index, FriendListResponse_PlayerInfo* pPlayerInfo )
{
    m_pFirendInfo = pPlayerInfo;

    switch (index)
    {
        case 0:
        {
            if(!m_pTrophy)
            {
                m_pTrophy = HSCCSprite::create(m_pTrophyTexture_0);
                m_pTrophy->setPosition(ccp(65,51));
                this->addChild(m_pTrophy);
            }else{
                m_pTrophy->setDisplayFrame(m_pTrophyTexture_0);
            }
        }
            break;
        case 1:
        {
            if(!m_pTrophy)
            {
                m_pTrophy = HSCCSprite::create(m_pTrophyTexture_1);
                m_pTrophy->setPosition(ccp(65,51));
                this->addChild(m_pTrophy);
            }else{
                //m_pTrophy->setDisplayFrame(m_pTrophyTexture_1);
            }
        }
            break;
        case 2:
        {
            if(!m_pTrophy)
            {
                m_pTrophy = HSCCSprite::create(m_pTrophyTexture_2);
                m_pTrophy->setPosition(ccp(65,51));
                this->addChild(m_pTrophy);
            }else{
                //m_pTrophy->setDisplayFrame(m_pTrophyTexture_2);
            }
        }
            break;
        default:
        {
            CCString* pRankingStr = CCString::createWithFormat("%02d",index);
            if (!m_pRanking)
            {
                CCTexture2D* temp = CCTextureCache::sharedTextureCache()->addImage("Image/Kaishimingcishuzi.png");
                m_pRanking = CCLabelAtlas::create(pRankingStr->getCString(),"Image/Kaishimingcishuzi.png",temp->getPixelsWide() / 10,temp->getPixelsHigh(),'0');
                m_pRanking->setAnchorPoint(HS_ANCHOR_CENTER);
                m_pRanking->setPosition(ccp(65,51));
                this->addChild(m_pRanking);
            }else{
                m_pRanking->setString(pRankingStr->getCString());
            }
            CC_SAFE_RELEASE_NULL(pRankingStr);
        }
            break;
    }
    
    if (!m_HeadIcon)
	{
        CCString* pHeadStr = CCString::createWithFormat("Image/%d.png",pPlayerInfo->headicon());
        
		m_HeadIcon = HSCCSprite::create(pHeadStr->getCString());
		m_HeadIcon->setPosition(ccp(173,51));
		this->addChild(m_HeadIcon);
        CC_SAFE_RELEASE_NULL(pHeadStr);
	}
    
    if(!m_pName)
    {
        m_pName = CCLabelTTF::create(pPlayerInfo->friendname().c_str(),HS_FONT_HuaKang,24,m_pNameFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
        m_pName->setPosition(m_pNameFrame->getAnchorPointInPoints());
        m_pNameFrame->addChild(m_pName);
    }
    
    if (!m_pGameScore)
    {
        CCString* pGameScoreStr = CCString::createWithFormat("%d",pPlayerInfo->gamescore());
        m_pGameScore = CCLabelTTF::create(pGameScoreStr->getCString(),HS_FONT_HuaKang,48,m_pGameScoreFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentBottom);
        CCPoint pos = m_pGameScoreFrame->getAnchorPointInPoints();
        pos.y -= 10;
        m_pGameScore->setPosition(pos);
        m_pGameScoreFrame->addChild(m_pGameScore);
        CC_SAFE_RELEASE_NULL(pGameScoreStr);
    }
    
    if(pPlayerInfo->game_uuid() == HS_TARGET_SELF().uid())
    {
        CCNode* pItem_01 = HSCCSprite::create("Image/Kaishizengsong_on.png");
        CCNode* pItem_02 = HSCCSprite::create("Image/Kaishizengsong_off.png");
        CCNode* pItem_03 = HSCCSprite::create("Image/Kaishizengsong_off.png");
        CCNode* pItem_04 = HSCCSprite::create("Image/Kaishizengsong_on.png");
        
        CCMenuItemSprite* itemImage1 = CCMenuItemSprite::create(pItem_01,pItem_02);
        CCMenuItemSprite* itemImage2 = CCMenuItemSprite::create(pItem_03,pItem_04);
        
        CCMenuItemToggle* pToggle = CCMenuItemToggle::createWithTarget(this,menu_selector(HSFriendInfoSprite::Call_IsAcceptTrophy),itemImage1,itemImage2,NULL);
        pToggle->setPosition(ccp(517,51));
        CCMenu* pMenu = CCMenu::create(pToggle,NULL);
        pMenu->setPosition(CCPointZero);
        this->addChild(pMenu);
        
        //是否接受邮件提示
        if(HS_GAME_CACHE_DATA()->isalreadyrungameguide())
        {
            pToggle->setSelectedIndex(1);
        }
    }else{
    
        CCNode* pItem_01 = HSCCSprite::create("Image/Kaishizengsong_0.png");
        CCNode* pItem_02 = HSCCSprite::create("Image/Kaishizengsong_1.png");
        CCNode* pItem_03 = HSCCSprite::create("Image/Kaishizengsong_1.png");
        CCNode* pItem_04 = HSCCSprite::create("Image/Kaishizengsong_0.png");
        
        CCMenuItemSprite* itemImage1 = CCMenuItemSprite::create(pItem_01,pItem_02);
        CCMenuItemSprite* itemImage2 = CCMenuItemSprite::create(pItem_03,pItem_04);
        
        CCMenuItemToggle* pToggle = CCMenuItemToggle::createWithTarget(this,menu_selector(HSFriendInfoSprite::Call_GiveTrophy),itemImage1,itemImage2,NULL);
        pToggle->setPosition(ccp(517,51));
        CCMenu* pMenu = CCMenu::create(pToggle,NULL);
        pMenu->setPosition(CCPointZero);
        this->addChild(pMenu);
        
        //是否允许赠送
        if(!m_pFirendInfo->isallowgive())
        {
            pToggle->setSelectedIndex(1);
        }
    }
}

void HSFriendInfoSprite::Call_GiveTrophy(CCObject* pObj)
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

void HSFriendInfoSprite::Call_IsAcceptTrophy(CCObject* pObj)
{
    HS_MUTABLE_GAME_CACHE_DATA()->set_isaccepttrophynotification(!HS_GAME_CACHE_DATA()->isalreadyrungameguide());
}















