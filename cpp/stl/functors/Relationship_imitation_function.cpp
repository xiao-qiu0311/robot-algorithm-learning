// -------- 关系仿函数 --------
/*
实现关系对比
仿函数原型：
- template<class T> bool equal_to<T>        // 等于
- template<class T> bool not_equal_to<T>    // 不等于
- template<class T> bool greater<T>         // 大于
- template<class T> bool greater_equal<T>   // 大于等于
- template<class T> bool less<T>            // 小于
- template<class T> bool less_equal<T>      // 小于等于
*/

#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>

class MyCompare{
public:
    bool operator()(int v1, int v2){ return v1 > v2; }

};

// greater
void test1(){
    std::vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(40);
    v.push_back(20);
    v.push_back(50);

    // 降序
    // std::sort(v.begin(), v.end(), MyCompare());
    
    // 使用内建函数实现降序排列
    std::sort(v.begin(), v.end(), std::greater<int>());
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;


}

int main(){
    test1();

    return 0;
}