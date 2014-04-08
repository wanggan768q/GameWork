#include "HSFriendsListVeiw.h"
#include "HSGameSceneJumpManage.h"

HSFriendsListVeiw::HSFriendsListVeiw(const CCSize& frameSize,const CCSize& itemSize,int onceCount):HSListViewInterface(frameSize,itemSize,onceCount)
{
	
}


HSFriendsListVeiw::~HSFriendsListVeiw(void)
{
}

HSFriendsListVeiw* HSFriendsListVeiw::create(const CCSize& frameSize,const CCSize& itemSize,int count )
{
	//HSAssert(pPlayerInfoList,"");
	HSFriendsListVeiw* pListView = new HSFriendsListVeiw(frameSize,itemSize,count);
	if ( pListView )
	{
		pListView->autorelease();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

CCNode* HSFriendsListVeiw::AddItem(int idx)
{
// 	int dataCount = this->m_pPlayerInfoList->list_size();
// 	HSAssert(idx < dataCount,"");

//	FriendListResponse_PlayerInfo* pPlayerInfo =  FriendListResponse_PlayerInfo::default_instance().New();
//	pPlayerInfo->set_friendname("12345");
//	pPlayerInfo->set_friendname("name");
//	pPlayerInfo->set_gamescore(3123);
//	pPlayerInfo->set_headicon(6000);
    
    HSFriendInfoSprite* pSprite = NULL;
    
    if(idx >= HS_GAME_CACHE()->m_FriendListResponse.friendlist_size())
    {
        pSprite = HSFriendInfoSprite::createWithDefault();
    }else{
        FriendListResponse_PlayerInfo* pPlayerInfo = HS_GAME_CACHE()->m_FriendListResponse.mutable_friendlist(idx);
        pSprite = HSFriendInfoSprite::create();
        pSprite->UpdataPlayerInfo(idx,pPlayerInfo);
    }
    
	//CC_SAFE_DELETE(pPlayerInfo);

	return pSprite;
}

bool HSFriendsListVeiw::UpdataItem( CCNode* pItem,int idx)
{
//	FriendListResponse_PlayerInfo* pPlayerInfo =  FriendListResponse_PlayerInfo::default_instance().New();
//	pPlayerInfo->set_friendname("12345");
//	pPlayerInfo->set_friendname("name");
//	pPlayerInfo->set_gamescore(3123);
//	pPlayerInfo->set_headicon(6000);
    
    HSFriendInfoSprite* pSprite = NULL;
    
    if(idx >= HS_GAME_CACHE()->m_FriendListResponse.friendlist_size())
    {
        pSprite = HSFriendInfoSprite::createWithDefault();
    }else{
        FriendListResponse_PlayerInfo* pPlayerInfo = HS_GAME_CACHE()->m_FriendListResponse.mutable_friendlist(idx);
        pSprite = HSFriendInfoSprite::create();
        pSprite->UpdataPlayerInfo(idx,pPlayerInfo);
    }

	return true;
}

void HSFriendsListVeiw::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
//	if(cell->getIdx() == HS_GAME_CACHE()->m_FriendListResponse.friendlist_size())
//    {
//        HS_GO_SCENE(HS_SCENE_AddressBookScene);
//    }
}


