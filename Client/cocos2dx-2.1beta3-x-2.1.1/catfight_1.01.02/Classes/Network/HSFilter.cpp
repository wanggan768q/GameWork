#include "HSFilter.h"
#define HS_CREATER_GOOGLE_MESSAGE(__ResponeClass__) ((::google::protobuf::Message*)message::__ResponeClass__::default_instance().New())

static HSFilter* s_hsFilter = NULL;
static int registerMessageIndex = 0;

HSFilter::HSFilter(void)
{
	this->m_hsMsg = NULL;
	this->RegisterAllMessage();
}

HSFilter::~HSFilter(void)
{
	this->m_MessageListMap.clear();
	if (this->m_hsMsg)
	{
		delete this->m_hsMsg;
		this->m_hsMsg = NULL;
	}
}

HSFilter* HSFilter::ShareFilter()
{
	if(s_hsFilter == NULL)
	{
		s_hsFilter = new HSFilter;
	}
	return s_hsFilter;
}

void HSFilter::Destroy()
{
	CC_SAFE_DELETE(s_hsFilter);
}

void HSFilter::RegisterMessage( int requestID,int responseID,std::string messageName )
{
	std::string req = messageName;
	std::string res = messageName;
	req.insert(0,"message.");
	req.insert(req.length(),"Request");
    
	res.insert(0,"message.");
	res.insert(res.length(),"Response");
    
#if HS_FILTER_LOG
	cocos2d::CCLog("RegisterMessage (%d) :	%d   ->   %s",(++registerMessageIndex),requestID,req.c_str());
	cocos2d::CCLog("RegisterMessage (%d) :	%d   ->   %s",(++registerMessageIndex),responseID,res.c_str());
#endif
	
	this->m_MessageListMap.insert(pair<string,int>(req,requestID));
	this->m_MessageListMap.insert(pair<string,int>(res,responseID));
}

bool HSFilter::CreaterMessage(google::protobuf::Message* msg )
{
	if (HS_IsRunGameGuide())
	{
		CC_SAFE_DELETE(msg);
		return false;
	}
    
	if (!msg)
	{
		return false;
	}
	std::string msgName = msg->GetTypeName();
	std::string strbody = msg->SerializeAsString();
	std::map<std::string,int>::iterator it = this->m_MessageListMap.find(msgName);
	if (it == this->m_MessageListMap.end())
	{
		msgName.append(" Not registered ");
		CC_SAFE_DELETE(msg);
		return false;
	}
	long long checksum = (long long)(this->Adler32((unsigned char*)strbody.c_str(),strbody.length()));
    
	if(!this->m_hsMsg)
	{
		this->m_hsMsg  = message::MessageInfo::default_instance().New();
	}
	m_hsMsg->Clear();
	message::Head* head = this->m_hsMsg->mutable_head();
	head->Clear();
	
	head->set_checksum(checksum);
	head->set_sign(0);
	head->set_uid(HS_GAME_CACHE_DATA()->uid().c_str());
	//head->set_uid("1425A7AFF693FDFA3A63DCE8E923FED1");
	head->set_imei("Ambition:IMEI");
    
    CCLOG(CCString::createWithFormat("UUID: %s",HS_GAME_CACHE_DATA()->uid().c_str())->getCString());
    
    
	CCLog("uid=%s",HS_GAME_CACHE_DATA()->uid().c_str());
	message::Body* body = this->m_hsMsg->mutable_body();
	int tempCommandID = it->second;
	body->add_commandid(tempCommandID);
	body->add_data(strbody);
    
	std::string data = m_hsMsg->SerializeAsString();
    
	this->SendDistribution(tempCommandID,data,msgName);
	
#if HS_FILTER_LOG
	if (it->second != 2010 && it->second != 3010)
	{
		//CCLog("\nSendData:(%d){\nID:%d -------- %s\nUUID: %s\n %s \n\n}\n",(int)data.length() + 4,it->second,msgName.c_str(),HS_GAME_CACHE_DATA()->uid().c_str(),data.c_str());
	}
#endif
    
	delete m_hsMsg;
	m_hsMsg = NULL;
	head = NULL;
	delete msg;
	msg = NULL;
    
	return true;
}

