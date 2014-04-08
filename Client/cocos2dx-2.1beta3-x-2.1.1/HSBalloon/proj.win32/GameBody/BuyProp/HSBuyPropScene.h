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
#include "HSPropItemSprite.h"
#include "PropInfoData.pb.h"
class HSBuyShopDialog;
class HSBuyPropInfoDialog;
//Layer
class HSBuyPropLayer:public CCLayer
{
public:
	HSBuyPropLayer(void);
	~HSBuyPropLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSBuyPropLayer);

private:
	//HSGameSceneRropManager* m_pHSGameSceneRropManager;
	CCLabelAtlas* m_pGameGold;	//½ð±Ò×Ö
	int m_curpGold;

public:
	CCNode* m_pDialogNode;
	HSBuyShopDialog* m_pBuyShopDialog;
	HSBuyPropInfoDialog* m_pBuyPropInfoDialog;
	bool m_isCloseGuide;
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

	void CallBackMainScene(CCObject* obj);

	void CallShopLayer(CCObject* obj);
	void CallDestoryShop(CCObject* obj);

	void CallPropInfo(CCObject* obj);
	void CallDestoryPropInfo(CCObject* obj);

	void Call_Ok(CCObject* obj);
	void Call_Cancel(CCObject* obj);

	void Call_Buy1(CCObject* obj);
	void Call_Buy2(CCObject* obj);

	void Update(float dt);



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
