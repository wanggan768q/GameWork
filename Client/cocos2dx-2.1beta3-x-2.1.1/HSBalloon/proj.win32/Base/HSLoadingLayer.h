/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/17   14:30
 *	File base:	HSLoadingLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSLoadingLayer_H__
#define __HSLoadingLayer_H__
#pragma once
#include "HSBase.h"
#include "HSMath.h"

class HSLoadingLayer : public CCLayerColor
{
public:
	HSLoadingLayer(void);
	~HSLoadingLayer(void);

private:
	std::vector<CCSprite*> m_vClawList;
	float m_intervalTime;
public:

	CREATE_FUNC(HSLoadingLayer);

	static HSLoadingLayer* ShareLoading();

	bool init();

	void SetIntervalTime(float v);

	virtual void setVisible(bool visible);
};
#endif // __HSLoadingLayer_H____


