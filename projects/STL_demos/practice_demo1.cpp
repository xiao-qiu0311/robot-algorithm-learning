// -------- 员工分组 --------

/*
案例描述:
    - 公司招聘了10个员工（ABCDEFG） 10名员工进入公司后需要指派员工在部门工作
    - 员工信息：姓名 工资组成； 部门分为：策划、美术、研发
    - 随即给10名员工分配部门和工资
    - 通过multimap进行信息的插入 key(部门编号)value(员工)
    - 分部门显示员工信息

实现步骤：
    - 创建10名员工 放到vector中
    - 遍历vector取出每个员工进行随机分组
    - 分组后将员工部门编号作为key 具体员工作为value 放入multimap中
    - 分部门显示员工信息
*/

#include <cerrno>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <string>
#include <ctime>

#define CEHUA 0
#define MEISHU 1
#define YANFA 2

class Worker{
public:
    std::string m_Name;
    int m_Salary;

};

void create_worker(std::vector<Worker>& v){
    std::string nameSeed = "ABCDEFGHIJ";
    for(int i = 0; i < 10; i++){
        Worker worker;
        worker.m_Name = "员工";
        worker.m_Name += nameSeed[i];

        worker.m_Salary = rand() % 10000 + 10000; // 10000 ~ 19999

        v.push_back(worker);
    }
}

void setGroup(std::vector<Worker>& v, std::multimap<int, Worker>& m){
    for(std::vector<Worker>::iterator it = v.begin(); it != v.end(); it++){
        // 产生随机部门编号
        int deptId = rand() % 3;
        // 将员工插入分组
        m.insert(std::make_pair(deptId, *it));
    }
}

void showWorkerByGroup(std::multimap<int, Worker>& m){
    // 0 A B C 1 D E F 2 G H I J
    std::cout << "策划部门: " << std::endl;
    std::multimap<int, Worker>::iterator pos = m.find(CEHUA);
    int count = m.count(CEHUA); // 统计人数
    int index = 0;
    for(; pos != m.end() && index < count; pos ++, index ++){
        std::cout << "姓名: " << pos->second.m_Name << " 工资: " << pos->second.m_Salary << std::endl;
    }

    std::cout << "----------------------" << std::endl;
    std::cout << "美术部门: " << std::endl;
    pos = m.find(MEISHU);
    count = m.count(MEISHU); // 统计人数
    index = 0;
    for(; pos != m.end() && index < count; pos ++, index ++){
        std::cout << "姓名: " << pos->second.m_Name << " 工资: " << pos->second.m_Salary << std::endl;
    }

    std::cout << "----------------------" << std::endl;
    std::cout << "研发部门: " << std::endl;
    pos = m.find(YANFA);
    count = m.count(YANFA); // 统计人数
    index = 0;
    for(; pos != m.end() && index < count; pos ++, index ++){
        std::cout << "姓名: " << pos->second.m_Name << " 工资: " << pos->second.m_Salary << std::endl;
    }
}

int main(){
    // 创建员工
    std::vector<Worker> vWorker;
    create_worker(vWorker);

    // // Debug
    // for(std::vector<Worker>::iterator it = v.begin(); it != v.end(); it++){
    //     std::cout << "姓名: " << it->m_Name << " 工资: " << it->m_Salary << std::endl;
    // }

    // 员工分组
    std::multimap<int, Worker> mWorker;    
    setGroup(vWorker, mWorker);

    // 分组显示员工
    showWorkerByGroup(mWorker);

    return 0;
}