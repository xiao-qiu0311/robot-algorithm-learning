// -------- 一元谓词 --------
#include <algorithm>
#include <iostream>
#include <vector>

class GreatFive{
public:
    bool operator()(int val){ return val > 5; }

};

void test1(){
    std::vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(i);
    }

    // 查找大于5的数字
    // 算法find_if
    std::vector<int>::iterator it = std::find_if(v.begin(), v.end(), GreatFive()); // 匿名函数对象GreatFive()
    if(it == v.end()){
        std::cout << "未找到" << std::endl;
    } else {
        std::cout << "找到大于5的数字: " << *it << std::endl;
    }

}

int main(){
    test1();

    return 0;
}