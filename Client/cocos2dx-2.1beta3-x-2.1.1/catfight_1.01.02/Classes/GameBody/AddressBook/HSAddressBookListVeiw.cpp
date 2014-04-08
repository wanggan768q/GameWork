#include "HSAddressBookListVeiw.h"


HSAddressBookListVeiw::HSAddressBookListVeiw(const CCSize& frameSize,const CCSize& itemSize,int onceCount):HSListViewInterface(frameSize,itemSize,onceCount)
{
	
}


HSAddressBookListVeiw::~HSAddressBookListVeiw(void)
{
}

HSAddressBookListVeiw* HSAddressBookListVeiw::create(const CCSize& frameSize,const CCSize& itemSize,int count )
{
	//HSAssert(pPlayerInfoList,"");
	HSAddressBookListVeiw* pListView = new HSAddressBookListVeiw(frameSize,itemSize,count);
	if ( pListView )
	{
		pListView->autorelease();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

CCNode* HSAddressBookListVeiw::AddItem(int idx)
{
    AddressBookResponse_Name* pName = HS_GAME_CACHE()->m_AddressBookResponse.mutable_namelist(idx);

	HSAddressSprite* pSprite = HSAddressSprite::create();
	pSprite->UpdataInfo(pName);

	return pSprite;
}

bool HSAddressBookListVeiw::UpdataItem( CCNode* pItem,int idx)
{
    AddressBookResponse_Name* pName = HS_GAME_CACHE()->m_AddressBookResponse.mutable_namelist(idx);

	HSAddressSprite* pSprite = dynamic_cast<HSAddressSprite*>(pItem);
	pSprite->UpdataInfo(pName);
    
	return true;
}

void HSAddressBookListVeiw::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	
}


