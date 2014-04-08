LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := mmcasdkjni
LOCAL_SRC_FILES := libcasdkjni.so
include $(PREBUILT_SHARED_LIBRARY)