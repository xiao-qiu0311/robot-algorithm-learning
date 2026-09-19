// -------- 方阵的幂 --------
/*
用Eigen::MatrixXd A(n,n); 定义方阵
必须是方阵才可求幂
*/

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <unsupported/Eigen/MatrixFunctions>

int main(){
    Eigen::MatrixXd A(2,2);
    A << 1, 1, 0, 1;
    Eigen::MatrixXd B(2,2);
    B = A.pow(10);

    std::cout << " B = " << std::endl;
    std::cout << B << std::endl;

    /*
    公式：
        前提：A，B可交换
        A^2-B^2 = (A+B)(A-B) = (A-B)(A+B)
        (A+B)^2 = A^2+2AB+B^2
        (A-B)^2 = A^2=2AB+B^2
        A^3-B^3 = (A-B)(A^2+AB+B^2)
        A^3+B^3 = (A+B)(A^2-AB+B^2)
        (AB)^k = A^k * B^k
    */

    return 0;
}