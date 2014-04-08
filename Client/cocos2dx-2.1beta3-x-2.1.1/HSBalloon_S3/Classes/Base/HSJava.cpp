#include "HSJava.h"
#include "HSGameCache.h"
#include "HSGameSceneJumpManage.h"
#include "HSJson.h"
#include "HSRequest.h"
#include "MobClickCpp.h"
#include "HSTool.h"
#include "HSLanRoomListScene.h"
#include "HSGameMainScene.h"
#include "HSLanFilter.h"
#include "HSNetworkDialog.h"
#include "HSLanActionManager.h"
#if HSIos
#include "HSSDK.h"
#endif


static HSJava* s_hsJAVA = new HSJava;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
    
	void Java_com_zrlh_tom_pkmmq_HSChannelManager_CallBuy(JNIEnv *env, jobject thiz, jint propID)
	{
		CCLog("-Android- Java_com_Zrong_HSBalloon_HSChannelManager_CallBuy   Begin");
        
		//const char* pData = HSJni::JByteArrayToCharArray(env,buffer);
		if (s_hsJAVA)
		{
			CCLog("s_hsJAVA");
			//if (pData)
			//{
            s_hsJAVA->CallBuy((int)propID);
			//}
		}
		CCLog("-Android- Java_com_Zrong_HSBalloon_HSChannelManager_CallBuy  End");
	}
    
	/**
		 * 服务器收到要处理的数据
		 */
		void Java_jni_JniHelper_onHandleDistribute(JNIEnv* env,jobject thiz,jbyteArray buffer,jint size)
		{
			const char* pData = HSJni::JByteArrayToCharArray(env,buffer);
			if (s_hsJAVA)
			{
				CCLog("s_hsJAVA");
				if (pData)
				{
					CCLog("pData");
					int pDataSize = size;
					CCLog("bufferSize: %d",pDataSize);
					s_hsJAVA->onHandleDistribute(pData,pDataSize);
				}
			}
		}
		/**
		 * 客户端收到服务器处理后转发来的数据
		 */
		void Java_jni_JniHelper_onHandleDistributeReceived(JNIEnv* env,jobject thiz,jbyteArray buffer,jint size)
		{
			const char* pData = HSJni::JByteArrayToCharArray(env,buffer);
			if (s_hsJAVA)
			{
				CCLog("s_hsJAVA");
				if (pData)
				{
					CCLog("pData");
					int pDataSize = size;
					CCLog("bufferSize: %d",pDataSize);
					s_hsJAVA->onHandleDistributeReceived(pData,pDataSize);
				}
			}
		}

	void Java_jni_JniHelper_finishInit(JNIEnv *env,jobject thiz,jstring json)
	{
		CCLog("-Android- Java_jni_JniHelper_finishInit  Begin");
		if(s_hsJAVA)
		{
			CCLog("s_hsJAVA");
            
			std::string j = JniHelper::jstring2string(json);
			
			s_hsJAVA->CallFinishInit(j.c_str());
		}
		CCLog("-Android- Java_jni_JniHelper_finishInit End");
	}
    
	void Java_jni_JniHelper_finishPay(JNIEnv *env,jobject thiz,jstring json)
	{
		CCLog("-Android- Java_jni_JniHelper_finishPay  Begin");
		if(s_hsJAVA)
		{
			CCLog("s_hsJAVA");
            
			std::string j = JniHelper::jstring2string(json);
			s_hsJAVA->CallFinishInit(j.c_str());
		}
		CCLog("-Android- Java_jni_JniHelper_finishPay End");
	}
    
	void Java_jni_JniHelper_execCallback(JNIEnv *env,jobject thiz,jstring json)
	{
		CCLog("-Android- Java_jni_JniHelper_execCallback Begin");
		if(s_hsJAVA)
		{
			CCLog("s_hsJAVA");
			std::string j = JniHelper::jstring2string(json);
			CCLog("callback %s",j.c_str());
			s_hsJAVA->Callback(j.c_str());
		}
		CCLog("-Android- Java_jni_JniHelper_finishPay End");
	}
    
	jint Java_jni_JniHelper_gameEnd(JNIEnv*env, jobject thiz)
	{
        
		if(HSGameSceneJumpManage::SharedGameSceneJumpManage()->GetGameSceneID() !=HS_SCENE_BattleScene)
		{
			if(s_hsJAVA)
			{
				if(s_hsJAVA->m_lastTime ==0)
				{
					s_hsJAVA->m_lastTime = HSTime::GetLocalityTime();
					return 0;
				}
				else
				{
					long long cur = HSTime::GetLocalityTime();
                    
					if(cur - s_hsJAVA->m_lastTime >3500)
					{
						s_hsJAVA->m_lastTime = cur;
						return 0;
					}
					else
					{
						MobClickCpp::end();
						//CCDirector::sharedDirector()->end();
						return 1;
					}
				}
			}
			else
			{
                
			}
		}
		else
		{
            
		}
		return 2;
	}
    
	jint Java_jni_JniHelper_getProductId(JNIEnv*env,jobject thiz)
	{
		if(s_hsJAVA)
		{
			int appId = atoi(HS_Find_Configure("APPID").c_str());
			return appId;
		}
		return 0;
	}
    
    
    
    void Java_jni_JniHelper_nativeTest(JNIEnv *env,jobject thiz,jbyteArray buffer,jint size)
	{
		CCLog("-Android- Java_jni_JniHelper_Test Begin");
		const char* pData = HSJni::JByteArrayToCharArray(env,buffer);
        if (s_hsJAVA)
        {
            CCLog("s_hsJAVA");
            if (pData)
            {
                CCLog("pData");
                int pDataSize = size;
                CCLog("bufferSize: %d",pDataSize);
                s_hsJAVA->TestProto(pData,pDataSize);
            }
        }
		CCLog("-Android- Java_jni_JniHelper_Test End");
	}
    
};
#endif






