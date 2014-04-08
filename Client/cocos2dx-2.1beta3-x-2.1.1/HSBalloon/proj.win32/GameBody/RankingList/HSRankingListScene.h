/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/04/25   14:09
 *	File base:	HSRankingListScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSRankingListScene_H__
#define __HSRankingListScene_H__
#pragma once
#include "HSTool.h"

#include "HSRankListView.h"

//Layer
class HSRankingListLayer:public CCLayer
{
public:
	HSRankingListLayer(void);
	~HSRankingListLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSRankingListLayer);

public:
	static SearchRankResponse m_pRankData;
private:
	typedef enum 
	{
		RANKINGLIST_TYPE_WORLD = 0x2b,	//世界排行
		RANKINGLIST_TYPE_WEEK,			//周排行
	}RankingListType;

	message::SearchRankResponse* m_pRankingListWorld;	//世界排行数据

	message::SearchWeeklyScoreResponse* m_pRankingListWeek;//周排行数据

	HSRankListView* m_pWorldRank;
	HSRankListView* m_pSelfRank;

	float m_dt;

private:
	void Load();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	void Updata(float dt);

	//@Call
	void CallMenu(CCObject* obj);

	static void SetRankData(SearchRankResponse* pMsg);
	void ShowRank();
};




//Scene
class HSRankingListScene:public CCScene
{
public:
	HSRankingListScene(void);
	~HSRankingListScene(void);
private:
	HSRankingListLayer* hsRankingListLayer;

public:
	virtual bool init();
	CREATE_FUNC(HSRankingListScene);

	inline HSRankingListLayer* GetHSRankingListLayer(){return this->hsRankingListLayer;};

};
#endif // __HSRankingListScene_H____
