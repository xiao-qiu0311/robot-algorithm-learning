// -------- reverse --------
/*
- 将容器内元素进行反转
- reverse(iterator beg, iterator end);
*/

#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

void MyPrint(int val){
    std::cout << val << " ";
}

void test(){
    std::vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(i);
    }
    std::cout << "v before reversing: " << std::endl;
    std::for_each(v.begin(), v.end(), MyPrint);
    std::cout << std::endl;

    std::reverse(v.begin(), v.end());

    std::cout << "v after reversing: " << std::endl;
    std::for_each(v.begin(), v.end(), MyPrint);
    std::cout << std::endl;


}

int main(){
    test();

    return 0;
}