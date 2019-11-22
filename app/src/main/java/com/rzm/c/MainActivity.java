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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        utils = new JniUtils();
    }

    public void changeField(View view) {
        Log.d(TAG,"修改前"+utils.key);
        Toast.makeText(getApplicationContext(),"修改前"+utils.key,Toast.LENGTH_SHORT).show();
        String s = utils.changeJavaField();
        Toast.makeText(getApplicationContext(),"修改后"+utils.key,Toast.LENGTH_SHORT).show();
        Log.d(TAG,"修改后"+utils.key);
    }
}
