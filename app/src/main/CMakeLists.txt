cmake_minimum_required(VERSION 3.10.2)
# Declares and names the project.
project("renzhenming_project")

# TODO 批量导入的方式（方法一）>>>>>>>>>>>>>>>>>>>>>>>>
#CMAKE_CURRENT_SOURCE_DIR,指的是当前处理的 CMakeLists.txt 所在的路径，CMAKE_SOURCE_DIR，不论采用何种编译方式,都是工程顶层目录
file(GLOB CPP_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.c)

# 添加一个库（动态库SHARED，静态库STATIC）
add_library(
        native-lib
        SHARED
        ${CPP_SOURCE}
)


# TODO 每个文件单独导入的方式（方法二）>>>>>>>>>>>>>>>>>>>>>>>>
#add_library( # Sets the name of the library.
#        native-lib
#        # Sets the library as a shared library.
#        SHARED
#        # Provides a relative path to your source file(s).
#        src/main/cpp/native-lib.cpp
#        src/main/cpp/native-lib2.cpp
#        src/main/cpp/parcel-lib.cpp
#        src/main/cpp/MyParcel.cpp
#        )

find_library( # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

#TODO 多CMakeLists文件处理方式
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cpp/libget)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cpp/libcount)



# TODO >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ffmpeg>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
# 1.引入头文件 FFmpeg
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cpp/ffmpeg/include)

# 2.引入库文件 FFmpeg
set(FFMPEG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cpp/ffmpeg/})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_CURRENT_SOURCE_DIR}/cpp/ffmpeg")

#添加avcodec
#add_library(avcodec SHARED IMPORTED)
#set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libavcodec.so)
#
##添加avfilter
#add_library(avfilter SHARED IMPORTED)
#set_target_properties(avfilter PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libavfilter.so)
#
##添加avformat
#add_library(avformat SHARED IMPORTED)
#set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libavformat.so)
#
##添加avutil
#add_library(avutil SHARED IMPORTED)
#set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libavutil.so)
#
##添加swresample
#add_library(swresample SHARED IMPORTED)
#set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libswresample.so)
#
##添加swscale
#add_library(swscale SHARED IMPORTED)
#set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libswscale.so)
## TODO >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ffmpeg>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>



target_link_libraries( # Specifies the target library.
        native-lib
        get # 具体的库 链接到 libnative-lib.so里面去
        count # 具体的库 链接到 libnative-lib.so里面去


#        -Wl,--start-group # 忽略顺序引发的问题
#        avcodec avfilter avformat avutil swresample swscale
#        -Wl,--end-group
        avcodec avfilter avformat avutil swresample swscale
        ${log-lib})
