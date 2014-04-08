/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/10/22   11:13
 *	File base:	HSRequest.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSRequest_H__
#define __HSRequest_H__
#pragma once
#include "HSFilter.h"

#define HS_FILTER_REQUEST(request) HSFilter::ShareFilter()->CreaterMessage((::google::protobuf::Message*)request)

class HSRequest
{
private:
	HSRequest(void);
public:
	~HSRequest(void);

public:
	static HSRequest* ShareRequest();
	void Destroy();

public:
	void SendRegisterRequest(const char* userName);

	void SendSearchRankRequest();

	void SendCombatGainsRequest(unsigned int score);

	void SendSearchWeeklyScoreRequest();

	void SendLogRequest(LogRequest* pLogRequest);

	
};


#endif // __HSRequest_H____
