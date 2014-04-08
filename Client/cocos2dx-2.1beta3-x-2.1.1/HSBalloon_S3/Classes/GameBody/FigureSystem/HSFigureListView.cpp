#include "HSFigureListView.h"
#include "HSGameCache.h"

HSFigureListView::HSFigureListView(const CCSize& frameSize,const CCSize& itemSize,int onceCount):HSListViewInterface(frameSize,itemSize,onceCount)
{
    
}


HSFigureListView::~HSFigureListView(void)
{
}

HSFigureListView* HSFigureListView::create(const CCSize& frameSize,const CCSize& itemSize,int onceCount )
{
	HSFigureListView* pListView = new HSFigureListView(frameSize,itemSize,onceCount);
	if (pListView && pListView->init())
	{
		pListView->autorelease();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

bool HSFigureListView::init()
{
	return true;
}

CCNode* HSFigureListView::AddItem(int idx)
{
    vector<FigureData_FigureBase*>* v = HS_GAME_CACHE()->GetFigureList();
    
	HSFigureSprite* pSprite = HSFigureSprite::create(idx);
	pSprite->UpdataHSFigureSprite(idx,(*v)[idx]);
    
	return pSprite;
}

bool HSFigureListView::UpdataItem( CCNode* pItem,int idx )
{
    vector<FigureData_FigureBase*>* v = HS_GAME_CACHE()->GetFigureList();
    
	HSFigureSprite* pSprite = dynamic_cast<HSFigureSprite*>(pItem);
    
	if(pSprite)
	{
		pSprite->UpdataHSFigureSprite(idx,(*v)[idx]);
	}
    
	return true;
}

void HSFigureListView::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	
}