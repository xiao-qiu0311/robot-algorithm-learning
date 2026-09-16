// -------- sort --------
/*
函数原型：
- sort(iterator beg, iterator end, _Pred);
*/

#include <functional>
#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

void MyPrint(int val){ std::cout << val << " "; }

void test(){
    std::vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(60);
    v.push_back(20);
    v.push_back(40);
    v.push_back(70);
    v.push_back(5);

    std::sort(v.begin(), v.end());
    std::for_each(v.begin(), v.end(), MyPrint);
    std::cout << std::endl;

    // 改为降序
    std::sort(v.begin(), v.end(), std::greater<int>());
    // greater--> 内置降序排列 属于头文件<algorithm>
    std::for_each(v.begin(), v.end(), MyPrint);
    std::cout << std::endl;
}

int main(){
    test();

    return 0;
}