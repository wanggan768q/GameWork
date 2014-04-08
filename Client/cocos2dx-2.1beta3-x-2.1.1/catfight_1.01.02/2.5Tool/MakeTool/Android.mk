LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game


################################################################ 
#		 Ambition  [FileCount:15]		Time:	2012-10-24 11:30:59
################################################################ 


LOCAL_SRC_FILES := main.cpp \
../../../Classes/HSDataCache.cpp \
../../../Classes/HSFilter.cpp \
../../../Classes/HSProtocol.cpp \
../../../Classes/HSRequest.cpp \
../../../Classes/HSResponse.cpp \
../../../Classes/HSSocket.cpp \
../../../Classes/HSSocketPool.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../cocos2dx \
					  $(LOCAL_PATH)/../../../../cocos2dx/platform \
					  $(LOCAL_PATH)/../../../../cocos2dx/include \
					  $(LOCAL_PATH)/../../../../CocosDenshion/include \
					  $(LOCAL_PATH)/../../../../cocos2dx/lua_support \
					  $(LOCAL_PATH)/../../../Classes

LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/armeabi) \
                -lcocos2d -llog -lcocosdenshion \
                -L$(call host-path, $(LOCAL_PATH)/../../../../cocos2dx/platform/third_party/android/libraries/armeabi-v7a) -liconv \
                -L$(call host-path, $(LOCAL_PATH)/../../libs/libprotobuffull) -lprotobuf \
                -lGLESv2 \
                -lGLESv1_CM

-include $(BUILD_SHARED_LIBRARY)