/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/27   17:32
 *	File base:	HSGameGuideRaycastCallback.h
 *	Author:		Ambition
 *	
 *	Purpose:	新手引导线
*********************************************************************/
#ifndef __HSGameGuideRaycastCallback_H__
#define __HSGameGuideRaycastCallback_H__
#pragma once
#include "HSRaycastCallback.h"


class HSTrackMove;

class HSGameGuideRaycastCallback : public HSRaycastCallback,public CCObject
{
public:
	HSGameGuideRaycastCallback(void);
	~HSGameGuideRaycastCallback(void);

public:
	HSTrackMove* m_pTrackMove;
	//新手引导轨迹
	std::vector< std::vector< int >* > m_destroyBalloonIDList;
	bool m_isAddFrist;
public:

	virtual bool AddBalloon( HSBalloonSprite* ps );

	virtual void Reset();

	bool IsAllowDestroy();

	void StartGuide(CCNode* pNode);

};


class HSTrackMove : public CCObject
{
public:
	HSTrackMove(CCNode* pNode ,std::vector< int >* pTrackID);
	~HSTrackMove(void);

private:
	std::vector< int >* m_pTrackID;
	std::vector< int >::iterator m_TrackID_It;
	float m_duration;
	CCNode* m_pNode;

	enum ActionState
	{
		ActionState_Pause,
		ActionState_Run,
		ActionState_Await,
	};
	ActionState m_actionState;

public:
	void Start();

	void Next(CCNode* pNode);

	void Reset();

	void Stop();

	void SetTrack(std::vector< int >* pTrackID);

	CCNode* GetMoveNode();
};



#endif // __HSGameGuideRaycastCallback_H____


