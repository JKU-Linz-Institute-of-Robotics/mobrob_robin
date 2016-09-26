//
// File: mobrob_robin_inverse_kin_simulation_types.h
//
// Code generated for Simulink model 'mobrob_robin_inverse_kin_simulation'.
//
// Model version                  : 1.55
// Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
// C/C++ source code generated on : Mon Sep 26 07:52:44 2016
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_mobrob_robin_inverse_kin_simulation_types_h_
#define RTW_HEADER_mobrob_robin_inverse_kin_simulation_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

typedef struct {
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
} SL_Bus_ROSVariableLengthArrayInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_mobrob_robin_inverse_kin__MultiArrayDimension_nheqdn_
#define DEFINED_TYPEDEF_FOR_SL_Bus_mobrob_robin_inverse_kin__MultiArrayDimension_nheqdn_

// MsgType=std_msgs/MultiArrayDimension
typedef struct {
  // PrimitiveROSType=string:IsVarLen=1:VarLenCategory=data:VarLenElem=Label_SL_Info:TruncateAction=warn 
  uint8_T Label[128];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=Label
  SL_Bus_ROSVariableLengthArrayInfo Label_SL_Info;
  uint32_T Size;
  uint32_T Stride;
} SL_Bus_mobrob_robin_inverse_kin__MultiArrayDimension_nheqdn;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_mobrob_robin_inverse_kin__MultiArrayLayout_aj0hrv_
#define DEFINED_TYPEDEF_FOR_SL_Bus_mobrob_robin_inverse_kin__MultiArrayLayout_aj0hrv_

// MsgType=std_msgs/MultiArrayLayout
typedef struct {
  uint32_T DataOffset;

  // MsgType=std_msgs/MultiArrayDimension:IsVarLen=1:VarLenCategory=data:VarLenElem=Dim_SL_Info:TruncateAction=warn 
  SL_Bus_mobrob_robin_inverse_kin__MultiArrayDimension_nheqdn Dim[16];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=Dim
  SL_Bus_ROSVariableLengthArrayInfo Dim_SL_Info;
} SL_Bus_mobrob_robin_inverse_kin__MultiArrayLayout_aj0hrv;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_mobrob_robin_inverse_kin__Float64MultiArray_635d3r_
#define DEFINED_TYPEDEF_FOR_SL_Bus_mobrob_robin_inverse_kin__Float64MultiArray_635d3r_

// MsgType=std_msgs/Float64MultiArray
typedef struct {
  // IsVarLen=1:VarLenCategory=data:VarLenElem=Data_SL_Info:TruncateAction=warn
  real_T Data[128];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=Data
  SL_Bus_ROSVariableLengthArrayInfo Data_SL_Info;

  // MsgType=std_msgs/MultiArrayLayout
  SL_Bus_mobrob_robin_inverse_kin__MultiArrayLayout_aj0hrv Layout;
} SL_Bus_mobrob_robin_inverse_kin__Float64MultiArray_635d3r;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_mobrob_robin_inverse_kin__Vector3_ehi0g_
#define DEFINED_TYPEDEF_FOR_SL_Bus_mobrob_robin_inverse_kin__Vector3_ehi0g_

// MsgType=geometry_msgs/Vector3
typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_mobrob_robin_inverse_kin__Vector3_ehi0g;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf_
#define DEFINED_TYPEDEF_FOR_SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf_

// MsgType=geometry_msgs/Twist
typedef struct {
  // MsgType=geometry_msgs/Vector3
  SL_Bus_mobrob_robin_inverse_kin__Vector3_ehi0g Linear;

  // MsgType=geometry_msgs/Vector3
  SL_Bus_mobrob_robin_inverse_kin__Vector3_ehi0g Angular;
} SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_vOPqKz7If9YxAjgLAbEPLG_
#define DEFINED_TYPEDEF_FOR_struct_vOPqKz7If9YxAjgLAbEPLG_

