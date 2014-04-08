/********************************************************************
 *  Copyright(C) 2012 ( All rights reserved. )
 *	Created:	2012/09/25   9:34
 *	File base:	HSAllMessageHead.h
 *	Author:		Ambition
 *	
 *	Purpose:	����API ͷ�ļ�
*********************************************************************/
#ifndef __HSAllMessageHead_H__
#define __HSAllMessageHead_H__
#pragma once

#include "HSMessage.pb.h"
#include "GameLog.pb.h"
#include "BattleData.pb.h"

#include "Register.pb.h"
#include "Login.pb.h"
#include "Fighting.pb.h"
#include "TargetInfo.pb.h"
#include "BattleReady.pb.h"
#include "StartBattle.pb.h"
#include "KickOutDungoen.pb.h"
#include "Playerdisengage.pb.h"
#include "BattleResult.pb.h"
#include "UseBuff.pb.h"
#include "Buff.pb.h"
#include "Heartbeat.pb.h"
#include "GamePing.pb.h"
#include "BattlePing.pb.h"
#include "FriendList.pb.h"
#include "DestroyBalloon.pb.h"
#include "UseProp.pb.h"
#include "SearchUserInfo.pb.h"
#include "Achievement.pb.h"
#include "BattleTranscribeData.pb.h"
#include "AddFriend.pb.h"
#include "RoomData.pb.h"
#include "ClaimedDailyReward.pb.h"
#include "UserInfoUpdate.pb.h"
#include "ErrorMessage.pb.h"
#include "ExitAdvanced.pb.h"
#include "ReceiveAchievementReward.pb.h"
#include "Recharge.pb.h"
#include "AddressBook.pb.h"
#include "Email.pb.h"
#include "OpenEmail.pb.h"
#include "SendEmail.pb.h"
#include "Figure.pb.h"
#include "GameSearchStrength.pb.h"
#include "MatchSearchStrength.pb.h"
#include "GameBuyFigure.pb.h"
#include "GameUpgradeFigureLevel.pb.h"
#include "MatchBuyFigure.pb.h"
#include "MatchUpgradeFigureLevel.pb.h"
#include "NotifyUserUpdate.pb.h"
#include "ChangeFigure.pb.h"
#include "ValidateStrength.pb.h"

#pragma mark - Lan
#include "LanCreateRoom.pb.h"
#include "LanJoinRoom.pb.h"
#include "LanSearchRoom.pb.h"
#include "LanSyncUserInfo.pb.h"
#include "LanBattleReady.pb.h"
#include "LanStartBattle.pb.h"
#include "LanBattleData.pb.h"
#include "LanBattleResult.pb.h"
#include "LanQuitRoom.pb.h"




using namespace message;

#endif // __HSAllMessageHead_H__
