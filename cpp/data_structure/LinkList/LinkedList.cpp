#include <iostream>
#include <stdlib.h>
#include <ctime>

// 单链表只能向后遍历 尾节点地址为nullptr
// 常定义头节点，用指针head指向它，地址为空
struct Node{
    Node(int data=0) : data_(data), next_(nullptr){} // 构造函数
    int data_; // 数据域
    Node *next_; // 指针域
};

class Clink{
public:
    Clink(){
        // 给head初始化指向头节点，不属于有效节点之一
        head_ = new Node();
    }
    ~Clink(){
        // 节点的释放
        // 单链表不连续 不能先释放头节点
        // 遍历每一个节点并释放
        Node *p = head_;
        while(p != nullptr){
            head_ = head_->next_;
            delete p;
            p = head_;
        }

    }

public:
    // 尾插法，顾名思义将数据放到尾部
    void insertTail(int val){
        // 需先找到当前链表的尾节点 => 特征：地址域是空
        // 1、空链表
        // 2、有部分节点
        // 定义指针p指向头节点，判断p指向的next是否为空，不为空则令p = p->next
        Node* p = head_;
        while(p->next_ != nullptr){
            p = p->next_;
        }

        // 后生成新节点
        Node *node = new Node(val);
        // 把新节点挂在尾节点后
        p->next_ = node;
    }

    // 头插法O(1) 将生成的节点插在头节点和第一个节点之间
    void insertHead(int val){
        // 生成新节点
        // 1、新节点地址域存放原先第一个节点的地址
        // 2、头节点地址域存新节点的地址
        // 必须先改新节点的地址域再改头节点地址域
        Node *node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }

    // 节点的按值删除
    void remove(int val){
        // 1、从第一个节点开始遍历搜索data=val的节点
        // 先连接目标节点的前后节点，后删除目标节点，即释放其内存
        // 由于链表内存不一定连续，单链表不能向前，因此使用双指针
        // 定义q指向p前一个节点
        Node* p = head_->next_;
        Node* q = head_;
        while (p != nullptr){
            if(p->data_ == val){
                q->next_ = p->next_;
                Node* tmp = p;
                p = p->next_;
                delete tmp;
            } else {
                q = p;
                p = p->next_;
            }
        }
        
    }

    // 删除多个节点
    void removeAll(int val){
        Node *p = head_->next_;
        Node *q = head_;
        while(p != nullptr){
            if(p->data_ == val){
                // 多一步重置p
                q->next_ = p->next_;
                delete p;
                // 对指针p进行重置
                p = q->next_;
            } else {
                q = p;
                p = p->next_;
            }
        }
    }

    // 搜索节点 list O(n)
    bool find(int val){
        // 定义指针指向第一个节点开始遍历
        Node *p = head_->next_;
        while (p != nullptr)
        {
            if(p->data_ == val){
                return true;
            } else {
                p = p->next_;
            }
        }
        return false;
    }

    // 打印链表
    void show(){
        // 从尾部开始打印
        // 定义指针指向头节点的next
        Node *p = head_->next_;
        while(p != nullptr){
            std::cout << p->data_ << " ";
            p = p->next_;
        }
        std::cout << std::endl;
    }

private:
    Node *head_; // 指向链表的头节点
    Node *tail_; // 指向链表的尾节点

};

int main(){
    Clink link;
    srand(time(0));
    for(int i = 0; i < 10; i++){
        int val = rand() % 100;
        link.insertHead(val);
        std::cout << val << " ";
    }
    std::cout << std::endl;
    link.insertTail(200);
    link.insertTail(200);
    link.show();
    link.removeAll(200);
    // link.remove(200);
    link.show();

    return 0;
}