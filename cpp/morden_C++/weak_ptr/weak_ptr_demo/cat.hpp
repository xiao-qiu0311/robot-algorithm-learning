#ifndef CAT_HPP
#define CAT_HPP
#include <string>
#include <iostream>
#include <memory>

class Cat{
public:
    Cat(std::string name);
    Cat() = default;
    ~Cat();
    // ->
    void cat_info() const {
        std::cout << "cat info name: " << name << std::endl;
    }
    std::string get_name() const {
        return name;
    }
    void set_cat_name(const std::string &name){
        this->name = name;
    }
    void set_friend(std::shared_ptr<Cat> c){
        m_friend = c;
    }
private:
    std::string name{"Mimi"}; // defualt value
    std::weak_ptr<Cat>  m_friend; // only need to change this

};
#endif
