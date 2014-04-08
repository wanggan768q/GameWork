#include "HSShopListView.h"
#include "HSShopSprite.h"

HSShopListView::HSShopListView(const CCSize& frameSize,const CCSize& itemSize,int onceCount):HSListViewInterface(frameSize,itemSize,onceCount)
{
	
}


HSShopListView::~HSShopListView(void)
{
}

HSShopListView* HSShopListView::create( const CCSize& frameSize,const CCSize& itemSize,int onceCount )
{
	HSShopListView* pListView = new HSShopListView(frameSize,itemSize,onceCount);
	if (pListView && pListView->init())
	{
		pListView->autorelease();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

bool HSShopListView::init()
{

	return true;
}

CCNode* HSShopListView::AddItem(int idx)
{
	HSShopSprite* sprite = HSShopSprite::create(this->cellSizeForTable(NULL),HS_GAME_CACHE()->GetPropInfoData()->buygoldlist(idx));
	
	sprite->UpdateShopInfo(HS_GAME_CACHE()->GetPropInfoData()->buygoldlist(idx));

	return sprite;
}

bool HSShopListView::UpdataItem( CCNode* pItem,int idx )
{
	HSShopSprite* sprite = dynamic_cast<HSShopSprite*>(pItem);

	if(sprite)
	{
		sprite->UpdateShopInfo(HS_GAME_CACHE()->GetPropInfoData()->buygoldlist(idx));
	}
	return true;
}

void HSShopListView::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	
}

// void HSShopListView::registerWithTouchDispatcher()
// {
// // 	CCDirector* pDirector = CCDirector::sharedDirector();
// // 	pDirector->getTouchDispatcher()->addTargetedDelegate(this, -130 , true);
// }
