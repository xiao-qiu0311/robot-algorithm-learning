import rclpy
from rclpy.node import Node
from face_interfaces.srv import FaceDetector
import face_recognition
import cv2
from ament_index_python.packages import get_package_share_directory # 获取功能包sharea目录绝对路径
import os
from cv_bridge import CvBridge
import time
from rcl_interfaces.msg import SetParametersResult

class FaceDetectNode(Node):
    def __init__(self):
        super().__init__('face_detect_node')
        self.service_ = self.create_service(FaceDetector, 'face_detect', self.detect_face_callback)
        self.default_image_path = os.path.join(get_package_share_directory('demo_python_service'), 'resource/default.jpg')
        self.bridge = CvBridge()
        # 声明number_of_times_to_upsample model
        self.declare_parameter('number_of_times_to_upsample', 1)
        self.declare_parameter('model', 'hog')
        # 获取参数
        self.number_of_times_to_sample = self.get_parameter('number_of_times_to_upsample').value
        self.model = self.get_parameter('model').value
        self.get_logger().info("人脸检测服务启动")
        self.add_on_set_parameters_callback(self.parameters_callback)

    def parameters_callback(self, parameters):
        for parameter in parameters:
            self.get_logger().info(f"{parameter.name}->{parameter.value}")
            if parameter.name == 'number_of_times_to_sample':
                self.number_of_times_to_sample = parameter.value
            if parameter.name == 'model':
                self.model = parameter.value
        return SetParametersResult(successful=True)

    def detect_face_callback(self, request, response):
        if request.image.data:
            cv_image = self.bridge.imgmsg_to_cv2(request.image)
        else:
            cv_image = cv2.imread(self.default_image_path)
            self.get_logger().info("传入图像为空，使用默认图像进行识别")
            # 此时cv_image是opencv格式
        # 统计耗时
        start_time = time.time()
        self.get_logger().info("加载完成，图像开始识别...")
        # detect face
        face_locations = face_recognition.face_locations(cv_image, 
                                                         number_of_times_to_upsample=self.number_of_times_to_sample, 
                                                         model=self.model)
        response.use_time = time.time() - start_time
        response.number = len(face_locations)
        for top, right, bottom, left in face_locations:
            response.top.append(top)
            response.right.append(right)
            response.bottom.append(bottom)
            response.left.append(left)
        self.get_logger().info(f"检测完成，耗时:{response.use_time}")

        return response # 必须返回response

def main():
    rclpy.init()
    node = FaceDetectNode()
    rclpy.spin(node)
    rclpy.shutdown()