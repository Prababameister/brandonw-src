cmake_minimum_required(VERSION 3.0.2)
project(ik_solver)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/find_eigen)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

find_package(Eigen REQUIRED)
include_directories(${Eigen_INCLUDE_DIRS})

include_directories(${catkin_INCLUDE_DIRS})

add_service_files (
  FILES
  IKSolve.srv
)

generate_messages (
  DEPENDENCIES
  std_msgs
)

add_executable(ik_solver src/ik_solver.cc)
target_link_libraries(ik_solver
  ${catkin_LIBRARIES}
  ${Eigen_LIBRARIES}
  ${JSONCPP_LIBRARIES}
)

catkin_package()
