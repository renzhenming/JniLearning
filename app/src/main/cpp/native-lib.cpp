#include <jni.h>
#include <string>
#include <iostream>
#include <pthread.h>

// 日志输出
#include <android/log.h>

#define TAG "JNISTUDY"
// __VA_ARGS__ 代表 ...的可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__);

using namespace std;

void showToast(JNIEnv *env, jobject jobj, jobject context) {
    cout << "showToast" << endl;
    jclass toastClass = env->FindClass("android/widget/Toast");
    jmethodID makeTextMethodId = env->GetStaticMethodID(toastClass, "makeText",
                                                        "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");

    jstring str = env->NewStringUTF("我是native弹出来的toast");
    jobject toastObj = env->CallStaticObjectMethod(toastClass, makeTextMethodId, context, str, 0);
    jmethodID showMethodId = env->GetMethodID(toastClass, "show", "()V");
    env->CallVoidMethod(toastObj, showMethodId);
    env->DeleteLocalRef(toastObj);
}

void jLog(JNIEnv *env, jobject jobj, jstring str) {
    cout << "log:" << str << endl;
    jclass logClass = env->FindClass("android/util/Log");
    jmethodID dMethodId = env->GetStaticMethodID(logClass, "d",
                                                 "(Ljava/lang/String;Ljava/lang/String;)I");

    jstring Tag = env->NewStringUTF("Native");
    env->CallStaticIntMethod(logClass, dMethodId, Tag, str);
}

/**
 * 方法必须在这里上边定义，不然会找不到
 */
static const JNINativeMethod method[] = {
        {"showToast", "(Landroid/content/Context;)V", (void *) (showToast)},
        {"log",       "(Ljava/lang/String;)V",        (void *) (jLog)}
};

JavaVM *javaVm = nullptr;

// VM将在加载Library时调用JNI_OnLoad。它需要返回native需要的JNI版本。
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    cout << "JNI_OnLoad" << endl;
    ::javaVm = vm;
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        cout << "Get env " << std::hex << JNI_VERSION_1_6 << " failed" << endl;
        return JNI_VERSION_1_6;
    }

    jclass dynamicClass = env->FindClass("com/rzm/c/utils/JniDynamicUtils");
    if (dynamicClass == NULL) {
        cout << "find class JniDynamicUtils failed" << endl;
        return JNI_VERSION_1_6;
    }
    int ret = env->RegisterNatives(dynamicClass, method, sizeof(method) / sizeof(method[0]));
    if (ret != 0) {
        cout << "register natives failed, error: " << ret << endl;
    }
    return JNI_VERSION_1_6;
}

/**
 * // 1. JavaVM全局，绑定当前进程， 只有一个地址
// 2. JNIEnv线程绑定， 绑定主线程，绑定子线程
// 3. jobject 谁调用JNI函数，谁的实例会给jobject
 * @param vm
 * @param reserved
 */
// 当加载Library的类被垃圾回收时，VM会调用JNI_OnUnload。
void JNI_OnUnload(JavaVM *vm, void *reserved) {
    cout << "JNI_OnUnload" << endl;
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        cout << "JNI_OnUnload Get env " << std::hex << JNI_VERSION_1_6 << " failed" << endl;
        return;
    }
    jclass dynamicClass = env->FindClass("com/rzm/c/utils/JniDynamicUtils");
    if (dynamicClass == NULL) {
        cout << "JNI_OnUnload find class JniDynamicUtils failed" << endl;
        return;
    }
    env->UnregisterNatives(dynamicClass);
}

