#include <jni.h>
#include <string>

// 日志输出
#include <android/log.h>

// 采用C的编译方式
extern "C" {
#include "ffmpeg/include/libavutil/avutil.h"
}

#define TAG "JNISTUDY"
// __VA_ARGS__ 代表 ...的可变参数
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__);

extern "C"
JNIEXPORT jstring JNICALL
Java_com_rzm_c_FFmpegActivity_getFFmpegVersion(JNIEnv *env, jobject thiz) {
    std::string version_str = "当前ffmpeg版本是：";
    version_str.append(av_version_info());
    return env->NewStringUTF(version_str.c_str());
}