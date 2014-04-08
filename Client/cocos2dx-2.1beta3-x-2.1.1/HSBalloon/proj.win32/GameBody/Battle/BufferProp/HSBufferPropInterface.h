/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/16   17:34
 *	File base:	HSBufferPropInterface.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBufferPropInterface_H__
#define __HSBufferPropInterface_H__
#pragma once
#include "HSTool.h"

typedef bool (CCObject::*BufferBegin)();
typedef bool (CCObject::*BufferEnd)();
#define hs_call_buffer_Begin(__Begin__) (BufferBegin)(&__Begin__)
#define hs_call_buffer_End(__End__) (BufferEnd)(&__End__)

typedef enum
{
	Buffer_Porp_GoldErupt = 1004,		//金币爆发
}HSBufferPropType;


//////////////////////////////////////////////////////////////////////////

class HSBufferPropInterface : public CCNode
{
public:
	HSBufferPropInterface(void);
	~HSBufferPropInterface(void);

private:

	enum HSBufferStart
	{
		BufferStart_Idle,
		BufferStart_Listening,
		BufferStart_LogicBegin,
		BufferStart_LogicEnd,
	};

private:
	CCObject* m_pRecBegin;
	CCObject* m_pRecEnd;

	BufferBegin m_pFuncBegin;
	BufferEnd   m_pFuncEnd;

	HSBufferStart m_bufferStart;

	float m_fDurationTime;
	float m_fTakeTime;

public:
	/** 如果监听到Buffer执行 之后开始执行  LogicBegin*/
	virtual bool LogicBegin(float dt) = 0 ;

	/** 当 LogicBegin返回True的时候执行 */
	virtual bool LogicEnd(float dt) = 0;

	/** 倒计时过程逻辑 */
	virtual bool LogicCountDown(float dt) = 0;

	/** 设置Buffer开始执行条件 */
	virtual void SetListerBufferBegin(CCObject* pRec,BufferBegin isBegin);

	/** 设置Buffer结束以后回调函数 */
	virtual void SetListerBufferEnd(CCObject* pRec,BufferEnd isEnd);

	/** 设置Buffer 持续时间(单位: s) */
	virtual void SetDurationTime(float dt);

	virtual float GetDurationTime();

	virtual void Updata(float dt);

	/** 重置Buffer */
	virtual void Reset();

};

#endif // __HSBufferPropInterface_H____


