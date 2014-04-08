/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/04   13:41
 *	File base:	HSContacListener.h
 *	Author:		Ambition
 *	
 *	Purpose:	¸ÕÌåÅö×²¼ì²â ¼àÌýÆ÷
*********************************************************************/
#ifndef __HSContacListener_H__
#define __HSContacListener_H__
#pragma once
#include "HSBalloonSprite.h"

class HSOverlapBalloon
{
public:
	HSOverlapBalloon(HSBalloonSprite* pReferenObject,HSBalloonSprite* pWillChangeObect);
	~HSOverlapBalloon();

	HSBalloonSprite* GetReferenObject();
	HSBalloonSprite* GetWillChangeObect();
	void Handle();

private:
	HSBalloonSprite* m_pReferenObject;
	HSBalloonSprite* m_pWillChangeObect;

};

class HSContacListener : public b2ContactListener
{
public:
	HSContacListener(void);
	~HSContacListener(void);

private:
	std::vector<HSOverlapBalloon> m_willRestBalloonList;
public:
	virtual void BeginContact( b2Contact* contact );

	virtual void EndContact( b2Contact* contact );

	const std::vector<HSOverlapBalloon>* GetWillRestBalloonList();

	void Logic(float dt);
};
#endif // __HSContacListener_H____


