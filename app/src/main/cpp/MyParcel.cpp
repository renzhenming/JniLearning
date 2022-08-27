//
// Created by 任振铭 on 2022/8/27.
//

#include "MyParcel.h"

MyParcel::MyParcel() {
    this->mData = reinterpret_cast<char *>(malloc(1024));
}

MyParcel::~MyParcel() {
    if (this->mData) {
        free(this->mData);
        this->mData = NULL;
    }
    if (this->mDataPos) {
        this->mDataPos = NULL;
    }
}

void MyParcel::writeInt(int value) {
    //对象首地址(内存地址)的挪动位置mDataPos 第一次：0位置
    *reinterpret_cast<int *>(this->mData + this->mDataPos) = value;
    // this->mDataPos += sizeof(val); // 对象首地址(内存地址)的挪动位置mDataPos 第二次：4位置
    changPos(sizeof(value));// 对象首地址(内存地址)的挪动位置mDataPos 第二次：4位置
}

void MyParcel::setDataPosition(int position) {
    this->mDataPos = position;
}

int MyParcel::readInt() {
    int result = *reinterpret_cast<int *>(this->mData + this->mDataPos);
    changPos(sizeof(int));
    return result;
}

void MyParcel::changPos(int val) {
    this->mDataPos += val;
}
