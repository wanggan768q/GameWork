/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/21   18:38
 *	File base:	HSInputDialogLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSInputDialogLayer_H__
#define __HSInputDialogLayer_H__
#pragma once
#include "HSTool.h"

class HSInputDialogLayer : public CCLayer
{
public:
	HSInputDialogLayer(void);
	~HSInputDialogLayer(void);

public:
	virtual bool init();
	CREATE_FUNC(HSInputDialogLayer);

private:

	CCTextFieldTTF* m_pTextFieldTTF;
	CCRect m_InputRect;
	const char* m_nickname;

private:
	void Load();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	virtual void setVisible(bool visible);

	void CallYes(CCObject* obj);

	//Net
	void ResponseRegister(RegisterResponse* pMsg);

};
#endif // __HSInputDialogLayer_H____


