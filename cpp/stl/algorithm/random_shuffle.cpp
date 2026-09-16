// -------- random_shuffle --------
/*
功能描述：
- 将指定范围内的元素随机调整次序
函数原型：
- random_suffle(iterator beg, iterator end);
*/

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <vector>
#include <ctime>
#include <iostream>

void MyPrint(int val){ std::cout << val << " "; }

void test(){
    std::vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(i);
    }

    std::cout << "vector before random_shuffle:" << std::endl;
    std::for_each(v.begin(), v.end(), MyPrint);
    std::cout << std::endl;

    std::cout << "vector after random_shuffle: " << std::endl;
    // random_shuffle可以种随机数种子
    srand((unsigned int)time(NULL)); // 种随机数种子
    std::random_shuffle(v.begin(), v.end());
    std::for_each(v.begin(), v.end(), MyPrint);
    std::cout << std::endl;
    
}

int main(){
    test();

    return 0;
}