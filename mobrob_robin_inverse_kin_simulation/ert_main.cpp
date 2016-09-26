//
// File: ert_main.cpp
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
#include <stdio.h>
#include <stdlib.h>
#include "mobrob_robin_inverse_kin_simulation.h"
#include "mobrob_robin_inverse_kin_simulation_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "rt_nonfinite.h"
#include "linuxinitialize.h"

static Inversekine_Sim_mdlModelClass mobrob_robin_inverse_kin_si_Obj;// Instance of model class 

// Function prototype declaration
void exitTask(int sig);
void terminateTask(void *arg);
void baseRateTask(void *arg);
void subrateTask(void *arg);
volatile boolean_T runModel = true;
sem_t stopSem;
sem_t baserateTaskSem;
pthread_t schedulerThread;
pthread_t baseRateThread;
unsigned long threadJoinStatus[8];
int terminatingmodel = 0;
void baseRateTask(void *arg)
{
  runModel = (rtmGetErrorStatus(mobrob_robin_inverse_kin_si_Obj.getRTM()) ==
              (NULL));
  while (runModel) {
    sem_wait(&baserateTaskSem);
    mobrob_robin_inverse_kin_si_Obj.step();

    // Get model outputs here
    runModel = (rtmGetErrorStatus(mobrob_robin_inverse_kin_si_Obj.getRTM()) ==
                (NULL));
  }

  runModel = 0;
  terminateTask(arg);
  pthread_exit((void *)0);
}

void exitTask(int sig)
{
  rtmSetErrorStatus(mobrob_robin_inverse_kin_si_Obj.getRTM(),
                    "stopping the model");
}

void terminateTask(void *arg)
{
  terminatingmodel = 1;
  printf("**terminating the model**\n");
  fflush(stdout);

  {
    int ret;
    runModel = 0;
  }

  // Disable rt_OneStep() here

  // Terminate model
  mobrob_robin_inverse_kin_si_Obj.terminate();
  sem_post(&stopSem);
}

int main(int argc, char **argv)
{
  void slros_node_init(int argc, char** argv);
  slros_node_init(argc, argv);
  printf("**starting the model**\n");
  fflush(stdout);
  rtmSetErrorStatus(mobrob_robin_inverse_kin_si_Obj.getRTM(), 0);

  // Initialize model
  mobrob_robin_inverse_kin_si_Obj.initialize();

  // Call RTOS Initialization funcation
  myRTOSInit(0.01, 0);

  // Wait for stop semaphore
  sem_wait(&stopSem);
  return 0;
}

//
// File trailer for generated code.
//
// [EOF]
//
