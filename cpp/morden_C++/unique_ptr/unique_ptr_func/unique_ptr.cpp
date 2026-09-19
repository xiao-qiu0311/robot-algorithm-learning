#include <algorithm>
#include <iostream>
#include <memory>
#include "cat.hpp"

using namespace std;

// 用pass by value会导致指针的所有权到函数中 结束后会直接销毁
void do_with_cat_pass_value(std::unique_ptr<Cat> c){ c->cat_info(); }

// 有两种——加const 不加const--->不能修改指向而非值
void do_with_cat_pass_ref(const std::unique_ptr<Cat> &c){ 
    c->set_cat_name("oo"); 
    c->cat_info(); 
    // c.reset(); 
}

// 链式函数
std::unique_ptr<Cat> get_unique_ptr(){
    std::unique_ptr<Cat> p_dog = std::make_unique<Cat>("Locaal cat");
    cout << "unique address: " << p_dog.get() << endl; // get() 和 取址符& 返回的地址不同
    cout << "unique address: " << &p_dog << endl; // get() 和 取址符& 返回的地址不同
    return p_dog;
}

int main(int argc, char* argv[]){
    // 1、pass by value
    unique_ptr<Cat> c1 = make_unique<Cat>("f1");
    do_with_cat_pass_value(std::move(c1)); // 直接传c1会报错 需要用std::move
    // c1->cat_info();  // 这样无法调用
    do_with_cat_pass_value(make_unique<Cat>()); // 默认转换为move

    // 2、pass by reference
    unique_ptr<Cat> c2 = make_unique<Cat>("f2");
    // 不加const
    do_with_cat_pass_ref(c2);
    cout << "cat address " << c2.get() << endl;

    // 链式
    get_unique_ptr()->cat_info();

    cout << "------ 在main函数中最后一句结束后会自动调用析构函数 ------" << endl;
    return 0;
}