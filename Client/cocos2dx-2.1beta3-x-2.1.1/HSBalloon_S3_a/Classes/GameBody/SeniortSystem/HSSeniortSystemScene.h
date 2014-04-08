/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/23   15:44
 *	File base:	HSSeniortSystemScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSSeniortSystemScene_H__
#define __HSSeniortSystemScene_H__
#pragma once
#include "HSTool.h"
#include "HSRoomListView.h"
#include "HSGameShopLayer.h"
//Layer
class HSSeniortSystemLayer:public CCLayer
{
public:
	HSSeniortSystemLayer(void);
	~HSSeniortSystemLayer(void);

private:
	CCLabelAtlas* m_pMoney;
public:
	virtual bool init(); 
	CREATE_FUNC(HSSeniortSystemLayer);

private:
	void Load();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	void Updata(float dt);

	void CallShop(CCObject* pObj);
	void CallBack(CCObject* pObj);

	//@ Net
	void ResponseFighting(FightingResponse*r);
	void ResponseTargetInfo(TargetInfoResponse*r);
	void ResponseExitAdvanced(ExitAdvancedResponse* pMsg);
};




//Scene
class HSSeniortSystemScene:public CCScene
{
public:
	HSSeniortSystemScene(void);
	~HSSeniortSystemScene(void);
private:
	HSSeniortSystemLayer* hsSeniortSystemLayer;
	HSGameShopLayer* hsGameShopLayer;

public:
	virtual bool init();
	CREATE_FUNC(HSSeniortSystemScene);

	inline HSSeniortSystemLayer* GetHSSeniortSystemLayer(){return this->hsSeniortSystemLayer;};
	inline void SetHSGameShopLayer(HSGameShopLayer* layer)
	{
		this->hsGameShopLayer = layer;
		this->addChild(layer,HS_BASE_TAG,HS_BASE_TAG);
	}
	inline HSGameShopLayer* GetHSGameShopLayer(){return this->hsGameShopLayer;};

};

#endif // __HSSeniortSystemScene_H____