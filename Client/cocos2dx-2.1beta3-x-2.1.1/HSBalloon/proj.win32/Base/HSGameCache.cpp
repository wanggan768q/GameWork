#include "HSGameCache.h"
#include "PropInfoData.pb.h"
HSGameCache::HSGameCache(void)
{
	m_pUseBufferPropData = NULL;

 

	string fullFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Data/PropInfo.data");

	HSFileData data(fullFilePath.c_str(),"rb");

	m_pPropInfoData = message::PropInfoData::default_instance().New();

	bool isOk = m_pPropInfoData->ParsePartialFromArray((const void*)(data.GetBuffer() + 2) ,data.GetSize() - 2);

	if (!isOk)
	{
		HSMessageBox("Data/PropInfo.data     Error");
				 
		CC_SAFE_DELETE(m_pPropInfoData);
	}

	m_pGameCacheData = message::GameCacheData::default_instance().New();

	this->Read();
}


HSGameCache::~HSGameCache(void)
{
	CC_SAFE_DELETE(m_pPropInfoData);
}

HSGameCache* HSGameCache::ShareGameCache()
{
	static HSGameCache s_hsGameCache;
	return &s_hsGameCache;
}

void HSGameCache::Destroy()
{
	this->Save();
	CC_SAFE_DELETE(m_pGameCacheData);
}

bool HSGameCache::AddGold( int useNum )
{
	int gold = m_pGameCacheData->gold();

	gold += useNum;

	if (gold < 0)
	{
		HSMessageBox("Gold is not enough");
		return false;
	}

	m_pGameCacheData->set_gold(gold);

	this->Save();

	return true;
}

void HSGameCache::SetGold(int num)
{
	m_pGameCacheData->set_gold(num);
}

void HSGameCache::AddHistoryScore( unsigned int score )
{
	if (score == 0)
	{
		return;
	}
	if (m_pGameCacheData->maxhighestscore() < score)
	{
		m_pGameCacheData->set_maxhighestscore(score);
	}
	m_pGameCacheData->add_historyscorelist(score);
	this->Save();
}

void HSGameCache::ClearHistoryScoreList()
{
	m_pGameCacheData->clear_historyscorelist();
	this->Save();
}

void HSGameCache::AddUseProp( const message::PropInfo& info,int postion )
{
	message::PropInfo* usePro = m_pGameCacheData->add_useproplist();
	usePro->CopyFrom(info);
	usePro->set_pos(postion);
}

int HSGameCache::GetHistoryScore()
{
	return m_pGameCacheData->maxhighestscore();
}

bool HSGameCache::IsPropSlotLock(int index)
{
	return m_pGameCacheData->propslotlock(index);
}

void HSGameCache::SetIsPropSlotLock(bool b,int index)
{
	m_pGameCacheData->set_propslotlock(index,b);
}

bool HSGameCache::IsLevelLock(int index)
{
	return m_pGameCacheData->levellock(index);
}

void HSGameCache::SetIsLevelLock(int index,bool b)
{
	m_pGameCacheData->set_levellock(index,b);
}

void HSGameCache::SetPropNumber(int index,int number)
{
	m_pGameCacheData->mutable_propcachedata()->mutable_propcache(index)->set_number(number);
	this->Save();
}

int HSGameCache::GetPropNumber(int index)
{
	return m_pGameCacheData->propcachedata().propcache(index).number();
}

void HSGameCache::SetPropUseFrequency(const int& index,const int& frequency)
{
	m_pGameCacheData->mutable_propcachedata()->mutable_propcache(index)->set_usefrequency(frequency);
}

int HSGameCache::GetPropUseFrequency(const int& index)
{
	return m_pGameCacheData->propcachedata().propcache(index).usefrequency();
}

int HSGameCache::GetPropUseFrequencyByLevel(const int& level)
{
	int lv =(int)10* pow(2.0f,level-1);
	return lv;
}

void HSGameCache::SetPropLevel(const int& index,const int& level)
{
	m_pGameCacheData->mutable_propcachedata()->mutable_propcache(index)->set_level(level);
}

const int HSGameCache::GetPropLevel(const int& index)
{
	return m_pGameCacheData->propcachedata().propcache(index).level();
}

void HSGameCache::SetPropIndex(const int& index)
{
	m_pGameCacheData->mutable_propcachedata()->set_propindex(index);
}

const int HSGameCache::GetPropIndex()
{
	return m_pGameCacheData->propcachedata().propindex();
}

void HSGameCache::SetLastTime(const long long& lastTime)
{
	m_pGameCacheData->mutable_propcachedata()->set_lasttime(lastTime);
}

const long long HSGameCache::GetLastTime()
{
	return m_pGameCacheData->propcachedata().lasttime();
}

int HSGameCache::GetUseBackgroundID()
{
	return m_pGameCacheData->usebackgroundid();
}

