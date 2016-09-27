cmake_minimum_required(VERSION 2.8.3)
project(mobrob_robin_rqt)


find_package(catkin REQUIRED COMPONENTS)


catkin_package()
catkin_python_setup()


install(FILES plugin.xml
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(DIRECTORY resource
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(PROGRAMS scripts/mobrob_robin_rqt
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


