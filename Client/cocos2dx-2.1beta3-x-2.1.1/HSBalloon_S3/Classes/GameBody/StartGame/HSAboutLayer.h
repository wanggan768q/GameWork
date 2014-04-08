#ifndef __HSAboutLayer__H__
#define __HSAboutLayer__H__
#pragma once
#include "HSTool.h"
class HSAboutLayer :public CCLayer
{
public:
	HSAboutLayer(void);
	~HSAboutLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(HSAboutLayer);

	static HSAboutLayer* ShareHSAboutLayer();
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

	void CallReturn_About();
	void CallMore_About();
};
#endif
