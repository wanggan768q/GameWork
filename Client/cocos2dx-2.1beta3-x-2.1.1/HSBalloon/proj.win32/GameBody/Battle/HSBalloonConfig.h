/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/03/20   14:53
 *	File base:	HSBalloonConfig.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSBalloonConfig_H__
#define __HSBalloonConfig_H__
#pragma once
#include "HSBase.h"
#include "HSTime.h"
#include "HSMath.h"
#include "HSSoundManage.h"

typedef struct _BalloonTestInfo
{
	int   balloonNumber_;//气球个数

	float linearVelocity;//上升速度

	float linearDamping_;//上升阻尼

	float density_______;//密度

	float friction______;//摩擦力

	float restitution___;//弹性比例

	void Reset()
	{
		balloonNumber_ = 20;
		linearVelocity = 2.f;
		linearDamping_ = 0.5f;

		density_______ = 2.f;
		friction______ = 1.f;
		restitution___ = 0.2f;
	}
	
	void Set(const _BalloonTestInfo& config)
	{
		balloonNumber_ = config.balloonNumber_;
		linearVelocity = config.linearVelocity;
		linearDamping_ = config.linearDamping_;
		density_______ = config.density_______;
		friction______ = config.friction______;
		restitution___ = config.restitution___;
	}

	_BalloonTestInfo()
	{
		Reset();
	}
	
}BalloonTestInfo;

typedef enum _BalloonColorType
{
	BALLOON_COLOR_UNKNOW = 0,
	BALLOON_COLOR_BLUE,//蓝色
	BALLOON_COLOR_BROWN,//棕色
	BALLOON_COLOR_GREEN,//绿色
	BALLOON_COLOR_ORANGE,//橙色
	BALLOON_COLOR_PURPLE,//紫色
}BalloonColorType;

typedef enum {
	BALLOON_PROPS_UnKnow = 0x1b,
	BALLOON_PROPS_King,				//皇冠道具
	BALLOON_PROPS_Bomb,				//爆炸道具
	BALLOON_PROPS_Money,			//金币道具
	BALLOON_PROPS_StopStratagemTime,//停止机关时间道具
	BALLOON_PROPS_Fog,				//云雾道具
	BALLOON_PROPS_AddStratagemLevel,//机关等级加1
	BALLOON_PROPS_SubStratagemLevel,//机关等级减1
	BALLOON_PROPS_ChangeColor,		//在指定范围内变色变色
	BALLOON_PROPS_Shield,			//护盾道具
	BALLOON_PROPS_Ink,				//墨汁道具


	BALLOON_PROPS_ChangeColorFullScreen,	//变色龙之眼 全屏随即变色(手动)
	BALLOON_PROPS_Lightning,				//喵之闪电
	BALLOON_PROPS_KingTime,					//喵之恩赐 黄金时间(手动)
	BALLOON_PROPS_StratagemLevelByZero,		//喵酱宽恕
}BalloonPropsType;

typedef enum {
	STRATAGEM_STATE_Stop,
	STRATAGEM_STATE_Up,
	STRATAGEM_STATE_Down,
}StratagemStateType;

