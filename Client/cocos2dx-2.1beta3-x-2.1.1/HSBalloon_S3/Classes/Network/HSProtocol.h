/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/09/18   16:16
 *	File base:	HSProtocol.h
 *	Author:		Ambition
 *	
 *	Purpose:	Э��
*********************************************************************/
#ifndef __HSProtocol_H__
#define __HSProtocol_H__
#pragma once

#define API_ErrorMessageInfo 61000

#define API_RegisterRequest 1001
#define API_RegisterResponse 61001

#define API_LoginRequest 1002
#define API_LoginResponse 61002

//////////////////////////////////////////////////////////////////////////

#define API_FightingRequest 2001
#define API_FightingResponse 62001

#define API_HeartbeatGameRequest 2010
#define API_HeartbeatGameResponse 62010

#define API_SearchUserInfoRequest 2002
#define API_SearchUserInfoResponse 62002

#define API_FriendListRequest 2003
#define API_FriendListResponse 62003

#define API_UserInfoUpdateRequest 2005
#define API_UserInfoUpdateResponse 62005

#define API_ClaimedDailyRewardRequest 2006			
#define API_ClaimedDailyRewardResponse 62006

#define API_AchievementRequest 2007
#define API_AchievementResponse 62007

#define API_ReceiveAchievementRewardRequest 2008
#define API_ReceiveAchievementRewardResponse 62008

#define API_SendEmailRequest 2004
#define API_SendEmailResponse 62004

#define API_EmailRequest 2011
#define API_EmailResponse 62011

#define API_RechargeResponse 62012

#define API_AddressBookRequest 2013
#define API_AddressBookResponse 62013

#define API_OpenEmailRequest 2014
#define API_OpenEmailResponse 62014

#define API_GameBuyFigureRequest 2015      //购买形象
#define API_GameBuyFigureResponse 62015

#define API_GameUpgradeFigureLevelRequest 2016  //形象升级
#define API_GameUpgradeFigureLevelResponse 62016

#define API_GameSearchStrengthRequest 2017  //查询体力
#define API_GameSearchStrengthResponse 62017

#define API_ValidateStrengthRequest 2018  //校验体力值是否大于0
#define API_ValidateStrengthResponse 62018



//////////////////////////////////////////////////////////////////////////

#define API_TargetInfoRequest 3001
#define API_TargetInfoResponse 63001

#define API_BattleReadyRequest 3002
#define API_BattleReadyResponse 63002

#define API_KickOutDungoen 63003

#define API_BattleDataRequest 3004
#define API_BattleDataResponse 63004

#define API_BattleResultRequest 3005
#define API_BattleResultResponse 63005

#define API_PlayerDisengageRequest 3006
#define API_PlayerDisengageResponse 63006

#define API_StartBattle 63007

#define API_UseBuffRequest 3008
#define API_UseBuffResponse 63008

#define API_NotifyChangeBuff 63009

#define API_HeartbeatBattleRequest 3010
#define API_HeartbeatBattleResponse 63010

#define API_DestroyBalloonRequest 3011
#define API_DestroyBalloonResponse 63011

#define API_UsePropRequest 3012
#define API_UsePropResponse 63012

#define API_AddFriendRequest 3013
#define API_AddFriendResponse 63013

#define API_RoomDataRequest 3014
#define API_RoomDataResponse 63014

#define API_ExitAdvancedRequest 3015
#define API_ExitAdvancedResponse 63015

#define API_MatchBuyFigureRequest 3016 //
#define API_MatchBuyFigureResponse 63016

#define API_MatchUpgradeFigureLevelRequest 3017
#define API_MatchUpgradeFigureLevelResponse 63017

#define API_ChangeFigureRequest 3018
#define API_ChangeFigureResponse 63018

#define API_NotifyUserUpdateRequest 3019
#define API_NotifyUserUpdateResponse 63019

#define API_MatchSearchStrengthRequest 3020  //查询体力
#define API_MatchSearchStrengthResponse 63020




/////////////////////////////////////////////////////////////////////////////
//    Lan 协议

#define API_LAN_LanSyncUserInfoNotice   7000
#define API_LAN_LanBattleReadyNotice    7001
#define API_LAN_LanBattleDataNotice     7002
#define API_LAN_LanStartBattleNotify    7003
#define API_LAN_LanBattleResultNotice   7004
#define API_LAN_LanQuitRoomNotice       7005
#define API_LAN_LanUseBufferNotice      7006


















































#endif // __HSProtocol_H__

