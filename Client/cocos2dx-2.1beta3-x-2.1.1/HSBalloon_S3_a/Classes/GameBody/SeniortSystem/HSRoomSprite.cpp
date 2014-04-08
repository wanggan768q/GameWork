#include "HSRoomSprite.h"


HSRoomSprite::HSRoomSprite(void)
{
	m_pPlayerCountTTF = NULL;
	m_pStakeCountTTF = NULL;
}


HSRoomSprite::~HSRoomSprite(void)
{
}

bool HSRoomSprite::init()
{
	if (m_TextureMap.empty())
	{
		for (int i=1;i<6;++i)
		{
			CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("Image/SelectChannel/pindao_%d.png",i)->getCString());
			m_TextureMap.insert(pair<int,CCTexture2D*>(i,pTexture));
		}
	}
	this->initWithFile("Image/SelectChannel/xuanzepindao.png");
	this->setAnchorPoint(HS_ANCHOR_LD);

	m_pRoomName = CCSprite::create("Image/SelectChannel/pindao_1.png");
	m_pRoomName->setPosition(ccp(272,123));
	this->addChild(m_pRoomName);

	m_pPlayerCountFrame = CCSprite::create("Image/SelectChannel/Shuzidiandikuang.png");
	m_pPlayerCountFrame->setPosition(ccp(215,55));
	this->addChild(m_pPlayerCountFrame);

	m_pStakeGoldFrame = CCSprite::create("Image/SelectChannel/Shuzidiandikuang.png");
	m_pStakeGoldFrame->setPosition(ccp(443,55));
	this->addChild(m_pStakeGoldFrame);

	return true;
}

void HSRoomSprite::UpdataRoomInfo( const RoomDataResponse_Room& room )
{
	std::map<int,CCTexture2D*>::iterator it = m_TextureMap.find(room.id());
	if (it == m_TextureMap.end())
	{
		return;
	}
	m_pRoomName->setTexture(it->second);

	if (!m_pPlayerCountTTF)
	{
		m_pPlayerCountTTF = CCLabelTTF::create(CCString::createWithFormat("%d",room.playercount())->getCString(),HS_FONT_HuaKang,25.f);
		m_pPlayerCountTTF->setAnchorPoint(HS_ANCHOR_L_CENTER);
		m_pPlayerCountTTF->setPosition(ccp(0,m_pPlayerCountTTF->getContentSize().height));
		m_pPlayerCountFrame->addChild(m_pPlayerCountTTF);
	}else{
		m_pPlayerCountTTF->setString(CCString::createWithFormat("%d",room.playercount())->getCString());
	}

	if (!m_pStakeCountTTF)
	{
		m_pStakeCountTTF = CCLabelTTF::create(CCString::createWithFormat("%d",room.stakegold())->getCString(),HS_FONT_HuaKang,25.f);
		m_pStakeCountTTF->setAnchorPoint(HS_ANCHOR_L_CENTER);
		m_pStakeCountTTF->setPosition(ccp(0,m_pStakeCountTTF->getContentSize().height));
		m_pStakeGoldFrame->addChild(m_pStakeCountTTF);
	}else{
		m_pStakeCountTTF->setString(CCString::createWithFormat("%d",room.stakegold())->getCString());
	}
}
