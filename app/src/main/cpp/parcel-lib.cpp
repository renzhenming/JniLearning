#include <jni.h>
#include <string>
#include <iostream>
#include <pthread.h>

// 日志输出
#include <android/log.h>
#include "MyParcel.h"

#define TAG "JNISTUDY"
// __VA_ARGS__ 代表 ...的可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__);

using namespace std;

extern "C"
JNIEXPORT jlong JNICALL
Java_com_rzm_c_parcel_MyParcel_nativeCreate(JNIEnv *env, jobject thiz) {
    MyParcel *myParcel = new MyParcel;
    return reinterpret_cast<jlong>(myParcel);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_rzm_c_parcel_MyParcel_nativeReadInt(JNIEnv *env, jobject thiz, jlong m_native_ptr) {
    MyParcel *myParcel = reinterpret_cast<MyParcel *>(m_native_ptr);
    return myParcel->readInt();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_parcel_MyParcel_nativeSetDataPosition(JNIEnv *env, jobject thiz, jlong m_native_ptr,
                                                     jint position) {
    MyParcel *myParcel = reinterpret_cast<MyParcel *>(m_native_ptr);
    myParcel->setDataPosition(position);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_parcel_MyParcel_nativeWriteInt(JNIEnv *env, jobject thiz, jlong m_native_ptr,
                                              jint value) {
    MyParcel *myParcel = reinterpret_cast<MyParcel *>(m_native_ptr);
    myParcel->writeInt(value);
}