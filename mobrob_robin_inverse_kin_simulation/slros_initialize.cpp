#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "mobrob_robin_inverse_kin_simulation";

// For Block mobrob_robin_inverse_kin_simulation/Subscribe
SimulinkSubscriber<geometry_msgs::Twist, SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf> Sub_mobrob_robin_inverse_kin_simulation_124;

// For Block mobrob_robin_inverse_kin_simulation/Publish
SimulinkPublisher<std_msgs::Float64MultiArray, SL_Bus_mobrob_robin_inverse_kin__Float64MultiArray_635d3r> Pub_mobrob_robin_inverse_kin_simulation_123;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

