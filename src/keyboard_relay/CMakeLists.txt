cmake_minimum_required(VERSION 3.0.2)
project(keyboard_relay)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package()

include_directories( include ${catkin_INCLUDE_DIRS} )

catkin_install_python(
  PROGRAMS scripts/simple_keyboard_input.py
           scripts/keyboard_input_relay.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
