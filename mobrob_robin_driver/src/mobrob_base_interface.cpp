#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>



double phi_lf = 0.0;
double phi_rb = 0.0;



// Initialize a callback to get velocity values:



void cmd_wheelsCallback( const std_msgs::Float64MultiArrayConstPtr& msg) {

  phi_lf = msg->data[2];
  phi_rb = msg->data[4];
  
}



int main( int argc, char** argv) {

  ros::init(argc, argv, "base_interface");
  
  ros::NodeHandle n;
  ros::Subscriber wheels_sub = n.subscribe("base/wheels/joint_states", 1, cmd_wheelsCallback);
  
  ros::Publisher pub_lf = n.advertise<std_msgs::Float64>("base/lf_position_controller/command", 50);
  ros::Publisher pub_rb = n.advertise<std_msgs::Float64>("base/rb_position_controller/command", 50); 
  
  
  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();
  
  
  ros::Rate r(100.0);
  while (n.ok()) {
    
      
      std_msgs::Float64 lf_msg;
      std_msgs::Float64 rb_msg;
      
      lf_msg.data = phi_lf;
      rb_msg.data = phi_rb;
      
      pub_lf.publish(lf_msg);
      pub_rb.publish(rb_msg);


      last_time = current_time;

      ros::spinOnce();
      r.sleep();
    
   }  
}
