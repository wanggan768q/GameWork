/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/05   17:16
 *	File base:	HSAchievemenLsitView.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSAchievemenLsitView_H__
#define __HSAchievemenLsitView_H__
#pragma once
#include "HSAchievemenSrpite.h"

class HSAchievemenListView : public HSListViewInterface
{
public:
	HSAchievemenListView(const CCSize& frameSize,const CCSize& itemSize,int onceCount);
	~HSAchievemenListView(void);

public:
	static HSAchievemenListView* create(AchievementResponse* pAchievementResponse,const CCSize& frameSize,const CCSize& itemSize,int onceCount);

	virtual bool init(AchievementResponse* pAchievementResponse);

	virtual CCNode* AddItem(int idx);

	virtual bool UpdataItem( CCNode* pItem,int idx );

	virtual void tableCellTouched( CCTableView* table, CCTableViewCell* cell );

private:
	AchievementResponse* m_pAchievementResponse;
};
#endif // __HSAchievemenLsitView_H____