HSJava::HSJava(void)
{
	m_lastTime = 0;
}


HSJava::~HSJava(void)
{
    
}

HSJava* HSJava::ShaderJava()
{
	if (s_hsJAVA)
	{
		s_hsJAVA = new HSJava;
        s_hsJAVA->autorelease();
        s_hsJAVA->retain();
        s_hsJAVA->init();
	}
	return s_hsJAVA;
}


void HSJava::CallFinishInit(const char* json)
{
	return;
}


void HSJava::CallFinishPay(const char*)
{
    
	return;
}

void HSJava::CallBuy( int propID )
{
	return;
}


bool HSJava::init()
{
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(HSJava::Updata), this, 0.f, false);
    
    return true;
}

void HSJava::Init(const char* json)
{
    
    
    
	return;
    
#if(CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID)
	HSAssert(json,"");
    
	CCLog("-Android- -------------------");
    
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","init","(Ljava/lang/String;)V");
    
	if (!isOk)
	{
		HSMessageBox("jni/JniHelper/init Fail");
		return;
	}
	jstring jjson = minfo.env->NewStringUTF(json);
	minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID,jjson);
    
	CCLog("-Android- -------------------");
#endif
}



void HSJava::Pay(int gold)
{
    const BuyGold* pBuyGold = HS_GAME_CACHE()->GetReasonableChargeId(gold);
    
    int num = HS_GAME_CACHE()->GetChargeNumber(gold,pBuyGold->gold_number());

	Json::Value jsonData;
	jsonData["JNI_ID"] = Json::Value(1001);
	jsonData["PAY_UID"] = Json::Value(HS_GAME_CACHE_DATA()->uid().c_str());
	jsonData["goodID"] = pBuyGold->id();
	jsonData["size"] = num;
	jsonData["total"] = pBuyGold->money();
	HSJson* pJson = HSJson::CreateWithWriter();
	std::string data = pJson->Writer(jsonData);
    
	eventDict dict;
    
	MobClickCpp::event("HSQuickBuyGold",&dict);
    
#if HSAndroid
	HSJava::ShaderJava()->JavaExec(data.c_str());
#else
    HSMessageBox(data.c_str());
#endif
	
}

CCString* HSJava::JavaExec(const char* json)
{
    HSAssert(json != NULL,"");
    CCString* pstr = NULL;
#if HSAndroid
	CCLog("-Android- -------------------");
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","exec","(Ljava/lang/String;)Ljava/lang/String;");
	if (!isOk)
	{
		HSMessageBox("jni/JniHelper/init Fail");
		return NULL;
	}
	jstring jjson = minfo.env->NewStringUTF(json);
	//minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID,jjson);
    
	jstring obj = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID,jjson);
    
	std::string objstr = JniHelper::jstring2string(obj);
    
	if(objstr == "")
	{
		return NULL;
	}else{
		pstr = CCString::create(objstr);
	}
#elif HSIos
	pstr = Exec(json);
    return pstr;
    
#else
    HSMessageBox(json);
    pstr = NULL;

#endif
    
    return pstr;

}

void HSJava::KillProcess()
{
#if HSAndroid
	CCLog("-Android- -------------------");
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","killProcess","()V");
    
	if (!isOk)
	{
		HSMessageBox("jni/JniHelper/init Fail");
		return;
	}
    
	//jint = minfo.env->GetStaticIntField(minfo.classID,minfo.methodID);
	minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID);
    
	//minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
    
	CCLog("-Android- -------------------");
