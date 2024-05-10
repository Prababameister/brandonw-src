cmake_minimum_required(VERSION 3.0.2)
project(arm_gamepad_controller)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

add_message_files(
  FILES
  Gamepad.msg
)

generate_messages (
  DEPENDENCIES
  std_msgs
)

include_directories(include ${catkin_INCLUDE_DIRS})

catkin_install_python(PROGRAMS scripts/gamepad_controller.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

catkin_package()