/**
 * 访问Java对象的非静态变量
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_rzm_c_utils_JniUtils_changeJavaField(JNIEnv *env, jobject instance) {

    //修改field值首先要获取到这个field，获取field需要先获取到fieldID，获取fieldId需要获取到对象的class
    //1.获取到所需要获取field对象的jclass
    jclass objClass = env->GetObjectClass(instance);

    //2.获取到fieldId
    //“Ljava/lang/String”来代表一个 JVM 中的字段类 型。这个字符串被称为 JNI field descriptor(字段描述符)。
    // 字符串的内容由字段被声明的类型决定。例如，使用“I”来表示一个 int 类型的字段，“F” 来表示一个 float 类型的字段，
    // “D”来表示一个 double 类型的字段，“Z”来表示一个 boolean 类型的字段等等。
    //像 java.lang.String 这样的引用类型的描述符都是以 L 开头，后面跟着一个 JNI 类描述符，以 分号结尾。
    // 一个 JAVA 类的全名中的包名分隔符“.”被转化成“/”。因此，对于一个字段类 型的字段来说，它的描述符是
    // “Ljava/lang/String”。数组的描述符中包含“]”字符，后面会跟着数组类型的描述符，如“[I”是 int[]类型的字段
    // 的描述符。12.3.3 详细介绍了各种类型的字段描述以及他们代表的 JAVA 类型。 你可以使用 javap 工具来生成字段描述符。
    jfieldID fieldId = env->GetFieldID(objClass, "key", "Ljava/lang/String;");

    //调用 GetFieldID 时，我们仍然需要检查 是否有错误发生，因为 VM 可能没有足够的内存分配给字段 ID
    if (fieldId == NULL) {
        return NULL;
    }

    //3.获取到field
    jstring field = (jstring) env->GetObjectField(instance, fieldId);

    //4.转化成char
    //通过调用 JNI 函数 GetStringUTFChars 来读取字符串的内容。 GetStringUTFChars 可以把一个 jstring 指针(指向
    // JVM 内部的 Unicode 字符序列)转化成一 个 UTF-8 格式的 C 字符串。不要忘记检查 GetStringUTFChars。
    // 因为 JVM 需要为新诞生的 UTF-8 字符串分配 内存，这个操作有可能因为内存太少而失败。失败时，GetStringUTFChars
    // 会返 回 NULL，并抛出一个 OutOfMemoryError 异常
    char *ctr = (char *) env->GetStringUTFChars(field, NULL);

    if (ctr == NULL) {
        return NULL;
    }

    //5.在原字符串后拼接" add something"
    //length = length+ sizeof(ctr);
    char text[sizeof(" add something") + 1] = " add something";
    strcat(ctr, text);

    //6.char转为jstring
    //如果一个 VM 不能为构造 java.lang.String 分配足够的内存，NewStringUTF 会 抛出一个 OutOfMemoryError 异常，
    // 并返回一个 NULL。在这个例子中，我们不必 检查它的返回值，因为本地方法会立即返回。如果 NewStringUTF 失败，
    // OutOfMemoryError 这个异常会被在 Prompt.main(本地方法的调用者)中抛出。 如果 NeweStringUTF 成功，
    // 它会返回一个 JNI 引用，这个引用指向新创建的 java.lang.String 对象。这个对象被 Prompt.getLine 返回然后被
    // 赋值给 Prompt.main 中的本地 input。
    jstring newString = env->NewStringUTF(ctr);

    //7.设置给Java对象
    env->SetObjectField(instance, fieldId, newString);

//    env->DeleteLocalRef(newString);

    env->ReleaseStringUTFChars(field, ctr);

    return newString;
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_rzm_c_utils_JniUtils_changeJavaField2(JNIEnv *env, jobject instance, jobject object) {

    jclass objClass = env->GetObjectClass(object);
    jfieldID fieldId = env->GetFieldID(objClass, "key", "Ljava/lang/String;");
    if (fieldId == NULL) {
        return NULL;
    }
    jstring field = (jstring) env->GetObjectField(object, fieldId);
    char *ctr = (char *) env->GetStringUTFChars(field, NULL);
    if (ctr == NULL) {
        return NULL;
    }
    char text[sizeof(" i am toy") + 1] = " i am toy";
    strcat(ctr, text);
    jstring newString = env->NewStringUTF(ctr);
    env->SetObjectField(object, fieldId, newString);
    env->ReleaseStringUTFChars(field, ctr);
    return newString;

}

/**
 * c++修改Java对象中的静态属性值
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_rzm_c_utils_JniUtils_changeJavaStaticField(JNIEnv *env, jobject instance, jobject object) {

    jclass objClass = env->GetObjectClass(object);
    jfieldID objFieldId = env->GetStaticFieldID(objClass, "keyStatic", "Ljava/lang/String;");
    if (objFieldId == NULL) {
        return NULL;
    }
    jstring objStr = (jstring) env->GetStaticObjectField(objClass, objFieldId);
    char *objChar = (char *) env->GetStringUTFChars(objStr, JNI_FALSE);
    if (objChar == NULL) {
        return NULL;
    }
    char *temp = " what day is it today?";
    jstring objNew;
    if (strcmp(objChar, temp) == 0) {
        objNew = env->NewStringUTF("today is friday");
    } else {
        objNew = env->NewStringUTF("wrong");
    }
    env->SetStaticObjectField(objClass, objFieldId, objNew);
    env->ReleaseStringUTFChars(objStr, objChar);
    return objNew;
}
/**
 * c++调用Java中的成员方法
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_utils_JniUtils_callJavaMethod(JNIEnv *env, jobject instance, jobject object,
                                             jobject context) {

    jclass jclass = env->GetObjectClass(object);
    jmethodID jmethodID = env->GetMethodID(jclass, "showToast", "(Landroid/content/Context;)V");
    env->CallVoidMethod(object, jmethodID, context);

    //CallxxxMethod xxx表示方法返回值类型
//    env->CallIntMethod()
//    env->CallFloatMethod()
//    env->CallLongMethod()
//    env->CallObjectMethod()
}

/**
 * C++调用Java静态成员方法
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_utils_JniUtils_callJavaStaticMethod(JNIEnv *env, jobject instance, jobject object,
                                                   jobject context) {
    jclass objClass = env->GetObjectClass(object);
    jmethodID methodId = env->GetStaticMethodID(objClass, "showToast2",
                                                "(Landroid/content/Context;)V");
    env->CallStaticVoidMethod(objClass, methodId, context);
}
/**
 * C++调用Java构造方法
 * @param view
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_rzm_c_utils_JniUtils_callJavaConstructMethod(JNIEnv *env, jobject instance,
                                                      jobject object) {

    //通过调用Java中的Date获取当前时间,//根据包名得到类，类似反射
    jclass dateClass = env->FindClass("java/util/Date");
    if (dateClass == NULL)
        return 0;
    //(获取构造方法，方法名传"<init>")
    jmethodID methodId = env->GetMethodID(dateClass, "<init>", "()V");
    if (methodId == NULL)
        return 0;
    ////实例化一个对象，类似反射
    jobject dateobj = env->NewObject(dateClass, methodId);
    jmethodID getTimeMethodId = env->GetMethodID(dateClass, "getTime", "()J");
    if (getTimeMethodId == NULL)
        return 0;
    jlong timeMills = env->CallLongMethod(dateobj, getTimeMethodId);
    printf("时间：%lld", timeMills);
    env->DeleteLocalRef(dateobj);
    return timeMills;
}

/**
 * C++调用被子类覆盖的父类方法
 * FindClass( ) 和 getObjectClass( )的区别？
 * FindClass( ) 就是通过包名类名去找，这个相当于绝对路径
 * getObjectClass( ) 是通过一个obj的类型去找，这个地方需要注意的是，他是通过对象类型去找，不是通过引用类型去找
 * 比如一开始在java 里面写了
 * Father p=new Child();
 * 那么在C＋＋里面获得这个obj之后，如果用getObjectClass( ) 获得的就是 Child 的 Class ， 不是 Father 的 Class
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_utils_JniUtils_callJavaNonVirtualMethod(JNIEnv *env, jobject instance, jobject obj,
                                                       jobject context) {

    env->GetObjectClass(obj);
    jclass fClass = env->FindClass("com/rzm/c/JavaInstance");
    //这里通过传入父类的class去寻找log方法，如果传入子类的class，那么是调用不到父类的log方法的
    //比如我们通过env->GetObjectClass(obj)获取class后传入，虽然这个obj在Java中是父类引用指向子类
    //对象，但是其实获取到的class是子类的class
    jmethodID methodId = env->GetMethodID(fClass, "log", "(Landroid/content/Context;)V");
    env->CallNonvirtualVoidMethod(obj, fClass, methodId, context);


}
/**
 * C++调用子类重写父类后的方法
 * @param view
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_utils_JniUtils_callJavaVirtualMethod(JNIEnv *env, jobject instance, jobject object,
                                                    jobject context) {

    jclass fClass = env->FindClass("com/rzm/c/JavaInstance");
    jmethodID methodId = env->GetMethodID(fClass, "log", "(Landroid/content/Context;)V");
    env->CallVoidMethod(object, methodId, context);

}

/**
 * C++操作Java中的数组
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_utils_JniUtils_setJavaArray(JNIEnv *env, jobject instance, jintArray arr_) {
    jint *arr = env->GetIntArrayElements(arr_, NULL);
    arr[0] = 999;
    //将排序结果同步到Java中的数组
    //最后一个参数 mode
    //0  表示Java数组进行更新，并且释放c/c++数组
    //JNI_ABORT  表示Java数组不更新，释放c/c++数组
    //JNI_COMMIT 表示Java数组进行更新，但不释放c/c++数组
    //TODO 最后一个参数是对Java层数组修改的关键
    env->ReleaseIntArrayElements(arr_, arr, 0);
}

/**
 * C++操作Java中的字符串
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_utils_JniUtils_setString(JNIEnv *env, jobject instance, jstring value_) {
    char *value = (char *) env->GetStringUTFChars(value_, 0);

    //将第一个字母变成a
    value[0] = 'a';

    //ReleaseStringUTFChars 告诉 JVM 这个 UTF-8 字符串不会被使用了，因为这个 UTF-8 字符串占用的内存会被回收。
    //TODO ReleaseStringUTFChars不同于ReleaseIntArrayElements，ReleaseStringUTFChars只是回收，不会修改Java层字符串值
    env->ReleaseStringUTFChars(value_, value);
}

/**
 * C++层返回一个数组到Java层
 */
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_rzm_c_utils_JniUtils_getArray(JNIEnv *env, jobject instance) {

    jintArray array = env->NewIntArray(10);
    jint *elem = env->GetIntArrayElements(array, JNI_FALSE);
    for (int i = 0; i < 10; i++) {
        elem[i] = i * 100;
    }
    env->ReleaseIntArrayElements(array, elem, JNI_FALSE);
    return array;
}

