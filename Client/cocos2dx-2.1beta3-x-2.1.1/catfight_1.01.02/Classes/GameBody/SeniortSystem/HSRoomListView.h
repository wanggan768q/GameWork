/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/23   15:51
 *	File base:	HSRoomListView.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSRoomListView_H__
#define __HSRoomListView_H__
#pragma once
#include "HSRoomSprite.h"

class HSRoomListView : public HSListViewInterface
{
public:
	HSRoomListView(const CCSize& frameSize,const CCSize& itemSize,int onceCount);
	~HSRoomListView(void);

public:
	static HSRoomListView* create(const CCSize& frameSize,const CCSize& itemSize,int onceCount);

	virtual bool init();

	virtual CCNode* AddItem(int idx);

	virtual bool UpdataItem( CCNode* pItem,int idx );

	virtual void tableCellTouched( CCTableView* table, CCTableViewCell* cell );
};

#endif // __HSRoomListView_H____