#endif
}

void HSJava::ShowToast( const char* text,int dt /*= 0*/ )
{
    
#if HSAndroid
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","showToast","(Ljava/lang/String;)V");
    
	if (!isOk)
	{
		HSMessageBox("jni/JniHelper/showToast Fail");
		return;
	}
	jstring jTitle = minfo.env->NewStringUTF(text);
	minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID,jTitle);
#else
    HSMessageBox(text);
    
#endif
}

void HSJava::OpenURL(const char* text)
{
#if HSAndroid
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","OpenURL","(Ljava/lang/String;)V");

	if (!isOk)
	{
		HSMessageBox("jni/JniHelper/OpenURL Fail");
		return;
	}
	jstring jTitle = minfo.env->NewStringUTF(text);
	minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID,jTitle);
#else
	HSMessageBox(text);
#endif
}

void HSJava::autoDistribute(const char* data,int size)
{
#if HSAndroid
    CCLog("%s 给JAVA 层发送数据",__FUNCTION__);
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","autoDistribute","([B)V");

	if(!isOk)
	{
		HSMessageBox("jni/JniHelper/autoDistribute Fail");
		return;
	}

	//jbyteArray bytes = minfo.env->NewByteArray(((jsize)size);
	 //将char* 转换为byte数组

	 //minfo.env->SetByteArrayRegion(bytes, 0, (jsize)size, (jbyte*)data);

	 //minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID,bytes);

	 jbyteArray bytes = minfo.env->NewByteArray((jsize)size);
	 //将char* 转换为byte数组
	 minfo.env->SetByteArrayRegion(bytes, 0, (jsize)size, (jbyte*)data);

	 minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID,bytes);
#else
    this->onHandleDistributeReceived(data, size);
#endif
}

void HSJava::TestProto(const char* pdata,int size)
{
    HSLanFilter::SharedLanFilter()->CreaterMessage((char*)pdata, size);
}

void HSJava::distributeDataToOthers(const char* data,int size)
{
#if HSAndroid
    CCLog("%s 给JAVA 层发送数据 %d",__FUNCTION__,size);
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","distributeDataToOthers","([BI)V");

	if(!isOk)
	{
		HSMessageBox("jni/JniHelper/distributeDataToOthers Fail");
		return;
	}

	 jbyteArray bytes = minfo.env->NewByteArray((jsize)size);
	 //将char* 转换为byte数组
	 minfo.env->SetByteArrayRegion(bytes, 0, (jsize)size, (jbyte*)data);

	 minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID,bytes,size);
#else
    this->onHandleDistributeReceived(data, size);
#endif
}


void HSJava::handleDistribute(const char* data,int size)
{
#if HSAndroid
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","handleDistribute","([B)V");

	if(!isOk)
	{
		HSMessageBox("jni/JniHelper/handleDistribute Fail");
		return;
	}

	 jbyteArray bytes = minfo.env->NewByteArray((jsize)size);
	 //将char* 转换为byte数组
	 minfo.env->SetByteArrayRegion(bytes, 0, (jsize)size, (jbyte*)data);

	 minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID,bytes);
#else

#endif
}

void HSJava::distribute(const char* data,int size)
{
#if HSAndroid
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","distribute","([B)V");

	if(!isOk)
	{
		HSMessageBox("jni/JniHelper/distribute Fail");
		return;
	}

	 jbyteArray bytes = minfo.env->NewByteArray((jsize)size);
	 //将char* 转换为byte数组
	 minfo.env->SetByteArrayRegion(bytes, 0, (jsize)size, (jbyte*)data);

	 minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID,bytes);
#else

#endif
}

void HSJava::onHandleDistribute(const char* data,int pdataSize)
{
        /* */
    CCLog("%s : 接收JAVA 层转发的数据 (size: %d)",__FUNCTION__,pdataSize);
    
}

void HSJava::onHandleDistributeReceived(const char* data,int pdataSize)
{
    CCLog("%s : 接收JAVA 层转发的数据 (size: %d)",__FUNCTION__,pdataSize);
    m_gameCacheDataLock.Lock();
    
    _CacheNode* cacheNode = new _CacheNode(data,pdataSize);
    
    m_GameCacheDataList.push_back(cacheNode);
    
    m_gameCacheDataLock.UnLock();
    
}

