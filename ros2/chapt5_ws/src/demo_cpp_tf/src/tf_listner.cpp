#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"             // 提供消息接口
#include "tf2/LinearMath/Quaternion.hpp" // 提供四元数
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp" // 消息类型转换函数
#include "tf2_ros/transform_listener.hpp" // 坐标监听器
#include "tf2_ros/buffer.hpp"             // 提供buffer
#include "tf2/utils.hpp"                  // 提供四元数相关方法
#include <chrono>

using namespace std::chrono_literals;

class TFListener : public rclcpp::Node{
public:
    TFListener() : Node("tf_listener"){
        buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        this->listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_, this);
        timer_ = this->create_wall_timer(5s, std::bind(&TFListener::getTransform, this));
    }
    
    void getTransform(){
        // 到buffer查询坐标关系
        // 查到返回关系 未查到抛异常
        // 捕获异常
        try{
            // 查询坐标关系
            const auto transform = buffer_->lookupTransform(
                "base_link", "target_point", get_clock()->now(), rclcpp::Duration::from_seconds(1.0f)
            );
            // 获取查询结果
            auto translation = transform.transform.translation;
            auto rotation = transform.transform.rotation;
            double y, p, r;
            // 四元数转欧拉角
            tf2::getEulerYPR(rotation, y, p, r);
            RCLCPP_INFO(this->get_logger(), "平移:%f,%f,%f", translation.x, translation.y, translation.z);
            RCLCPP_INFO(this->get_logger(), "旋转:%f,%f,%f,", y, p, r);

        } catch(const std::exception& e){
            RCLCPP_WARN(this->get_logger(), "%s", e.what());
        }
    }

private:
    std::shared_ptr<tf2_ros::TransformListener> listener_; // 广播器的共享指针
    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<tf2_ros::Buffer> buffer_;
    
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TFListener>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}