/*
Node for the Sick PLS200 Laserscanner
Functionality:
Create a SickPLS200 Object with the correct Serial Port
OpenCommunication() will establish a serial connection with 500k Baud
StartContinuesStream() will set the Operation Mode of the Laser to... conitnues streaming
ReadLaserData() will give back 1 set of Range Data with 361 Points over 180° 
The range data is published as a LaserScan
*/


#include <ros/ros.h>
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>
#include <sick_pls200/pls200_driver.h>
#include <signal.h>

int NUM_READINGS = 361;
int LASER_FREQUENCY = 25;

SickPLS200* laser = NULL;

void mySigintHandler(int sig)
{
  
	if(laser != NULL){
		laser->CloseSerial();
	}

	ros::shutdown();
}

int main(int argc, char** argv){
	ros::init(argc, argv, "laser_scan_publisher");  

	ros::NodeHandle n;
	
	signal(SIGINT, mySigintHandler);
	
	ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("laser_front/scan", 0); 

	laser = new SickPLS200("/dev/ttyUSB0");

	if( laser->OpenCommunication() != 0){
		ROS_ERROR("could not open serial");
		return 0;
	}	
	
	//laser.Set9600Baud();  only for debugging purposes	 

	if (laser->StartContinuesStream() != 0){
		ROS_ERROR("could not start continues stream");
		return 0;
	}
	
	std::vector<uint16_t> mm_ranges;
	ros::Rate r(100);
	while(n.ok()){	

		if(laser->ReadLaserData(mm_ranges) == 0){   

			ros::Time scan_time = ros::Time::now();    
	   
			//populate the LaserScan message
			sensor_msgs::LaserScan scan;
			scan.header.stamp = scan_time;
			scan.header.frame_id = "PLS200";
			scan.angle_min = -3.141516/2.0;
			scan.angle_max = 3.141516/2.0;
			scan.angle_increment = 3.141516 / NUM_READINGS;
			scan.time_increment = (1 / LASER_FREQUENCY) / (NUM_READINGS);
			scan.range_min = 0.0;
			scan.range_max = 100.0;
			
			for(unsigned int i = 0; i < NUM_READINGS; ++i){
			  scan.ranges.push_back(mm_ranges[i] * 10 / 1e3);
			  scan.intensities.push_back(100);
			}			
			scan_pub.publish(scan); 
			
		} else {
			ROS_ERROR("Laser is not sending data anymore");
			ROS_INFO("Resetting Laser");
			laser->Reset();
			ros::Duration(2.0).sleep();
			while (laser->StartContinuesStream() != 0){
				ROS_ERROR("Could not start continues stream again, retrying");
			}
		}
		r.sleep(); 
		ros::spinOnce();
	}
	laser->CloseSerial();
}

