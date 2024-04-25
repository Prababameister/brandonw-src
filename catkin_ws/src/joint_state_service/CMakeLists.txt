cmake_minimum_required(VERSION 3.0.2)
project(joint_state_service)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

add_service_files(
  FILES
  JointPosition.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

catkin_install_python(PROGRAMS scripts/joint_state_service_server.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
