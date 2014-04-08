/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/08/22   17:31
 *	File base:	HSCrossBorderInterface.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSCrossBorderInterface_H__
#define __HSCrossBorderInterface_H__
#pragma once
#include "HSBase.h"

class HSCrossBorderInterface
{
public:
	HSCrossBorderInterface(void);
	~HSCrossBorderInterface(void);

public:
	virtual void HandleCross(CCObject* pObj) = 0;

};

#endif // __HSCrossBorderInterface_H____



