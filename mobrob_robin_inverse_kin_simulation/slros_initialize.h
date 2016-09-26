#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block mobrob_robin_inverse_kin_simulation/Subscribe
extern SimulinkSubscriber<geometry_msgs::Twist, SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf> Sub_mobrob_robin_inverse_kin_simulation_124;

// For Block mobrob_robin_inverse_kin_simulation/Publish
extern SimulinkPublisher<std_msgs::Float64MultiArray, SL_Bus_mobrob_robin_inverse_kin__Float64MultiArray_635d3r> Pub_mobrob_robin_inverse_kin_simulation_123;

void slros_node_init(int argc, char** argv);

#endif
