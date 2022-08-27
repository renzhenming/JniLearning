package com.rzm.c.parcel

import android.os.Bundle
import android.os.Parcel
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.rzm.c.R

class ParcelActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_parcel)
        initAndroidParcel()
        initMyParcel()
    }

    private fun initMyParcel() {
        var parcel = MyParcel.obtain() // 使用Parcel而已

        // 【重点：怎么去写入】
        parcel.writeInt(10000)
        parcel.writeInt(20000)
        /*parcel.writeString("AAA")
        parcel.writeString("BBB")*/

        parcel.setDataPosition(0)

        // 【重点：怎么去读取】
        val r1 = parcel.readInt()
        val r2 = parcel.readInt()
        /*val r3 = parcel.readString()
        val r4 = parcel.readString()
        Log.d("Derry", "DParcel 读取的结果是 r1:$r1, r2:$r2, r3:$r3, r4:$r4")*/

        // String 写入 与 读取 后面再搞，还没有写完
        Log.d("ParcelActivity", "initMyParcel 读取的结果是 r1:$r1, r2:$r2")
    }

    private fun initAndroidParcel() {
        var parcel = Parcel.obtain() // 使用Parcel而已

        // 【重点：怎么去写入】
        parcel.writeInt(12)
        parcel.writeInt(24)

        parcel.setDataPosition(0)

        // 【重点：怎么去读取】
        val r1 = parcel.readInt()
        val r2 = parcel.readInt()
        Log.d("ParcelActivity", "initAndroidParcel 读取的结果是 r1:$r1, r2:$r2")
    }
}