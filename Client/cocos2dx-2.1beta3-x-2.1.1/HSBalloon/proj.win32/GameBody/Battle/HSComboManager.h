/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/09   11:13
 *	File base:	HSComboManager.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSComboManager_H__
#define __HSComboManager_H__
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "HSBalloonConfig.h"

class HSComboManager : public CCNode
{
public:
	HSComboManager(void);
	~HSComboManager(void);

private:
	CCSprite*		m_pCombo_5_or_10;
	CCSprite*		m_pCombo_King;
	CCSprite*		m_pCombo_Normal;

	CCLabelAtlas*	m_pCombo_5_or_10_Num;
	CCLabelAtlas*	m_pCombo_King_Num;
	CCLabelAtlas*	m_pCombo_Normal_Num;

	CCSize m_Combo_5_or_10_Num_PngSize ;
	CCSize m_Combo_King_Num_PngSize ;
	CCSize m_Combo_Normal_PngSize ;

	int m_iLastDribbleCount;

	bool m_isShowCombo;

public:
	static HSComboManager* create();

	bool Init();

	void Update(float dt);

	bool GetIsShowCombo() const;

	int GetComboCount();
};


#endif // __HSComboManager_H____
