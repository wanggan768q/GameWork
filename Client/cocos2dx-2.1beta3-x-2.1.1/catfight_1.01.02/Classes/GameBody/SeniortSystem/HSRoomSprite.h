/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/23   15:54
 *	File base:	HSRoomSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSRoomSprite_H__
#define __HSRoomSprite_H__
#pragma once
#include "HSTool.h"
#include "HSGoldInadequateDialog.h"

class HSRoomSprite : public CCSprite
{
public:
	HSRoomSprite(void);
	~HSRoomSprite(void);

private:
	std::map<int,CCSpriteFrame*> m_TextureMap;
	CCSprite* m_pRoomName;
	CCSprite* m_pPlayerCountFrame;
	CCSprite* m_pStakeGoldFrame;
	CCLabelTTF* m_pPlayerCountTTF;
	CCLabelTTF* m_pStakeCountTTF;
    int m_id;
public:
	CREATE_FUNC(HSRoomSprite);

	bool init();

    void ROOMCall(CCObject* pObj);
    
	void UpdataRoomInfo(int idx,const RoomDataResponse_Room& room);
};

#endif // __HSRoomSprite_H____

