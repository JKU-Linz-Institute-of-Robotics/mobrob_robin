//
// File: mobrob_robin_inverse_kin_simulation.h
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
#ifndef RTW_HEADER_mobrob_robin_inverse_kin_simulation_h_
#define RTW_HEADER_mobrob_robin_inverse_kin_simulation_h_
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef mobrob_robin_inverse_kin_simulation_COMMON_INCLUDES_
# define mobrob_robin_inverse_kin_simulation_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "slros_initialize.h"
#endif                                 // mobrob_robin_inverse_kin_simulation_COMMON_INCLUDES_ 

#include "mobrob_robin_inverse_kin_simulation_types.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#define mobrob_robin_inverse_kin_simulation_M (mobrob_robin_inverse_kin_sim_M)

// Block signals for system '<S11>/only activate for direction change'
typedef struct {
  real_T y;                            // '<S11>/only activate for direction change' 
} B_onlyactivatefordirectioncha_T;

// Block states (auto storage) for system '<S11>/only activate for direction change' 
typedef struct {
  boolean_T is_initialized;            // '<S11>/only activate for direction change' 
} DW_onlyactivatefordirectionch_T;

// Block signals for system '<S10>/Toggle'
typedef struct {
  real_T y;                            // '<S10>/Toggle'
} B_Toggle_mobrob_robin_inverse_T;

// Block states (auto storage) for system '<S10>/Toggle'
typedef struct {
  real_T toggle;                       // '<S10>/Toggle'
} DW_Toggle_mobrob_robin_invers_T;

// Block signals (auto storage)
typedef struct {
  SL_Bus_mobrob_robin_inverse_kin__Float64MultiArray_635d3r msg;// '<Root>/MATLAB Function' 
  SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf In1;// '<S7>/In1'
  SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf varargout_2;
  real_T TmpSignalConversionAtSFunct[6];// '<Root>/MATLAB Function'
  char_T cv0[42];
  B_Toggle_mobrob_robin_inverse_T sf_Toggle1;// '<S10>/Toggle1'
  B_Toggle_mobrob_robin_inverse_T sf_Toggle;// '<S10>/Toggle'
  B_onlyactivatefordirectioncha_T sf_onlyactivatefordirectionch_m;// '<S16>/only activate for direction change' 
  B_onlyactivatefordirectioncha_T sf_onlyactivatefordirectionchan;// '<S11>/only activate for direction change' 
} B_mobrob_robin_inverse_kin_si_T;

// Block states (auto storage) for system '<Root>'
typedef struct {
  real_T Memory_PreviousInput[2];      // '<S10>/Memory'
  real_T Memory1_PreviousInput[2];     // '<S10>/Memory1'
  real_T Memory2_PreviousInput;        // '<S16>/Memory2'
  real_T Memory2_PreviousInput_a;      // '<S11>/Memory2'
  void *SourceBlock_PWORK;             // '<S4>/SourceBlock'
  void *SinkBlock_PWORK;               // '<S3>/SinkBlock'
  robotics_slros_internal_block_T obj; // '<S3>/SinkBlock'
  robotics_slros_internal_blo_h_T obj_d;// '<S4>/SourceBlock'
  DW_Toggle_mobrob_robin_invers_T sf_Toggle1;// '<S10>/Toggle1'
  DW_Toggle_mobrob_robin_invers_T sf_Toggle;// '<S10>/Toggle'
  DW_onlyactivatefordirectionch_T sf_onlyactivatefordirectionch_m;// '<S16>/only activate for direction change' 
  DW_onlyactivatefordirectionch_T sf_onlyactivatefordirectionchan;// '<S11>/only activate for direction change' 
} DW_mobrob_robin_inverse_kin_s_T;

// Parameters (auto storage)
struct P_mobrob_robin_inverse_kin_si_T_ {
  struct_vOPqKz7If9YxAjgLAbEPLG mob_rob_param_struct;// Variable: mob_rob_param_struct
                                                     //  Referenced by:
                                                     //    '<S10>/Gain'
                                                     //    '<S10>/rad//s to m//s'
                                                     //    '<S11>/rad//s 2 m//s'
                                                     //    '<S16>/rad//s 2 m//s'

  real_T CompareToConstant1_const;     // Mask Parameter: CompareToConstant1_const
                                       //  Referenced by: '<S22>/Constant'

  real_T CompareToConstant_const;      // Mask Parameter: CompareToConstant_const
                                       //  Referenced by: '<S21>/Constant'

