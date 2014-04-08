/********************************************************************
*  Copyright(C) 2013 Zrong ( All rights reserved. )
*	Created:	2013/04/26   16:07
*	File base:	HSPropItemSprite.h
*	Author:		Ambition
*	
*	Purpose:	注意拷贝函数  HSPropItemSprite::Copy()
*********************************************************************/
#ifndef __HSPropItemSprite_H__
#define __HSPropItemSprite_H__
#pragma once
#include "HSTool.h"
#include "HSBuySlotDialog.h"
#include "HSReadUI.h"
class HSPropItemSprite;

typedef struct _HSEquipFrame
{
	_HSEquipFrame()
	{
		id = 0;
		frame = NULL;
		isEquip = false;
		equip = NULL;
		isLock = false;
	}
	int id;			//装备槽 id
	HSCCSprite* frame;	//装备道具的Frame 指针 用来隐藏 装备
	bool isEquip;	//是否有装备
	HSPropItemSprite* equip;
	bool isLock;	//是否 锁定

}HSEquipFrame;


class HSPropItemSprite : public HSGraySprite,public CCTargetedTouchDelegate  
{
private:
	HSPropItemSprite(void);
public:
	~HSPropItemSprite(void);

public:
	static CCLabelTTF* s_lastDescribeInfo;
	static CCMenuItemImage* s_lastCCMenuItemImage;
public:
	message::PropInfo m_PropInfo;
	bool m_isCanTouch;
	bool m_isEquip;				//判断当前装备时候安装到 装备槽
	HSPropItemSprite* m_byCopyObj;	//不需要释放
	HSEquipFrame* m_pEuipFrame;		//不需要释放

	CCLabelTTF* m_pDescribeInfo;	//描述
	CCLabelTTF* m_pNumber;          //数量
	int m_curNumber;               //当前数量
	 
	CCSize m_describePaneSize;
public:
	static HSPropItemSprite* create(int index);

	static HSPropItemSprite* create(const message::PropInfo propInfo ,int index);

	bool Init(int index);

	bool Init(const message::PropInfo propInfo,int index);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();

	virtual void onExit();

	void Update(float dt);

	HSPropItemSprite* Copy();

	void SetCopyObj(HSPropItemSprite* item);

	void SetEquipFrame(HSEquipFrame* frame);

	void SetIsEquip(bool is);

	void SetDescribeInfo(CCLabelTTF* pDescribeInfo);

	void SetNumber(CCLabelTTF* pNumber);

	void CallPropDialog(CCObject* obj);
};



//////////////////////////////////////////////////////////////////////////

class HSGameEquipManager : public CCNode
{
public:
	HSGameEquipManager();
	~HSGameEquipManager();
private:
	std::vector<HSEquipFrame> m_EquipFrameList;
public:
	static int m_iMaxEquipCount;	//最大装备数量
	static int m_iYetEquipCount;	//已经装备数量
public:
	 
	HSBuySlotDialog* m_dialog;
public:
	static HSGameEquipManager* create();

	bool Init();

	void Update(float dt);

	void CallLock(CCObject* obj);	//道具锁按钮回调

	static bool GetIsCanEquip();

	void CallBattleScene(CCObject* obj);

	void SaveEquipProp();

	void CallOk(CCObject* obj);

	void CallCancle(CCObject* obj);

	 

};







#endif // __HSPropItemSprite_H____

