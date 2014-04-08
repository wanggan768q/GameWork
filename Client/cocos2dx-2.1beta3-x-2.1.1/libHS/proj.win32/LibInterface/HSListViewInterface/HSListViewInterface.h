/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/02   17:55
 *	File base:	HSListViewInterface.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSListViewInterface_H__
#define __HSListViewInterface_H__
#pragma once
#include "HSItemDataInterface.h"
#include "HSTouchItemInterface.h"

HS_namespace_HSListViewControl_Begin

class HSListViewInterface : public CCTableView , public HSItemDataInterface,public HSTouchItemInterface
{
public:
	HSListViewInterface(const CCSize& frameSize,const CCSize& itemSize,int onceCount);
	~HSListViewInterface(void);

public:

	virtual CCNode* AddItem(int idx) = 0;

	virtual bool UpdataItem( CCNode* pItem,int idx ) = 0;

	virtual void tableCellTouched( CCTableView* table, CCTableViewCell* cell ) = 0;

	virtual void registerWithTouchDispatcher();

};

HS_namespace_HSListViewControl_End

#endif // __HSListViewInterface_H____



