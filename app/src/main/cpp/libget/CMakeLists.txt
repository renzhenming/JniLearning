cmake_minimum_required(VERSION 3.10.2)

file(GLOB SOURCE *.c *.cpp)
add_library(
        get
        SHARED
        ${SOURCE}
)


