package com.rzm.c.utils;

import android.content.Context;
import android.util.Log;

import com.rzm.c.JavaInstance;
import com.rzm.c.MainActivity;

/**
 * Created by renzm on 2019/11/22.
 */

public class JniUtils {

    public String key = "renzhenming";


    static{
        System.loadLibrary("native-lib");
    }


    public void javaThrowException() {
        Log.d("JniUtils", "javaThrowException before");
        if (true) {
            throw new NullPointerException("空指针异常。。。。。");
        }
        Log.d("JniUtils", "javaThrowException after");
    }

    /**
     * 访问Java对象的非静态变量
     */
    public native String changeJavaField();
    public native String changeJavaField2(Object object);

    /**
     * c++修改Java对象中的静态属性值
     * @param object
     * @return
     */
    public native String changeJavaStaticField(Object object);

    /**
     * c++调用Java中的成员方法
     * @param object
     * @param context
     */
    public native void callJavaMethod(Object object, Context context);

    /**
     * C++调用Java静态成员方法
     * @param object
     */
    public native void callJavaStaticMethod(Object object,Object object2);

    /**
     * C++调用Java构造方法
     * @param object
     */
    public native long callJavaConstructMethod(Object object);

    /**
     * C++调用被子类覆盖的父类方法
     */
    public native void callJavaNonVirtualMethod(Object object,Context context);

    /**
     * C++调用被子类覆盖的父类方法
     */
    public native void callJavaVirtualMethod(Object object, Context context);

    /**
     * C++操作Java中的数组
     */
    public native void setJavaArray(int[] arr);

    /**
     * C++操作Java中的字符串
     * @param value
     */
    public native void setString(String value) ;

    /**
     * C++层返回一个数组到Java层
     * @return
     */
    public native int[] getArray();

    /**
     * C++层抛出异常到Java层
     */
    public native void catchException(Object object) ;

    /**
     * C++调用java方法时，java内部发生异常
     */
    public native void catchException2();

    /**
     * C++处理自己的异常
     */
    public native void catchException3();

    /**
     * 局部引用
     */
    public native void localReference() ;

    /**
     * C++创建全局引用
     */
    public native boolean createGlobalReference();

    /**
     * C++删除全局引用
     * @return
     */
    public native boolean deleteGlobalReference();
}
