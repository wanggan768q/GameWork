/********************************************************************
 *  Copyright(C) 2014 Ambition_HS ( All rights reserved. )
 *	Created:	14-3-13
 *	File base:	HSChangeFigureScene.h
 *	Author:		Ambition
 *
 *	Purpose:
 *********************************************************************/
#ifndef __HSChangeFigureScene_H__
#define __HSChangeFigureScene_H__
#pragma once
#include "HSTool.h"
#include "HSShowGlobal.h"
#include "HSFigureListView.h"

//Layer
class HSChangeFigureLayer : public CCLayer
{
public:
	HSChangeFigureLayer(void);
	~HSChangeFigureLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSChangeFigureLayer);
    
private:
	void Load();
    void UpdataFigureListView();
    void Call_Back(CCObject* obj);
    void Updata(float dt);
public:
    
    void SetIsShowLoading(bool b);
public:
    void ResponseGameBuyFigure(GameBuyFigureResponse* pMsg);
    void ResponseChangeFigure(ChangeFigureResponse* pMsg);
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
    
private:
    HSFigureListView* m_pListView;
    CCNode* m_pLoding;
    CCMenu* m_pBack;
};




//Scene
class HSChangeFigureScene : public CCScene
{
public:
	HSChangeFigureScene(void);
	~HSChangeFigureScene(void);
private:
	HSChangeFigureLayer* m_pHSChangeFigureLayer;
    
public:
	virtual bool init();
	CREATE_FUNC(HSChangeFigureScene);
    
	inline HSChangeFigureLayer* GetHSChangeFigureLayer(){return this->m_pHSChangeFigureLayer;};
    
};






#endif /* defined(__HSChangeFigureScene_H__) */





