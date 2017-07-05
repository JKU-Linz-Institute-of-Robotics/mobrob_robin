#include <ros/ros.h>
#include <math.h>
#include <vector>

//Ros Includes
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64MultiArray.h>
#include <sensor_msgs/JointState.h>

#define _USE_MATH_DEFINES

ros::Publisher cmd_vel_pub;
ros::Publisher steering_angles_pub;
geometry_msgs::Twist old_twist;
geometry_msgs::Twist zero_twist;

double x_r_f = 0.2;
double y_r_f = 0.15;
double x_r_b = -0.2;
double y_r_b = -0.15;

double phi_f = 0.0;
double phi_b = 0.0;

bool steering = false;

std::vector<double> old_velocities;

bool twist_is_zero( geometry_msgs::Twist twist ){
	return fabs(twist.linear.x) < 0.05 && fabs(twist.linear.y) < 0.05 && fabs(twist.angular.z) < 0.05;
}

void calc_steering_angles( geometry_msgs::Twist twist, std_msgs::Float64MultiArray &angles){
	//calculate the angles
	angles.data.resize(2);
	angles.data[0] = atan2(twist.linear.y+twist.angular.z*x_r_f, twist.linear.x-twist.angular.z*y_r_f); 
	angles.data[1] = atan2(twist.linear.y+twist.angular.z*x_r_b, twist.linear.x-twist.angular.z*y_r_b);
	
	
	if(fabs(angles.data[0]) >= 2.0*M_PI/3.0){
		angles.data[0] += M_PI;
	}
	
	if(fabs(angles.data[1]) >= 2.0*M_PI/3.0){
		angles.data[1] += M_PI;
	}
	
	angles.data[0] = fmod(angles.data[0]+M_PI, 2.0*M_PI) - M_PI;  //map to -pi +pi
	angles.data[1] = fmod(angles.data[1]+M_PI, 2.0*M_PI) - M_PI;	
	
	
}

bool direction_change(geometry_msgs::Twist twist, std_msgs::Float64MultiArray &angles){
	//calculate the velocities for the wheels, this is needed to match the simulink model
	//and to prevent sudden direction changes of the wheel speeds!
	std::vector<double> velocities;
	velocities.resize(2);
	velocities[0] = (cos(angles.data[0]) * (twist.linear.x - twist.angular.z * y_r_f) + sin(angles.data[0]) * (twist.linear.y + twist.angular.z * x_r_f));
	velocities[1] = (cos(angles.data[1]) * (twist.linear.x - twist.angular.z * y_r_b) + sin(angles.data[1]) * (twist.linear.y + twist.angular.z * x_r_b));
	
	return ((old_velocities[0]*velocities[0] < -0.01) || (old_velocities[1]*velocities[1] < -0.01));
	
}


//capture the velocity commands before sending them to the robot
void cmd_vel_raw_callback( const geometry_msgs::Twist twist ){
	std_msgs::Float64MultiArray angles;
	
	if(twist_is_zero(twist)){
		angles.data.resize(2);
		angles.data[0] = 0.0;
		angles.data[1] = 0.0;
		steering_angles_pub.publish(angles);
	}
	
	//only send steering angles if we move from a standstill?
	double threshhold = 0.2; 
	if(twist_is_zero(old_twist)){
		threshhold = 0.2;
	} else {
		threshhold = 0.7;
	}
	
	calc_steering_angles(twist, angles);	
	//do we have to steer? or does the direction of velocity change?
	if((fabs(angles.data[0] - phi_f) > threshhold) || (fabs(angles.data[1] - phi_b) > threshhold) || direction_change(twist, angles)){			
		steering_angles_pub.publish(angles);
		cmd_vel_pub.publish(zero_twist);
		steering = true;
		//ROS_INFO("steering error %f - %f and %f - %f", angles.data[0] ,phi_f, angles.data[1], phi_b);
	} else {
		//ROS_INFO("not steering");
		steering = false;
	}		
	
	
	if(!steering || twist_is_zero(twist)){
		cmd_vel_pub.publish(twist);
		old_twist = twist;
	}
}


//get the current wheel orientation
void joint_state_callback( const sensor_msgs::JointState joint_state ){
	phi_f = joint_state.position[3];
	phi_b = joint_state.position[4];	
}


int main( int argc, char** argv) {

  ros::init(argc, argv, "cmd_vel_controller");
  ros::NodeHandle n;
  
  old_twist.linear.x = 0;
  old_twist.linear.y = 0;
  old_twist.linear.z = 0;
  old_twist.angular.x = 0;
  old_twist.angular.y = 0;
  old_twist.angular.z = 0;
  
  zero_twist.linear.x = 0;
  zero_twist.linear.y = 0;
  zero_twist.linear.z = 0;
  zero_twist.angular.x = 0;
  zero_twist.angular.y = 0;
  zero_twist.angular.z = 0;
  
  old_velocities.resize(2);
  old_velocities[0] = 0.0;
  old_velocities[1] = 0.0;
  
  
  //init subscribers
  ros::Subscriber joint_state_subscriber = n.subscribe( "/joint_states", 1, joint_state_callback );
  ros::Subscriber cmd_vel_raw_subscriber = n.subscribe( "/cmd_vel_raw", 1, cmd_vel_raw_callback );
  
  //init publisher and start loop
  cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_ctrl", 1000);
  steering_angles_pub = n.advertise<std_msgs::Float64MultiArray>("mobrob_robin/base/drives/control/steering_target", 1000);
  
  ros::spin();
}
