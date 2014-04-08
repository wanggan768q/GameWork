#include "HSEmailSprite.h"
#include "HSReadPlist.h"
#include "HSJava.h"
#include "HSEmailSystemScene.h"
#include "HSShareLayer.h"

HSEmailSprite::HSEmailSprite(void)
{
    m_pEmailInfo = NULL;
	m_pName = NULL;
    m_pMenuItem = NULL;
}

HSEmailSprite::~HSEmailSprite(void)
{
}

HSEmailSprite* HSEmailSprite::create()
{
	HSEmailSprite* pSprite = new HSEmailSprite();
	if(pSprite && pSprite->Init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool HSEmailSprite::Init()
{
	this->initWithFile("Image/Kaishihaoyoulandiban.png");
	this->setAnchorPoint(HS_ANCHOR_LD);
    
    CCNode* pItem_01 = HSCCSprite::create("Image/Kaishizengsong_0.png");
    CCNode* pItem_02 = HSCCSprite::create("Image/Kaishizengsong_0.png");
    m_pMenuItem = CCMenuItemSprite::create(pItem_01,pItem_02,this,menu_selector(HSEmailSprite::Call_GetAward));
	m_pMenuItem->setPosition(ccp(482,56));
	CCMenu* pMenu = CCMenu::create(m_pMenuItem,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
    
	return true;
}

void HSEmailSprite::UpdataInfo(EmailResponse_EmailInfo* pEmailInfo )
{
    m_pEmailInfo = pEmailInfo;
    
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
		m_pName = CCLabelTTF::create(pEmailInfo->givepalyername().c_str(),"",30.f,CCSizeZero,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		m_pName->setPosition(ccp(271,56));
		this->addChild(m_pName);
	}
}

void HSEmailSprite::Call_GetAward( CCObject* pObj )
{
    CCMenuItem* pItem = dynamic_cast<CCMenuItem*>(pObj);
    pItem->setEnabled(false);
    

    std::vector<unsigned long long> v;
    v.push_back(m_pEmailInfo->email_id());
    HSRequest::ShareRequest()->SendOPenEmailRequest(v);
    
    
    CCString* pText = CCString::createWithFormat(L("Email"),m_pEmailInfo->givepalyername().c_str());
    
    HSJson* pJson = HSJson::CreateWithWriter();
    Json::Value jsonData;
    jsonData["JNI_ID"] = 2002;
    jsonData["WEIBO_TEXT"] = pText->getCString();
    jsonData["WEIBO_TYPE"] = HS_GAME_CACHE()->GetLoginType();
    
    HSShareData shareData;
    shareData.wbText = pJson->Writer(jsonData);
    shareData.shareText = L("GetGift");
    shareData.feedbackText = L("SendGift_Feedback");
    
    CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
    HSShareLayer* pShareLayer = HSShareLayer::create(shareData);
    pScene->addChild(pShareLayer,1000);
    
}






























