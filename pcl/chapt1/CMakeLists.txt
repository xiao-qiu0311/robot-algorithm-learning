cmake_minimum_required(VERSION 3.10)

project(KdTree&OcTree)

find_package(PCL 1.12 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})

add_definitions(${PCL_DEFINITIONS})

add_executable(kdtree kd_tree.cpp)

target_link_libraries(kdtree ${PCL_LIBRARIES})
