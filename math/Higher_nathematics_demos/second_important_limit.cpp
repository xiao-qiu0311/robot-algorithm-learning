#include <iostream>
#include <cmath>

double compute(int n){
    return std::pow(1.0 + 1.0 / n, n);
}

int main(){
    for(int i = 1; i < 10000; i++){
        std::cout << compute(i) << std::endl;
    }

    return 0;
}
