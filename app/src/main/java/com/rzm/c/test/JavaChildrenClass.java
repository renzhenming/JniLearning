package com.rzm.c.test;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

import com.rzm.c.JavaInstance;

public class JavaChildrenClass extends JavaEngine {

    @Override
    public void log(Context context) {
        Log.d("JavaChildrenClass","子类log");
        Toast.makeText(context,"调用了子类方法",Toast.LENGTH_SHORT).show();
    }
}
