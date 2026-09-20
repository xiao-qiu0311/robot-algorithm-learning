#include <algorithm>
#include <iostream>
#include <memory>
#include "cat.hpp"

using namespace std;

std::unique_ptr<Cat> get_unique_ptr(){
    std::unique_ptr<Cat> cat_p = std::make_unique<Cat>();
    return cat_p;
}

int main(int argc, char* argv[]){
    // 1、transpose ptrs
    std::unique_ptr<Cat> c_p_1 = std::make_unique<Cat>("dd");
    std::shared_ptr<Cat> c_p_2 = std::move(c_p_1); // can't use c_p_1

    cout << "c_p_2 use conut: " << c_p_2.use_count() << endl;

    // func
    std::shared_ptr c_p_3 = get_unique_ptr();
    if(c_p_3){
        c_p_3->cat_info();
        cout << "transpose successfully" << endl;
        cout << "c_p_3 use conut: " << c_p_3.use_count() << endl;
    }

    cout << "------ 在main函数中最后一句结束后会自动调用析构函数 ------" << endl;
    return 0;
}