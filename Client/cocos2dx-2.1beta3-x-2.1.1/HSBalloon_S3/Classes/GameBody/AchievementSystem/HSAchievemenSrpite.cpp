#include "HSAchievemenSrpite.h"
#include "HSAchievemenScene.h"


AchievementResponse_AchievemenStateInfo* HSAchievemenSrpite::S_ReceiveAchievementReward = NULL;

HSAchievemenSrpite::HSAchievemenSrpite(void)
{
}


HSAchievemenSrpite::~HSAchievemenSrpite(void)
{
}

HSAchievemenSrpite* HSAchievemenSrpite::create()
{
	HSAchievemenSrpite* pSprite = new HSAchievemenSrpite;
	if(pSprite && pSprite->init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool HSAchievemenSrpite::init()
{

	this->initWithFile("Image/Kaishihaoyoulandiban.png");
	this->setAnchorPoint(HS_ANCHOR_LD);
	


	m_pIcon = HSGraySprite::create("Image/Chengjiutubiao.png");
	m_pIcon->setPosition(ccp(51,53));
	this->addChild(m_pIcon);


    CCNode* pNameFrame = CCSprite::create("Image/Chengjiuwenbenlanfanwei.png");
    pNameFrame->setPosition(ccp(264,80));
    this->addChild(pNameFrame);

	m_pName = CCLabelTTF::create("",HS_FONT_HuaKang,28,pNameFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	m_pName->setPosition(pNameFrame->getAnchorPointInPoints());
	pNameFrame->addChild(m_pName);
    
    CCNode* pDesFrame = CCSprite::create("Image/Chengjiuwenbenlanfanwei.png");
    pDesFrame->setPosition(ccp(264,35));
    this->addChild(pDesFrame);

	m_pDescribe = CCLabelTTF::create("",HS_FONT_HuaKang,18,pDesFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentTop);
	m_pDescribe->setPosition(pDesFrame->getAnchorPointInPoints());
	pDesFrame->addChild(m_pDescribe);

    CCNode* pItem_01 = HSCCSprite::create("Image/Chengjiulingqu_01.png");
    CCNode* pitem_02 = HSCCSprite::create("Image/Chengjiulingqu_02.png");
	CCMenuItemSprite* pMenuItem = CCMenuItemSprite::create(pItem_01,pitem_02,this,menu_selector(HSAchievemenSrpite::Call));
	pMenuItem->setPosition(ccp(509,53));
	m_pGetMenu= CCMenu::create(pMenuItem,NULL);
	m_pGetMenu->setPosition(CCPointZero);
	m_pGetMenu->setVisible(false);
	this->addChild(m_pGetMenu);

	m_pYiLingQu = HSCCSprite::create("Image/Chengjiuyilingqu.png");
	m_pYiLingQu->setPosition(ccp(509,53));
    m_pYiLingQu->setVisible(false);
	this->addChild(m_pYiLingQu);

	m_pWeiLingQu = HSCCSprite::create("Image/Chengjiuweiwancheng.png");
	m_pWeiLingQu->setPosition(ccp(509,53));
    m_pWeiLingQu->setVisible(false);
	this->addChild(m_pWeiLingQu);
    
    m_pSuo = HSCCSprite::create("Image/Pipeidaojusuo.png");
	m_pSuo->setPosition(ccp(51,53));
    m_pSuo->setVisible(false);
	this->addChild(m_pSuo);
    
    


	return true;
}

void HSAchievemenSrpite::UpdataAchievemen( AchievementResponse_AchievemenStateInfo* pAchievement )
{
	if (!pAchievement)
	{
		return;
	}
	m_pInfoData = pAchievement;

	std::string name = pAchievement->name();
	std::string describe = pAchievement->desc();
	m_pName->setString(name.c_str());
	m_pDescribe->setString(describe.c_str());

	switch (pAchievement->state())
	{
        case AchievementResponse_AchievemenStateInfo_State_State_Not_Receive:
		{
            m_pWeiLingQu->setVisible(true);
            m_pGetMenu->setVisible(false);
            m_pSuo->setVisible(true);
            m_pIcon->GrayProgram();
		}
            break;
        case AchievementResponse_AchievemenStateInfo_State_State_Can_Receive:
		{
            m_pIcon->RecoverProgram();
            m_pSuo->setVisible(false);
            m_pGetMenu->setVisible(true);
            m_pWeiLingQu->setVisible(false);
            m_pYiLingQu->setVisible(false);
		}
            break;
        case AchievementResponse_AchievemenStateInfo_State_State_Have_Receive:
		{
            m_pIcon->RecoverProgram();
            m_pSuo->setVisible(false);
            m_pGetMenu->setVisible(false);
            m_pYiLingQu->setVisible(true);
            m_pWeiLingQu->setVisible(false);
		}
            break;
	}
}

void HSAchievemenSrpite::Call( CCObject* pObj )
{
	if (m_pInfoData && m_pInfoData->state() == AchievementResponse_AchievemenStateInfo_State_State_Can_Receive)
	{
        HSAchievemenSrpite::S_ReceiveAchievementReward = m_pInfoData;
		HSRequest::ShareRequest()->SendReceiveAchievementRewardRequest(m_pInfoData->achievementid());
		m_pInfoData->set_state(AchievementResponse_AchievemenStateInfo_State_State_Have_Receive);
		UpdataAchievemen(m_pInfoData);

//		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
//		HSAchievemenLayer* pLayer = ((HSAchievemenScene*)pScene)->GetHSAchievemenLayer();
	}
}







