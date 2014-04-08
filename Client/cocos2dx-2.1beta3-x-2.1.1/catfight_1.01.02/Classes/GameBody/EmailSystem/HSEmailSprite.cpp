#include "HSEmailSprite.h"
#include "HSReadPlist.h"
#include "HSJava.h"
#include "HSEmailSystemScene.h"
#include "HSShareLayer.h"

HSEmailSprite::HSEmailSprite(void)
{
    m_pEmailInfo = NULL;
	m_pName = NULL;
    m_pNameFrame = NULL;
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
	this->initWithFile("Image/Haoyoujiemiandilan.png");
	this->setAnchorPoint(HS_ANCHOR_LD);
    
	m_pNameFrame = CCNode::create();
    m_pNameFrame->setContentSize(CCSizeMake(274, 60));
	m_pNameFrame->setPosition(ccp(275,67));
	this->addChild(m_pNameFrame);
    
    CCNode* pItem_01 = HSCCSprite::create("Image/lingquanniu.png");
    CCNode* pItem_02 = HSCCSprite::create("Image/lingquanniu.png");
    CCNode* pItem_03 = HSGraySprite::create("Image/lingquanniu.png");
    CCNode* pItem_04 = HSGraySprite::create("Image/lingquanniu.png");
    
    CCMenuItemSprite* itemImage1 = CCMenuItemSprite::create(pItem_01,pItem_02);
	CCMenuItemSprite* itemImage2 = CCMenuItemSprite::create(pItem_03,pItem_04);
    
	CCMenuItemToggle* m_pMenuItem = CCMenuItemToggle::createWithTarget(this,menu_selector(HSEmailSprite::Call_GetAward),itemImage1,itemImage2,NULL);
	m_pMenuItem->setPosition(ccp(467,45));
	CCMenu* pMenu = CCMenu::create(m_pMenuItem,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
    
	return true;
}

void HSEmailSprite::UpdataInfo(EmailResponse_EmailInfo* pEmailInfo )
{
    m_pEmailInfo = pEmailInfo;
	
//	if (!m_HeadIcon)
//	{
//		m_HeadIcon = HSCCSprite::create(CCString::createWithFormat("Image/%s",pPlayerInfo->headicon().c_str())->getCString());
//		m_HeadIcon->setPosition(m_pHeadFrame->getAnchorPointInPoints());
//		m_pHeadFrame->addChild(m_HeadIcon);
//	}
//    
	if (!m_pName)
	{
		m_pName = CCLabelTTF::create(pEmailInfo->givepalyername().c_str(),"",30.f,m_pNameFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
		m_pName->setPosition(m_pNameFrame->getAnchorPointInPoints());
		m_pNameFrame->addChild(m_pName);
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






























