package com.rzm.c;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.rzm.c.utils.JniUtils;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private JniUtils utils;
    private JavaInstance instance;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        utils = new JniUtils();
        instance = new JavaInstance();
    }

    /**
     * 通过jni修改Java对象中非静态成员变量
     * @param view
     */
    public void changeField(View view) {
        Log.d(TAG,"修改前"+utils.key);
        Toast.makeText(getApplicationContext(),"修改前"+utils.key,Toast.LENGTH_SHORT).show();
        String s = utils.changeJavaField();
        Toast.makeText(getApplicationContext(),"修改后"+utils.key,Toast.LENGTH_SHORT).show();
        Log.d(TAG,"修改后"+utils.key);
    }

    /**
     * 通过jni修改指定Java对象中非静态成员变量
     * @param view
     */
    public void changeField2(View view) {
        Log.d(TAG,"修改前"+instance.key);
        Toast.makeText(getApplicationContext(),"修改前"+instance.key,Toast.LENGTH_SHORT).show();
        String s = utils.changeJavaField2(instance);
        Toast.makeText(getApplicationContext(),"修改后"+instance.key,Toast.LENGTH_SHORT).show();
        Log.d(TAG,"修改后"+instance.key);
    }
}
