/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/10/22   11:12
 *	File base:	HSResponse.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSResponse_H__
#define __HSResponse_H__
#pragma once
#include "HSFilter.h"
#include "HSProtocol.h"

class HSResponse
{
private:
	HSResponse(void);
public:
	~HSResponse(void);
public:
	static HSResponse* ShareResponse();
	void Destroy();

	void HandleFactory(int commandId,google::protobuf::Message* responseMsg);
    
    void HandleError(int id);
public:





};

#endif // __HSResponse_H____
