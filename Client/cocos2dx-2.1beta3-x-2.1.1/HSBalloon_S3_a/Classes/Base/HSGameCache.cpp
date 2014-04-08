#include "HSGameCache.h"
#include "HSEffect_ColorfulCandy.h"
#include "HSEffect_SickMucus.h"
#include "HSGamePairScene.h"
#include "HSGameSceneJumpManage.h"
HSGameCache::HSGameCache(void)
{
	m_isLogin = false;
	m_refrushUserInfo = false;

	ReadPropInfoData();
	m_pGameCacheData = message::GameCacheData::default_instance().New();

	this->Read();
	m_pGameCacheData->set_isrungameguide(false);

	m_pTargetInfoResponse = TargetInfoResponse::default_instance().New();

	m_pBattleResult = BattleResultResponse::default_instance().New();
	//默认是输
	//m_pBattleResult->set_result(BattleResultResponse_PlayerMatchResult_WIN);

	//@SendUseBuffRequest 缓存 
	m_pUseBuffRequest = UseBuffRequest::default_instance().New();

	/************************************************************************/
	/* 写两个测试的数据*/
	/************************************************************************/

	


// 	if(!HS_ONLINE)
// 	{
// 		m_pTargetInfoResponse->set_dungoenid("1000");
// 
// 		UserBasicInfo* self = m_pTargetInfoResponse->mutable_self();
// 		self->set_uid("10000");
// 		self->set_name("xiaoguo");
// 		self->set_level(1);
// 		self->set_style(1);
// 		self->set_wincount(100);
// 		self->set_losecount(30);
// 		self->set_winrate(30.f);
// 
// 		UserBasicInfo* target = m_pTargetInfoResponse->mutable_target();
// 		target->set_uid("10001");
// 		target->set_name("laoyang");
// 		target->set_level(1);
// 		target->set_style(1);
// 		target->set_wincount(100);
// 		target->set_losecount(40);
// 		target->set_winrate(40.f);
// 
// 		HS_GAME_CACHE()->AddGold(10000);
	//}
	
}

void HSGameCache::ReadPropInfoData()
{
	/**
	read PropInfoData
	*/
	string fullFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Data/PropInfo.data");

	HSFileData data(fullFilePath.c_str(),"rb");

	m_pPropInfoData = message::PropInfoData::default_instance().New();

	bool isOk = m_pPropInfoData->ParsePartialFromArray((const void*)(data.GetBuffer() + 2) ,data.GetSize() - 2);

	if (!isOk)
	{
		HSMessageBox("Data/PropInfo.data Error");
				 
		CC_SAFE_DELETE(m_pPropInfoData);
	}
	else
	{
		int manualSize =  m_pPropInfoData->manualpropinfolist().size();

		for(int i = 0; i < manualSize;i++)
		{
			m_propInfoMap.insert(pair<int,const message::PropInfo*>(m_pPropInfoData->manualpropinfolist(i).id(),&m_pPropInfoData->manualpropinfolist(i)));
		}

		int bufferSize = m_pPropInfoData->bufferpropinfolist().size();

		for(int i =0; i < bufferSize; i++)
		{
			m_propInfoMap.insert(pair<int,const message::PropInfo*>(m_pPropInfoData->bufferpropinfolist(i).id(),&m_pPropInfoData->bufferpropinfolist(i)));
		}

		int effectSize = m_pPropInfoData->effectpropinfolist().size();

		for(int i =0; i <effectSize; i++)
		{
			m_propInfoMap.insert(pair<int,const message::PropInfo*>(m_pPropInfoData->effectpropinfolist(i).id(),&m_pPropInfoData->effectpropinfolist(i)));
		}

		int lockSize = m_pPropInfoData->lockpropinfolist().size();

		for(int i=0; i <lockSize; i++)
		{
			m_propInfoMap.insert(pair<int,const message::PropInfo*>(m_pPropInfoData->lockpropinfolist(i).id(),&m_pPropInfoData->lockpropinfolist(i)));
		}

		int headSize = m_pPropInfoData->headlist().size();

		for(int i=0; i <headSize; i++)
		{
			m_propInfoMap.insert(pair<int,const message::PropInfo*>(m_pPropInfoData->headlist(i).id(),&m_pPropInfoData->headlist(i)));
		}
	}
}

HSGameCache::~HSGameCache(void)
{
	m_pTargetInfoResponse = NULL;
}

 HSGameCache* HSGameCache::ShareGameCache()
 {
	static HSGameCache s_hsGameCache;
	return &s_hsGameCache;
 }

void HSGameCache::Destroy()
{
	this->Save();
	//CC_SAFE_DELETE(m_pGameCacheData);
}

