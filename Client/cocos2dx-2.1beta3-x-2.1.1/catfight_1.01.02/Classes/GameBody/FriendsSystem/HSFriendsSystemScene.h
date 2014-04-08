/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/03   9:53
 *	File base:	HSFriendsSystemScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSFriendsSystemScene_H__
#define __HSFriendsSystemScene_H__
#pragma once
#include "HSTool.h"
#include "HSFriendsListVeiw.h"
#include "HSTableMenu.h"
#include "HSGameShopScene.h"

//Layer
class HSFriendsSystemLayer:public CCLayer
{
public:
	HSFriendsSystemLayer(void);
	~HSFriendsSystemLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSFriendsSystemLayer);

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
    void Call_AddressBook(CCObject* pObj);
    void Call_Email(CCObject* pObj);
    
    //Net
    void ResponseEmail(EmailResponse* pMsg);;
    void ResponseAddressBook(AddressBookResponse* pMsg);

	void Updata(float dt);


private:
	HSFriendsListVeiw* m_pFriendsListView;
	CCLabelAtlas* m_pMoney;
    int m_iMoney;
};




//Scene
class HSFriendsSystemScene:public CCScene
{
public:
	HSFriendsSystemScene(void);
	~HSFriendsSystemScene(void);
private:
	HSFriendsSystemLayer* hsFriendsSystemLayer;
	HSGameShopLayer* hsGameShopLayer;

public:
	virtual bool init();
	CREATE_FUNC(HSFriendsSystemScene);

	inline HSFriendsSystemLayer* GetHSFriendsSystemLayer(){return this->hsFriendsSystemLayer;};

	inline void SetHSGameShopLayer(HSGameShopLayer* layer)
	{
		this->hsGameShopLayer = layer;
		this->addChild(layer,HS_BASE_TAG,HS_BASE_TAG);
	}
	inline HSGameShopLayer* GetHSGameShopLayer(){return this->hsGameShopLayer;};

};
#endif // __HSFriendsSystemScene_H____

