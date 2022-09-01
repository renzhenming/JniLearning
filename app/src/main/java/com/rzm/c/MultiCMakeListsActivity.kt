package com.rzm.c

import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity

class MultiCMakeListsActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_multi_cmake_lists)
    }

    fun invokeStatic(view: View) {
        invokeStaticNative()
    }


    fun invokeShared(view: View) {
        invokeSharedNative()
    }

    private external fun invokeStaticNative()
    private external fun invokeSharedNative()
}