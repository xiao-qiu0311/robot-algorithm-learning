// -------- 统计元素个数 --------
/*
函数原型：
- count(iterator beg, iterator end, value);
*/

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

// 统计内置数据类型
void test1(){
    std::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(30);

    int num = std::count(v.begin(), v.end(), 40);

    std::cout << "number of 40: " << num << std::endl;

}

// 统计自定义数据类型
class Person{
public:
    Person(std::string name, int age){
        this->name_ = name;
        this->age_ = age;
    }

    // 重载内部== 底层重载必须加const
    bool operator==(const Person& p){
        if(this->age_ == p.age_) return true;
        else return false;
    }

    std::string name_;
    int age_;

};

void test2(){
    std::vector<Person> v;
    Person p1("a", 12);
    Person p2("b", 18);
    Person p3("c", 29);
    Person p4("d", 30);
    Person p5("e", 30);
    Person p6("f", 12);
    Person p7("g", 12);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);
    v.push_back(p6);
    v.push_back(p7);

    Person p("aa", 12);

    int num = std::count(v.begin(), v.end(), p);
    std::cout << "same age with aa: " << num << std::endl;

}

int main(){
    test1();
    test2();

    return 0;
}