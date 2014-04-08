/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/09/05   16:45
 *	File base:	HSPlayerInfoListView.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSPlayerInfoListView_H__
#define __HSPlayerInfoListView_H__
#pragma once
#include "HSTool.h"
class HSPlayerInfoListView : public HSListViewInterface
{
public:
	HSPlayerInfoListView(const CCSize& frameSize,const CCSize& itemSize,int onceCount);
	~HSPlayerInfoListView(void);

public:
	static HSPlayerInfoListView* create(const UserBasicInfo* user,const CCSize& frameSize,const CCSize& itemSize,int onceCount);

	virtual bool init(const UserBasicInfo* user);

	virtual CCNode* AddItem(int idx);

	virtual bool UpdataItem( CCNode* pItem,int idx );

	virtual void tableCellTouched( CCTableView* table, CCTableViewCell* cell );

private:
	const UserBasicInfo* m_pUser;
};
#endif // __HSPlayerInfoListView_H____


