/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/05   14:05
 *	File base:	HSLanRoomSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSLanRoomSprite_H__
#define __HSLanRoomSprite_H__
#pragma once
#include "HSTool.h"

class HSLanRoomSprite : public HSCCSprite
{
public:
	HSLanRoomSprite(void);
	~HSLanRoomSprite(void);

public:
	static HSLanRoomSprite* create();

	bool Init();

	void UpdataRoomInfo(int index,LanSearchRoomResponse_room* pRoom);
    
    void Call_Room(CCObject* pObj);

private:
    
    CCLabelTTF* m_pRoomName;
    
    CCLabelTTF* m_pRoomInfo;
    
    LanSearchRoomResponse_room* m_pRoom;
    

};

#endif // __HSLanRoomSprite_H__


