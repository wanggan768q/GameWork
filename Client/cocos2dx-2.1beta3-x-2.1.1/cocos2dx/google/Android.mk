LOCAL_PATH := $(call my-dir)


#protobuf_2.5

################## Build ProtoBuf ################
include $(CLEAR_VARS)


LOCAL_ARM_MODE := arm
LOCAL_CPPFLAGS += -frtti
LOCAL_MODULE := protobuf_static

LOCAL_MODULE_FILENAME := libprotobuf_LITE_RUNTIME

LOCAL_CPP_EXTENSION := .cc

LOCAL_SRC_FILES := \
protobuf/io/coded_stream.cc                \
protobuf/stubs/common.cc                   \
protobuf/extension_set.cc                  \
protobuf/generated_message_util.cc         \
protobuf/stubs/once.cc                     \
protobuf/repeated_field.cc                 \
protobuf/wire_format_lite.cc               \
protobuf/io/zero_copy_stream_impl_lite.cc  \
protobuf/io/zero_copy_stream.cc						 \
protobuf/message_lite.cc


LOCAL_C_INCLUDES += . \
$(LOCAL_PATH)/../ \




::LOCAL_LDLIBS := -llog -lgcc -lpthreads \
::      E:/InstallationApplication/Cygwin/android-ndk-r8b-windows/android-ndk-r8b/sources/cxx-stl/gnu-libstdc++/4.6/gnu-libstdc++/libs/armeabi/libstdc++.a \


::ifndef NDK_ROOT
::include external/stlport/libstlport.mk
::endif
::include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
