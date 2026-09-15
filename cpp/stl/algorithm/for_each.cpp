// -------- 常用遍历算法 —— for_each --------
/*
函数原型：
- for_each(iterator beg, iterator end, func);
*/

#include <algorithm>
#include <iostream>
#include <vector>

// 普通函数
void print01(int val){
    std::cout << val << " ";
}

// 仿函数
class print02{
public:
    void operator()(int val){ std::cout << val << " "; }

};

void test(){
    std::vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(i);
    }

    std::for_each(v.begin(), v.end(), print01);
    std::cout << std::endl;

    std::for_each(v.begin(), v.end(), print02());
    std::cout << std::endl;

}

int main(){
    test();

    return 0;
}