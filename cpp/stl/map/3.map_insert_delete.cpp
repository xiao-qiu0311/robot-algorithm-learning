// -------- map插入和删除 --------
/*
函数原型：
- insert(elem);
- clear();
- erase(pos);       // 删除pos迭代器所值的元素，返回下一个元素的迭代器
- erase(beg, end);
- erase(key);       // 删除值为key的元素
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

void test(){
    std::map<int, int> m;
    // 插入
    // 第一种
    m.insert(std::pair<int, int>(1, 10));

    // 第二种
    m.insert(std::make_pair(2, 20)); // 直接写入键和值

    // 第三种
    m.insert(std::map<int, int>::value_type(3, 30)); // 较麻烦

    // 第四中
    m[4] = 40;  // []中的是键 后面赋值 (不建议使用)
    // 一般使用[]访问value
    // cout << m[5] << endl;  --> 当键不存在会自动创建键对应的值且赋为0

    printMap(m);

    // 删除
    m.erase(m.begin());
    printMap(m);

    m.erase(3); // 传入key值
    // 若输入的key不存在 不会进行删除也不报错
    printMap(m);

    m.erase(m.begin(), m.end()); // 等价于清空
    printMap(m);

    m.clear();
    printMap(m);

}

int main(){
    test();

    return 0;
}