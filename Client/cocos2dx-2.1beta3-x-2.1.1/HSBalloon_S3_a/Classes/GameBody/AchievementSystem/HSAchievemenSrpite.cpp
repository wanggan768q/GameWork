#include "HSAchievemenSrpite.h"
#include "HSAchievemenScene.h"

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
	m_pTextureNotFinish = CCTextureCache::sharedTextureCache()->addImage("Image/AchievementSystem/Suochengjiutu.png");
	m_pTextureFinish = CCTextureCache::sharedTextureCache()->addImage("Image/AchievementSystem/Jiangbeitu.png");

	this->initWithFile("Image/AchievementSystem/Chengjiudikuanghengtiao.png");
	this->setAnchorPoint(HS_ANCHOR_L_CENTER);
	this->setPosition(ccp(0,this->getAnchorPointInPoints().y + 15.f));


	m_pIcon = CCSprite::createWithTexture(m_pTextureNotFinish);
	m_pIcon->setPosition(ccp(58,46));
	this->addChild(m_pIcon);

	CCSprite* pNameFrame = CCSprite::create("Image/AchievementSystem/XinXiKuang.png");
	pNameFrame->setPosition(ccp(265,68));
	this->addChild(pNameFrame);

	CCSprite* pDescribeFrame = CCSprite::create("Image/AchievementSystem/XinXiKuang.png");
	pDescribeFrame->setPosition(ccp(265,24));
	this->addChild(pDescribeFrame);

	m_pName = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,pNameFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	m_pName->setPosition(pNameFrame->getAnchorPointInPoints());
	pNameFrame->addChild(m_pName);

	m_pDescribe = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,pDescribeFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
	m_pDescribe->setPosition(pDescribeFrame->getAnchorPointInPoints());
	pDescribeFrame->addChild(m_pDescribe);

	CCMenuItemImage* pMenuItem = CCMenuItemImage::create("Image/AchievementSystem/Lingquanniu_01.png","Image/AchievementSystem/Lingquanniu_02.png",this,menu_selector(HSAchievemenSrpite::Call));
	pMenuItem->setPosition(ccp(467,46));
	m_pGetMenu= CCMenu::create(pMenuItem,NULL);
	m_pGetMenu->setPosition(ccp(0,0));
	m_pGetMenu->setVisible(false);
	this->addChild(m_pGetMenu);

	m_pFinishSprite = CCSprite::create("Image/AchievementSystem/Chengjiufangkuang.png");
	m_pFinishSprite->setPosition(ccp(467,46));
	this->addChild(m_pFinishSprite);

	CCSprite* pOK = CCSprite::create("Image/AchievementSystem/Chengjiuzhongduigou.png");
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
			m_pIcon->setTexture(m_pTextureNotFinish);
			m_pGetMenu->setVisible(false);
			m_pFinishSprite->setVisible(false);
		}
		break;
	case AchievementResponse_AchievemenStateInfo_State_State_Can_Receive:
		{
			m_pIcon->setTexture(m_pTextureNotFinish);
			m_pGetMenu->setVisible(true);
		}
		break;
	case AchievementResponse_AchievemenStateInfo_State_State_Have_Receive:
		{
			m_pIcon->setTexture(m_pTextureFinish);
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
		HSRequest::ShareRequest()->SendReceiveAchievementRewardRequest(m_pInfoData->achievementid());
		m_pInfoData->set_state(AchievementResponse_AchievemenStateInfo_State_State_Have_Receive);
		UpdataAchievemen(m_pInfoData);

		CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
		HSAchievemenLayer* pLayer = ((HSAchievemenScene*)pScene)->GetHSAchievemenLayer();
		pLayer->GetHaveReceiveNum()++;
	}
}
