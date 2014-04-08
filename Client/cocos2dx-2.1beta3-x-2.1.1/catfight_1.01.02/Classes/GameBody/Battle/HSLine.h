/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/08/12   9:26
 *	File base:	HSLine.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSLine_H__
#define __HSLine_H__
#pragma once
#include "HSBalloonSprite.h"

class HSLine : public HSCCSprite
{
public:
	HSLine();
	~HSLine(void);

public:
	static HSLine* create(HSBalloonSprite* pBegin,HSBalloonSprite* pEnd);

	bool Init(HSBalloonSprite* pBegin,HSBalloonSprite* pEnd);

	void Updata(float dt);

private:
	HSBalloonSprite* m_pBegin;
	HSBalloonSprite* m_pEnd;
};

#endif // __HSLine_H____

