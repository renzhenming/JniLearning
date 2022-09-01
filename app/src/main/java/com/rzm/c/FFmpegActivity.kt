package com.rzm.c

import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class FFmpegActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_ffmpeg)
        var textView = findViewById<TextView>(R.id.text)
        textView.text = getFFmpegVersion()
    }

    private external fun getFFmpegVersion(): String
}