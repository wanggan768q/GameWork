/********************************************************************
 *  Copyright(C) 2013 Ambition_HS ( All rights reserved. )
 *	Created:	2013/10/17   15:19
 *	File base:	HSJson.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#define HS_USING_HSJson

#ifdef HS_USING_HSJson

#ifndef __HSJson_H__
#define __HSJson_H__
#pragma once
#include "HSBase.h"
#include "HSFileData.h"
#include "json/json.h"
#ifdef WIN32
#pragma comment(lib,"libs/Debug/2012/json_vc71_libmtd.lib")
#endif

class HSJson : public CCObject
{
private:
	HSJson(void);
public:
	~HSJson(void);

private:
	Json::Reader m_reader;
	Json::FastWriter m_fastWriter;
	Json::Value m_root;

public:
	static HSJson* CreateWithFile(const char* pFileName);

	static HSJson* CreateWithData(const void* pData);

	static HSJson* CreateWithWriter();

	bool InitWithFile(const char* pFileName);

	bool InitWithData(const void* pData);

	bool InitWithWriter();

	const Json::Value& GetValue();

	const std::string Writer(const Json::Value& data);
};

#endif // __HSJson_H____


#endif // HS_USING_HSJson





