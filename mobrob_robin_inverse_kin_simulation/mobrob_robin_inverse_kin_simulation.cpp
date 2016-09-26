//
// File: mobrob_robin_inverse_kin_simulation.cpp
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
#include "mobrob_robin_inverse_kin_simulation.h"
#include "mobrob_robin_inverse_kin_simulation_private.h"
#define mobrob_robin_in_MessageQueueLen (1)

//
// System initialize for atomic system:
//    '<S11>/only activate for direction change'
//    '<S16>/only activate for direction change'
//
void onlyactivatefordirectionch_Init(DW_onlyactivatefordirectionch_T *localDW)
{
  // '<S14>:1:6' is_initialized = false;
  localDW->is_initialized = false;

  //  initalize the persistent variable
}

//
// Output and update for atomic system:
//    '<S11>/only activate for direction change'
//    '<S16>/only activate for direction change'
//
void onlyactivatefordirectionchange(real_T rtu_u,
  B_onlyactivatefordirectioncha_T *localB, DW_onlyactivatefordirectionch_T
  *localDW)
{
  int32_T output;

  // MATLAB Function 'inverse kinematics/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds/compute velocity direction/only activate for direction change': '<S14>:1' 
  // '<S14>:1:5' if isempty(is_initialized)
  // '<S14>:1:10' output = 0;
  output = 0;

  // '<S14>:1:12' if (~is_initialized) && (u > 0.005)
  if ((!localDW->is_initialized) && (rtu_u > 0.005)) {
    // '<S14>:1:13' output = 1;
    output = 1;

    // '<S14>:1:14' is_initialized = true;
    localDW->is_initialized = true;
  }

  // '<S14>:1:17' if (is_initialized) && (u < 0.005)
  if (localDW->is_initialized && (rtu_u < 0.005)) {
    // '<S14>:1:18' is_initialized = false;
    localDW->is_initialized = false;
  }

  // '<S14>:1:21' y = output;
  localB->y = output;
}

//
// System initialize for atomic system:
//    '<S10>/Toggle'
//    '<S10>/Toggle1'
//
void mobrob_robin_invers_Toggle_Init(DW_Toggle_mobrob_robin_invers_T *localDW)
{
  // '<S25>:1:5' toggle = 0.0;
  localDW->toggle = 0.0;

  //  initalize the persistent variable
}

