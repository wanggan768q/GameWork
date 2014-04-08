#include "HSAchievemenLsitView.h"


HSAchievemenListView::HSAchievemenListView(const CCSize& frameSize,const CCSize& itemSize,int onceCount):HSListViewInterface(frameSize,itemSize,onceCount)
{
}


HSAchievemenListView::~HSAchievemenListView(void)
{
}

HSAchievemenListView* HSAchievemenListView::create( AchievementResponse* pAchievementResponse,const CCSize& frameSize,const CCSize& itemSize,int onceCount )
{
	HSAchievemenListView* pListView = new HSAchievemenListView(frameSize,itemSize,onceCount);
	if (pListView && pListView->init(pAchievementResponse))
	{
		pListView->autorelease();
		return pListView;
	}
	CC_SAFE_DELETE(pListView);
	return NULL;
}

bool HSAchievemenListView::init(AchievementResponse* pAchievementResponse)
{
	m_pAchievementResponse = pAchievementResponse;
	return true;
}

CCNode* HSAchievemenListView::AddItem(int idx)
{
	HSAchievemenSrpite* pSprite = HSAchievemenSrpite::create();
	message::AchievementResponse_AchievemenStateInfo* info = HS_GAME_CACHE()->m_AchievementResponse.mutable_achievementlist(idx);
	pSprite->UpdataAchievemen(info);
	return pSprite;
}

bool HSAchievemenListView::UpdataItem( CCNode* pItem,int idx )
{
	HSAchievemenSrpite* pSprite = dynamic_cast<HSAchievemenSrpite*>(pItem);
	message::AchievementResponse_AchievemenStateInfo* info = HS_GAME_CACHE()->m_AchievementResponse.mutable_achievementlist(idx);
	pSprite->UpdataAchievemen(info);
	return true;
}

void HSAchievemenListView::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	
}