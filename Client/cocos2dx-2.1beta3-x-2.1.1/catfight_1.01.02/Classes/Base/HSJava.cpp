#include "HSJava.h"
#include "HSGameCache.h"
#include "HSGameSceneJumpManage.h"
#include "HSJson.h"
#include "HSRequest.h"
#include "MobClickCpp.h"
#include "HSTool.h"

#if HSIos
#include "HSSDK.h"
#endif


static HSJava* s_hsJAVA = new HSJava;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
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
						CCDirector::sharedDirector()->end();
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

	jstring obj = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID,jjson);

	std::string objstr = JniHelper::jstring2string(obj);

	if(objstr == "")
	{
		return NULL;
	}else{
		CCString* pstr = CCString::create(objstr);

		return pstr;
	}
#elif HSIos
    
    return Exec(json);
    
#else
    HSMessageBox(json);
    return NULL;
#endif

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

void HSJava::ShowToast( const char* text,int dt )
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
    return 0;
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
	return obj;
	//return 10101;
	CCLog("-Android- -------------------");
#else

	return 10101;

#endif
}

CCString* HSJava::GetVersionName()
{
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
		CCString* pstr = CCString::create(objstr);
		return pstr;
	}
#else
	return NULL;
#endif
}

int HSJava::GetChannel()
{
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
	return obj;
	//return 10003;
	CCLog("-Android- -------------------");
#else

	return 10003;

#endif
}

//////////////////////////////////////////////////


void HSJava::Callback(const char* pJsonData)
{
	HSJson* pJson = HSJson::CreateWithData(pJsonData);
    HSAssert(pJson, "");

    const Json::Value v = pJson->GetValue();
    
    int responseID  = v["JNI_ID"].asInt();

    int status = v["WEIBO_RESULT"].asInt();

    switch (responseID)
    {
        case 62000:
        {

        	eventDict dict;


        	if (0 == strcmp("99", HS_GAME_CACHE()->GetLoginType()))
			{
				dict["logintype"] = "99";
			}
			else
			{
				dict["logintype"] = HS_Find_Configure("ChannelID").c_str();
			}

        	if(status ==0)
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


        	if(status ==0)
        	{
        		const char* weiBoUUID = v["WEIBO_OPENID"].asCString();

        		//HS_ShowLoading();
        		HSLoadingLayer::ShareLoading()->SetTime(30);
        		HSRequest::ShareRequest()->SendLoginRequest(weiBoUUID);
				HS_MUTABLE_GAME_CACHE_DATA()->set_weibo_id(weiBoUUID);
				HS_MUTABLE_GAME_CACHE_DATA()->set_weibo_name(v["WEIBO_NAME"].asCString());

        	}
        	else
        	{
                HSLoadingLayer::ShareLoading()->setVisible(false);
        		this->ShowToast(v["WEIBO_ERR"].asCString(),0);
        	}
        }
        break;
        case 66000:
        	//HS_HideLoading();
        	break;
        default:
            break;
    }
}


#if HSIos
CCString* HSJava::Exec(const char* json)
{
    HSJson* pJson = HSJson::CreateWithData(json);
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
            
        default:
            break;
    }
    
    
}
#endif














