package com.rzm.c.test;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

public class JavaEngine {

    public String key = "春江潮水连海平，海上明月共潮生";
    public int price = 2000;

    public static String keyStatic = "today is a good day";

    public JavaEngine() {
    }

    public JavaEngine(int price, String key) {
        this.price = price;
        this.key = key;
    }

    public void showToast(Context context) {
        Toast.makeText(context, "调用了Java方法", Toast.LENGTH_SHORT).show();
    }

    public static void showToast2(Context context) {
        Toast.makeText(context, "调用了Java静态方法", Toast.LENGTH_SHORT).show();
    }

    public void log(Context context) {
        Log.d("JavaInstance", "父类log");
        Toast.makeText(context, "调用了父类方法", Toast.LENGTH_SHORT).show();
    }
}
