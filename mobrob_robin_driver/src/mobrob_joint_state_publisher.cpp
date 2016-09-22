/*
 * @file   mobrob_joint_state_publisher.cpp
 * @Author Christoph Stöger / Lukas Proprentner
 * @date   März, 2015 / modified September 2016
 * @brief  Publishs the joint state of the robot.
 *
 * This node read in sensor data from the driver and publish it to
 * the /joint_state topic.
 */
#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Bool.h"
#include "std_srvs/Empty.h"
#include "sensor_msgs/JointState.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "tf/transform_datatypes.h"

double x = 0.0;
double y = 0.0;
double yaw = 0.0, yaw0;
double yaw_imu = 0.0, offset_imu=0.0;
double vx = 0.0;
double vy = 0.0;
double omegaz = 0.0;
double omegaz_imu = 0.0;

bool no_imu_data_received = true;


sensor_msgs::JointState base_joint_state;

nav_msgs::Odometry odom;

ros::Publisher joint_state_publisher;
ros::Publisher odometry_publisher;

ros::Time current_time, last_time;

void base_callback( const geometry_msgs::Twist base_vel ){
	base_joint_state.header.stamp 	= ros::Time::now();
	last_time = current_time;
	current_time = base_joint_state.header.stamp;
	
	// fill joint state
	vx = base_vel.linear.x;
	vy = base_vel.linear.y;
	omegaz = base_vel.angular.z;  
	
	double dt = (current_time - last_time).toSec();
    double I_vx = (vx * cos(yaw) - vy * sin(yaw));
    double I_vy = (vx * sin(yaw) + vy * cos(yaw));
    
    double delta_x = I_vx * dt;
    double delta_y = I_vy * dt;
    double delta_yaw = omegaz * dt;

    x += delta_x ;
    y += delta_y ;
    yaw += delta_yaw;    
    
    base_joint_state.position[0] = x;
	base_joint_state.position[1] = y;
	base_joint_state.position[2] = yaw;
	
	base_joint_state.velocity[0] = I_vx;
	base_joint_state.velocity[1] = I_vy;
	base_joint_state.velocity[2] = omegaz;

	joint_state_publisher.publish( base_joint_state);
 	
 	// publish odometry for navigation stack
 	odom.header.stamp = current_time;
 	
 	odom.header.frame_id = "odom";
 	odom.pose.pose.position.x = x;
 	odom.pose.pose.position.y = y;
 	odom.pose.pose.position.z = 0.0;
 	odom.pose.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw (0.0, 0.0, yaw);
 	
 	odom.child_frame_id = "base_link";
 	odom.twist.twist.linear.x = vx;
 	odom.twist.twist.linear.y = vy;
 	odom.twist.twist.linear.z = 0.0;
 	odom.twist.twist.angular.x = 0.0;
 	odom.twist.twist.angular.y = 0.0;
 	odom.twist.twist.angular.z = omegaz;
 	
 	odometry_publisher.publish( odom );
 	
 	return;
 	
}


int main(int argc, char **argv)
{
  //  init node
  ros::init(argc, argv, "mobrob_joint_state_publisher");
  ros::NodeHandle n;
  
  ROS_INFO("joint_state_publisher_initializing");
  
  // init subscriber and msg - BASE
  std::string base_prefix = "base_";
  base_joint_state.name.resize(3);
  base_joint_state.name[0] = base_prefix + "x_joint";
  base_joint_state.name[1] = base_prefix + "y_joint";
  base_joint_state.name[2] = base_prefix + "yaw_joint";
  
  base_joint_state.position.resize(3);
  base_joint_state.velocity.resize(3);
  base_joint_state.effort.resize(3);
  
  // read parameters
  if(  n.hasParam( "/mobrob_robin/base/odometry/x0" ) ){
	n.getParam( "/mobrob_robin/base/odometry/x0", x);
  }
  if(  n.hasParam( "/mobrob_robin/base/odometry/y0" ) ){
	n.getParam( "/mobrob_robin/base/odometry/y0", y);
  }
  if(  n.hasParam( "/mobrob_robin/base/odometry/yaw0" ) ){
	n.getParam( "/mobrob_robin/base/odometry/yaw0", yaw0);
	yaw = yaw0;
  }
  
  std::vector<double> covariance;
  covariance.resize(36);
  if( n.hasParam( "/mobrob_robin/base/odometry/pose_covariance" ) ){
	n.getParam( "/mobrob_robin/base/odometry/pose_covariance", covariance);
	for(unsigned int i=0; i<36; i++){
		odom.pose.covariance[i] = (double) covariance[i];
	}
  }else{
	ROS_WARN("pose covariance not specified, use default values");
	odom.pose.covariance[0] = 1e3;
	odom.pose.covariance[1+6] = 1e3;
	odom.pose.covariance[2+2*6] = 1e6;
	odom.pose.covariance[3+3*6] = 1e6;
	odom.pose.covariance[4+4*6] = 1e6;
	odom.pose.covariance[5+5*6] = 1e-3;
  }
  if( n.hasParam( "/mobrob_robin/base/odometry/twist_covariance") ){
	n.getParam( "/mobrob_robin/base/odometry/twist_covariance", covariance);
	for( unsigned int i=0; i<36; i++){
		odom.twist.covariance[i] = (double) covariance[i];
	}
  }else{
	ROS_WARN("velocity covariance not specified, use default values");
	odom.twist.covariance[0] = 1e3;
	odom.twist.covariance[1+6] = 1e3;
	odom.twist.covariance[2+2*6] = 1e6;
	odom.twist.covariance[3+3*6] = 1e6;
	odom.twist.covariance[4+4*6] = 1e6;
	odom.twist.covariance[5+5*6] = 1e-3;
  }
 	
  
  ros::Subscriber base_state_subscriber = n.subscribe( "/mobrob_robin/base/drives/state/vel", 0, base_callback );

  // init publisher and start loop
  joint_state_publisher = n.advertise<sensor_msgs::JointState>("/joint_states", 0);
  odometry_publisher = n.advertise<nav_msgs::Odometry>("/odom", 0);

  ROS_INFO("joint_state_publisher running");
  
  current_time = ros::Time::now();
  
  /*
  ros::Rate r(100);
  
  while(ros::ok()){
	  ros::spinOnce();
	  r.sleep();
  }
  */
  
  ros::spin();

  return 0;

}
