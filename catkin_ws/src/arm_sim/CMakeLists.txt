cmake_minimum_required(VERSION 3.0.2)
project(arm_sim)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  urdf
  controller_manager
  joint_state_controller
  robot_state_controller
)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})
