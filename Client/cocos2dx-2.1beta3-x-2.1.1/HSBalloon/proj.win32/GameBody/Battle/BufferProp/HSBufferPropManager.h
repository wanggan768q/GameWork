/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/16   20:23
 *	File base:	HSBufferPropManager.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBufferPropManager_H__
#define __HSBufferPropManager_H__
#pragma once
#include "HSBufferPropList.h"

class HSBufferPropManager : public CCNode
{
public:
	HSBufferPropManager(void);
	~HSBufferPropManager(void);

private:
	bool m_isHasBuffer;
public:
	CREATE_FUNC(HSBufferPropManager);

	bool init();

	bool IsHasBuffer();
};

#endif // __HSBufferPropManager_H____