//
// Output and update for atomic system:
//    '<S10>/Toggle'
//    '<S10>/Toggle1'
//
void mobrob_robin_inverse_kin_Toggle(real_T rtu_set, real_T rtu_reset,
  B_Toggle_mobrob_robin_inverse_T *localB, DW_Toggle_mobrob_robin_invers_T
  *localDW)
{
  // MATLAB Function 'inverse kinematics/maintain wheel orientations for small motions/Toggle': '<S25>:1' 
  // '<S25>:1:4' if isempty(toggle)
  // '<S25>:1:8' if set > 0.5
  if (rtu_set > 0.5) {
    // '<S25>:1:9' toggle = 1.0;
    localDW->toggle = 1.0;
  }

  // '<S25>:1:12' if reset > 0.5
  if (rtu_reset > 0.5) {
    // '<S25>:1:13' toggle = 0.0;
    localDW->toggle = 0.0;
  }

  // '<S25>:1:16' y = toggle;
  localB->y = localDW->toggle;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2((real_T)u0_0, (real_T)u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  if (u1 == 0.0) {
    y = u0;
  } else if (!((!rtIsNaN(u0)) && (!rtIsInf(u0)) && ((!rtIsNaN(u1)) && (!rtIsInf
                (u1))))) {
    y = (rtNaN);
  } else {
    tmp = u0 / u1;
    if (u1 <= floor(u1)) {
      y = u0 - floor(tmp) * u1;
    } else if (fabs(tmp - rt_roundd_snf(tmp)) <= DBL_EPSILON * fabs(tmp)) {
      y = 0.0;
    } else {
      y = (tmp - floor(tmp)) * u1;
    }
  }

  return y;
}

// Model step function
void Inversekine_Sim_mdlModelClass::step()
{
  boolean_T varargout_1;
  int32_T s8_iter;
  real_T rtb_phi_r_f_p_p;
  real_T rtb_Gain_j;
  real_T rtb_phi_r_f_p;
  real_T rtb_Sum1_f;
  real_T rtb_Sum1;

  // Outputs for Atomic SubSystem: '<Root>/Subscribe'
  // Start for MATLABSystem: '<S4>/SourceBlock' incorporates:
  //   Inport: '<S7>/In1'
  //   MATLABSystem: '<S4>/SourceBlock'

  varargout_1 = Sub_mobrob_robin_inverse_kin_simulation_124.getLatestMessage
    (&mobrob_robin_inverse_kin_simu_B.varargout_2);

  // Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S7>/Enable'

  if (varargout_1) {
    mobrob_robin_inverse_kin_simu_B.In1 =
      mobrob_robin_inverse_kin_simu_B.varargout_2;
  }

  // End of Start for MATLABSystem: '<S4>/SourceBlock'
  // End of Outputs for SubSystem: '<S4>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe'

  // Outputs for Iterator SubSystem: '<S5>/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds' incorporates:
  //   ForIterator: '<S8>/For Iterator'

  for (s8_iter = 1; s8_iter <=
       mobrob_robin_inverse_kin_simu_P.ForIterator_IterationLimit; s8_iter++) {
    // Sum: '<S12>/Sum1' incorporates:
    //   Constant: '<S12>/Constant'
    //   Constant: '<S12>/Constant1'
    //   Fcn: '<S8>/Fcn1'
    //   Gain: '<S8>/Gain'
    //   Math: '<S12>/Math Function'
    //   Memory: '<S11>/Memory2'
    //   Sum: '<S12>/Sum'
    //   Sum: '<S8>/Add'

    rtb_Sum1_f = rt_modd_snf((rt_atan2d_snf
      (mobrob_robin_inverse_kin_simu_B.In1.Angular.Z * 0.2 +
       mobrob_robin_inverse_kin_simu_B.In1.Linear.Y,
       mobrob_robin_inverse_kin_simu_B.In1.Linear.X -
       mobrob_robin_inverse_kin_simu_B.In1.Angular.Z * 0.15) +
      mobrob_robin_inverse_kin_simu_P.Gain_Gain *
      mobrob_robin_inverse_kin_sim_DW.Memory2_PreviousInput_a) -
      mobrob_robin_inverse_kin_simu_P.mapphitopipi_offset,
      mobrob_robin_inverse_kin_simu_P.mapphitopipi_range) +
      mobrob_robin_inverse_kin_simu_P.mapphitopipi_offset;

    // Fcn: '<S8>/Fcn2'
    rtb_phi_r_f_p_p = ((mobrob_robin_inverse_kin_simu_B.In1.Linear.X -
                        mobrob_robin_inverse_kin_simu_B.In1.Angular.Z * 0.15) *
                       cos(rtb_Sum1_f) +
                       (mobrob_robin_inverse_kin_simu_B.In1.Angular.Z * 0.2 +
                        mobrob_robin_inverse_kin_simu_B.In1.Linear.Y) * sin
                       (rtb_Sum1_f)) / 0.1;

    // MATLAB Function: '<S11>/only activate for direction change' incorporates:
    //   Abs: '<S11>/Abs'
    //   Gain: '<S11>/rad//s 2 m//s'

    onlyactivatefordirectionchange
      (mobrob_robin_inverse_kin_simu_P.mob_rob_param_struct.r_f * fabs
       (rtb_phi_r_f_p_p),
       &mobrob_robin_inverse_kin_simu_B.sf_onlyactivatefordirectionchan,
       &mobrob_robin_inverse_kin_sim_DW.sf_onlyactivatefordirectionchan);

    // Switch: '<S13>/Switch2' incorporates:
    //   Abs: '<S13>/Abs1'
    //   Switch: '<S11>/Switch1'

    if ((!(mobrob_robin_inverse_kin_simu_B.sf_onlyactivatefordirectionchan.y >=
           mobrob_robin_inverse_kin_simu_P.Switch1_Threshold)) && (fabs
         (rtb_Sum1_f) >= mobrob_robin_inverse_kin_simu_P.Switch2_Threshold)) {
      // Switch: '<S15>/Switch3' incorporates:
      //   Memory: '<S11>/Memory2'

      if (mobrob_robin_inverse_kin_sim_DW.Memory2_PreviousInput_a >=
          mobrob_robin_inverse_kin_simu_P.Switch3_Threshold) {
        // Update for Memory: '<S11>/Memory2' incorporates:
        //   Constant: '<S15>/Constant'

        mobrob_robin_inverse_kin_sim_DW.Memory2_PreviousInput_a =
          mobrob_robin_inverse_kin_simu_P.Constant_Value_b;
      } else {
        // Update for Memory: '<S11>/Memory2' incorporates:
        //   Constant: '<S15>/Constant1'

        mobrob_robin_inverse_kin_sim_DW.Memory2_PreviousInput_a =
          mobrob_robin_inverse_kin_simu_P.Constant1_Value;
      }

      // End of Switch: '<S15>/Switch3'
    }

    // End of Switch: '<S13>/Switch2'
  }

  // End of Outputs for SubSystem: '<S5>/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds' 

  // Gain: '<S10>/rad//s to m//s' incorporates:
  //   Abs: '<S10>/Abs'

  rtb_Gain_j = mobrob_robin_inverse_kin_simu_P.mob_rob_param_struct.r_f * fabs
    (rtb_phi_r_f_p_p);

  // MATLAB Function: '<S10>/Toggle' incorporates:
  //   Constant: '<S21>/Constant'
  //   Constant: '<S22>/Constant'
  //   DataTypeConversion: '<S10>/Data Type Conversion'
  //   DataTypeConversion: '<S10>/Data Type Conversion1'
  //   RelationalOperator: '<S21>/Compare'
  //   RelationalOperator: '<S22>/Compare'

  mobrob_robin_inverse_kin_Toggle((real_T)(rtb_Gain_j >=
    mobrob_robin_inverse_kin_simu_P.CompareToConstant1_const), (real_T)
    (rtb_Gain_j <= mobrob_robin_inverse_kin_simu_P.CompareToConstant_const),
    &mobrob_robin_inverse_kin_simu_B.sf_Toggle,
    &mobrob_robin_inverse_kin_sim_DW.sf_Toggle);

  // Switch: '<S10>/Switch1' incorporates:
  //   Memory: '<S10>/Memory'

  if (!(mobrob_robin_inverse_kin_simu_B.sf_Toggle.y >
        mobrob_robin_inverse_kin_simu_P.Switch1_Threshold_c)) {
    rtb_phi_r_f_p_p = mobrob_robin_inverse_kin_sim_DW.Memory_PreviousInput[0];
    rtb_Sum1_f = mobrob_robin_inverse_kin_sim_DW.Memory_PreviousInput[1];
  }

  // End of Switch: '<S10>/Switch1'

  // Outputs for Iterator SubSystem: '<S5>/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds1' incorporates:
  //   ForIterator: '<S9>/For Iterator'

  for (s8_iter = 1; s8_iter <=
       mobrob_robin_inverse_kin_simu_P.ForIterator_IterationLimit_k; s8_iter++)
  {
    // Sum: '<S17>/Sum1' incorporates:
    //   Constant: '<S17>/Constant'
    //   Constant: '<S17>/Constant1'
    //   Fcn: '<S9>/Fcn1'
    //   Gain: '<S9>/Gain'
    //   Math: '<S17>/Math Function'
    //   Memory: '<S16>/Memory2'
    //   Sum: '<S17>/Sum'
    //   Sum: '<S9>/Add'

    rtb_Sum1 = rt_modd_snf((rt_atan2d_snf
      (mobrob_robin_inverse_kin_simu_B.In1.Angular.Z * -0.2 +
       mobrob_robin_inverse_kin_simu_B.In1.Linear.Y,
       mobrob_robin_inverse_kin_simu_B.In1.Linear.X -
       mobrob_robin_inverse_kin_simu_B.In1.Angular.Z * -0.15) +
      mobrob_robin_inverse_kin_simu_P.Gain_Gain_h *
      mobrob_robin_inverse_kin_sim_DW.Memory2_PreviousInput) -
      mobrob_robin_inverse_kin_simu_P.mapphitopipi_offset_k,
      mobrob_robin_inverse_kin_simu_P.mapphitopipi_range_j) +
      mobrob_robin_inverse_kin_simu_P.mapphitopipi_offset_k;

    // Fcn: '<S9>/Fcn2'
    rtb_phi_r_f_p = ((mobrob_robin_inverse_kin_simu_B.In1.Linear.X -
                      mobrob_robin_inverse_kin_simu_B.In1.Angular.Z * -0.15) *
                     cos(rtb_Sum1) +
                     (mobrob_robin_inverse_kin_simu_B.In1.Angular.Z * -0.2 +
                      mobrob_robin_inverse_kin_simu_B.In1.Linear.Y) * sin
                     (rtb_Sum1)) / 0.1;

    // MATLAB Function: '<S16>/only activate for direction change' incorporates:
    //   Abs: '<S16>/Abs'
    //   Gain: '<S16>/rad//s 2 m//s'

    onlyactivatefordirectionchange
      (mobrob_robin_inverse_kin_simu_P.mob_rob_param_struct.r_b * fabs
       (rtb_phi_r_f_p),
       &mobrob_robin_inverse_kin_simu_B.sf_onlyactivatefordirectionch_m,
       &mobrob_robin_inverse_kin_sim_DW.sf_onlyactivatefordirectionch_m);

    // Switch: '<S18>/Switch2' incorporates:
    //   Abs: '<S18>/Abs1'
    //   Switch: '<S16>/Switch1'

    if ((!(mobrob_robin_inverse_kin_simu_B.sf_onlyactivatefordirectionch_m.y >=
           mobrob_robin_inverse_kin_simu_P.Switch1_Threshold_p)) && (fabs
         (rtb_Sum1) >= mobrob_robin_inverse_kin_simu_P.Switch2_Threshold_j)) {
      // Switch: '<S20>/Switch3' incorporates:
      //   Memory: '<S16>/Memory2'

      if (mobrob_robin_inverse_kin_sim_DW.Memory2_PreviousInput >=
          mobrob_robin_inverse_kin_simu_P.Switch3_Threshold_o) {
        // Update for Memory: '<S16>/Memory2' incorporates:
        //   Constant: '<S20>/Constant'

        mobrob_robin_inverse_kin_sim_DW.Memory2_PreviousInput =
          mobrob_robin_inverse_kin_simu_P.Constant_Value_f;
      } else {
        // Update for Memory: '<S16>/Memory2' incorporates:
        //   Constant: '<S20>/Constant1'

        mobrob_robin_inverse_kin_sim_DW.Memory2_PreviousInput =
          mobrob_robin_inverse_kin_simu_P.Constant1_Value_n;
      }

      // End of Switch: '<S20>/Switch3'
    }

    // End of Switch: '<S18>/Switch2'
  }

  // End of Outputs for SubSystem: '<S5>/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds1' 

  // Gain: '<S10>/Gain' incorporates:
  //   Abs: '<S10>/Abs1'

  rtb_Gain_j = mobrob_robin_inverse_kin_simu_P.mob_rob_param_struct.r_b * fabs
    (rtb_phi_r_f_p);

  // MATLAB Function: '<S10>/Toggle1' incorporates:
  //   Constant: '<S23>/Constant'
  //   Constant: '<S24>/Constant'
  //   DataTypeConversion: '<S10>/Data Type Conversion2'
  //   DataTypeConversion: '<S10>/Data Type Conversion3'
  //   RelationalOperator: '<S23>/Compare'
  //   RelationalOperator: '<S24>/Compare'

  mobrob_robin_inverse_kin_Toggle((real_T)(rtb_Gain_j >=
    mobrob_robin_inverse_kin_simu_P.CompareToConstant3_const), (real_T)
    (rtb_Gain_j <= mobrob_robin_inverse_kin_simu_P.CompareToConstant2_const),
    &mobrob_robin_inverse_kin_simu_B.sf_Toggle1,
    &mobrob_robin_inverse_kin_sim_DW.sf_Toggle1);

  // Switch: '<S10>/Switch2' incorporates:
  //   Memory: '<S10>/Memory1'

  if (!(mobrob_robin_inverse_kin_simu_B.sf_Toggle1.y >
        mobrob_robin_inverse_kin_simu_P.Switch2_Threshold_n)) {
    rtb_phi_r_f_p = mobrob_robin_inverse_kin_sim_DW.Memory1_PreviousInput[0];
    rtb_Sum1 = mobrob_robin_inverse_kin_sim_DW.Memory1_PreviousInput[1];
  }

  // End of Switch: '<S10>/Switch2'

  // SignalConversion: '<S2>/TmpSignal ConversionAt SFunction Inport2' incorporates:
  //   Constant: '<S6>/Constant'
  //   Constant: '<S6>/Constant1'
  //   MATLAB Function: '<Root>/MATLAB Function'

  mobrob_robin_inverse_kin_simu_B.TmpSignalConversionAtSFunct[0] =
    rtb_phi_r_f_p_p;
  mobrob_robin_inverse_kin_simu_B.TmpSignalConversionAtSFunct[1] = rtb_phi_r_f_p;
  mobrob_robin_inverse_kin_simu_B.TmpSignalConversionAtSFunct[2] = rtb_Sum1_f;
  mobrob_robin_inverse_kin_simu_B.TmpSignalConversionAtSFunct[3] =
    mobrob_robin_inverse_kin_simu_P.Constant_Value_b2;
  mobrob_robin_inverse_kin_simu_B.TmpSignalConversionAtSFunct[4] = rtb_Sum1;
  mobrob_robin_inverse_kin_simu_B.TmpSignalConversionAtSFunct[5] =
    mobrob_robin_inverse_kin_simu_P.Constant1_Value_p;

  // MATLAB Function: '<Root>/MATLAB Function' incorporates:
  //   Constant: '<S1>/Constant'

  //  Assign the output message to be the same with input blank message
  // MATLAB Function 'MATLAB Function': '<S2>:1'
  // '<S2>:1:5' msg = blankMessage;
  mobrob_robin_inverse_kin_simu_B.msg =
    mobrob_robin_inverse_kin_simu_P.Constant_Value;

  //  Modify the nested message
  // '<S2>:1:9' size_data = size(data);
  // '<S2>:1:11' for i = 1:size_data(1)
  for (s8_iter = 0; s8_iter < 6; s8_iter++) {
    // '<S2>:1:12' msg.Data(i) = data(i);
    mobrob_robin_inverse_kin_simu_B.msg.Data[s8_iter] =
      mobrob_robin_inverse_kin_simu_B.TmpSignalConversionAtSFunct[s8_iter];
  }

  // '<S2>:1:15' msg.Data_SL_Info.CurrentLength = uint32(size_data(1));
  mobrob_robin_inverse_kin_simu_B.msg.Data_SL_Info.CurrentLength = 6U;

  // Outputs for Atomic SubSystem: '<Root>/Publish'
  // Start for MATLABSystem: '<S3>/SinkBlock' incorporates:
  //   MATLABSystem: '<S3>/SinkBlock'

  Pub_mobrob_robin_inverse_kin_simulation_123.publish
    (&mobrob_robin_inverse_kin_simu_B.msg);

  // End of Outputs for SubSystem: '<Root>/Publish'

  // Update for Memory: '<S10>/Memory' incorporates:
  //   Gain: '<S10>/remove wheel speed'

  mobrob_robin_inverse_kin_sim_DW.Memory_PreviousInput[0] = 0.0;

  // Update for Memory: '<S10>/Memory1' incorporates:
  //   Gain: '<S10>/remove wheel speed2'

  mobrob_robin_inverse_kin_sim_DW.Memory1_PreviousInput[0] = 0.0;

  // Update for Memory: '<S10>/Memory' incorporates:
  //   Gain: '<S10>/remove wheel speed'

  mobrob_robin_inverse_kin_sim_DW.Memory_PreviousInput[0] +=
    mobrob_robin_inverse_kin_simu_P.removewheelspeed_Gain[0] * rtb_phi_r_f_p_p;

  // Update for Memory: '<S10>/Memory1' incorporates:
  //   Gain: '<S10>/remove wheel speed2'

  mobrob_robin_inverse_kin_sim_DW.Memory1_PreviousInput[0] +=
    mobrob_robin_inverse_kin_simu_P.removewheelspeed2_Gain[0] * rtb_phi_r_f_p;

  // Update for Memory: '<S10>/Memory' incorporates:
  //   Gain: '<S10>/remove wheel speed'

  mobrob_robin_inverse_kin_sim_DW.Memory_PreviousInput[0] +=
    mobrob_robin_inverse_kin_simu_P.removewheelspeed_Gain[2] * rtb_Sum1_f;

  // Update for Memory: '<S10>/Memory1' incorporates:
  //   Gain: '<S10>/remove wheel speed2'

  mobrob_robin_inverse_kin_sim_DW.Memory1_PreviousInput[0] +=
    mobrob_robin_inverse_kin_simu_P.removewheelspeed2_Gain[2] * rtb_Sum1;

  // Update for Memory: '<S10>/Memory' incorporates:
  //   Gain: '<S10>/remove wheel speed'

  mobrob_robin_inverse_kin_sim_DW.Memory_PreviousInput[1] = 0.0;

  // Update for Memory: '<S10>/Memory1' incorporates:
  //   Gain: '<S10>/remove wheel speed2'

  mobrob_robin_inverse_kin_sim_DW.Memory1_PreviousInput[1] = 0.0;

  // Update for Memory: '<S10>/Memory' incorporates:
  //   Gain: '<S10>/remove wheel speed'

  mobrob_robin_inverse_kin_sim_DW.Memory_PreviousInput[1] +=
    mobrob_robin_inverse_kin_simu_P.removewheelspeed_Gain[1] * rtb_phi_r_f_p_p;

  // Update for Memory: '<S10>/Memory1' incorporates:
  //   Gain: '<S10>/remove wheel speed2'

  mobrob_robin_inverse_kin_sim_DW.Memory1_PreviousInput[1] +=
    mobrob_robin_inverse_kin_simu_P.removewheelspeed2_Gain[1] * rtb_phi_r_f_p;

  // Update for Memory: '<S10>/Memory' incorporates:
  //   Gain: '<S10>/remove wheel speed'

  mobrob_robin_inverse_kin_sim_DW.Memory_PreviousInput[1] +=
    mobrob_robin_inverse_kin_simu_P.removewheelspeed_Gain[3] * rtb_Sum1_f;

  // Update for Memory: '<S10>/Memory1' incorporates:
  //   Gain: '<S10>/remove wheel speed2'

  mobrob_robin_inverse_kin_sim_DW.Memory1_PreviousInput[1] +=
    mobrob_robin_inverse_kin_simu_P.removewheelspeed2_Gain[3] * rtb_Sum1;
}

// Model initialize function
void Inversekine_Sim_mdlModelClass::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // initialize error status
  rtmSetErrorStatus((&mobrob_robin_inverse_kin_sim_M), (NULL));

  // block I/O
  (void) memset(((void *) &mobrob_robin_inverse_kin_simu_B), 0,
                sizeof(B_mobrob_robin_inverse_kin_si_T));

  // states (dwork)
  (void) memset((void *)&mobrob_robin_inverse_kin_sim_DW, 0,
                sizeof(DW_mobrob_robin_inverse_kin_s_T));

  {
    static const char_T tmp[38] = { '/', 'm', 'o', 'b', 'r', 'o', 'b', '_', 'r',
      'o', 'b', 'i', 'n', '/', 'b', 'a', 's', 'e', '/', 'w', 'h', 'e', 'e', 'l',
      's', '/', 'j', 'o', 'i', 'n', 't', '_', 's', 't', 'a', 't', 'e', 's' };

    static const char_T tmp_0[41] = { '/', 'm', 'o', 'b', 'r', 'o', 'b', '_',
      'r', 'o', 'b', 'i', 'n', '/', 'b', 'a', 's', 'e', '/', 'd', 'r', 'i', 'v',
      'e', 's', '/', 'c', 'o', 'n', 't', 'r', 'o', 'l', '/', 'c', 'm', 'd', '_',
      'v', 'e', 'l' };

    char_T tmp_1[39];
    int32_T i;

    // Start for Atomic SubSystem: '<Root>/Subscribe'
    // Start for MATLABSystem: '<S4>/SourceBlock'
    mobrob_robin_inverse_kin_sim_DW.obj_d.isInitialized = 0;
    mobrob_robin_inverse_kin_sim_DW.obj_d.isInitialized = 1;
    for (i = 0; i < 41; i++) {
      mobrob_robin_inverse_kin_simu_B.cv0[i] = tmp_0[i];
    }

    mobrob_robin_inverse_kin_simu_B.cv0[41] = '\x00';
    Sub_mobrob_robin_inverse_kin_simulation_124.createSubscriber
      (mobrob_robin_inverse_kin_simu_B.cv0, mobrob_robin_in_MessageQueueLen);

    // End of Start for MATLABSystem: '<S4>/SourceBlock'
    // End of Start for SubSystem: '<Root>/Subscribe'

    // Start for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S3>/SinkBlock'
    mobrob_robin_inverse_kin_sim_DW.obj.isInitialized = 0;
    mobrob_robin_inverse_kin_sim_DW.obj.isInitialized = 1;
    for (i = 0; i < 38; i++) {
      tmp_1[i] = tmp[i];
    }

    tmp_1[38] = '\x00';
    Pub_mobrob_robin_inverse_kin_simulation_123.createPublisher(tmp_1,
      mobrob_robin_in_MessageQueueLen);

    // End of Start for MATLABSystem: '<S3>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish'

    // InitializeConditions for Memory: '<S10>/Memory'
    mobrob_robin_inverse_kin_sim_DW.Memory_PreviousInput[0] =
      mobrob_robin_inverse_kin_simu_P.Memory_X0[0];

    // InitializeConditions for Memory: '<S10>/Memory1'
    mobrob_robin_inverse_kin_sim_DW.Memory1_PreviousInput[0] =
      mobrob_robin_inverse_kin_simu_P.Memory1_X0[0];

    // InitializeConditions for Memory: '<S10>/Memory'
    mobrob_robin_inverse_kin_sim_DW.Memory_PreviousInput[1] =
      mobrob_robin_inverse_kin_simu_P.Memory_X0[1];

    // InitializeConditions for Memory: '<S10>/Memory1'
    mobrob_robin_inverse_kin_sim_DW.Memory1_PreviousInput[1] =
      mobrob_robin_inverse_kin_simu_P.Memory1_X0[1];

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S7>/Out1'
    mobrob_robin_inverse_kin_simu_B.In1 =
      mobrob_robin_inverse_kin_simu_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe'

    // SystemInitialize for Iterator SubSystem: '<S5>/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds' 
    // InitializeConditions for Memory: '<S11>/Memory2'
    mobrob_robin_inverse_kin_sim_DW.Memory2_PreviousInput_a =
      mobrob_robin_inverse_kin_simu_P.Memory2_X0;

    // SystemInitialize for MATLAB Function: '<S11>/only activate for direction change' 
    onlyactivatefordirectionch_Init
      (&mobrob_robin_inverse_kin_sim_DW.sf_onlyactivatefordirectionchan);

    // End of SystemInitialize for SubSystem: '<S5>/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds' 

    // SystemInitialize for MATLAB Function: '<S10>/Toggle'
    mobrob_robin_invers_Toggle_Init(&mobrob_robin_inverse_kin_sim_DW.sf_Toggle);

    // SystemInitialize for Iterator SubSystem: '<S5>/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds1' 
    // InitializeConditions for Memory: '<S16>/Memory2'
    mobrob_robin_inverse_kin_sim_DW.Memory2_PreviousInput =
      mobrob_robin_inverse_kin_simu_P.Memory2_X0_h;

    // SystemInitialize for MATLAB Function: '<S16>/only activate for direction change' 
    onlyactivatefordirectionch_Init
      (&mobrob_robin_inverse_kin_sim_DW.sf_onlyactivatefordirectionch_m);

    // End of SystemInitialize for SubSystem: '<S5>/compute wheel orientation phi_s in (-pi//pi] and wheel velocity phi_r_p The sign of phi_r_p is determined at lower speeds1' 

    // SystemInitialize for MATLAB Function: '<S10>/Toggle1'
    mobrob_robin_invers_Toggle_Init(&mobrob_robin_inverse_kin_sim_DW.sf_Toggle1);
  }
}

