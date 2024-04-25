cmake_minimum_required(VERSION 3.0.2)
project(arm_keyboard_controller)

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

catkin_install_python(PROGRAMS scripts/keyboard_controller.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
