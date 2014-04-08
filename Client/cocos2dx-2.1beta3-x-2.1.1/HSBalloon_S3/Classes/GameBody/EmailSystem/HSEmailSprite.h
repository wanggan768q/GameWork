/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/05   14:05
 *	File base:	HSEmailSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSEmailSprite_H__
#define __HSEmailSprite_H__
#pragma once
#include "HSTool.h"
#include "HSGameDialogLayer.h"

class HSEmailSprite : public HSCCSprite
{
public:
	HSEmailSprite(void);
	~HSEmailSprite(void);

public:
	static HSEmailSprite* create();

	bool Init();

	void UpdataInfo(EmailResponse_EmailInfo* pEmailInfo);

	void Call_GetAward(CCObject* pObj);

private:
    CCMenuItemSprite* m_pMenuItem;
	CCLabelTTF* m_pName;
    CCSprite* m_HeadIcon;
    
    EmailResponse_EmailInfo* m_pEmailInfo;
};

#endif // __HSEmailSprite_H__


