package com.rzm.c.utils;

import android.content.Context;

public class JniDynamicUtils {
    static {
        System.loadLibrary("native-lib");
    }

    public native void showToast(Context context);

    public native void log(String log);
}
