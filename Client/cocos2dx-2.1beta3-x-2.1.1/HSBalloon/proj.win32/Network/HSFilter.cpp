#include "HSFilter.h"


#define HS_CREATER_GOOGLE_MESSAGE(__ResponeClass__) ((::google::protobuf::Message*)message::__ResponeClass__::default_instance().New())

static HSFilter* s_hsFilter = NULL;
static int registerMessageIndex = 0;

HSFilter::HSFilter(void)
{
	this->hsMsg = NULL;
	this->RegisterAllMessage();
}

HSFilter::~HSFilter(void)
{
	this->mMessageListMap.clear();
	if (this->hsMsg)
	{
		delete this->hsMsg;
		this->hsMsg = NULL;
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

void HSFilter::RegisterMessage( int requestID,int responseID,string messageName )
{
	string req = messageName;
	string res = messageName;
	req.insert(0,"message.");
	req.insert(req.length(),"Request");

	res.insert(0,"message.");
	res.insert(res.length(),"Response");

#if HS_FILTER_LOG
	cocos2d::CCLog("RegisterMessage (%d) :	%d   ->   %s",(++registerMessageIndex),requestID,req.c_str());
	cocos2d::CCLog("RegisterMessage (%d) :	%d   ->   %s",(++registerMessageIndex),responseID,res.c_str());
#endif
	
	this->mMessageListMap.insert(pair<string,int>(req,requestID));
	this->mMessageListMap.insert(pair<string,int>(res,responseID));
}

bool HSFilter::CreaterMessage(google::protobuf::Message* msg )
{
	if (!msg)
	{
		return false;
	}
	string msgName = msg->GetTypeName();
	string strbody = msg->SerializeAsString();
	std::map<string,int>::iterator it = this->mMessageListMap.find(msgName);
	if (it == this->mMessageListMap.end())
	{
		msgName.append(" Not registered ");
		delete msg;
		msg = NULL;
		return false;
	}
	long long checksum = (long long)(this->Adler32((unsigned char*)strbody.c_str(),strbody.length()));

	if(!this->hsMsg)
	{
		this->hsMsg  = message::MessageInfo::default_instance().New();
	}
	hsMsg->Clear();
	message::Head* head = this->hsMsg->mutable_head();
	head->Clear();
	
	head->set_checksum(checksum);
	head->set_sign(0);
	head->set_uid(HS_GAME_CACHE_DATA()->uuid());
	head->set_imei(HS_GAME_CACHE_DATA()->imei());

	message::Body* body = this->hsMsg->mutable_body();
	body->add_commandid(it->second);
	body->add_data(strbody);

	string data = hsMsg->SerializeAsString();
	HSSocketPool::ShareSocketPool()->GetSocketWithTag(DEFAULT_SOCKET)->SendData(data);
	
#if HS_FILTER_LOG
	CCLog("\nSendData:{\nID:%d \n %s \n\n}\n",it->second,data.c_str());
#endif

	delete hsMsg;
	hsMsg = NULL;
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

	message::MessageInfo* temp_hsMsg = message::MessageInfo::default_instance().New();
	temp_hsMsg->ParseFromArray(data,lenth);
	message::Head temp_head = temp_hsMsg->head();
	message::Body temp_Body = temp_hsMsg->body();

	::google::protobuf::Message* mainMsg = NULL;
	int infoCount = temp_Body.commandid_size();
	if (infoCount != temp_Body.data_size())
	{
		CCMessageBox("Server data issued by mistake","HSFilter");
		delete temp_hsMsg;
		temp_hsMsg = NULL;
		return;
	}
	int mainCommandID = 0;
	for (int i=0;i<infoCount;++i)
	{
		int commandId = temp_Body.commandid(i);

		string msgBodyBuf = temp_Body.data(i);
		::google::protobuf::Message* googleMsg = this->CreaterMessage(commandId);
		if (!googleMsg)
		{
			CCMessageBox("Through the id to create news failure","HSFilter");
			delete temp_hsMsg;
			temp_hsMsg = NULL;
			googleMsg = NULL;
			return ;
		}
		googleMsg->ParseFromString(msgBodyBuf);

#if HS_FILTER_LOG
		CCLog("\nResponseData(%d %% %d):{\nID:%d \n%s\n}\n",i + 1,infoCount,commandId,msgBodyBuf.c_str());
#endif
		
		if (i == 0)
		{
			mainMsg = googleMsg;
			mainCommandID = commandId;
		}else{
			HSDataCache::ShareDataCache()->AddCacheData(commandId,googleMsg);
			delete googleMsg;
			googleMsg = NULL;
		}
	}
	HSResponse::ShareResponse()->HandleFactory(mainCommandID,mainMsg);
	delete mainMsg;
	mainMsg = NULL;

	delete temp_hsMsg;
	temp_hsMsg = NULL;
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

	case API_CombatGainsResponse:

		return HS_CREATER_GOOGLE_MESSAGE(CombatGainsResponse);

	case API_SearchRankResponse:

		return HS_CREATER_GOOGLE_MESSAGE(SearchRankResponse);

	case API_SearchWeeklyScoreResponse:

		return HS_CREATER_GOOGLE_MESSAGE(SearchWeeklyScoreResponse);

	case API_LogResponse:

		return HS_CREATER_GOOGLE_MESSAGE(LogResponse);

	default:
		HSMessageBox(CCString::createWithFormat("Error code ID : %d",ID)->getCString());
		return NULL;
	}	
	return NULL;
}

void HSFilter::RegisterAllMessage()
{

#define HS_REGISTER_PROTOCOL(__Request__,__Response__,__Name__) this->RegisterMessage(__Request__,__Response__,__Name__)

	HS_REGISTER_PROTOCOL(API_RegisterRequest,API_RegisterResponse,"Register");

	HS_REGISTER_PROTOCOL(API_CombatGainsRequest,API_CombatGainsResponse,"CombatGains");

	HS_REGISTER_PROTOCOL(API_SearchRankRequest,API_SearchRankResponse,"SearchRank");

	HS_REGISTER_PROTOCOL(API_SearchWeeklyScoreRequest,API_SearchWeeklyScoreResponse,"SearchWeeklyScore");

	HS_REGISTER_PROTOCOL(API_LogRequest,API_LogResponse,"Log");
}
