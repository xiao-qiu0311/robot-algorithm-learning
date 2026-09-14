// -------- map查找和统计 --------
/*
函数原型：
- find(key);    // 查找key是否存在 若存在返回迭代器 否则 返回mep.end()
- count(key);   // 统计key的元素个数
*/

#include <future>
#include <iostream>
#include <map>
#include <utility>

void test(){
    std::map<int, int> m;
    m.insert(std::make_pair(1, 10));
    m.insert(std::make_pair(2, 20));
    m.insert(std::make_pair(3, 30));
    m.insert(std::make_pair(4, 40));

    // 查找
    std::map<int, int>::iterator pos = m.find(3);
    if(pos != m.end()){
        std::cout << "查到元素 key: " << pos->first << " value: " << pos->second << std::endl;
    } else {
        std::cout << "未找到元素" << std::endl;
    }

    // 统计
    int num = m.count(3);  // num 只会是 0或1 ---> map不允许重复插入同一个key的元素
    std::cout << "num = " << num << std::endl;

}

int main(){
    test();
    
    return 0;
}