void HSFilter::CreaterMessage( char* data,int lenth )
{
	if(!data)
	{
		CCMessageBox("Descending data is NULL","HSFilter");
		return;
	}
    
	message::MessageInfo temp_hsMsg = message::MessageInfo::default_instance();
	bool isOK = temp_hsMsg.ParsePartialFromArray(data,lenth);
	if (!isOK)
	{
		//HSMessageBox("Data parsing errors");
		CCLog("HS error: Data parsing errors  %d",lenth);
		return;
	}
	message::Head temp_head = temp_hsMsg.head();
	message::Body temp_Body = temp_hsMsg.body();
    
	::google::protobuf::Message* mainMsg = NULL;
	//HSFilterData* pFilterData = new HSFilterData;
    
	int infoCount = temp_Body.commandid_size();
	if (infoCount != temp_Body.data_size())
	{
		HSMessageBox("Server data issued by mistake");
		return;
	}
	
	int mainCommandID = 0;
	for (int i=0;i<infoCount;++i)
	{
		int commandId = temp_Body.commandid(i);
        
        if(commandId != 61000)
        {
            if(HS_GAME_CACHE_DATA()->uid() != temp_head.uid())
            {
                //CCString* pstr = CCString::createWithFormat("ME: %d NEW: %d",HS_GAME_CACHE_DATA()->uid().length(),temp_head.uid().length());
                //HSMessageBox(pstr->getCString());
                if (temp_head.has_uid())
                {
                    HS_MUTABLE_GAME_CACHE_DATA()->set_uid(temp_head.uid());
                    HS_GAME_CACHE()->Save();
                }
            }
        }
        
		std::string msgBodyBuf = temp_Body.data(i);
		
		::google::protobuf::Message* googleMsg = this->CreaterMessage(commandId);
		
		if (!googleMsg)
		{
			CCMessageBox("Through the id to create news failure","HSFilter");
			googleMsg = NULL;
			return ;
		}
		googleMsg->ParseFromString(msgBodyBuf);
        
#if HS_FILTER_LOG
		if (commandId != 62010 && commandId != 63010)
		{
			CCLog("\nResponseData(%d %% %d):{\nID:%d -------- %s\n}\n",i + 1,infoCount,commandId,googleMsg->GetTypeName().c_str());
		}
#endif
        
		if (i == 0)
		{
			mainMsg = googleMsg;
			//pFilterData->pMsg = googleMsg;
			mainCommandID = commandId;
			//pFilterData->commandId = commandId;
		}else{
			//HSMessageBox("Multiple packages");
			HSDataCache::ShareDataCache()->AddCacheData(commandId,googleMsg);
			delete googleMsg;
			googleMsg = NULL;
		}
	}
    
	//m_FilterDaraQueue.push(pFilterData);
	HSResponse::ShareResponse()->HandleFactory(mainCommandID,mainMsg);
	delete mainMsg;
	mainMsg = NULL;
}

void HSFilter::Distribution()
{
	if (!m_FilterDaraQueue.empty())
	{
		HSFilterData* hsFilterData = m_FilterDaraQueue.front();
		HSResponse::ShareResponse()->HandleFactory(hsFilterData->commandId,hsFilterData->pMsg);
		CC_SAFE_DELETE(hsFilterData);
		m_FilterDaraQueue.pop();
	}
}

