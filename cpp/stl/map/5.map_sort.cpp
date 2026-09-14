// -------- map 排序 --------
/*
默认会升序排序

主要技术点：
- 利用仿函数 可以改变排序规则
*/

#include <iostream>
#include <map>
#include <utility>

class MyCompare{
public:
    bool operator()(int v1, int v2) const { return v1 > v2; }
};

void test(){
    std::map<int, int, MyCompare> m;
    m.insert(std::make_pair(1, 10));
    m.insert(std::make_pair(2, 20));
    m.insert(std::make_pair(3, 30));
    m.insert(std::make_pair(4, 40));
    m.insert(std::make_pair(5, 50));
    m.insert(std::make_pair(6, 60));

    for(std::map<int, int, MyCompare>::iterator it = m.begin(); it != m.end(); it++){
        std::cout << "key = " << it->first << " value = " << it->second << std::endl;
    }

}

int main(){
    test();
    
    return 0;
}