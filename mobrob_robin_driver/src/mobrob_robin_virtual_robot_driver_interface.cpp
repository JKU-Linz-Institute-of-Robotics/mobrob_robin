#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float64MultiArray.h>
#include <sensor_msgs/JointState.h>
#include <std_srvs/Empty.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <control_msgs/JointTrajectoryControllerState.h>
#include <ros_common_robin_tools/common_cpp_tools.h>

class BASE{
	private:
		// state
		bool drives_enabled;
		geometry_msgs::Twist cmd_vel;
		
		// advertised services
		ros::ServiceServer start_drives_service, stop_drives_service, reference_drives_service;
		
		// subscribed topics
		ros::Subscriber cmd_vel_subscriber;
		
		// published topics
		ros::Publisher cmd_vel_publisher;
		ros::Publisher state_vel_publisher;
		ros::Publisher base_state_ready_publisher;

	public:
		BASE( ros::NodeHandle handle, std::string group_name, std::string emergency_stop_topic ){
			// state
			drives_enabled = true;
			
			// advertised services
			start_drives_service = handle.advertiseService( group_name + "/drives/control/" + "start",  &BASE::start_drives, this);
			stop_drives_service = handle.advertiseService( group_name + "/drives/control/" + "stop",  &BASE::stop_drives, this);
			
			// subscribed topics
			cmd_vel_subscriber = handle.subscribe( group_name + "/drives/control/" + "cmd_vel", 10, &BASE::read_cmd_vel, this);
			
			// published topics
			cmd_vel_publisher = handle.advertise<geometry_msgs::Twist>( group_name + "/cmd_vel", 10);
			state_vel_publisher = handle.advertise<geometry_msgs::Twist>( group_name + "/drives/state/vel", 10);
			base_state_ready_publisher = handle.advertise<std_msgs::Bool>( group_name + "/drives/state/info/motors_ready_and_enabled", 1000);
		}
		
	private:
		void reset_cmd_vel( void ){
			cmd_vel.linear.x = 0.0;
			cmd_vel.linear.y = 0.0;
			cmd_vel.angular.z = 0.0;
		}
		
		bool start_drives( std_srvs::Empty::Request &req, std_srvs::Empty::Response &res ){
			drives_enabled = true;
		}
		
		bool stop_drives( std_srvs::Empty::Request &req, std_srvs::Empty::Response &res ){
			// stop motion
			reset_cmd_vel();
			cmd_vel_publisher.publish( cmd_vel);
			
			// disable drive
			drives_enabled = false;
		}
		
		void read_cmd_vel( const geometry_msgs::Twist & cmd_vel ){
			this->cmd_vel = cmd_vel;
		}
		
	public:
		/**
		 * This function has to be called repeatedly to continuously transmit motion commands to the simulation.
		 */
		void transmit_command( void ){
			if( drives_enabled ){
				cmd_vel_publisher.publish( cmd_vel );
				state_vel_publisher.publish( cmd_vel );
			}
		} 
		
		void publish_state( void ){
			std_msgs::Bool state;
			
			state.data = drives_enabled;
			base_state_ready_publisher.publish( state);			
		}
		
}; // class base

int main( int argc, char** argv) {

	// init ros node
	ros::init(argc, argv, "mobrob_robin_virtual_robot_driver_interface");
	ros::NodeHandle handle;
	
	double Ts=0.01;

	BASE base( handle, "/mobrob_robin/base", "/mobrob_robin/emergency_stop" );
	
	ros::Duration rate(Ts);
	
	while( ros::ok() ){
		base.transmit_command();
		ros::spinOnce();
		
		base.publish_state();
		ros::spinOnce();
		
		rate.sleep();
	}
}// main
