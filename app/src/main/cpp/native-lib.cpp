#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_rzm_c_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
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
    jfieldID fieldId = env->GetFieldID(objClass,"key","Ljava/lang/String;");

    //调用 GetFieldID 时，我们仍然需要检查 是否有错误发生，因为 VM 可能没有足够的内存分配给字段 ID
    if (fieldId == NULL){
        return NULL;
    }

    //3.获取到field
    jstring field = (jstring) env->GetObjectField(instance, fieldId);

    //4.转化成char
    //通过调用 JNI 函数 GetStringUTFChars 来读取字符串的内容。 GetStringUTFChars 可以把一个 jstring 指针(指向
    // JVM 内部的 Unicode 字符序列)转化成一 个 UTF-8 格式的 C 字符串。不要忘记检查 GetStringUTFChars。
    // 因为 JVM 需要为新诞生的 UTF-8 字符串分配 内存，这个操作有可能因为内存太少而失败。失败时，GetStringUTFChars
    // 会返 回 NULL，并抛出一个 OutOfMemoryError 异常
    char* ctr = (char *) env->GetStringUTFChars(field, NULL);

    if (ctr == NULL){
        return NULL;
    }

    //5.在原字符串后拼接" add something"
    //length = length+ sizeof(ctr);
    char text[sizeof(" add something")+1] = " add something";
    strcat(ctr,text);

    //6.char转为jstring
    //如果一个 VM 不能为构造 java.lang.String 分配足够的内存，NewStringUTF 会 抛出一个 OutOfMemoryError 异常，
    // 并返回一个 NULL。在这个例子中，我们不必 检查它的返回值，因为本地方法会立即返回。如果 NewStringUTF 失败，
    // OutOfMemoryError 这个异常会被在 Prompt.main(本地方法的调用者)中抛出。 如果 NeweStringUTF 成功，
    // 它会返回一个 JNI 引用，这个引用指向新创建的 java.lang.String 对象。这个对象被 Prompt.getLine 返回然后被
    // 赋值给 Prompt.main 中的本地 input。
    jstring newString = env->NewStringUTF(ctr);

    //7.设置给Java对象
    env->SetObjectField(instance,fieldId,newString);

//    env->DeleteLocalRef(newString);

    env->ReleaseStringUTFChars(field,ctr);

    return newString;
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_rzm_c_utils_JniUtils_changeJavaField2(JNIEnv *env, jobject instance, jobject object) {

    jclass objClass = env->GetObjectClass(object);
    jfieldID fieldId = env->GetFieldID(objClass,"key","Ljava/lang/String;");
    if (fieldId == NULL){
        return NULL;
    }
    jstring field = (jstring) env->GetObjectField(object, fieldId);
    char* ctr = (char *) env->GetStringUTFChars(field, NULL);
    if (ctr == NULL){
        return NULL;
    }
    char text[sizeof(" i am toy")+1] = " i am toy";
    strcat(ctr,text);
    jstring newString = env->NewStringUTF(ctr);
    env->SetObjectField(object,fieldId,newString);
    env->ReleaseStringUTFChars(field,ctr);
    return newString;

}

/**
 * c++修改Java对象中的静态属性值
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_rzm_c_utils_JniUtils_changeJavaStaticField(JNIEnv *env, jobject instance, jobject object) {

    jclass objClass = env->GetObjectClass(object);
    jfieldID objFieldId = env->GetStaticFieldID(objClass,"keyStatic","Ljava/lang/String;");
    if (objFieldId == NULL){
        return NULL;
    }
    jstring objStr = (jstring) env->GetStaticObjectField(objClass, objFieldId);
    char* objChar = (char *) env->GetStringUTFChars(objStr, JNI_FALSE);
    if(objChar == NULL){
        return NULL;
    }
    char* temp = "what day is it today?";
    jstring objNew;
    if (strcmp(objChar,temp) == 0){
        objNew = env->NewStringUTF("today is friday");
    }else{
        objNew = env->NewStringUTF("wrong");
    }
    env->SetStaticObjectField(objClass,objFieldId,objNew);
    env->ReleaseStringUTFChars(objStr,objChar);
    return objNew;
}