/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/08/27   14:20
 *	File base:	HSPropIconInterface.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSPropIconInterface_H__
#define __HSPropIconInterface_H__
#pragma once
#include "HSBase.h"
#include "PropInfo.pb.h"
using namespace message;

#define CREATE_PROP_FUNC(__TYPE__) \
	static __TYPE__* create(const PropInfo* pPropInfo,int index) \
	{ \
		__TYPE__ *pRet = new __TYPE__(); \
		if (pRet && pRet->InitProp(pPropInfo)) \
		{ \
			pRet->SetIndex(index); \
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

class HSPropIconInterface : public CCNode
{
public:
	HSPropIconInterface(void);
	~HSPropIconInterface(void);

private:
	std::string m_basePath;
	const PropInfo* m_pPropInfo;
	int m_index;
	bool m_isActivate;
	CCProgressTimer* m_CD_Progress;
	bool m_isInvalid;
    CCMenuItem* m_pMenuItem;

private:
	
	void Call_CDEnd(CCNode* pProgress);
	void Call_CheckInvalid(float dt);

public:
	bool AddCD(CCObject* pMenuItem);

	void SetIsActivate(bool b);

	bool GetIsActivate();

	void SetIndex(int index);

	int GetIndex();

	void SetPropInfoData(const PropInfo* pPropInfo);

	const PropInfo* GetPropInfoData() const;

	const std::string& GetBasePath();

	bool Buy();

	virtual bool InitProp(const PropInfo* pPropInfo) = 0;

	virtual void SetIsInvalid(bool is) = 0;

	virtual void Call(CCObject* pObj);

	virtual void Updata(float dt) = 0;
};

#endif // __HSPropIconInterface_H____
