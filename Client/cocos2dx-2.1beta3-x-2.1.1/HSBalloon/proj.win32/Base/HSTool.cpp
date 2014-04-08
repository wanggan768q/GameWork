#include "HSTool.h"
#include "HSGameSceneJumpManage.h"
#include "HSRequest.h"
#include "HSChannel.pb.h"
#include "HSChannelManager.h"
static HSTool* s_hsTool = NULL;

HSTool::HSTool(void)
{
	ReadConfiguration();
}

HSTool::~HSTool(void)
{
}

HSTool* HSTool::ShareHSTool()
{
	if(!s_hsTool)
	{
		s_hsTool = new HSTool;
	}
	return s_hsTool;
}
void HSTool::Destroy()
{
	CC_SAFE_DELETE(s_hsTool);
	HSGameCache::ShareGameCache()->Destroy();
}

void HSTool::Release()
{
	//Destroy
	HSGameSceneJumpManage::SharedGameSceneJumpManage()->Destroy();
	HSSocketPool::ShareSocketPool()->Destroy();
	HSRequest::ShareRequest()->Destroy();
	HSResponse::ShareResponse()->Destroy();
	HSDataCache::ShareDataCache()->Destroy();
	HSFilter::ShareFilter()->Destroy();
	HSSoundManage::ShareSoundManage()->Destroy();
}

const char* HSTool::GetUUID()
{
	 
	std::string uuid = "";
	
	long long time = HSTime::GetLocalityTime();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "1234567890";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	/**
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"com/Zrong/HSBalloon/HSDeviceInfo","GetUUID","()Ljava/lang/String;");

	if (!isOk)
	{
		HSMessageBox("Get UUID Fail");
		return "";
	}
	jstring obj = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
	uuid = JniHelper::jstring2string(obj);
	*/
	const char* s = CCString::createWithFormat("%s%s%s",HSTime::GetTime(),FindConfiguration("APPID").c_str(),FindConfiguration("ChannelID").c_str())->getCString();
	return s;
	//uuid = CCString::createWithFormat("%s%s%ld",FindConfiguration("APPID").c_str(),FindConfiguration("ChannelID").c_str(),HSTime::GetLocalityTimeAccurate());
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_IOS)
	//uuid = CCString::createWithFormat("%s%s%ld",FindConfiguration("APPID").c_str(),FindConfiguration("ChannelID").c_str(),HSTime::GetLocalityTimeAccurate());

	return "1234567890";
#endif
	CCLog("-HSAndroid- : UUID : %s",uuid.c_str());
	return uuid.c_str();
	
}

const char* HSTool::GetSystemVersions()
{
	std::string systemVersions = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "WIN7";
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"com/zrlh/tom/pkmmq/HSDeviceInfo","GetSystemVersions","()Ljava/lang/String;");

	if (!isOk)
	{
		HSMessageBox("Get SystemVersions Fail");
		return "";
	}
	jstring obj = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
	systemVersions = JniHelper::jstring2string(obj);
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_IOS)
	return "IOS";
#endif
	CCLog("-HSAndroid- : SystemVersions : %s",systemVersions.c_str());
	return systemVersions.c_str();
}

const char* HSTool::GetNetType()
{
	std::string netType = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "WIN7_WANG";
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"com/zrlh/tom/pkmmq/HSDeviceInfo","GetNetType","()Ljava/lang/String;");

	if (!isOk)
	{
		HSMessageBox("Get NetType Fail");
		return "";
	}
	jstring obj = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
	netType = JniHelper::jstring2string(obj);
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_IOS)
	return "WIFI";
#endif
	CCLog("-HSAndroid- : NetType : %s",netType.c_str());
	return netType.c_str();
}

const char* HSTool::GetOperator()
{
	std::string Operator = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "Ambition";
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"com/zrlh/tom/pkmmq/HSDeviceInfo","GetOperator","()Ljava/lang/String;");

	if (!isOk)
	{
		HSMessageBox("Get Operator Fail");
		return "";
	}
	jstring obj = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
	Operator = JniHelper::jstring2string(obj);
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_IOS)
	return "WIFI";
#endif
	CCLog("-HSAndroid- : Operator : %s",Operator.c_str());
	return Operator.c_str();
}

const char* HSTool::GetCountryInfo()
{
	std::string Country = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "CN";
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"com/zrlh/tom/pkmmq/HSDeviceInfo","GetCountryInfo","()Ljava/lang/String;");

	if (!isOk)
	{
		HSMessageBox("Get Country Fail");
		return "";
	}
	jstring obj = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
	Country = JniHelper::jstring2string(obj);
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_IOS)
	return "CN";
#endif
	CCLog("-HSAndroid- : Country : %s",Country.c_str());
	return Country.c_str();
}

const char* HSTool::GetCityInfo()
{
	std::string City = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "bj";
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"com/zrlh/tom/pkmmq/HSDeviceInfo","GetCityInfo","()Ljava/lang/String;");

	if (!isOk)
	{
		HSMessageBox("Get City Fail");
		return "";
	}
	jstring obj = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
	City = JniHelper::jstring2string(obj);
#elif(CC_TARGET_PLATFORM ==CC_PLATFORM_IOS)
	return "WIFI";
#endif
	CCLog("-HSAndroid- : City : %s",City.c_str());
	return City.c_str();
}

void HSTool::ReadConfiguration()
{
	if (m_configurationMap.size() != 0)
	{
		return;
	}
	HSBase::GetDictionary_Key_V__WithFile("configuration.data",&m_configurationMap);
}

std::string HSTool::FindConfiguration( const std::string& key )
{
	std::map<std::string,std::string>::iterator it = m_configurationMap.find(key);
	if (it!=m_configurationMap.end())
	{
		return it->second;
	}
	HSMessageBox("Failed to query the configuration file");
	return "";
}

void HSTool::Buy(int id,int money,const char* title,const char*describ)
{
	CCLog("title=%s,discrib=%s",title,describ);
	Channel* channel = message::Channel::default_instance().New();

	Channel_Tom* tom = channel->mutable_tom();
	tom->set_gamemoney(money);
	tom->set_propid(id);
	tom->set_title(title);
	tom->set_describe(describ);
	HSChannelManager::ShaderChannelManager()->Buy(channel);
}
