LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game_shared
LOCAL_MODULE_FILENAME := libgame


################################################################ 
#		 Ambition  [FileCount:17130]		Time:	2013-07-26 11:29:44
################################################################ 


LOCAL_SRC_FILES := Main/main.cpp \
../../Classes/Base/GameCacheData.pb.cpp \
../../Classes/Base/HSChannel.pb.cpp \
../../Classes/Base/HSGameGuide.pb.cpp \
../../Classes/GameBody/Battle/HSStratagemData.pb.cpp \
../../Classes/GameBody/BuyProp/PropInfo.pb.cpp \
../../Classes/GameBody/BuyProp/PropInfoData.pb.cpp \
../../Classes/LibStructure/DownloadList.pb.cpp \
../../Classes/LibStructure/HSLanguage.pb.cpp \
../../Classes/LibStructure/HSMessage.pb.cpp \
../../Classes/LibStructure/IoFile.pb.cpp \
../../Classes/LibStructure/UIData.pb.cpp \
../../Classes/NetMessage/CombatGains.pb.cpp \
../../Classes/NetMessage/ErrorMessage.pb.cpp \
../../Classes/NetMessage/GameLog.pb.cpp \
../../Classes/NetMessage/Register.pb.cpp \
../../Classes/NetMessage/SearchRank.pb.cpp \
../../Classes/NetMessage/SearchWeeklyScore.pb.cpp \
../../Classes/Base/HSBox2dShapeCache.cpp \
../../Classes/Base/HSChannelManager.cpp \
../../Classes/Base/HSGameCache.cpp \
../../Classes/Base/HSGameGuide.cpp \
../../Classes/Base/HSJava.cpp \
../../Classes/Base/HSLoadingLayer.cpp \
../../Classes/Base/HSLog.cpp \
../../Classes/Base/HSTool.cpp \
../../Classes/GameBody/Battle/BalloonProp/HSPropSpriteInterface.cpp \
../../Classes/GameBody/Battle/BalloonProp/HSProp_AddStratagemLevel.cpp \
../../Classes/GameBody/Battle/BalloonProp/HSProp_Bomb.cpp \
../../Classes/GameBody/Battle/BalloonProp/HSProp_ChangeColor.cpp \
../../Classes/GameBody/Battle/BalloonProp/HSProp_Fog.cpp \
../../Classes/GameBody/Battle/BalloonProp/HSProp_Ink.cpp \
../../Classes/GameBody/Battle/BalloonProp/HSProp_King.cpp \
../../Classes/GameBody/Battle/BalloonProp/HSProp_Money.cpp \
../../Classes/GameBody/Battle/BalloonProp/HSProp_Shield.cpp \
../../Classes/GameBody/Battle/BalloonProp/HSProp_StopStratagemTime.cpp \
../../Classes/GameBody/Battle/BalloonProp/HSProp_SubStratagemLevel.cpp \
../../Classes/GameBody/Battle/BufferProp/HSBufferPropInterface.cpp \
../../Classes/GameBody/Battle/BufferProp/HSBufferPropManager.cpp \
../../Classes/GameBody/Battle/BufferProp/HSBufferProp_GoldErupt.cpp \
../../Classes/GameBody/Battle/HSBalloonConfig.cpp \
../../Classes/GameBody/Battle/HSBalloonFactory.cpp \
../../Classes/GameBody/Battle/HSBalloonSprite.cpp \
../../Classes/GameBody/Battle/HSBattleOverLayer.cpp \
../../Classes/GameBody/Battle/HSBattlePauseLayer.cpp \
../../Classes/GameBody/Battle/HSBattleScene.cpp \
../../Classes/GameBody/Battle/HSChangeColorEffect.cpp \
../../Classes/GameBody/Battle/HSComboManager.cpp \
../../Classes/GameBody/Battle/HSContacListener.cpp \
../../Classes/GameBody/Battle/HSInputDialogLayer.cpp \
../../Classes/GameBody/Battle/HSLightEffect.cpp \
../../Classes/GameBody/Battle/HSSoulEffect.cpp \
../../Classes/GameBody/Battle/HSStratagemManager.cpp \
../../Classes/GameBody/Battle/HSStratagemSprite.cpp \
../../Classes/GameBody/Battle/HSTouchBalloonEffect.cpp \
../../Classes/GameBody/Battle/ManualProp/HSProp_ChangeColorFullScreen.cpp \
../../Classes/GameBody/Battle/ManualProp/HSProp_KingTime.cpp \
../../Classes/GameBody/Battle/ManualProp/HSProp_Lightning.cpp \
../../Classes/GameBody/Battle/ManualProp/HSProp_StratagemLevelByZero.cpp \
../../Classes/GameBody/Battle/ManualProp/HSUsePropInterface.cpp \
../../Classes/GameBody/Battle/ManualProp/HSUsePropManager.cpp \
../../Classes/GameBody/BuyProp/HSBuyPropInfoDialog.cpp \
../../Classes/GameBody/BuyProp/HSBuyPropScene.cpp \
../../Classes/GameBody/BuyProp/HSBuySceneDialog.cpp \
../../Classes/GameBody/BuyProp/HSBuyShopDialog.cpp \
../../Classes/GameBody/BuyProp/HSBuySlotDialog.cpp \
../../Classes/GameBody/BuyProp/HSGameScenePropSprite.cpp \
../../Classes/GameBody/BuyProp/HSPropItemSprite.cpp \
../../Classes/GameBody/RankingList/HSRankCell.cpp \
../../Classes/GameBody/RankingList/HSRankingListScene.cpp \
../../Classes/GameBody/RankingList/HSRankListView.cpp \
../../Classes/GameBody/RankingList/HSUserRankDataBule.cpp \
../../Classes/GameBody/RankingList/HSUserRankDataRed.cpp \
../../Classes/GameBody/RankingList/HSUserRankSprite.cpp \
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
../../Classes/LibFunction/HSFileData.cpp \
../../Classes/LibFunction/HSLanguage.cpp \
../../Classes/LibFunction/HSReadData.cpp \
../../Classes/LibFunction/HSReadPlist.cpp \
../../Classes/LibFunction/HSReadUI.cpp \
../../Classes/LibFunction/HSSoundManage.cpp \
../../Classes/LibFunction/HSTime.cpp \
../../Classes/LibFunction/HSVisibleRect.cpp \
../../Classes/LibFunction/HSWriteData.cpp \
../../Classes/LibInterface/HSModalDialogInterface.cpp \
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
../../Classes/LibNewCocos2dx/HSCCLayer.cpp \
../../Classes/LibNewCocos2dx/HSCCSprite.cpp \
../../Classes/LibNewCocos2dx/HSClippingNode.cpp \
../../Classes/LibNewCocos2dx/HSDownload.cpp \
../../Classes/LibNewCocos2dx/HSDrawLines.cpp \
../../Classes/LibNewCocos2dx/HSGraySprite.cpp \
../../Classes/LibNewCocos2dx/HSSet.cpp \
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
../../Classes/Network/HSDataCache.cpp \
../../Classes/Network/HSFilter.cpp \
../../Classes/Network/HSProtocol.cpp \
../../Classes/Network/HSRequest.cpp \
../../Classes/Network/HSResponse.cpp \
../../Classes/Network/HSSocket.cpp \
../../Classes/Network/HSSocketPool.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					  $(LOCAL_PATH)/../../Classes/Base \
					  $(LOCAL_PATH)/../../Classes/GameBody \
					  $(LOCAL_PATH)/../../Classes/GameBody/Battle \
					  $(LOCAL_PATH)/../../Classes/GameBody/Battle/BalloonProp \
					  $(LOCAL_PATH)/../../Classes/GameBody/Battle/BufferProp \
					  $(LOCAL_PATH)/../../Classes/GameBody/Battle/ManualProp \
					  $(LOCAL_PATH)/../../Classes/GameBody/BuyProp \
					  $(LOCAL_PATH)/../../Classes/GameBody/RankingList \
					  $(LOCAL_PATH)/../../Classes/GameMain \
					  $(LOCAL_PATH)/../../Classes/LibBase \
					  $(LOCAL_PATH)/../../Classes/LibBox2d \
					  $(LOCAL_PATH)/../../Classes/LibFunction \
					  $(LOCAL_PATH)/../../Classes/LibInterface \
					  $(LOCAL_PATH)/../../Classes/LibIO \
					  $(LOCAL_PATH)/../../Classes/LibJni \
					  $(LOCAL_PATH)/../../Classes/LibMath \
					  $(LOCAL_PATH)/../../Classes/LibNewCocos2dx \
					  $(LOCAL_PATH)/../../Classes/LibShaders \
					  $(LOCAL_PATH)/../../Classes/LibSPX \
					  $(LOCAL_PATH)/../../Classes/LibStructure \
					  $(LOCAL_PATH)/../../Classes/LibTemplate \
					  $(LOCAL_PATH)/../../Classes/NetMessage \
					  $(LOCAL_PATH)/../../Classes/Network 


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static 


LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../libs/libprotobuffull) -lprotobuf


include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)

