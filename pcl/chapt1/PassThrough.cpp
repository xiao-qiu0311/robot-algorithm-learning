#include <iostream>
#include "pcl/point_types.h"
#include "pcl/filters/passthrough.h"

int main(){
    // 创建两个点云的智能指针
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

    // 创建点云数据
    cloud->width = 10;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);

    for(auto& point : *cloud){
        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
        point.z = 1024 * rand() / (RAND_MAX + 1.0f);
    }

    std::cout << "Cloud before filtering: " << std::endl;
    for(auto& point : *cloud){
        std::cout << "  " << point.x << " "
                  << " " << point.y
                  << " " << point.z
                  << std::endl;
    }

    // 创建滤波器
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud(cloud);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(0.0, 1.0);
    // pass.setNegative(true);
    pass.filter(*cloud_filtered);

    std::cout << "Cloud after filtering: " << std::endl;
    for(auto& point : *cloud_filtered){
        std::cout << "  " << point.x << " "
                  << " " << point.y
                  << " " << point.z
                  << std::endl;
    }

    return 0;

}