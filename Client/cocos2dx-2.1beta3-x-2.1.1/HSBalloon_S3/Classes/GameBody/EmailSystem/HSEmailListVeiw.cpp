#include "HSEmailListVeiw.h"


HSEmailListVeiw::HSEmailListVeiw(const CCSize& frameSize,const CCSize& itemSize,int onceCount):HSListViewInterface(frameSize,itemSize,onceCount)
{
	
}


HSEmailListVeiw::~HSEmailListVeiw(void)
{
}

HSEmailListVeiw* HSEmailListVeiw::create(const CCSize& frameSize,const CCSize& itemSize,int count )
{
	//HSAssert(pPlayerInfoList,"");
	HSEmailListVeiw* pListView = new HSEmailListVeiw(frameSize,itemSize,count);
	if ( pListView )
	{
		pListView->autorelease();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

CCNode* HSEmailListVeiw::AddItem(int idx)
{
    EmailResponse_EmailInfo* pEmailInfo = HS_GAME_CACHE()->m_EmailResponse.mutable_emaillist(idx);

	HSEmailSprite* pSprite = HSEmailSprite::create();
	pSprite->UpdataInfo(pEmailInfo);

	return pSprite;
}

bool HSEmailListVeiw::UpdataItem( CCNode* pItem,int idx)
{
    EmailResponse_EmailInfo* pInfo = HS_GAME_CACHE()->m_EmailResponse.mutable_emaillist(idx);

	HSEmailSprite* pSprite = dynamic_cast<HSEmailSprite*>(pItem);
	pSprite->UpdataInfo(pInfo);
    
	return true;
}

void HSEmailListVeiw::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	
}


