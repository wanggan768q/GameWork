/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/08/27   14:18
 *	File base:	HSDebuffPropInterface.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSDebuffPropInterface_H__
#define __HSDebuffPropInterface_H__
#pragma once
#include "HSBalloonSprite.h"


#define CREATE_PROP_FUNC(__TYPE__) \
	static __TYPE__* create(const PropInfo* pPropInfo) \
{ \
	__TYPE__ *pRet = new __TYPE__(); \
	if (pRet && pRet->InitProp(pPropInfo)) \
	{ \
	pRet->SetPropInfoData(pPropInfo); \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}

class HSPropBalloonInterface : public CCNode
{
public:
	HSPropBalloonInterface(void);
	~HSPropBalloonInterface(void);

private:
	std::string m_basePath;
	const PropInfo* m_pPropInfo;

public:

	void SetPropInfoData(const PropInfo* pPropInfo);

	const PropInfo* GetPropInfoData();

	virtual bool InitProp(const PropInfo* pPropInfo) = 0;

	virtual void Updata(float dt) = 0;
};


#endif // __HSDebuffPropInterface_H____