void HSJava::disConnect(bool b)
{
    HSLanActionManager::ShareLanActionManager()->AddAction(Lan_Action_QuitRoom);
#if HSAndroid
	CCLog("-Android- -------------------");
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","disConnect","(Z)V");

	if (!isOk)
	{
		HSMessageBox("jni/JniHelper/disConnect Fail");
		return;
	}
    jboolean jb = (jboolean)b;
	minfo.env->CallStaticIntMethod(minfo.classID,minfo.methodID,jb);

	CCLog("-Android- -------------------");
#else

#endif
}

void HSJava::StopSearchingShareCircle()
{
#if HSAndroid
	CCLog("-Android- -------------------");
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniEggshell","stopSearchingShareCircle","()V");
    
	if (!isOk)
	{
		HSMessageBox("jni/JniEggshell/stopSearchingShareCircle Fail");
		return;
	}
	minfo.env->CallStaticIntMethod(minfo.classID,minfo.methodID);
    
	CCLog("-Android- -------------------");
#endif
}

int HSJava::CheckUser()
{
    
#if HSAndroid
    
	Json::Value jsonData;
    
	jsonData["JNI_ID"] = Json::Value(2003);
    
	HSJson* hsJson = HSJson::CreateWithWriter();
    
	std::string data = hsJson->Writer(jsonData);
    
	CCString* pStr =  HSJava::ShaderJava()->JavaExec(data.c_str());
    
	HSJson* pJson = HSJson::CreateWithData(pStr->getCString());
    
    HSAssert(pJson, "");
    
    const Json::Value v = pJson->GetValue();
    
    int type = v["WEIBO_TYPE"].asInt();
    
    pStr->release();
    
    return type;
#else
    return 1;
#endif
}

void HSJava::NotifyVersionCode(int newVersionCode)
{
    HSJson* pJson = HSJson::CreateWithWriter();
    
	Json::Value jsonData;
    
	jsonData["JNI_ID"] = Json::Value(2004);
    
	jsonData["NEW_VERSIONCODE"] = Json::Value(newVersionCode);
    pJson->Writer(jsonData);
#if HSAndroid
    HSJava::ShaderJava()->JavaExec(pJson->Writer(jsonData).c_str());
#else
	HSMessageBox(pJson->Writer(jsonData).c_str());
#endif
    
    pJson->release();
}

int HSJava::GetVersion()
{
	int version = 0;
#if HSAndroid
	CCLog("-Android- -------------------");
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","getVersion","()I");
    
	if (!isOk)
	{
		HSMessageBox("jni/JniHelper/init Fail");
		return 0;
	}
    
	jint obj = (jint)minfo.env->CallStaticIntMethod(minfo.classID,minfo.methodID);
	CCLog("version(%d)",obj);
	version = (int)obj;
	return version;
#else
    
	version = 10101;
    
#endif
	return version;
}

CCString* HSJava::GetVersionName()
{
    CCString* pstr = NULL;
#if HSAndroid
	CCLog("-Android---------------------");
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","getVersionName","()Ljava/lang/String;");

	if(!isOk)
	{
		HSMessageBox("jni/JniHelper/GetVersionName Fail");
		return NULL;
	}

	jstring str = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);

	std::string objstr = JniHelper::jstring2string(str);

	if(objstr == "")
	{
		return NULL;
	}
	else
	{
		pstr = CCString::create(objstr);
		return pstr;
	}
#else
	return pstr = CCString::create("VersionName 1.0 ios");;
#endif
}

int HSJava::GetChannel()
{
	int channel = 0;
#if HSAndroid
	CCLog("-Android- -------------------");
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","getChannel","()I");
    
	if (!isOk)
	{
		HSMessageBox("jni/JniHelper/init Fail");
		return 0;
	}
    
	jint obj = (jint)minfo.env->CallStaticIntMethod(minfo.classID,minfo.methodID);
	CCLog("channel(%d)",obj);
	channel = (int)obj;

	CCLog("-Android- -------------------");
#else
    
	channel = 10003;
    
#endif
	return channel;
}

CCString* HSJava::GetPhoneModel()
{
    CCString* pstr = NULL;
    
#if HSAndroid
	JniMethodInfo minfo;
	bool isOk = JniHelper::getStaticMethodInfo(minfo,"jni/JniHelper","getPhoneModel","()Ljava/lang/String;");
    
	if(!isOk)
	{
		HSMessageBox("jni/JniHelper/init Fail");
		return NULL;
	}
	jstring obj = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
    
	std::string objstr = JniHelper::jstring2string(obj);
    
    
    
	if(objstr == "")
	{
		pstr = CCString::createWithFormat("%d", HSMath::Random(1000, 9999));
	}else{
		pstr = CCString::create(objstr);
	}
    HS_MUTABLE_GAME_CACHE_DATA_LAN()->set_name(pstr->getCString());
    
    
#else
    pstr = CCString::create("Lan_自己名字");
#endif
    
    HS_MUTABLE_GAME_CACHE_DATA_LAN()->set_name(pstr->getCString());
    string tempUUID = HSMath::GetUUID();
    HS_MUTABLE_GAME_CACHE_DATA_LAN()->set_uuid(tempUUID);
    
    return pstr;
}

