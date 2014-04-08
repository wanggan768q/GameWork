//
//  HSLanFilter.cpp
//  HSBalloon_S3
//
//  Created by Ambition on 13-12-12.
//
//

#include "HSLanFilter.h"
#include "HSJava.h"
#include "HSLanResponse.h"


static HSLanFilter* s_HSLanFilter = NULL;


HSLanFilter::HSLanFilter(void)
{
    RegistermLanProtocol();
}

HSLanFilter::~HSLanFilter(void)
{
    
}

HSLanFilter* HSLanFilter::SharedLanFilter()
{
    if (!s_HSLanFilter)
    {
        s_HSLanFilter = new HSLanFilter;
    }
    return s_HSLanFilter;
}

bool HSLanFilter::CreaterMessage(google::protobuf::Message* msg)
{    
	if (!msg)
	{
		return false;
	}
	std::string msgName = msg->GetTypeName();
    
	CCLog(msgName.c_str());
    
    if(!msg->IsInitialized())
    {
        CCString* pErrorInfo = CCString::createWithFormat("Init Error [ %s ]",msgName.c_str());
        HSMessageBox(pErrorInfo->getCString());
        
        pErrorInfo->release();
        return false;
    }
    
	std::string strbody = msg->SerializeAsString();
	std::map<std::string,int>::iterator it = m_lanProtocol.find(msgName);
	if (it == this->m_lanProtocol.end())
	{
		msgName.append(" LAN Not registered ");
		CC_SAFE_DELETE(msg);
		return false;
	}
	long long checksum = (long long)(this->Adler32((unsigned char*)strbody.c_str(),strbody.length()));
    
    
    MessageInfo hsMsg = message::MessageInfo::default_instance();
    hsMsg.Clear();
    message::Head* head = hsMsg.mutable_head();
    head->set_checksum(checksum);
	head->set_sign(0);
	head->set_uid(HS_GAME_CACHE_DATA_LAN().uuid());
	head->set_imei("Ambition:IMEI");
    Body* body = hsMsg.mutable_body();
    body->add_commandid(it->second);
	body->add_data(strbody);
    
    
	std::string data = hsMsg.SerializeAsString();

    
    CCLog("Send_Lan %d: %s",data.length(),data.c_str());
    HSJava::ShaderJava()->distributeDataToOthers(data.c_str(), data.length());    
    
    delete msg;
    msg = NULL;
    
	return true;
}

void HSLanFilter::CreaterMessage(char* data,int lenth)
{
    if(!data)
	{
		CCMessageBox("Descending data is NULL","HSLanFilter");
		return;
	}
    string strDara = "";
    strDara.assign(data, lenth);
    
	message::MessageInfo temp_hsMsg = message::MessageInfo::default_instance();
	bool isOK = temp_hsMsg.ParseFromString(strDara);
	if (!isOK)
	{
		CCLog(" %s HS error: Data parsing errors  %d",__FUNCTION__,lenth);
		return;
	}
	message::Head temp_head = temp_hsMsg.head();
	message::Body temp_Body = temp_hsMsg.body();
    
    
    if (temp_head.uid() == HS_GAME_CACHE_DATA_LAN().uuid())
    {
        return;
    }
    
    
    
	::google::protobuf::Message* mainMsg = NULL;
    
	int infoCount = temp_Body.commandid_size();
	if (infoCount != temp_Body.data_size())
	{
		HSMessageBox("Server data issued by mistake");
		return;
	}
	
	int mainCommandID = 0;
	for (int i=0;i<1;++i)
	{
		mainCommandID = temp_Body.commandid(i);
        
		std::string msgBodyBuf = temp_Body.data(i);
		
		mainMsg = this->CreaterLanMessage(mainCommandID);
		
		if (!mainMsg)
		{
			CCMessageBox("Through the id to create news failure","HSFilter");
			CC_SAFE_DELETE(mainMsg);
			return ;
		}
		mainMsg->ParseFromString(msgBodyBuf);
        
	}
    
	//m_FilterDaraQueue.push(pFilterData);
	HSLanResponse::ShareLanResponse()->HandleFactory(mainCommandID,mainMsg);
    
	CC_SAFE_DELETE(mainMsg);
    
}

::google::protobuf::Message* HSLanFilter::CreaterLanMessage(int ID)
{

    switch (ID)
    {
        case API_LAN_LanSyncUserInfoNotice:
            
            
            return HS_CREATER_GOOGLE_MESSAGE(LanSyncUserInfoNotice);
            
        case API_LAN_LanBattleReadyNotice:
            
            return HS_CREATER_GOOGLE_MESSAGE(LanBattleReadyNotice);
            
        case API_LAN_LanBattleDataNotice:
            
            return HS_CREATER_GOOGLE_MESSAGE(LanBattleDataNotice);
            
        case API_LAN_LanStartBattleNotify:
            
            return HS_CREATER_GOOGLE_MESSAGE(LanStartBattleNotify);
            
        case API_LAN_LanBattleResultNotice:
            
            return HS_CREATER_GOOGLE_MESSAGE(LanBattleResultNotice);
            
        case API_LAN_LanQuitRoomNotice :
            
            return HS_CREATER_GOOGLE_MESSAGE(LanQuitRoomNotice);
            
        default:
        {
            HSMessageBox("Lan CreaterLanMessage ");
        }
            break;
    }
    
    return NULL;
}

void HSLanFilter::RegistermLanProtocol()
{
    m_lanProtocol.insert(pair<string, int>("message.LanSyncUserInfoNotice",API_LAN_LanSyncUserInfoNotice));
    m_lanProtocol.insert(pair<string, int>("message.LanStartBattleNotify",API_LAN_LanStartBattleNotify));
    m_lanProtocol.insert(pair<string, int>("message.LanBattleReadyNotice",API_LAN_LanBattleReadyNotice));
    m_lanProtocol.insert(pair<string, int>("message.LanBattleDataNotice",API_LAN_LanBattleDataNotice));
    m_lanProtocol.insert(pair<string, int>("message.LanBattleResultNotice",API_LAN_LanBattleResultNotice));
    m_lanProtocol.insert(pair<string, int>("message.LanQuitRoomNotice",API_LAN_LanQuitRoomNotice));
    
    m_lanProtocol.insert(pair<string, int>("message.UseBuff",API_LAN_LanUseBufferNotice));
    
}






































