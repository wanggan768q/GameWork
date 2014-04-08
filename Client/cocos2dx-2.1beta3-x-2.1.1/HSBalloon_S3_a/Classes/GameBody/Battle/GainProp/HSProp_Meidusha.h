/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/08/26   17:45
 *	File base:	HSProp_Meidusha.h
 *	Author:		Ambition
 *	
 *	Purpose:	√¿∂≈…Ø
*********************************************************************/
#ifndef __HSProp_Meidusha_H__
#define __HSProp_Meidusha_H__
#pragma once
#include "HSPropIconInterface.h"

class HSProp_Meidusha : public HSPropIconInterface
{
public:
	HSProp_Meidusha(void);
	~HSProp_Meidusha(void);
public:
	CREATE_PROP_FUNC(HSProp_Meidusha);

	virtual bool InitProp( const PropInfo* pPropInfo );

	virtual void Call( CCObject* pObj );

	virtual void Updata( float dt );

};

#endif // __HSProp_Meidusha_H____

