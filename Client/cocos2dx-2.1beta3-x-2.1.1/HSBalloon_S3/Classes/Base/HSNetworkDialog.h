/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	2014/01/06   10:30
 *	File base:	HSNetworkDialog.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSNetworkDialog_H__
#define __HSNetworkDialog_H__
#pragma once

#include "HSTool.h"

class HSNetworkDialog : public HSModalDialogInterface
{
public:
	HSNetworkDialog(void);
	~HSNetworkDialog(void);
    
public:
    static HSNetworkDialog* ShareNetworkDialog();
public:
	CREATE_FUNC(HSNetworkDialog);
    
    virtual bool InitBackground();
	virtual bool InitDialog();
    
public:
    
    void Show();
    
    void Call_Sure(CCObject* pObj);
    
    void Call_Cancel(CCObject* pObj);
};

#endif // __HSNetworkDialog_H__