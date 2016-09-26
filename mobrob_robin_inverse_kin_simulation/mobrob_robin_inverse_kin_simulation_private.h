//
// File: mobrob_robin_inverse_kin_simulation_private.h
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
#ifndef RTW_HEADER_mobrob_robin_inverse_kin_simulation_private_h_
#define RTW_HEADER_mobrob_robin_inverse_kin_simulation_private_h_
#include "rtwtypes.h"
#include "mobrob_robin_inverse_kin_simulation.h"

extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern real_T rt_roundd_snf(real_T u);
extern real_T rt_modd_snf(real_T u0, real_T u1);
extern void onlyactivatefordirectionch_Init(DW_onlyactivatefordirectionch_T
  *localDW);
extern void onlyactivatefordirectionchange(real_T rtu_u,
  B_onlyactivatefordirectioncha_T *localB, DW_onlyactivatefordirectionch_T
  *localDW);
extern void mobrob_robin_invers_Toggle_Init(DW_Toggle_mobrob_robin_invers_T
  *localDW);
extern void mobrob_robin_inverse_kin_Toggle(real_T rtu_set, real_T rtu_reset,
  B_Toggle_mobrob_robin_inverse_T *localB, DW_Toggle_mobrob_robin_invers_T
  *localDW);

#endif                                 // RTW_HEADER_mobrob_robin_inverse_kin_simulation_private_h_ 

//
// File trailer for generated code.
//
// [EOF]
//
