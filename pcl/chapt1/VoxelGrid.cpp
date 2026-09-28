#include <iostream>
#include "pcl/io/pcd_io.h"
#include "pcl/point_types.h"
#include "pcl/filters/voxel_grid.h"

int main(){
    // 创建智能指针
    pcl::PCLPointCloud2::Ptr cloud(new pcl::PCLPointCloud2());
    pcl::PCLPointCloud2::Ptr cloud_filtered(new pcl::PCLPointCloud2());

    // 从文件加载点云
    pcl::PCDReader reader;
    try{
        reader.read("/home/qiu/Desktop/robot-algorithm-learning/pcl/chapt1/table_scene_lms400.pcd", *cloud);
    } catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    std::cout << "PointCloud before filtering: " << cloud->width * cloud->height 
              << " data points(" << pcl::getFieldsList(*cloud) << ")" << std::endl;

    // 创建滤波器
    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud(cloud);
    sor.setLeafSize(0.01f, 0.01f, 0.01f);
    sor.filter(*cloud_filtered);

    std::cout << "PointCloud before filtering: " << cloud_filtered->width * cloud_filtered->height 
              << " data points(" << pcl::getFieldsList(*cloud_filtered) << ")" << std::endl;

    pcl::PCDWriter writer;
    writer.write("/home/qiu/Desktop/robot-algorithm-learning/pcl/chapt1/table_scene_lms400_downsampled.pcd", *cloud_filtered,
                Eigen::Vector4f::Zero(), Eigen::Quaternionf::Identity(), false);

    return 0;
}