  real_T CompareToConstant3_const;     // Mask Parameter: CompareToConstant3_const
                                       //  Referenced by: '<S24>/Constant'

  real_T CompareToConstant2_const;     // Mask Parameter: CompareToConstant2_const
                                       //  Referenced by: '<S23>/Constant'

  real_T mapphitopipi_offset;          // Mask Parameter: mapphitopipi_offset
                                       //  Referenced by: '<S12>/Constant1'

  real_T mapphitopipi_offset_k;        // Mask Parameter: mapphitopipi_offset_k
                                       //  Referenced by: '<S17>/Constant1'

  real_T mapphitopipi_range;           // Mask Parameter: mapphitopipi_range
                                       //  Referenced by: '<S12>/Constant'

  real_T mapphitopipi_range_j;         // Mask Parameter: mapphitopipi_range_j
                                       //  Referenced by: '<S17>/Constant'

  real_T computewheelorientationphi_sinp;// Mask Parameter: computewheelorientationphi_sinp
                                         //  Referenced by: '<S11>/Constant1'

  real_T computewheelorientationphi_si_h;// Mask Parameter: computewheelorientationphi_si_h
                                         //  Referenced by: '<S16>/Constant1'

  SL_Bus_mobrob_robin_inverse_kin__Float64MultiArray_635d3r Constant_Value;// Computed Parameter: Constant_Value
                                                                      //  Referenced by: '<S1>/Constant'

  SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf Out1_Y0;// Computed Parameter: Out1_Y0
                                                        //  Referenced by: '<S7>/Out1'

  SL_Bus_mobrob_robin_inverse_kin__Twist_6k0yuf Constant_Value_p;// Computed Parameter: Constant_Value_p
                                                                 //  Referenced by: '<S4>/Constant'

  real_T Constant1_Value;              // Expression: 1
                                       //  Referenced by: '<S15>/Constant1'

  real_T Constant_Value_b;             // Expression: 0
                                       //  Referenced by: '<S15>/Constant'

  real_T Switch3_Threshold;            // Expression: 0.5
                                       //  Referenced by: '<S15>/Switch3'

  real_T Switch2_Threshold;            // Expression: pi/2
                                       //  Referenced by: '<S13>/Switch2'

  real_T phi_r_p_Y0;                   // Computed Parameter: phi_r_p_Y0
                                       //  Referenced by: '<S8>/phi_r_p'

  real_T phi_s_Y0;                     // Computed Parameter: phi_s_Y0
                                       //  Referenced by: '<S8>/phi_s'

  real_T Memory2_X0;                   // Expression: 0
                                       //  Referenced by: '<S11>/Memory2'

  real_T Gain_Gain;                    // Expression: pi
                                       //  Referenced by: '<S8>/Gain'

  real_T Switch1_Threshold;            // Expression: 0.5
                                       //  Referenced by: '<S11>/Switch1'

  real_T Constant1_Value_n;            // Expression: 1
                                       //  Referenced by: '<S20>/Constant1'

  real_T Constant_Value_f;             // Expression: 0
                                       //  Referenced by: '<S20>/Constant'

  real_T Switch3_Threshold_o;          // Expression: 0.5
                                       //  Referenced by: '<S20>/Switch3'

  real_T Switch2_Threshold_j;          // Expression: pi/2
                                       //  Referenced by: '<S18>/Switch2'

  real_T phi_r_p_Y0_h;                 // Computed Parameter: phi_r_p_Y0_h
                                       //  Referenced by: '<S9>/phi_r_p'

  real_T phi_s_Y0_p;                   // Computed Parameter: phi_s_Y0_p
                                       //  Referenced by: '<S9>/phi_s'

  real_T Memory2_X0_h;                 // Expression: 0
                                       //  Referenced by: '<S16>/Memory2'

  real_T Gain_Gain_h;                  // Expression: pi
                                       //  Referenced by: '<S9>/Gain'

  real_T Switch1_Threshold_p;          // Expression: 0.5
                                       //  Referenced by: '<S16>/Switch1'

  real_T Memory_X0[2];                 // Expression: [0,0]
                                       //  Referenced by: '<S10>/Memory'

  real_T Switch1_Threshold_c;          // Expression: 0
                                       //  Referenced by: '<S10>/Switch1'

  real_T Memory1_X0[2];                // Expression: [0,0]
                                       //  Referenced by: '<S10>/Memory1'

