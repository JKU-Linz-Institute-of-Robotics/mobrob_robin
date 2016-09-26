#ifndef _SLROS_BUSMSG_CONVERSION_H_
#define _SLROS_BUSMSG_CONVERSION_H_

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/MultiArrayLayout.h>
#include "mobrob_robin_inverse_kin_simulation_types.h"
#include "slros_msgconvert_utils.h"


void convertFromBus(geometry_msgs::Twist* msgPtr, SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf const* busPtr);
void convertToBus(SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf* busPtr, geometry_msgs::Twist const* msgPtr);

void convertFromBus(geometry_msgs::Vector3* msgPtr, SL_Bus_mobrob_robin_inverse_kin__Vector3_ehi0g const* busPtr);
void convertToBus(SL_Bus_mobrob_robin_inverse_kin__Vector3_ehi0g* busPtr, geometry_msgs::Vector3 const* msgPtr);

void convertFromBus(std_msgs::Float64MultiArray* msgPtr, SL_Bus_mobrob_robin_inverse_kin__Float64MultiArray_635d3r const* busPtr);
void convertToBus(SL_Bus_mobrob_robin_inverse_kin__Float64MultiArray_635d3r* busPtr, std_msgs::Float64MultiArray const* msgPtr);

void convertFromBus(std_msgs::MultiArrayDimension* msgPtr, SL_Bus_mobrob_robin_inverse_kin__MultiArrayDimension_nheqdn const* busPtr);
void convertToBus(SL_Bus_mobrob_robin_inverse_kin__MultiArrayDimension_nheqdn* busPtr, std_msgs::MultiArrayDimension const* msgPtr);

void convertFromBus(std_msgs::MultiArrayLayout* msgPtr, SL_Bus_mobrob_robin_inverse_kin__MultiArrayLayout_aj0hrv const* busPtr);
void convertToBus(SL_Bus_mobrob_robin_inverse_kin__MultiArrayLayout_aj0hrv* busPtr, std_msgs::MultiArrayLayout const* msgPtr);


#endif
