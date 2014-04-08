#include "HSBattleTranscribe.h"


HSBattleTranscribe::HSBattleTranscribe(void)
{
    m_isVideo = false;
	m_pBattleTranscribeDataList = BattleTranscribeDataList::default_instance().New();
}


HSBattleTranscribe::~HSBattleTranscribe(void)
{
	CC_SAFE_DELETE(m_pBattleTranscribeDataList);
}

bool HSBattleTranscribe::init()
{
    string videoConfig = HS_Find_Configure("Isvideo");
    if (videoConfig == "1")
    {
        m_isVideo = true;
    }
	return true;
}

void HSBattleTranscribe::AddFrame( const BattleInfo& battleInfo )
{
    if(!m_isVideo)
    {
        return;
    }
	BattleInfo* tempbattleInfo = m_pBattleTranscribeDataList->add_battleinfo();
	tempbattleInfo->CopyFrom(battleInfo);
}

void HSBattleTranscribe::Save()
{
    if(!m_isVideo)
    {
        return;
    }
    
    //CCString* pFileName = CCString::createWithFormat("%d%02d%2d%2d%2d%2d.bid",HSTime::GetYear(),HSTime::GetMonth(),HSTime::GetToday(),HSTime::GetHour(),HSTime::GetMinute(),HSTime::GetSec());
    CCString* pFileName = CCString::createWithFormat("%s.bid",HSTime::GetTime());
	std::string fileName = pFileName->getCString();
    std::string path = CCFileUtils::sharedFileUtils()->getWriteablePath() + fileName;
    
    FILE *pFile = NULL;
	HS_fopen(pFile,path.c_str(),"wb+");
	if (pFile != NULL)
    {
		int size = m_pBattleTranscribeDataList->GetCachedSize();
		std::string data = m_pBattleTranscribeDataList->SerializeAsString();
		size = data.length();
		fwrite(data.c_str(),1,size,pFile);
		CCLog(CCString::createWithFormat("Save [ %s ] success",fileName.c_str())->getCString());
	}
	fclose(pFile);
	pFile = NULL;
    
    HSMessageBox("Save [ %s ] success",fileName.c_str());
    
    pFileName->release();
}
