/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/10   17:09
 *	File base:	HSSet.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSSet_H__
#define __HSSet_H__
#pragma once
#include "HSBase.h"

class HSSet : public CCSet
{
public:
	HSSet(void);
	~HSSet(void);

public:
	void removeAllObjects();
};

#endif // __HSSet_H____


