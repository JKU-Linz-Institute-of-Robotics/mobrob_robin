#include <ros/ros.h>
#include <math.h>
#include <vector>

//Ros Includes
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64MultiArray.h>
#include <sensor_msgs/JointState.h>

#define _USE_MATH_DEFINES

ros::Publisher cmd_drives_pub;
ros::Publisher cmd_vel_pub;
ros::Publisher steering_angles_pub;
geometry_msgs::Twist joy_twist;
geometry_msgs::Twist move_base_twist;
geometry_msgs::Twist old_twist;
geometry_msgs::Twist zero_twist;

double x_r_f = 0.2;
double y_r_f = 0.15;
double x_r_b = -0.2;
double y_r_b = -0.15;
double r = 0.1;

double phi_limit = 130.0/180.0*M_PI;  //driver limit is 120 degree

double phi_f = 0.0;
double phi_b = 0.0;

bool steering = false;

std_msgs::Float64MultiArray cmd_drives; 	// phi_r_f_p phi_r_b_p phi_s_f phi_s_b
std_msgs::Float64MultiArray old_cmd_drives;

void calc_steering_angles( geometry_msgs::Twist twist, std_msgs::Float64MultiArray &cmd_drives);

double wrap_to_pi(double angle){	
	double wrapped = fmod(angle+M_PI, 2.0*M_PI) - M_PI;
	if(wrapped > phi_limit){
		wrapped -= M_PI;
	}
	if(wrapped < -phi_limit){
		wrapped += M_PI;
	}
	return wrapped;
}


bool twist_is_zero( geometry_msgs::Twist twist ){
	return fabs(twist.linear.x) < 0.05 && fabs(twist.linear.y) < 0.05 && fabs(twist.angular.z) < 0.05;
}


void calc_cmd_drives( geometry_msgs::Twist twist, std_msgs::Float64MultiArray &cmd_drives){
	calc_steering_angles(twist, cmd_drives);
	
	cmd_drives.data[0] = (cos(cmd_drives.data[2]) * (twist.linear.x - twist.angular.z * y_r_f) + sin(cmd_drives.data[2]) * (twist.linear.y + twist.angular.z * x_r_f))/r;
	cmd_drives.data[1] = (cos(cmd_drives.data[3]) * (twist.linear.x - twist.angular.z * y_r_b) + sin(cmd_drives.data[3]) * (twist.linear.y + twist.angular.z * x_r_b))/r;
	
}

void calc_steering_angles( geometry_msgs::Twist twist, std_msgs::Float64MultiArray &cmd_drives){
	//calculate the angles
	cmd_drives.data[2] = atan2(twist.linear.y+twist.angular.z*x_r_f, twist.linear.x-twist.angular.z*y_r_f); 
	cmd_drives.data[3] = atan2(twist.linear.y+twist.angular.z*x_r_b, twist.linear.x-twist.angular.z*y_r_b);
	
		
	cmd_drives.data[2] = wrap_to_pi(cmd_drives.data[2]);  //map to -pi +pi
	cmd_drives.data[3] = wrap_to_pi(cmd_drives.data[3]);
		
	
	//calculate the difference to the current steering angle
	//add PI and check which one is smaller -> choose the smaller one	
		
	
	double e_f = fabs(phi_f - cmd_drives.data[2]);
	double e_b = fabs(phi_b - cmd_drives.data[3]);
	
	
	// add pi or subtract pi if the angle is over M_PI - phi_limit // > 50 degrees
	
	double phi_f_pi = cmd_drives.data[2];
	double phi_b_pi = cmd_drives.data[3];
	
	
	if(cmd_drives.data[2] > (M_PI-phi_limit)){     
		phi_f_pi = cmd_drives.data[2]-M_PI;
		ROS_INFO("test1");
	} else 	if(cmd_drives.data[2] < -(M_PI-phi_limit)) {   
		ROS_INFO("test2");
		phi_f_pi = cmd_drives.data[2]+M_PI;
	} 
	
	if(cmd_drives.data[3] > (M_PI-phi_limit)){    
		ROS_INFO("test3");
		phi_b_pi = cmd_drives.data[3]-M_PI;
	} else	if(cmd_drives.data[3] < -(M_PI-phi_limit)) {   
		ROS_INFO("test4");
		phi_b_pi = cmd_drives.data[3]+M_PI;
	}
	
	
	
	double e_f_pi = fabs(phi_f - phi_f_pi);
	double e_b_pi = fabs(phi_b - phi_b_pi);
	
	/*
	ROS_INFO("phi_f phi_b = %f %f", phi_f*180/M_PI, phi_b*180/M_PI);
	ROS_INFO("f b = %f %f", cmd_drives.data[2]*180/M_PI, cmd_drives.data[3]*180/M_PI);
	ROS_INFO("phi_f_pi phi_b_pi = %f %f", phi_f_pi*180/M_PI, phi_b_pi*180/M_PI);	
	ROS_INFO("e_f e_b = %f %f", e_f*180/M_PI, e_b*180/M_PI);
	ROS_INFO("e_f_pi e_b_pi = %f %f \n \n", e_f_pi*180/M_PI, e_b_pi*180/M_PI);
	*/
	
	if(e_f > e_f_pi){
		cmd_drives.data[2] = phi_f_pi;
	}				
	if(e_b > e_b_pi) {
		cmd_drives.data[3] = phi_b_pi;
	}
	ROS_INFO("final %f %f", cmd_drives.data[2], cmd_drives.data[3]);
	
}

