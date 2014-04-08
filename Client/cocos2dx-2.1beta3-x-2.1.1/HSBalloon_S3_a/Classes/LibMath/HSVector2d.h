/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/02/28   11:08
 *	File base:	HSVector2d.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSVector2d_H__
#define __HSVector2d_H__
#pragma once
#include "HSMath.h"

class HSVector2d
{
public:
	HSVector2d(float x, float y);
	~HSVector2d(void);

private:
	float m_x;
	float m_y;

public:
	inline float GetX() const { return this->m_x;}

	inline float GetY() const { return this->m_y;}

	inline void Set(float x,float y){ this->m_x = x; this->m_y = y;}
};

typedef std::vector<HSVector2d> HSVector2dV;

#endif // __HSVector2d_H____

