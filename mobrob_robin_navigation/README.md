This package includes the config, map and launch files for the move base navigation of the Robot.

Currently the package uses AMCL for localization and the TEB local planner for path planning.
There are two different maps used, the amcl_fullMap only includes walls an obstacles visible to the laser scanner.
The fullMap also includes tables and other objects the path planner should avoid.
