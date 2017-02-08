LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE	:= liblive2d
LOCAL_SRC_FILES	:= ../jniLibs/$(TARGET_ARCH_ABI)/liblive2d.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_CPPFLAGS := -DL2D_TARGET_ANDROID_ES2

LOCAL_MODULE    := Live2DSimple
LOCAL_SRC_FILES := Live2DSimple.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../jni
					
LOCAL_LDLIBS := -llog			# ログ機能を使用するので Android-specific Log Support を追加します。
LOCAL_LDLIBS += -lGLESv2		# OpenGL ES 2.0 を使用するので OpenGL ES 2.0 ライブラリを追加します。

LOCAL_WHOLE_STATIC_LIBRARIES += liblive2d

include $(BUILD_SHARED_LIBRARY)
