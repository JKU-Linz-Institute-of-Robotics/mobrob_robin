cmake_minimum_required(VERSION 2.8.3)
project(mobrob_robin_control)

find_package(catkin REQUIRED
	roscpp
	tf
	ros_common_robin_tools
)

catkin_package(
	#INCLUDE_DIRS include
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(mobrob_robin_cmd_vel_controller src/mobrob_robin_cmd_vel_controller.cpp)
target_link_libraries(mobrob_robin_cmd_vel_controller ${catkin_LIBRARIES})
