/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/05   14:05
 *	File base:	HSAddressSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSAddressSprite_H__
#define __HSAddressSprite_H__
#pragma once
#include "HSTool.h"
#include "HSGameDialogLayer.h"

class HSAddressSprite : public HSCCSprite
{
public:
	HSAddressSprite(void);
	~HSAddressSprite(void);

public:
	static HSAddressSprite* create();

	bool Init();

	void UpdataInfo(AddressBookResponse_Name* pName);

	void Call_Invite(CCObject* pObj);

private:
	CCLabelTTF* m_pName;
    CCSprite* m_HeadIcon;
    CCMenuItemSprite* m_pMenuItem;
    
    AddressBookResponse_Name* m_address;
};

#endif // __HSAddressSprite_H__


