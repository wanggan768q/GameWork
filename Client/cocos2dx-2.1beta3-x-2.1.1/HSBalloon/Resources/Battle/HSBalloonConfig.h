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

typedef struct _BallonTestInfo
{
	_BallonTestInfo()
	{
		default();
	}
	void Set(const _BallonTestInfo& config)
	{
		balloonNumber_ = config.balloonNumber_;
		linearVelocity = config.linearVelocity;
		linearDamping_ = config.linearDamping_;
		density_______ = config.density_______;
		friction______ = config.friction______;
		restitution___ = config.restitution___;
	}
	void default()
	{
		balloonNumber_ = 20;
		linearVelocity = 2.f;
		linearDamping_ = 0.5f;

		density_______ = 2.f;
		friction______ = 1.f;
		restitution___ = 0.2f;
	}
	int   balloonNumber_;//气球个数

	float linearVelocity;//上升速度

	float linearDamping_;//上升阻尼

	float density_______;//密度

	float friction______;//摩擦力

	float restitution___;//弹性比例
}BallonTestInfo;


class HSBalloonConfig
{
private:
	HSBalloonConfig(void);
public:
	~HSBalloonConfig(void);
public:
	BallonTestInfo* m_pBallonTestInfo;
	
public:
	static HSBalloonConfig* SharedBallonCofig();

	void Destroy();

	void SaveBallonConfig();

	BallonTestInfo* ReadBallonConfig();

	void RestBallonConfig();

	inline BallonTestInfo* GetBalloonConfigData(){return this->m_pBallonTestInfo;}
};

#endif // __HSBalloonConfig_H____


