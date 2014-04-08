/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/09/09   10:36
 *	File base:	HSPlayerInfoSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSPlayerInfoSprite_H__
#define __HSPlayerInfoSprite_H__
#pragma once
#include "HSTool.h"
class HSPlayerInfoSprite : public CCSprite
{
public:
	HSPlayerInfoSprite(void);
	~HSPlayerInfoSprite(void);
public:
	static HSPlayerInfoSprite* create(int index);
	bool Init(int index);
	void UpdataPlayerInfo(int index,const message::UserBasicInfo* userInfo);
public:
	CCLabelTTF* m_pLeft;
	CCLabelTTF* m_pRight;
	CCSprite* m_pBackGround;
	CCTexture2D* m_pdark;
	CCTexture2D* m_plight;
};

#endif // __HSPlayerInfoSprite_H____


