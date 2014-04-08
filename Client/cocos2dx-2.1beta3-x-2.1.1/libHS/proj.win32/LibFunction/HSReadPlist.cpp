#include "HSReadPlist.h"

HSReadPlist::HSReadPlist(void)
{
}

HSReadPlist::~HSReadPlist(void)
{
	Destroy();
}

HSReadPlist* HSReadPlist::ShareReadPlist()
{
	static HSReadPlist s_hsReadPlist;

	return &s_hsReadPlist;
}

void HSReadPlist::Open(const char* plistFileName,const char* plistPng)
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFileName,plistPng);
	m_plistNameList.insert(std::string(plistFileName));
}

CCSpriteFrame* HSReadPlist::GetSpriteFrameWithKey(const char* key)
{
	CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key);
	return frame != NULL ? frame : NULL;
}

HSCCSprite* HSReadPlist::CreateSpriteWithKey(const char* key)
{
	CCSpriteFrame* pSpriteFrame = GetSpriteFrameWithKey(key);
	//CCRect rect = pSpriteFrame->getRect();
	HSAssert(pSpriteFrame,"pSpriteFrame == NULL");
	//CCSprite* pSprite = CCSprite::spriteWithSpriteFrame(pSpriteFrame);
	HSCCSprite* pSprite = HSCCSprite::create(pSpriteFrame);
	//pSprite->setContentSize(rect.size);
	return pSprite;
}

void HSReadPlist::Destroy()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->purgeSharedSpriteFrameCache();
}

bool HSReadPlist::Close( const char* plistFilename )
{
	std::set<std::string>::iterator it = m_plistNameList.find(plistFilename);
	if (it == m_plistNameList.end())
	{
		return false;
	}
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile((*it).c_str());
	return true;
}

bool HSReadPlist::CloseAllPlist()
{
	std::set<std::string>::reverse_iterator rit = m_plistNameList.rbegin();
	for (;rit != m_plistNameList.rend();++rit)
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile((*rit).c_str());
	}
	m_plistNameList.clear();

	return true;
}