bool HSGameCache::Save()
{
	std::string path = CCFileUtils::sharedFileUtils()->getWriteablePath() + HS_GAME_CACHE_FILE_NAME;

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
		
		if (isOK)
		{
			CCLog("Read game cache success");
			return true;
		}
	}
	else
	{
		 
	}

	return false;
}
//@道具
const message::PropInfoData* HSGameCache::GetPropInfoData()
{
	return m_pPropInfoData;
}

const char* HSGameCache::GetEffectResName(const int& id)
{
	int size = m_pPropInfoData->effectpropinfolist().size();

	for(int i =0; i < size; i++)
	{
		if(m_pPropInfoData->effectpropinfolist(i).id()==id)
		{
			return m_pPropInfoData->effectpropinfolist(i).localname().c_str();
		}
	}

	return NULL;
}

const message::PropInfo* HSGameCache::GetPropInfo(const int& id)
{
	PROP_MAP::iterator p_itr = m_propInfoMap.find(id);

	if(p_itr!=m_propInfoMap.end())
	{
		return p_itr->second;
	}
	return NULL;
}

const message::GameCacheData* HSGameCache::GetGameCacheData()
{
	return m_pGameCacheData;
}

message::GameCacheData* HSGameCache::GetMutableGameCacheData()
{
	return m_pGameCacheData;
}

void HSGameCache::ResponseNotifyChangeBuff(NotifyChangeBuff* r)
{
	//临时写到这里
	//NotifyChangeBuff* r = (NotifyChangeBuff*)responseMsg; 

	HS_GAME_CACHE()->GetGameCacheData()->userinfo();
	string uid = r->targetuid();

	
	if(uid == HS_TARGET_SELF().uid())//指向我自己的
	{
		HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_targetuid(r->targetuid());
		HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_attacker(r->attacker());
		HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_propid(r->propid());
		HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_refrash(true);
	}
	else if(uid ==HS_TARGET_TARGET().uid())//指向对方的
	{
		HS_MUTABLE_TARGET_TARGET()->mutable_effect()->set_targetuid(r->targetuid());
		HS_MUTABLE_TARGET_TARGET()->mutable_effect()->set_attacker(r->attacker());
		HS_MUTABLE_TARGET_TARGET()->mutable_effect()->set_propid(r->propid());
		HS_MUTABLE_TARGET_TARGET()->mutable_effect()->set_refrash(true);
	}
}

void HSGameCache::ResponseUseBuff(UseBuffResponse* responseMsg)
{
	 if(responseMsg->status()==UseBuffResponse_UseStatus_SUCCESS)
	 {
		 string uid = HS_GAME_CACHE()->m_pUseBuffRequest->targetuid();

		 if(uid == HS_TARGET_SELF().uid())//指向我自己的
		 {
			 HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_targetuid(uid);
			 HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_attacker("mySelf");
			 HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_propid(HS_GAME_CACHE()->m_pUseBuffRequest->propid());
			 HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_refrash(true);
		 }
		 else if(uid ==HS_TARGET_TARGET().uid())//指向对方的
		 {
			 HS_MUTABLE_TARGET_TARGET()->mutable_effect()->set_targetuid(uid); 
			 HS_MUTABLE_TARGET_TARGET()->mutable_effect()->set_attacker("mySelf");
			 HS_MUTABLE_TARGET_TARGET()->mutable_effect()->set_propid(HS_GAME_CACHE()->m_pUseBuffRequest->propid());
			 HS_MUTABLE_TARGET_TARGET()->mutable_effect()->set_refrash(true);
		 }
	 }
	 else
	 {
		 CCLog("HSGameCache::ResponseUseBuff::UseBuff fail@yz");
	 }
}

void HSGameCache::ResponseSearchUserInfo(SearchUserInfoResponse* r)
{
	if(r->status()==SearchUserInfoResponse_SearchStatus_SearchStatus_SUCCESS)
	{
		const UserBasicInfo& info = r->userinfo();

		const string& uid = info.uid();

		const char* uidChar = info.uid().c_str();

		HS_MUTABLE_TARGET_SELF()->CopyFrom(info);
	}
	else
	{
		HSMessageBox("SearchUserInfo Fail");
	}
}
bool HSGameCache::AddGold( int money )
{
	//int gold = HS_TARGET_SELF().golds();
// 	if (money > gold)
// 	{
// 		HSMessageBox("Gold is not enough");
// 		return false;
// 	}

	int temp = HS_TARGET_SELF().golds() + money;
	if (temp < 0 )
	{
		temp = 0;

		HSMessageBox("Gold is not enough");
		return false;
	}

	HS_MUTABLE_TARGET_SELF()->set_golds(temp);

	this->Save();

	return true;
}

