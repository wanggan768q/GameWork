/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/13   11:30
 *	File base:	HSGameMainScene.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGameMainScene_H__
#define __HSGameMainScene_H__
#pragma once
#include "HSTool.h"

class HSGameMainLayer:public CCLayer
{
public:
	HSGameMainLayer(void);
	~HSGameMainLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSGameMainLayer);
	
private:
	void Load();

public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
    
public:
    void MicroblogLogin();

public:
    void Call_Login(CCObject* pObj);
    void Call_LoginType(CCObject* pObj);
    void Call_LAN(CCObject* pobj);

    void ResponseRegister( RegisterResponse* r );
    void ResponseLogin(LoginResponse* r);
    void ResponseSearchStrength(GameSearchStrengthResponse* pMsg);
    
    void ListerSearchRoomFinish(float dt);
    void ListerOnce(float dt);
    
    void Call_Test(CCNode* pNode);
    
public:
	void Update(float dt);
public:
    
    
    //@ Lan
    bool m_isSearchRoomFinsh;

};












//Scene
class HSGameMainScene:public CCScene
{
public:
	HSGameMainScene(void);
	~HSGameMainScene(void);
private:
	HSGameMainLayer* hsGameMainLayer;
public:
	virtual bool init();
	CREATE_FUNC(HSGameMainScene);

	inline HSGameMainLayer* GetHSGameMainLayer(){return this->hsGameMainLayer;};
};


#endif // __HSGameMainScene_H____
