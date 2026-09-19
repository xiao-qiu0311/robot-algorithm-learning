import rclpy
from rclpy.node import Node
from face_interfaces.srv import FaceDetector
import face_recognition
import cv2
from ament_index_python.packages import get_package_share_directory # 获取功能包sharea目录绝对路径
import os
from cv_bridge import CvBridge
import time
from rcl_interfaces.srv import SetParameters
from rcl_interfaces.msg import Parameter, ParameterValue, ParameterType

class FaceDetectClientNode(Node):
    def __init__(self):
        super().__init__('face_detect_client_node')
        self.default_image_path = os.path.join(get_package_share_directory('demo_python_service'), 'resource/test.jpg')
        self.bridge = CvBridge()
        self.get_logger().info("人脸检测客户端启动")
        self.client_ = self.create_client(FaceDetector, 'face_detect')
        self.img = cv2.imread(self.default_image_path)

    def call_set_parameters(self, parameters):
        """
        调用服务，修改参数值
        """
        # 1、创建客户端，等待服务段上线
        update_param_client = self.create_client(SetParameters, 'face_detect_node/set_parameters')
        while update_param_client.wait_for_service(timeout_sec=1.0) is False:
            self.get_logger().info('等待参数更新服务端上线...')
        # 2、创建request
        request = SetParameters.Request()
        request.parameters = parameters
        # 3、调用服务端更新参数
        future = update_param_client.call_async(request)
        rclpy.spin_until_future_complete(self, future) # 等待服务端返回响应
        response = future.result()
        return response
    
    def update_detect_model(self, model='hog'):
        """
        根据传入的model，构造Parameters，然后调用call_set_parameters更新服务端参数
        """
        # 1、创建参数对象
        param = Parameter()
        param.name = 'model'
        # 2、创建参数值对象
        param_value = ParameterValue()
        param_value.type = ParameterType.PARAMETER_STRING
        param_value.string_value = model
        # 3、封装参数
        param.value = param_value
        # 4、请求更新参数
        response = self.call_set_parameters([param])
        for result in response.results:
            if result.successful:
                self.get_logger().info(f"设置参数结果:{result.successful}{result.reason}")

    def send_request(self):
        # 1、判断服务端是否在线
        while self.client_.wait_for_service(timeout_sec=1.0) is False:
            self.get_logger().info("等待服务端上线...")
        # 2、构造request
        request = FaceDetector.Request()
        request.image = self.bridge.cv2_to_imgmsg(self.img)
        # 3、发送请求 等待处理
        future = self.client_.call_async(request) # 异步获取结果 返回future 当前future未包含相应结果 需要等待服务端处理完成将结果放到future
        # while not future.done():
        #     time.sleep() # 休眠当前线程 等待服务完成 造成当前线程无法继续接受来自服务端的返回 导致持续无法完成future.done()返回True
        # rclpy.spin_until_future_complete(self, future) # 等待服务端返回响应
        def result_callback(result_future):
            response = future.result() # 使用多线程时可以这样写
            self.get_logger().info(f"接收到响应，共有{response.number}张人脸，耗时{response.use_time}s")
            self.show_response(response)

        future.add_done_callback(result_callback)

    def show_response(self, response):
        for i in range(response.number):
            top = response.top[i]
            bottom = response.bottom[i]
            right = response.right[i]
            left = response.left[i]
            cv2.rectangle(self.img, (left, top), (right, bottom), (255, 0, 0), 4)
        cv2.imshow("Face Detect Result", self.img)
        # cv2.waitKey(0)  # 也是阻塞的 会导致spin无法正常运行

def main():
    rclpy.init()
    node = FaceDetectClientNode()
    node.update_detect_model('hog')
    node.send_request()
    node.update_detect_model('cnn')
    rclpy.spin(node)
    rclpy.shutdown()
