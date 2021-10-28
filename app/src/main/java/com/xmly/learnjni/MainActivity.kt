package com.xmly.learnjni

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        findViewById<TextView>(R.id.sample_text).text = stringFromJNI2()
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(name:String): String
    external fun stringFromJNI2(): String

    private fun returnFromJNI(){
       Log.d("MainActivity","returnFromJNI -> ${System.currentTimeMillis()}");
    }
    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib2")
        }
    }
}