int HSGameCache::GetGold()
{
	return HS_TARGET_SELF().golds();
}

void HSGameCache::CopyUser(const UserBasicInfo& user)
{
	if(user.has_uid())
	{
		HS_MUTABLE_TARGET_SELF()->set_uid(user.uid());
	}

	if(user.has_name())
	{
		HS_MUTABLE_TARGET_SELF()->set_name(user.name());
	}

	if(user.has_level())
	{
		HS_MUTABLE_TARGET_SELF()->set_level(user.level());
	}

	if(user.has_style())
	{
		HS_MUTABLE_TARGET_SELF()->set_style(user.has_style());
	}

	if(user.has_wincount())
	{
		HS_MUTABLE_TARGET_SELF()->set_wincount(user.wincount());
	}

	if(user.has_losecount())
	{
		HS_MUTABLE_TARGET_SELF()->set_losecount(user.losecount());
	}

	if(user.has_winrate())
	{
		HS_MUTABLE_TARGET_SELF()->set_winrate(user.winrate());
	}

	if(user.has_effect())
	{
		HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_refrash(user.effect().refrash());
		HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_targetuid(user.effect().targetuid());
		HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_attacker(user.effect().attacker());
		HS_MUTABLE_TARGET_SELF()->mutable_effect()->set_propid(user.effect().propid());
	}

	if(user.has_iconid())
	{
		HS_MUTABLE_TARGET_SELF()->set_iconid(user.iconid());
	}

	if(user.has_oncelong())
	{
		HS_MUTABLE_TARGET_SELF()->set_oncelong(user.oncelong());
	}

	if(user.has_maximum())
	{
		HS_MUTABLE_TARGET_SELF()->set_maximum(user.maximum());
	}

	if(user.has_totaltime())
	{
		HS_MUTABLE_TARGET_SELF()->set_totaltime(user.totaltime());
	}

	if(user.has_roundsplayed())
	{
		HS_MUTABLE_TARGET_SELF()->set_roundsplayed(user.roundsplayed());
	}

	if(user.has_throwstones())
	{
		HS_MUTABLE_TARGET_SELF()->set_throwstones(user.thrownstones());
	}

	if(user.has_thrownstones())
	{
		HS_MUTABLE_TARGET_SELF()->set_thrownstones(user.thrownstones());
	}

	if(user.has_colorcats())
	{
		HS_MUTABLE_TARGET_SELF()->set_colorcats(user.colorcats());
	}

	if(user.has_consumegolds())
	{
		HS_MUTABLE_TARGET_SELF()->set_consumegolds(user.consumegolds());
	}

	if(user.has_consumeitems1())
	{
		HS_MUTABLE_TARGET_SELF()->set_consumeitems1(user.consumeitems1());
	}

	if(user.has_consumeitems2())
	{
		HS_MUTABLE_TARGET_SELF()->set_consumeitems2(user.consumeitems2());
	}

	if(user.has_consumeitems3())
	{
		HS_MUTABLE_TARGET_SELF()->set_consumeitems3(user.consumeitems3());
	}

	if(user.has_consumeitems4())
	{
		HS_MUTABLE_TARGET_SELF()->set_consumeitems4(user.consumeitems4());
	}

	if(user.has_golds())
	{
		HS_MUTABLE_TARGET_SELF()->set_golds(user.golds());
	}

	if(user.has_experience())
	{
		HS_MUTABLE_TARGET_SELF()->set_experience(user.experience());
	}

	if (user.has_maxexperience())
	{
		HS_MUTABLE_TARGET_SELF()->set_maxexperience(user.maxexperience());
	}

	HS_MUTABLE_TARGET_SELF()->mutable_buyequipframe()->Clear();

	int size = user.buyequipframe().size();
	for(int i =0; i < size;i++)
	{
		HS_MUTABLE_TARGET_SELF()->mutable_buyequipframe()->Add(user.buyequipframe(i));
	}

	if (user.has_successionwincount())
	{
		HS_MUTABLE_TARGET_SELF()->set_successionwincount(user.successionwincount());
	}
}

const message::PropInfo* HSGameCache::GetPropData( int id )
{
	std::vector<const message::PropInfo*>::iterator it = m_pFightingProp.begin();
	for (;it!=m_pFightingProp.end();++it)
	{
		if ((*it)->id() == id)
		{
			return (*it);
		}
	}
	return NULL;
}

bool HSGameCache::IsRegister()
{
	if (m_pGameCacheData->uid() == "0")
	{
		return false;
	}
	return true;
}

bool HSGameCache::IsLogin()
{
	return m_isLogin;
}

void HSGameCache::SetIsLogin( bool b )
{
	m_isLogin = b;
}
