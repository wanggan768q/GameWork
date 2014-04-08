/********************************************************************
 *  Copyright(C) 2013 Zrong ( All rights reserved. )
 *	Created:	2013/01/22   14:50
 *	File base:	HSSoundManage.h
 *	Author:		Ambition
 *	
 *	Purpose:	
*********************************************************************/
#ifndef __HSSoundManage_H__
#define __HSSoundManage_H__
#pragma once
#include "HSBase.h"

#ifndef HS_MUSIC_PLATFORM
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		#define HS_MUSIC_PLATFORM "win32/"
	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		#define HS_MUSIC_PLATFORM "android/"
	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		#define HS_MUSIC_PLATFORM "ios/"
	#endif
#endif /*HS_MUSIC_PLATFORM*/

#ifndef HS_Play_Music
#define HS_Play_Music(__Music__) HSSoundManage::ShareSoundManage()->PlayMusic(__Music__)
#define HS_Play_Sound(__Sound__) HSSoundManage::ShareSoundManage()->PlayerEffect(__Sound__)
#endif

class HSSoundManage
{
private:
	HSSoundManage(void);
	~HSSoundManage(void);

private:

	//struct _finddata_t
	map<std::string,std::string> m_backgroundMusicMap;
	map<std::string,std::string> m_effectMusicMap;

	std::string m_currterMusic;
	std::string m_effectMusic;

	bool m_isPlayMusic;
	bool m_isPlayEffect;


private:

	/*保留函数 为以后音乐文件下载而设定的*/
	std::string GetPath(const char* fileName);
public:
	static HSSoundManage* ShareSoundManage();

	void Destroy();

	void Load(const char* backgroundMusic,const char* effect);

	void PlayMusic(const char* key,bool isLoop = true);

	void PlayerEffect(const char* key,bool isLoop = false);

	void Stop();

	void Pause();

	void Resume();

	void SetMusicVolume(float volume);

	void SetEffcetVolume(float volume);

	void SetIsPlayMusic(bool b);

	void SetIsPlayEffect(bool b);
};

#endif // __HSSoundManage_H____
