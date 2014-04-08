#include "HSSoundManage.h"


HSSoundManage::HSSoundManage(void)
{
	this->m_currterMusic = "";
	this->m_effectMusic = "";

	m_isPlayMusic = true;
	m_isPlayEffect = true;
    
}

HSSoundManage::~HSSoundManage(void)
{
	Destroy();
}

HSSoundManage* HSSoundManage::ShareSoundManage()
{
	static HSSoundManage s_hsSoundManage;

	return &s_hsSoundManage;
}

void HSSoundManage::Destroy()
{
	this->m_backgroundMusicMap.clear();
	this->m_effectMusicMap.clear();
	SimpleAudioEngine::sharedEngine()->end();
}

std::string HSSoundManage::GetPath(const char* fileName)
{
	std::string funllPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	return funllPath;
}

void HSSoundManage::Load(const char* backgroundMusic,const char* effect)
{
	HSBase::GetDictionary_Key_V__WithFile(backgroundMusic,&this->m_backgroundMusicMap);
	HSBase::GetDictionary_Key_V__WithFile(effect,&this->m_effectMusicMap);

	map<std::string,std::string>::iterator it = this->m_backgroundMusicMap.begin();

	//Ô¤ÏÈ¼ÓÔØ±³¾°ÒôÀÖ
	for (;it!=this->m_backgroundMusicMap.end();++it)
	{
		std::string folder = "music/";
		folder += HS_MUSIC_PLATFORM;
		folder += it->second;
		folder += ".mp3";
		std::string filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(folder.c_str());
		it->second = filePath;
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(filePath.c_str());
		CCLog("Load Music: %s",filePath.c_str());
	}

	//Ô¤ÏÈ¼ÓÔØÒôÐ§
	it = this->m_effectMusicMap.begin();
	for (;it!=this->m_effectMusicMap.end();++it)
	{
		std::string folder = "music/";
		folder += HS_MUSIC_PLATFORM;
		folder += it->second;
		folder += HS_AUDIO_SUFFIX;		
		std::string filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(folder.c_str());
		it->second = folder;
		SimpleAudioEngine::sharedEngine()->preloadEffect(filePath.c_str());
		CCLog("Load Sound: %s",filePath.c_str());
	}
}

void HSSoundManage::PlayMusic(const char* key,bool isLoop /*= true*/)
{
	map<std::string,std::string>::iterator it = this->m_backgroundMusicMap.find(key);
	if(it != this->m_backgroundMusicMap.end())
	{
		m_currterMusic = CCFileUtils::sharedFileUtils()->fullPathForFilename(it->second.c_str());
		if (m_isPlayMusic)
		{
            CCLOG(m_currterMusic.c_str());
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(m_currterMusic.c_str(),isLoop);
		}
	}else{
		//HSMessageBox("[ " + string(key) + " ] " + "Can't find" );
		CCLog(CCString::createWithFormat("\nHS warning: [%s] can't find\n",key)->getCString());
	}
}

void HSSoundManage::PlayerEffect(const char* key,bool isLoop /* = false*/)
{
	map<std::string,std::string>::iterator it = this->m_effectMusicMap.find(key);
	if(it != this->m_effectMusicMap.end())
	{
		m_effectMusic = CCFileUtils::sharedFileUtils()->fullPathForFilename(it->second.c_str());
		if (m_isPlayEffect)
		{
			SimpleAudioEngine::sharedEngine()->playEffect(m_effectMusic.c_str(),isLoop);
		}
	}else{
		//HSMessageBox("[ " + string(key) + " ] " + "Can't find" );
		CCLog(CCString::createWithFormat("\nHS warning: [%s] can't find\n",key)->getCString());
	}
}

void HSSoundManage::Stop()
{
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void HSSoundManage::SetMusicVolume( float volume )
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume / 10.f);	
}

void HSSoundManage::SetEffcetVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume / 10.f);
}

void HSSoundManage::SetIsPlayMusic( bool b )
{
	if (b == false)
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}else{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(m_currterMusic.c_str(),true);
	}
	m_isPlayMusic = b;
}

void HSSoundManage::SetIsPlayEffect( bool b )
{
	if (b == false)
	{
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
	}
	m_isPlayEffect = b;
}

void HSSoundManage::Pause()
{
	//SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

void HSSoundManage::Resume()
{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
