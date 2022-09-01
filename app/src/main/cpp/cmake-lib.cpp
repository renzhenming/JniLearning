#include <jni.h>
#include <string>
#include <iostream>

// 日志输出
#include <android/log.h>

// 采用C的编译方式
extern "C" {
#include "libget/getutil.h"
}

#define TAG "JNISTUDY"
// __VA_ARGS__ 代表 ...的可变参数
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__);

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_MultiCMakeListsActivity_invokeStaticNative(JNIEnv *env, jobject thiz) {
    const char *char_str = get1_action();
    LOGE("char_str = %s", char_str)
    const char *char_str2 = get2_action();
    LOGE("char_str2 = %s", char_str)
    const char *char_str3 = get3_action();
    LOGE("char_str3 = %s", char_str)
}