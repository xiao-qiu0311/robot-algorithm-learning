cmake_minimum_required(VERSION 3.10)
project(linear_angebra)

find_package(Eigen3 REQUIRED)

add_executable(matrix_multi matrix_multi.cpp)
add_executable(power_of_matrix power_of_matrix.cpp)
add_executable(matrix_transpose matrix_transpose.cpp)

target_link_libraries(matrix_multi PRIVATE Eigen3::Eigen)
target_link_libraries(power_of_matrix PRIVATE Eigen3::Eigen)
target_link_libraries(matrix_transpose PRIVATE Eigen3::Eigen)