typedef struct {
  real_T i_G_r_f;
  real_T i_G_r_b;
  real_T i_G_s_f;
  real_T i_G_s_b;
  real_T x_r_f;
  real_T y_r_f;
  real_T r_f;
  real_T t_f;
  real_T x_r_b;
  real_T y_r_b;
  real_T r_b;
  real_T t_b;
  real_T length;
  real_T width;
  real_T x_c;
  real_T y_c;
  real_T y_m_r_f;
  real_T y_m_r_b;
  real_T m_r_f;
  real_T m_r_b;
  real_T m_m_s_f;
  real_T m_m_s_b;
  real_T m_m_r_f;
  real_T m_m_r_b;
  real_T m_c;
  real_T C_c;
  real_T B_m_r_f;
  real_T B_m_r_b;
  real_T C_m_r_f;
  real_T C_m_r_b;
  real_T C_m_s_f;
  real_T C_m_s_b;
  real_T B_r_f;
  real_T B_r_b;
  real_T C_r_f;
  real_T C_r_b;
  real_T r_c_s_f;
  real_T r_c_s_b;
  real_T r_v_s_f;
  real_T r_v_s_b;
  real_T r_c_r_f;
  real_T r_c_r_b;
  real_T r_v_r_f;
  real_T r_v_r_b;
  real_T param_basis_nominell_without_friciton[10];
} struct_vOPqKz7If9YxAjgLAbEPLG;

#endif

#ifndef struct_tag_saG5948SFTrUFnIbVUb0TZH
#define struct_tag_saG5948SFTrUFnIbVUb0TZH

struct tag_saG5948SFTrUFnIbVUb0TZH
{
  int32_T isInitialized;
};

#endif                                 //struct_tag_saG5948SFTrUFnIbVUb0TZH

#ifndef typedef_robotics_slros_internal_block_T
#define typedef_robotics_slros_internal_block_T

typedef struct tag_saG5948SFTrUFnIbVUb0TZH robotics_slros_internal_block_T;

#endif                                 //typedef_robotics_slros_internal_block_T

#ifndef struct_tag_saG5948SFTrUFnIbVUb0TZH
#define struct_tag_saG5948SFTrUFnIbVUb0TZH

struct tag_saG5948SFTrUFnIbVUb0TZH
{
  int32_T isInitialized;
};

#endif                                 //struct_tag_saG5948SFTrUFnIbVUb0TZH

#ifndef typedef_robotics_slros_internal_blo_h_T
#define typedef_robotics_slros_internal_blo_h_T

typedef struct tag_saG5948SFTrUFnIbVUb0TZH robotics_slros_internal_blo_h_T;

#endif                                 //typedef_robotics_slros_internal_blo_h_T

#ifndef typedef_struct_T_mobrob_robin_inverse_T
#define typedef_struct_T_mobrob_robin_inverse_T

typedef struct {
  char_T f0[4];
} struct_T_mobrob_robin_inverse_T;

#endif                                 //typedef_struct_T_mobrob_robin_inverse_T

#ifndef typedef_struct_T_mobrob_robin_inver_h_T
#define typedef_struct_T_mobrob_robin_inver_h_T

typedef struct {
  char_T f0[8];
} struct_T_mobrob_robin_inver_h_T;

#endif                                 //typedef_struct_T_mobrob_robin_inver_h_T

#ifndef typedef_struct_T_mobrob_robin_inve_h2_T
#define typedef_struct_T_mobrob_robin_inve_h2_T

typedef struct {
  char_T f0[7];
} struct_T_mobrob_robin_inve_h2_T;

#endif                                 //typedef_struct_T_mobrob_robin_inve_h2_T

#ifndef typedef_struct_T_mobrob_robin_inv_h2a_T
#define typedef_struct_T_mobrob_robin_inv_h2a_T

typedef struct {
  char_T f0[8];
  char_T f1[7];
  char_T f2[6];
} struct_T_mobrob_robin_inv_h2a_T;

#endif                                 //typedef_struct_T_mobrob_robin_inv_h2a_T

// Parameters (auto storage)
typedef struct P_mobrob_robin_inverse_kin_si_T_ P_mobrob_robin_inverse_kin_si_T;

// Forward declaration for rtModel
typedef struct tag_RTM_mobrob_robin_inverse__T RT_MODEL_mobrob_robin_inverse_T;

#endif                                 // RTW_HEADER_mobrob_robin_inverse_kin_simulation_types_h_ 

//
// File trailer for generated code.
//
// [EOF]
//
