package com.rzm.c

import android.content.Intent
import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import com.rzm.c.parcel.ParcelActivity

class HomeActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_home)
    }

    fun goJniPage(view: View) {
        startActivity(Intent(applicationContext, MainActivity::class.java))
    }

    fun parcel(view: View) {
        startActivity(Intent(applicationContext, ParcelActivity::class.java))
    }
}