// -------- set容器排序 --------
/*
主要技术点：利用仿函数可以改变排序规则
*/

#include <iostream>
#include <set>

// set 容器排序 存放自定义数据类型

class Person{
public:
    Person(std::string name, int age){
        this->m_Name = name;
        this->m_Age = age;
    }

    std::string m_Name;
    int m_Age;

};

class MyCompare{
public:
    bool operator()(const Person& p1, const Person& p2) const {
        return p1.m_Age < p2.m_Age;
    }

};


void test(){
    std::set<Person, MyCompare> s;
    
    Person p1("刘备", 24);
    Person p2("关羽", 28);
    Person p3("张飞", 25);
    Person p4("孙权", 21);
    
    s.insert(p1);
    s.insert(p2);
    s.insert(p3);
    s.insert(p4);

    for(std::set<Person, MyCompare>::iterator it = s.begin(); it != s.end(); it++){
        std::cout << "姓名: " << it->m_Name << " 年龄: " << it->m_Age << std::endl;
    }
}

int main(){
    test();

    return 0;
}