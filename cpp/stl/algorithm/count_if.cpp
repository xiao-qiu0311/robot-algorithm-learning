// -------- count_if --------
/*
按条件统计元素个数
函数原型：
- count_if(iterator beg, iterator end, _Pred);
*/

#include <algorithm>
#include <iostream>
#include <vector>

class Greater20{
public:
    bool operator()(int val){ return  val > 20;}

};

// 统计内置数据类型
void test1(){
    std::vector<int> v;
    v.push_back(10);
    v.push_back(40);
    v.push_back(30);
    v.push_back(20);
    v.push_back(40);
    v.push_back(20);
    v.push_back(20);

    // _Pred --> 谓词
    int num = std::count_if(v.begin(), v.end(), Greater20());
    std::cout << "number of greater than 20: " << num << std::endl;

}

// 统计自定义数据类型
class Person{
public:
    Person(std::string name, int age){
        this->name_ = name;
        this->age_ = age;
    }

    std::string name_;
    int age_;

};

class AgeGreater30{
public:
    bool operator()(const Person& p1){
        if(p1.age_ > 30) return true;
        else return false;
    }

};

void test2(){
    std::vector<Person> v;
    Person p1("a", 20);
    Person p2("b", 50);
    Person p3("c", 34);
    Person p4("d", 20);
    Person p5("e", 20);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);

    // age greater than 30
    int num = std::count_if(v.begin(), v.end(), AgeGreater30());
    std::cout << "number of age whose graeter than 30: " << num << std::endl;

}

int main(){
    test1();
    test2();

    return 0;
}