// -------- binary_search --------
/*
主要用于查找指定元素是否存在
- bool binary_search(iterator beg, iterator end, value);
// 查到返回true 未查到返回false
// ===== 注意：在无序序列中不可用 =====
// 本质是二分搜索无序可能会导致结果错误
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>

void test(){
    std::vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(i);
    }
    // 查找是否有9
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    bool res = std::binary_search(v.begin(), v.end(), 9);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    if(res) std::cout << "找到元素" << std::endl;
    else std::cout << "未找到元素" << std::endl;
    std::cout << "uesd time: " << time_used.count() << std::endl;

}

int main(){
    test();

    return 0;
}