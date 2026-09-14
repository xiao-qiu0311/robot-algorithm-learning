import face_recognition
import cv2
from ament_index_python.packages import get_package_share_directory # 获取功能包sharea目录绝对路径
import os

def main():
    # get real image path
    default_image_path = os.path.join(get_package_share_directory('demo_python_service'), 'resource/default.jpg')
    print(f'图片真实路径:{default_image_path}')
    
    # load image by cv2
    image = cv2.imread(default_image_path)
    
    # detect face
    face_locations = face_recognition.face_locations(image, number_of_times_to_upsample=1, model='hog')
   
    # draw face rectancle
    for top, right, bottom, left in face_locations:
        cv2.rectangle(image, (left, top), (right, bottom), (255, 0, 0), 4)
    
    # show result
    cv2.imshow('Face Detecte Result', image)
    cv2.waitKey(0)