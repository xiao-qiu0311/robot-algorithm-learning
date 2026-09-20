#include <pcl/point_cloud.h>    // header of point classes defining
#include <pcl/kdtree/kdtree_flann.h>  // header of kdtree classes defining

#include <iostream>
#include <vector>
#include <ctime>

int
main(int argc, char* argv[]){
    srand(time(NULL));  // random number seed
    // build a PointCloud<pcl::PointXYZ>
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>); // a pointer

    // make point clouds randomly
    cloud->width = 1000;        // show the number of point clouds
    cloud->height = 1;          // show that it is disorded point clouds
    cloud->points.resize(cloud->width * cloud->height);

    for(size_t i = 0; i < cloud->points.size(); i++){ // use loop to fill data in pc
        // make float numbers in range 0~1024
        cloud->points[i].x = 1024.0f * rand() / (RAND_MAX + 1.0f);
        cloud->points[i].y = 1024.0f * rand() / (RAND_MAX + 1.0f);
        cloud->points[i].z = 1024.0f * rand() / (RAND_MAX + 1.0f);
    }

    // make object of KdTreeFLANN,and set the pc into input, then build a variable searchPoint as searching point
    pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
    // set searching space
    kdtree.setInputCloud(cloud);
    // build random point and put random number in it
    pcl::PointXYZ searchPoint;
    searchPoint.x = 1024.0f * rand() / (RAND_MAX + 1.0f);
    searchPoint.y = 1024.0f * rand() / (RAND_MAX + 1.0f);
    searchPoint.z = 1024.0f * rand() / (RAND_MAX + 1.0f);

    // K neighbor searches
    // 创建一个整数（设置为10）和两个向量来存储搜索到的K近邻，两个乡两种，一个存储搜索到查寻点近邻的索引，另一个村树近邻点对应距离平方
    int K = 10;
    std::vector<int> pointIdxNKNSearch(K);
    std::vector<float> pointNKNSquaredDistance(K);
    // 打印相关信息
    std::cout << "K neaerest neighbor search at (" << searchPoint.x
        << " " << searchPoint.y
        << " " << searchPoint.z
        << ") with K = " << K << std::endl;
    
    // 执行K近邻搜索
    if(kdtree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0){
        // 打印所有近邻坐标
        for(size_t i = 0; i < pointIdxNKNSearch.size(); ++i){
            std::cout << "    " << cloud->points[pointIdxNKNSearch[i]].x
            << " " << cloud->points[pointIdxNKNSearch[i]].y
            << " " << cloud->points[pointIdxNKNSearch[i]].z
            << "(squared distance: " << pointNKNSquaredDistance[i] << ")" << std::endl;
        }
    }

    /*****************************************************
    下面的代码展示查找到给定的searchPoint的某一半径（随机产生）内所
    有近邻，重新定义两个向量来存储关于近邻的信息
    ******************************************************/
    // 半径R内近邻搜索方法

    std::vector<int> pointIdxRadiusSearch;
    std::vector<float> pointRadiusSquaredDistance;

    float radius = 256.0f * rand() / (RAND_MAX + 1.0f);

    std::cout << "Neighbor within radius search at (" << searchPoint.x
            << " " << searchPoint.y
            << " " << searchPoint.z
            << ") with radius = " << radius << std::endl;

            

    return 0;
}