cmake_minimum_required(VERSION 2.8.3)
project(mobrob_robin_driver)

find_package(catkin REQUIRED
	roscpp
	tf
	controller_manager
	hardware_interface
)

catkin_package(
	
)

add_executable(mobrob_odometry_publisher_simulation_only src/mobrob_odometry_publisher_simulation_only.cpp)
target_link_libraries(mobrob_odometry_publisher_simulation_only ${catkin_LIBRARIES})

add_executable(mobrob_base_interface src/mobrob_base_interface.cpp)
target_link_libraries(mobrob_base_interface ${catkin_LIBRARIES})
