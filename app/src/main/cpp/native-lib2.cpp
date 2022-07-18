#include <jni.h>
#include <string>
#include <android/log.h>
#include <iostream>

using namespace std;

//定义TAG之后，我们可以在LogCat通过TAG过滤出NDK打印的日志
#define TAG "JNITEST"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

extern "C"
JNIEXPORT jstring JNICALL
Java_com_rzm_c_test_EngineUtils_changeJavaField(JNIEnv *env, jobject engineObj) {
    jclass engineClass = env->GetObjectClass(engineObj);
    jfieldID keyFieldId = env->GetFieldID(engineClass, "key", "Ljava/lang/String;");
    //调用 GetFieldID 时，我们仍然需要检查 是否有错误发生，因为 VM 可能没有足够的内存分配给字段 ID
    if (keyFieldId == NULL) {
        return NULL;
    }
    jstring keyObject = (jstring) env->GetObjectField(engineObj, keyFieldId);
    char *value = (char *) env->GetStringUTFChars(keyObject, NULL);

    if (value == NULL) {
        return NULL;
    }
    char *addStr = " is very good at living";
    char *newStr = strcat(value, addStr);
    jstring str = env->NewStringUTF(newStr);
    env->SetObjectField(engineObj, keyFieldId, str);
    env->ReleaseStringUTFChars(keyObject, value);
    return str;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_test_EngineUtils_changeJavaField2(JNIEnv *env, jobject thiz, jobject instance) {
    jclass instanceClass = env->GetObjectClass(instance);
    jfieldID paramsFiledId = env->GetFieldID(instanceClass, "price", "I");
    if (paramsFiledId == NULL) {
        return;
    }
    jint priceInt = env->GetIntField(instance, paramsFiledId);
    int result = 100 + priceInt;
    env->SetIntField(instance, paramsFiledId, result);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_rzm_c_test_EngineUtils_changeJavaStaticField(JNIEnv *env, jobject thiz, jobject instance) {
    jclass instaceClass = env->GetObjectClass(instance);
    jfieldID keyStaticFieldId = env->GetStaticFieldID(instaceClass, "keyStatic",
                                                      "Ljava/lang/String;");
    if (keyStaticFieldId == NULL) {
        return NULL;
    }
    jstring keyStaticStr = (jstring) env->GetStaticObjectField(instaceClass, keyStaticFieldId);
    char *valueStr = (char *) env->GetStringUTFChars(keyStaticStr, JNI_FALSE);
    if (valueStr == NULL) {
        return NULL;
    }
    char *append = "what is wrong with you, it's raining";
    char *newC = strcat(valueStr, append);
    jstring newStr = (jstring) env->NewStringUTF(newC);
    env->SetStaticObjectField(instaceClass, keyStaticFieldId, newStr);
    env->ReleaseStringUTFChars(keyStaticStr, valueStr);
    return newStr;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_test_EngineUtils_callJavaMethod(JNIEnv *env, jobject thiz, jobject instance,
                                               jobject context) {
    jclass instanceClass = env->GetObjectClass(instance);
    jmethodID voidMethodId = env->GetMethodID(instanceClass, "showToast",
                                              "(Landroid/content/Context;)V");
    env->CallVoidMethod(instance, voidMethodId, context);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_test_EngineUtils_callJavaStaticMethod(JNIEnv *env, jobject thiz, jobject instance,
                                                     jobject context) {
    jclass instanceClass = env->GetObjectClass(instance);
    jmethodID jmethodId = env->GetStaticMethodID(instanceClass, "showToast2",
                                                 "(Landroid/content/Context;)V");
    env->CallStaticVoidMethod(instanceClass, jmethodId, context);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_test_EngineUtils_callJavaConstructMethod(JNIEnv *env, jobject thiz,
                                                        jobject context) {
    jclass instanceClass = env->FindClass("com/rzm/c/test/JavaEngine");
    jmethodID initMethodId = env->GetMethodID(instanceClass, "<init>", "()V");
    if (initMethodId == NULL)
        return;
    jobject obj = env->NewObject(instanceClass, initMethodId);
    jmethodID logMehtodid = env->GetMethodID(instanceClass, "log", "(Landroid/content/Context;)V");
    if (logMehtodid == NULL)
        return;
    env->CallVoidMethod(obj, logMehtodid, context);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_test_EngineUtils_callJavaNonVirtualMethod(JNIEnv *env, jobject thiz,
                                                         jobject instance,
                                                         jobject preview_activity) {

    jclass fClass = env->FindClass("com/rzm/c/test/JavaEngine");
    jmethodID logMethodId = env->GetMethodID(fClass, "log", "(Landroid/content/Context;)V");
    env->CallNonvirtualVoidMethod(instance, fClass, logMethodId, preview_activity);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_test_EngineUtils_callJavaVirtualMethod(JNIEnv *env, jobject thiz, jobject instance,
                                                      jobject preview_activity) {

    jclass instanceClass = env->GetObjectClass(instance);
    jmethodID logMethodId = env->GetMethodID(instanceClass, "log", "(Landroid/content/Context;)V");
    env->CallVoidMethod(instance, logMethodId, preview_activity);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_test_EngineUtils_setJavaArray(JNIEnv *env, jobject thiz, jintArray arr) {


    jint *jarr = env->GetIntArrayElements(arr, JNI_FALSE);
    jarr[2] = 999999;
    env->ReleaseIntArrayElements(arr, jarr, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_test_EngineUtils_setString(JNIEnv *env, jobject thiz, jstring value) {
    char *cAtt = (char *) env->GetStringUTFChars(value, JNI_FALSE);
    cAtt[0] = 'z';
    //TODO ReleaseStringUTFChars不同于ReleaseIntArrayElements，ReleaseStringUTFChars只是回收，不会修改Java层字符串值
    env->ReleaseStringUTFChars(value, cAtt);
}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_rzm_c_test_EngineUtils_getArray(JNIEnv *env, jobject thiz, jint length) {

    jintArray jArray = env->NewIntArray(length);

    jint *arr = env->GetIntArrayElements(jArray, JNI_FALSE);
    for (int i = 0; i < length; i++) {
        *(arr + i) = 100 + i;
    }
    env->ReleaseIntArrayElements(jArray, arr, 0);
    return jArray;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_test_EngineUtils_catchException(JNIEnv *env, jobject thiz, jobject instance) {

    jclass instanceClass = env->GetObjectClass(instance);
    jfieldID keyFieldId = env->GetFieldID(instanceClass, "key2", "Ljava/lang/String;");
    jthrowable exe = env->ExceptionOccurred();
    if (exe != NULL) {
        env->ExceptionClear();
        keyFieldId = env->GetFieldID(instanceClass, "key", "Ljava/lang/String;");
    }

    jstring keyValue = (jstring) env->GetObjectField(instance, keyFieldId);
    char *Ckey = (char *) env->GetStringUTFChars(keyValue, NULL);

    if (strcmp(Ckey, "rzm") != 0) {
        jclass exeClass = env->FindClass("java/lang/IllegalStateException");
        env->ThrowNew(exeClass, "key is wrong, please check it");
    }
}












extern "C"
JNIEXPORT jboolean JNICALL
Java_com_rzm_c_test_EngineUtils_localReference(JNIEnv *env, jobject thiz) {
    for (int i = 0; i < 10; i++) {
//        jclass dateClass = env->FindClass("java/util/Date");
//        jmethodID dateMethodId = env->GetMethodID(dateClass,"<init>","()V");
//        jobject obj = env->NewObject(dateClass,dateMethodId);
//        jmethodID getTimeMethodId = env->GetMethodID(dateClass,"getTime","()J");
//        jlong time = env->CallLongMethod(obj,getTimeMethodId);
//        printf("aaaaaaaaa = %lld",time);
//        env->DeleteLocalRef(obj);


        jclass listClass = env->FindClass("java/util/ArrayList");
        jmethodID cMethodId = env->GetMethodID(listClass, "<init>", "()V");
        jobject listObj = env->NewObject(listClass, cMethodId);
        jmethodID eMethodId = env->GetMethodID(listClass, "isEmpty", "()Z");
        jboolean ieEmpty = env->CallBooleanMethod(listObj, eMethodId);

        env->DeleteLocalRef(listObj);
        return ieEmpty;
    }
    return false;
}

jstring globalStr = NULL;
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_rzm_c_test_EngineUtils_createGlobalReference(JNIEnv *env, jobject thiz) {

    jstring str = env->NewStringUTF("我是中国公民");
    globalStr = (jstring) env->NewGlobalRef(str);
    if (globalStr != NULL) {
        return true;
    }
    return false;
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_rzm_c_test_EngineUtils_deleteGlobalReference(JNIEnv *env, jobject thiz) {

    if (globalStr != NULL) {
        env->DeleteGlobalRef(globalStr);
        return true;
    }
    return false;

}