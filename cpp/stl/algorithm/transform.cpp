// -------- 常用遍历算法 —— transform --------
/*
函数原型：
- transform(iterator beg1, iterator end1, iterator beg2, _func);
// beg1 源容器开始迭代器
// end1 源容器结束迭代器
// beg2 目标容器开始迭代器
// _func 函数或函数对象
*/

#include <vector>
#include <algorithm>
#include <iostream>

class Transform{
public:
    int operator()(int v){ return v + 1; }

};

class print{
public:
    void operator()(int v){ std::cout << v << " "; }

};

void test(){
    std::vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(i);
    }

    std::vector<int> vTarget; // 目标容器
    vTarget.resize(v.size()); // 开辟空间
    std::transform(v.begin(), v.end(), vTarget.begin(), Transform());
    std::for_each(vTarget.begin(), vTarget.end(), print());
    std::cout << std::endl;

}

int main(){
    test();

    return 0;
}