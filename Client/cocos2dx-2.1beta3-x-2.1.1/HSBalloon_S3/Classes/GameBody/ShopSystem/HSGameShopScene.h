/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/09/11   17:50
 *	File base:	HSGameShopLayer.h
 *	Author:		Ambition
 *
 *	Purpose:
*********************************************************************/
#ifndef __HSGameShopScene_H__
#define __HSGameShopScene_H__
#pragma once
#include "HSTool.h"
class HSShopListView;
class HSGameShopLayer:public CCLayer
{
public:
	HSGameShopLayer(void);
	~HSGameShopLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSGameShopLayer);

	static HSGameShopLayer* SharedShopLayer();

private:
	void Load();
    void Call_Back(CCObject* obj);
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

public:
	//@logic
	void Shop_FlyIn(CCNode& shop_frame,CCPoint&frame_Position);
	void Shop_FlyOut(CCNode& shop_frame,CCPoint& frame_Position);
	void Shop_FlyOutFinish();
	void Shop_FlyInFinish();
public:
	//@update
	void Updata(float dt);
private:

};

class HSGameShopScene:public CCScene
{
public:
	HSGameShopScene(void);
	~HSGameShopScene(void);
public:
	HSGameShopLayer* shopLayer;
public:
	virtual bool init();
	CREATE_FUNC(HSGameShopScene);
};

#endif // __HSGameShopLayer_H____