//////////////////////////////////////////////////


void HSJava::Callback(const char* pJsonData)
{
	CCLOG(pJsonData);
    
    m_jsonCacheDataLock.Lock();
    
    _CacheNode* cacheNode = new _CacheNode(pJsonData,(int)strlen((char*)pJsonData));
    
    m_JsonCacheDataList.push_back(cacheNode);
    
    m_jsonCacheDataLock.UnLock();

	
}


#if HSIos
CCString* HSJava::Exec(const char* json)
{
    //const char* testJson = "{\"JNI_ID\":3001,\"JNI_EGG_ROOM_LIST\":[{\"JNI_EGG_ROOM_CURNUM\":1,\"JNI_EGG_ROOM_NAME\":\"yangzheng\",\"JNI_EGG_ROOM_MAXNUM\":2,\"JNI_EGG_IP\":\"192.168.43.1\"}]}";
    
    //const char* testJson = "{\"JNI_ID\":3001,\"JNI_EGG_ROOM_LIST\":[]}";
    
    HSJson* pJson = HSJson::CreateWithData(json);
    //HSJson* pJson = HSJson::CreateWithData(testJson);
    const Json::Value v = pJson->GetValue();
    
    int reqID  = v["JNI_ID"].asInt();
    
    switch (reqID)
    {
        case 2000:  //	授权接口
        {
            std::string wbType  = v["WEIBO_TYPE"].asString();
            HSSDK::SharedSDK()->SetWBType(wbType.c_str());
            
            HSSDK::SharedSDK()->SetGameUUID(HS_GAME_CACHE_DATA()->uid().c_str());
            
            HSSDK::SharedSDK()->SetAPPID(atoi(HS_Find_Configure("APPID").c_str()));
            
            HSSDK::SharedSDK()->Login(atoi(wbType.c_str()));
        }
            break;
        case 2002:
        {
            std::string wbType  = v["WEIBO_TYPE"].asString();
            std::string text = v["WEIBO_TEXT"].asString();
            HSSDK::SharedSDK()->PostText(text.c_str(),atoi(wbType.c_str()));
        }
            break;
        case 3000: //1.	创建房间接口
        {
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            HSLanRoomListScene* pLanRoomListScene = dynamic_cast<HSLanRoomListScene*>(pScene);
            if (pLanRoomListScene)
            {
                LanCreateRoomResponse* pCreateLanRoomRes = LanCreateRoomResponse::default_instance().New();
                pCreateLanRoomRes->set_jsonid(63000);
                pCreateLanRoomRes->set_jni_egg_result(0);
                
                pLanRoomListScene->GetHSLanRoomListLayer()->ResponseLanCreateRoom(pCreateLanRoomRes);
            }
            
        }
            break;
        case 3001: //2.	查询房间接口
        {
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            HSLanRoomListScene* pHSLanRoomListScene = dynamic_cast<HSLanRoomListScene*>(pScene);
            if (pHSLanRoomListScene)
            {
                LanSearchRoomResponse pRes = LanSearchRoomResponse::default_instance();
                pRes.set_jsonid(reqID);
                
                HSJsonValue vTemp = v["JNI_EGG_ROOM_LIST"];
                
                for (int i=0; i<vTemp.size(); ++i)
                {
                    string roomName = vTemp[i]["JNI_EGG_ROOM_NAME"].asCString();
                    int roomMaxCount = vTemp[i]["JNI_EGG_ROOM_MAXNUM"].asInt();
                    int roomCurrent = vTemp[i]["JNI_EGG_ROOM_CURNUM"].asInt();
                    string ssid = vTemp[i]["JNI_EGG_SSID"].asCString();
                    
                    LanSearchRoomResponse_room* pRoom = pRes.add_roomlist();
                    pRoom->set_jni_egg_room_name(roomName);
                    pRoom->set_jni_egg_room_maxnum(roomMaxCount);
                    pRoom->set_jni_egg_room_curnum(roomCurrent);
                    pRoom->set_jni_egg_ssid(ssid);
                }
                pHSLanRoomListScene->GetHSLanRoomListLayer()->ResponseLanSearchRoom(&pRes);
            }
//            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
//            HSGameMainScene* pGameMainScene = dynamic_cast<HSGameMainScene*>(pScene);
//            if (pGameMainScene)
//            {
//                LanSearchRoomResponse* pRes = LanSearchRoomResponse::default_instance().New();
//                pRes->set_jsonid(63001);
//                
//                
//                for (int i=0; i<10; ++i)
//                {
//                    CCString* pRoomName = CCString::createWithFormat("房间: [ %d ]",i);
//                    string roomName = pRoomName->getCString();
//                    int roomMaxCount = 2;
//                    int roomCurrent = 1;
//                    
//                    LanSearchRoomResponse_room* pRoom = pRes->add_roomlist();
//                    pRoom->set_jni_egg_room_name(roomName);
//                    pRoom->set_jni_egg_room_maxnum(roomMaxCount);
//                    pRoom->set_jni_egg_room_curnum(roomCurrent);
//                    pRoom->set_jni_egg_ip("192.168.xx.xx");
//                    
//                    pRoomName->release();
//                }
//                pGameMainScene->GetHSGameMainLayer()->ResponseLanSearchRoom(pRes);
//            }
            
        }
            break;
        case 3002: //3.	加入房间接口
        {
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            HSLanRoomListScene* pLanRoomListScene = dynamic_cast<HSLanRoomListScene*>(pScene);
            if (pLanRoomListScene)
            {
                LanJoinRoomResponse* pRes = LanJoinRoomResponse::default_instance().New();
                pRes->set_jsonid(63002);
                pRes->set_jni_egg_result(0);
                pRes->set_jni_egg_status(0);
                
                pLanRoomListScene->GetHSLanRoomListLayer()->ResponseLanJoinRoom(pRes);
            }
            
        }
            break;
        default:
            break;
    }
    
    CC_SAFE_RELEASE_NULL(pJson);
    
    return NULL;
    
}

