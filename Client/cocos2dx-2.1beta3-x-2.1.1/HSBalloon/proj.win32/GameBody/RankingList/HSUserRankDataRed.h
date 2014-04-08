/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/20   11:09
 *	File base:	HSUserRankDataRed.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSUserRankDataRed_H__
#define __HSUserRankDataRed_H__
#pragma once
#include "HSBase.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;
#include "HSUserRankSprite.h"
#include "HSRankCell.h"

class HSUserRankDataRed : public CCTableViewDataSource ,public cocos2d::extension::CCTableViewDelegate
{
public:
	HSUserRankDataRed(void);

	~HSUserRankDataRed(void);

private:
	CCSize m_cellSize;
	int m_cellCount;
	SearchRankResponse* m_pRankData;

public:
	static HSUserRankDataRed* New(const CCSize& cellSize,int count,CCNode* pNode);

	bool init(const CCSize& cellSize,int count,CCNode* pNode);

	virtual CCSize cellSizeForTable( CCTableView *table );

	virtual CCTableViewCell* tableCellAtIndex( CCTableView *table, unsigned int idx );

	virtual unsigned int numberOfCellsInTableView( CCTableView *table );

	virtual void tableCellTouched( CCTableView* table, CCTableViewCell* cell );

	virtual void scrollViewDidScroll( CCScrollView* view );

	virtual void scrollViewDidZoom( CCScrollView* view );

	void SetSelfRankData(SearchRankResponse* pMsg);

};
#endif // __HSUserRankDataRed_H____


