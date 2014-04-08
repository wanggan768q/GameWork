/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/07/24   10:16
 *	File base:	HSJni.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSJni_H__
#define __HSJni_H__
#pragma once

#include "HSBase.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif



class HSJni
{
public:
	HSJni(void);
	~HSJni(void);

private:

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo m_minfo;
#endif

	std::string m_returnType;

private:
	const char* FormatType(const char* C_type);

	std::string FormatReturnType(const char* C_type);

	std::string FormatParameter(const char* C_parameter);

	std::vector<std::string> Split(const char* str,const char* format);

public:

	bool LoadStaticClass(const char* javaClass,const char* C_ReturnType,const char* functionName,const char* parameter,const std::string& buffer);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	static jstring StrToJstring(JNIEnv* env, const char* pStr);

	static jbyteArray StringToJByteArray(JNIEnv* env,const char* buffer);

	static const char* JByteArrayToCharArray(JNIEnv* env,jbyteArray buffer);
#endif

};

#endif // __HSJni_H____


