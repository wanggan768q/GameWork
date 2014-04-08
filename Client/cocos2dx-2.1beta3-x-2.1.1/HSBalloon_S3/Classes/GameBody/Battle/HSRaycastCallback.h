/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/08/06   18:58
 *	File base:	HSRaycastCallback.cpp
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSRaycastCallback_H__
#define __HSRaycastCallback_H__
#pragma once
#include "HSBalloonSprite.h"
#include "HSLine.h"
#include "HSPoint.h"
#include "HSFormula.h"

#define HS_Raycast_filter -1
#define HS_Raycast_terminate 0
#define HS_Raycast_continue 1
#ifndef HS_MAX_DISTANCE
#define HS_MAX_DISTANCE 150.f
#endif


class HSRaycastCallback : public b2RayCastCallback
{
public:
	HSRaycastCallback(void);
	~HSRaycastCallback(void);

protected:
	std::map<int,HSBalloonSprite*> m_passBalloonMap;
	std::vector<HSBalloonSprite*> m_passBalloonList;
	std::vector<HSLine*>* m_pLineList;
	std::vector<HSPoint*>* m_pPointList;
	BalloonColorType m_listerBalloonColorType;
	int* m_pDrawLineCount;

public:
	float32 ReportFixture(b2Fixture *fixture,const b2Vec2 &point,const b2Vec2 &normal,float32 fraction);

	virtual bool AddBalloon(HSBalloonSprite* ps);

	bool RemoveBalloon(int balloonID);

	bool Reverse(HSBalloonSprite* ps);

	const std::map<int,HSBalloonSprite*>* GetPassBalloonMap();

	const std::vector<HSBalloonSprite*>* GetPassBalloonList();

	void SetLineList(std::vector<HSLine*>* pLineList);

	void SetPointList(std::vector<HSPoint*>* pPointList);

	void SetLineCount(int* lineCount);

	bool ReverseLine();
	bool ReverseLineAll();

	bool ReversePoint();
	bool ReversePointAll();
	

	virtual void Reset();
};

#endif // __HSRaycastCallback_H____