/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/06/02   13:30
 *	File base:	HSProp_Lightning.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_Lightning_H__
#define __HSProp_Lightning_H__
#pragma once
#include "HSUsePropInterface.h"
#include "HSBalloonFactory.h"

class HSProp_Lightning : public HSUsePropInterface
{
public:
	HSProp_Lightning(void);
	~HSProp_Lightning(void);

private:
	bool m_isLister;
	HSBalloonFactory m_factory;
	std::vector<HSBalloonSprite*> m_workingAreaSprites;
public:
	HS_CREATE_USE_PROP_FUNC(HSProp_Lightning);

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

	virtual void Updata( float dt );

private:
	void QueryAABB();

	void Lihgtning();

	

};

#endif // __HSProp_Lightning_H____

