#include "HSAddressSprite.h"
#include "HSReadPlist.h"
#include "HSJava.h"
#include "HSAddressBookScene.h"
#include "HSFeedbackLayer.h"
#include "MobClickCpp.h"
HSAddressSprite::HSAddressSprite(void)
{
	m_pName = NULL;
    m_pNameFrame = NULL;
}

HSAddressSprite::~HSAddressSprite(void)
{
}

HSAddressSprite* HSAddressSprite::create()
{
	HSAddressSprite* pSprite = new HSAddressSprite();
	if(pSprite && pSprite->Init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool HSAddressSprite::Init()
{
	this->initWithFile("Image/Haoyoujiemiandilan.png");
	this->setAnchorPoint(HS_ANCHOR_LD);
    
	m_pNameFrame = CCNode::create();
    m_pNameFrame->setContentSize(CCSizeMake(274, 60));
	m_pNameFrame->setPosition(ccp(275,67));
	this->addChild(m_pNameFrame);
    
    CCNode* pItem_01 = HSCCSprite::create("Image/yaoqing_01.png");
    CCNode* pItem_02 = HSCCSprite::create("Image/yaoqing_02.png");
    CCNode* pItem_03 = HSGraySprite::create("Image/yaoqing_02.png");
    CCNode* pItem_04 = HSGraySprite::create("Image/yaoqing_02.png");

    
    CCMenuItemSprite* itemImage1 = CCMenuItemSprite::create(pItem_01,pItem_02);
	CCMenuItemSprite* itemImage2 = CCMenuItemSprite::create(pItem_03,pItem_04);
    
	CCMenuItemToggle* m_pMenuItem = CCMenuItemToggle::createWithTarget(this,menu_selector(HSAddressSprite::Call_Invite),itemImage1,itemImage2,NULL);
	m_pMenuItem->setPosition(ccp(422,45));
	CCMenu* pMenu = CCMenu::create(m_pMenuItem,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
    
	return true;
}

void HSAddressSprite::UpdataInfo(AddressBookResponse_Name* pName )
{
    m_address = pName;
	
//	if (!m_HeadIcon)
//	{
//		m_HeadIcon = HSCCSprite::create(CCString::createWithFormat("Image/%s",pPlayerInfo->headicon().c_str())->getCString());
//		m_HeadIcon->setPosition(m_pHeadFrame->getAnchorPointInPoints());
//		m_pHeadFrame->addChild(m_HeadIcon);
//	}
//    
	if (!m_pName)
	{
		m_pName = CCLabelTTF::create(m_address->nick_name().c_str(),"",30.f,m_pNameFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
		m_pName->setPosition(m_pNameFrame->getAnchorPointInPoints());
		m_pNameFrame->addChild(m_pName);
	}
}

void HSAddressSprite::Call_Invite( CCObject* pObj )
{
    CCMenuItem* pItem = dynamic_cast<CCMenuItem*>(pObj);
    pItem->setEnabled(false);
    
    eventDict dict;
    dict["type"] ="inviteShared";
    MobClickCpp::event("HSShared",&dict);


    CCString* pText = CCString::createWithFormat(L("AddressBook"),m_address->wb_name().c_str(),HS_GAME_CACHE()->m_gameName.c_str(),HS_GAME_CACHE()->m_gameDownload.c_str());
    
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
        HSFeedbackLayer* pFeedbackLayer = HSFeedbackLayer::create(L("SendGift_Feedback"));
        pScene->addChild(pFeedbackLayer,10000);
    }
    
    
}































