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

class HSRoomSprite : public CCSprite
{
public:
	HSRoomSprite(void);
	~HSRoomSprite(void);

private:
	std::map<int,CCTexture2D*> m_TextureMap;
	CCSprite* m_pRoomName;
	CCSprite* m_pPlayerCountFrame;
	CCSprite* m_pStakeGoldFrame;
	CCLabelTTF* m_pPlayerCountTTF;
	CCLabelTTF* m_pStakeCountTTF;
public:
	CREATE_FUNC(HSRoomSprite);

	bool init();

	void UpdataRoomInfo(const RoomDataResponse_Room& room);
};

#endif // __HSRoomSprite_H____

