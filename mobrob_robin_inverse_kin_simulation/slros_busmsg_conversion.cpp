#include "slros_busmsg_conversion.h"


// Conversions between SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf and geometry_msgs::Twist

void convertFromBus(geometry_msgs::Twist* msgPtr, SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf const* busPtr)
{
  const std::string rosMessageType("geometry_msgs/Twist");

  convertFromBus(&msgPtr->angular, &busPtr->Angular);
  convertFromBus(&msgPtr->linear, &busPtr->Linear);
}

void convertToBus(SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf* busPtr, geometry_msgs::Twist const* msgPtr)
{
  const std::string rosMessageType("geometry_msgs/Twist");

  convertToBus(&busPtr->Angular, &msgPtr->angular);
  convertToBus(&busPtr->Linear, &msgPtr->linear);
}


// Conversions between SL_Bus_mobrob_robin_inverse_kin__Vector3_ehi0g and geometry_msgs::Vector3

void convertFromBus(geometry_msgs::Vector3* msgPtr, SL_Bus_mobrob_robin_inverse_kin__Vector3_ehi0g const* busPtr)
{
  const std::string rosMessageType("geometry_msgs/Vector3");

  msgPtr->x =  busPtr->X;
  msgPtr->y =  busPtr->Y;
  msgPtr->z =  busPtr->Z;
}

void convertToBus(SL_Bus_mobrob_robin_inverse_kin__Vector3_ehi0g* busPtr, geometry_msgs::Vector3 const* msgPtr)
{
  const std::string rosMessageType("geometry_msgs/Vector3");

  busPtr->X =  msgPtr->x;
  busPtr->Y =  msgPtr->y;
  busPtr->Z =  msgPtr->z;
}


// Conversions between SL_Bus_mobrob_robin_inverse_kin__Float64MultiArray_635d3r and std_msgs::Float64MultiArray

void convertFromBus(std_msgs::Float64MultiArray* msgPtr, SL_Bus_mobrob_robin_inverse_kin__Float64MultiArray_635d3r const* busPtr)
{
  const std::string rosMessageType("std_msgs/Float64MultiArray");

  convertFromBusVariablePrimitiveArray(msgPtr->data, busPtr->Data, busPtr->Data_SL_Info);
  convertFromBus(&msgPtr->layout, &busPtr->Layout);
}

void convertToBus(SL_Bus_mobrob_robin_inverse_kin__Float64MultiArray_635d3r* busPtr, std_msgs::Float64MultiArray const* msgPtr)
{
  const std::string rosMessageType("std_msgs/Float64MultiArray");

  convertToBusVariablePrimitiveArray(busPtr->Data, busPtr->Data_SL_Info, msgPtr->data, slros::EnabledWarning(rosMessageType, "data"));
  convertToBus(&busPtr->Layout, &msgPtr->layout);
}


// Conversions between SL_Bus_mobrob_robin_inverse_kin__MultiArrayDimension_nheqdn and std_msgs::MultiArrayDimension

void convertFromBus(std_msgs::MultiArrayDimension* msgPtr, SL_Bus_mobrob_robin_inverse_kin__MultiArrayDimension_nheqdn const* busPtr)
{
  const std::string rosMessageType("std_msgs/MultiArrayDimension");

  convertFromBusVariablePrimitiveArray(msgPtr->label, busPtr->Label, busPtr->Label_SL_Info);
  msgPtr->size =  busPtr->Size;
  msgPtr->stride =  busPtr->Stride;
}

void convertToBus(SL_Bus_mobrob_robin_inverse_kin__MultiArrayDimension_nheqdn* busPtr, std_msgs::MultiArrayDimension const* msgPtr)
{
  const std::string rosMessageType("std_msgs/MultiArrayDimension");

  convertToBusVariablePrimitiveArray(busPtr->Label, busPtr->Label_SL_Info, msgPtr->label, slros::EnabledWarning(rosMessageType, "label"));
  busPtr->Size =  msgPtr->size;
  busPtr->Stride =  msgPtr->stride;
}


// Conversions between SL_Bus_mobrob_robin_inverse_kin__MultiArrayLayout_aj0hrv and std_msgs::MultiArrayLayout

void convertFromBus(std_msgs::MultiArrayLayout* msgPtr, SL_Bus_mobrob_robin_inverse_kin__MultiArrayLayout_aj0hrv const* busPtr)
{
  const std::string rosMessageType("std_msgs/MultiArrayLayout");

  msgPtr->data_offset =  busPtr->DataOffset;
  convertFromBusVariableNestedArray(msgPtr->dim, busPtr->Dim, busPtr->Dim_SL_Info);
}

void convertToBus(SL_Bus_mobrob_robin_inverse_kin__MultiArrayLayout_aj0hrv* busPtr, std_msgs::MultiArrayLayout const* msgPtr)
{
  const std::string rosMessageType("std_msgs/MultiArrayLayout");

  busPtr->DataOffset =  msgPtr->data_offset;
  convertToBusVariableNestedArray(busPtr->Dim, busPtr->Dim_SL_Info, msgPtr->dim, slros::EnabledWarning(rosMessageType, "dim"));
}

