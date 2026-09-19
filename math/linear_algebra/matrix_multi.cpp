#include <iostream>
#include <Eigen/Core>       // Matrix/Array基础
#include <Eigen/Geometry>   // 旋转、四元数、变换
#include <Eigen/Dense>

int main(){
    Eigen::MatrixXd A(1, 2); // ！！！A(行, 列)！！！
    A << 2.0, 3.0;
    Eigen::MatrixXd B(2, 1);
    B << 4.0, 5.0;
    Eigen::MatrixXd C = A * B;

    std::cout << "A * B = " << C << std::endl;

    return 0;
}