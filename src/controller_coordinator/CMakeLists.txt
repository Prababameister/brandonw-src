cmake_minimum_required(VERSION 3.0.2)
project(controller_coordinator)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

add_service_files(
  FILES
  AddController.srv
  RemoveController.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

include_directories(
# include
# ${catkin_INCLUDE_DIRS}
)

catkin_package()
