#include "pcl/io/pcd_io.h"
#include <iostream>
#include "pcl/point_types.h"

int main(){
    pcl::PointCloud<pcl::PointXYZ> cloud;
    cloud.width = 5;
    cloud.height = 1;
    cloud.is_dense = false;
    cloud.resize(cloud.height * cloud.width);

    for(auto& point : cloud){
        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
        point.z = 1024 * rand() / (RAND_MAX + 1.0f);
    }

    // 将点云写入pcd文件
    // 写入的文件会生成在build文件夹下
    pcl::io::savePCDFile("test_pcd.pcd", cloud);
    std::cout << "Saved " << cloud.size() << " data points to test_pcd.pcd" << std::endl;

    for(const auto& point : cloud)
        std::cout << "  " << point.x << " " << point.y << " " << point.z << std::endl;

    return 0;
}