cmake_minimum_required(VERSION 2.8.3)
project(spline_test)

find_package(catkin REQUIRED COMPONENTS
  ros_common_robin_bst
  roscpp
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(spline_test src/spline_test.cpp)
target_link_libraries(spline_test ${catkin_LIBRARIES})
