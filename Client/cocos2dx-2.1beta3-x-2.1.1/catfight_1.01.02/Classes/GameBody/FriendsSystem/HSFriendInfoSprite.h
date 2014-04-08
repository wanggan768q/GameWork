/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/05   14:05
 *	File base:	HSFriendInfoSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSFriendInfoSprite_H__
#define __HSFriendInfoSprite_H__
#pragma once
#include "HSTool.h"

class HSFriendInfoSprite : public HSCCSprite
{
public:
	HSFriendInfoSprite(void);
	~HSFriendInfoSprite(void);

public:
	static HSFriendInfoSprite* create();

	bool Init();

	void UpdataPlayerInfo(int index,FriendListResponse_PlayerInfo* pPlayerInfo);

	void Call_SendEmail(CCObject* pObj);

private:
	CCSpriteFrame* m_pTrophyTexture_0;
	CCSpriteFrame* m_pTrophyTexture_1;
	CCSpriteFrame* m_pTrophyTexture_2;

	CCSpriteFrame* m_pState_0;
	CCSpriteFrame* m_pState_1;
	CCSpriteFrame* m_pState_2;

	CCSprite* m_pHeadFrame;
	CCSprite* m_HeadIcon;
	CCSprite* m_pTrophy;
	CCSprite* m_pState;
	CCSprite* m_pBell;
	CCSprite* m_pNameFrame;
	CCSprite* m_pMoneyFrame;

	CCLabelTTF* m_pName;
	CCLabelTTF* m_pMoney;
	CCLabelTTF* m_pGameScore;
	CCLabelTTF* m_pRanking;
    
    CCMenu* m_pSendEmailMenu;
    
    FriendListResponse_PlayerInfo* m_pFirendInfo;

};

#endif // __HSFriendInfoSprite_H____


