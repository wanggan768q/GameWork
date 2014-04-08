#include "HSJava.h"
#include "HSChannel.pb.h"
#include "HSGameCache.h"
#include "HSGameSceneJumpManage.h"
static HSJava* s_hsJAVA = new HSJava;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{

// 	void Java_com_zrlh_tom_pkmmq_HSChannelManager_CallBuy(JNIEnv *env, jobject thiz, jbyteArray buffer)
// 	{
// 		CCLog("-Android- Java_com_Zrong_HSBalloon_HSChannelManager_CallBuy   Begin");
// 
// 		const char* pData = HSJni::JByteArrayToCharArray(env,buffer);
// 		if (s_hsJAVA)
// 		{
// 			CCLog("s_hsJAVA");
// 			if (pData)
// 			{
// 				CCLog("pData");
// 				int pDataSize = strlen(pData);
// 				CCLog("bufferSize: %d",pDataSize);
// 				s_hsJAVA->CallBuy(pData,pDataSize);
// 			}
// 		}
// 		CCLog("-Android- Java_com_Zrong_HSBalloon_HSChannelManager_CallBuy  End");
// 	}

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
};
#endif







HSJava::HSJava(void)
{
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

void HSJava::CallBuy( const void* pData,int size )
{
	CCLog("-Android- CallBuy Begin");

	message::Channel* channel = message::Channel::default_instance().New();
	bool isOK = channel->ParseFromArray(pData,size);

	if(!isOK)
	{
		HSMessageBox("HSJava::CallBuy Fail");
		return;
	}

	message::Channel_Tom* tom = channel->mutable_tom();

	CCLog("gameMoney=%d",tom->gamemoney());
	CCLog("propid=%d",tom->propid());
	CCLog(tom->title().c_str());
	CCLog(tom->describe().c_str());

	int type = HS_PROP_TYPE(tom->propid());
	int index = HS_PROP_INDEX(tom->propid());
	int number =1;
	switch (type)
	{
	case HS_MANUAL_PROP_TYPE:
		HS_GAME_CACHE()->SetPropNumber(index,HS_GAME_CACHE()->GetPropNumber(index)+1);
		break;
	case HS_BUFFER_PROP_TYPE:
		HS_GAME_CACHE()->SetUseBufferPropData(&HS_GAME_CACHE()->GetPropInfoData()->bufferpropinfolist(0)); 
		HS_GO_SCENE(HS_SCENE_BattleScene);
		break;
	case HS_GIFT_PROP_TYPE:
		HS_GAME_CACHE()->SetPropNumber(index,HS_GAME_CACHE()->GetPropInfoData()->giftbagpropinfolist(index).giftbag(0).count());
		break;
	case HS_CHEAP_PROP_TYPE:
		HS_GAME_CACHE()->SetPropNumber(index,HS_GAME_CACHE()->GetPropNumber(index)+1);
		break;
	case HS_LOCK_PROP_TYPE:
		HS_GAME_CACHE()->SetIsPropSlotLock(false,index);
		break;
	}
	HSLog::ShareLog()->SendBuyGoodLog(LogRequest_BuyType_BuyItem,tom->propid(),number,LogRequest_BuyState_Success);
	HS_GAME_CACHE()->Save();

	CCLog("-Android- CallBuy End");
	 
}

void HSJava::CallBuy( int propID )
{
	int type = HS_PROP_TYPE(propID);
	int index = HS_PROP_INDEX(propID);
	int number =1;
	switch (type)
	{
	case HS_MANUAL_PROP_TYPE:
		HS_GAME_CACHE()->SetPropNumber(index,HS_GAME_CACHE()->GetPropNumber(index)+1);
		break;
	case HS_BUFFER_PROP_TYPE:
		HS_GAME_CACHE()->SetUseBufferPropData(&HS_GAME_CACHE()->GetPropInfoData()->bufferpropinfolist(0)); 
		HS_GO_SCENE(HS_SCENE_BattleScene);
		break;
	case HS_GIFT_PROP_TYPE:
		HS_GAME_CACHE()->SetPropNumber(index,HS_GAME_CACHE()->GetPropInfoData()->giftbagpropinfolist(index).giftbag(0).count());
		break;
	case HS_CHEAP_PROP_TYPE:
		HS_GAME_CACHE()->SetPropNumber(index,HS_GAME_CACHE()->GetPropNumber(index)+1);
		break;
	case HS_LOCK_PROP_TYPE:
		HS_GAME_CACHE()->SetIsPropSlotLock(false,index);
		break;
	}
	HSLog::ShareLog()->SendBuyGoodLog(LogRequest_BuyType_BuyItem,propID,number,LogRequest_BuyState_Success);
	HS_GAME_CACHE()->Save();
}

