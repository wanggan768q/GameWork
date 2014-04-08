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

	bool Close(const char* plistFilename);

	bool CloseAllPlist();

	void Destroy();

	CCSpriteFrame* GetSpriteFrameWithKey(const char* key);

	HSCCSprite* CreateSpriteWithKey(const char* key);

};


#endif // __HSReadPlist_H____
