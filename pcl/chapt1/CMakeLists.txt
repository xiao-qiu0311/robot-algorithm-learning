cmake_minimum_required(VERSION 3.10)

project(KdTree&OcTree)

find_package(PCL 1.12 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})

add_definitions(${PCL_DEFINITIONS})

add_executable(points_writer points_writer.cpp)
add_executable(points_loader points_loader.cpp)
add_executable(PassThrough PassThrough.cpp)
add_executable(VoxelGrid VoxelGrid.cpp)

target_link_libraries(points_writer ${PCL_LIBRARIES})
target_link_libraries(points_loader ${PCL_LIBRARIES})
target_link_libraries(PassThrough ${PCL_LIBRARIES})
target_link_libraries(VoxelGrid ${PCL_LIBRARIES})
