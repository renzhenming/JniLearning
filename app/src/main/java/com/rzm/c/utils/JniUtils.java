package com.rzm.c.utils;

import android.content.Context;

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
}
