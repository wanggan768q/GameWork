/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/02   17:55
 *	File base:	HSItemDataInterface.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSItemDataInterface_H__
#define __HSItemDataInterface_H__
#pragma once
#include "HSCellInterface.h"

HS_namespace_HSListViewControl_Begin

class HSItemDataInterface : public CCTableViewDataSource
{
public:
	HSItemDataInterface(const CCSize& itemSize,int onceCount);
	~HSItemDataInterface(void);

public:
	virtual CCNode* AddItem(int idx) = 0;

	virtual bool UpdataItem(CCNode* pItem,int idx) = 0;

	virtual CCSize cellSizeForTable( CCTableView *table );

	virtual CCTableViewCell* tableCellAtIndex( CCTableView *table, unsigned int idx );

	virtual unsigned int numberOfCellsInTableView( CCTableView *table );

private:
	CCSize m_itemSize;
	int m_itemCount;

};

HS_namespace_HSListViewControl_End

#endif // __HSItemDataInterface_H____
