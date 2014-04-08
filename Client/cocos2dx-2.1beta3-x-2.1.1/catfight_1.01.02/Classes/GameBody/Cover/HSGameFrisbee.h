/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/30   17:06
 *	File base:	HSGameFrisbee.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGameFrisbee_H__
#define __HSGameFrisbee_H__
#pragma once
#include "HSTool.h"
#include "HSReadUI.h"

class HSGameFrisbee : public CCNode
{
public:
	HSGameFrisbee(void);
	~HSGameFrisbee(void);

private:
	struct _MenuItem
	{
		CCNode* pNode;
		CCPoint srcPos;
		CCPoint endPos;

	};
	enum Sate
	{
		Sate_Show,
		Sate_Hide,
	};
	std::vector<_MenuItem> m_menuList;
	std::vector<_MenuItem>::iterator m_menuListIt;
	std::vector<_MenuItem>::reverse_iterator m_menuListRIt;
	Sate m_sate;

private:
	void RunAction(HSGameFrisbee::_MenuItem menuItem);

	//@ Call
	void Call_Sound(CCObject* obj);
	void Call_Muisc(CCObject* obj);
	void Call_Help(CCObject* obj);
	void Call_About(CCObject* obj);
public:
	CREATE_FUNC(HSGameFrisbee);

	bool init();

	void Show();

	void Hide();

	int GetSate();

	void Call(CCNode* pNode);


};

#endif // __HSGameFrisbee_H____


