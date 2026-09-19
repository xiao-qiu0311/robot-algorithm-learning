#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

int main(){
    MatrixXd A(3,3);
    A << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    cout << "A = " << endl;
    cout << A << endl;
    cout << endl;
    MatrixXd A_t(3,3);
    A_t = A.transpose();
    cout << "A^T = " << endl;
    cout << A_t << endl;

    return 0;
}