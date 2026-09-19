#include <algorithm>
#include <iostream>
#include <memory>
#include "cat.hpp"

using namespace std;

int main(int argc, char* argv[]){
    // 常量类型
    shared_ptr<int> i_p_1 = make_shared<int>(10);
    cout << "value: " << *i_p_1 << endl;
    cout << "use count: " << i_p_1.use_count() << endl;

    // copy
    shared_ptr<int> i_p_2 = i_p_1;
    cout << "i_p_1 use count: " << i_p_1.use_count() << endl;
    cout << "i_p_2 use count: " << i_p_2.use_count() << endl;

    // change
    *i_p_2 = 30; // two pointers pointing a same value, change one of them, the other changes too.
    cout << "i_p_1: " << *i_p_1 << endl;
    cout << "i_p_2: " << *i_p_2 << endl;

    // if change i_p_2 to nullptr, i_p_1 won't change
    cout << endl;
    i_p_2 = nullptr;
    cout << "i_p_1 use count: " << i_p_1.use_count() << endl; 
    cout << "i_p_2 use count: " << i_p_2.use_count() << endl;
    // // if change i_p_1, i_p_2 won't change too 
    shared_ptr<int> i_p_3 = i_p_1;
    i_p_1 = nullptr;
    cout << "i_p_1 use count: " << i_p_1.use_count() << endl; // 0
    cout << "i_p_2 use count: " << i_p_2.use_count() << endl; // 2
    cout << "i_p_3 use count: " << i_p_3.use_count() << endl; // 2

    // 自定义类型

    cout << "------ 在main函数中最后一句结束后会自动调用析构函数 ------" << endl;
    return 0;
}