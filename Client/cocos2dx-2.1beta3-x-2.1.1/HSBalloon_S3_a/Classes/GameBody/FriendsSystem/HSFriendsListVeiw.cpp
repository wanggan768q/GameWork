#include "HSFriendsListVeiw.h"


HSFriendsListVeiw::HSFriendsListVeiw(const CCSize& frameSize,const CCSize& itemSize,int onceCount):HSListViewInterface(frameSize,itemSize,onceCount)
{
	m_pPlayerInfoList = NULL;
}


HSFriendsListVeiw::~HSFriendsListVeiw(void)
{
}

HSFriendsListVeiw* HSFriendsListVeiw::create( const FriendInfoResponse_PlayerInfoList* pPlayerInfoList,const CCSize& frameSize,const CCSize& itemSize )
{
	//HSAssert(pPlayerInfoList,"");
	HSFriendsListVeiw* pListView = new HSFriendsListVeiw(frameSize,itemSize,pPlayerInfoList->maxcount());
	if (pListView && pListView->init(pPlayerInfoList))
	{
		pListView->autorelease();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

bool HSFriendsListVeiw::init( const FriendInfoResponse_PlayerInfoList* pPlayerInfoList )
{
	m_pPlayerInfoList = pPlayerInfoList;
	return true;
}

CCNode* HSFriendsListVeiw::AddItem(int idx)
{
// 	int dataCount = this->m_pPlayerInfoList->list_size();
// 	HSAssert(idx < dataCount,"");

	FriendInfoResponse_PlayerInfo* pPlayerInfo =  FriendInfoResponse_PlayerInfo::default_instance().New();
	pPlayerInfo->set_frienduuid("12345");
	pPlayerInfo->set_friendname("name");
	pPlayerInfo->set_gamescore(3123);
	pPlayerInfo->set_headicon("test.png");
	pPlayerInfo->set_state(FriendInfoResponse_PlayerInfo_State_State_Busy);

	HSFriendInfoSprite* pSprite = HSFriendInfoSprite::create(InfoType_Friend);
	pSprite->UpdataPlayerInfo(idx,pPlayerInfo);
	
	CC_SAFE_DELETE(pPlayerInfo);

	return pSprite;
}

bool HSFriendsListVeiw::UpdataItem( CCNode* pItem,int idx)
{
	FriendInfoResponse_PlayerInfo* pPlayerInfo =  FriendInfoResponse_PlayerInfo::default_instance().New();
	pPlayerInfo->set_frienduuid("12345");
	pPlayerInfo->set_friendname("name");
	pPlayerInfo->set_gamescore(3123);
	pPlayerInfo->set_headicon("test.png");
	pPlayerInfo->set_state(FriendInfoResponse_PlayerInfo_State_State_Busy);

	HSFriendInfoSprite* pSprite = dynamic_cast<HSFriendInfoSprite*>(pItem);
	pSprite->UpdataPlayerInfo(idx,pPlayerInfo);
	CC_SAFE_DELETE(pPlayerInfo);
	
	CCLog("Updata  %d",idx);
	return true;
}

void HSFriendsListVeiw::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	
}


