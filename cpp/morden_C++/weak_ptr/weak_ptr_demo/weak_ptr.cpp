#include <algorithm>
#include <iostream>
#include <memory>
#include "cat.hpp"

using namespace std;

int main(int argc, char* argv[]){
    // weak_ptr can only exist by shared_ptr
    std::shared_ptr<Cat> s_p_c1 = std::make_shared<Cat>();
    std::weak_ptr<Cat> w_p_c1(s_p_c1);

    // use_count()?
    // can be used but count won't +1    

    cout << "w_p_c1: " << w_p_c1.use_count() << endl;
    cout << "s_p_c1: " << s_p_c1.use_count() << endl;
    
    // w_p_c1->cat_info(); // weak_ptr can't use '->'

    // transpose weak_ptr to shared_ptr
    std::shared_ptr<Cat> s_p_c2 = w_p_c1.lock();

    cout << endl;
    cout << "w_p_c1: " << w_p_c1.use_count() << endl;
    cout << "s_p_c1: " << s_p_c1.use_count() << endl;
    cout << "s_p_c2: " << s_p_c2.use_count() << endl;

    // ciclic dependencies problem --- a usual problem
    std::shared_ptr<Cat> c3 = std::make_shared<Cat>("c3");
    std::shared_ptr<Cat> c4 = std::make_shared<Cat>("c4");

    // make c3 & c4 being friends to each other
    c3->set_friend(c4);
    c4->set_friend(c3);
    // to solve this problem, go to change the class of 'friend' into weak_ptr
    // notice: only change the private member
    // because of the loop,c3 & c4 do not be released after the fuc main ends

    cout << "------ after the function main ends,it will use de destructor autoly ------" << endl;
    return 0;
}