#endif

void HSJava::Updata(float dt)
{
    if (m_JsonCacheDataList.size() > 0)
    {
        
        _CacheNode* pCacheNode = m_JsonCacheDataList[0];
        
        CCLog("%s 开始处理Json数据 ( %s )",__FUNCTION__,pCacheNode->data);
        
        this->HandleJsonCacheData(pCacheNode->data, pCacheNode->size);
        
        CC_SAFE_DELETE(pCacheNode);
        
        m_JsonCacheDataList.erase(m_JsonCacheDataList.begin());
        
        CCLog("%s 处理完成Json数据 ( 剩余 %d ) )",__FUNCTION__,m_JsonCacheDataList.size());
        
    }else if(m_GameCacheDataList.size() > 0){
        
        _CacheNode* pCacheNode = m_GameCacheDataList[0];
        
        CCLog("%s 开始处理 Game 数据 size = %d",__FUNCTION__,pCacheNode->size);
        
        this->HandleGameCacheData(pCacheNode->data, pCacheNode->size);
        
        CC_SAFE_DELETE(pCacheNode);
        
        m_GameCacheDataList.erase(m_GameCacheDataList.begin());
        
        CCLog("%s 处理完成 Game 数据 ( 剩余 %d )",__FUNCTION__,m_GameCacheDataList.size());
    }
}

