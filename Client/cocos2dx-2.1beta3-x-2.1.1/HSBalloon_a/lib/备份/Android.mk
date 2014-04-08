LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game_shared
LOCAL_MODULE_FILENAME := libgame


################################################################ 
#		 Ambition  [FileCount:16]		Time:	2013-04-24 13:32:19
################################################################ 


LOCAL_SRC_FILES := Main/main.cpp \
../../Classes/StratagemConfig.pb.cpp \
../../Classes/HSBalloonFactory.cpp \
../../Classes/HSBalloonProps.cpp \
../../Classes/HSBalloonSprite.cpp \
../../Classes/HSBattleScene.cpp \
../../Classes/HSStratagem.cpp \
../../Classes/HSStratagemSprite.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes 


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static 


LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/libprotobuffull) -lprotobuf


include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)

