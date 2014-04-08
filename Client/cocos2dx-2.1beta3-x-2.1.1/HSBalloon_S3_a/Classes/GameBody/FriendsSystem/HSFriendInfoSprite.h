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

typedef enum 
{
	InfoType_Friend = 0,
	InfoType_Enemy = 1,
}HSInfoType;

class HSFriendInfoSprite : public CCSprite
{
public:
	HSFriendInfoSprite(void);
	~HSFriendInfoSprite(void);

public:
	static HSFriendInfoSprite* create(const HSInfoType& type);

	bool init(const HSInfoType& type);

	void UpdataPlayerInfo(int index,const FriendInfoResponse_PlayerInfo* pPlayerInfo);

	void Call(CCObject* pObj);

private:
	CCTexture2D* m_pTrophyTexture_0;
	CCTexture2D* m_pTrophyTexture_1;
	CCTexture2D* m_pTrophyTexture_2;

	CCTexture2D* m_pState_0;
	CCTexture2D* m_pState_1;
	CCTexture2D* m_pState_2;

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

	HSInfoType m_type;
};

#endif // __HSFriendInfoSprite_H____


