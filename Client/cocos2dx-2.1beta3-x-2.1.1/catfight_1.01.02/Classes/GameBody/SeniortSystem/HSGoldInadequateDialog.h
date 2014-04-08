/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/23   17:22
 *	File base:	HSGoldInadequateDialog.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGoldInadequateDialog_H__
#define __HSGoldInadequateDialog_H__
#pragma once
#include "HSTool.h"

class HSGoldInadequateDialog : public HSModalDialogInterface
{
public:
	HSGoldInadequateDialog(void);
	~HSGoldInadequateDialog(void);
public:
	CREATE_FUNC(HSGoldInadequateDialog);

	virtual bool InitBackground();

	virtual bool InitDialog();
public:
	void Set_BugGold(const BuyGold* bugGold,const int& num);

private:
	void Call_GoRoom(CCObject* pObj);
	void Call_Buy(CCObject* pObj);

private:
	const BuyGold* m_buyGold;
	int m_num;
	CCLabelTTF* m_pGoldTTF;
	CCLabelTTF* m_pMoneyTTF;

};

#endif // __HSGoldInadequateDialog_H____