bool direction_change(geometry_msgs::Twist twist, std_msgs::Float64MultiArray &cmd_drives){
	//calculate the velocities for the wheels, this is needed to match the simulink model
	//and to prevent sudden direction changes of the wheel speeds!
	
	cmd_drives.data[0] = (cos(cmd_drives.data[2]) * (twist.linear.x - twist.angular.z * y_r_f) + sin(cmd_drives.data[2]) * (twist.linear.y + twist.angular.z * x_r_f));
	cmd_drives.data[1] = (cos(cmd_drives.data[3]) * (twist.linear.x - twist.angular.z * y_r_b) + sin(cmd_drives.data[3]) * (twist.linear.y + twist.angular.z * x_r_b));
	
	return ((old_cmd_drives.data[0]*cmd_drives.data[0] < -0.01) || (old_cmd_drives.data[1]*cmd_drives.data[1] < -0.01));	
}


//capture the velocity commands before sending them to the robot
void cmd_vel_raw_callback( const geometry_msgs::Twist twist ){

	geometry_msgs::Twist current_twist;
	current_twist = twist;
	
	if(twist_is_zero(twist)){
		cmd_drives.data.resize(4);
		cmd_drives.data[0] = 0.0;
		cmd_drives.data[1] = 0.0;
		cmd_drives.data[2] = 0.0;
		cmd_drives.data[3] = 0.0;
		old_cmd_drives.data[0] = 0.0;
		old_cmd_drives.data[1] = 0.0;
		old_cmd_drives.data[2] = 0.0;
		old_cmd_drives.data[3] = 0.0;
		cmd_drives_pub.publish(cmd_drives);
		return;
	}	
	
	
	//if there is a large rotation value and vx and vy is small, set vx and vy zero	&&  0.1 < (fabs(twist.linear.x) + fabs(twist.linear.y))
	/*if(fabs(twist.angular.z) > 0.5 * (fabs(twist.linear.x) + fabs(twist.linear.y)) ){
		current_twist.linear.x = 0;
		current_twist.linear.y = 0;
	}*/	
	
	//only send steering angles if we move from a standstill?
	double threshhold = 0.2; 
	if(twist_is_zero(old_twist)){
		threshhold = 0.2;
	} else {
		threshhold = 0.7;
	}
	
	calc_cmd_drives(current_twist, cmd_drives);	
	
	//do we have to steer? or does the direction of velocity change?
	if((fabs(cmd_drives.data[2] - phi_f) > threshhold) || (fabs(cmd_drives.data[3] - phi_b) > threshhold)){	
		cmd_drives.data[0] = 0;
		cmd_drives.data[1] = 0;		
		cmd_drives_pub.publish(cmd_drives);
		steering = true;
		//ROS_INFO("steering error %f - %f and %f - %f", angles.data[0] ,phi_f, angles.data[1], phi_b);
	} else {
		//ROS_INFO("not steering");
		steering = false;
	}		
	
	if(!steering){
		cmd_drives_pub.publish(cmd_drives);
		old_cmd_drives = cmd_drives;
		old_twist = current_twist;
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
  
  cmd_drives.data.resize(4);
  old_cmd_drives.data.resize(4);
  old_cmd_drives.data[0] = 0;
  old_cmd_drives.data[1] = 0;
  old_cmd_drives.data[2] = 0;
  old_cmd_drives.data[3] = 0;
  
  
  //init subscribers
  ros::Subscriber joint_state_subscriber = n.subscribe( "/joint_states", 1, joint_state_callback );
  ros::Subscriber cmd_vel_raw_subscriber = n.subscribe( "/cmd_vel_raw", 1, cmd_vel_raw_callback );
  
  //init publisher and start loop
  cmd_drives_pub = n.advertise<std_msgs::Float64MultiArray>("/cmd_drives", 1000);
  
  ros::spin();
}
