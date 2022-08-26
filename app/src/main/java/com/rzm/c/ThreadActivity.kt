package com.rzm.c

import android.os.Bundle
import android.os.Looper
import android.util.Log
import android.view.View
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity

class ThreadActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_thread)
    }

    external fun nativeThread()
    external fun closeThread()

    fun nativeCallJava(view: View?) {
        nativeThread()
    }

    override fun onDestroy() {
        super.onDestroy()
        closeThread()
    }

    fun updateActivityUI() {
        if (Looper.getMainLooper() == Looper.myLooper()) {
            // TODO C++ 用主线程调用
            AlertDialog.Builder(ThreadActivity@ this)
                .setTitle("UI")
                .setMessage("updateActivityUI Activity UI ...").setPositiveButton("确定", null)
                .show();
        } else {
            // TODO C++ 用异步线程调用到此函数 ----> 异步线程
            Log.d("", "updateActivityUI 所属于子线程，只能打印日志了..");
            runOnUiThread {
                // 哪怕是异步线程 UI操作 正常下去 runOn @Override
                // 可以在子线程里面 操作UI
                AlertDialog.Builder(ThreadActivity@ this)
                    .setTitle("updateActivityUI").setMessage("所属于子线程，只能打印日志了..")
                    .setPositiveButton("确定", null)
                    .show();
            }
        }
    }
}