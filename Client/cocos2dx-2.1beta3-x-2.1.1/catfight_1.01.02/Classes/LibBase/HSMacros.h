/********************************************************************
 *  Copyright(C) 2012 Zrong ( All rights reserved. )
 *	Created:	2012/11/20   16:13
 *	File base:	HSMacros.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSMacros_H__
#define __HSMacros_H__

#include "cocos2d.h"
using namespace cocos2d;

#ifndef HSAssert
#define HSAssert(__cond__ , __msg__) \
{ \
	if((__cond__) == false) \
	{ \
		CCLog("HSAssert:-------------------------------------------"); \
		CCLog("HSAssert: error: - %s - %s (%d)",__msg__,__FUNCTION__,__LINE__); \
		CCLog("HSAssert:-------------------------------------------"); \
		std::string __INFO__ = std::string(__msg__) + "\n" + std::string(__FUNCTION__); \
		CCMessageBox(__INFO__.c_str()," HSAssert "); \
	} \
    assert(__cond__); \
}
#endif /*HSAssert*/


#ifndef HSPlatform
#define HSPlatform
#define HSWin32     (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define HSAndroid   (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define HSIos       (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif


#ifndef HS_UI_TYPE
#define HS_UI_TYPE
	typedef enum{
		UI_TYPE_Sprite = 0xa1,
		UI_TYPE_Panel,
		UI_TYPE_Menu,
		UI_TYPE_Spx,
	}HSUiType;
#endif /*HS_UI_TYPE*/

#ifndef HS_BASE_TAG
#define HS_BASE_TAG 100
#endif

#ifndef HS_AUDIO_SUFFIX
	#define HS_AUDIO_SUFFIX ".mp3"
// 	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
// 		#define HS_AUDIO_SUFFIX ".mp3"
// 	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// 		#define HS_AUDIO_SUFFIX ".ogg"
// 	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// 		#define HS_AUDIO_SUFFIX ".caf"
// 	#endif

#endif /*HS_AUDIO_SUFFIX*/

#ifndef HS_CONTENT_SCALE
#define HS_CONTENT_SCALE CCDirector::sharedDirector()->getContentScaleFactor()
#endif /*HS_CONTENT_SCALE*/


#define HS_ANCHOR_CENTER ccp(0.5f,0.5f)
#define HS_ANCHOR_LD ccp(0.f,0.f)
#define HS_ANCHOR_LU ccp(0.f,1.f)
#define HS_ANCHOR_L_CENTER ccp(0.f,0.5f)
#define HS_ANCHOR_RD ccp(1.f,0.f)
#define HS_ANCHOR_RU ccp(1.f,1.f)
#define HS_ANCHOR_R_CENTER ccp(1.f,0.5f)
#define HS_ANCHOR_U_CENTER ccp(0.5f,1.f)
#define HS_ANCHOR_D_CENTER ccp(0.5f,0.f)

#ifndef HS_PTM_RATIO
#define HS_PTM_RATIO 32.f
#endif

#ifndef HS_SizeHalf
#define HS_SizeHalf_Point(__CCSize__) ccp(__CCSize__.width / 2.f,__CCSize__.height / 2.f)
#define HS_SizeHalf_Size(__CCSize__) CCSizeMake(__CCSize__.width / 2.f,__CCSize__.height / 2.f)
#endif // !HS_SizeHalf



#ifndef HS_fopen
	#if WIN32
		#define HS_fopen(__pFile__ , __fileName__ , __mode__) fopen_s(&__pFile__,__fileName__,__mode__)
	#else
		#define HS_fopen(__pFile__ , __fileName__ , __mode__) __pFile__=fopen(__fileName__,__mode__)
	#endif
#endif /*HS_FOPEN*/

#ifndef HS_BLEND_SRC_DST_FUNC
#define HS_BLEND_SRC_DST_FUNC(__Obj__) \
	{ \
		ccBlendFunc func; \
		func.src = CC_BLEND_SRC; \
		func.dst = CC_BLEND_DST; \
		(__Obj__)->setBlendFunc(func); \
	}
	
#endif



#endif // __HSMacros_H____
// #pragma once
// 
// class HSMacros
// {
// public:
// 	HSMacros(void);
// 	~HSMacros(void);
// };
