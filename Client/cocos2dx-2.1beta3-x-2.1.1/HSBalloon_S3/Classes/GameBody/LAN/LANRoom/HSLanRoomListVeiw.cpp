#include "HSLanRoomListVeiw.h"


HSLanRoomListVeiw::HSLanRoomListVeiw(const CCSize& frameSize,const CCSize& itemSize,int onceCount):HSListViewInterface(frameSize,itemSize,onceCount)
{
	
}


HSLanRoomListVeiw::~HSLanRoomListVeiw(void)
{
}

HSLanRoomListVeiw* HSLanRoomListVeiw::create(const CCSize& frameSize,const CCSize& itemSize,int count )
{
	//HSAssert(pPlayerInfoList,"");
	HSLanRoomListVeiw* pListView = new HSLanRoomListVeiw(frameSize,itemSize,count);
	if ( pListView )
	{
		pListView->autorelease();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

CCNode* HSLanRoomListVeiw::AddItem(int idx)
{

    LanSearchRoomResponse_room* pRoomInfo = HS_GAME_CACHE()->m_LanRoomList.mutable_roomlist(idx);

	HSLanRoomSprite* pSprite = HSLanRoomSprite::create();
	pSprite->UpdataRoomInfo(idx,pRoomInfo);

	return pSprite;
}

bool HSLanRoomListVeiw::UpdataItem( CCNode* pItem,int idx)
{

    
    LanSearchRoomResponse_room* pRoomInfo = HS_GAME_CACHE()->m_LanRoomList.mutable_roomlist(idx);

	HSLanRoomSprite* pSprite = dynamic_cast<HSLanRoomSprite*>(pItem);
	pSprite->UpdataRoomInfo(idx,pRoomInfo);


	return true;
}

void HSLanRoomListVeiw::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	
}


