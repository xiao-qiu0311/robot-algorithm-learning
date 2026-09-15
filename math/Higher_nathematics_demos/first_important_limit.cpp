#include <iostream>
#include <cmath>

double compute(double x){
    return std::sin(x) / x;
}

int main(){
    for(double x = 1.0; x > 1e-8; x /= 2.0){
        std::cout << x << "\t" << compute(x) << std::endl;
    }
    std::cout << "---" << std::endl;
    for(double x = -1.0; x < -1e-8; x /= 2.0){
        std::cout << x << "\t" << compute(x) << std::endl;
    }
    return 0;
}
