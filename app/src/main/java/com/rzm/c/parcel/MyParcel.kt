package com.rzm.c.parcel

class MyParcel private constructor() {
    // used by native code
    private var mNativePtr: Long = 0

    companion object {
        init {
            System.loadLibrary("native-lib")
        }

        fun obtain(): MyParcel {
            return MyParcel()
        }
    }

    init {
        mNativePtr = nativeCreate()
    }

    fun writeInt(value: Int) {
        nativeWriteInt(mNativePtr, value)
    }

    fun setDataPosition(position: Int) {
        nativeSetDataPosition(mNativePtr, position)
    }

    fun readInt(): Any {
        return nativeReadInt(mNativePtr)
    }

    private external fun nativeCreate(): Long
    private external fun nativeReadInt(mNativePtr: Long): Int
    private external fun nativeSetDataPosition(mNativePtr: Long, position: Int)
    private external fun nativeWriteInt(mNativePtr: Long, value: Int)
}