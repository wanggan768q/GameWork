/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/11/13   10:25
 *	File base:	HSReadPlist.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSReadPlist_H__
#define __HSReadPlist_H__
#pragma once
#include "HSBase.h"
#include "HSMacros.h"
#include "HSCCSprite.h"


#ifndef HS_READ_PLIST
#define HS_READ_PLIST
#define HS_RP_GetSpriteFrame(__TextureName__) HSReadPlist::ShareReadPlist()->GetSpriteFrameWithKey((__TextureName__))
#define HS_RP_GetTexture2D(__TextureName__) HS_RP_GetSpriteFrame(__TextureName__)->getTexture()
#define HS_RP_GetTextureSize(__TextureName__) HS_RP_GetSpriteFrame(__TextureName__)->getRect().size
#endif


class HSReadPlist
{
private:
	HSReadPlist(void);
	~HSReadPlist(void);

private:
	std::set<std::string> m_plistNameList;

public:
	static HSReadPlist* ShareReadPlist();

	void Open(const char* plistFileName,const char* plistPng);
    
    void Open(const char* plistFileName,CCTexture2D* pTexture);
    
    void Open(const char* plistFileName,CCImage* pImage);

	bool Close(const char* plistFilename);

	bool CloseAllPlist();

	void Destroy();

	CCSpriteFrame* GetSpriteFrameWithKey(const char* key);

	HSCCSprite* CreateSpriteWithKey(const char* key);

};


#endif // __HSReadPlist_H____
