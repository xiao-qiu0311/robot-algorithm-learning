// -------- 算术仿函数 --------
/*
功能描述：
- 实现四则运算
- 其中negate是一元运算 其他都是二元运算
仿函数原型：
- template<class T> T plus<T>           // 加法
- template<class T> T minus<T>          // 减法
- template<class T> T multiplies<T>     // 乘法
- template<class T> T divides<T>        // 除法
- template<class T> T modulus<T>        // 取模
- template<class T> T negate<T>         // 取反
*/

#include <iostream>
#include <algorithm>
#include <functional>

// negate 一元仿函数 取反仿函数
void test1(){
    std::negate<int> n;

    int res = n(50);

    std::cout << res << std::endl;

}

// plus 二元仿函数 加法
void test2(){
    std::plus<int> p;
    std::cout << p(10, 20) << std::endl;
    // 二元仿函数用法与plus类似
}

int main(){
    test2();

    return 0;
}