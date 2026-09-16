#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/executors.hpp"
#include "rclcpp/node.hpp"
#include "rclcpp/publisher.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/service.hpp"
#include "rclcpp/subscription.hpp"
#include "rclcpp/utilities.hpp"
#include "face_interfaces/srv/partol.hpp"
#include "turtlesim/msg/pose.hpp"
#include <chrono>
#include <cmath>
#include <cstddef>
#include <functional>
#include <memory>
#include <rclcpp/client.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/timer.hpp>

using namespace std::chrono_literals;  // 可以使用 10s, 100ms等
using Partol = face_interfaces::srv::Partol;

class PartolClient : public rclcpp::Node{
public:
    PartolClient() : Node("partol_client"){
        srand(time(NULL)); // 初始化随机数种子
        partol_client_ = this->create_client<Partol>("partol");
        timer_ = this->create_wall_timer(5s, [&]()->void{
            // 1、检测服务端是否上线（wait_for_service 返回 true 表示服务可用）
            while (!this->partol_client_->wait_for_service(1s)) {
                if(!rclcpp::ok()){
                    RCLCPP_ERROR(this->get_logger(), "服务上线过程中rclcpp挂了");
                    return;
                }
                RCLCPP_INFO(this->get_logger(), "等待服务上线...");
            }
            // 2、构造请求的对象（服务端只接受 0 < 坐标 < 12，这里取 1~11）
            auto request = std::make_shared<Partol::Request>();
            request->target_x = rand() % 11 + 1;
            request->target_y = rand() % 11 + 1;
            RCLCPP_INFO(this->get_logger(), "准备好目标点%.1f, %.1f",
                        request->target_x, request->target_y);
            // 3、发送请求
            this->partol_client_->async_send_request(request, 
            [&](rclcpp::Client<Partol>::SharedFuture result_future)->void{
                auto response = result_future.get();
                if(response->result == Partol::Response::SUCCESS) RCLCPP_INFO(this->get_logger(), "请求巡逻目标点成功");
                if(response->result == Partol::Response::FAIL)    RCLCPP_INFO(this->get_logger(), "请求巡逻目标点失败");
            });  // 异步发送请求SUCCESS
        });
    }

private:
    

private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Client<Partol>::SharedPtr partol_client_;

};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PartolClient>();
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}