/**
 * C++层抛出异常到Java层
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_utils_JniUtils_catchException(JNIEnv *env, jobject instance, jobject obj) {

    jclass objClass = env->GetObjectClass(obj);
    jfieldID fieldId = env->GetFieldID(objClass, "key2", "Ljava/lang/String;");
    //检测是否发生Java异常
    jthrowable exception = env->ExceptionOccurred();
    if (exception != NULL) {
        //让Java代码可以继续运行
        //清空异常信息
        env->ExceptionClear();
        //补救措施
        fieldId = env->GetFieldID(objClass, "key", "Ljava/lang/String;");
    }
    //获取属性值
    jstring jstr = (jstring) env->GetObjectField(obj, fieldId);
    char *str = (char *) env->GetStringUTFChars(jstr, NULL);
    if (strcmp(str, "hello") != 0) {
        //抛出异常，让Java端处理
        jclass newExc = env->FindClass("java/lang/IllegalArgumentException");
        env->ThrowNew(newExc, "wrong");
    }
}

/**
 * C++处理java层抛出的异常
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_utils_JniUtils_catchException2(JNIEnv *env, jobject thiz) {
    LOGI("native层:>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>1");
    jclass javaClass = env->GetObjectClass(thiz);
    jmethodID javaMethodId = env->GetMethodID(javaClass, "javaThrowException", "()V");
    env->CallVoidMethod(thiz, javaMethodId);

    //CallVoidMethod发生异常后并不会马上崩溃，而是预留了时间，给我们处理
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
    LOGI("native层:>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>2");
}

/**
 * 局部引用
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_utils_JniUtils_localReference(JNIEnv *env, jobject instance) {

    for (int i = 0; i < 10; i++) {
        jclass dateClass = env->FindClass("java/util/Date");
        jmethodID dateMethodId = env->GetMethodID(dateClass, "<init>", "()V");
        jobject obj = env->NewObject(dateClass, dateMethodId);
        jmethodID getTimeMethodId = env->GetMethodID(dateClass, "getTime", "()J");
        jlong time = env->CallLongMethod(obj, getTimeMethodId);
        printf("aaaaaaaaa = %lld", time);
        env->DeleteLocalRef(obj);
    }

}

/**
 * C++创建全局引用
 */

