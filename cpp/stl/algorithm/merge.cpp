// -------- merge --------
/*
两个容器元素合并 并存储到另一个容器中
函数原型：
- merge(interator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
// dest -- 目标容器开始迭代器
// 注意：两个容器必须都是有序且顺序一致的 合并后的容器也是有序的
*/

#include <algorithm>
#include <iostream>
#include <vector>

void MyPrint(int val){ std::cout << val << " "; }

void test(){
    std::vector<int> v1;
    std::vector<int> v2;

    for(int i = 0; i < 10; i++){
        v1.push_back(i);
        v2.push_back(i+1);
    }
    std::vector<int> v_target;
    v_target.resize(v1.size() + v2.size());

    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target.begin());
    std::for_each(v_target.begin(), v_target.end(), MyPrint);
    std::cout << std::endl;
}

int main(){
    test();

    return 0;
}