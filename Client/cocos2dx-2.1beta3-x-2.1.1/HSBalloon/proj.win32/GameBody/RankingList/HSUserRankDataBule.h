/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/20   11:09
 *	File base:	HSUserRankDataBule.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSUserRankDataBule_H__
#define __HSUserRankDataBule_H__
#pragma once
#include "HSBase.h"
#include "cocos-ext.h"
#include "HSReadUI.h"
using namespace cocos2d::extension;

#include "HSRankCell.h"
#include "HSUserRankSprite.h"

class HSUserRankDataBule :public CCTableViewDataSource ,public cocos2d::extension::CCTableViewDelegate
{
public:
	HSUserRankDataBule(void);

	~HSUserRankDataBule(void);

private:
	CCSize m_cellSize;
	int m_cellCount;
	SearchRankResponse* m_pRankData;

public:
	static HSUserRankDataBule* New(const CCSize& cellSize,int count,CCNode* pNode);

	bool init(const CCSize& cellSize,int count,CCNode* pNode);

	virtual CCSize cellSizeForTable( CCTableView *table );

	virtual CCTableViewCell* tableCellAtIndex( CCTableView *table, unsigned int idx );

	virtual unsigned int numberOfCellsInTableView( CCTableView *table );

	virtual void tableCellTouched( CCTableView* table, CCTableViewCell* cell );

	virtual void scrollViewDidScroll( CCScrollView* view );

	virtual void scrollViewDidZoom( CCScrollView* view );

	void SetWorldRandData(SearchRankResponse* pMsg);

};
#endif // __HSUserRankDataBule_H____


