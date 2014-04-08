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
	m_pTextureNotFinish = HS_RP_GetSpriteFrame("Image/Suochengjiutu.png");
	m_pTextureFinish = HS_RP_GetSpriteFrame("Image/Jiangbeitu.png");

	this->initWithFile("Image/Chengjiudikuanghengtiao.png");
	this->setAnchorPoint(HS_ANCHOR_L_CENTER);
	this->setPosition(ccp(0,this->getAnchorPointInPoints().y + 15.f));


	m_pIcon = HSCCSprite::create(m_pTextureNotFinish);
	m_pIcon->setPosition(ccp(58,46));
	this->addChild(m_pIcon);

	CCSprite* pNameFrame = HSCCSprite::create("Image/XinXiKuang.png");
	pNameFrame->setPosition(ccp(265,68));
	this->addChild(pNameFrame);

	CCSprite* pDescribeFrame = HSCCSprite::create("Image/XinXiKuang.png");
	pDescribeFrame->setPosition(ccp(265,24));
	this->addChild(pDescribeFrame);

	m_pName = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,pNameFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	m_pName->setPosition(pNameFrame->getAnchorPointInPoints());
	pNameFrame->addChild(m_pName);

	m_pDescribe = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,pDescribeFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	m_pDescribe->setPosition(pDescribeFrame->getAnchorPointInPoints());
	pDescribeFrame->addChild(m_pDescribe);

    CCNode* pItem_01 = HSCCSprite::create("Image/Lingquanniu_01.png");
    CCNode* pitem_02 = HSCCSprite::create("Image/Lingquanniu_02.png");
	CCMenuItemSprite* pMenuItem = CCMenuItemSprite::create(pItem_01,pitem_02,this,menu_selector(HSAchievemenSrpite::Call));
	pMenuItem->setPosition(ccp(467,46));
	m_pGetMenu= CCMenu::create(pMenuItem,NULL);
	m_pGetMenu->setPosition(ccp(0,0));
	m_pGetMenu->setVisible(false);
	this->addChild(m_pGetMenu);

	m_pFinishSprite = HSCCSprite::create("Image/Chengjiufangkuang.png");
	m_pFinishSprite->setPosition(ccp(467,46));
	this->addChild(m_pFinishSprite);

	CCSprite* pOK = HSCCSprite::create("Image/Chengjiuzhongduigou.png");
	pOK->setAnchorPoint(HS_ANCHOR_LD);
	m_pFinishSprite->addChild(pOK);


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
            m_pIcon->setDisplayFrame(m_pTextureNotFinish);
			m_pGetMenu->setVisible(false);
			m_pFinishSprite->setVisible(false);
		}
            break;
        case AchievementResponse_AchievemenStateInfo_State_State_Can_Receive:
		{
            m_pIcon->setDisplayFrame(m_pTextureFinish);
			m_pGetMenu->setVisible(true);
            m_pFinishSprite->setVisible(false);
		}
            break;
        case AchievementResponse_AchievemenStateInfo_State_State_Have_Receive:
		{
            m_pIcon->setDisplayFrame(m_pTextureFinish);
			m_pGetMenu->setVisible(false);
			m_pFinishSprite->setVisible(true);
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

		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
		HSAchievemenLayer* pLayer = ((HSAchievemenScene*)pScene)->GetHSAchievemenLayer();
		pLayer->GetHaveReceiveNum()++;
	}
}







