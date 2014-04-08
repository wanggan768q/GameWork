/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/20   11:01
 *	File base:	HSRankListView.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSRankListView_H__
#define __HSRankListView_H__
#pragma once
#include "HSBase.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;

#include "HSUserRankDataBule.h"
#include "HSUserRankDataRed.h"

class HSRankListView : public CCTableView
{
public:
	HSRankListView(void);
	~HSRankListView(void);

private:
	HSUserRankDataBule* m_pUserRankDataBult;
	HSUserRankDataRed* m_pUserRankDataRed;
	RankSpriteType m_pType;
public:
	static HSRankListView* Create(const CCSize& size,const RankSpriteType& type,CCNode* pNode,SearchRankResponse* pMsg);

	bool init(const CCSize& size,const RankSpriteType& type,CCNode* pNode,SearchRankResponse* pMsg);

	void SetRankData(SearchRankResponse* pMsg);
};

#endif // __HSRankListView_H____

