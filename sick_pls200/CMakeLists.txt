cmake_minimum_required(VERSION 2.8.3)
project(sick_pls200)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

add_executable(pls200 src/pls200.cpp)
target_link_libraries(pls200 ${catkin_LIBRARIES})



