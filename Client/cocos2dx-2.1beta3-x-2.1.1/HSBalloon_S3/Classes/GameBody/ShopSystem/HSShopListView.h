/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/09/12   10:27
 *	File base:	HSShopListView.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSShopListView_H__
#define __HSShopListView_H__
#pragma once
#include "HSTool.h"
class HSShopListView : public HSListViewInterface
{
public:
	HSShopListView(const CCSize& frameSize,const CCSize& itemSize,int onceCount);
	~HSShopListView(void);
public:
	static HSShopListView* create(const CCSize& frameSize,const CCSize& itemSize,int onceCount);

	virtual bool init();

	virtual CCNode* AddItem(int idx);

	virtual bool UpdataItem(CCNode* pItem,int idx );

	virtual void tableCellTouched( CCTableView* table, CCTableViewCell* cell );

	//virtual void registerWithTouchDispatcher();

};
#endif // __HSShopListView_H____


