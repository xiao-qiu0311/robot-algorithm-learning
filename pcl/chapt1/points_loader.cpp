#include <iostream>
#include <string>
#include "pcl/io/pcd_io.h"
#include "pcl/point_types.h"

int main(int argc, char* argv[]){
    if(argc < 2){std::cerr << "plz input a pcd file path" << std::endl;  return -1;}
    std::string pcd_path = argv[1];
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    if(pcl::io::loadPCDFile(pcd_path, *cloud) == -1){
        printf("Couldn't read file %s", pcd_path.c_str());
        return -1;
    }

    std::cout << "Loaded "
              << cloud->width * cloud->height
              << " data points from " << pcd_path << "with the following fields:"
              << std::endl;

    for(const auto& point : *cloud){
        std::cout << "  " << point.x
                  << " " << point.y
                  << " " << point.z
                  << std::endl;
    }

    return 0;
}