cmake_minimum_required(VERSION 3.10.2)

# 批量导入
file(GLOB SOURCE *.cpp)

add_library(
        count
        STATIC        # 最终生成 libcount.so  剔除 lib  剔除 .so
        ${SOURCE}
)


