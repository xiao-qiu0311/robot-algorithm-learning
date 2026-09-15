// -------- find_if --------
/*
- find(operator beg, operator end, _Pred);
// _Pred 函数或谓词
*/

#include <algorithm>
#include <iostream>
#include <vector>

class greater{
public:
    bool operator()(int v){ return v > 5; }
    
};

void test1(){
    std::vector<int> v;
    for(int i = 0; i < 10; i++){v.push_back(i);}
    std::vector<int>::iterator it = std::find_if(v.begin(), v.end(), greater());
    if(it == v.end()) std::cout << "未找到" << std::endl;
    else std::cout << "找到元素: " << *it << std::endl;

}

// 自定义数据类型
class Person{
public:
    Person(std::string name, int age){
        this->name_ = name;
        this->age_ = age;
    }

    std::string name_;
    int age_;

};


class greater20{
public:
    bool operator()(Person& p){ return p.age_ > 2; }

};

void test2(){
    std::vector<Person> v;

    Person p1("a", 1);
    Person p2("b", 2);
    Person p3("c", 3);
    Person p4("d", 4);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    // 找年龄大于2的人
    std::vector<Person>::iterator it = std::find_if(v.begin(), v.end(), greater20());
    if(it == v.end()) std::cout << "未找到" << std::endl;
    else std::cout << "找到姓名: " << (*it).name_ << " 年龄: " << (*it).age_ << std::endl;
}

int main(){
    test1();
    test2();

    return 0;
}