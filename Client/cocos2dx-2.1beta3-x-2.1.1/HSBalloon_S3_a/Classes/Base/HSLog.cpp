#include "HSLog.h"
#include "HSGameCache.h"

HSLog::HSLog(void)
{
	m_iChannel = 0;

	m_pLog = LogRequest::default_instance().New();

	this->Read();

	m_pLastUserLog = m_pLog->add_userlogs();

	m_plastGoodLog = m_pLog->add_goodslog();
}


HSLog::~HSLog(void)
{
	this->Destroy();
}

HSLog* HSLog::ShareLog()
{
	static HSLog s_hsLog;
	return &s_hsLog;
}

const LogRequest* HSLog::GetLogData()
{
	return m_pLog;
}

LogRequest* HSLog::GetMutableLogData()
{
	return m_pLog;
}

bool HSLog::Save()
{
	std::string path = CCFileUtils::sharedFileUtils()->getWriteablePath() + HS_LOG_FILE_NAME;

	FILE *pFile = NULL;
	HS_fopen(pFile,path.c_str(),"wb+");
	if (pFile != NULL)
	{
		int size = m_pLog->GetCachedSize();
		string data = m_pLog->SerializeAsString();
		size = data.length();
		fwrite(data.c_str(),1,size,pFile);
		fclose(pFile);
		CCLog("Save game log success");
		return true;
	}
	HSMessageBox("Save game log Fail");
	return false;
}

bool HSLog::Read()
{
	string path = CCFileUtils::sharedFileUtils()->getWriteablePath() + HS_LOG_FILE_NAME;

	FILE *pFile = NULL;
	HS_fopen(pFile,path.c_str(),"rb");
	if (pFile != NULL)
	{
		m_pLog->Clear();

		fseek(pFile, 0, SEEK_END);
		long fileSize = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		char* buffer = new char[fileSize];
		memset(buffer,0,fileSize);
		fread(buffer,fileSize,1,pFile);

		fclose(pFile);

		bool isOK = m_pLog->ParseFromArray(buffer,fileSize);
		CC_SAFE_DELETE_ARRAY(buffer);
		if (isOK)
		{
			CCLog("Read game cache success");
			return true;
		}
	}
	//HSMessageBox("Read game cache Fail");
	return false;
}

void HSLog::Destroy()
{

}

void HSLog::SendDeviceInfo()
{
	LogRequest_TerminalLog* deviceInfo = m_pLog->mutable_terminallogs();
	std::string platform = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	platform = "Windows";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	platform = "Android";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	platform = "IOS";
#endif
	CCString* dpiSize = CCString::createWithFormat("%dx%d",(int)HSBase::GetScreenWidth(),(int)HSBase::GetScreenHeight());


	deviceInfo->set_osname(platform);
	deviceInfo->set_dpisize(dpiSize->getCString());
	deviceInfo->set_clitype(platform);
	deviceInfo->set_verinfo(HSTool::ShareHSTool()->GetSystemVersions());
	deviceInfo->set_nettype(HSTool::ShareHSTool()->GetNetType());
	deviceInfo->set_netproinfo(HSTool::ShareHSTool()->GetOperator());
	deviceInfo->set_countryinfo(HSTool::ShareHSTool()->GetCountryInfo());
	deviceInfo->set_cityinfo(HSTool::ShareHSTool()->GetCityInfo());

	dpiSize->release();
}

void HSLog::SendBuyGoodLog(LogRequest_BuyType sendType,int goodId,int goodNumber,LogRequest_BuyState buystate)
{
	m_plastGoodLog->set_chid(m_iChannel);

	m_plastGoodLog->set_type(sendType);

	m_plastGoodLog->set_goodsid(goodId);

	m_plastGoodLog->set_buysize(goodNumber);

	m_plastGoodLog->set_state(buystate);

	m_plastGoodLog->set_buytime(0);

	m_plastGoodLog->set_stime(0);

	const int maxCount = 10;
	int count = m_pLog->goodslog_size();
	if (count > maxCount)
	{
		for (int i=0;i<maxCount-1;++i)
		{
			m_pLog->mutable_goodslog()->SwapElements(i,i + 1);
		}
		m_pLog->mutable_goodslog()->RemoveLast();
	}

	int size = m_pLog->goodslog().size();

	this->SendLog();
	
}

void HSLog::SendUserLog(LogRequest_ActionType sendType)
{
	return;
	m_pLastUserLog->set_chid(m_iChannel);

// 	if (!HS_GAME_CACHE_DATA()->issenddeviceinfo())
// 	{
// 		sendType = LogRequest_ActionType_Activate;
// 	}

	switch (sendType)
	{
	case LogRequest_ActionType_Activate:

		this->SendActivateLog();

		break;

	case LogRequest_ActionType_Register:

		this->SendRegisterLog();

		break;

	case LogRequest_ActionType_Login:

		this->SendLoginLog();

		break;

	case LogRequest_ActionType_Logout:

		this->SendLogoutLog();

		break;

	case LogRequest_ActionType_Logoff:

		this->SendLogoff();

		break;
	}

	m_pLastUserLog->set_stime(0);

	const int maxCount = 10;
	int count = m_pLog->userlogs_size();
	if (count > maxCount)
	{
		for (int i=0;i<maxCount-1;++i)
		{
			m_pLog->mutable_userlogs()->SwapElements(i,i + 1);
		}
		m_pLog->mutable_userlogs()->RemoveLast();
	}

	int size = m_pLog->userlogs().size();

	this->SendLog();
	
}

void HSLog::SendLog()
{
	//HSRequest::ShareRequest()->SendLogRequest(m_pLog);
	HSTool::ShareHSTool()->SendLog(NULL,-1);

	m_pLog->clear_userlogs();

	m_pLog->clear_goodslog();

	m_pLastUserLog = m_pLog->add_userlogs();

	m_plastGoodLog = m_pLog->add_goodslog();
}

LogRequest_UserLog* HSLog::GetLastUserLog()
{
	return m_pLastUserLog;
}

void HSLog::SendActivateLog()
{
	this->SendDeviceInfo();

	m_pLastUserLog->set_actiontype(LogRequest_ActionType_Activate);
	m_pLastUserLog->set_logintime(0);
}

void HSLog::SendRegisterLog()
{

}

void HSLog::SendLoginLog()
{
	m_pLastUserLog->set_actiontype(LogRequest_ActionType_Login);
	m_pLastUserLog->set_logintime(0);
}

void HSLog::SendLogoutLog()
{
	m_pLastUserLog->set_actiontype(LogRequest_ActionType_Logout);
	m_pLastUserLog->set_logouttime(0);
}

void HSLog::SendLogoff()
{

}

void HSLog::SendChannelID( int id )
{
	m_iChannel = id;
}
