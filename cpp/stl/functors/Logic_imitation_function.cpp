// -------- 逻辑仿函数 --------
/*
实现逻辑运算
函数原型：
- template<class T> bool logical_and<T> // 与
- template<class T> bool logical_or<T>  // 或
- template<class T> bool logical_not<T> // 非
*/

#include <functional>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>


// 逻辑非 logical_not
void test(){
    std::vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    v.push_back(false);

    for(std::vector<bool>::iterator it = v.begin(); it != v.end(); it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 利用逻辑非 将v放到v2中并执行取反
    std::vector<bool> v2;
    //目标容器必须提前开辟空间
    v2.resize(v.size());
    // 利用逻辑非搬运容器并进行取反
    std::transform(v.begin(), v.end(), v2.begin(),std::logical_not<bool>());
    for(std::vector<bool>::iterator it = v2.begin(); it != v2.end(); it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

}

int main(){
    test();

    return 0;
}