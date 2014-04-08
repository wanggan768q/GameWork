/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-13
 *	File base:	HSFigureListView.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSFigureListView_H__
#define __HSFigureListView_H__
#pragma once
#include "HSTool.h"
#include "HSFigureSprite.h"

class HSFigureListView : public HSListViewInterface
{
public:
	HSFigureListView(const CCSize& frameSize,const CCSize& itemSize,int onceCount);
	~HSFigureListView(void);
    
public:
	static HSFigureListView* create(const CCSize& frameSize,const CCSize& itemSize,int onceCount);
    
	virtual bool init();
    
	virtual CCNode* AddItem(int idx);
    
	virtual bool UpdataItem( CCNode* pItem,int idx );
    
	virtual void tableCellTouched( CCTableView* table, CCTableViewCell* cell );

};

#endif /* defined(__HSFigure_H__) */





