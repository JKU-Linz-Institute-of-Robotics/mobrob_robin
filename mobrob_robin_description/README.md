# mobrob_robin_description

This package provides the URDF file for the Robots RVIZ / Gazebo Visualization.  
It spawn the complete tf tree for all the Ultrasonic sensors and the laserscanner.

### Meshes:
Includes the differet meshes used in the robot.

### robots:
mobrob_robin_real and mobrob_robin_simulated both call the mobrob.urdf.xacro.  
Only a bool variable is set to 1 in mobrob_robin_simulated file.  
These variable is used to add controllers for the wheels for gazebo simulation.  
mobrob.urdf.xacro calls alle the relevant macros from the urdf files to build the urdf tree for the robot.

### urdf:
These files describe the different parts of the robots, all dimensions can be set in the properties.xacro.
