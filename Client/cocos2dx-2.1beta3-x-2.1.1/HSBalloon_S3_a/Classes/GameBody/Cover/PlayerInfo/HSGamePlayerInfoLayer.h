/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/09/05   16:46
 *	File base:	HSGamePlayerInfoLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGamePlayerInfoLayer_H__
#define __HSGamePlayerInfoLayer_H__
#pragma once
#include "HSTool.h"
class HSPlayerInfoListView;
class HSGamePlayerInfoLayer:public CCLayer
{
public:
	HSGamePlayerInfoLayer(void);
	~HSGamePlayerInfoLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSGamePlayerInfoLayer);

	static HSGamePlayerInfoLayer* SharedPlayerInfoLayer();
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
	void CallReturn(CCObject*);
	void CallChangeHead(CCObject*);
	void CloseChangeHead(CCObject*);
	void CloseChangeHead(CCNode* ,void* data);
public:
	//@update
	void Update(float dt);
public:
	//ui
	void PL_FlyIn(CCNode&,CCPoint&);
	void PL_FlyOut(CCNode& ppanle,CCPoint& pposition);
	void PL_FlyInFinish();
	void PL_FlyOutFinish();
private:
	//@UI
	HSPlayerInfoListView* m_pPlayerInfoListView;
	CCSprite* m_pHead;
	int m_iconId;
	CCNode* m_ppanle;
	CCPoint m_panlePosition;

	CCNode* m_pHeadPanle;

	CCLayer* m_p_foreLayer;
	CCSprite* m_p_background;

	bool m_flyin;
	 
};


#endif // __HSGamePlayerInfoLayer_H____




