package com.rzm.c;

import android.content.Context;
import android.widget.Toast;

/**
 * Created by renzm on 2019/11/22.
 */

public class JavaInstance {

    public String key = "who are you?";

    public static String keyStatic = "what day is it today?";

    public void showToast(Context context){
        Toast.makeText(context,"调用了Java方法",Toast.LENGTH_SHORT).show();
    }

    public static void showToast2(Context context){
        Toast.makeText(context,"调用了Java静态方法",Toast.LENGTH_SHORT).show();
    }
}