#ifndef HS_TEST_MODE
#define HS_TEST_MODE 0
#endif
typedef struct _BalloonGameData
{
	_BalloonGameData()
	{
		Reset();
	}

	void Reset()
	{
		dribbleCount = 0;
		comboCount = 0;
		maxHit = 3;
		dribbleIntervalTime = 0.7f;

		bangBalloonCount = 0;
		playSoundID = 0;

		gameScore = 0;
		//gameGold = 0;
		lastBalloonColorType = BALLOON_COLOR_UNKNOW;
		lastBalloonPropsType = BALLOON_PROPS_UnKnow;

		energy = 0.f;
#if HS_TEST_MODE
		energyMax = 10.f;
#else
		energyMax = 100.f;
#endif

		isFreeEnergy = false;

		stratagemMaxCycleCount = 8;
#if HS_TEST_MODE
		stratagemEachCycleSec = 20;
#else
		stratagemEachCycleSec = 20;
#endif
		stratagemCurCycle = stratagemMaxCycleCount - 1;
		stratagemCurSec = stratagemEachCycleSec;
		lastStratagemLevel = stratagemCurCycle;

		//stratagemRollBackStep = 0;
		stratagemRollBackStepCount = 0;

		isDribbleFail = true;

		//isRunStratagem = false;

		curShowHowColorType = 0;

		//gameCurGold = 0;

		isKingEffect = false;

		isMoneyEffect = false;

		isKingDeath = false;

		m_isPauseStratagemTime = false;

		perEnergyList.clear();

		isShowSuperman = false;

		isListerLastBalloonType = false;

	}

	bool IsEnergyFull()
	{
		return HSMath::EqualsWithFloat(energy,energyMax);
	}


	int dribbleCount;			//连击数
	int comboCount;				//Combo数
	int maxHit;					//每次点中几个算一次连击
	float dribbleIntervalTime;	//每次连击在此间隔时间内算连击

	long bangBalloonCount;		//点爆的气球个数
	int playSoundID;			//当前播放音效ID

	float energy;				//当前能量
	float energyMax;			//最大能量
	bool isFreeEnergy;			//当能量满 是否达到释放要求
	std::vector<float> perEnergyList;	//单次能量增长的值

	int gameScore;	//游戏得分
	//int gameGold;	//金币
	//int gameCurGold;
	BalloonColorType lastBalloonColorType;	//最后一次的颜色类型
	BalloonPropsType lastBalloonPropsType;	//最后一次的道具类型

	int curShowHowColorType;	//当前显示几种类型的气球

	int stratagemMaxCycleCount;		//机关圈数
	int stratagemCurCycle;			//当前是第几圈
	int stratagemEachCycleSec;		//机关每圈代表多少秒
	int stratagemCurSec;			//当前多少秒

	//int stratagemRollBackStep;		//机关回滚步数
	int stratagemRollBackStepCount;	//机关回滚步数量
	bool m_isPauseStratagemTime;	//是否暂停机关倒计时
	int lastStratagemLevel;			//最后一次机关等级


	bool isDribbleFail;			//是否连击失败

	//bool isRunStratagem;		//是否运行机关

	bool isKingEffect;			//是否是皇冠气球

	bool isMoneyEffect;			//是否是金币效果

	bool isKingDeath;			//皇冠气球是否结束

	bool isShowSuperman;		//是否播放超人动画

	bool isListerLastBalloonType;	//是否监听最后一个气球的类型

	BalloonColorType  freeFreeEnergyBalloonType;

}BalloonGameData;

#define HS_GAME_CONFIG() HSBalloonConfig::SharedBalloonCofig()
#define HS_GAME_CONFIG_DATA() HS_GAME_CONFIG()->GetBalloonGameData()
#define HS_GAME_CONFIG_MUTABLE_DATA() HS_GAME_CONFIG()->m_pBGD

class HSBalloonConfig
{
private:
	HSBalloonConfig(void);
public:
	~HSBalloonConfig(void);

private:
	unsigned long long m_lastTime;
	float m_dt;
	int m_stratagemMoveStep;

public:
	BalloonTestInfo* m_pBalloonTestInfo;
	BalloonGameData* m_pBGD;//m_pballoonGameData 简写
	bool m_isPauseUpdate;
	bool m_isOvertime;
	
public:
	static HSBalloonConfig* SharedBalloonCofig();

	void Reset();

	void Destroy();

	void SaveBallonConfig();

	BalloonTestInfo* ReadBalloonConfig();

	void RestBallonConfig();

	inline BalloonTestInfo* GetBalloonConfigData(){return this->m_pBalloonTestInfo;}

	void DribbleLogic(BalloonColorType colorType , int balloonID);

	void Update(float dt);

	void AddEnergy();

	const BalloonGameData* GetBalloonGameData()const;

	void SetLaseTime();

	StratagemStateType GetStratagemStateType();

	int GetStratagemMoveStep();

	void SetStratagemMoveStep(int step);

	void AddStratagemTime(int time);

	void ResetStratagemTime();

	void SetIsPause(bool b);

private:
	void StratagemTimeLogic(float dt);
};

#endif // __HSBalloonConfig_H____


