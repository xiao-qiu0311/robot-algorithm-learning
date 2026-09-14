// -------- map构造和赋值 --------
/*
函数原型：
- map<T1, T2> mp;
- map(const map &mp);
赋值：
- map& operator=(const map& mp);
*/

#include <iostream>
#include <map>
#include <utility>

void printMap(const std::map<int, int>& m){
    for(std::map<int, int>::const_iterator it = m.begin(); it != m.end(); it++){
        // 对组取值有两种方法: (*it).某个值 || it->某个值
        std::cout << "key = " << it->first << " value = " << (*it).second << std::endl;
    }
    std::cout << std::endl;
}

void test(){
    std::map<int, int> m;
    // 会自动按照key排序

    m.insert(std::pair<int, int>(1, 10));
    m.insert(std::pair<int, int>(2, 20));
    m.insert(std::pair<int, int>(3, 30));
    m.insert(std::pair<int, int>(4, 40));

    printMap(m);

    // 拷贝构造
    std::map<int, int> m2(m);
    printMap(m2);

    // 赋值
    std::map<int, int> m3;
    m3 = m2;
    printMap(m3);

}

int main(){
    test();

    return 0;
}