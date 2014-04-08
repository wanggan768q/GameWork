#include "HSPlayerInfoListView.h"
#include "HSPlayerInfoSprite.h"

HSPlayerInfoListView::HSPlayerInfoListView(const CCSize& frameSize,const CCSize& itemSize,int onceCount):HSListViewInterface(frameSize,itemSize,onceCount)
{
	m_pUser = NULL;
}


HSPlayerInfoListView::~HSPlayerInfoListView(void)
{
}

HSPlayerInfoListView* HSPlayerInfoListView::create(const UserBasicInfo* user, const CCSize& frameSize,const CCSize& itemSize,int onceCount )
{
	HSPlayerInfoListView* pListView = new HSPlayerInfoListView(frameSize,itemSize,onceCount);
	if (pListView && pListView->init(user))
	{
		pListView->autorelease();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

bool HSPlayerInfoListView::init(const UserBasicInfo* user)
{
	this->m_pUser = user;
	return true;
}

CCNode* HSPlayerInfoListView::AddItem(int idx)
{
	HSPlayerInfoSprite* pSprite = HSPlayerInfoSprite::create(idx);
	pSprite->UpdataPlayerInfo(idx,m_pUser);

	return pSprite;
	return NULL;
}

bool HSPlayerInfoListView::UpdataItem( CCNode* pItem,int idx )
{
	HSPlayerInfoSprite* pSprite = dynamic_cast<HSPlayerInfoSprite*>(pItem);

	if(pSprite)
	{
		pSprite->UpdataPlayerInfo(idx,m_pUser);
	}

	return true;
}

void HSPlayerInfoListView::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	
}
