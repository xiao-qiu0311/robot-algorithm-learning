#include <iostream>
#include <memory>
#include "cat.hpp"

using namespace std;

int main(int argc, char* argv[]){
    // ==================== stack =========================
    // Cat c1("ok");
    // c1.cat_info();
    // // 局部作用域
    // {
    //     Cat c1("ok");
    //     c1.cat_info();
    // }
    // ===================================================

    // ==================== heap =========================
    // // raw pointer 非常不安全
    // Cat *c_p1 = new Cat("yy");
    // int *i_p1 = new int(100);
    // c_p1->cat_info();
    // {
    //     int *i_p1 = new int(200);
    //     Cat *c_p1 = new Cat("yy_scope");
    //     c_p1->cat_info();
    //     delete c_p1; // 手动释放内存
    //     delete i_p1; // 作用域内释放后无需在作用域外再次释放否则会导致程序崩溃
    // }
    // delete c_p1;
    // ===================================================

    // ==================== unique_pointer的三种创建方式 =========================
    // 法一：
    // Cat *c_p2 = new Cat("qiu");
    // std::unique_ptr<Cat> u_c_p2{c_p2};
    // // 建议销毁c_p2否则如下
    // // c_p2依然可用
    // c_p2->cat_info();
    // // u_c_p2亦然
    // u_c_p2->cat_info();
    // c_p2->set_cat_name("ok");
    // u_c_p2->cat_info();
    // // 销毁
    // delete c_p2;
    // c_p2 = nullptr;
    // u_c_p2->cat_info();

    // 法二：new
    std::unique_ptr<Cat> u_c_p3{new Cat("dd")};
    std::unique_ptr<int> u_i_p3{new int(100)};
    u_c_p3->cat_info();
    u_c_p3->set_cat_name("oo");
    u_c_p3->cat_info();
    cout << *u_i_p3 << endl; // 解引用
    cout << "int address" << u_i_p3.get() << endl; // 通过get获取地址
    cout << "int address" << u_c_p3.get() << endl;

    cout << endl;

    // 推荐-法三：std::make_unique
    std::unique_ptr<Cat> u_c_p4 = make_unique<Cat>();
    std::unique_ptr<int> u_i_p4 = make_unique<int>(200);
    u_c_p4->cat_info();
    u_c_p4->set_cat_name("pp");
    u_c_p4->cat_info();
    cout << *u_i_p4 << endl; // 解引用
    cout << "int address" << u_i_p4.get() << endl; // 通过get获取地址
    cout << "int address" << u_c_p4.get() << endl;
    // get和常量类型


    // ========================================================================

    cout << "------ 在main函数中最后一句结束后会自动调用析构函数 ------" << endl;
    return 0;
}