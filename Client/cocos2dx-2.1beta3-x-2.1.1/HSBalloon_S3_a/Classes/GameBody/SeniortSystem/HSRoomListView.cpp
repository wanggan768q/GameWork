#include "HSRoomListView.h"
#include "HSGamePairScene.h"

HSRoomListView::HSRoomListView(const CCSize& frameSize,const CCSize& itemSize,int onceCount):HSListViewInterface(frameSize,itemSize,onceCount)
{
}


HSRoomListView::~HSRoomListView(void)
{
}

HSRoomListView* HSRoomListView::create( const CCSize& frameSize,const CCSize& itemSize,int onceCount )
{
	HSRoomListView* pListView = new HSRoomListView(frameSize,itemSize,onceCount);
	if (pListView && pListView->init())
	{
		pListView->autorelease();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

bool HSRoomListView::init()
{
	return true;
}

CCNode* HSRoomListView::AddItem(int idx)
{
	RoomDataResponse_Room r = HS_GAME_CACHE()->m_RoomDataResponse.roomlist(idx);
	HSRoomSprite* s = HSRoomSprite::create();
	s->UpdataRoomInfo(r);
	return s;
}

bool HSRoomListView::UpdataItem( CCNode* pItem,int idx )
{
	HSRoomSprite* pSprite = dynamic_cast<HSRoomSprite*>(pItem);
	RoomDataResponse_Room r = HS_GAME_CACHE()->m_RoomDataResponse.roomlist(idx);
	pSprite->UpdataRoomInfo(r);
	return true;
}

void HSRoomListView::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	RoomDataResponse* pRoomDataResponse = &HS_GAME_CACHE()->m_RoomDataResponse;
	if (pRoomDataResponse->roomlist_size() <= (int)cell->getIdx())
	{
		return;
	}
	RoomDataResponse_Room pRoomInfo = pRoomDataResponse->roomlist(cell->getIdx());

	if (pRoomInfo.sweepstakegold() > HS_GAME_CACHE()->GetGold())
	{
		//Show Diaog
		HSGoldInadequateDialog* pDialog = HSGoldInadequateDialog::create();
		this->getParent()->addChild(pDialog);

	}else{
		HSRequest::ShareRequest()->SendTargetInfoRequest(pRoomInfo.id());
		HSGamePairLayer::s_CURRENT_ROOM_ID = pRoomInfo.id();
		HSLoadingLayer::ShareLoading()->setVisible(true);
	}
}