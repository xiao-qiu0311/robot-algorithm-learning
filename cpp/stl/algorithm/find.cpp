// ------- find --------
/*
查找指定元素，找到返回其迭代器，未找到返回结束迭代器end()
- find(iterator beg, iterator end, value)
*/

#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>

void test1(){
    std::vector<int> v;
    for(int i = 0; i < 10; i++){ v.push_back(i); }

    // 查找是否有5
    std::vector<int>::iterator it = std::find(v.begin(), v.end(), 5);
    if(it == v.end()){
        std::cout << "未找到元素" << std::endl;
    } else {
        std::cout << "找到元素" << *it << std::endl;
    }

}

// 查找自定义数据类型
class Person{
public:
    Person(std::string name, int age){
        this->m_Name = name;
        this->age = age;
    }

    // 必须重载== 底层find知道如何对比person数据类型
    bool operator==(const Person& p){
        if(this->m_Name == p.m_Name && this->age == p.age) return true;
        else return false;
    } 
    std::string m_Name;
    int age;

};


void test2(){
    std::vector<Person> v;
    // 创建数据
    Person p1("aaa", 10);
    Person p2("bbb", 20);
    Person p3("ccc", 30);
    Person p4("ddd", 40);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    Person pp("bbb", 20);

    // 查找是否存在pp
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    std::vector<Person>::iterator it = std::find(v.begin(), v.end(), pp);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    if(it == v.end()){
        std::cout << "未找到" << std::endl;
    } else{
        std::cout << "找到元素，姓名: " << (*it).m_Name << " 年龄: " << (*it).age << std::endl;
    }
    std::cout << "uesd time: " << time_used.count() << std::endl;

}

int main(){
    test1();
    test2();

    return 0;
}