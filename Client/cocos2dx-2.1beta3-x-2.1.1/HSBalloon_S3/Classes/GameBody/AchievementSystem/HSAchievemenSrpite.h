/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/05   17:17
 *	File base:	HSAchievemenSrpite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSAchievemenSrpite_H__
#define __HSAchievemenSrpite_H__
#pragma once
#include "HSTool.h"

class HSAchievemenSrpite : public HSCCSprite
{
public:
	HSAchievemenSrpite(void);
	~HSAchievemenSrpite(void);

public:
	static HSAchievemenSrpite* create();

	bool init();

	void UpdataAchievemen( AchievementResponse_AchievemenStateInfo* pAchievement);

	void Call(CCObject* pObj);
public:
    static AchievementResponse_AchievemenStateInfo* S_ReceiveAchievementReward;
    
private:
	HSGraySprite* m_pIcon;
	CCSprite* m_pYiLingQu;
    CCSprite* m_pWeiLingQu;
    CCSprite* m_pSuo;
	CCMenu* m_pGetMenu;

	CCLabelTTF* m_pName;
	CCLabelTTF* m_pDescribe;
	AchievementResponse_AchievemenStateInfo* m_pInfoData;
};
#endif // __HSAchievemenSrpite_H____


