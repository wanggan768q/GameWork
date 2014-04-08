/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/04/26   10:26
 *	File base:	HSBuyPropScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBuyPropScene_H__
#define __HSBuyPropScene_H__
#pragma once
#include "HSTool.h"
#include "HSGameScenePropSprite.h"


//Layer
class HSBuyPropLayer:public CCLayer,public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
	HSBuyPropLayer(void);
	~HSBuyPropLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSBuyPropLayer);

private:
	void Load();

public:
	//@CCLayer
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();


	//@CCTableViewDataSource
	virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);


	//@CCTableViewDelegate
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
};




//Scene
class HSBuyPropScene:public CCScene
{
public:
	HSBuyPropScene(void);
	~HSBuyPropScene(void);
private:
	HSBuyPropLayer* hsBuyPropLayer;

public:
	virtual bool init();
	CREATE_FUNC(HSBuyPropScene);

	inline HSBuyPropLayer* GetHSBuyPropLayer(){return this->hsBuyPropLayer;};

};
#endif // __HSBuyPropScene_H____
