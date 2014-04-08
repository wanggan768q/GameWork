/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/27   13:22
 *	File base:	HSModalDialog.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSModalDialogInterface_H__
#define __HSModalDialogInterface_H__
#pragma once
#include "HSBase.h"

class HSModalDialogInterface : public CCLayerColor
{
public:
	HSModalDialogInterface(void);
	~HSModalDialogInterface(void);

private:
	cocos2d::CCMenu *m_pMenu;
	cocos2d::CCArray *m_pMenuItemArray;
	bool m_isTouchedMenu;
	CCLayer* m_pBackground;

private:  
	/** Initialize the menu will be added to the modal dialog box*/  
	bool InitMenu();

public:
	virtual bool init();

	virtual bool InitBackground();

	virtual void SetBackground(CCLayer* pLayer);

	virtual bool InitDialog() = 0;

	virtual void onEnter();

	virtual void onExit();

	void PushMenu(CCMenuItem *pItem);

	void PushMenu(CCArray* pArray);

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent); 

	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent); 
};

#endif // __HSModalDialogInterface_H__


