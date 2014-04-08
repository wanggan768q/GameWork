#include "HSRankListView.h"


HSRankListView::HSRankListView(void)
{
	m_pUserRankDataBult = NULL;
	m_pUserRankDataRed = NULL;
}


HSRankListView::~HSRankListView(void)
{
	CC_SAFE_DELETE(m_pUserRankDataBult);
	CC_SAFE_DELETE(m_pUserRankDataRed);
}

HSRankListView* HSRankListView::Create(const CCSize& size, const RankSpriteType& type ,CCNode* pNode,SearchRankResponse* pMsg)
{
	HSRankListView* rankListView = new HSRankListView;
	if (rankListView && rankListView->init(size,type,pNode,pMsg))
	{
		rankListView->autorelease();
		return rankListView;
	}
	CC_SAFE_DELETE(rankListView);
	return NULL;
}

bool HSRankListView::init( const CCSize& size, const RankSpriteType& type ,CCNode* pNode,SearchRankResponse* pMsg )
{
	m_pType = type;
	int count = 0;
	switch (type)
	{
	case RankSprite_Bule:
		{
			if (pMsg)
			{
				count = pMsg->usertopranks_size();
			}else{
				count = 200;
			}
			m_pUserRankDataBult = HSUserRankDataBule::New(CCSizeMake(605.8f,65.f),count,pNode);
			m_pUserRankDataBult->SetWorldRandData(pMsg);

			this->initWithViewSize(size);
			this->setDataSource(m_pUserRankDataBult);
			this->setDirection(kCCScrollViewDirectionVertical);
			this->setPosition(ccp(20.f,pNode->getContentSize().height));
			this->setDelegate(m_pUserRankDataBult);
			this->setVerticalFillOrder(kCCTableViewFillTopDown);

		}
		break;
	case RankSprite_Red:
		{
			if (pMsg)
			{
				count = pMsg->userselfranks_size();
			}else{
				count = 5;
			}
			m_pUserRankDataRed = HSUserRankDataRed::New(CCSizeMake(605.8f,65.f),count,pNode);
			m_pUserRankDataRed->SetSelfRankData(pMsg);

			this->initWithViewSize(size);
			this->setDataSource(m_pUserRankDataRed);
			this->setDirection(kCCScrollViewDirectionVertical);
			this->setPosition(ccp(20.f,0));
			this->setDelegate(m_pUserRankDataRed);
			this->setVerticalFillOrder(kCCTableViewFillTopDown);
		}
		break;
	}

	return true;
}

void HSRankListView::SetRankData( SearchRankResponse* pMsg )
{
	switch (m_pType)
	{
	case RankSprite_Bule:
		m_pUserRankDataBult->SetWorldRandData(pMsg);
		break;
	case RankSprite_Red:
		m_pUserRankDataRed->SetSelfRankData(pMsg);
		break;
	default:
		break;
	}
}
