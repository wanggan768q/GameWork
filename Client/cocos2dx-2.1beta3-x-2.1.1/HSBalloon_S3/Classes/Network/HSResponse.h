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
public:
	HSResponse(void);
	~HSResponse(void);
public:
	static HSResponse* ShareResponse();
	void Destroy();

	virtual void HandleFactory(int commandId,google::protobuf::Message* responseMsg);
    
    void HandleError(int id);

};

#endif // __HSResponse_H____
