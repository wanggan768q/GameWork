/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/09/03   9:53
 *	File base:	HSAddressBookScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSAddressBookScene_H__
#define __HSAddressBookScene_H__
#pragma once
#include "HSTool.h"
#include "HSAddressBookListVeiw.h"
#include "HSTableMenu.h"
#include "HSGameShopScene.h"

//Layer
class HSAddressBookLayer:public CCLayer
{
public:
	HSAddressBookLayer(void);
	~HSAddressBookLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSAddressBookLayer);

private:
	void Load();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	void Call_Back(CCObject* pObj);

	void Updata(float dt);


private:
	HSAddressBookListVeiw* m_pFriendsListView;
};




//Scene
class HSAddressBookScene:public CCScene
{
public:
	HSAddressBookScene(void);
	~HSAddressBookScene(void);
private:
	HSAddressBookLayer* hsAddressBookLayer;
	HSGameShopLayer* hsGameShopLayer;

public:
	virtual bool init();
	CREATE_FUNC(HSAddressBookScene);

	inline HSAddressBookLayer* GetHSAddressBookLayer(){return this->hsAddressBookLayer;};

};
#endif // __HSFriendsSystemScene_H____

