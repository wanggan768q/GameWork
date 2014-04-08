/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/09/17   13:54
 *	File base:	HSTool.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSToolBase_H__
#define __HSToolBase_H__
#pragma once
#include "HSBase.h"
#include "HSDataStruct.h"
#include "HSMacros.h"
#include "HSStructure.h"
#include "SPX_Sprite.h"
#include "HSTime.h"
#include "HSMath.h"
#include "HSReadData.h"
#include "HSCCSprite.h"
#include "HSReadUI.h"
#include "HSReadPlist.h"
#include "HSSoundManage.h"
#include "HSVisibleRect.h"
#include "HSOffset.h"
#include "HSJson.h"

class HSToolBase
{
public:
	HSToolBase(void);
	~HSToolBase(void);

public:
	virtual void Release() = 0;

	static void SetLayerScale(CCNode* layer);

	static void SetSelfLayerScale(CCNode* layer);

	static void SetNodeFilldScreen(CCNode* pNode);

	static void SetLayerFillScreen(CCLayer* pLayer);

	static void SetPointScale(CCPoint& pos);

	static void SetRectScale(CCRect& rect);

	static const CCSize& SetSizeScale(CCSize& size,float sx,float sy);
	static const CCSize& SetSizeScale(CCSize& size,float s);

	static float GetOffsetX();
	static float GetOffsetY();

};

#endif // __HSToolBase_H__
