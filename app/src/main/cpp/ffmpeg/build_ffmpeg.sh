#!/bin/bash
NDK_ROOT=/Users/renzhenming/Android/ndk/android-ndk-r17c
#TOOLCHAIN 变量指向NDK中的交叉编译gcc所在的目录
#/root/android-ndk-r17c/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin
#/root/android-ndk-r17c/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/
TOOLCHAIN=$NDK_ROOT/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64
#FLAGS与INCLUDES变量 可以从 AS ndk工程的。externalnaticveBuild/camake/debug/armeabi-v7a/build.ninja中拷贝需要，注意的是**地址**
FLAGS="-isystem $NDK_ROOT/sysroot/usr/include/arm-linux-androideabi -D__ANDROID_API__=21 -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -fno-addrsig -march=armv7-a -mthumb -Wa,--noexecstack -Wformat -Werror=format-security  -O0 -fno-limit-debug-info  -fPIC"
INCLUDES="-isystem $NDK_ROOT/sources/cxx-stl/llvm-libc++/include -isystem $NDK_ROOT/sources/android/surpport/include -isystem $NDK_ROOT/sources/cxx-stl/llvm-libc++abi/include"

#执行configure脚本，用于生成makefile
#--prefix：安装目录
#--enable-small：优化大小
#--disable-avdevice：关闭所有编码器（播放不需要编码）
#--disable-muxers：关闭所有复用器（封装器），不需要生成MP4这样的文件，所以关闭
#--disable-filters：关闭视频滤镜
#--enable-cross-compile：开启交叉编译
#disable-shared enable-static：不写也可以，默认就是这样
#--sysroot
#--extra-cflags：会传给gcc的参数
#--arch--target-os：

PREFIX=./android/armeabi
./configure \
--prefix=$PREFIX \
--enable-small \
--disable-programs \
--disable-avdevice \
--disable-encoders \
--disable-muxers \
--disable-filters \
--enable-cross-compile \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
--enable-shared \
--disable-static \
--sysroot=$NDK_ROOT/platforms/android-17/arch-arm \
--extra-cflags="-isysroot $NDK_ROOT/sysroot -isystem $NDK_ROOT/sysroot/usr/include/arm-linux-androideabi -D__ANDROID_API__=17 -U_FILE_OFFSET_BITS  -DANDROID -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -mthumb -Wa,--noexecstack -Wformat -Werror=format-security  -O0 -fPIC" \
--arch=arm \
--target-os=android

make clean
make install