jstring jGlobalStrenv;
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_rzm_c_utils_JniUtils_createGlobalReference(JNIEnv *env, jobject instance) {
    jstring jstr = env->NewStringUTF("jni is a bitch");
    jGlobalStrenv = (jstring) env->NewGlobalRef(jstr);
    if (jGlobalStrenv != NULL) {
        return true;
    }
    return false;
}

/**
 * 删除全局引用
 */
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_rzm_c_utils_JniUtils_deleteGlobalReference(JNIEnv *env, jobject instance) {
    env->DeleteGlobalRef(jGlobalStrenv);
    return true;
}


class MyContext {
public:
    JNIEnv *env = nullptr;// 不能跨线程 ，会奔溃
    jobject obj = nullptr;// 不能跨线程,除非提升为全局引用
};

void *myThreadAction(void *pVoid) {
    LOGE("myThreadAction run")
    MyContext *context = static_cast<MyContext *>(pVoid);
    //TODO 错误的用法，env是绑定线程的，主线程的env不能传递到子线程使用
    //jclass mainActivityClass = context->env->FindClass("com/rzm/c/ThreadActivity");

    //正确的做法是：
    //jint AttachCurrentThread(JNIEnv** p_env, void* thr_args)
    JNIEnv *env = nullptr;
    jint result = ::javaVm->AttachCurrentThread(&env, nullptr);
    if (result != JNI_OK) {
        return 0;
    }
    jclass threadActivityClass = env->GetObjectClass(context->obj);
    jmethodID updateActivityUIMethodId = env->GetMethodID(threadActivityClass, "updateActivityUI",
                                                          "()V");
    env->CallVoidMethod(context->obj, updateActivityUIMethodId);

    ::javaVm->DetachCurrentThread();
    LOGE("myThreadAction C++ 异步线程OK")
    //TODO 如果这里不反回nullptr，回报下面的错误并崩溃
    //    --------- beginning of crash
    //2022-08-26 11:05:40.810 9879-9879/? A/DEBUG:
    // #00 pc 0000000000045814  /data/app/~~wT_U_QyX8VYKR8i0H7A2Cg==/com.rzm.c-o0vYH1mFj3hnFGwUAesfAQ
    // ==/lib/arm64/libnative-lib.so (myThreadAction(void*)+44)
    // (BuildId: bb8d26da41f52367c6d718a79a77b90a8fbee1dc)
    return nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_ThreadActivity_nativeThread(JNIEnv *env, jobject thiz) {

    MyContext *myContext = new MyContext;
    myContext->env = env;
    //myContext->instance = job; // 默认是局部引用，会奔溃
    myContext->obj = env->NewGlobalRef(thiz);// 提升全局引用

    pthread_t pthread;
    //int pthread_create(pthread_t* __pthread_ptr, pthread_attr_t const* __attr, void* (*__start_routine)(void*), void*);
    pthread_create(&pthread, nullptr, myThreadAction, myContext);
    pthread_join(pthread, nullptr);
    env->DeleteGlobalRef(myContext->obj);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_rzm_c_ThreadActivity_closeThread(JNIEnv *env, jobject thiz) {
//    env->DeleteGlobalRef()
}