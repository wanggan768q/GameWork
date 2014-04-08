/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/03   9:53
 *	File base:	HSEmailSystemScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSEmailSystemScene_H__
#define __HSEmailSystemScene_H__
#pragma once
#include "HSTool.h"
#include "HSEmailListVeiw.h"
#include "HSGameShopScene.h"

//Layer
class HSEmailSystemLayer:public CCLayer
{
public:
	HSEmailSystemLayer(void);
	~HSEmailSystemLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSEmailSystemLayer);

private:
	void Load();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	void Call_Shop(CCObject* pObj);
	void Call_Back(CCObject* pObj);
    void Call_AllRevc(CCObject* pObj);

	void Updata(float dt);


private:
	HSEmailListVeiw* m_pEmailListView;
	CCLabelAtlas* m_pMoney;
    int m_iMoney;
};




//Scene
class HSEmailSystemScene:public CCScene
{
public:
	HSEmailSystemScene(void);
	~HSEmailSystemScene(void);
private:
	HSEmailSystemLayer* hsEmailSystemLayer;
	HSGameShopLayer* hsGameShopLayer;

public:
	virtual bool init();
	CREATE_FUNC(HSEmailSystemScene);

	inline HSEmailSystemLayer* GetHSEmailSystemLayer(){return this->hsEmailSystemLayer;};

	inline void SetHSGameShopLayer(HSGameShopLayer* layer)
	{
		this->hsGameShopLayer = layer;
		this->addChild(layer,HS_BASE_TAG,HS_BASE_TAG);
	}
	inline HSGameShopLayer* GetHSGameShopLayer(){return this->hsGameShopLayer;};

};
#endif // __HSFriendsSystemScene_H____

