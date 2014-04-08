#include "HSBattleTranscribe.h"


HSBattleTranscribe::HSBattleTranscribe(void)
{
	m_pBattleTranscribeDataList = BattleTranscribeDataList::default_instance().New();
}


HSBattleTranscribe::~HSBattleTranscribe(void)
{
	CC_SAFE_DELETE(m_pBattleTranscribeDataList);
}

bool HSBattleTranscribe::init()
{
	return true;
}

void HSBattleTranscribe::AddFrame( const BattleInfo& battleInfo )
{
	BattleInfo* tempbattleInfo = m_pBattleTranscribeDataList->add_battleinfo();
	tempbattleInfo->CopyFrom(battleInfo);
}

void HSBattleTranscribe::Save()
{
	std::string fileName = CCString::createWithFormat("%d%02d%2d%2d%2d%2d.bid",HSTime::GetYear(),HSTime::GetMonth(),HSTime::GetToday(),HSTime::GetHour(),HSTime::GetMinute(),HSTime::GetSec())->getCString();
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
}
