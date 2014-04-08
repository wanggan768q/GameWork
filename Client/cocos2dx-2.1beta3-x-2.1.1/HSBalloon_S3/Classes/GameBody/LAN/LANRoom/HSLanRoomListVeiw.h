/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/03   10:01
 *	File base:	HSLanRoomListVeiw.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSLanRoomListVeiw_H__
#define __HSLanRoomListVeiw_H__
#pragma once
#include "HSLanRoomSprite.h"


class HSLanRoomListVeiw : public HSListViewInterface
{
public:
	HSLanRoomListVeiw(const CCSize& frameSize,const CCSize& itemSize,int onceCount);
	~HSLanRoomListVeiw(void);

public:
	static HSLanRoomListVeiw* create(const CCSize& frameSize,const CCSize& itemSize,int count);

	virtual CCNode* AddItem(int idx);

	virtual bool UpdataItem( CCNode* pItem,int idx );

	virtual void tableCellTouched( CCTableView* table, CCTableViewCell* cell );



};

#endif // __HSLanRoomListVeiw_H__