bool HSFilter::SendDistribution( int commandID , const std::string& data,const std::string &describe)
{
    HSSocket* pSocket = NULL;
    
    HSSocketSendData sendData;
    sendData.init(data, commandID,describe);
    
	if (commandID >= 3000)
	{
		pSocket = HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_L_Battle);
        
	}else if (commandID >= 2000){
        
		pSocket = HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_D_Logic);
        
	}else if(commandID >= 1000){
        
		pSocket = HSSocketPool::ShareSocketPool()->GetSocketWithTag(S_D_Login);
        
	}else{
		CCString* error = CCString::createWithFormat("The wrong agreement ID [%d] ",commandID);
		HSMessageBox(error->getCString());
		return false;
	}
	CCLog("send id=%d",commandID);
    pSocket->AddSendData(sendData);
	return true;
}


void HSFilter::SetIsShowLog(bool b)
{
	if ( b == HS_FILTER_LOG)
	{
		return;
	}
    
	if (b == true)
	{
#ifdef HS_FILTER_LOG
#undef HS_FILTER_LOG
#define HS_FILTER_LOG 1
#endif
        
	}else{
#ifdef HS_FILTER_LOG
#undef HS_FILTER_LOG
#define HS_FILTER_LOG 0
#endif
	}
}

unsigned long long HSFilter::Adler32(unsigned char* buf, int len)
{
	unsigned long long adler = 1;
	unsigned long long s1 = adler & 0xffff;
	unsigned long long s2 = (adler >> 16) & 0xffff;
	for (int i = 0; i < len; i++)
	{
		s1 = (s1 + buf[i]) % BASE;
		s2 = (s2 + s1) % BASE;
	}
	return (s2 << 16) + s1;
}

::google::protobuf::Message* HSFilter::CreaterMessage(int ID)
{
	switch(ID)
	{
        case API_ErrorMessageInfo:
            
            return HS_CREATER_GOOGLE_MESSAGE(ErrorMessageInfo);
            
        case API_RegisterResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(RegisterResponse);
            
        case API_LoginResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(LoginResponse);
            
        case API_FightingResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(FightingResponse);
            
        case API_TargetInfoResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(TargetInfoResponse);
            
        case API_BattleReadyResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(BattleReadyResponse);
            
        case API_StartBattle:
            
            return HS_CREATER_GOOGLE_MESSAGE(NotifyStartBattle);
            
        case API_PlayerDisengageResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(PlayerDisengageResponse);
            
        case API_KickOutDungoen:
            
            return HS_CREATER_GOOGLE_MESSAGE(NotifyKickedOutDungoen);
            
        case API_BattleDataResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(BattleDataResponse);
            
        case API_BattleResultResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(BattleResultResponse);
            
        case API_UseBuffResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(UseBuffResponse);
            
        case API_NotifyChangeBuff:
            
            return HS_CREATER_GOOGLE_MESSAGE(NotifyChangeBuff);
            
        case API_HeartbeatGameResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(GamePingResponse);
            
        case API_HeartbeatBattleResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(BattlePingResponse);
            
        case API_FriendListResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(FriendListResponse);
            
        case API_SearchUserInfoResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(SearchUserInfoResponse);
            
        case API_DestroyBalloonResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(DestroyBalloonResponse);
        case API_UsePropResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(UsePropResponse);
            
        case API_AddFriendResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(AddFriendResponse);
            
        case API_RoomDataResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(RoomDataResponse);
            
        case API_ClaimedDailyRewardResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(ClaimedDailyRewardResponse);
            
        case API_UserInfoUpdateResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(UserInfoUpdateResponse);
            
        case API_ExitAdvancedResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(ExitAdvancedResponse);
            
        case API_AchievementResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(AchievementResponse);
            
        case API_ReceiveAchievementRewardResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(ReceiveAchievementRewardResponse);
            
        case API_SendEmailResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(SendEmailResponse);
            
        case API_EmailResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(EmailResponse);
            
        case API_OpenEmailResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(OpenEmailResponse);
            
        case API_AddressBookResponse:
            
            return HS_CREATER_GOOGLE_MESSAGE(AddressBookResponse);
        case API_RechargeResponse:

        		return HS_CREATER_GOOGLE_MESSAGE(NotifyRecharge);
            
        default:
            
            HSMessageBox(CCString::createWithFormat("Error code ID : %d",ID)->getCString());
            return NULL;
	}
}