// Model terminate function
void Inversekine_Sim_mdlModelClass::terminate()
{
  // Terminate for Atomic SubSystem: '<Root>/Subscribe'
  // Start for MATLABSystem: '<S4>/SourceBlock' incorporates:
  //   Terminate for MATLABSystem: '<S4>/SourceBlock'

  if (mobrob_robin_inverse_kin_sim_DW.obj_d.isInitialized == 1) {
    mobrob_robin_inverse_kin_sim_DW.obj_d.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S4>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe'

  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Start for MATLABSystem: '<S3>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S3>/SinkBlock'

  if (mobrob_robin_inverse_kin_sim_DW.obj.isInitialized == 1) {
    mobrob_robin_inverse_kin_sim_DW.obj.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S3>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish'
}

// Constructor
Inversekine_Sim_mdlModelClass::Inversekine_Sim_mdlModelClass()
{
  static const P_mobrob_robin_inverse_kin_si_T
    mobrob_robin_inverse_kin_simu_P_temp = {
    {
      64.0,
      64.0,
      415.0,
      415.0,
      0.2,
      0.15,
      0.1,
      0.03,
      -0.2,
      -0.15,
      0.1,
      0.03,
      0.6,
      0.5,
      0.0,
      0.0,
      0.0,
      0.0,
      2.0,
      2.0,
      4.0,
      4.0,
      4.0,
      4.0,
      66.0,
      3.355,
      0.0,
      0.0,
      0.00012,
      0.00012,
      5.9e-6,
      5.9e-6,
      0.0139,
      0.0139,
      0.0148,
      0.0148,
      0.031100000000000003,
      0.031100000000000003,
      1.9746031746031748e-5,
      1.9746031746031748e-5,
      0.034,
      0.034,
      0.00010793650793650795,
      0.00010793650793650795,

      { 86.0, 0.0, 0.0, 4.6347680963855424, 4.1851807228915672e-5,
        4.1851807228915672e-5, 0.0, 3.3935546875e-6, 0.0, 3.3935546875e-6 }
    },                                 // Variable: mob_rob_param_struct
                                       //  Referenced by:
                                       //    '<S10>/Gain'
                                       //    '<S10>/rad//s to m//s'
                                       //    '<S11>/rad//s 2 m//s'
                                       //    '<S16>/rad//s 2 m//s'

    0.01,                              // Mask Parameter: CompareToConstant1_const
                                       //  Referenced by: '<S22>/Constant'

    0.005,                             // Mask Parameter: CompareToConstant_const
                                       //  Referenced by: '<S21>/Constant'

    0.01,                              // Mask Parameter: CompareToConstant3_const
                                       //  Referenced by: '<S24>/Constant'

    0.005,                             // Mask Parameter: CompareToConstant2_const
                                       //  Referenced by: '<S23>/Constant'

    -3.1415926535897931,               // Mask Parameter: mapphitopipi_offset
                                       //  Referenced by: '<S12>/Constant1'

    -3.1415926535897931,               // Mask Parameter: mapphitopipi_offset_k
                                       //  Referenced by: '<S17>/Constant1'

    6.2831853071795862,                // Mask Parameter: mapphitopipi_range
                                       //  Referenced by: '<S12>/Constant'

    6.2831853071795862,                // Mask Parameter: mapphitopipi_range_j
                                       //  Referenced by: '<S17>/Constant'

    0.005,                             // Mask Parameter: computewheelorientationphi_sinp
                                       //  Referenced by: '<S11>/Constant1'

    0.005,                             // Mask Parameter: computewheelorientationphi_si_h
                                       //  Referenced by: '<S16>/Constant1'


    {
      {
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0 }
      ,                                // Data

      {
        0U,                            // CurrentLength
        0U                             // ReceivedLength
      },                               // Data_SL_Info

      {
        0U,                            // DataOffset

        {
          {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          }, {
            {
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
              0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
            ,                          // Label

            {
              0U,                      // CurrentLength
              0U                       // ReceivedLength
            },                         // Label_SL_Info
            0U,                        // Size
            0U                         // Stride
          } }
        ,                              // Dim

        {
          0U,                          // CurrentLength
          0U                           // ReceivedLength
        }                              // Dim_SL_Info
      }                                // Layout
    },                                 // Computed Parameter: Constant_Value
                                       //  Referenced by: '<S1>/Constant'


    {
      {
        0.0,                           // X
        0.0,                           // Y
        0.0                            // Z
      },                               // Linear

      {
        0.0,                           // X
        0.0,                           // Y
        0.0                            // Z
      }                                // Angular
    },                                 // Computed Parameter: Out1_Y0
                                       //  Referenced by: '<S7>/Out1'


    {
      {
        0.0,                           // X
        0.0,                           // Y
        0.0                            // Z
      },                               // Linear

      {
        0.0,                           // X
        0.0,                           // Y
        0.0                            // Z
      }                                // Angular
    },                                 // Computed Parameter: Constant_Value_p
                                       //  Referenced by: '<S4>/Constant'

    1.0,                               // Expression: 1
                                       //  Referenced by: '<S15>/Constant1'

    0.0,                               // Expression: 0
                                       //  Referenced by: '<S15>/Constant'

    0.5,                               // Expression: 0.5
                                       //  Referenced by: '<S15>/Switch3'

    1.5707963267948966,                // Expression: pi/2
                                       //  Referenced by: '<S13>/Switch2'

    0.0,                               // Computed Parameter: phi_r_p_Y0
                                       //  Referenced by: '<S8>/phi_r_p'

    0.0,                               // Computed Parameter: phi_s_Y0
                                       //  Referenced by: '<S8>/phi_s'

    0.0,                               // Expression: 0
                                       //  Referenced by: '<S11>/Memory2'

    3.1415926535897931,                // Expression: pi
                                       //  Referenced by: '<S8>/Gain'

    0.5,                               // Expression: 0.5
                                       //  Referenced by: '<S11>/Switch1'

    1.0,                               // Expression: 1
                                       //  Referenced by: '<S20>/Constant1'

    0.0,                               // Expression: 0
                                       //  Referenced by: '<S20>/Constant'

    0.5,                               // Expression: 0.5
                                       //  Referenced by: '<S20>/Switch3'

    1.5707963267948966,                // Expression: pi/2
                                       //  Referenced by: '<S18>/Switch2'

    0.0,                               // Computed Parameter: phi_r_p_Y0_h
                                       //  Referenced by: '<S9>/phi_r_p'

    0.0,                               // Computed Parameter: phi_s_Y0_p
                                       //  Referenced by: '<S9>/phi_s'

    0.0,                               // Expression: 0
                                       //  Referenced by: '<S16>/Memory2'

    3.1415926535897931,                // Expression: pi
                                       //  Referenced by: '<S9>/Gain'

    0.5,                               // Expression: 0.5
                                       //  Referenced by: '<S16>/Switch1'


    //  Expression: [0,0]
    //  Referenced by: '<S10>/Memory'

    { 0.0, 0.0 },
    0.0,                               // Expression: 0
                                       //  Referenced by: '<S10>/Switch1'


    //  Expression: [0,0]
    //  Referenced by: '<S10>/Memory1'

    { 0.0, 0.0 },
    0.0,                               // Expression: 0
                                       //  Referenced by: '<S10>/Switch2'

    0.0,                               // Expression: 0
                                       //  Referenced by: '<S6>/Constant'

    0.0,                               // Expression: 0
                                       //  Referenced by: '<S6>/Constant1'


    //  Expression: diag([0,1])
    //  Referenced by: '<S10>/remove wheel speed'

    { 0.0, 0.0, 0.0, 1.0 },

    //  Expression: diag([0,1])
    //  Referenced by: '<S10>/remove wheel speed2'

    { 0.0, 0.0, 0.0, 1.0 },
    2,                                 // Computed Parameter: ForIterator_IterationLimit
                                       //  Referenced by: '<S8>/For Iterator'

    2                                  // Computed Parameter: ForIterator_IterationLimit_k
                                       //  Referenced by: '<S9>/For Iterator'

  };                                   // Modifiable parameters

  // Initialize tunable parameters
  mobrob_robin_inverse_kin_simu_P = mobrob_robin_inverse_kin_simu_P_temp;
}

// Destructor
Inversekine_Sim_mdlModelClass::~Inversekine_Sim_mdlModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
RT_MODEL_mobrob_robin_inverse_T * Inversekine_Sim_mdlModelClass::getRTM()
{
  return (&mobrob_robin_inverse_kin_sim_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
