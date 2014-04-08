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
	void CallCloudFinish(CCNode*);
	void CallShake();
	 
	void CallCatDownShake();
	void CallCat();
	void CallCatFinish();
	void CallTitleDown();
	void CallTitleDownFinish();
    void Call_Login(CCObject* pObj);
    void Call_LoginType(CCObject* pObj);

    void ResponseRegister( RegisterResponse* r );
    void ResponseLogin(LoginResponse* r);
    
public:
	void Update(float dt);
public:
	//@UI
	CCSprite* m_p_main_cloud1;
	CCSprite* m_p_main_cloud1s;
	CCPoint m_cloud1Position;

	CCSprite* m_p_main_cloud2;
	CCSprite* m_p_main_cloud2s;
	CCPoint m_cloud2Postion;


	CCSprite* m_p_main_cloud3;
	CCSprite* m_p_main_cloud3s;
	CCPoint m_cloud3Postion;

	CCSprite* m_p_main_cloud4;
	CCSprite* m_p_main_cloud4s;
	CCPoint m_cloud4Postion;

	CCSprite* m_p_main_cloud5;
	CCSprite* m_p_main_cloud5s;
	CCPoint m_cloud5Postion;

	CCSprite* m_p_main_catblack1;
	CCPoint m_main_catblack1Position;
	CCSprite* m_p_main_catblack2;
	CCPoint m_main_catblack2Position;

	CCSprite* m_p_main_title;
	CCPoint m_p_main_title_position;

	CCSprite* m_p_main_cat1;
	CCPoint m_p_main_cat1_position;

	CCSprite* m_p_main_cat2;
	CCPoint m_p_main_cat2_position;

	CCSprite* m_p_main_backGround;

	HSCCSprite* m_pb; //±³¾°Í¼
	//@logic
	float m_catblack1count;
	float m_catblack2count;

public:
	static float m_maxcatblack1;
	static float m_maxcatblack2;

	static float m_downMaxCount;
	static float m_downMinCount;

	static float m_cat1MinX;
	static float m_cat1MaxX;

	static float m_cat2MinX;
	static float m_cat2MaxX;
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
