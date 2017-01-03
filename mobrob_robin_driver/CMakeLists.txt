cmake_minimum_required(VERSION 2.8.3)
project(mobrob_robin_driver)

find_package(catkin REQUIRED
	roscpp
	tf
	controller_manager
	hardware_interface
	ros_common_robin_tools
)

catkin_package(
	#INCLUDE_DIRS include
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(mobrob_odometry_publisher_simulation_only src/mobrob_odometry_publisher_simulation_only.cpp)
target_link_libraries(mobrob_odometry_publisher_simulation_only ${catkin_LIBRARIES})

add_executable(mobrob_base_interface src/mobrob_base_interface.cpp)
target_link_libraries(mobrob_base_interface ${catkin_LIBRARIES})


add_executable(mobrob_joint_state_publisher src/mobrob_joint_state_publisher.cpp)
target_link_libraries(mobrob_joint_state_publisher ${catkin_LIBRARIES})

add_executable(mobrob_robin_virtual_robot_driver_interface src/mobrob_robin_virtual_robot_driver_interface.cpp)
target_link_libraries(mobrob_robin_virtual_robot_driver_interface ${catkin_LIBRARIES})
