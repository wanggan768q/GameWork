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
    static HSFriendInfoSprite* createWithDefault();

	bool Init();
    bool InitWithDefault();
    
	void UpdataPlayerInfo(int index,FriendListResponse_PlayerInfo* pPlayerInfo);

	void Call_GiveTrophy(CCObject* pObj);
    void Call_IsAcceptTrophy(CCObject* pObj);
    
    void Call_AddFriend(CCObject* obj);

private:
	CCSpriteFrame* m_pTrophyTexture_0;
	CCSpriteFrame* m_pTrophyTexture_1;
	CCSpriteFrame* m_pTrophyTexture_2;

	CCSprite* m_HeadIcon;
	CCSprite* m_pTrophy;
    CCSprite* m_pGameScoreFrame;
    CCSprite* m_pNameFrame;

	CCLabelTTF* m_pName;
	CCLabelTTF* m_pMoney;
	CCLabelTTF* m_pGameScore;
	CCLabelAtlas* m_pRanking;
    
    FriendListResponse_PlayerInfo* m_pFirendInfo;

};

#endif // __HSFriendInfoSprite_H____


