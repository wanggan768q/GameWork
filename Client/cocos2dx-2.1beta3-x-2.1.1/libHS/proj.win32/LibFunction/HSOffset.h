/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/18   19:08
 *	File base:	HSOffset.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSOffset_H__
#define __HSOffset_H__
#pragma once
#include "HSBase.h"

class HSOffset
{
public:
	HSOffset(void);
	~HSOffset(void);


public:
	static HSOffset* ShaderOffset();

	float OffsetX();
	float OffsetY();

	float GetScaleX();

	float GetScaleY();


public:
	float m_fScaleX;
	float m_fScaleY;
	CCSize m_frameSize;
	CCSize m_lsSize;
};

#endif // __HSOffset_H____

