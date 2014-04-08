#include "HSUserRankDataBule.h"


HSUserRankDataBule::HSUserRankDataBule(void)
{
}


HSUserRankDataBule::~HSUserRankDataBule(void)
{
	CC_SAFE_DELETE(m_pRankData);
}

HSUserRankDataBule* HSUserRankDataBule::New(const CCSize& cellSize,int count,CCNode* pNode)
{
	HSUserRankDataBule* bule = new HSUserRankDataBule;
	if (bule && bule->init(cellSize,count,pNode))
	{
		return bule;
	}
	CC_SAFE_DELETE(bule);
	return NULL;
}

bool HSUserRankDataBule::init( const CCSize& cellSize,int count ,CCNode* pNode)
{
	m_cellSize = cellSize;
	m_cellCount = count;
	
	m_pRankData = SearchRankResponse::default_instance().New();

	return true;
}

cocos2d::CCSize HSUserRankDataBule::cellSizeForTable( CCTableView *table )
{
	return m_cellSize;
}

CCTableViewCell* HSUserRankDataBule::tableCellAtIndex( CCTableView *table, unsigned int idx )
{

	const SearchRankResponse_UserRank* pUserRankData = NULL;
	if (m_pRankData)
	{
		int dataCount = this->m_pRankData->usertopranks_size();
		if ((int)idx < dataCount)
		{
			pUserRankData = &this->m_pRankData->usertopranks(idx);
		}
	}

	 CCString *string = CCString::createWithFormat("%d", idx);
	 CCTableViewCell *cell = table->dequeueCell();
	 if (!cell) 
	 {
		 cell = new HSRankCell();
		 cell->autorelease();

		 HSUserRankSprite* sprite = HSUserRankSprite::Create(RankSprite_Bule,pUserRankData);
		 //sprite->setAnchorPoint(CCPointZero);
		 CCPoint pos = sprite->getPosition();
		 pos.y += sprite->getContentSize().height;
		 sprite->setPosition(pos);
		 sprite->setTag(1000);
		 cell->addChild(sprite);

// 		 CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
// 		 label->setPosition(CCPointZero);
// 		 label->setAnchorPoint(CCPointZero);
// 		 label->setTag(1001);
// 		 cell->addChild(label);
	 }
	 else
	 {
		 //CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(1001);
		 //label->setString(string->getCString());

		 HSUserRankSprite *sprite = (HSUserRankSprite*)cell->getChildByTag(1000);
		 sprite->SetUserRank(pUserRankData);
	 }

	 //CCLog("Bule   %s",string->getCString());
	 return cell;
}

unsigned int HSUserRankDataBule::numberOfCellsInTableView( CCTableView *table )
{
	return m_cellCount;
}

void HSUserRankDataBule::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	CCLOG("Bule cell touched at index: %i", cell->getIdx());
}

void HSUserRankDataBule::scrollViewDidScroll( CCScrollView* view )
{
	
}

void HSUserRankDataBule::scrollViewDidZoom( CCScrollView* view )
{
	
}

void HSUserRankDataBule::SetWorldRandData( SearchRankResponse* pMsg )
{
	m_pRankData->Clear();
	m_pRankData->CopyFrom(*pMsg);
}
