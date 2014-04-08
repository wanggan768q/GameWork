/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/03   10:01
 *	File base:	HSEmailListVeiw.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSEmailListVeiw_H__
#define __HSEmailListVeiw_H__
#pragma once
#include "HSEmailSprite.h"
#include "HSReadUI.h"


class HSEmailListVeiw : public HSListViewInterface
{
public:
	HSEmailListVeiw(const CCSize& frameSize,const CCSize& itemSize,int onceCount);
	~HSEmailListVeiw(void);

public:
	static HSEmailListVeiw* create(const CCSize& frameSize,const CCSize& itemSize,int count);

	virtual CCNode* AddItem(int idx);

	virtual bool UpdataItem( CCNode* pItem,int idx );

	virtual void tableCellTouched( CCTableView* table, CCTableViewCell* cell );



};

#endif // __HSEmailListVeiw_H____

