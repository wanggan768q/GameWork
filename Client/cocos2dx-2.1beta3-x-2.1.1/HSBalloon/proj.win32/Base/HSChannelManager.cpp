#include "HSChannelManager.h"
#include "HSTool.h"
#include "HSJava.h"

HSChannelManager::HSChannelManager(void)
{
	m_currentChannel = HS_CHANNEL_TYPE_Unknow;
	if(!CheckChannelType(HSTool::ShareHSTool()->FindConfiguration("ChannelID").c_str()))
	{
		HSMessageBox("Illegal channels types");
	}
	HSJava::ShaderJava();
}


HSChannelManager::~HSChannelManager(void)
{
}

HSChannelManager* HSChannelManager::ShaderChannelManager()
{
	static HSChannelManager s_hsChannelManager;
	return &s_hsChannelManager;
}

bool HSChannelManager::CheckChannelType( const char* typeID )
{
	int channelID = atoi(typeID);
	if (channelID >= MIN_CHANNEL_TYPE && channelID <= MAX_CHANNEL_TYPE)
	{
		m_currentChannel = (HSChannelType)channelID;
		return true;
	}
	return false;
}

void HSChannelManager::Buy( Channel* pMsg )
{
	HSAssert(pMsg,"");


	std::string buffer = pMsg->SerializeAsString();
	if (buffer == "")
	{
		CCLog("SerializeToArray Fail  %d",buffer.length());
	}
	CCLog("-Android- -------------------");
	CCLog(buffer.c_str());

	HSJni jni;
	jni.LoadStaticClass("com/zrlh/tom/pkmmq/HSChannelManager","void","Buy","byteArray",buffer);
	//jni.LoadStaticClass("com/Zrong/HSBalloon/HSChannelManager","void","Buy","string",buffer);

	CCLog("-Android- -------------------");

	CC_SAFE_DELETE(pMsg);
}




