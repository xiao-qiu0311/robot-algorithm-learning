#include <iostream>

// 函数对象在使用时，可以像普通函数一样调用，可以有参数，可以有返回值
class MyAdd{
public:
    int operator()(int a, int b){ return a + b; }

};

void test1(){
    MyAdd myadd;
    std::cout << myadd(10, 23) << std::endl;

}

// 函数对象超出普通函数的概念 可以有自己的状态
class MyPrint{
public:
    MyPrint(){ this->count = 0; }

    void operator()(std::string test) { std::cout << test << std::endl; this->count++; }

    int count; // 内部自己的状态

};

void test2(){
    MyPrint myprint;
    myprint("hello world");
    std::cout << "MyPrint调用次数: " << myprint.count << std::endl;

}

// 函数对象可以作为参数进行传递
void doPrint(MyPrint& mp, std::string test){
    mp(test); // 自身重载函数对象
}

void test3(){
    MyPrint myPrint;
    doPrint(myPrint, "hello test3");
}

int main(){
    test1();
    test2();
    test3();

    return 0;
}