void HSJava::HandleJsonCacheData(const char* pData,int size)
{
    HSJson* pJson = HSJson::CreateWithData(pData);
    HSAssert(pJson, "");
    
    const Json::Value v = pJson->GetValue();
    
    int responseID  = v["JNI_ID"].asInt();
    
    
    switch (responseID)
    {
        case 62000:
        {
            
        	string status = v["WEIBO_RESULT"].asString();
            
        	eventDict dict;
            
            
        	if (0 == strcmp("99", HS_GAME_CACHE()->GetLoginType()))
			{
				dict["logintype"] = "99";
			}
			else
			{
				dict["logintype"] = HS_Find_Configure("ChannelID").c_str();
			}
            
        	if(status == "")
        	{
        		if(HS_GAME_CACHE()->m_isRegistSuccess)//说明刚刚成功注册
        		{
        			MobClickCpp::event("HSThirdPartRegist",&dict);
        			//MobClickCpp::endEvent("HSThirdPartRegistTime");
        			MobClickCpp::endEventWithAttributes("HSThirdPartRegistTime","hs");
        		}
        		else
        		{
        			MobClickCpp::event("HSThirdPart",&dict);
        			//MobClickCpp::endEvent("HSThirdPartTime");
        			MobClickCpp::endEventWithAttributes("HSThirdPartTime","hs");
        		}
        	}
            
            
        	if(status == "" || status == "s10011")
        	{
        		const char* weiBoUUID = v["WEIBO_OPENID"].asCString();
                
        		HS_ShowLoading();
        		HSLoadingLayer::ShareLoading()->SetTime(10);
        		HSRequest::ShareRequest()->SendLoginRequest(weiBoUUID);
				HS_MUTABLE_GAME_CACHE_DATA()->set_weibo_id(weiBoUUID);
				HS_MUTABLE_GAME_CACHE_DATA()->set_weibo_name(v["WEIBO_NAME"].asCString());
                
        	}
        	else
        	{
                HS_MUTABLE_GAME_CACHE_DATA()->Clear();
                HS_GAME_CACHE()->Save();
                //this->ShowToast(v["WEIBO_ERR"].asCString(),0);
                //HSLoadingLayer::ShareLoading()->setVisible(false);
                HS_GO_SCENE(HS_SCENE_GameMainScene);
        	}
        }
            break;
        case 63000: //1.	创建房间接口
        {
//            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
//            HSLanRoomListScene* pLanRoomListScene = dynamic_cast<HSLanRoomListScene*>(pScene);
//            if (pLanRoomListScene)
//            {
//                LanCreateRoomResponse* pCreateLanRoomRes = LanCreateRoomResponse::default_instance().New();
//                pCreateLanRoomRes->set_jsonid(responseID);
//                pCreateLanRoomRes->set_jni_egg_result(v["JNI_EGG_RESULT"].asInt());
//                
//                pLanRoomListScene->GetHSLanRoomListLayer()->ResponseLanCreateRoom(pCreateLanRoomRes);
//                
//                CC_SAFE_DELETE(pCreateLanRoomRes);
//            }
            HS_MUTABLE_TARGET_TARGET()->Clear();
            if(v["JNI_EGG_RESULT"].asInt() == 0)
            {
                HSLanActionManager::ShareLanActionManager()->m_CreateRoom = Lan_Action_Status_Success;
                HS_GAME_CACHE()->m_isJoinRoomSucceed = true;
                //设置自己为房主
                HS_MUTABLE_GAME_CACHE_DATA_LAN()->set_type(0);
                //去配对界面
                //HS_GO_SCENE(HS_SCENE_GamePairScene);
                
            }else{
                HSLanActionManager::ShareLanActionManager()->m_CreateRoom = Lan_Action_Status_Fail;
                HSMessageBox("创建房间失败");
                HS_GAME_CACHE()->m_isJoinRoomSucceed = false;
            }
            

            HSLanActionManager::ShareLanActionManager()->Pop();
        }
            break;
        case 63001: //2.	查询房间接口
        {
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            HSLanRoomListScene* pHSLanRoomListScene = dynamic_cast<HSLanRoomListScene*>(pScene);
            if (pHSLanRoomListScene)
            {
                LanSearchRoomResponse pRes = LanSearchRoomResponse::default_instance();
                pRes.set_jsonid(responseID);
                
                HSJsonValue vTemp = v["JNI_EGG_ROOM_LIST"];
                
                for (int i=0; i<vTemp.size(); ++i)
                {
                    string roomName = vTemp[i]["JNI_EGG_ROOM_NAME"].asCString();
                    CCLOG("RoomName[%d]: %s",i,roomName.c_str());
                    int roomMaxCount = vTemp[i]["JNI_EGG_ROOM_MAXNUM"].asInt();
                    int roomCurrent = vTemp[i]["JNI_EGG_ROOM_CURNUM"].asInt();
                    string ssid = vTemp[i]["JNI_EGG_SSID"].asCString();
                    
                    LanSearchRoomResponse_room* pRoom = pRes.add_roomlist();
                    pRoom->set_jni_egg_room_name(roomName);
                    pRoom->set_jni_egg_room_maxnum(roomMaxCount);
                    pRoom->set_jni_egg_room_curnum(roomCurrent);
                    pRoom->set_jni_egg_ssid(ssid);
                }
                pHSLanRoomListScene->GetHSLanRoomListLayer()->ResponseLanSearchRoom(&pRes);
            }
            HSLanActionManager::ShareLanActionManager()->m_SearchRoom = Lan_Action_Status_Success;
            HSLanActionManager::ShareLanActionManager()->Pop();
            
        }
            break;
        case 63002: //3.	加入房间接口
        {
            int result = v["JNI_EGG_RESULT"].asInt();
            int status = v["JNI_EGG_STATUS"].asInt();
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            HSLanRoomListScene* pLanRoomListScene = dynamic_cast<HSLanRoomListScene*>(pScene);
            if (pLanRoomListScene)
            {
                
                LanJoinRoomResponse* pRes = LanJoinRoomResponse::default_instance().New();
                pRes->set_jsonid(responseID);
                pRes->set_jni_egg_result(result);
                pRes->set_jni_egg_status(status);
                
                pLanRoomListScene->GetHSLanRoomListLayer()->ResponseLanJoinRoom(pRes);

            }else{
                CCLog("加入房间失败 不在当前场景 %d-%d",result,status);
            }
            
            if ( result == 0)
            {
                HSLanActionManager::ShareLanActionManager()->m_JoinRoom = Lan_Action_Status_Success;
            }else{
                HSLanActionManager::ShareLanActionManager()->m_JoinRoom = Lan_Action_Status_Fail;
            }
            
            HSLanActionManager::ShareLanActionManager()->Pop();
            
//            int result = v["JNI_EGG_RESULT"].asInt();
//            
//            if(result == 0)
//            {
//                //发送自己的数据
//                //设置自己为房间成员
//                HS_MUTABLE_GAME_CACHE_DATA_LAN()->set_type(1);
//                HSLanRequest::ShareLanRequest()->SendLanSyncUserInfoNotice();
//                
//                HS_GAME_CACHE()->m_isJoinRoomSucceed = true;
//            }else{
//                HS_GAME_CACHE()->m_isJoinRoomSucceed = false;
//            }
            
        }
            break;
            
        case 63007: //4.    退出房间回调     异常退出
        {
            string userName = v["JNI_EGG_USER_NAME"].asString();
            
            CCLog("异常 [ %s ] 退出",userName.c_str());
            
            
            UserBasicInfo* pTarget = HS_MUTABLE_TARGET_TARGET();
            pTarget->Clear();
            HS_GAME_CACHE()->m_LanTargetInfo.Clear();
            
            //HS_GO_SCENE(HS_SCENE_LanRoomListScene);
            HS_GO_SCENE(HS_SCENE_GameMainScene);
        }
            break;
            
        case 63008:  // 关闭热点 回调  正常退出
        {
            int b = v["JNI_EGG_WIFI_CLOSE"].asInt();
            
            HSLanActionManager::ShareLanActionManager()->m_QuitRoom = Lan_Action_Status_Success;
            HSLanActionManager::ShareLanActionManager()->Pop();

//            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
//            HSGamePairScene* pHSGamePairScene = dynamic_cast<HSGamePairScene*>(pScene);
//            if(pHSGamePairScene)
//            {
//                CCLog("服务端 退出房间成功 关闭 WIFI 状态 [ %d ]",b);
//                HS_GO_SCENE(HS_SCENE_LanRoomListScene);
//            }

        }
            break;
        case 63009:    //恢复wifi
        {
            int r = v["JNI_EGG_WIFI_RESTORE"].asInt();
            if(r == 0)
            {
                HSLanActionManager::ShareLanActionManager()->m_RestoreWIFI = Lan_Action_Status_Success;
                HSJava::ShaderJava()->ShowToast("WIFI 恢复成功");
            }else{
                HSLanActionManager::ShareLanActionManager()->m_RestoreWIFI = Lan_Action_Status_Fail;
                HSJava::ShaderJava()->ShowToast("WIFI 恢复失败");
            }
            
//            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
//            HSGameMainScene* pHSGameMainScene = dynamic_cast<HSGameMainScene*>(pScene);
//            if (pHSGameMainScene)
//            {
//                CCLog("WIFI 恢复 %d",r);
//                if(r == 0)
//                {
//                    HS_HideLoading();
//                }else{
//                    HSNetworkDialog::ShareNetworkDialog()->Show();
//                }
//            }
        }
            break;
            
        case 63010:
        {
            int e0 = v["Excption_CreateShareCircle"].asInt();
            int e1 = v["Excption_CreateClient"].asInt();
            int e2 = v["Excption_SearchShard"].asInt();//
            int e3 = v["Excption_SearchShardOuttime"].asInt();
            
            if ( e0 == 1)
            {
                HSMessageBox("创建服务端 异常");
            }
            if ( e1 == 1)
            {
                HSMessageBox("创建客户端 异常");
            }
            if ( e2 == 1)
            {
                HSMessageBox("搜索房间 异常");
            }
            if( e3 == 1)
            {
                HSMessageBox("搜索房间超时 异常");
            }
        }
        	break;
        default:
            break;
    }
    
    CC_SAFE_RELEASE_NULL(pJson);
}

void HSJava::HandleGameCacheData(const char* pData,int size)
{
    HSLanFilter::SharedLanFilter()->CreaterMessage((char*)pData, size);
}












