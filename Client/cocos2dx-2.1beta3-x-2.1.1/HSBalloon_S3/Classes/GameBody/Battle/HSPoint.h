/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/12   19:04
 *	File base:	HSPoint.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSPoint_H__
#define __HSPoint_H__
#pragma once
#include "HSTool.h"

class HSPoint : public HSCCSprite
{
public:
	HSPoint(void);
	~HSPoint(void);

private:
	CCNode* m_pPosNode;
public:
	static HSPoint* create(CCNode* pPos);

	bool init(CCNode* pPos);

	void Updata(float dt);
};
#endif // __HSPoint_H____


