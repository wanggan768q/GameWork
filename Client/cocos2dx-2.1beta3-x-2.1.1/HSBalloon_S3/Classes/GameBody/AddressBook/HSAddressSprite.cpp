#include "HSAddressSprite.h"
#include "HSReadPlist.h"
#include "HSJava.h"
#include "HSAddressBookScene.h"
#include "HSFeedbackLayer.h"
#include "MobClickCpp.h"
HSAddressSprite::HSAddressSprite(void)
{
	m_pName = NULL;
    m_HeadIcon = NULL;
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
	this->initWithFile("Image/Kaishihaoyoulandiban.png");
	this->setAnchorPoint(HS_ANCHOR_LD);
    
    CCNode* pItem_01 = HSCCSprite::create("Image/Yaoqinganniu_01.png");
    CCNode* pItem_02 = HSCCSprite::create("Image/Yaoqinganniu_02.png");
    m_pMenuItem = CCMenuItemSprite::create(pItem_01,pItem_02,this,menu_selector(HSAddressSprite::Call_Invite));
	m_pMenuItem->setPosition(ccp(482,56));
	CCMenu* pMenu = CCMenu::create(m_pMenuItem,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
    
	return true;
}

void HSAddressSprite::UpdataInfo(AddressBookResponse_Name* pName )
{
    m_address = pName;
	
	if (!m_HeadIcon)
	{
        CCString* pStr = CCString::createWithFormat("Image/%s.png","Morentouxiang");
		m_HeadIcon = HSCCSprite::create(pStr->getCString());
		m_HeadIcon->setPosition(ccp(62,56));
		this->addChild(m_HeadIcon);
        CC_SAFE_RELEASE_NULL(pStr);
	}
    
	if (!m_pName)
	{
		m_pName = CCLabelTTF::create(m_address->nick_name().c_str(),"",30.f,CCSizeZero,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		m_pName->setPosition(ccp(271,56));
		this->addChild(m_pName);
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































