cmake_minimum_required(VERSION 3.0.2)
project(keyboard_control)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs genmsg)

generate_messages(DEPENDENCIES std_msgs)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(keypubber src/keypubber.cc)
target_link_libraries(keypubber ${catkin_LIBRARIES})

