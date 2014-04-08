#include "HSUserRankSprite.h"


HSUserRankSprite::HSUserRankSprite(void)
{
	m_fontName = "华康海报体W12(P)";

	m_pNameTTF = NULL;
	m_pRankIndexTTF = NULL;
	m_pRankChangeTTF = NULL;
	m_pRankUpOrDownSprite = NULL;
	m_pScoreTTF = NULL;

}	


HSUserRankSprite::~HSUserRankSprite(void)
{
}

HSUserRankSprite* HSUserRankSprite::Create( const RankSpriteType& type,const SearchRankResponse_UserRank* pUserRank )
{
	HSUserRankSprite* s = new HSUserRankSprite;
	if (s && s->init(type,pUserRank))
	{
		s->autorelease();
		return s;
	}
	CC_SAFE_DELETE(s);
	return NULL;
}

bool HSUserRankSprite::init( const RankSpriteType& type,const SearchRankResponse_UserRank* pUserRank )
{
	string fileName = "";
	switch (type)
	{
	case RankSprite_Bule:
		{
			fileName = "RankInfoBule";
		}
		break;
	case RankSprite_Red:
		{
			fileName = "RankInfoRed";
		}
		break;
	}

	this->m_pRankIndexFrame = HSCCSprite::create(CCString::createWithFormat("Image/RankingList/%s/s_Tiao1.png",fileName.c_str())->getCString());
	this->m_pRankUpOrDownFrame = HSCCSprite::create(CCString::createWithFormat("Image/RankingList/%s/s_Tiao2_1.png",fileName.c_str())->getCString());
	this->m_pRankChangeFrame = HSCCSprite::create(CCString::createWithFormat("Image/RankingList/%s/s_Tiao2_2.png",fileName.c_str())->getCString());
	this->m_pNameFrame = HSCCSprite::create(CCString::createWithFormat("Image/RankingList/%s/s_Tiao3_1.png",fileName.c_str())->getCString());
	this->m_pScoreFrame = HSCCSprite::create(CCString::createWithFormat("Image/RankingList/%s/s_Tiao3_2.png",fileName.c_str())->getCString());

	this->m_pRankIndexFrame->setPosition(ccp(53.f,32.f));
	this->m_pRankUpOrDownFrame->setPosition(ccp(174.f,48.f));
	this->m_pRankChangeFrame->setPosition(ccp(174.f,16.f));
	this->m_pNameFrame->setPosition(ccp(424.f,48.f));
	this->m_pScoreFrame->setPosition(ccp(424.f,16.f));

	this->addChild(this->m_pRankIndexFrame);
	this->addChild(this->m_pRankUpOrDownFrame);
	this->addChild(this->m_pRankChangeFrame);
	this->addChild(this->m_pNameFrame);
	this->addChild(this->m_pScoreFrame);

	m_pUpTexture = CCTextureCache::sharedTextureCache()->addImage("Image/RankingList/RankInfoBule/s_ShangSheng.png");
	m_pDownTexture = CCTextureCache::sharedTextureCache()->addImage("Image/RankingList/RankInfoBule/s_XiaJiang.png");

	if (pUserRank)
	{
		SetUserRank(pUserRank);
	}
	return true;
}

void HSUserRankSprite::SetUserRank( const SearchRankResponse_UserRank* pUserRank )
{
	if (!pUserRank)
	{
		if (m_pNameTTF)
		{
			m_pNameTTF->setVisible(false);
			m_pRankIndexTTF->setVisible(false);
			m_pRankChangeTTF->setVisible(false);
			m_pRankUpOrDownSprite->setVisible(false);
			m_pScoreTTF->setVisible(false);
		}
		return;
	}
// 	pUserRank = message::SearchRankResponse_UserRank::default_instance().New();
// 	pUserRank->set_username("GXB");
// 	pUserRank->set_rank(1025);
// 	pUserRank->set_rankchange(HSMath::Random(-10,10));
// 	pUserRank->set_score(985232);

	if (!m_pNameTTF)
	{
		m_pNameTTF = CCLabelTTF::create("",m_fontName,30.f);

		m_pRankIndexTTF = CCLabelTTF::create("",m_fontName,30.f);

		m_pRankChangeTTF = CCLabelTTF::create("",m_fontName,30.f);

		m_pRankUpOrDownSprite = HSCCSprite::create(m_pUpTexture);
		
		//m_pRankUpOrDownSprite->setVisible(false);

		m_pScoreTTF = CCLabelTTF::create("",m_fontName,30.f);

		m_pNameTTF->setPosition(HS_SizeHalf_Point(m_pNameFrame->getContentSize()));
		m_pRankIndexTTF->setPosition(HS_SizeHalf_Point(m_pRankIndexFrame->getContentSize()));
		m_pRankChangeTTF->setPosition(HS_SizeHalf_Point(m_pRankChangeFrame->getContentSize()));
		m_pRankUpOrDownSprite->setPosition(HS_SizeHalf_Point(m_pRankUpOrDownFrame->getContentSize()));
		m_pScoreTTF->setPosition(HS_SizeHalf_Point(m_pScoreFrame->getContentSize()));

		m_pNameTTF->setColor(ccc3(0,0,0));
		m_pScoreTTF->setColor(ccc3(0,0,0));

		this->m_pNameFrame->addChild(m_pNameTTF);
		this->m_pRankIndexFrame->addChild(m_pRankIndexTTF);
		this->m_pRankChangeFrame->addChild(m_pRankChangeTTF);
		this->m_pRankUpOrDownFrame->addChild(m_pRankUpOrDownSprite);
		this->m_pScoreFrame->addChild(m_pScoreTTF);
		
	}

	m_pRankIndexTTF->setString(CCString::createWithFormat("%d",pUserRank->rank())->getCString());

	if (pUserRank->rankchange() < 0)
	{
		m_pRankUpOrDownSprite->setTexture(m_pDownTexture);
	}else{
		m_pRankUpOrDownSprite->setTexture(m_pUpTexture);
	}
	
	m_pRankChangeTTF->setString(CCString::createWithFormat("%d",pUserRank->rankchange())->getCString());

	m_pNameTTF->setString(pUserRank->username().c_str());

	m_pScoreTTF->setString(CCString::createWithFormat("%d",pUserRank->score())->getCString());


	m_pNameTTF->setVisible(true);
	m_pRankIndexTTF->setVisible(true);
	m_pRankChangeTTF->setVisible(true);
	m_pRankUpOrDownSprite->setVisible(true);
	m_pScoreTTF->setVisible(true);
}
