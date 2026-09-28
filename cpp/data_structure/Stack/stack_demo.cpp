#include <iostream>
#include <string>

// ---------- 数组实现的栈（LIFO） ----------
class Stack {
public:
    Stack(int cap = 16) : cap_(cap), top_(-1) {
        data_ = new int[cap];
    }
    ~Stack() { delete[] data_; }

    void push(int val) {
        if (top_ == cap_ - 1) {
            // 简单扩容：不处理也够用，这里直接拒绝
            std::cout << "stack overflow\n";
            return;
        }
        data_[++top_] = val;
    }

    bool pop(int &out) {
        if (isEmpty()) return false;
        out = data_[top_--];
        return true;
    }

    bool peek(int &out) const {
        if (isEmpty()) return false;
        out = data_[top_];
        return true;
    }

    bool isEmpty() const { return top_ == -1; }

private:
    int *data_;
    int cap_;
    int top_;
};

// ---------- 数组实现的队列（FIFO，环状） ----------
class Queue {
public:
    Queue(int cap = 16) : cap_(cap), head_(0), tail_(0), size_(0) {
        data_ = new int[cap];
    }
    ~Queue() { delete[] data_; }

    void enqueue(int val) {
        if (size_ == cap_) {
            std::cout << "queue full\n";
            return;
        }
        data_[tail_] = val;
        tail_ = (tail_ + 1) % cap_;
        ++size_;
    }

    bool dequeue(int &out) {
        if (isEmpty()) return false;
        out = data_[head_];
        head_ = (head_ + 1) % cap_;
        --size_;
        return true;
    }

    bool isEmpty() const { return size_ == 0; }

private:
    int *data_;
    int cap_;
    int head_;
    int tail_;
    int size_;
};

// ---------- 括号匹配：用栈检查 () [] {} 是否配对 ----------
bool isMatch(char left, char right) {
    return (left == '(' && right == ')') ||
           (left == '[' && right == ']') ||
           (left == '{' && right == '}');
}

bool checkBrackets(const std::string &s) {
    Stack st(s.size());
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            int top;
            if (!st.peek(top)) {
                std::cout << "  [多余右括号]: " << c << "\n";
                return false;
            }
            if (!isMatch((char)top, c)) {
                std::cout << "  [不匹配]: " << (char)top << " vs " << c << "\n";
                return false;
            }
            st.pop(top);
        }
    }
    if (!st.isEmpty()) {
        std::cout << "  [左括号未闭合]\n";
        return false;
    }
    return true;
}

int main() {
    // 栈 demo
    Stack st;
    st.push(10);
    st.push(20);
    st.push(30);
    int v;
    while (st.pop(v)) {
        std::cout << "pop: " << v << std::endl;  // 30 20 10（后进先出）
    }

    // 队列 demo
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    while (q.dequeue(v)) {
        std::cout << "dequeue: " << v << std::endl;  // 1 2 3（先进先出）
    }

    // 括号匹配 demo
    std::string tests[] = {
        "{[()]}",    // 合法
        "{[(])}",    // 非法：不匹配
        "((()))",    // 合法
        "([{",       // 非法：未闭合
        "(]",        // 非法：不匹配
        ")",         // 非法：多余右括号
    };
    for (auto &t : tests) {
        std::cout << "check: " << t << " -> " << (checkBrackets(t) ? "合法" : "非法") << std::endl;
    }

    return 0;
}