void HSGameCache::SetUseBackgroundID( unsigned int id )
{
	m_pGameCacheData->set_usebackgroundid(id);
}

int HSGameCache::GetGold()
{
	return m_pGameCacheData->gold();
}

const message::GameCacheData* HSGameCache::GetGameCacheData()
{
	return m_pGameCacheData;
}

message::GameCacheData* HSGameCache::GetMutableGameCacheData()
{
	return m_pGameCacheData;
}

const message::PropInfoData* HSGameCache::GetPropInfoData()
{
	return m_pPropInfoData;
}

bool HSGameCache::Save()
{
	string path;
	path = CCFileUtils::sharedFileUtils()->getWriteablePath() + HS_GAME_CACHE_FILE_NAME;

	FILE *pFile = NULL;
	HS_fopen(pFile,path.c_str(),"wb+");
	if (pFile != NULL)
	{
		int size = m_pGameCacheData->GetCachedSize();
		string data = m_pGameCacheData->SerializeAsString();
		size = data.length();
		fwrite(data.c_str(),1,size,pFile);
		fclose(pFile);
		CCLog("Save game cache success");
		return true;
	}
	HSMessageBox("Save game cache Fail");
	return false;
}

bool HSGameCache::Read()
{
	std::string path = CCFileUtils::sharedFileUtils()->getWriteablePath() + HS_GAME_CACHE_FILE_NAME;

	FILE *pFile = NULL;
	HS_fopen(pFile,path.c_str(),"rb");
	if (pFile != NULL)
	{
		m_pGameCacheData->Clear();

		fseek(pFile, 0, SEEK_END);
		long fileSize = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);
		char* buffer = new char[fileSize];
		memset(buffer,0,fileSize);
		fread(buffer,fileSize,1,pFile);
		fclose(pFile);
		bool isOK = m_pGameCacheData->ParsePartialFromArray(buffer,fileSize);
		CC_SAFE_DELETE_ARRAY(buffer);


		long long lastTime = this->GetLastTime();//上次的时间
		int index = this->GetPropIndex();//上次的索引
		long long mmTIme = HSTime::GetLocalityTimeAccurate();
		if(mmTIme>lastTime+7*24*60*60*1000)
		{
			if(index>=3)
			{
				index =0;
			}
			else
			{
				index+=1;
			}
			 
			this->SetPropIndex(index);
			this->SetLastTime(mmTIme);
			this->Save();
		}

		m_pGameCacheData->clear_useproplist();

		if (isOK)
		{
			CCLog("Read game cache success");
			return true;
		}

		

	}
	else//说明没有本地存储，先存一个默认的进去
	{
		m_pGameCacheData->set_imei(HSTool::ShareHSTool()->GetUUID());

		for(int i=0; i < 4; i++)
		{
			if(i ==0)
			{
				m_pGameCacheData->add_propslotlock(false);
			}
			else
			{
				m_pGameCacheData->add_propslotlock(true);
			}
		}

		for(int i =0; i < 3; i++)
		{
		 
			m_pGameCacheData->add_levellock(true);
			 
		}

		this->SetLastTime(HSTime::GetLocalityTimeAccurate());

		this->SetPropIndex(0);
		

		GameCacheData_PropCacheData*  propCacheData =  m_pGameCacheData->mutable_propcachedata();

		for(int i=0; i<4; i++)
		{
			GameCacheData_PropCache* propCache = propCacheData->add_propcache();

			propCache->set_number(1);
			
			propCache->set_level(1);

			propCache->set_usefrequency(this->GetPropUseFrequencyByLevel(1));
		}

		Save();
	}
	//HSMessageBox("Read game cache Fail");
	return false;
}

void HSGameCache::AddBoughtBackgroundID( unsigned int id )
{
	for (int i=0;i<m_pGameCacheData->boughtbackgroundid_size();++i)
	{
		if (m_pGameCacheData->boughtbackgroundid(i) == id)
		{
			return;
		}
	}
	m_pGameCacheData->add_boughtbackgroundid(id);
}

void HSGameCache::SetIsOpenBackgroundMusic( bool b )
{
	m_pGameCacheData->set_isbackgroundmusic(b);
	this->Save();
}

void HSGameCache::SetIsOpenIsSound( bool b )
{
	m_pGameCacheData->set_issound(b);
	this->Save();
}

