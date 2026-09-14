// -------- 二元谓词 --------
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

class MyCompare{
public:
    bool operator()(int v1, int v2){ return v1 > v2; }

};

void test1(){
    std::vector<int> v;
    v.push_back(10);
    v.push_back(40);
    v.push_back(20);
    v.push_back(30);
    v.push_back(50);
    
    std::sort(v.begin(), v.end());
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); it ++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "------------------------------" << std::endl;
    // 使用函数对象改变算法策略-->变为降序
    std::sort(v.begin(), v.end(), MyCompare());
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); it ++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

}

int main(){
    test1();

    return 0;
}