#APP_STL := stlport_static
APP_STL := gnustl_static
APP_CPPFLAGS := -frtti -DCC_ENABLE_BOX2D_INTEGRATION=1 -DCOCOS2D_DEBUG=1
APP_PLATFORM := android-8
APP_CFLAGS += -Wno-error=format-security

APP_ABI := armeabi