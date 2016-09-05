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

#add_executable(pls200_driver src/pls200_driver.cpp)
#target_link_libraries(pls200_driver ${catkin_LIBRARIES})

add_executable(pls_node src/pls_node.cpp src/pls200_driver.cpp)
target_link_libraries(pls_node ${catkin_LIBRARIES})



