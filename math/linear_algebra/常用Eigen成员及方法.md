# 常用 Eigen 成员及方法

## 引入头文件

Eigen 是纯头文件库，直接包含即可：

```cpp
#include <Eigen/Dense>        // 常用：矩阵、向量、分解等
// 或按需包含：
#include <Eigen/Core>         // Matrix/Array 基础
#include <Eigen/Geometry>     // 旋转、四元数、变换
#include <Eigen/Sparse>       // 稀疏矩阵
```

编译时需要指定头文件路径：

```bash
g++ main.cpp -I/usr/include/eigen3 -o main
```

若装在自定义路径，把 `-I` 指向 Eigen 的父目录（即 `Eigen/` 所在目录）。用 CMake 时：

```cmake
find_package(Eigen3 REQUIRED)
target_link_libraries(myapp PRIVATE Eigen3::Eigen)
```

---

## 矩阵乘法

```cpp
#include <Eigen/Dense>
using namespace Eigen;

MatrixXd A(2,3), B(3,4);
MatrixXd C = A * B;        // 矩阵乘矩阵

VectorXd v(3);
VectorXd w = A * v;        // 矩阵乘向量

// 逐元素乘（不是矩阵乘法）
MatrixXd D = A.array() * A.array();

// 标量乘
MatrixXd E = 2.0 * A;
```

---

## 定义与初始化

```cpp
MatrixXd m(3,3);                    // 动态 double
MatrixXf mf(3,3);                   // 动态 float
Matrix<int,3,3> mi;                 // 固定 3x3 int
VectorXd v(5);                      // 列向量
RowVectorXd rv(5);                  // 行向量
MatrixXd::Zero(3,3);
MatrixXd::Ones(3,3);
MatrixXd::Identity(3,3);
MatrixXd::Random(3,3);
MatrixXd::Constant(3,3, 1.5);
```

---

## 常用成员方法

```cpp
m.rows(); m.cols(); m.size();
m.resize(2,2);
m.setZero(); m.setOnes(); m.setIdentity(); m.setRandom();
m.transpose(); m.adjoint();          // 转置 / 共轭转置
m.determinant(); m.trace();
m.inverse();                          // 求逆（慎用，建议解方程）
m.norm(); m.squaredNorm(); m.normalize();
m.sum(); m.mean(); m.minCoeff(); m.maxCoeff();
m.cwiseProduct(other);                // 逐元素乘
m.cwiseAbs(); m.cwiseSqrt();
m.block(i,j,p,q);                     // 子块
m.row(i); m.col(j);
m.topRows(n); m.bottomRows(n); m.leftCols(n); m.rightCols(n);
```

---

## 线性代数（需要 `<Eigen/Dense>`）

```cpp
m.lu();                               // LU 分解
m.llt();                              // Cholesky (LL^T)
m.ldlt();                             // LDL^T
m.qr();                               // QR
m.fullPivLu();                        // 全主元 LU
m.jacobiSvd(ComputeThinU|ComputeThinV);// SVD
m.selfadjointView<Lower>().eigenvalues();
m.eigenvalues(); m.eigenvectors();
m.colPivHouseholderQr().rank();
m.norm(); m.blueNorm();
```

---

## 解方程（推荐，优于求逆）

```cpp
VectorXd x = A.colPivHouseholderQr().solve(b);  // 通用
VectorXd x = A.ldlt().solve(b);                 // 对称正定
VectorXd x = A.partialPivLu().solve(b);         // 方阵
```

---

## 数组逐元素运算（`.array()`）

```cpp
A.array() + 1.0;
A.array().sin(); A.array().exp(); A.array().log();
A.array().pow(2.0); A.array().sqrt();
(A.array() < 0.0).select(0.0, A.array());  // 条件选择
```

---

## 几何（`<Eigen/Geometry>`）

```cpp
Quaterniond q; q.setFromTwoVectors(a,b); q.toRotationMatrix();
AngleAxisd aa(M_PI/4, Vector3d::UnitZ());
Isometry3d T = Translation3d(1,2,3) * aa;
```

---

## 注意点

- `auto` 配合表达式模板可能出问题，跨表达式赋值用 `MatrixXd` 显式类型。
- `A*B` 是矩阵乘，`A.cwiseProduct(B)` 或 `A.array()*B.array()` 是逐元素乘。
- 求逆解方程优先用分解 `.solve()`，避免 `.inverse()`。
- 编译需 `-I/usr/include/eigen3`。
