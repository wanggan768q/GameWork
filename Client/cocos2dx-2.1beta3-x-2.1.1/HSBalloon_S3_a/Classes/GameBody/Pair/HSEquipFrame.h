/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/08/19   14:50
 *	File base:	HSEquipFrame.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSEquipFrame_H__
#define __HSEquipFrame_H__
#pragma once
#include "HSTool.h"
class HSEquipFrame : public HSGraySprite,public CCTargetedTouchDelegate
{
public:
	HSEquipFrame();  
	~HSEquipFrame();
public:
	//@data
	const PropInfo* m_pFrameInfo;
	const PropInfo* m_pPropInfo;
	//@UI
	CCSprite* m_pPropSprite;
	CCSprite* m_pLockSprite;
	CCLabelTTF* m_pDescrib;
	CCSprite* m_pBell;
	CCSprite* m_frame;
	//@logic
	float m_frame_scaleX;
	float m_frame_scaleY;

	bool m_lock;
	bool m_equip;
	bool m_buy;
	int m_index;
public:
	static HSEquipFrame* create(const message::PropInfo& frameInfo,int index);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();
	bool Init(const message::PropInfo& frameInfo,int index);
	bool SetPropInfo(const message::PropInfo& propInfo);
public:
	//@logic
	void Delete();
	void Lock();
	void NeedBuy();
	void Open();
public:
	//@update
	void Update(float dt);
};

class HSEquipManager
{
public:
	HSEquipManager();  
	~HSEquipManager();
public:


};
#endif // __HSEquipFrame_H____
