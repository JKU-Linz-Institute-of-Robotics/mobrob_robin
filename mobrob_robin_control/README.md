This package includes several launch files for controlling the robot and the high level velocity controller.

launch files:
all_controllers: deprecated and only for the simulation
base_control: simulation controllers
cmd_vel_controller.launch: launches the vel_controller node
joint_states: launches the joint state publisher for the simulation
velocity_smoother: Launches the velocity smoother for joystick inputs.

config files:
base_control: definition of the simulation controllers
joint_states: definition of the joint states
veloctiy_smoother_params: self explanetory

src files:
cmd_vel_controller:
This is the main component of the driver package, taking inputs from the joystick or move-base to calculate the inverse kinematics of the robot and trying to minimize wheel rotations while respected the angle limits.
