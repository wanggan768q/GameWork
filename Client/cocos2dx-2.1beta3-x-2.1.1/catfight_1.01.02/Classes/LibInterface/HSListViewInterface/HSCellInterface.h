/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/02   17:55
 *	File base:	HSCellInterface.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSCellInterface_H__
#define __HSCellInterface_H__
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;

#define HS_namespace_HSListViewControl_Begin namespace HSListViewControl{
#define HS_namespace_HSListViewControl_End }
#define HS_namespace_Using_HSListViewControl using namespace HSListViewControl

HS_namespace_HSListViewControl_Begin

class HSCellInterface : public CCTableViewCell
{
public:
	HSCellInterface(void);
	~HSCellInterface(void);
public:
	CREATE_FUNC(HSCellInterface);

	bool init();

	virtual void addChild(CCNode* child,int zOrder, int tag);

	CCNode* GetChild();

private:
	CCNode* m_pChild;
};

HS_namespace_HSListViewControl_End

#endif // __HSCellInterface_H____


