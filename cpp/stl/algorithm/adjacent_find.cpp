// -------- adjacent_find --------
/*
- adjacent_find(iterator beg, iterator end);
========= 重复 相连 =========
*/

#include <iostream>
#include <algorithm>
#include <vector>

void test(){
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(2);
    v.push_back(0);
    v.push_back(2);
    v.push_back(3);
    v.push_back(3);

    std::vector<int>::iterator it = std::adjacent_find(v.begin(), v.end());
    if(it == v.end()) std::cout << "未找到元素" << std::endl;
    else std::cout << "找到元素: " << *it << std::endl;
}

int main(){
    test();

    return 0;
}