/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/16   13:13
 *	File base:	HSGameSelectPropLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGameSelectPropLayer_H__
#define __HSGameSelectPropLayer_H__
#pragma once
#include "HSTool.h"
class HSPropItemSprite;
class HSEquipFrame;

class HSGameSelectPropLayer:public CCLayer
{
public:
	HSGameSelectPropLayer(void);
	~HSGameSelectPropLayer(void);
public:
	//@data
	std::vector<HSPropItemSprite*> m_propItemSpriteArray;
	std::vector<HSEquipFrame*> m_equipFrameArray;
	CCRect rect;
	//@UI
	CCLabelTTF* m_pDescrib;
public:
	virtual bool init(); 
	CREATE_FUNC(HSGameSelectPropLayer);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
	
	void setVisible(bool visible);
public:
	void Load();
public:
	//@logic
	void Close(CCObject* obj);
	bool AddEquip(const PropInfo* prop);
	bool DeleteEquip(const PropInfo* prop);
	void CallLoadData();
public:
	//@Set
	void SetDescrib(const char*);
};
#endif // __HSGameSelectPropLayer_H____