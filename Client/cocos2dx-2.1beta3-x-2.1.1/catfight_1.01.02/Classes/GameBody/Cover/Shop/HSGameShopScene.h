/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )

 *	Created:	2013/09/11   17:50
 *	File base:	HSGameShopScene.h
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
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	virtual void setVisible(bool visible);

public:
	//@logic
	void CallReturn(CCObject* pObj);
	void Shop_FlyIn(CCNode& shop_frame,CCPoint&frame_Position);
	void Shop_FlyOut(CCNode& shop_frame,CCPoint& frame_Position);
	void Shop_FlyOutFinish();
	void Shop_FlyInFinish();
public:
	//@update
	void Update(float dt);
private:
	//@UI
	CCLabelAtlas* m_p_shop_money;
	HSShopListView* m_p_shop_listview;
	CCNode* m_p_shop_frame;
	CCPoint m_shop_frame_Position;
	CCLayer* m_p_foregroundLayer;
	CCSprite* m_p_backgournd;
	bool m_shop_flyIn;
	int m_money;

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





