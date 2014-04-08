/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/08/26   18:02
 *	File base:	HSProp_Chameleon.h
 *	Author:		Ambition
 *	
 *	Purpose:	±äÉ«Áú
*********************************************************************/
#ifndef __HSProp_Chameleon_H__
#define __HSProp_Chameleon_H__
#pragma once
#include "HSPropIconInterface.h"

class HSProp_Chameleon : public HSPropIconInterface
{
public:
	HSProp_Chameleon(void);
	~HSProp_Chameleon(void);
public:
	CREATE_PROP_FUNC(HSProp_Chameleon);

	virtual bool InitProp( const PropInfo* pPropInfo );

	virtual void Call( CCObject* pObj );

	virtual void Updata( float dt );

};

#endif // __HSProp_Chameleon_H____


