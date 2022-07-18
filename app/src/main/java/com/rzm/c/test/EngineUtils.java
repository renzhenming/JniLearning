package com.rzm.c.test;

import android.content.Context;

public class EngineUtils {

    static {
        System.loadLibrary("native-lib2");
    }

    public String key = "renzhenming";

    public native String changeJavaField();

    public native void changeJavaField2(JavaEngine instance);

    public native String changeJavaStaticField(JavaEngine instance);

    public native void callJavaMethod(JavaEngine instance, Context previewActivity);

    public native void callJavaStaticMethod(JavaEngine instance, Context context);

    public native void callJavaConstructMethod(Context previewActivity);

    public native void callJavaNonVirtualMethod(JavaEngine instance, Context previewActivity);

    public native void callJavaVirtualMethod(JavaEngine instance, Context previewActivity);

    public native void setJavaArray(int[] arr);

    public native void setString(String value);

    public native int[] getArray(int i);

    public native void catchException(JavaEngine instance);

    public native boolean localReference();

    public native boolean createGlobalReference();

    public native boolean deleteGlobalReference();
}
