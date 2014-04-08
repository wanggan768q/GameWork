/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/08/26   11:15
 *	File base:	HSProp_LaserGun.h
 *	Author:		Ambition
 *	
 *	Purpose:	º§π‚«π
*********************************************************************/
#ifndef __HSProp_LaserGun_H__
#define __HSProp_LaserGun_H__
#pragma once
#include "HSPropIconInterface.h"
#include "HSGraySprite.h"
#include "HSBalloonSprite.h"

class HSProp_LaserGun : public HSPropIconInterface
{
public:
	HSProp_LaserGun(void);
	~HSProp_LaserGun(void);

public:
	CREATE_PROP_FUNC(HSProp_LaserGun);

	virtual bool InitProp( const PropInfo* pPropInfo );

	virtual void Updata(float dt);

	virtual void Call( CCObject* pObj );

private:
	CCMenuItemToggle* m_pToggle;

	int m_maxCount;
	int m_currentCount;
	CCLabelTTF* m_pCurrentCountTTF;
	


};

#endif // __HSProp_LaserGun_H____


