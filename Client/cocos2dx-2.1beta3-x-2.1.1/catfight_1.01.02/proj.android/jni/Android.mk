LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game_shared
LOCAL_MODULE_FILENAME := libgame


################################################################ 
#		 Ambition  [FileCount:46157]		Time:	2013-11-22 09:41:48
################################################################ 


LOCAL_SRC_FILES := Main/main.cpp \
Umeng/MobClickCpp.cpp \
../../Classes/Base/BuyGold.pb.cpp \
../../Classes/Base/GameCacheData.pb.cpp \
../../Classes/Base/HSGameGuide.pb.cpp \
../../Classes/Base/PropInfo.pb.cpp \
../../Classes/Base/PropInfoData.pb.cpp \
../../Classes/LibStructure/HSLanguage.pb.cpp \
../../Classes/LibStructure/HSMessage.pb.cpp \
../../Classes/LibStructure/UIData.pb.cpp \
../../Classes/NetMessage/Achievement.pb.cpp \
../../Classes/NetMessage/AddFriend.pb.cpp \
../../Classes/NetMessage/Address.pb.cpp \
../../Classes/NetMessage/AddressBook.pb.cpp \
../../Classes/NetMessage/BattleData.pb.cpp \
../../Classes/NetMessage/BattleInfoData.pb.cpp \
../../Classes/NetMessage/BattlePing.pb.cpp \
../../Classes/NetMessage/BattleReady.pb.cpp \
../../Classes/NetMessage/BattleResult.pb.cpp \
../../Classes/NetMessage/BattleTranscribeData.pb.cpp \
../../Classes/NetMessage/Buff.pb.cpp \
../../Classes/NetMessage/ClaimedDailyReward.pb.cpp \
../../Classes/NetMessage/DailyRewardSystem.pb.cpp \
../../Classes/NetMessage/DestroyBalloon.pb.cpp \
../../Classes/NetMessage/Email.pb.cpp \
../../Classes/NetMessage/ErrorMessage.pb.cpp \
../../Classes/NetMessage/ExitAdvanced.pb.cpp \
../../Classes/NetMessage/Fighting.pb.cpp \
../../Classes/NetMessage/FriendList.pb.cpp \
../../Classes/NetMessage/GameLog.pb.cpp \
../../Classes/NetMessage/GamePing.pb.cpp \
../../Classes/NetMessage/Heartbeat.pb.cpp \
../../Classes/NetMessage/KickOutDungoen.pb.cpp \
../../Classes/NetMessage/Login.pb.cpp \
../../Classes/NetMessage/OpenEmail.pb.cpp \
../../Classes/NetMessage/Playerdisengage.pb.cpp \
../../Classes/NetMessage/ReceiveAchievementReward.pb.cpp \
../../Classes/NetMessage/Recharge.pb.cpp \
../../Classes/NetMessage/Register.pb.cpp \
../../Classes/NetMessage/RoomData.pb.cpp \
../../Classes/NetMessage/SearchUserInfo.pb.cpp \
../../Classes/NetMessage/SendEmail.pb.cpp \
../../Classes/NetMessage/StartBattle.pb.cpp \
../../Classes/NetMessage/TargetInfo.pb.cpp \
../../Classes/NetMessage/UseBuff.pb.cpp \
../../Classes/NetMessage/UseProp.pb.cpp \
../../Classes/NetMessage/UserInfo.pb.cpp \
../../Classes/NetMessage/UserInfoUpdate.pb.cpp \
../../Classes/Base/HSBox2dShapeCache.cpp \
../../Classes/Base/HSFeedbackLayer.cpp \
../../Classes/Base/HSGameCache.cpp \
../../Classes/Base/HSGameDialogLayer.cpp \
../../Classes/Base/HSGameGuide.cpp \
../../Classes/Base/HSInputDialogLayer.cpp \
../../Classes/Base/HSJava.cpp \
../../Classes/Base/HSLoadingLayer.cpp \
../../Classes/Base/HSLog.cpp \
../../Classes/Base/HSShareLayer.cpp \
../../Classes/Base/HSTool.cpp \
../../Classes/GameBody/AchievementSystem/HSAchievemenLsitView.cpp \
../../Classes/GameBody/AchievementSystem/HSAchievemenScene.cpp \
../../Classes/GameBody/AchievementSystem/HSAchievemenSrpite.cpp \
../../Classes/GameBody/AddressBook/HSAddressBookListVeiw.cpp \
../../Classes/GameBody/AddressBook/HSAddressBookScene.cpp \
../../Classes/GameBody/AddressBook/HSAddressSprite.cpp \
../../Classes/GameBody/Battle/DebuffProp/HSPropBalloonInterface.cpp \
../../Classes/GameBody/Battle/GainProp/HSPropIconInterface.cpp \
../../Classes/GameBody/Battle/GainProp/HSPropManager.cpp \
../../Classes/GameBody/Battle/GainProp/HSProp_Chameleon.cpp \
../../Classes/GameBody/Battle/GainProp/HSProp_EnergyShield.cpp \
../../Classes/GameBody/Battle/GainProp/HSProp_LaserGun.cpp \
../../Classes/GameBody/Battle/GainProp/HSProp_Meidusha.cpp \
../../Classes/GameBody/Battle/HSBalloonFactory.cpp \
../../Classes/GameBody/Battle/HSBalloonSprite.cpp \
../../Classes/GameBody/Battle/HSBattleOverLayer.cpp \
../../Classes/GameBody/Battle/HSBattleScene.cpp \
../../Classes/GameBody/Battle/HSBattleTranscribe.cpp \
../../Classes/GameBody/Battle/HSContacListener.cpp \
../../Classes/GameBody/Battle/HSCrossBorderInterface.cpp \
../../Classes/GameBody/Battle/HSEffectItemSprite.cpp \
../../Classes/GameBody/Battle/HSGameGuideRaycastCallback.cpp \
../../Classes/GameBody/Battle/HSLine.cpp \
../../Classes/GameBody/Battle/HSPoint.cpp \
../../Classes/GameBody/Battle/HSRankUpLayer.cpp \
../../Classes/GameBody/Battle/HSRaycastCallback.cpp \
../../Classes/GameBody/Cover/HSGameCoverScene.cpp \
../../Classes/GameBody/Cover/HSGameFrisbee.cpp \
../../Classes/GameBody/Cover/PlayerInfo/HSGamePlayerInfoLayer.cpp \
../../Classes/GameBody/Cover/PlayerInfo/HSHeadSprite.cpp \
../../Classes/GameBody/Cover/PlayerInfo/HSPlayerInfoListView.cpp \
../../Classes/GameBody/Cover/PlayerInfo/HSPlayerInfoSprite.cpp \
../../Classes/GameBody/Cover/Shop/HSGameShopScene.cpp \
../../Classes/GameBody/Cover/Shop/HSShopListView.cpp \
../../Classes/GameBody/Cover/Shop/HSShopSprite.cpp \
../../Classes/GameBody/Cover/HSAboutLayer.cpp \
../../Classes/GameBody/DailyRewardSystem/HSDailyRewardSystemLayer.cpp \
../../Classes/GameBody/EmailSystem/HSEmailListVeiw.cpp \
../../Classes/GameBody/EmailSystem/HSEmailSprite.cpp \
../../Classes/GameBody/EmailSystem/HSEmailSystemScene.cpp \
../../Classes/GameBody/FriendsSystem/HSFriendInfoSprite.cpp \
../../Classes/GameBody/FriendsSystem/HSFriendsListVeiw.cpp \
../../Classes/GameBody/FriendsSystem/HSFriendsSystemScene.cpp \
../../Classes/GameBody/Pair/EffectProp/HSEffect_BlackInk.cpp \
../../Classes/GameBody/Pair/EffectProp/HSEffect_ColorfulCandy.cpp \
../../Classes/GameBody/Pair/EffectProp/HSEffect_SickMucus.cpp \
../../Classes/GameBody/Pair/HSEquipFrame.cpp \
../../Classes/GameBody/Pair/HSGameAdvancedPairLayer.cpp \
../../Classes/GameBody/Pair/HSGamePairScene.cpp \
../../Classes/GameBody/Pair/HSGameSelectPropLayer.cpp \
../../Classes/GameBody/Pair/HSPropItemSprite.cpp \
../../Classes/GameBody/Pair/HSUseBufferLayer.cpp \
../../Classes/GameBody/SeniortSystem/HSGoldInadequateDialog.cpp \
../../Classes/GameBody/SeniortSystem/HSRoomListView.cpp \
../../Classes/GameBody/SeniortSystem/HSRoomSprite.cpp \
../../Classes/GameBody/SeniortSystem/HSSeniortSystemScene.cpp \
../../Classes/GameBody/Logo/HSLogoScene.cpp \
../../Classes/GameMain/AppDelegate.cpp \
../../Classes/GameMain/HelloWorldScene.cpp \
../../Classes/GameMain/HSGameMainScene.cpp \
../../Classes/GameMain/HSGameSceneJumpManage.cpp \
../../Classes/LibBase/GE_Base.cpp \
../../Classes/LibBase/GLES-Render.cpp \
../../Classes/LibBase/HSBase.cpp \
../../Classes/LibBase/HSDataStruct.cpp \
../../Classes/LibBase/HSMacros.cpp \
../../Classes/LibBase/HSToolBase.cpp \
../../Classes/LibBox2d/HSBox2dTool.cpp \
../../Classes/LibFunction/HSFileData.cpp \
../../Classes/LibFunction/HSJson.cpp \
../../Classes/LibFunction/HSLanguage.cpp \
../../Classes/LibFunction/HSOffset.cpp \
../../Classes/LibFunction/HSReadData.cpp \
../../Classes/LibFunction/HSReadPlist.cpp \
../../Classes/LibFunction/HSReadUI.cpp \
../../Classes/LibFunction/HSSoundManage.cpp \
../../Classes/LibFunction/HSTime.cpp \
../../Classes/LibFunction/HSVisibleRect.cpp \
../../Classes/LibFunction/HSWriteData.cpp \
../../Classes/LibInterface/HSListViewInterface/HSCellInterface.cpp \
../../Classes/LibInterface/HSListViewInterface/HSItemDataInterface.cpp \
../../Classes/LibInterface/HSListViewInterface/HSListViewInterface.cpp \
../../Classes/LibInterface/HSListViewInterface/HSTouchItemInterface.cpp \
../../Classes/LibInterface/HSModalDialogInterface/HSModalDialogInterface.cpp \
../../Classes/LibIO/IO_Base.cpp \
../../Classes/LibIO/IO_CharDecoder.cpp \
../../Classes/LibIO/IO_CharEncoder.cpp \
../../Classes/LibIO/IO_CircularBuffer.cpp \
../../Classes/LibIO/IO_ConfigFile.cpp \
../../Classes/LibIO/IO_DataBlock.cpp \
../../Classes/LibIO/IO_Exception.cpp \
../../Classes/LibIO/IO_InputBuffer.cpp \
../../Classes/LibIO/IO_InputDataStream.cpp \
../../Classes/LibIO/IO_InputFile.cpp \
../../Classes/LibIO/IO_InputStream.cpp \
../../Classes/LibIO/IO_InputTextStream.cpp \
../../Classes/LibIO/IO_ISerialize.cpp \
../../Classes/LibIO/IO_OutputBuffer.cpp \
../../Classes/LibIO/IO_OutputDataStream.cpp \
../../Classes/LibIO/IO_OutputFile.cpp \
../../Classes/LibIO/IO_OutputStream.cpp \
../../Classes/LibIO/IO_OutputTextStream.cpp \
../../Classes/LibJni/HSJni.cpp \
../../Classes/LibMath/HSMath.cpp \
../../Classes/LibMath/HSTriangular.cpp \
../../Classes/LibMath/HSVector2d.cpp \
../../Classes/LibNet/HSIPAddress.cpp \
../../Classes/LibNet/HSSocketInterface.cpp \
../../Classes/LibNet/HSSocketRecvData.cpp \
../../Classes/LibNet/HSSocketSendData.cpp \
../../Classes/LibNewCocos2dx/HSCCLayer.cpp \
../../Classes/LibNewCocos2dx/HSCCSprite.cpp \
../../Classes/LibNewCocos2dx/HSClippingNode.cpp \
../../Classes/LibNewCocos2dx/HSDrawLines.cpp \
../../Classes/LibNewCocos2dx/HSFadeIn.cpp \
../../Classes/LibNewCocos2dx/HSGraySprite.cpp \
../../Classes/LibNewCocos2dx/HSSet.cpp \
../../Classes/LibNewCocos2dx/HSTableMenu.cpp \
../../Classes/LibNewCocos2dx/HSTexture2D.cpp \
../../Classes/LibSPX/SPX_Action.cpp \
../../Classes/LibSPX/SPX_Base.cpp \
../../Classes/LibSPX/SPX_Bitmap.cpp \
../../Classes/LibSPX/SPX_Data.cpp \
../../Classes/LibSPX/SPX_Demo.cpp \
../../Classes/LibSPX/SPX_Element.cpp \
../../Classes/LibSPX/SPX_Frame.cpp \
../../Classes/LibSPX/SPX_FrameSequence.cpp \
../../Classes/LibSPX/SPX_ISpriteEvent.cpp \
../../Classes/LibSPX/SPX_Manager.cpp \
../../Classes/LibSPX/SPX_Rect.cpp \
../../Classes/LibSPX/SPX_SequenceItem.cpp \
../../Classes/LibSPX/SPX_Skin.cpp \
../../Classes/LibSPX/SPX_Sprite.cpp \
../../Classes/LibSPX/SPX_Tile.cpp \
../../Classes/LibSPX/SPX_TileElement.cpp \
../../Classes/LibSPX/SPX_TileSet.cpp \
../../Classes/LibTemplate/HSObjectPool.cpp \
../../Classes/LibThread/HSLock.cpp \
../../Classes/LibThread/HSSem.cpp \
../../Classes/LibThread/HSThread.cpp \
../../Classes/Network/HSDataCache.cpp \
../../Classes/Network/HSFilter.cpp \
../../Classes/Network/HSProtocol.cpp \
../../Classes/Network/HSRequest.cpp \
../../Classes/Network/HSResponse.cpp \
../../Classes/Network/HSSocket.cpp \
../../Classes/Network/HSSocketPool.cpp \
../../Classes/Network/HSSocketTemp.cpp



LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					  $(LOCAL_PATH)/../../../cocos2dx/jsoncpp/include \
					  $(LOCAL_PATH)/../../../cocos2dx/jsoncpp/include/json \
					  $(LOCAL_PATH)/../../../cocos2dx/google \
					  $(LOCAL_PATH)/../../Classes/Base \
					  $(LOCAL_PATH)/../../Classes/GameBody \
					  $(LOCAL_PATH)/../../Classes/GameBody/AchievementSystem \
					  $(LOCAL_PATH)/../../Classes/GameBody/AddressBook \
					  $(LOCAL_PATH)/../../Classes/GameBody/Battle \
					  $(LOCAL_PATH)/../../Classes/GameBody/Battle/DebuffProp \
					  $(LOCAL_PATH)/../../Classes/GameBody/Battle/GainProp \
					  $(LOCAL_PATH)/../../Classes/GameBody/Cover \
					  $(LOCAL_PATH)/../../Classes/GameBody/Cover/PlayerInfo \
					  $(LOCAL_PATH)/../../Classes/GameBody/Cover/Shop \
					  $(LOCAL_PATH)/../../Classes/GameBody/DailyRewardSystem \
					  $(LOCAL_PATH)/../../Classes/GameBody/EmailSystem \
					  $(LOCAL_PATH)/../../Classes/GameBody/FriendsSystem \
					  $(LOCAL_PATH)/../../Classes/GameBody/Pair \
					  $(LOCAL_PATH)/../../Classes/GameBody/Pair/EffectProp \
					  $(LOCAL_PATH)/../../Classes/GameBody/SeniortSystem \
					  $(LOCAL_PATH)/../../Classes/GameBody/Logo \
					  $(LOCAL_PATH)/../../Classes/GameMain \
					  $(LOCAL_PATH)/../../Classes/LibBase \
					  $(LOCAL_PATH)/../../Classes/LibBox2d \
					  $(LOCAL_PATH)/../../Classes/LibFunction \
					  $(LOCAL_PATH)/../../Classes/LibInterface \
					  $(LOCAL_PATH)/../../Classes/LibInterface/HSListViewInterface \
					  $(LOCAL_PATH)/../../Classes/LibInterface/HSModalDialogInterface \
					  $(LOCAL_PATH)/../../Classes/LibIO \
					  $(LOCAL_PATH)/../../Classes/LibJni \
					  $(LOCAL_PATH)/../../Classes/LibMath \
					  $(LOCAL_PATH)/../../Classes/LibNet \
					  $(LOCAL_PATH)/../../Classes/LibNewCocos2dx \
					  $(LOCAL_PATH)/../../Classes/LibShaders \
					  $(LOCAL_PATH)/../../Classes/LibSPX \
					  $(LOCAL_PATH)/../../Classes/LibStructure \
					  $(LOCAL_PATH)/../../Classes/LibTemplate \
					  $(LOCAL_PATH)/../../Classes/LibThread \
					  $(LOCAL_PATH)/../../Classes/NetMessage \
					  $(LOCAL_PATH)/../../Classes/Network \
					  $(LOCAL_PATH)/../../Classes/Umeng


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static protobuf_static jsoncpp_static 
#LOCAL_SHARED_LIBRARIES := bspatch

::LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../libs/libprotobuffull) -lprotobuf


include $(BUILD_SHARED_LIBRARY)
include $(LOCAL_PATH)/prebuilt/Android.mk
include $(LOCAL_PATH)/AndroidMMcasdkjni.mk
include $(LOCAL_PATH)/AndroidMMidentifyapp.mk

$(call import-module,cocos2dx/jsoncpp) \
$(call import-module,cocos2dx/google) \
$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)

