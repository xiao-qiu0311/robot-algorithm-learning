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

#include "rcl_interfaces/msg/parameter.hpp"
#include "rcl_interfaces/msg/parameter_value.hpp"
#include "rcl_interfaces/msg/parameter_type.hpp"
#include "rcl_interfaces/srv/set_parameters.hpp"

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
using SetP = rcl_interfaces::srv::SetParameters;

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

    /*创建客户端发送请求返回结果*/
    SetP::Response::SharedPtr call_set_parameters(const rcl_interfaces::msg::Parameter & param)
    {
        auto param_client = this->create_client<SetP>("/turtle_controller/set_parameters");
        while (!param_client->wait_for_service(1s)) {
            if(!rclcpp::ok()){
                RCLCPP_ERROR(this->get_logger(), "服务上线过程中rclcpp挂了");
                return nullptr;
            }
            RCLCPP_INFO(this->get_logger(), "等待服务上线...");
        }
        // 2、构造请求的对象
        auto request = std::make_shared<SetP::Request>();
        request->parameters.push_back(param);

        // 3、发送请求 同步修改
        auto future = param_client->async_send_request(request);
        rclcpp::spin_until_future_complete(this->get_node_base_interface(), future); // this->get_node_base_interface()返回的节点共享指针
        auto response = future.get();
        return response;
    }

    /*更新参数K*/
    void update_server_param_k(double k){
        // 1、创建参数对象
        auto param = rcl_interfaces::msg:: Parameter();
        param.name = "k";
        // 2、创建参数值
        auto param_value = rcl_interfaces::msg::ParameterValue();
        param_value.type = rcl_interfaces::msg::ParameterType::PARAMETER_DOUBLE;
        param_value.double_value = k;
        param.value = param_value;
        // 3、请求更新参数并处理
        auto response = this->call_set_parameters(param);
        if(response == NULL){
            RCLCPP_INFO(this->get_logger(), "参数更新失败");
            return;
        }
        for(auto result : response->results){
            if(result.successful == false){
                RCLCPP_INFO(this->get_logger(), "参数更新失败，原因：%s", result.reason.c_str());
            } else {
                RCLCPP_INFO(this->get_logger(), "参数更新成功");
            }
        }
    }

private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Client<Partol>::SharedPtr partol_client_;

};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PartolClient>();
    node->update_server_param_k(4.0);   // 外部调用更新
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
