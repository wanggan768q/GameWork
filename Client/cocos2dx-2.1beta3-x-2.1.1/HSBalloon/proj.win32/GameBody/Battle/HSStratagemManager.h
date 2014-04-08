/********************************************************************
*  Copyright(C) 2013 Zrong ( All rights reserved. )
*	Created:	2013/05/21   14:12
*	File base:	HSStratagemManager.h
*	Author:		Ambition
*	
*	Purpose:	
*********************************************************************/
#ifndef __HSStratagemManager_H__
#define __HSStratagemManager_H__
#pragma once
#include "HSTool.h"
#include "HSBase.h"
#include "HSStratagemSprite.h"

class HSStratagemManager : public CCNode
{
private:
	HSStratagemManager(void);
public:
	~HSStratagemManager(void);

private:
	message::StratagemData* m_pData;
	std::map<unsigned int,HSStratagemSprite*> m_StratagemSpriteMap;
	bool m_isFrsitUpdata;

	std::vector<const message::StratagemData_StratagemConfig*> m_ConfigList;
	std::vector<const message::StratagemData_StratagemConfig*>::iterator m_ConfigIt;
	std::vector<const message::StratagemData_StratagemAction*> m_actionQueue;
	int m_actionIndex;

	bool m_isUseNextStratagemConfig;

public:

	static HSStratagemManager* create(const char* configeDataName,b2World* pWorld);

	bool Init(const char* configeDataName,b2World* pWorld);

	void Up();

	void Down();

	void Updata(float dt);

	int GetActionIndex();

};

#endif // __HSStratagemManager_H____