void HSFilter::RegisterAllMessage()
{
    
#ifndef HS_REGISTER_PROTOCOL
#define HS_REGISTER_PROTOCOL(__Request__,__Response__,__Name__) this->RegisterMessage(__Request__,__Response__,__Name__)
#endif // !HS_REGISTER_PROTOCOL
    
    
	HS_REGISTER_PROTOCOL(API_RegisterRequest,API_RegisterResponse,"Register");
	HS_REGISTER_PROTOCOL(API_LoginRequest,API_LoginResponse,"Login");
	
    
	//////////////////////////////////////////////////////////////////////////
    
	HS_REGISTER_PROTOCOL(API_FightingRequest,API_FightingResponse,"Fighting");
	HS_REGISTER_PROTOCOL(API_HeartbeatGameRequest,API_HeartbeatGameResponse,"GamePing");
	HS_REGISTER_PROTOCOL(API_FriendListRequest,API_FriendListResponse,"FriendList");
	HS_REGISTER_PROTOCOL(API_SearchUserInfoRequest,API_SearchUserInfoResponse,"SearchUserInfo");
	HS_REGISTER_PROTOCOL(API_AddFriendRequest,API_AddFriendResponse,"AddFriend");
	HS_REGISTER_PROTOCOL(API_RoomDataRequest,API_RoomDataResponse,"RoomData");
	HS_REGISTER_PROTOCOL(API_ClaimedDailyRewardRequest,API_ClaimedDailyRewardResponse,"ClaimedDailyReward");
	HS_REGISTER_PROTOCOL(API_UserInfoUpdateRequest,API_UserInfoUpdateResponse,"UserInfoUpdate");
	HS_REGISTER_PROTOCOL(API_AchievementRequest,API_AchievementResponse,"Achievement");
    
    HS_REGISTER_PROTOCOL(API_ReceiveAchievementRewardRequest,API_ReceiveAchievementRewardResponse,"ReceiveAchievementReward");
    HS_REGISTER_PROTOCOL(API_SendEmailRequest,API_SendEmailResponse,"SendEmail");
    HS_REGISTER_PROTOCOL(API_EmailRequest,API_EmailResponse,"Email");
    HS_REGISTER_PROTOCOL(API_OpenEmailRequest,API_OpenEmailResponse,"OpenEmail");
    HS_REGISTER_PROTOCOL(API_AddressBookRequest,API_AddressBookResponse,"AddressBook");
    
	//////////////////////////////////////////////////////////////////////////
    
	HS_REGISTER_PROTOCOL(API_TargetInfoRequest,API_TargetInfoResponse,"TargetInfo");
	HS_REGISTER_PROTOCOL(API_BattleReadyRequest,API_BattleReadyResponse,"BattleReady");
	HS_REGISTER_PROTOCOL(API_BattleResultRequest,API_BattleResultResponse,"BattleResult");
	HS_REGISTER_PROTOCOL(API_PlayerDisengageRequest,API_PlayerDisengageResponse,"PlayerDisengage");
	HS_REGISTER_PROTOCOL(API_BattleDataRequest,API_BattleDataResponse,"BattleData");
	HS_REGISTER_PROTOCOL(API_UseBuffRequest,API_UseBuffResponse,"UseBuff");
	HS_REGISTER_PROTOCOL(API_HeartbeatBattleRequest,API_HeartbeatBattleResponse,"BattlePing");
	HS_REGISTER_PROTOCOL(API_DestroyBalloonRequest,API_DestroyBalloonResponse,"DestroyBalloon");
	HS_REGISTER_PROTOCOL(API_UsePropRequest,API_UsePropResponse,"UseProp");
	HS_REGISTER_PROTOCOL(API_ExitAdvancedRequest,API_ExitAdvancedResponse,"ExitAdvanced");
}
