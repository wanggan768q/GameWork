/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/16   14:09
 *	File base:	HSTableMenu.h
 *	Author:		Ambition
 *	
 *	Purpose:	Ä£·ÂMFC Table¿Ø¼þ
*********************************************************************/
#ifndef __HSTableMenu_H__
#define __HSTableMenu_H__
#pragma once
#include "HSBase.h"

class HSTableMenu : public CCMenu
{
public:
	HSTableMenu(void);
	~HSTableMenu(void);

public:
	CREATE_FUNC(HSTableMenu);

	void AddItem(CCMenuItem* pItem);

	void SetSelect(int index);

	int GetSelect();

	virtual bool ccTouchBegan( CCTouch* touch, CCEvent* event );

	virtual void ccTouchEnded( CCTouch* touch, CCEvent* event );

private:
	std::vector<CCMenuItem*> m_menuItemList;
	int m_selectItemIndex;
	int m_tagCount;
};

#endif // __HSTableMenu_H____


