import launch
import launch_ros

# 函数名固定
def generate_launch_description():
    # 声明一个launch参数
    action_declare_arg_background_g = launch.actions.DeclareLaunchArgument(
        'launch_arg_g',default_value="150" 
    )
    # 将参数手动传递给某个节点

    """用于产生launch描述"""
    action_node_turtlesim_node = launch_ros.actions.Node(
        package='turtlesim',                # 功能包名
        executable='turtlesim_node',        # 可執行文件名
        parameters=[{'background_g':launch.substitutions.LaunchConfiguration
                     ('launch_arg_g',default="150")}], # 获取参数
        output='screen'                     # 日志、输出目的地
    )
    action_node_partol_client = launch_ros.actions.Node(
        package='demo_cpp_service',         # 功能包名
        executable='partol_client',         # 可執行文件名
        output='log'                        # 日志、输出目的地
    )
    action_node_turtle_control = launch_ros.actions.Node(
        package='demo_cpp_service',         # 功能包名
        executable='turtle_control',        # 可執行文件名
        output='both'                       # 日志、输出目的地
    )

    # 返回值也固定，用于产生节点描述
    return launch.LaunchDescription([
        # action 动作
        action_declare_arg_background_g,
        action_node_turtlesim_node,
        action_node_partol_client,
        action_node_turtle_control,
    ])
