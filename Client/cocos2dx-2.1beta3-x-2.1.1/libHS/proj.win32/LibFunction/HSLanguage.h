/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/18   8:57
 *	File base:	HSLanguage.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSLanguage_H__
#define __HSLanguage_H__
#pragma once
#include "HSBase.h"
#include "HSStructure.h"

#ifndef L
#define L(__Key__) HSLanguage::ShaderLanguage()->Find(__Key__)
#endif // !L


class HSLanguage
{
public:
	HSLanguage(void);
	~HSLanguage(void);

private:
	LanguageData* m_pLanguageData;

	std::map<std::string,std::string> m_LanguageMap;

public:

	static HSLanguage* ShaderLanguage();

	void Read(const char* fileName,const char* currentLanguage);

	const char* Find(const char* key);
};

#endif // __HSLanguage_H____


