#include "HSFriendInfoSprite.h"


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

HSFriendInfoSprite* HSFriendInfoSprite::create( const HSInfoType& type )
{
	HSFriendInfoSprite* pSprite = new HSFriendInfoSprite;
	if(pSprite && pSprite->init(type))
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool HSFriendInfoSprite::init( const HSInfoType& type)
{
	m_type = type;

	m_pTrophyTexture_0 = CCTextureCache::sharedTextureCache()->addImage("Image/FriendsSystem/Jinjiangbei.png");
	m_pTrophyTexture_1 = CCTextureCache::sharedTextureCache()->addImage("Image/FriendsSystem/Yinjiangbei.png");
	m_pTrophyTexture_2 = CCTextureCache::sharedTextureCache()->addImage("Image/FriendsSystem/Tongjiangbei.png");

	m_pState_0 = CCTextureCache::sharedTextureCache()->addImage("Image/FriendsSystem/Zaixian.png");
	m_pState_1 = CCTextureCache::sharedTextureCache()->addImage("Image/FriendsSystem/Zanli.png");
	m_pState_2 = CCTextureCache::sharedTextureCache()->addImage("Image/FriendsSystem/Lixian.png");

	this->initWithFile("Image/FriendsSystem/Haoyoujiemiandilan.png");
	this->setAnchorPoint(HS_ANCHOR_LD);
	//this->setPosition(ccp(0,this->getAnchorPointInPoints().y + 20.f));
	//m_pFriendFrame = CCSprite::create("Image/FriendsSystem/Haoyoujiemiandilan.png");
	//m_pFriendFrame->setAnchorPoint(HS_ANCHOR_L_CENTER);
	//m_pFriendFrame->setPosition(ccp(0,m_pFriendFrame->getAnchorPointInPoints().y));
	//@·ÖÏß
	CCSprite* pFenXian = CCSprite::create("Image/FriendsSystem/FengeXian.png");
	pFenXian->setPosition(ccp(284,45));
	this->addChild(pFenXian);
	//@Í·Ïñ
	m_pHeadFrame = CCSprite::create("Image/FriendsSystem/Touxiangkuang.png");
	m_pHeadFrame->setPosition(ccp(140,45));
	this->addChild(m_pHeadFrame);
	//@½±±­
	m_pTrophy = CCSprite::createWithTexture(m_pTrophyTexture_0);
	m_pTrophy->setPosition(ccp(48,45));
	this->addChild(m_pTrophy);
	//@×´Ì¬
	m_pState = CCSprite::createWithTexture(m_pState_0);
	m_pState->setPosition(ccp(172,24));
	this->addChild(m_pState);
	//@Áåîõ
	m_pBell = CCSprite::create("Image/FriendsSystem/Lingdangxiao.png");
	m_pBell->setPosition(ccp(215,24));
	this->addChild(m_pBell);
	//@Ãû×Ö¿ò
	m_pNameFrame = CCSprite::create("Image/FriendsSystem/Mingziditu.png");
	m_pNameFrame->setPosition(ccp(275,67));
	this->addChild(m_pNameFrame);
	//@Ç®¿ò
	m_pMoneyFrame = CCSprite::create("Image/FriendsSystem/Jinbidiandikuang.png");
	m_pMoneyFrame->setPosition(ccp(304,24));
	this->addChild(m_pMoneyFrame);
	//@ÐÅÏ¢°´Å¥
	CCMenuItemImage* m_pMenuItem = CCMenuItemImage::create("Image/FriendsSystem/Tanchucaidananniu_01.png","Image/FriendsSystem/Tanchucaidananniu_02.png",this,menu_selector(HSFriendInfoSprite::Call));
	m_pMenuItem->setPosition(ccp(467,45));
	CCMenu* pMenu = CCMenu::create(m_pMenuItem,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	switch (type)
	{
	case InfoType_Friend:
		{
			m_pBell->setVisible(false);
		}
		break;
	case InfoType_Enemy:
		{

		}
		break;
	}

	return true;
}

void HSFriendInfoSprite::UpdataPlayerInfo(int index, const FriendInfoResponse_PlayerInfo* pPlayerInfo )
{

	switch (m_type)
	{
	case InfoType_Friend:
		{
			switch (index)
			{
			case 0:
				{
					m_pTrophy->setTexture(m_pTrophyTexture_0);
				}
				break;
			case 1:
				{
					m_pTrophy->setTexture(m_pTrophyTexture_1);
				}
				break;
			case 2:
				{
					m_pTrophy->setTexture(m_pTrophyTexture_2);
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
		}
		break;
	case InfoType_Enemy:
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

	




	
	if (!m_HeadIcon)
	{
		m_HeadIcon = CCSprite::create(CCString::createWithFormat("Image/%s",pPlayerInfo->headicon().c_str())->getCString());
		m_HeadIcon->setPosition(m_pHeadFrame->getAnchorPointInPoints());
		m_pHeadFrame->addChild(m_HeadIcon);
	}

	if (!m_pName)
	{
		m_pName = CCLabelTTF::create(pPlayerInfo->friendname().c_str(),"",25.f,m_pNameFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
		m_pName->setPosition(m_pNameFrame->getAnchorPointInPoints());
		m_pNameFrame->addChild(m_pName);
	}

	switch (pPlayerInfo->state())
	{
	case FriendInfoResponse_PlayerInfo_State_State_Online:
		{
			m_pState->setTexture(m_pState_0);
		}
		break;
	case FriendInfoResponse_PlayerInfo_State_State_Busy:
		{
			m_pState->setTexture(m_pState_1);
		}
		break;
	case FriendInfoResponse_PlayerInfo_State_State_Offline:
		{
			m_pState->setTexture(m_pState_2);
		}
		break;
	default:
		break;
	}

	switch (m_type)
	{
	case InfoType_Friend:
		{
			if (!m_pGameScore)
			{
				m_pGameScore = CCLabelTTF::create(CCString::createWithFormat("%d",pPlayerInfo->gamescore())->getCString(),HS_FONT_HuaKang,25.f,m_pMoneyFrame->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
				m_pGameScore->setPosition(m_pMoneyFrame->getAnchorPointInPoints());
				m_pMoneyFrame->addChild(m_pGameScore);
			}
		}
		break;
	case InfoType_Enemy:
		{
			if (!m_pMoney)
			{
				m_pMoney = CCLabelTTF::create(CCString::createWithFormat("%d",pPlayerInfo->money())->getCString(),HS_FONT_HuaKang,25.f,m_pGameScore->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
				m_pMoney->setPosition(m_pGameScore->getAnchorPointInPoints());
				m_pMoneyFrame->addChild(m_pGameScore);
			}
		}
		break;
	}

}

void HSFriendInfoSprite::Call( CCObject* pObj )
{

}
