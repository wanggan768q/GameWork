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
	s->UpdataRoomInfo(idx,r);
	return s;
}

bool HSRoomListView::UpdataItem( CCNode* pItem,int idx )
{
	HSRoomSprite* pSprite = dynamic_cast<HSRoomSprite*>(pItem);
	RoomDataResponse_Room r = HS_GAME_CACHE()->m_RoomDataResponse.roomlist(idx);
	pSprite->UpdataRoomInfo(idx,r);
	return true;
}

void HSRoomListView::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{

//	RoomDataResponse* pRoomDataResponse = &HS_GAME_CACHE()->m_RoomDataResponse;
//
//	int idx = cell->getIdx();
//
//	CCLOG("tableCellTouched: %d",idx);
//
//	if (pRoomDataResponse->roomlist_size() <= (int)cell->getIdx())
//	{
//		return;
//	}
//
//	RoomDataResponse_Room pRoomInfo = pRoomDataResponse->roomlist(cell->getIdx());
//
//	//CCLog("cell idx ==============>%d,roomId(%d),gold(%d),gold2(%d)",idx,pRoomInfo.id(),pRoomInfo.sweepstakegold(),pRoomInfo.stakegold());
//
//	if (pRoomInfo.sweepstakegold() > HS_GAME_CACHE()->GetGold())
//	{
//		HSGoldInadequateDialog* pDialog = HSGoldInadequateDialog::create();
//		pDialog->Set_BugGold(HS_GAME_CACHE()->GetReasonableChargeId(pRoomInfo.sweepstakegold()-HS_GAME_CACHE()->GetGold()));
//		this->getParent()->addChild(pDialog);
//	}
//	else
//	{
//		HS_GAME_CACHE()->roomGold = pRoomInfo.stakegold();
//		HS_GAME_CACHE()->m_roomId = pRoomInfo.id();
//		HSRequest::ShareRequest()->SendTargetInfoRequest(pRoomInfo.id());
//
//		HSGamePairLayer::s_CURRENT_ROOM_ID = pRoomInfo.id();
//		HSLoadingLayer::ShareLoading()->setVisible(true);
//	}
}
