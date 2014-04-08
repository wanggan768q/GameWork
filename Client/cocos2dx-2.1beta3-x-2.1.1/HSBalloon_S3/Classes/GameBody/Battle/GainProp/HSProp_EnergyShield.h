/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/08/26   17:57
 *	File base:	HSProp_EnergyShield.h
 *	Author:		Ambition
 *	
 *	Purpose:	ÄÜÁ¿»¤¶Ü
*********************************************************************/
#ifndef __HSProp_EnergyShield_H__
#define __HSProp_EnergyShield_H__
#pragma once
#include "HSPropIconInterface.h"

class HSProp_EnergyShield : public HSPropIconInterface
{
public:
	HSProp_EnergyShield(void);
	~HSProp_EnergyShield(void);
public:
	CREATE_PROP_FUNC(HSProp_EnergyShield);

	virtual bool InitProp( const PropInfo* pPropInfo );
    
    virtual void SetIsInvalid(bool is);

	virtual void Call( CCObject* pObj );

	virtual void Updata( float dt );

	void Call_CCDelayTime();
    
private:
    CCMenuItemSprite* m_pMenuItem;


};
#endif // __HSProp_EnergyShield_H____


