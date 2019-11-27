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
    private JavaInstance childInstance;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        utils = new JniUtils();
        instance = new JavaInstance();
        childInstance = new JavaInstanceChildren();
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

    /**
     * c++修改Java对象中的静态属性值
     * @param view
     */
    public void changeStaticField(View view) {
        Log.d(TAG,"修改前"+instance.keyStatic);
        Toast.makeText(getApplicationContext(),"修改前"+instance.keyStatic,Toast.LENGTH_SHORT).show();
        String s = utils.changeJavaStaticField(instance);
        Toast.makeText(getApplicationContext(),"修改后"+instance.keyStatic,Toast.LENGTH_SHORT).show();
        Log.d(TAG,"修改后"+instance.keyStatic);
    }

    /**
     * c++调用Java中的成员方法
     * @param view
     */
    public void callJavaMethod(View view) {
        utils.callJavaMethod(instance,this);
    }

    /**
     * C++调用Java静态成员方法
     * @param view
     */
    public void callJavaStaticMethod(View view) {
        utils.callJavaStaticMethod(instance,this);
    }

    /**
     * C++调用Java构造方法
     * @param view
     */
    public void callJavaConstructMethod(View view) {
        long time = utils.callJavaConstructMethod(instance);
        System.out.println("getTime = "+time);
    }

    /**
     *  C++调用被子类覆盖的父类方法
     * @param view
     */
    public void callJavaNonVirtualMethod(View view) {
        utils.callJavaNonVirtualMethod(childInstance,this);
    }

    /**
     * C++调用子类重写父类后的方法
     * @param view
     */
    public void callJavaOverrideMethod(View view) {
        utils.callJavaVirtualMethod(childInstance,this);
    }

    /**
     * C++操作Java中的数组
     * @param view
     */
    public void modifyJavaArray(View view) {
        int arr [] = {12,3,43,55,44,1,566};
        utils.setJavaArray(arr);
        for (int i : arr) {
            System.out.println(i);
        }
        //打印发现第一个元素变成了999
    }

    /**
     * C++操作Java中的字符串
     * @param view
     */
    public void modifyJavaString(View view) {
        String value = "tomorrow is good";
        utils.setString(value);
        System.out.println(value);
    }

    /**
     * C++层返回一个数组到Java层
     * @param view
     */
    public void returnArrayFromCPP(View view) {
        int arr[] = utils.getArray();
        for (int i : arr) {
            System.out.println(i);
        }
    }

    /**
     * C++层抛出异常到Java层
     * @param view
     */
    public void throwException(View view) {
        try {
            utils.catchException(instance);
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("发生异常："+e.getMessage());
        } finally {
        }
    }

    /**
     * C++局部引用
     * @param view
     */
    public void localReference(View view) {
        utils.localReference();
    }
}
