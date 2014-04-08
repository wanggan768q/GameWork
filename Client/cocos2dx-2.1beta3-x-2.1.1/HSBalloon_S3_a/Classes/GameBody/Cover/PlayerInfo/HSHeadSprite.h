/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/09/11   11:05
 *	File base:	HSHeadSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSHeadSprite_H__
#define __HSHeadSprite_H__
#pragma once
#include "HSTool.h"
class HSHeadSprite : public CCNode
{
public:
	HSHeadSprite(void);
	~HSHeadSprite(void);
public:
	static HSHeadSprite* create(const message::PropInfo& propInfo ,int index);
	bool Init(const message::PropInfo& propInfo,int index);
private:
	//@logic
	void Select(CCObject*);
public:
	//@logic
	void SetTarget(CCObject* rec,SEL_CallFuncND selector,void* data);
private:
	//@call
	CCObject* m_pTarget;
private:
	//@data
	const message::PropInfo* m_propInfo;
	int m_index;
private:
	//logic
	CCObject* pTarget;
	SEL_CallFuncND selector;
	void* pData;

private:
	//@UI
	CCMenu* m_pMenu;
	CCLabelAtlas* m_pMoney;
	

};
#endif // __HSHeadSprite_H____


