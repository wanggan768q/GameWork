/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/27   16:04
 *	File base:	HSGameDialogLayer.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGameDialogLayer_H__
#define __HSGameDialogLayer_H__
#pragma once
#include "HSTool.h"
#endif // __HSGameDialogLayer_H____

enum DialogType
{
	TYPE_NONO=1,
	TYPE_SINGLE=2,
	TYPE_DOUDLE =3
};
class HSGameDialogLayer:public CCLayer
{
public:
	HSGameDialogLayer(void);
	~HSGameDialogLayer(void);
public:
	virtual bool init(); 
	CREATE_FUNC(HSGameDialogLayer);
public:
	bool Init(DialogType type);
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
	static HSGameDialogLayer* create(DialogType type);
public:
	//@logic
	
	void Close(CCObject*);
	void OK(CCObject*);

	void Conform(CCObject*);
	//@set
	void SetTarget(CCObject* rec,SEL_CallFuncND selector,void* data);
	void SetText(const char*);
public:
	//@
	DialogType m_type;
	//@logic
	CCObject* pTarget;
	SEL_CallFuncND selector;
	void* pData;
	//@show
	const char* m_pText;
	CCLabelTTF* m_pLable;
};

