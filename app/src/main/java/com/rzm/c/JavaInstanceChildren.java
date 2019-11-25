package com.rzm.c;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

/**
 * Created by renzm on 2019/11/25.
 */

public class JavaInstanceChildren extends JavaInstance {

    @Override
    public void log(Context context) {
        Log.d("JavaInstance","子类log");
        Toast.makeText(context,"调用了子类方法",Toast.LENGTH_SHORT).show();
    }
}
