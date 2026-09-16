#include "geometry_msgs/msg/detail/twist__struct.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/executors.hpp"
#include "rclcpp/node.hpp"
#include "rclcpp/publisher.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/service.hpp"
#include "rclcpp/subscription.hpp"
#include "rclcpp/utilities.hpp"
#include "turtlesim/msg/detail/pose__struct.hpp"
#include "face_interfaces/srv/partol.hpp"
#include "turtlesim/msg/pose.hpp"
#include <cmath>
#include <functional>
#include <memory>

using Partol = face_interfaces::srv::Partol;

class TurtleController : public rclcpp::Node{
public:
    TurtleController() : Node("turtle_controller"){
        velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(
            "/turtle1/cmd_vel", 10);
        pose_subscription_ = this->create_subscription<turtlesim::msg::Pose>(
            "turtle1/pose", 10,
            std::bind(&TurtleController::on_pose_received_, this, std::placeholders::_1));
        partol_service_ = this->create_service<Partol>("partol",
            [&](const Partol::Request::SharedPtr request,
                Partol::Response::SharedPtr response)->void{
            if(
                (0.0f < request->target_x && request->target_x < 12.0f) &&
                (0.0f < request->target_y && request->target_y < 12.0f)
            ){
                this->target_x_ = request->target_x;
                this->target_y_ = request->target_y;
                response->result = Partol::Response::SUCCESS;
            } else {
                response->result = Partol::Response::FAIL;
            }
        });
    }

private:
    void on_pose_received_(const turtlesim::msg::Pose::SharedPtr pose){
        auto message = geometry_msgs::msg::Twist();
        // 1、记录当前位置
        double current_x = pose->x;
        double current_y = pose->y;
        RCLCPP_INFO(this->get_logger(), "当前位置:(x=%f,y=%f)", current_x, current_y);

        // 到边界自动掉头：把目标反射到对侧，实现来回巡逻
        if(current_x < boundary_margin_){
            target_x_ = kWorldSize - boundary_margin_;
        } else if(current_x > kWorldSize - boundary_margin_){
            target_x_ = boundary_margin_;
        }
        if(current_y < boundary_margin_){
            target_y_ = kWorldSize - boundary_margin_;
        } else if(current_y > kWorldSize - boundary_margin_){
            target_y_ = boundary_margin_;
        }

        // 2、计算距离目标的距离 与当前海龟朝向的角度差
        double distance =
            std::sqrt((target_x_ - current_x) * (target_x_ - current_x) +
                      (target_y_ - current_y) * (target_y_ - current_y));
        double angle =
            std::atan2(target_y_ - current_y, target_x_ - current_x) - pose->theta;
        // 归一化到 [-π, π]，避免绕远路
        while (angle > M_PI) angle -= 2.0 * M_PI;
        while (angle < -M_PI) angle += 2.0 * M_PI;

        // 3、控制策略：距离大于0.1继续运动 角度差大于0.2则原地旋转，否则直行
        if(distance > 0.1){
            if(fabs(angle) > 0.2){
                // 保留符号：目标在右侧时向负方向（顺时针）旋转
                message.angular.z = angle;
            } else {
            // 通过比例控制器计算输出速度
            message.linear.x = k_ * distance;
            }
        }

        // 4、限制最大值并发布消息
        if(message.linear.x > max_speed_){
            message.linear.x = max_speed_;
        }
        velocity_publisher_->publish(message);
    }

private:
    rclcpp::Service<Partol>::SharedPtr partol_service_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
    static constexpr double kWorldSize{11.0};  // turtlesim 坐标范围 0~11
    double boundary_margin_{1.5};              // 距边界小于该值即掉头
    double target_x_{1.0};    // 目标位置X，默认值1.0
    double target_y_{1.0};    // 目标位置Y，默认值1.0
    double k_{1.0};           // 比例系数，控制输出=误差*比例系数
    double max_speed_{3.0};   // 最大线速度，默认3.0

};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleController>();
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}