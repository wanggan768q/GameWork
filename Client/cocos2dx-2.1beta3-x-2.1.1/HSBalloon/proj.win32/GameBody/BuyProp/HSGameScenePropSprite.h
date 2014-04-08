/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/04/26   14:18
 *	File base:	HSGameScenePropSprite.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSGameScenePropSprite_H__
#define __HSGameScenePropSprite_H__
#pragma once
#include "HSTool.h"
#include "PropInfo.pb.h"
#include "HSReadUI.h"
#include "HSBuySceneDialog.h"

class HSGameScenePropSprite : public HSGraySprite, public CCTargetedTouchDelegate  
{
public:
	HSGameScenePropSprite(void);
	~HSGameScenePropSprite(void);

private:
	HSCCSprite* m_pPropFirst;
	HSCCSprite* m_pPropMoneyFirst;
	
public:
	message::PropInfo m_PropInfo;

	CCNode* m_pFrameNode;

	HSCCSprite* m_pSelectFrame;

	HSBuySceneDialog* m_pSceneDialog;

	static HSGameScenePropSprite* s_TouchGameScenePropSprite;
	static CCNode* s_lastSelectFrameNode;
	static CCNode* s_lastSelectedGameSceneFrameNode;

public:

	static HSGameScenePropSprite* create(int index);

	static HSGameScenePropSprite* create(const message::PropInfo propInfo ,int index);

	bool Init(int index);

	bool Init(const message::PropInfo propInfo ,int index);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();

	virtual void onExit();

	static HSGameScenePropSprite* GetTouchGameScenePropSprite();

	static void SetTouchGameScenePropSprite(HSGameScenePropSprite* scene);

	void Buy();

	void SetBuy();

	void CallOk(CCObject* obj);

	void CallCancel(CCObject* obj);

	void Update(float dt);
};

#endif // __HSGameScenePropSprite_H____

