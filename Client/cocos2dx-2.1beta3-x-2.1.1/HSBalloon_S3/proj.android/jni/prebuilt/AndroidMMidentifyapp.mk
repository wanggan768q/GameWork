LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := mmidentifyapp
LOCAL_SRC_FILES := libidentifyapp.so
include $(PREBUILT_SHARED_LIBRARY)