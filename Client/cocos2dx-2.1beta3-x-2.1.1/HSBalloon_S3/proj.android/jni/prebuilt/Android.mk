LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := bspatch
LOCAL_SRC_FILES := libbspatch.so
include $(PREBUILT_SHARED_LIBRARY)