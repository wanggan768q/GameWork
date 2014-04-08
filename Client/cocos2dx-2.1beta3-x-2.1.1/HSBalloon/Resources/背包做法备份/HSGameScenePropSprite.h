/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/04/26   14:18
 *	File base:	HSGameScenePropSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGameScenePropSprite_H__
#define __HSGameScenePropSprite_H__
#pragma once
#include "HSTool.h"


class HSGameScenePropSprite : public cocos2d::extension::CCTableViewCell
{
public:
	HSGameScenePropSprite(void);
	~HSGameScenePropSprite(void);

private:
	HSGameScenePropSprite* m_pLastSprite;
	HSGameScenePropSprite* m_pNextSprite;
	int m_id;
	bool m_isBuy;

public:
	static HSGameScenePropSprite* create(const char* fileName,int id,bool isBuy);

	bool Init(const char* fileName,int id,bool isBuy);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

#endif // __HSGameScenePropSprite_H____

