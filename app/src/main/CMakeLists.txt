cmake_minimum_required(VERSION 3.10.2)
# Declares and names the project.
project("renzhenming_project")

# TODO 批量导入的方式（方法一）>>>>>>>>>>>>>>>>>>>>>>>>
file(GLOB CPP_SOURCE ${CMAKE_SOURCE_DIR}/cpp/*.cpp ${CMAKE_SOURCE_DIR}/cpp/*.c)

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
add_subdirectory(${CMAKE_SOURCE_DIR}/cpp/libget)
add_subdirectory(${CMAKE_SOURCE_DIR}/cpp/libcount)

target_link_libraries( # Specifies the target library.
        native-lib
        get # 具体的库 链接到 libnative-lib.so里面去
        count # 具体的库 链接到 libnative-lib.so里面去
        ${log-lib})
