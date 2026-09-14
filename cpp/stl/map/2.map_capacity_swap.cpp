// -------- 大小和交换 --------
/*
函数原型：
- size();
- empty();
- swap(st);
*/

#include <iostream>
#include <map>
#include <algorithm>
#include <utility>

void printMap(const std::map<int, int>& m){
    for(std::map<int, int>::const_iterator it = m.begin(); it != m.end(); it++){
        // 对组取值有两种方法: (*it).某个值 || it->某个值
        std::cout << "key = " << it->first << " value = " << (*it).second << std::endl;
    }
    std::cout << std::endl;
}

void test1(){
    std::map<int, int> m1;
    m1.insert(std::pair<int, int>(1, 10));
    m1.insert(std::pair<int, int>(2, 20));
    m1.insert(std::pair<int, int>(3, 30));

    if(m1.empty()){
        std::cout << "m1为空" << std::endl;
    } else {
        std::cout << "m1不为空" << std::endl;
        std::cout << "m1大小 = " << m1.size() << std::endl;
    }

}

void test2(){
    std::map<int, int> m1;
    m1.insert(std::pair<int, int>(1, 10));
    m1.insert(std::pair<int, int>(2, 20));
    m1.insert(std::pair<int, int>(3, 30));

    std::map<int, int> m2;
    m2.insert(std::pair<int, int>(4, 100));
    m2.insert(std::pair<int, int>(5, 200));
    m2.insert(std::pair<int, int>(6, 300));

    std::cout << "交换前: " << std::endl;
    printMap(m1);
    printMap(m2);

    m1.swap(m2);

    std::cout << "交换后: " << std::endl;
    printMap(m1);
    printMap(m2);

}

int main(){
    test1();
    test2();

    return 0;
}