//
// Created by 任振铭 on 2022/8/27.
//

#include <malloc.h>

#ifndef JNILEARNING_MYPARCEL_H
#define JNILEARNING_MYPARCEL_H


class MyParcel {
public:
    MyParcel();

    virtual ~MyParcel();

    void writeInt(int value);

    void setDataPosition(int position);

    int readInt();

private:
    char *mData = 0;//对象共享内存的首地址(内存地址)
    int mDataPos = 0;//对象共享内存的首地址(内存地址)的指针地址挪动位置
    void changPos(int val);// 用于改变指针地址挪动位置
    long *stringObj = NULL; // StringObj对象的 首地址(内存地址)
};


#endif //JNILEARNING_MYPARCEL_H
