/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/04/08   13:45
 *	File base:	HSStratagemSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSStratagemSprite_H__
#define __HSStratagemSprite_H__
#pragma once
#include "HSBase.h"
#include "cocos-ext.h"
#include "GLES-Render.h"
USING_NS_CC_EXT;
#include "HSStratagemData.pb.h"
#include "HSBox2dShapeCache.h"
#include "HSBalloonConfig.h"

class HSStratagemSprite : public CCPhysicsSprite
{
public:
	~HSStratagemSprite(void);
private:
	HSStratagemSprite(void);

private:
	std::vector<const message::StratagemData_StratagemStep*> m_moveStepList;
	bool m_isMoveOver;
	HSStratagemSprite* m_pNexyStratagem;

	CCPoint m_sourcePoint;

public:
	static HSStratagemSprite* create(const message::StratagemData_StratagemBase* pBase,b2World* pWorld);

	bool Init(const message::StratagemData_StratagemBase* pBase,b2World* pWorld);

	b2Body* createBody(const message::StratagemData_StratagemBase* pBase,b2World* pWorld);

	void AddMoveStep(const message::StratagemData_StratagemStep* pStep);

	void Start();

	void MoveToZero();

	void Over();

	bool GetIsMoveOver();

	void SetNextStratagem(HSStratagemSprite* pNext);
};

#endif // __HSStratagemSprite_H____


