#include "HSUserRankDataRed.h"


HSUserRankDataRed::HSUserRankDataRed(void)
{
}


HSUserRankDataRed::~HSUserRankDataRed(void)
{
}

HSUserRankDataRed* HSUserRankDataRed::New( const CCSize& cellSize,int count,CCNode* pNode )
{
	HSUserRankDataRed* red = new HSUserRankDataRed;
	if (red && red->init(cellSize,count,pNode))
	{
		return red;
	}
	CC_SAFE_DELETE(red);
	return NULL;
}

bool HSUserRankDataRed::init( const CCSize& cellSize,int count,CCNode* pNode )
{
	m_cellSize = cellSize;
	m_cellCount = count;

	m_pRankData = SearchRankResponse::default_instance().New();


	return true;
}

cocos2d::CCSize HSUserRankDataRed::cellSizeForTable( CCTableView *table )
{
	return m_cellSize;
}

CCTableViewCell* HSUserRankDataRed::tableCellAtIndex( CCTableView *table, unsigned int idx )
{
	const SearchRankResponse_UserRank* pUserRankData = NULL;
	if (m_pRankData)
	{
		if ((int)idx < this->m_pRankData->userselfranks_size())
		{
			pUserRankData = &this->m_pRankData->userselfranks(idx);
		}
	}


	CCString *string = CCString::createWithFormat("%d", idx);
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new HSRankCell();
		cell->autorelease();

		HSUserRankSprite* sprite = HSUserRankSprite::Create(RankSprite_Red,pUserRankData);
		CCPoint pos = sprite->getPosition();
		pos.y += sprite->getContentSize().height;
		sprite->setPosition(pos);
		sprite->setTag(1000);
		cell->addChild(sprite);

// 		CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
// 		label->setPosition(CCPointZero);
// 		label->setAnchorPoint(CCPointZero);
// 		label->setTag(1001);
// 		cell->addChild(label);
	}
	else
	{
		//CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(1001);
		//label->setString(string->getCString());

		HSUserRankSprite *sprite = (HSUserRankSprite*)cell->getChildByTag(1000);
		sprite->SetUserRank(pUserRankData);
	}
	return cell;
}

unsigned int HSUserRankDataRed::numberOfCellsInTableView( CCTableView *table )
{
	return m_cellCount;
}

void HSUserRankDataRed::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	CCLOG("Red cell touched at index: %i", cell->getIdx());
}

void HSUserRankDataRed::scrollViewDidScroll( CCScrollView* view )
{
	
}

void HSUserRankDataRed::scrollViewDidZoom( CCScrollView* view )
{
	
}

void HSUserRankDataRed::SetSelfRankData( SearchRankResponse* pMsg )
{
	m_pRankData->Clear();
	m_pRankData->CopyFrom(*pMsg);
}

