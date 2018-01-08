# mobrob_robin_navigation

This package includes the config, map and launch files for the move base navigation of the Robot.  
Currently the package uses AMCL for localization and the TEB local planner for path planning.  
There are two different maps used, the amcl_fullMap only includes walls an obstacles visible to the laser scanner.  
The fullMap also includes tables and other objects the path planner should avoid.

### config
move_base, global_planner, teb_local_planner, and costmap config files are located here.

### launch
complete_amcl.launch gets called when bringing up the robot launching all necesarry nods.

### map
All know maps are located here.


