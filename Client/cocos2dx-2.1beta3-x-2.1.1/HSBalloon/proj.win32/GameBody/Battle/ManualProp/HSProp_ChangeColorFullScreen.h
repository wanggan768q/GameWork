/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/05/30   19:54
 *	File base:	HSProp_ChangeColorFullScreen.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSProp_ChangeColorFullScreen_H__
#define __HSProp_ChangeColorFullScreen_H__
#pragma once
#include "HSUsePropInterface.h"
#include "HSBalloonFactory.h"

class HSProp_ChangeColorFullScreen : public HSUsePropInterface
{
public:
	HSProp_ChangeColorFullScreen(void);
	~HSProp_ChangeColorFullScreen(void);

public:
	HS_CREATE_USE_PROP_FUNC(HSProp_ChangeColorFullScreen);

	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );

private:
	void ChangerColor();

};

#endif // __HSProp_ChangeColorFullScreen_H____

