#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <ctime>

class Array{
public:
    // 构造函数 对成员初始化
    Array(int size = 10) : mCur_(0), mCap(size){
        mpArr = new int[mCap]();
    }

    ~Array(){
        // 释放资源
        delete[] mpArr;
        mpArr = nullptr; // 防止野指针的出现
    }

public:
    // 定义操作接口
    // 末尾增加元素
    void push_back(int val){
        if(mCur_ == mCap){
            // 扩容
            expand(2 * mCap);
        }
        mpArr[mCur_++] = val;
    }

    // 末尾删除元素
    void pop_back(){
        // 可直接将mCur_ -- 访问不到原本最后一个元素
        if(mCur_ == 0){
            return;
        }
        mCur_ --;
    }

    // 按位置增加元素
    void insert(int pos, int val){
        if(pos < 0 || pos > mCur_){
            return; // throw "pos invalid"
        }

        // 考虑是否有剩余空间插入
        if(mCur_ == mCap){
            expand(2 * mCap);
        }

        // 移动元素
        for(int i =mCur_ - 1; i >= pos; i--){
            mpArr[i + 1] = mpArr[i];
        }
        mpArr[pos] = val;
        mCur_++;
    }

    // 按位置删除（与find配合）
    void erase(int pos){
        // 判断参数有效性
        if(pos < 0 || pos >= mCur_){
            return;
        }
        for(int i = pos + 1; i < mCur_; i++){
            mpArr[i - 1] = mpArr[i];
        }
        mCur_ --;
    }

    // 元素查询
    int find(int val){
        for(int i = 0; i < mCur_; i++){
            if(mpArr[i] == val){
                return i;
            }
        }
        return -1;
    }

    // 打印数据
    void show() const{
        for(int i = 0; i < mCur_; i++){
            std::cout << mpArr[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    // 动态扩容、使用指针指向内存
    int* mpArr; // 指向堆上可扩容的内存
    // 需要一个变量描述数组扩容的总大小
    int mCap; // 数组容量
    int mCur_; // 数组有效元素个数

private:
    // 内部数组扩容接口
    void expand(int size){
        // 扩容：在原有基础上扩容新的内存（2倍） 拷贝原有数据 释放原有堆内存
        int *p = new int[size];
        memcpy(p, mpArr, sizeof(int) * mCap); // 属于头文件<cstring>
        delete[] mpArr;

        mpArr = p;
        mCap = size;
    }
};

int main(){
    Array arr;

    srand(time(0));
    for(int i = 0; i < 10; i++){
        arr.push_back(rand() % 100);
    }
    arr.show();
    arr.pop_back();
    arr.show();

    arr.insert(0, 100);
    arr.show();

    int pos = arr.find(12);
    std::cout << pos << std::endl;

    return 0;
}