#include <ros/ros.h>
#include <signal.h>

#include <ros_common_robin_bst/Bs.h>

#include <std_msgs/Float64MultiArray.h>
#include <visualization_msgs/MarkerArray.h>

ros::Publisher points_pub;
double rgb[3] = {0.0, 0.0, 0.0};
int seq = 0;

void points_planCallback(const std_msgs::Float64MultiArray::ConstPtr &msg){
	if(msg->data.size() > 0){
		int num_of_points = msg->data.size() / msg->layout.dim[0].size;
		int size = msg->layout.dim[0].size;		
		visualization_msgs::MarkerArray spline_points;
		spline_points.markers.resize(num_of_points);
		
		for(int i = 0; i < num_of_points; i++){
			int k = i*size;
			spline_points.markers[i].header.stamp = ros::Time::now();
			spline_points.markers[i].header.frame_id = "odom";
			spline_points.markers[i].header.seq = seq;
			spline_points.markers[i].id = seq;
			spline_points.markers[i].type = 0;
			spline_points.markers[i].action = 0;
			spline_points.markers[i].lifetime = ros::Duration(0);
			spline_points.markers[i].scale.x = 0.02;
			spline_points.markers[i].scale.y = 0.005;
			spline_points.markers[i].scale.z = 0.001;
			
			spline_points.markers[i].pose.position.x = msg->data[k+1];
			spline_points.markers[i].pose.position.y = msg->data[k+2];
			spline_points.markers[i].pose.position.z = 0;
			spline_points.markers[i].pose.orientation.x = msg->data[k+3];
			spline_points.markers[i].pose.orientation.y = msg->data[k+4];
			spline_points.markers[i].pose.orientation.z = msg->data[k+5];
			spline_points.markers[i].pose.orientation.w = msg->data[k+6];
			
							
			spline_points.markers[i].color.r = rgb[0];
			spline_points.markers[i].color.g = rgb[1];
			spline_points.markers[i].color.b = rgb[2];
			spline_points.markers[i].color.a = 1;
			
			
			seq++;			
		}
		
		if(rgb[0] < 0.9) {
			rgb[0] += 0.1;
		} else if(rgb[1] < 0.9) {
			rgb[1] += 0.1;
		
		} else {
			rgb[0] = 0.0;
			rgb[1] = 0.0;
			rgb[2] = 0.0;
		}
		
		
		
		points_pub.publish(spline_points);
		
	}
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "spline_test");
  ros::NodeHandle n;
  
  
  ros::Subscriber points_sub = n.subscribe("/move_base/DWASplinePlannerROS/points_plan", 1, points_planCallback);
  
  points_pub = n.advertise<visualization_msgs::MarkerArray>("Spline_points", 100);
  
  ros::spin();
  return 0;
}