int HSGameCache::AddHistoryFiveHighestScore( unsigned int score )
{
	unsigned int saveScore = score;
	int reviseIndex = -1;

	if (m_pGameCacheData->historyfivehighestscorelist_size() < 5)
	{

		m_pGameCacheData->add_historyfivehighestscorelist(score);

	}else{

		int count = m_pGameCacheData->historyfivehighestscorelist_size();
		for (int i=0;i<count;++i)
		{
			unsigned int tempScore = m_pGameCacheData->historyfivehighestscorelist(i);
			if (tempScore < score)
			{
				m_pGameCacheData->set_historyfivehighestscorelist(i,score);
				score = tempScore;
			}
		}
	}

	//排序
	int count = m_pGameCacheData->historyfivehighestscorelist_size();
	//unsigned int tempScore = 0;
	for(int i=0;i<count;i++)
	{
		for(int j=0;j<count-i-1;j++)
		{
			unsigned int begin = m_pGameCacheData->historyfivehighestscorelist( j );
			unsigned int end = m_pGameCacheData->historyfivehighestscorelist( j + 1);
			if(begin < end)
			{
				m_pGameCacheData->set_historyfivehighestscorelist( j ,end);
				m_pGameCacheData->set_historyfivehighestscorelist( j + 1,begin);
			}
		}
	}

	for(int i=0;i<count;i++)
	{
		unsigned int tempScore = m_pGameCacheData->historyfivehighestscorelist(i);
		if (tempScore == saveScore)
		{
			reviseIndex = i;
		}
	}
	const int maxCount = 5;
	if (reviseIndex >= maxCount)
	{
		HSMessageBox("Overflow error   MaxCount = 5");
		return -1;
	}

	this->Save();

	return reviseIndex;
}

void HSGameCache::AddFiveDayScore( unsigned int score )
{
	unsigned long long today = HSTime::GetToday();

	const int maxCount = 5;
	int count = m_pGameCacheData->fivedayscorelist_size();

	if (count == 0)
	{
		GameCacheData_DayScore* addDayScore = m_pGameCacheData->add_fivedayscorelist();
		addDayScore->set_key(today);
		addDayScore->set_score(score);
		return;
	}

	if (count != 0 && count <= maxCount)
	{
		int index = count - 1;
		GameCacheData_DayScore* dayScore = m_pGameCacheData->mutable_fivedayscorelist(index);
		if (dayScore->key() == today)
		{
			unsigned long long sum = m_pGameCacheData->fivedayscorelist(index).score() + score;
			dayScore->set_score(sum);
		}else{
			GameCacheData_DayScore* addDayScore = m_pGameCacheData->add_fivedayscorelist();
			addDayScore->set_key(today);
			addDayScore->set_score(score);
		}
	}

	count = m_pGameCacheData->fivedayscorelist_size();
	if (count > maxCount)
	{
		for (int i=0;i<count-1;++i)
		{
			m_pGameCacheData->mutable_fivedayscorelist()->SwapElements(i,i + 1);
		}
		m_pGameCacheData->mutable_fivedayscorelist()->RemoveLast();
	}

	count = m_pGameCacheData->fivedayscorelist_size();

	this->Save();

#pragma region 打印当前存的哪几天的分数
#if 0
	CCLog("----------------------------------------------------------");
	for (int i=0;i<count;++i)
	{
		CCLog("%ld",m_pGameCacheData->fivedayscorelist(i).key());
	}
#endif
#pragma endregion 打印当前存的哪几天的分数

}

void HSGameCache::SetWorldRankData( SearchRankResponse* pMsg )
{
	unsigned long long today = HSTime::GetToday();

	m_pGameCacheData->clear_worldrankdata();

	GameCacheData_WorldRankData* pWorldData = m_pGameCacheData->mutable_worldrankdata();
	pWorldData->set_key(today);
	SearchRankResponse* pData = pWorldData->mutable_data();
	pData->CopyFrom(*pMsg);

	this->Save();
}

void HSGameCache::SetWeekRankData( SearchWeeklyScoreResponse* pMsg )
{
	unsigned long long today = HSTime::GetToday();

	m_pGameCacheData->clear_weekrankdata();

	GameCacheData_WeekRankData* pWeekData = m_pGameCacheData->mutable_weekrankdata();
	pWeekData->set_key(today);
	SearchWeeklyScoreResponse* pData = pWeekData->mutable_data();
	pData->CopyFrom(*pMsg);

	this->Save();
}

void HSGameCache::SetUserInfo( const char* pName,const std::string& uid )
{
	m_pGameCacheData->set_name(pName);
	m_pGameCacheData->set_uuid(uid);

	this->Save();
}

void HSGameCache::SetIsSendDeviceInfo( bool b )
{
	m_pGameCacheData->set_issenddeviceinfo(b);
}

void HSGameCache::SetUseBufferPropData( const PropInfo* pBufferProp )
{
	if (m_pUseBufferPropData == NULL)
	{
		m_pUseBufferPropData = PropInfo::default_instance().New();
	}
	m_pUseBufferPropData->Clear();
	if (pBufferProp)
	{
		m_pUseBufferPropData->CopyFrom(*pBufferProp);
	}
}

const PropInfo* HSGameCache::GetUseBufferPropData()
{
	return m_pUseBufferPropData;
}

bool HSGameCache::IsRunGameGuide()
{
	return m_pGameCacheData->isrungameguide();
}

void HSGameCache::SetIsRunGameGuide( bool b )
{
	m_pGameCacheData->set_isrungameguide(b);
	this->Save();
}
