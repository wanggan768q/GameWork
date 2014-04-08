/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/08/19   17:22
 *	File base:	HSBox2dTool.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBox2dTool_H__
#define __HSBox2dTool_H__
#pragma once
#include "HSBase.h"

#ifdef CC_ENABLE_BOX2D_INTEGRATION
#include "Box2D/Box2D.h"
#endif /* CC_ENABLE_BOX2D_INTEGRATION */

class HSBox2dTool
{
public:
	HSBox2dTool(void);
	~HSBox2dTool(void);
public:
#ifdef CC_ENABLE_BOX2D_INTEGRATION
	static void ScaleBody(b2Body* pBody,float fScale);
	static void Scaleb2Fixture(b2Fixture* pFixture,float fScale);
#endif /* CC_ENABLE_BOX2D_INTEGRATION */


};


#endif // __HSBox2dTool_H____