  real_T Switch2_Threshold_n;          // Expression: 0
                                       //  Referenced by: '<S10>/Switch2'

  real_T Constant_Value_b2;            // Expression: 0
                                       //  Referenced by: '<S6>/Constant'

  real_T Constant1_Value_p;            // Expression: 0
                                       //  Referenced by: '<S6>/Constant1'

  real_T removewheelspeed_Gain[4];     // Expression: diag([0,1])
                                       //  Referenced by: '<S10>/remove wheel speed'

  real_T removewheelspeed2_Gain[4];    // Expression: diag([0,1])
                                       //  Referenced by: '<S10>/remove wheel speed2'

  int32_T ForIterator_IterationLimit;  // Computed Parameter: ForIterator_IterationLimit
                                       //  Referenced by: '<S8>/For Iterator'

  int32_T ForIterator_IterationLimit_k;// Computed Parameter: ForIterator_IterationLimit_k
                                       //  Referenced by: '<S9>/For Iterator'

};

// Real-time Model Data Structure
struct tag_RTM_mobrob_robin_inverse__T {
  const char_T *errorStatus;
};

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

// Class declaration for model mobrob_robin_inverse_kin_simulation
class Inversekine_Sim_mdlModelClass {
  // public data and function members
 public:
  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  void terminate();

  // Constructor
  Inversekine_Sim_mdlModelClass();

  // Destructor
  ~Inversekine_Sim_mdlModelClass();

  // Real-Time Model get method
  RT_MODEL_mobrob_robin_inverse_T * getRTM();

  // private data and function members
 private:
  // Tunable parameters
  P_mobrob_robin_inverse_kin_si_T mobrob_robin_inverse_kin_simu_P;

  // Block signals
  B_mobrob_robin_inverse_kin_si_T mobrob_robin_inverse_kin_simu_B;

  // Block states
  DW_mobrob_robin_inverse_kin_s_T mobrob_robin_inverse_kin_sim_DW;

  // Real-Time Model
  RT_MODEL_mobrob_robin_inverse_T mobrob_robin_inverse_kin_sim_M;
};

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'mobrob_robin_inverse_kin_simulation'
//  '<S1>'   : 'mobrob_robin_inverse_kin_simulation/Blank Message'
//  '<S2>'   : 'mobrob_robin_inverse_kin_simulation/MATLAB Function'
//  '<S3>'   : 'mobrob_robin_inverse_kin_simulation/Publish'
//  '<S4>'   : 'mobrob_robin_inverse_kin_simulation/Subscribe'
//  '<S5>'   : 'mobrob_robin_inverse_kin_simulation/inverse kinematics'
//  '<S6>'   : 'mobrob_robin_inverse_kin_simulation/numeric derivative not yet implimented'
//  '<S7>'   : 'mobrob_robin_inverse_kin_simulation/Subscribe/Enabled Subsystem'
//  '<S8>'   : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds'
//  '<S9>'   : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds1'
//  '<S10>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/maintain wheel orientations for small motions'
//  '<S11>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds/compute velocity direction'
//  '<S12>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds/map phi to (-pi,pi] '
//  '<S13>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds/compute velocity direction/check if direction should be swtiched'
//  '<S14>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds/compute velocity direction/only activate for direction change'
//  '<S15>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds/compute velocity direction/check if direction should be swtiched/Subsystem'
//  '<S16>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds1/compute velocity direction'
//  '<S17>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds1/map phi to (-pi,pi] '
//  '<S18>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds1/compute velocity direction/check if direction should be swtiched'
//  '<S19>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds1/compute velocity direction/only activate for direction change'
//  '<S20>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds1/compute velocity direction/check if direction should be swtiched/Subsystem'
//  '<S21>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/maintain wheel orientations for small motions/Compare To Constant'
//  '<S22>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/maintain wheel orientations for small motions/Compare To Constant1'
//  '<S23>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/maintain wheel orientations for small motions/Compare To Constant2'
//  '<S24>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/maintain wheel orientations for small motions/Compare To Constant3'
//  '<S25>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/maintain wheel orientations for small motions/Toggle'
//  '<S26>'  : 'mobrob_robin_inverse_kin_simulation/inverse kinematics/maintain wheel orientations for small motions/Toggle1'

#endif                                 // RTW_HEADER_mobrob_robin_inverse_kin_simulation_h_ 

//
// File trailer for generated code.
//
// [EOF]
//
