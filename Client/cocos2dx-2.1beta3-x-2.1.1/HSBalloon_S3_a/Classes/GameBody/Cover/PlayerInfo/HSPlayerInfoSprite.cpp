#include "HSPlayerInfoSprite.h"


HSPlayerInfoSprite::HSPlayerInfoSprite(void)
{
	m_pLeft = NULL;
	m_pRight = NULL;
	m_pdark = NULL;
	m_plight = NULL;
}


HSPlayerInfoSprite::~HSPlayerInfoSprite(void)
{
	m_pLeft = NULL;
	m_pRight = NULL;
	m_pdark = NULL;
	m_plight = NULL;
}

HSPlayerInfoSprite* HSPlayerInfoSprite::create(int index)
{
	HSPlayerInfoSprite* pSprite = new HSPlayerInfoSprite;
	if(pSprite && pSprite->Init(index))
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool HSPlayerInfoSprite::Init(int index)
{

	m_pdark = CCTextureCache::sharedTextureCache()->addImage("Image/main/playerInfo/Shentiao.png");
	m_plight = CCTextureCache::sharedTextureCache()->addImage("Image/main/playerInfo/Qiantiao.png");

	if(index%2==0)
	{
		this->initWithTexture(m_pdark);
	}
	else
	{
		this->initWithTexture(m_plight);
	}
	this->setAnchorPoint(HS_ANCHOR_L_CENTER);
	this->setPosition(ccp(0,this->getAnchorPointInPoints().y));


// 	if(index%2==0)
// 	{
		//this->initWithFile("Image/main/playerInfo/Shentiao.png");
// 	}
// 	else
// 	{
// 		this->initWithFile("Image/main/playerInfo/Qiantiao.png");
// 	}
// 
// 	this->setAnchorPoint(HS_ANCHOR_L_CENTER);
// 	this->setPosition(ccp(0,this->getAnchorPointInPoints().y));

	if(!m_pLeft)
	{
		m_pLeft = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,this->getContentSize(),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
		m_pLeft->setPosition(ccp(this->getContentSize().width/2+10,this->getContentSize().height/2));
		this->addChild(m_pLeft);
	}

	if(!m_pRight)
	{
		m_pRight = CCLabelTTF::create("",HS_FONT_HuaKang,25.f,this->getContentSize(),kCCTextAlignmentRight,kCCVerticalTextAlignmentCenter);
		m_pRight->setPosition(ccp(this->getContentSize().width/2-10,this->getContentSize().height/2));
		this->addChild(m_pRight);
	}
	return true;
}

void HSPlayerInfoSprite::UpdataPlayerInfo(int index,const message::UserBasicInfo* userInfo)
{
	

	if(index%2==0)
	{
		this->setTexture(m_pdark);
	}
	else
	{
		this->setTexture(m_plight);
	}
	this->setAnchorPoint(HS_ANCHOR_L_CENTER);
	this->setPosition(ccp(0,this->getAnchorPointInPoints().y));

	switch (index)
	{
	case 0:
		m_pLeft->setString(L("player_level"));

		m_pRight->setString(CCString::createWithFormat("%d",userInfo->level())->getCString());
		break;
	case 1:
		m_pLeft->setString(L("player_win"));
		m_pRight->setString(CCString::createWithFormat("%d",userInfo->wincount())->getCString());
		break;
	case 2:
		m_pLeft->setString(L("player_lose"));

		m_pRight->setString(CCString::createWithFormat("%d",userInfo->losecount())->getCString());
		break;
	case 3:
		m_pLeft->setString(L("player_winRate"));
		
		m_pRight->setString(CCString::createWithFormat("%d%%",(int)(userInfo->winrate() * 100.f))->getCString());
		break;
	case 4:
		m_pLeft->setString(L("player_longest"));

		m_pRight->setString(CCString::createWithFormat("%d",userInfo->oncelong())->getCString());
		break;
	case 5:
		m_pLeft->setString(L("player_total_remove"));

		m_pRight->setString(CCString::createWithFormat("%lld",userInfo->maximum())->getCString());

		break;
	case 6:
		m_pLeft->setString(L("player_total_time"));

		m_pRight->setString(CCString::createWithFormat("%lld",userInfo->totaltime())->getCString());
		break;
	case 7:
		m_pLeft->setString(L("player_total_rounds"));

		m_pRight->setString(CCString::createWithFormat("%d",userInfo->roundsplayed())->getCString());
		break;
	case 8:
		m_pLeft->setString(L("player_send_stone"));

		m_pRight->setString(CCString::createWithFormat("%d",userInfo->throwstones())->getCString());
		break;
	case 9:
		m_pLeft->setString(L("player_receive_stone"));

		m_pRight->setString(CCString::createWithFormat("%d",userInfo->thrownstones())->getCString());
		break;
	case 10:
		m_pLeft->setString(L("player_get_color"));

		m_pRight->setString(CCString::createWithFormat("%d",userInfo->colorcats())->getCString());
		break;
	case 11:
		m_pLeft->setString(L("player_consume_gold"));

		m_pRight->setString(CCString::createWithFormat("%d",userInfo->consumegolds())->getCString());
		break;
	case 12:
		m_pLeft->setString(L("player_consume_prop1"));

		m_pRight->setString(CCString::createWithFormat("%d",userInfo->consumeitems1())->getCString());
		break;
	case 13:
		m_pLeft->setString(L("player_consume_prop2"));

		m_pRight->setString(CCString::createWithFormat("%d",userInfo->consumeitems2())->getCString());
		break;
	case 14:
		m_pLeft->setString(L("player_consume_prop3"));

		m_pRight->setString(CCString::createWithFormat("%d",userInfo->consumeitems3())->getCString());
		break;
	case 15:
		m_pLeft->setString(L("player_consume_prop4"));

		m_pRight->setString(CCString::createWithFormat("%d",userInfo->consumeitems4())->getCString());
		break;
	default:
		break;
	}

}
