/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/16   17:15
 *	File base:	HSPropItemSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSPropItemSprite_H__
#define __HSPropItemSprite_H__
#pragma once
#include "HSTool.h"
class HSPropItemSprite : public CCNode
{
public:
	HSPropItemSprite();  
	~HSPropItemSprite();
public:
	//@data
	const PropInfo* m_pPropInfo;
	//@UI
	CCSprite* m_pLockSprite;
	CCLabelTTF* m_pLockLevel;
	CCSprite* m_pFrame;
	CCMenuItemToggle* m_pToggle;
	//@logic

	float m_frame_scaleX;
	float m_frame_scaleY;
	bool lock;
	bool isAdd;

public:
	static HSPropItemSprite* create(const message::PropInfo& propInfo ,int index);
	bool Init(const message::PropInfo& propInfo,int index);
public:
	void Call(CCObject*);
	bool Recover();
public:
	void Update(float dt);
};
#endif // __HSPropItemSprite_H____


