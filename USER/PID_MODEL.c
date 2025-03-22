/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PID_MODEL.c
 *
 * Code generated for Simulink model 'PID_MODEL'.
 *
 * Model version                  : 4.8
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon Mar 10 17:17:40 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "PID_MODEL.h"
#include "rtwtypes.h"
#include <math.h>

/* Named constants for Chart: '<S25>/Chart1' */
#define IN_ADD                         ((uint8_T)1U)
#define IN_IDLE                        ((uint8_T)2U)
#define IN_SUB                         ((uint8_T)3U)

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void Chart1_Init(real32_T *rty_u2);
static void Chart1(real32_T rtu_u1, real32_T *rty_u2, DW_Chart1 *localDW);

/*
 * System initialize for atomic system:
 *    '<S25>/Chart1'
 *    '<S181>/Chart1'
 *    '<S337>/Chart1'
 *    '<S493>/Chart1'
 *    '<S649>/Chart1'
 *    '<S805>/Chart1'
 *    '<S961>/Chart1'
 *    '<S1117>/Chart1'
 *    '<S1273>/Chart1'
 *    '<S1429>/Chart1'
 *    ...
 */
static void Chart1_Init(real32_T *rty_u2)
{
  *rty_u2 = 0.0F;
}

/*
 * Output and update for atomic system:
 *    '<S25>/Chart1'
 *    '<S181>/Chart1'
 *    '<S337>/Chart1'
 *    '<S493>/Chart1'
 *    '<S649>/Chart1'
 *    '<S805>/Chart1'
 *    '<S961>/Chart1'
 *    '<S1117>/Chart1'
 *    '<S1273>/Chart1'
 *    '<S1429>/Chart1'
 *    ...
 */
static void Chart1(real32_T rtu_u1, real32_T *rty_u2, DW_Chart1 *localDW)
{
  /* Chart: '<S25>/Chart1' */
  if (localDW->is_active_c1_PID_MODEL == 0U) {
    localDW->is_active_c1_PID_MODEL = 1U;
    localDW->is_c1_PID_MODEL = IN_IDLE;
  } else {
    switch (localDW->is_c1_PID_MODEL) {
     case IN_ADD:
      if (rtu_u1 <= -5000.0F) {
        localDW->is_c1_PID_MODEL = IN_SUB;
        *rty_u2 = -1.0F;
      } else if ((rtu_u1 < 5000.0F) && (rtu_u1 > -5000.0F)) {
        localDW->is_c1_PID_MODEL = IN_IDLE;
      }
      break;

     case IN_IDLE:
      if (rtu_u1 >= 5000.0F) {
        localDW->is_c1_PID_MODEL = IN_ADD;
        *rty_u2 = 1.0F;
      } else if (rtu_u1 <= -5000.0F) {
        localDW->is_c1_PID_MODEL = IN_SUB;
        *rty_u2 = -1.0F;
      } else {
        *rty_u2 = 0.0F;
      }
      break;

     default:
      /* case IN_SUB: */
      if (rtu_u1 >= 5000.0F) {
        localDW->is_c1_PID_MODEL = IN_ADD;
        *rty_u2 = 1.0F;
      } else if ((rtu_u1 < 5000.0F) && (rtu_u1 > -5000.0F)) {
        localDW->is_c1_PID_MODEL = IN_IDLE;
      }
      break;
    }
  }

  /* End of Chart: '<S25>/Chart1' */
}

/* Model step function */
void PID_MODEL_step(void)
{
  real32_T rtb_FilterCoefficient;
  real32_T rtb_FilterCoefficient_ba;
  real32_T rtb_FilterCoefficient_hh;
  real32_T rtb_FilterCoefficient_jq;
  real32_T rtb_FilterCoefficient_lb;
  real32_T rtb_Integrator_ow;
  real32_T rtb_Switch1_bt;
  real32_T rtb_Switch2_ft;
  real32_T u0;

  /* Switch: '<Root>/Switch2' incorporates:
   *  Abs: '<Root>/Abs'
   *  Constant: '<Root>/Constant'
   *  Inport: '<Root>/distance'
   */
  if ((real32_T)fabs(rtU.distance) > rtP.DEADBAND_POS) {
    rtb_Integrator_ow = rtU.distance;
  } else {
    rtb_Integrator_ow = 0.0F;
  }

  /* End of Switch: '<Root>/Switch2' */

  /* DiscreteIntegrator: '<S3333>/Integrator' incorporates:
   *  Inport: '<Root>/reset_status_dist'
   */
  if (((rtU.reset_status_dist > 0.0F) && (rtDW.Integrator_PrevResetState <= 0)) ||
      ((rtU.reset_status_dist <= 0.0F) && (rtDW.Integrator_PrevResetState == 1)))
  {
    rtDW.Integrator_DSTATE = 0.0F;
  }

  /* DiscreteIntegrator: '<S3328>/Filter' incorporates:
   *  Inport: '<Root>/reset_status_dist'
   */
  if (((rtU.reset_status_dist > 0.0F) && (rtDW.Filter_PrevResetState <= 0)) ||
      ((rtU.reset_status_dist <= 0.0F) && (rtDW.Filter_PrevResetState == 1))) {
    rtDW.Filter_DSTATE = 0.0F;
  }

  /* Gain: '<S3336>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S3328>/Filter'
   *  Gain: '<S3326>/Derivative Gain'
   *  Sum: '<S3328>/SumD'
   */
  rtb_FilterCoefficient = (rtP.POS_D * rtb_Integrator_ow - rtDW.Filter_DSTATE) *
    100.0F;

  /* Sum: '<S3342>/Sum' incorporates:
   *  DiscreteIntegrator: '<S3333>/Integrator'
   *  Gain: '<S3338>/Proportional Gain'
   */
  u0 = (rtP.POS_P * rtb_Integrator_ow + rtDW.Integrator_DSTATE) +
    rtb_FilterCoefficient;

  /* Saturate: '<S3340>/Saturation' */
  if (u0 > 8000.0F) {
    /* Outport: '<Root>/vel_out' */
    rtY.vel_out = 8000.0F;
  } else if (u0 < -8000.0F) {
    /* Outport: '<Root>/vel_out' */
    rtY.vel_out = -8000.0F;
  } else {
    /* Outport: '<Root>/vel_out' */
    rtY.vel_out = u0;
  }

  /* End of Saturate: '<S3340>/Saturation' */

  /* Switch: '<Root>/Switch1' incorporates:
   *  Abs: '<Root>/Abs1'
   *  Constant: '<Root>/Constant1'
   *  Inport: '<Root>/ang_err'
   */
  if ((real32_T)fabs(rtU.ang_err) > rtP.DEADBAND_ANG) {
    rtb_Switch1_bt = rtU.ang_err;
  } else {
    rtb_Switch1_bt = 0.0F;
  }

  /* End of Switch: '<Root>/Switch1' */

  /* DiscreteIntegrator: '<S3383>/Integrator' incorporates:
   *  Inport: '<Root>/reset_status_ang'
   */
  if (((rtU.reset_status_ang > 0.0F) && (rtDW.Integrator_PrevResetState_k <= 0))
      || ((rtU.reset_status_ang <= 0.0F) && (rtDW.Integrator_PrevResetState_k ==
        1))) {
    rtDW.Integrator_DSTATE_e = 0.0F;
  }

  /* DiscreteIntegrator: '<S3378>/Filter' incorporates:
   *  Inport: '<Root>/reset_status_ang'
   */
  if (((rtU.reset_status_ang > 0.0F) && (rtDW.Filter_PrevResetState_p <= 0)) ||
      ((rtU.reset_status_ang <= 0.0F) && (rtDW.Filter_PrevResetState_p == 1))) {
    rtDW.Filter_DSTATE_l = 0.0F;
  }

  /* Gain: '<S3386>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S3378>/Filter'
   *  Gain: '<S3376>/Derivative Gain'
   *  Sum: '<S3378>/SumD'
   */
  rtb_FilterCoefficient_lb = (rtP.POS_A_D * rtb_Switch1_bt -
    rtDW.Filter_DSTATE_l) * 100.0F;

  /* Sum: '<S3392>/Sum' incorporates:
   *  DiscreteIntegrator: '<S3383>/Integrator'
   *  Gain: '<S3388>/Proportional Gain'
   */
  u0 = (rtP.POS_A_P * rtb_Switch1_bt + rtDW.Integrator_DSTATE_e) +
    rtb_FilterCoefficient_lb;

  /* Saturate: '<S3390>/Saturation' */
  if (u0 > 8000.0F) {
    /* Outport: '<Root>/omega_out' */
    rtY.omega_out = 8000.0F;
  } else if (u0 < -8000.0F) {
    /* Outport: '<Root>/omega_out' */
    rtY.omega_out = -8000.0F;
  } else {
    /* Outport: '<Root>/omega_out' */
    rtY.omega_out = u0;
  }

  /* End of Saturate: '<S3390>/Saturation' */

  /* SwitchCase: '<S1>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH1_1'
   */
  switch ((int32_T)rtU.status_CH1_1) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S1>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S24>/Action Port'
     */
    /* Sum: '<S24>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_1'
     *  Inport: '<Root>/target_CH1_1'
     */
    rtb_Switch2_ft = rtU.target_CH1_1 - rtU.speed_rpm_CH1_1;

    /* Switch: '<S24>/Switch2' incorporates:
     *  Abs: '<S24>/Abs'
     *  Constant: '<S24>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH1_1)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S24>/Switch2' */

    /* DiscreteIntegrator: '<S55>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_1'
     */
    if (((rtU.reset_status1_1 > 0.0F) && (rtDW.Filter_PrevResetState_bi <= 0)) ||
        ((rtU.reset_status1_1 <= 0.0F) && (rtDW.Filter_PrevResetState_bi == 1)))
    {
      rtDW.Filter_DSTATE_ks = 0.0F;
    }

    /* Gain: '<S63>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S55>/Filter'
     *  Gain: '<S53>/Derivative Gain'
     *  Sum: '<S55>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH1_1 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_ks) * 100.0F;

    /* DiscreteIntegrator: '<S60>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_1'
     */
    if (((rtU.reset_status1_1 > 0.0F) && (rtDW.Integrator_PrevResetState_a2a <=
          0)) || ((rtU.reset_status1_1 <= 0.0F) &&
                  (rtDW.Integrator_PrevResetState_a2a == 1))) {
      rtDW.Integrator_DSTATE_lm = 0.0F;
    }

    /* Sum: '<S69>/Sum' incorporates:
     *  DiscreteIntegrator: '<S60>/Integrator'
     *  Gain: '<S65>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_1 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_lm) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S67>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_1' */
      rtY.SPD_OUT_CH1_1 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_1' */
      rtY.SPD_OUT_CH1_1 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH1_1' */
      rtY.SPD_OUT_CH1_1 = u0;
    }

    /* End of Saturate: '<S67>/Saturation' */

    /* Update for DiscreteIntegrator: '<S55>/Filter' incorporates:
     *  DiscreteIntegrator: '<S60>/Integrator'
     *  Inport: '<Root>/reset_status1_1'
     */
    rtDW.Filter_DSTATE_ks += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status1_1 > 0.0F) {
      rtDW.Filter_PrevResetState_bi = 1;
      rtDW.Integrator_PrevResetState_a2a = 1;
    } else {
      if (rtU.reset_status1_1 < 0.0F) {
        rtDW.Filter_PrevResetState_bi = -1;
      } else if (rtU.reset_status1_1 == 0.0F) {
        rtDW.Filter_PrevResetState_bi = 0;
      } else {
        rtDW.Filter_PrevResetState_bi = 2;
      }

      if (rtU.reset_status1_1 < 0.0F) {
        rtDW.Integrator_PrevResetState_a2a = -1;
      } else if (rtU.reset_status1_1 == 0.0F) {
        rtDW.Integrator_PrevResetState_a2a = 0;
      } else {
        rtDW.Integrator_PrevResetState_a2a = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S55>/Filter' */

    /* Update for DiscreteIntegrator: '<S60>/Integrator' incorporates:
     *  Gain: '<S57>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_lm += rtP.SPD_I_CH1_1 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S1>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S1>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S25>/Action Port'
     */
    /* Sum: '<S25>/Sum' incorporates:
     *  Gain: '<S25>/Gain'
     *  Inport: '<Root>/circle_CH1_1'
     *  Inport: '<Root>/ecd_CH1_1'
     *  Inport: '<Root>/target_CH1_1'
     *  Sum: '<S25>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH1_1 - (8191.0F * rtU.circle_CH1_1 +
      rtU.ecd_CH1_1);

    /* Abs: '<S25>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S25>/Switch2' incorporates:
     *  Constant: '<S25>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH1_1)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S25>/Switch2' */

    /* Gain: '<S166>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S158>/Filter'
     *  Gain: '<S156>/Derivative Gain'
     *  Sum: '<S158>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH1_1 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_hs) * 100.0F;

    /* Switch: '<S25>/Switch1' incorporates:
     *  Constant: '<S25>/Constant'
     *  Gain: '<S25>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_1'
     *  Saturate: '<S170>/Saturation'
     *  Sum: '<S25>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH1_1) {
      /* Sum: '<S172>/Sum' incorporates:
       *  DiscreteIntegrator: '<S163>/Integrator'
       *  Gain: '<S168>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_1 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_ag) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S170>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH1_1 * u0 - rtU.speed_rpm_CH1_1;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S25>/Switch1' */

    /* DiscreteIntegrator: '<S108>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_1'
     */
    if (((rtU.reset_status1_1 > 0.0F) && (rtDW.Filter_PrevResetState_hk <= 0)) ||
        ((rtU.reset_status1_1 <= 0.0F) && (rtDW.Filter_PrevResetState_hk == 1)))
    {
      rtDW.Filter_DSTATE_j = 0.0F;
    }

    /* Gain: '<S116>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S108>/Filter'
     *  Gain: '<S106>/Derivative Gain'
     *  Sum: '<S108>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH1_1 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_j) * 100.0F;

    /* DiscreteIntegrator: '<S113>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_1'
     */
    if (((rtU.reset_status1_1 > 0.0F) && (rtDW.Integrator_PrevResetState_mx <= 0))
        || ((rtU.reset_status1_1 <= 0.0F) && (rtDW.Integrator_PrevResetState_mx ==
          1))) {
      rtDW.Integrator_DSTATE_l4 = 0.0F;
    }

    /* Sum: '<S122>/Sum' incorporates:
     *  DiscreteIntegrator: '<S113>/Integrator'
     *  Gain: '<S118>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_1 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_l4) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S120>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_1' */
      rtY.ANG_OUT_CH1_1 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_1' */
      rtY.ANG_OUT_CH1_1 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH1_1' */
      rtY.ANG_OUT_CH1_1 = u0;
    }

    /* End of Saturate: '<S120>/Saturation' */

    /* Chart: '<S25>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_1'
     *  Inport: '<Root>/last_ecd_CH1_1'
     *  Sum: '<S25>/Sum3'
     */
    Chart1(rtU.ecd_CH1_1 - rtU.last_ecd_CH1_1, &rtDW.u2_nnb, &rtDW.sf_Chart1);

    /* Outport: '<Root>/circle_out_CH1_1' incorporates:
     *  Inport: '<Root>/circle_CH1_1'
     *  Sum: '<S25>/Sum4'
     */
    rtY.circle_out_CH1_1 = rtDW.u2_nnb + rtU.circle_CH1_1;

    /* Update for DiscreteIntegrator: '<S163>/Integrator' incorporates:
     *  Gain: '<S160>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ag += rtP.ANG_A_I_CH1_1 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S158>/Filter' */
    rtDW.Filter_DSTATE_hs += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S108>/Filter' incorporates:
     *  DiscreteIntegrator: '<S113>/Integrator'
     *  Inport: '<Root>/reset_status1_1'
     */
    rtDW.Filter_DSTATE_j += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status1_1 > 0.0F) {
      rtDW.Filter_PrevResetState_hk = 1;
      rtDW.Integrator_PrevResetState_mx = 1;
    } else {
      if (rtU.reset_status1_1 < 0.0F) {
        rtDW.Filter_PrevResetState_hk = -1;
      } else if (rtU.reset_status1_1 == 0.0F) {
        rtDW.Filter_PrevResetState_hk = 0;
      } else {
        rtDW.Filter_PrevResetState_hk = 2;
      }

      if (rtU.reset_status1_1 < 0.0F) {
        rtDW.Integrator_PrevResetState_mx = -1;
      } else if (rtU.reset_status1_1 == 0.0F) {
        rtDW.Integrator_PrevResetState_mx = 0;
      } else {
        rtDW.Integrator_PrevResetState_mx = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S108>/Filter' */

    /* Update for DiscreteIntegrator: '<S113>/Integrator' incorporates:
     *  Gain: '<S110>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_l4 += rtP.ANG_S_I_CH1_1 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S1>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S1>/Switch Case' */

  /* SwitchCase: '<S2>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH1_2'
   */
  switch ((int32_T)rtU.status_CH1_2) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S2>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S180>/Action Port'
     */
    /* Sum: '<S180>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_2'
     *  Inport: '<Root>/target_CH1_2'
     */
    rtb_Switch2_ft = rtU.target_CH1_2 - rtU.speed_rpm_CH1_2;

    /* Switch: '<S180>/Switch2' incorporates:
     *  Abs: '<S180>/Abs'
     *  Constant: '<S180>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH1_2)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S180>/Switch2' */

    /* DiscreteIntegrator: '<S211>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_2'
     */
    if (((rtU.reset_status1_2 > 0.0F) && (rtDW.Filter_PrevResetState_o2 <= 0)) ||
        ((rtU.reset_status1_2 <= 0.0F) && (rtDW.Filter_PrevResetState_o2 == 1)))
    {
      rtDW.Filter_DSTATE_d5 = 0.0F;
    }

    /* Gain: '<S219>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S211>/Filter'
     *  Gain: '<S209>/Derivative Gain'
     *  Sum: '<S211>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH1_2 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_d5) * 100.0F;

    /* DiscreteIntegrator: '<S216>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_2'
     */
    if (((rtU.reset_status1_2 > 0.0F) && (rtDW.Integrator_PrevResetState_ar <= 0))
        || ((rtU.reset_status1_2 <= 0.0F) && (rtDW.Integrator_PrevResetState_ar ==
          1))) {
      rtDW.Integrator_DSTATE_hf = 0.0F;
    }

    /* Sum: '<S225>/Sum' incorporates:
     *  DiscreteIntegrator: '<S216>/Integrator'
     *  Gain: '<S221>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_2 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_hf) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S223>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_2' */
      rtY.SPD_OUT_CH1_2 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_2' */
      rtY.SPD_OUT_CH1_2 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH1_2' */
      rtY.SPD_OUT_CH1_2 = u0;
    }

    /* End of Saturate: '<S223>/Saturation' */

    /* Update for DiscreteIntegrator: '<S211>/Filter' incorporates:
     *  DiscreteIntegrator: '<S216>/Integrator'
     *  Inport: '<Root>/reset_status1_2'
     */
    rtDW.Filter_DSTATE_d5 += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status1_2 > 0.0F) {
      rtDW.Filter_PrevResetState_o2 = 1;
      rtDW.Integrator_PrevResetState_ar = 1;
    } else {
      if (rtU.reset_status1_2 < 0.0F) {
        rtDW.Filter_PrevResetState_o2 = -1;
      } else if (rtU.reset_status1_2 == 0.0F) {
        rtDW.Filter_PrevResetState_o2 = 0;
      } else {
        rtDW.Filter_PrevResetState_o2 = 2;
      }

      if (rtU.reset_status1_2 < 0.0F) {
        rtDW.Integrator_PrevResetState_ar = -1;
      } else if (rtU.reset_status1_2 == 0.0F) {
        rtDW.Integrator_PrevResetState_ar = 0;
      } else {
        rtDW.Integrator_PrevResetState_ar = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S211>/Filter' */

    /* Update for DiscreteIntegrator: '<S216>/Integrator' incorporates:
     *  Gain: '<S213>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_hf += rtP.SPD_I_CH1_2 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S2>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S2>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S181>/Action Port'
     */
    /* Sum: '<S181>/Sum' incorporates:
     *  Gain: '<S181>/Gain'
     *  Inport: '<Root>/circle_CH1_2'
     *  Inport: '<Root>/ecd_CH1_2'
     *  Inport: '<Root>/target_CH1_2'
     *  Sum: '<S181>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH1_2 - (8191.0F * rtU.circle_CH1_2 +
      rtU.ecd_CH1_2);

    /* Abs: '<S181>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S181>/Switch2' incorporates:
     *  Constant: '<S181>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH1_2)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S181>/Switch2' */

    /* Gain: '<S322>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S314>/Filter'
     *  Gain: '<S312>/Derivative Gain'
     *  Sum: '<S314>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH1_2 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_kn) * 100.0F;

    /* Switch: '<S181>/Switch1' incorporates:
     *  Constant: '<S181>/Constant'
     *  Gain: '<S181>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_2'
     *  Saturate: '<S326>/Saturation'
     *  Sum: '<S181>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH1_2) {
      /* Sum: '<S328>/Sum' incorporates:
       *  DiscreteIntegrator: '<S319>/Integrator'
       *  Gain: '<S324>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_2 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_j0) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S326>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH1_2 * u0 - rtU.speed_rpm_CH1_2;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S181>/Switch1' */

    /* DiscreteIntegrator: '<S264>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_2'
     */
    if (((rtU.reset_status1_2 > 0.0F) && (rtDW.Filter_PrevResetState_a2 <= 0)) ||
        ((rtU.reset_status1_2 <= 0.0F) && (rtDW.Filter_PrevResetState_a2 == 1)))
    {
      rtDW.Filter_DSTATE_ne = 0.0F;
    }

    /* Gain: '<S272>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S264>/Filter'
     *  Gain: '<S262>/Derivative Gain'
     *  Sum: '<S264>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH1_2 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_ne) * 100.0F;

    /* DiscreteIntegrator: '<S269>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_2'
     */
    if (((rtU.reset_status1_2 > 0.0F) && (rtDW.Integrator_PrevResetState_d <= 0))
        || ((rtU.reset_status1_2 <= 0.0F) && (rtDW.Integrator_PrevResetState_d ==
          1))) {
      rtDW.Integrator_DSTATE_k1 = 0.0F;
    }

    /* Sum: '<S278>/Sum' incorporates:
     *  DiscreteIntegrator: '<S269>/Integrator'
     *  Gain: '<S274>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_2 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_k1) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S276>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_2' */
      rtY.ANG_OUT_CH1_2 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_2' */
      rtY.ANG_OUT_CH1_2 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH1_2' */
      rtY.ANG_OUT_CH1_2 = u0;
    }

    /* End of Saturate: '<S276>/Saturation' */

    /* Chart: '<S181>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_2'
     *  Inport: '<Root>/last_ecd_CH1_2'
     *  Sum: '<S181>/Sum3'
     */
    Chart1(rtU.ecd_CH1_2 - rtU.last_ecd_CH1_2, &rtDW.u2_jxj, &rtDW.sf_Chart1_m);

    /* Outport: '<Root>/circle_out_CH1_2' incorporates:
     *  Inport: '<Root>/circle_CH1_2'
     *  Sum: '<S181>/Sum4'
     */
    rtY.circle_out_CH1_2 = rtDW.u2_jxj + rtU.circle_CH1_2;

    /* Update for DiscreteIntegrator: '<S319>/Integrator' incorporates:
     *  Gain: '<S316>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_j0 += rtP.ANG_A_I_CH1_2 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S314>/Filter' */
    rtDW.Filter_DSTATE_kn += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S264>/Filter' incorporates:
     *  DiscreteIntegrator: '<S269>/Integrator'
     *  Inport: '<Root>/reset_status1_2'
     */
    rtDW.Filter_DSTATE_ne += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status1_2 > 0.0F) {
      rtDW.Filter_PrevResetState_a2 = 1;
      rtDW.Integrator_PrevResetState_d = 1;
    } else {
      if (rtU.reset_status1_2 < 0.0F) {
        rtDW.Filter_PrevResetState_a2 = -1;
      } else if (rtU.reset_status1_2 == 0.0F) {
        rtDW.Filter_PrevResetState_a2 = 0;
      } else {
        rtDW.Filter_PrevResetState_a2 = 2;
      }

      if (rtU.reset_status1_2 < 0.0F) {
        rtDW.Integrator_PrevResetState_d = -1;
      } else if (rtU.reset_status1_2 == 0.0F) {
        rtDW.Integrator_PrevResetState_d = 0;
      } else {
        rtDW.Integrator_PrevResetState_d = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S264>/Filter' */

    /* Update for DiscreteIntegrator: '<S269>/Integrator' incorporates:
     *  Gain: '<S266>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_k1 += rtP.ANG_S_I_CH1_2 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S2>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S2>/Switch Case' */

  /* SwitchCase: '<S3>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH1_3'
   */
  switch ((int32_T)rtU.status_CH1_3) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S3>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S336>/Action Port'
     */
    /* Sum: '<S336>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_3'
     *  Inport: '<Root>/target_CH1_3'
     */
    rtb_Switch2_ft = rtU.target_CH1_3 - rtU.speed_rpm_CH1_3;

    /* Switch: '<S336>/Switch2' incorporates:
     *  Abs: '<S336>/Abs'
     *  Constant: '<S336>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH1_3)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S336>/Switch2' */

    /* DiscreteIntegrator: '<S367>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_3'
     */
    if (((rtU.reset_status1_3 > 0.0F) && (rtDW.Filter_PrevResetState_pr <= 0)) ||
        ((rtU.reset_status1_3 <= 0.0F) && (rtDW.Filter_PrevResetState_pr == 1)))
    {
      rtDW.Filter_DSTATE_hj = 0.0F;
    }

    /* Gain: '<S375>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S367>/Filter'
     *  Gain: '<S365>/Derivative Gain'
     *  Sum: '<S367>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH1_3 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_hj) * 100.0F;

    /* DiscreteIntegrator: '<S372>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_3'
     */
    if (((rtU.reset_status1_3 > 0.0F) && (rtDW.Integrator_PrevResetState_g1 <= 0))
        || ((rtU.reset_status1_3 <= 0.0F) && (rtDW.Integrator_PrevResetState_g1 ==
          1))) {
      rtDW.Integrator_DSTATE_cx = 0.0F;
    }

    /* Sum: '<S381>/Sum' incorporates:
     *  DiscreteIntegrator: '<S372>/Integrator'
     *  Gain: '<S377>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_3 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_cx) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S379>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_3' */
      rtY.SPD_OUT_CH1_3 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_3' */
      rtY.SPD_OUT_CH1_3 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH1_3' */
      rtY.SPD_OUT_CH1_3 = u0;
    }

    /* End of Saturate: '<S379>/Saturation' */

    /* Update for DiscreteIntegrator: '<S367>/Filter' incorporates:
     *  DiscreteIntegrator: '<S372>/Integrator'
     *  Inport: '<Root>/reset_status1_3'
     */
    rtDW.Filter_DSTATE_hj += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status1_3 > 0.0F) {
      rtDW.Filter_PrevResetState_pr = 1;
      rtDW.Integrator_PrevResetState_g1 = 1;
    } else {
      if (rtU.reset_status1_3 < 0.0F) {
        rtDW.Filter_PrevResetState_pr = -1;
      } else if (rtU.reset_status1_3 == 0.0F) {
        rtDW.Filter_PrevResetState_pr = 0;
      } else {
        rtDW.Filter_PrevResetState_pr = 2;
      }

      if (rtU.reset_status1_3 < 0.0F) {
        rtDW.Integrator_PrevResetState_g1 = -1;
      } else if (rtU.reset_status1_3 == 0.0F) {
        rtDW.Integrator_PrevResetState_g1 = 0;
      } else {
        rtDW.Integrator_PrevResetState_g1 = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S367>/Filter' */

    /* Update for DiscreteIntegrator: '<S372>/Integrator' incorporates:
     *  Gain: '<S369>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_cx += rtP.SPD_I_CH1_3 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S3>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S3>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S337>/Action Port'
     */
    /* Sum: '<S337>/Sum' incorporates:
     *  Gain: '<S337>/Gain'
     *  Inport: '<Root>/circle_CH1_3'
     *  Inport: '<Root>/ecd_CH1_3'
     *  Inport: '<Root>/target_CH1_3'
     *  Sum: '<S337>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH1_3 - (8191.0F * rtU.circle_CH1_3 +
      rtU.ecd_CH1_3);

    /* Abs: '<S337>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S337>/Switch2' incorporates:
     *  Constant: '<S337>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH1_3)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S337>/Switch2' */

    /* Gain: '<S478>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S470>/Filter'
     *  Gain: '<S468>/Derivative Gain'
     *  Sum: '<S470>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH1_3 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_gs) * 100.0F;

    /* Switch: '<S337>/Switch1' incorporates:
     *  Constant: '<S337>/Constant'
     *  Gain: '<S337>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_3'
     *  Saturate: '<S482>/Saturation'
     *  Sum: '<S337>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH1_3) {
      /* Sum: '<S484>/Sum' incorporates:
       *  DiscreteIntegrator: '<S475>/Integrator'
       *  Gain: '<S480>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_3 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_ik) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S482>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH1_3 * u0 - rtU.speed_rpm_CH1_3;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S337>/Switch1' */

    /* DiscreteIntegrator: '<S420>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_3'
     */
    if (((rtU.reset_status1_3 > 0.0F) && (rtDW.Filter_PrevResetState_na <= 0)) ||
        ((rtU.reset_status1_3 <= 0.0F) && (rtDW.Filter_PrevResetState_na == 1)))
    {
      rtDW.Filter_DSTATE_f53 = 0.0F;
    }

    /* Gain: '<S428>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S420>/Filter'
     *  Gain: '<S418>/Derivative Gain'
     *  Sum: '<S420>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH1_3 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_f53) * 100.0F;

    /* DiscreteIntegrator: '<S425>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_3'
     */
    if (((rtU.reset_status1_3 > 0.0F) && (rtDW.Integrator_PrevResetState_pi <= 0))
        || ((rtU.reset_status1_3 <= 0.0F) && (rtDW.Integrator_PrevResetState_pi ==
          1))) {
      rtDW.Integrator_DSTATE_l3w = 0.0F;
    }

    /* Sum: '<S434>/Sum' incorporates:
     *  DiscreteIntegrator: '<S425>/Integrator'
     *  Gain: '<S430>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_3 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_l3w) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S432>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_3' */
      rtY.ANG_OUT_CH1_3 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_3' */
      rtY.ANG_OUT_CH1_3 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH1_3' */
      rtY.ANG_OUT_CH1_3 = u0;
    }

    /* End of Saturate: '<S432>/Saturation' */

    /* Chart: '<S337>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_3'
     *  Inport: '<Root>/last_ecd_CH1_3'
     *  Sum: '<S337>/Sum3'
     */
    Chart1(rtU.ecd_CH1_3 - rtU.last_ecd_CH1_3, &rtDW.u2_j2, &rtDW.sf_Chart1_h);

    /* Outport: '<Root>/circle_out_CH1_3' incorporates:
     *  Inport: '<Root>/circle_CH1_3'
     *  Sum: '<S337>/Sum4'
     */
    rtY.circle_out_CH1_3 = rtDW.u2_j2 + rtU.circle_CH1_3;

    /* Update for DiscreteIntegrator: '<S475>/Integrator' incorporates:
     *  Gain: '<S472>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ik += rtP.ANG_A_I_CH1_3 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S470>/Filter' */
    rtDW.Filter_DSTATE_gs += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S420>/Filter' incorporates:
     *  DiscreteIntegrator: '<S425>/Integrator'
     *  Inport: '<Root>/reset_status1_3'
     */
    rtDW.Filter_DSTATE_f53 += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status1_3 > 0.0F) {
      rtDW.Filter_PrevResetState_na = 1;
      rtDW.Integrator_PrevResetState_pi = 1;
    } else {
      if (rtU.reset_status1_3 < 0.0F) {
        rtDW.Filter_PrevResetState_na = -1;
      } else if (rtU.reset_status1_3 == 0.0F) {
        rtDW.Filter_PrevResetState_na = 0;
      } else {
        rtDW.Filter_PrevResetState_na = 2;
      }

      if (rtU.reset_status1_3 < 0.0F) {
        rtDW.Integrator_PrevResetState_pi = -1;
      } else if (rtU.reset_status1_3 == 0.0F) {
        rtDW.Integrator_PrevResetState_pi = 0;
      } else {
        rtDW.Integrator_PrevResetState_pi = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S420>/Filter' */

    /* Update for DiscreteIntegrator: '<S425>/Integrator' incorporates:
     *  Gain: '<S422>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_l3w += rtP.ANG_S_I_CH1_3 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S3>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S3>/Switch Case' */

  /* SwitchCase: '<S4>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH1_4'
   */
  switch ((int32_T)rtU.status_CH1_4) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S4>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S492>/Action Port'
     */
    /* Sum: '<S492>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_4'
     *  Inport: '<Root>/target_CH1_4'
     */
    rtb_Switch2_ft = rtU.target_CH1_4 - rtU.speed_rpm_CH1_4;

    /* Switch: '<S492>/Switch2' incorporates:
     *  Abs: '<S492>/Abs'
     *  Constant: '<S492>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH1_4)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S492>/Switch2' */

    /* DiscreteIntegrator: '<S523>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_4'
     */
    if (((rtU.reset_status1_4 > 0.0F) && (rtDW.Filter_PrevResetState_pt <= 0)) ||
        ((rtU.reset_status1_4 <= 0.0F) && (rtDW.Filter_PrevResetState_pt == 1)))
    {
      rtDW.Filter_DSTATE_gr = 0.0F;
    }

    /* Gain: '<S531>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S523>/Filter'
     *  Gain: '<S521>/Derivative Gain'
     *  Sum: '<S523>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH1_4 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_gr) * 100.0F;

    /* DiscreteIntegrator: '<S528>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_4'
     */
    if (((rtU.reset_status1_4 > 0.0F) && (rtDW.Integrator_PrevResetState_j3 <= 0))
        || ((rtU.reset_status1_4 <= 0.0F) && (rtDW.Integrator_PrevResetState_j3 ==
          1))) {
      rtDW.Integrator_DSTATE_c3 = 0.0F;
    }

    /* Sum: '<S537>/Sum' incorporates:
     *  DiscreteIntegrator: '<S528>/Integrator'
     *  Gain: '<S533>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_4 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_c3) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S535>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_4' */
      rtY.SPD_OUT_CH1_4 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_4' */
      rtY.SPD_OUT_CH1_4 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH1_4' */
      rtY.SPD_OUT_CH1_4 = u0;
    }

    /* End of Saturate: '<S535>/Saturation' */

    /* Update for DiscreteIntegrator: '<S523>/Filter' incorporates:
     *  DiscreteIntegrator: '<S528>/Integrator'
     *  Inport: '<Root>/reset_status1_4'
     */
    rtDW.Filter_DSTATE_gr += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status1_4 > 0.0F) {
      rtDW.Filter_PrevResetState_pt = 1;
      rtDW.Integrator_PrevResetState_j3 = 1;
    } else {
      if (rtU.reset_status1_4 < 0.0F) {
        rtDW.Filter_PrevResetState_pt = -1;
      } else if (rtU.reset_status1_4 == 0.0F) {
        rtDW.Filter_PrevResetState_pt = 0;
      } else {
        rtDW.Filter_PrevResetState_pt = 2;
      }

      if (rtU.reset_status1_4 < 0.0F) {
        rtDW.Integrator_PrevResetState_j3 = -1;
      } else if (rtU.reset_status1_4 == 0.0F) {
        rtDW.Integrator_PrevResetState_j3 = 0;
      } else {
        rtDW.Integrator_PrevResetState_j3 = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S523>/Filter' */

    /* Update for DiscreteIntegrator: '<S528>/Integrator' incorporates:
     *  Gain: '<S525>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_c3 += rtP.SPD_I_CH1_4 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S4>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S4>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S493>/Action Port'
     */
    /* Sum: '<S493>/Sum' incorporates:
     *  Gain: '<S493>/Gain'
     *  Inport: '<Root>/circle_CH1_4'
     *  Inport: '<Root>/ecd_CH1_4'
     *  Inport: '<Root>/target_CH1_4'
     *  Sum: '<S493>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH1_4 - (8191.0F * rtU.circle_CH1_4 +
      rtU.ecd_CH1_4);

    /* Abs: '<S493>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S493>/Switch2' incorporates:
     *  Constant: '<S493>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH1_4)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S493>/Switch2' */

    /* Gain: '<S634>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S626>/Filter'
     *  Gain: '<S624>/Derivative Gain'
     *  Sum: '<S626>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH1_4 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_m1s) * 100.0F;

    /* Switch: '<S493>/Switch1' incorporates:
     *  Constant: '<S493>/Constant'
     *  Gain: '<S493>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_4'
     *  Saturate: '<S638>/Saturation'
     *  Sum: '<S493>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH1_4) {
      /* Sum: '<S640>/Sum' incorporates:
       *  DiscreteIntegrator: '<S631>/Integrator'
       *  Gain: '<S636>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_4 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_jp) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S638>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH1_4 * u0 - rtU.speed_rpm_CH1_4;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S493>/Switch1' */

    /* DiscreteIntegrator: '<S576>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_4'
     */
    if (((rtU.reset_status1_4 > 0.0F) && (rtDW.Filter_PrevResetState_gs <= 0)) ||
        ((rtU.reset_status1_4 <= 0.0F) && (rtDW.Filter_PrevResetState_gs == 1)))
    {
      rtDW.Filter_DSTATE_lm = 0.0F;
    }

    /* Gain: '<S584>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S576>/Filter'
     *  Gain: '<S574>/Derivative Gain'
     *  Sum: '<S576>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH1_4 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_lm) * 100.0F;

    /* DiscreteIntegrator: '<S581>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_4'
     */
    if (((rtU.reset_status1_4 > 0.0F) && (rtDW.Integrator_PrevResetState_f <= 0))
        || ((rtU.reset_status1_4 <= 0.0F) && (rtDW.Integrator_PrevResetState_f ==
          1))) {
      rtDW.Integrator_DSTATE_nn = 0.0F;
    }

    /* Sum: '<S590>/Sum' incorporates:
     *  DiscreteIntegrator: '<S581>/Integrator'
     *  Gain: '<S586>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_4 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_nn) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S588>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_4' */
      rtY.ANG_OUT_CH1_4 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_4' */
      rtY.ANG_OUT_CH1_4 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH1_4' */
      rtY.ANG_OUT_CH1_4 = u0;
    }

    /* End of Saturate: '<S588>/Saturation' */

    /* Chart: '<S493>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_4'
     *  Inport: '<Root>/last_ecd_CH1_4'
     *  Sum: '<S493>/Sum3'
     */
    Chart1(rtU.ecd_CH1_4 - rtU.last_ecd_CH1_4, &rtDW.u2_a, &rtDW.sf_Chart1_d);

    /* Outport: '<Root>/circle_out_CH1_4' incorporates:
     *  Inport: '<Root>/circle_CH1_4'
     *  Sum: '<S493>/Sum4'
     */
    rtY.circle_out_CH1_4 = rtDW.u2_a + rtU.circle_CH1_4;

    /* Update for DiscreteIntegrator: '<S631>/Integrator' incorporates:
     *  Gain: '<S628>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_jp += rtP.ANG_A_I_CH1_4 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S626>/Filter' */
    rtDW.Filter_DSTATE_m1s += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S576>/Filter' incorporates:
     *  DiscreteIntegrator: '<S581>/Integrator'
     *  Inport: '<Root>/reset_status1_4'
     */
    rtDW.Filter_DSTATE_lm += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status1_4 > 0.0F) {
      rtDW.Filter_PrevResetState_gs = 1;
      rtDW.Integrator_PrevResetState_f = 1;
    } else {
      if (rtU.reset_status1_4 < 0.0F) {
        rtDW.Filter_PrevResetState_gs = -1;
      } else if (rtU.reset_status1_4 == 0.0F) {
        rtDW.Filter_PrevResetState_gs = 0;
      } else {
        rtDW.Filter_PrevResetState_gs = 2;
      }

      if (rtU.reset_status1_4 < 0.0F) {
        rtDW.Integrator_PrevResetState_f = -1;
      } else if (rtU.reset_status1_4 == 0.0F) {
        rtDW.Integrator_PrevResetState_f = 0;
      } else {
        rtDW.Integrator_PrevResetState_f = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S576>/Filter' */

    /* Update for DiscreteIntegrator: '<S581>/Integrator' incorporates:
     *  Gain: '<S578>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_nn += rtP.ANG_S_I_CH1_4 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S4>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S4>/Switch Case' */

  /* SwitchCase: '<S5>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH1_5'
   */
  switch ((int32_T)rtU.status_CH1_5) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S5>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S648>/Action Port'
     */
    /* Sum: '<S648>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_5'
     *  Inport: '<Root>/target_CH1_5'
     */
    rtb_Switch2_ft = rtU.target_CH1_5 - rtU.speed_rpm_CH1_5;

    /* Switch: '<S648>/Switch2' incorporates:
     *  Abs: '<S648>/Abs'
     *  Constant: '<S648>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH1_5)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S648>/Switch2' */

    /* DiscreteIntegrator: '<S679>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_5'
     */
    if (((rtU.reset_status1_5 > 0.0F) && (rtDW.Filter_PrevResetState_ds <= 0)) ||
        ((rtU.reset_status1_5 <= 0.0F) && (rtDW.Filter_PrevResetState_ds == 1)))
    {
      rtDW.Filter_DSTATE_eu = 0.0F;
    }

    /* Gain: '<S687>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S679>/Filter'
     *  Gain: '<S677>/Derivative Gain'
     *  Sum: '<S679>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH1_5 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_eu) * 100.0F;

    /* DiscreteIntegrator: '<S684>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_5'
     */
    if (((rtU.reset_status1_5 > 0.0F) && (rtDW.Integrator_PrevResetState_jx <= 0))
        || ((rtU.reset_status1_5 <= 0.0F) && (rtDW.Integrator_PrevResetState_jx ==
          1))) {
      rtDW.Integrator_DSTATE_kt = 0.0F;
    }

    /* Sum: '<S693>/Sum' incorporates:
     *  DiscreteIntegrator: '<S684>/Integrator'
     *  Gain: '<S689>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_5 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_kt) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S691>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_5' */
      rtY.SPD_OUT_CH1_5 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_5' */
      rtY.SPD_OUT_CH1_5 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH1_5' */
      rtY.SPD_OUT_CH1_5 = u0;
    }

    /* End of Saturate: '<S691>/Saturation' */

    /* Update for DiscreteIntegrator: '<S679>/Filter' incorporates:
     *  DiscreteIntegrator: '<S684>/Integrator'
     *  Inport: '<Root>/reset_status1_5'
     */
    rtDW.Filter_DSTATE_eu += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status1_5 > 0.0F) {
      rtDW.Filter_PrevResetState_ds = 1;
      rtDW.Integrator_PrevResetState_jx = 1;
    } else {
      if (rtU.reset_status1_5 < 0.0F) {
        rtDW.Filter_PrevResetState_ds = -1;
      } else if (rtU.reset_status1_5 == 0.0F) {
        rtDW.Filter_PrevResetState_ds = 0;
      } else {
        rtDW.Filter_PrevResetState_ds = 2;
      }

      if (rtU.reset_status1_5 < 0.0F) {
        rtDW.Integrator_PrevResetState_jx = -1;
      } else if (rtU.reset_status1_5 == 0.0F) {
        rtDW.Integrator_PrevResetState_jx = 0;
      } else {
        rtDW.Integrator_PrevResetState_jx = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S679>/Filter' */

    /* Update for DiscreteIntegrator: '<S684>/Integrator' incorporates:
     *  Gain: '<S681>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_kt += rtP.SPD_I_CH1_5 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S5>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S5>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S649>/Action Port'
     */
    /* Sum: '<S649>/Sum' incorporates:
     *  Gain: '<S649>/Gain'
     *  Inport: '<Root>/circle_CH1_5'
     *  Inport: '<Root>/ecd_CH1_5'
     *  Inport: '<Root>/target_CH1_5'
     *  Sum: '<S649>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH1_5 - (8191.0F * rtU.circle_CH1_5 +
      rtU.ecd_CH1_5);

    /* Abs: '<S649>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S649>/Switch2' incorporates:
     *  Constant: '<S649>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH1_5)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S649>/Switch2' */

    /* Gain: '<S790>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S782>/Filter'
     *  Gain: '<S780>/Derivative Gain'
     *  Sum: '<S782>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH1_5 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_nq) * 100.0F;

    /* Switch: '<S649>/Switch1' incorporates:
     *  Constant: '<S649>/Constant'
     *  Gain: '<S649>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_5'
     *  Saturate: '<S794>/Saturation'
     *  Sum: '<S649>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH1_5) {
      /* Sum: '<S796>/Sum' incorporates:
       *  DiscreteIntegrator: '<S787>/Integrator'
       *  Gain: '<S792>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_5 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_gp) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S794>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH1_5 * u0 - rtU.speed_rpm_CH1_5;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S649>/Switch1' */

    /* DiscreteIntegrator: '<S732>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_5'
     */
    if (((rtU.reset_status1_5 > 0.0F) && (rtDW.Filter_PrevResetState_k <= 0)) ||
        ((rtU.reset_status1_5 <= 0.0F) && (rtDW.Filter_PrevResetState_k == 1)))
    {
      rtDW.Filter_DSTATE_day = 0.0F;
    }

    /* Gain: '<S740>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S732>/Filter'
     *  Gain: '<S730>/Derivative Gain'
     *  Sum: '<S732>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH1_5 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_day) * 100.0F;

    /* DiscreteIntegrator: '<S737>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_5'
     */
    if (((rtU.reset_status1_5 > 0.0F) && (rtDW.Integrator_PrevResetState_a2 <= 0))
        || ((rtU.reset_status1_5 <= 0.0F) && (rtDW.Integrator_PrevResetState_a2 ==
          1))) {
      rtDW.Integrator_DSTATE_ih = 0.0F;
    }

    /* Sum: '<S746>/Sum' incorporates:
     *  DiscreteIntegrator: '<S737>/Integrator'
     *  Gain: '<S742>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_5 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_ih) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S744>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_5' */
      rtY.ANG_OUT_CH1_5 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_5' */
      rtY.ANG_OUT_CH1_5 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH1_5' */
      rtY.ANG_OUT_CH1_5 = u0;
    }

    /* End of Saturate: '<S744>/Saturation' */

    /* Chart: '<S649>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_5'
     *  Inport: '<Root>/last_ecd_CH1_5'
     *  Sum: '<S649>/Sum3'
     */
    Chart1(rtU.ecd_CH1_5 - rtU.last_ecd_CH1_5, &rtDW.u2_c, &rtDW.sf_Chart1_p);

    /* Outport: '<Root>/circle_out_CH1_5' incorporates:
     *  Inport: '<Root>/circle_CH1_5'
     *  Sum: '<S649>/Sum4'
     */
    rtY.circle_out_CH1_5 = rtDW.u2_c + rtU.circle_CH1_5;

    /* Update for DiscreteIntegrator: '<S787>/Integrator' incorporates:
     *  Gain: '<S784>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_gp += rtP.ANG_A_I_CH1_5 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S782>/Filter' */
    rtDW.Filter_DSTATE_nq += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S732>/Filter' incorporates:
     *  DiscreteIntegrator: '<S737>/Integrator'
     *  Inport: '<Root>/reset_status1_5'
     */
    rtDW.Filter_DSTATE_day += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status1_5 > 0.0F) {
      rtDW.Filter_PrevResetState_k = 1;
      rtDW.Integrator_PrevResetState_a2 = 1;
    } else {
      if (rtU.reset_status1_5 < 0.0F) {
        rtDW.Filter_PrevResetState_k = -1;
      } else if (rtU.reset_status1_5 == 0.0F) {
        rtDW.Filter_PrevResetState_k = 0;
      } else {
        rtDW.Filter_PrevResetState_k = 2;
      }

      if (rtU.reset_status1_5 < 0.0F) {
        rtDW.Integrator_PrevResetState_a2 = -1;
      } else if (rtU.reset_status1_5 == 0.0F) {
        rtDW.Integrator_PrevResetState_a2 = 0;
      } else {
        rtDW.Integrator_PrevResetState_a2 = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S732>/Filter' */

    /* Update for DiscreteIntegrator: '<S737>/Integrator' incorporates:
     *  Gain: '<S734>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ih += rtP.ANG_S_I_CH1_5 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S5>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S5>/Switch Case' */

  /* SwitchCase: '<S6>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH1_6'
   */
  switch ((int32_T)rtU.status_CH1_6) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S6>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S804>/Action Port'
     */
    /* Sum: '<S804>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_6'
     *  Inport: '<Root>/target_CH1_6'
     */
    rtb_Switch2_ft = rtU.target_CH1_6 - rtU.speed_rpm_CH1_6;

    /* Switch: '<S804>/Switch2' incorporates:
     *  Abs: '<S804>/Abs'
     *  Constant: '<S804>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH1_6)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S804>/Switch2' */

    /* DiscreteIntegrator: '<S835>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_6'
     */
    if (((rtU.reset_status1_6 > 0.0F) && (rtDW.Filter_PrevResetState_i <= 0)) ||
        ((rtU.reset_status1_6 <= 0.0F) && (rtDW.Filter_PrevResetState_i == 1)))
    {
      rtDW.Filter_DSTATE_a5 = 0.0F;
    }

    /* Gain: '<S843>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S835>/Filter'
     *  Gain: '<S833>/Derivative Gain'
     *  Sum: '<S835>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH1_6 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_a5) * 100.0F;

    /* DiscreteIntegrator: '<S840>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_6'
     */
    if (((rtU.reset_status1_6 > 0.0F) && (rtDW.Integrator_PrevResetState_nb <= 0))
        || ((rtU.reset_status1_6 <= 0.0F) && (rtDW.Integrator_PrevResetState_nb ==
          1))) {
      rtDW.Integrator_DSTATE_pw = 0.0F;
    }

    /* Sum: '<S849>/Sum' incorporates:
     *  DiscreteIntegrator: '<S840>/Integrator'
     *  Gain: '<S845>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_6 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_pw) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S847>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_6' */
      rtY.SPD_OUT_CH1_6 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_6' */
      rtY.SPD_OUT_CH1_6 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH1_6' */
      rtY.SPD_OUT_CH1_6 = u0;
    }

    /* End of Saturate: '<S847>/Saturation' */

    /* Update for DiscreteIntegrator: '<S835>/Filter' incorporates:
     *  DiscreteIntegrator: '<S840>/Integrator'
     *  Inport: '<Root>/reset_status1_6'
     */
    rtDW.Filter_DSTATE_a5 += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status1_6 > 0.0F) {
      rtDW.Filter_PrevResetState_i = 1;
      rtDW.Integrator_PrevResetState_nb = 1;
    } else {
      if (rtU.reset_status1_6 < 0.0F) {
        rtDW.Filter_PrevResetState_i = -1;
      } else if (rtU.reset_status1_6 == 0.0F) {
        rtDW.Filter_PrevResetState_i = 0;
      } else {
        rtDW.Filter_PrevResetState_i = 2;
      }

      if (rtU.reset_status1_6 < 0.0F) {
        rtDW.Integrator_PrevResetState_nb = -1;
      } else if (rtU.reset_status1_6 == 0.0F) {
        rtDW.Integrator_PrevResetState_nb = 0;
      } else {
        rtDW.Integrator_PrevResetState_nb = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S835>/Filter' */

    /* Update for DiscreteIntegrator: '<S840>/Integrator' incorporates:
     *  Gain: '<S837>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_pw += rtP.SPD_I_CH1_6 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S6>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S6>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S805>/Action Port'
     */
    /* Sum: '<S805>/Sum' incorporates:
     *  Gain: '<S805>/Gain'
     *  Inport: '<Root>/circle_CH1_6'
     *  Inport: '<Root>/ecd_CH1_6'
     *  Inport: '<Root>/target_CH1_6'
     *  Sum: '<S805>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH1_6 - (8191.0F * rtU.circle_CH1_6 +
      rtU.ecd_CH1_6);

    /* Abs: '<S805>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S805>/Switch2' incorporates:
     *  Constant: '<S805>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH1_6)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S805>/Switch2' */

    /* Gain: '<S946>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S938>/Filter'
     *  Gain: '<S936>/Derivative Gain'
     *  Sum: '<S938>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH1_6 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_pn) * 100.0F;

    /* Switch: '<S805>/Switch1' incorporates:
     *  Constant: '<S805>/Constant'
     *  Gain: '<S805>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_6'
     *  Saturate: '<S950>/Saturation'
     *  Sum: '<S805>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH1_6) {
      /* Sum: '<S952>/Sum' incorporates:
       *  DiscreteIntegrator: '<S943>/Integrator'
       *  Gain: '<S948>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_6 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_mf) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S950>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH1_6 * u0 - rtU.speed_rpm_CH1_6;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S805>/Switch1' */

    /* DiscreteIntegrator: '<S888>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_6'
     */
    if (((rtU.reset_status1_6 > 0.0F) && (rtDW.Filter_PrevResetState_lp <= 0)) ||
        ((rtU.reset_status1_6 <= 0.0F) && (rtDW.Filter_PrevResetState_lp == 1)))
    {
      rtDW.Filter_DSTATE_da = 0.0F;
    }

    /* Gain: '<S896>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S888>/Filter'
     *  Gain: '<S886>/Derivative Gain'
     *  Sum: '<S888>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH1_6 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_da) * 100.0F;

    /* DiscreteIntegrator: '<S893>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_6'
     */
    if (((rtU.reset_status1_6 > 0.0F) && (rtDW.Integrator_PrevResetState_j <= 0))
        || ((rtU.reset_status1_6 <= 0.0F) && (rtDW.Integrator_PrevResetState_j ==
          1))) {
      rtDW.Integrator_DSTATE_oo = 0.0F;
    }

    /* Sum: '<S902>/Sum' incorporates:
     *  DiscreteIntegrator: '<S893>/Integrator'
     *  Gain: '<S898>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_6 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_oo) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S900>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_6' */
      rtY.ANG_OUT_CH1_6 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_6' */
      rtY.ANG_OUT_CH1_6 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH1_6' */
      rtY.ANG_OUT_CH1_6 = u0;
    }

    /* End of Saturate: '<S900>/Saturation' */

    /* Chart: '<S805>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_6'
     *  Inport: '<Root>/last_ecd_CH1_6'
     *  Sum: '<S805>/Sum3'
     */
    Chart1(rtU.ecd_CH1_6 - rtU.last_ecd_CH1_6, &rtDW.u2_nn, &rtDW.sf_Chart1_j);

    /* Outport: '<Root>/circle_out_CH1_6' incorporates:
     *  Inport: '<Root>/circle_CH1_6'
     *  Sum: '<S805>/Sum4'
     */
    rtY.circle_out_CH1_6 = rtDW.u2_nn + rtU.circle_CH1_6;

    /* Update for DiscreteIntegrator: '<S943>/Integrator' incorporates:
     *  Gain: '<S940>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_mf += rtP.ANG_A_I_CH1_6 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S938>/Filter' */
    rtDW.Filter_DSTATE_pn += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S888>/Filter' incorporates:
     *  DiscreteIntegrator: '<S893>/Integrator'
     *  Inport: '<Root>/reset_status1_6'
     */
    rtDW.Filter_DSTATE_da += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status1_6 > 0.0F) {
      rtDW.Filter_PrevResetState_lp = 1;
      rtDW.Integrator_PrevResetState_j = 1;
    } else {
      if (rtU.reset_status1_6 < 0.0F) {
        rtDW.Filter_PrevResetState_lp = -1;
      } else if (rtU.reset_status1_6 == 0.0F) {
        rtDW.Filter_PrevResetState_lp = 0;
      } else {
        rtDW.Filter_PrevResetState_lp = 2;
      }

      if (rtU.reset_status1_6 < 0.0F) {
        rtDW.Integrator_PrevResetState_j = -1;
      } else if (rtU.reset_status1_6 == 0.0F) {
        rtDW.Integrator_PrevResetState_j = 0;
      } else {
        rtDW.Integrator_PrevResetState_j = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S888>/Filter' */

    /* Update for DiscreteIntegrator: '<S893>/Integrator' incorporates:
     *  Gain: '<S890>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_oo += rtP.ANG_S_I_CH1_6 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S6>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S6>/Switch Case' */

  /* SwitchCase: '<S7>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH1_7'
   */
  switch ((int32_T)rtU.status_CH1_7) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S7>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S960>/Action Port'
     */
    /* Sum: '<S960>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_7'
     *  Inport: '<Root>/target_CH1_7'
     */
    rtb_Switch2_ft = rtU.target_CH1_7 - rtU.speed_rpm_CH1_7;

    /* Switch: '<S960>/Switch2' incorporates:
     *  Abs: '<S960>/Abs'
     *  Constant: '<S960>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH1_7)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S960>/Switch2' */

    /* DiscreteIntegrator: '<S991>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_7'
     */
    if (((rtU.reset_status1_7 > 0.0F) && (rtDW.Filter_PrevResetState_am <= 0)) ||
        ((rtU.reset_status1_7 <= 0.0F) && (rtDW.Filter_PrevResetState_am == 1)))
    {
      rtDW.Filter_DSTATE_nc = 0.0F;
    }

    /* Gain: '<S999>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S991>/Filter'
     *  Gain: '<S989>/Derivative Gain'
     *  Sum: '<S991>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH1_7 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_nc) * 100.0F;

    /* DiscreteIntegrator: '<S996>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_7'
     */
    if (((rtU.reset_status1_7 > 0.0F) && (rtDW.Integrator_PrevResetState_ed <= 0))
        || ((rtU.reset_status1_7 <= 0.0F) && (rtDW.Integrator_PrevResetState_ed ==
          1))) {
      rtDW.Integrator_DSTATE_gt = 0.0F;
    }

    /* Sum: '<S1005>/Sum' incorporates:
     *  DiscreteIntegrator: '<S996>/Integrator'
     *  Gain: '<S1001>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_7 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_gt) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S1003>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_7' */
      rtY.SPD_OUT_CH1_7 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH1_7' */
      rtY.SPD_OUT_CH1_7 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH1_7' */
      rtY.SPD_OUT_CH1_7 = u0;
    }

    /* End of Saturate: '<S1003>/Saturation' */

    /* Update for DiscreteIntegrator: '<S991>/Filter' incorporates:
     *  DiscreteIntegrator: '<S996>/Integrator'
     *  Inport: '<Root>/reset_status1_7'
     */
    rtDW.Filter_DSTATE_nc += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status1_7 > 0.0F) {
      rtDW.Filter_PrevResetState_am = 1;
      rtDW.Integrator_PrevResetState_ed = 1;
    } else {
      if (rtU.reset_status1_7 < 0.0F) {
        rtDW.Filter_PrevResetState_am = -1;
      } else if (rtU.reset_status1_7 == 0.0F) {
        rtDW.Filter_PrevResetState_am = 0;
      } else {
        rtDW.Filter_PrevResetState_am = 2;
      }

      if (rtU.reset_status1_7 < 0.0F) {
        rtDW.Integrator_PrevResetState_ed = -1;
      } else if (rtU.reset_status1_7 == 0.0F) {
        rtDW.Integrator_PrevResetState_ed = 0;
      } else {
        rtDW.Integrator_PrevResetState_ed = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S991>/Filter' */

    /* Update for DiscreteIntegrator: '<S996>/Integrator' incorporates:
     *  Gain: '<S993>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_gt += rtP.SPD_I_CH1_7 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S7>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S7>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S961>/Action Port'
     */
    /* Sum: '<S961>/Sum' incorporates:
     *  Gain: '<S961>/Gain'
     *  Inport: '<Root>/circle_CH1_7'
     *  Inport: '<Root>/ecd_CH1_7'
     *  Inport: '<Root>/target_CH1_7'
     *  Sum: '<S961>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH1_7 - (8191.0F * rtU.circle_CH1_7 +
      rtU.ecd_CH1_7);

    /* Abs: '<S961>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S961>/Switch2' incorporates:
     *  Constant: '<S961>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH1_7)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S961>/Switch2' */

    /* Gain: '<S1102>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1094>/Filter'
     *  Gain: '<S1092>/Derivative Gain'
     *  Sum: '<S1094>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH1_7 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_hk) * 100.0F;

    /* Switch: '<S961>/Switch1' incorporates:
     *  Constant: '<S961>/Constant'
     *  Gain: '<S961>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_7'
     *  Saturate: '<S1106>/Saturation'
     *  Sum: '<S961>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH1_7) {
      /* Sum: '<S1108>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1099>/Integrator'
       *  Gain: '<S1104>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_7 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_g) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S1106>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH1_7 * u0 - rtU.speed_rpm_CH1_7;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S961>/Switch1' */

    /* DiscreteIntegrator: '<S1044>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_7'
     */
    if (((rtU.reset_status1_7 > 0.0F) && (rtDW.Filter_PrevResetState_nc <= 0)) ||
        ((rtU.reset_status1_7 <= 0.0F) && (rtDW.Filter_PrevResetState_nc == 1)))
    {
      rtDW.Filter_DSTATE_ax = 0.0F;
    }

    /* Gain: '<S1052>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1044>/Filter'
     *  Gain: '<S1042>/Derivative Gain'
     *  Sum: '<S1044>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH1_7 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_ax) * 100.0F;

    /* DiscreteIntegrator: '<S1049>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_7'
     */
    if (((rtU.reset_status1_7 > 0.0F) && (rtDW.Integrator_PrevResetState_gr <= 0))
        || ((rtU.reset_status1_7 <= 0.0F) && (rtDW.Integrator_PrevResetState_gr ==
          1))) {
      rtDW.Integrator_DSTATE_jo = 0.0F;
    }

    /* Sum: '<S1058>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1049>/Integrator'
     *  Gain: '<S1054>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_7 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_jo) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S1056>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_7' */
      rtY.ANG_OUT_CH1_7 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH1_7' */
      rtY.ANG_OUT_CH1_7 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH1_7' */
      rtY.ANG_OUT_CH1_7 = u0;
    }

    /* End of Saturate: '<S1056>/Saturation' */

    /* Chart: '<S961>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_7'
     *  Inport: '<Root>/last_ecd_CH1_7'
     *  Sum: '<S961>/Sum3'
     */
    Chart1(rtU.ecd_CH1_7 - rtU.last_ecd_CH1_7, &rtDW.u2_f4, &rtDW.sf_Chart1_o);

    /* Outport: '<Root>/circle_out_CH1_7' incorporates:
     *  Inport: '<Root>/circle_CH1_7'
     *  Sum: '<S961>/Sum4'
     */
    rtY.circle_out_CH1_7 = rtDW.u2_f4 + rtU.circle_CH1_7;

    /* Update for DiscreteIntegrator: '<S1099>/Integrator' incorporates:
     *  Gain: '<S1096>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_g += rtP.ANG_A_I_CH1_7 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1094>/Filter' */
    rtDW.Filter_DSTATE_hk += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S1044>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1049>/Integrator'
     *  Inport: '<Root>/reset_status1_7'
     */
    rtDW.Filter_DSTATE_ax += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status1_7 > 0.0F) {
      rtDW.Filter_PrevResetState_nc = 1;
      rtDW.Integrator_PrevResetState_gr = 1;
    } else {
      if (rtU.reset_status1_7 < 0.0F) {
        rtDW.Filter_PrevResetState_nc = -1;
      } else if (rtU.reset_status1_7 == 0.0F) {
        rtDW.Filter_PrevResetState_nc = 0;
      } else {
        rtDW.Filter_PrevResetState_nc = 2;
      }

      if (rtU.reset_status1_7 < 0.0F) {
        rtDW.Integrator_PrevResetState_gr = -1;
      } else if (rtU.reset_status1_7 == 0.0F) {
        rtDW.Integrator_PrevResetState_gr = 0;
      } else {
        rtDW.Integrator_PrevResetState_gr = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1044>/Filter' */

    /* Update for DiscreteIntegrator: '<S1049>/Integrator' incorporates:
     *  Gain: '<S1046>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_jo += rtP.ANG_S_I_CH1_7 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S7>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S7>/Switch Case' */

  /* SwitchCase: '<S12>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH2_5'
   */
  switch ((int32_T)rtU.status_CH2_5) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S12>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1740>/Action Port'
     */
    /* Sum: '<S1740>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_5'
     *  Inport: '<Root>/target_CH2_5'
     */
    rtb_Switch2_ft = rtU.target_CH2_5 - rtU.speed_rpm_CH2_5;

    /* Switch: '<S1740>/Switch2' incorporates:
     *  Abs: '<S1740>/Abs'
     *  Constant: '<S1740>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH2_5)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S1740>/Switch2' */

    /* DiscreteIntegrator: '<S1771>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_5'
     */
    if (((rtU.reset_status2_5 > 0.0F) && (rtDW.Filter_PrevResetState_n <= 0)) ||
        ((rtU.reset_status2_5 <= 0.0F) && (rtDW.Filter_PrevResetState_n == 1)))
    {
      rtDW.Filter_DSTATE_ke = 0.0F;
    }

    /* Gain: '<S1779>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1771>/Filter'
     *  Gain: '<S1769>/Derivative Gain'
     *  Sum: '<S1771>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH2_5 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_ke) * 100.0F;

    /* DiscreteIntegrator: '<S1776>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_5'
     */
    if (((rtU.reset_status2_5 > 0.0F) && (rtDW.Integrator_PrevResetState_km <= 0))
        || ((rtU.reset_status2_5 <= 0.0F) && (rtDW.Integrator_PrevResetState_km ==
          1))) {
      rtDW.Integrator_DSTATE_hq = 0.0F;
    }

    /* Sum: '<S1785>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1776>/Integrator'
     *  Gain: '<S1781>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_5 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_hq) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S1783>/Saturation' */
    if (u0 > 30000.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_5' */
      rtY.SPD_OUT_CH2_5 = 30000.0F;
    } else if (u0 < -30000.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_5' */
      rtY.SPD_OUT_CH2_5 = -30000.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH2_5' */
      rtY.SPD_OUT_CH2_5 = u0;
    }

    /* End of Saturate: '<S1783>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1771>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1776>/Integrator'
     *  Inport: '<Root>/reset_status2_5'
     */
    rtDW.Filter_DSTATE_ke += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status2_5 > 0.0F) {
      rtDW.Filter_PrevResetState_n = 1;
      rtDW.Integrator_PrevResetState_km = 1;
    } else {
      if (rtU.reset_status2_5 < 0.0F) {
        rtDW.Filter_PrevResetState_n = -1;
      } else if (rtU.reset_status2_5 == 0.0F) {
        rtDW.Filter_PrevResetState_n = 0;
      } else {
        rtDW.Filter_PrevResetState_n = 2;
      }

      if (rtU.reset_status2_5 < 0.0F) {
        rtDW.Integrator_PrevResetState_km = -1;
      } else if (rtU.reset_status2_5 == 0.0F) {
        rtDW.Integrator_PrevResetState_km = 0;
      } else {
        rtDW.Integrator_PrevResetState_km = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1771>/Filter' */

    /* Update for DiscreteIntegrator: '<S1776>/Integrator' incorporates:
     *  Gain: '<S1773>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_hq += rtP.SPD_I_CH2_5 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S12>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S12>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1741>/Action Port'
     */
    /* Sum: '<S1741>/Sum' incorporates:
     *  Gain: '<S1741>/Gain'
     *  Inport: '<Root>/circle_CH2_5'
     *  Inport: '<Root>/ecd_CH2_5'
     *  Inport: '<Root>/target_CH2_5'
     *  Sum: '<S1741>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH2_5 - (8191.0F * rtU.circle_CH2_5 +
      rtU.ecd_CH2_5);

    /* Abs: '<S1741>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S1741>/Switch2' incorporates:
     *  Constant: '<S1741>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH2_5)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S1741>/Switch2' */

    /* Gain: '<S1882>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1874>/Filter'
     *  Gain: '<S1872>/Derivative Gain'
     *  Sum: '<S1874>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH2_5 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_o0) * 100.0F;

    /* Switch: '<S1741>/Switch1' incorporates:
     *  Constant: '<S1741>/Constant'
     *  Gain: '<S1741>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_5'
     *  Saturate: '<S1886>/Saturation'
     *  Sum: '<S1741>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH2_5) {
      /* Sum: '<S1888>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1879>/Integrator'
       *  Gain: '<S1884>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_5 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_oq) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S1886>/Saturation' */
      if (u0 > 30000.0F) {
        u0 = 30000.0F;
      } else if (u0 < -30000.0F) {
        u0 = -30000.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH2_5 * u0 - rtU.speed_rpm_CH2_5;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S1741>/Switch1' */

    /* DiscreteIntegrator: '<S1824>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_5'
     */
    if (((rtU.reset_status2_5 > 0.0F) && (rtDW.Filter_PrevResetState_f3 <= 0)) ||
        ((rtU.reset_status2_5 <= 0.0F) && (rtDW.Filter_PrevResetState_f3 == 1)))
    {
      rtDW.Filter_DSTATE_ln = 0.0F;
    }

    /* Gain: '<S1832>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1824>/Filter'
     *  Gain: '<S1822>/Derivative Gain'
     *  Sum: '<S1824>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH2_5 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_ln) * 100.0F;

    /* DiscreteIntegrator: '<S1829>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_5'
     */
    if (((rtU.reset_status2_5 > 0.0F) && (rtDW.Integrator_PrevResetState_bs <= 0))
        || ((rtU.reset_status2_5 <= 0.0F) && (rtDW.Integrator_PrevResetState_bs ==
          1))) {
      rtDW.Integrator_DSTATE_o1 = 0.0F;
    }

    /* Sum: '<S1838>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1829>/Integrator'
     *  Gain: '<S1834>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_5 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_o1) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S1836>/Saturation' */
    if (u0 > 30000.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_5' */
      rtY.ANG_OUT_CH2_5 = 30000.0F;
    } else if (u0 < -30000.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_5' */
      rtY.ANG_OUT_CH2_5 = -30000.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH2_5' */
      rtY.ANG_OUT_CH2_5 = u0;
    }

    /* End of Saturate: '<S1836>/Saturation' */

    /* Chart: '<S1741>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_5'
     *  Inport: '<Root>/last_ecd_CH2_5'
     *  Sum: '<S1741>/Sum3'
     */
    Chart1(rtU.ecd_CH2_5 - rtU.last_ecd_CH2_5, &rtDW.u2_n2, &rtDW.sf_Chart1_dt);

    /* Outport: '<Root>/circle_out_CH2_5' incorporates:
     *  Inport: '<Root>/circle_CH2_5'
     *  Sum: '<S1741>/Sum4'
     */
    rtY.circle_out_CH2_5 = rtDW.u2_n2 + rtU.circle_CH2_5;

    /* Update for DiscreteIntegrator: '<S1879>/Integrator' incorporates:
     *  Gain: '<S1876>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_oq += rtP.ANG_A_I_CH2_5 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1874>/Filter' */
    rtDW.Filter_DSTATE_o0 += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S1824>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1829>/Integrator'
     *  Inport: '<Root>/reset_status2_5'
     */
    rtDW.Filter_DSTATE_ln += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status2_5 > 0.0F) {
      rtDW.Filter_PrevResetState_f3 = 1;
      rtDW.Integrator_PrevResetState_bs = 1;
    } else {
      if (rtU.reset_status2_5 < 0.0F) {
        rtDW.Filter_PrevResetState_f3 = -1;
      } else if (rtU.reset_status2_5 == 0.0F) {
        rtDW.Filter_PrevResetState_f3 = 0;
      } else {
        rtDW.Filter_PrevResetState_f3 = 2;
      }

      if (rtU.reset_status2_5 < 0.0F) {
        rtDW.Integrator_PrevResetState_bs = -1;
      } else if (rtU.reset_status2_5 == 0.0F) {
        rtDW.Integrator_PrevResetState_bs = 0;
      } else {
        rtDW.Integrator_PrevResetState_bs = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1824>/Filter' */

    /* Update for DiscreteIntegrator: '<S1829>/Integrator' incorporates:
     *  Gain: '<S1826>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_o1 += rtP.ANG_S_I_CH2_5 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S12>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S12>/Switch Case' */

  /* SwitchCase: '<S13>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH2_6'
   */
  switch ((int32_T)rtU.status_CH2_6) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S13>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1896>/Action Port'
     */
    /* Sum: '<S1896>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_6'
     *  Inport: '<Root>/target_CH2_6'
     */
    rtb_Switch2_ft = rtU.target_CH2_6 - rtU.speed_rpm_CH2_6;

    /* Switch: '<S1896>/Switch2' incorporates:
     *  Abs: '<S1896>/Abs'
     *  Constant: '<S1896>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH2_6)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S1896>/Switch2' */

    /* DiscreteIntegrator: '<S1927>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_6'
     */
    if (((rtU.reset_status2_6 > 0.0F) && (rtDW.Filter_PrevResetState_jv <= 0)) ||
        ((rtU.reset_status2_6 <= 0.0F) && (rtDW.Filter_PrevResetState_jv == 1)))
    {
      rtDW.Filter_DSTATE_k3 = 0.0F;
    }

    /* Gain: '<S1935>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1927>/Filter'
     *  Gain: '<S1925>/Derivative Gain'
     *  Sum: '<S1927>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH2_6 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_k3) * 100.0F;

    /* DiscreteIntegrator: '<S1932>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_6'
     */
    if (((rtU.reset_status2_6 > 0.0F) && (rtDW.Integrator_PrevResetState_gl <= 0))
        || ((rtU.reset_status2_6 <= 0.0F) && (rtDW.Integrator_PrevResetState_gl ==
          1))) {
      rtDW.Integrator_DSTATE_a = 0.0F;
    }

    /* Sum: '<S1941>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1932>/Integrator'
     *  Gain: '<S1937>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_6 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_a) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S1939>/Saturation' */
    if (u0 > 30000.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_6' */
      rtY.SPD_OUT_CH2_6 = 30000.0F;
    } else if (u0 < -30000.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_6' */
      rtY.SPD_OUT_CH2_6 = -30000.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH2_6' */
      rtY.SPD_OUT_CH2_6 = u0;
    }

    /* End of Saturate: '<S1939>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1927>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1932>/Integrator'
     *  Inport: '<Root>/reset_status2_6'
     */
    rtDW.Filter_DSTATE_k3 += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status2_6 > 0.0F) {
      rtDW.Filter_PrevResetState_jv = 1;
      rtDW.Integrator_PrevResetState_gl = 1;
    } else {
      if (rtU.reset_status2_6 < 0.0F) {
        rtDW.Filter_PrevResetState_jv = -1;
      } else if (rtU.reset_status2_6 == 0.0F) {
        rtDW.Filter_PrevResetState_jv = 0;
      } else {
        rtDW.Filter_PrevResetState_jv = 2;
      }

      if (rtU.reset_status2_6 < 0.0F) {
        rtDW.Integrator_PrevResetState_gl = -1;
      } else if (rtU.reset_status2_6 == 0.0F) {
        rtDW.Integrator_PrevResetState_gl = 0;
      } else {
        rtDW.Integrator_PrevResetState_gl = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1927>/Filter' */

    /* Update for DiscreteIntegrator: '<S1932>/Integrator' incorporates:
     *  Gain: '<S1929>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_a += rtP.SPD_I_CH2_6 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S13>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S13>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1897>/Action Port'
     */
    /* Sum: '<S1897>/Sum' incorporates:
     *  Gain: '<S1897>/Gain'
     *  Inport: '<Root>/circle_CH2_6'
     *  Inport: '<Root>/ecd_CH2_6'
     *  Inport: '<Root>/target_CH2_6'
     *  Sum: '<S1897>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH2_6 - (8191.0F * rtU.circle_CH2_6 +
      rtU.ecd_CH2_6);

    /* Abs: '<S1897>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S1897>/Switch2' incorporates:
     *  Constant: '<S1897>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH2_6)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S1897>/Switch2' */

    /* Gain: '<S2038>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2030>/Filter'
     *  Gain: '<S2028>/Derivative Gain'
     *  Sum: '<S2030>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH2_6 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_oz) * 100.0F;

    /* Switch: '<S1897>/Switch1' incorporates:
     *  Constant: '<S1897>/Constant'
     *  Gain: '<S1897>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_6'
     *  Saturate: '<S2042>/Saturation'
     *  Sum: '<S1897>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH2_6) {
      /* Sum: '<S2044>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2035>/Integrator'
       *  Gain: '<S2040>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_6 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_hd) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S2042>/Saturation' */
      if (u0 > 30000.0F) {
        u0 = 30000.0F;
      } else if (u0 < -30000.0F) {
        u0 = -30000.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH2_6 * u0 - rtU.speed_rpm_CH2_6;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S1897>/Switch1' */

    /* DiscreteIntegrator: '<S1980>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_6'
     */
    if (((rtU.reset_status2_6 > 0.0F) && (rtDW.Filter_PrevResetState_f <= 0)) ||
        ((rtU.reset_status2_6 <= 0.0F) && (rtDW.Filter_PrevResetState_f == 1)))
    {
      rtDW.Filter_DSTATE_ny = 0.0F;
    }

    /* Gain: '<S1988>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1980>/Filter'
     *  Gain: '<S1978>/Derivative Gain'
     *  Sum: '<S1980>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH2_6 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_ny) * 100.0F;

    /* DiscreteIntegrator: '<S1985>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_6'
     */
    if (((rtU.reset_status2_6 > 0.0F) && (rtDW.Integrator_PrevResetState_n <= 0))
        || ((rtU.reset_status2_6 <= 0.0F) && (rtDW.Integrator_PrevResetState_n ==
          1))) {
      rtDW.Integrator_DSTATE_ew = 0.0F;
    }

    /* Sum: '<S1994>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1985>/Integrator'
     *  Gain: '<S1990>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_6 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_ew) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S1992>/Saturation' */
    if (u0 > 30000.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_6' */
      rtY.ANG_OUT_CH2_6 = 30000.0F;
    } else if (u0 < -30000.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_6' */
      rtY.ANG_OUT_CH2_6 = -30000.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH2_6' */
      rtY.ANG_OUT_CH2_6 = u0;
    }

    /* End of Saturate: '<S1992>/Saturation' */

    /* Chart: '<S1897>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_6'
     *  Inport: '<Root>/last_ecd_CH2_6'
     *  Sum: '<S1897>/Sum3'
     */
    Chart1(rtU.ecd_CH2_6 - rtU.last_ecd_CH2_6, &rtDW.u2_h, &rtDW.sf_Chart1_n);

    /* Outport: '<Root>/circle_out_CH2_6' incorporates:
     *  Inport: '<Root>/circle_CH2_6'
     *  Sum: '<S1897>/Sum4'
     */
    rtY.circle_out_CH2_6 = rtDW.u2_h + rtU.circle_CH2_6;

    /* Update for DiscreteIntegrator: '<S2035>/Integrator' incorporates:
     *  Gain: '<S2032>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_hd += rtP.ANG_A_I_CH2_6 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2030>/Filter' */
    rtDW.Filter_DSTATE_oz += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S1980>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1985>/Integrator'
     *  Inport: '<Root>/reset_status2_6'
     */
    rtDW.Filter_DSTATE_ny += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status2_6 > 0.0F) {
      rtDW.Filter_PrevResetState_f = 1;
      rtDW.Integrator_PrevResetState_n = 1;
    } else {
      if (rtU.reset_status2_6 < 0.0F) {
        rtDW.Filter_PrevResetState_f = -1;
      } else if (rtU.reset_status2_6 == 0.0F) {
        rtDW.Filter_PrevResetState_f = 0;
      } else {
        rtDW.Filter_PrevResetState_f = 2;
      }

      if (rtU.reset_status2_6 < 0.0F) {
        rtDW.Integrator_PrevResetState_n = -1;
      } else if (rtU.reset_status2_6 == 0.0F) {
        rtDW.Integrator_PrevResetState_n = 0;
      } else {
        rtDW.Integrator_PrevResetState_n = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1980>/Filter' */

    /* Update for DiscreteIntegrator: '<S1985>/Integrator' incorporates:
     *  Gain: '<S1982>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ew += rtP.ANG_S_I_CH2_6 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S13>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S13>/Switch Case' */

  /* SwitchCase: '<S14>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH2_7'
   */
  switch ((int32_T)rtU.status_CH2_7) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S14>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S2052>/Action Port'
     */
    /* Sum: '<S2052>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_7'
     *  Inport: '<Root>/target_CH2_7'
     */
    rtb_Switch2_ft = rtU.target_CH2_7 - rtU.speed_rpm_CH2_7;

    /* Switch: '<S2052>/Switch2' incorporates:
     *  Abs: '<S2052>/Abs'
     *  Constant: '<S2052>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH2_5)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2052>/Switch2' */

    /* DiscreteIntegrator: '<S2083>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_7'
     */
    if (((rtU.reset_status2_7 > 0.0F) && (rtDW.Filter_PrevResetState_he <= 0)) ||
        ((rtU.reset_status2_7 <= 0.0F) && (rtDW.Filter_PrevResetState_he == 1)))
    {
      rtDW.Filter_DSTATE_oj = 0.0F;
    }

    /* Gain: '<S2091>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2083>/Filter'
     *  Gain: '<S2081>/Derivative Gain'
     *  Sum: '<S2083>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH2_7 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_oj) * 100.0F;

    /* DiscreteIntegrator: '<S2088>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_7'
     */
    if (((rtU.reset_status2_7 > 0.0F) && (rtDW.Integrator_PrevResetState_ik <= 0))
        || ((rtU.reset_status2_7 <= 0.0F) && (rtDW.Integrator_PrevResetState_ik ==
          1))) {
      rtDW.Integrator_DSTATE_b = 0.0F;
    }

    /* Sum: '<S2097>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2088>/Integrator'
     *  Gain: '<S2093>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_7 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_b) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S2095>/Saturation' */
    if (u0 > 30000.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_7' */
      rtY.SPD_OUT_CH2_7 = 30000.0F;
    } else if (u0 < -30000.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_7' */
      rtY.SPD_OUT_CH2_7 = -30000.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH2_7' */
      rtY.SPD_OUT_CH2_7 = u0;
    }

    /* End of Saturate: '<S2095>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2083>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2088>/Integrator'
     *  Inport: '<Root>/reset_status2_7'
     */
    rtDW.Filter_DSTATE_oj += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status2_7 > 0.0F) {
      rtDW.Filter_PrevResetState_he = 1;
      rtDW.Integrator_PrevResetState_ik = 1;
    } else {
      if (rtU.reset_status2_7 < 0.0F) {
        rtDW.Filter_PrevResetState_he = -1;
      } else if (rtU.reset_status2_7 == 0.0F) {
        rtDW.Filter_PrevResetState_he = 0;
      } else {
        rtDW.Filter_PrevResetState_he = 2;
      }

      if (rtU.reset_status2_7 < 0.0F) {
        rtDW.Integrator_PrevResetState_ik = -1;
      } else if (rtU.reset_status2_7 == 0.0F) {
        rtDW.Integrator_PrevResetState_ik = 0;
      } else {
        rtDW.Integrator_PrevResetState_ik = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2083>/Filter' */

    /* Update for DiscreteIntegrator: '<S2088>/Integrator' incorporates:
     *  Gain: '<S2085>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_b += rtP.SPD_I_CH2_7 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S14>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S14>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2053>/Action Port'
     */
    /* Sum: '<S2053>/Sum' incorporates:
     *  Gain: '<S2053>/Gain'
     *  Inport: '<Root>/circle_CH2_7'
     *  Inport: '<Root>/ecd_CH2_7'
     *  Inport: '<Root>/target_CH2_7'
     *  Sum: '<S2053>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH2_7 - (8191.0F * rtU.circle_CH2_7 +
      rtU.ecd_CH2_7);

    /* Abs: '<S2053>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S2053>/Switch2' incorporates:
     *  Constant: '<S2053>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH2_7)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S2053>/Switch2' */

    /* Gain: '<S2194>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2186>/Filter'
     *  Gain: '<S2184>/Derivative Gain'
     *  Sum: '<S2186>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH2_7 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_b) * 100.0F;

    /* Switch: '<S2053>/Switch1' incorporates:
     *  Constant: '<S2053>/Constant'
     *  Gain: '<S2053>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_7'
     *  Saturate: '<S2198>/Saturation'
     *  Sum: '<S2053>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH2_7) {
      /* Sum: '<S2200>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2191>/Integrator'
       *  Gain: '<S2196>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_7 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_l3) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S2198>/Saturation' */
      if (u0 > 30000.0F) {
        u0 = 30000.0F;
      } else if (u0 < -30000.0F) {
        u0 = -30000.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH2_7 * u0 - rtU.speed_rpm_CH2_7;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2053>/Switch1' */

    /* DiscreteIntegrator: '<S2136>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_7'
     */
    if (((rtU.reset_status2_7 > 0.0F) && (rtDW.Filter_PrevResetState_l <= 0)) ||
        ((rtU.reset_status2_7 <= 0.0F) && (rtDW.Filter_PrevResetState_l == 1)))
    {
      rtDW.Filter_DSTATE_op = 0.0F;
    }

    /* Gain: '<S2144>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2136>/Filter'
     *  Gain: '<S2134>/Derivative Gain'
     *  Sum: '<S2136>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH2_7 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_op) * 100.0F;

    /* DiscreteIntegrator: '<S2141>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_7'
     */
    if (((rtU.reset_status2_7 > 0.0F) && (rtDW.Integrator_PrevResetState_kl <= 0))
        || ((rtU.reset_status2_7 <= 0.0F) && (rtDW.Integrator_PrevResetState_kl ==
          1))) {
      rtDW.Integrator_DSTATE_dz = 0.0F;
    }

    /* Sum: '<S2150>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2141>/Integrator'
     *  Gain: '<S2146>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_7 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_dz) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S2148>/Saturation' */
    if (u0 > 30000.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_7' */
      rtY.ANG_OUT_CH2_7 = 30000.0F;
    } else if (u0 < -30000.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_7' */
      rtY.ANG_OUT_CH2_7 = -30000.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH2_7' */
      rtY.ANG_OUT_CH2_7 = u0;
    }

    /* End of Saturate: '<S2148>/Saturation' */

    /* Chart: '<S2053>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_7'
     *  Inport: '<Root>/last_ecd_CH2_7'
     *  Sum: '<S2053>/Sum3'
     */
    Chart1(rtU.ecd_CH2_7 - rtU.last_ecd_CH2_7, &rtDW.u2_e, &rtDW.sf_Chart1_k);

    /* Outport: '<Root>/circle_out_CH2_7' incorporates:
     *  Inport: '<Root>/circle_CH2_7'
     *  Sum: '<S2053>/Sum4'
     */
    rtY.circle_out_CH2_7 = rtDW.u2_e + rtU.circle_CH2_7;

    /* Update for DiscreteIntegrator: '<S2191>/Integrator' incorporates:
     *  Gain: '<S2188>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_l3 += rtP.ANG_A_I_CH2_7 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2186>/Filter' */
    rtDW.Filter_DSTATE_b += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S2136>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2141>/Integrator'
     *  Inport: '<Root>/reset_status2_7'
     */
    rtDW.Filter_DSTATE_op += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status2_7 > 0.0F) {
      rtDW.Filter_PrevResetState_l = 1;
      rtDW.Integrator_PrevResetState_kl = 1;
    } else {
      if (rtU.reset_status2_7 < 0.0F) {
        rtDW.Filter_PrevResetState_l = -1;
      } else if (rtU.reset_status2_7 == 0.0F) {
        rtDW.Filter_PrevResetState_l = 0;
      } else {
        rtDW.Filter_PrevResetState_l = 2;
      }

      if (rtU.reset_status2_7 < 0.0F) {
        rtDW.Integrator_PrevResetState_kl = -1;
      } else if (rtU.reset_status2_7 == 0.0F) {
        rtDW.Integrator_PrevResetState_kl = 0;
      } else {
        rtDW.Integrator_PrevResetState_kl = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2136>/Filter' */

    /* Update for DiscreteIntegrator: '<S2141>/Integrator' incorporates:
     *  Gain: '<S2138>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_dz += rtP.ANG_S_I_CH2_7 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S14>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S14>/Switch Case' */

  /* SwitchCase: '<S15>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH3_1'
   */
  switch ((int32_T)rtU.status_CH3_1) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S15>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S2208>/Action Port'
     */
    /* Sum: '<S2208>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_1'
     *  Inport: '<Root>/target_CH3_1'
     */
    rtb_Switch2_ft = rtU.target_CH3_1 - rtU.speed_rpm_CH3_1;

    /* Switch: '<S2208>/Switch2' incorporates:
     *  Abs: '<S2208>/Abs'
     *  Constant: '<S2208>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH3_1)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2208>/Switch2' */

    /* DiscreteIntegrator: '<S2239>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_1'
     */
    if (((rtU.reset_status3_1 > 0.0F) && (rtDW.Filter_PrevResetState_dp <= 0)) ||
        ((rtU.reset_status3_1 <= 0.0F) && (rtDW.Filter_PrevResetState_dp == 1)))
    {
      rtDW.Filter_DSTATE_ae = 0.0F;
    }

    /* Gain: '<S2247>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2239>/Filter'
     *  Gain: '<S2237>/Derivative Gain'
     *  Sum: '<S2239>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH3_1 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_ae) * 100.0F;

    /* DiscreteIntegrator: '<S2244>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_1'
     */
    if (((rtU.reset_status3_1 > 0.0F) && (rtDW.Integrator_PrevResetState_e1k <=
          0)) || ((rtU.reset_status3_1 <= 0.0F) &&
                  (rtDW.Integrator_PrevResetState_e1k == 1))) {
      rtDW.Integrator_DSTATE_h = 0.0F;
    }

    /* Sum: '<S2253>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2244>/Integrator'
     *  Gain: '<S2249>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_1 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_h) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S2251>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_1' */
      rtY.SPD_OUT_CH3_1 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_1' */
      rtY.SPD_OUT_CH3_1 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH3_1' */
      rtY.SPD_OUT_CH3_1 = u0;
    }

    /* End of Saturate: '<S2251>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2239>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2244>/Integrator'
     *  Inport: '<Root>/reset_status3_1'
     */
    rtDW.Filter_DSTATE_ae += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status3_1 > 0.0F) {
      rtDW.Filter_PrevResetState_dp = 1;
      rtDW.Integrator_PrevResetState_e1k = 1;
    } else {
      if (rtU.reset_status3_1 < 0.0F) {
        rtDW.Filter_PrevResetState_dp = -1;
      } else if (rtU.reset_status3_1 == 0.0F) {
        rtDW.Filter_PrevResetState_dp = 0;
      } else {
        rtDW.Filter_PrevResetState_dp = 2;
      }

      if (rtU.reset_status3_1 < 0.0F) {
        rtDW.Integrator_PrevResetState_e1k = -1;
      } else if (rtU.reset_status3_1 == 0.0F) {
        rtDW.Integrator_PrevResetState_e1k = 0;
      } else {
        rtDW.Integrator_PrevResetState_e1k = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2239>/Filter' */

    /* Update for DiscreteIntegrator: '<S2244>/Integrator' incorporates:
     *  Gain: '<S2241>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_h += rtP.SPD_I_CH3_1 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S15>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S15>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2209>/Action Port'
     */
    /* Sum: '<S2209>/Sum' incorporates:
     *  Gain: '<S2209>/Gain'
     *  Inport: '<Root>/circle_CH3_1'
     *  Inport: '<Root>/ecd_CH3_1'
     *  Inport: '<Root>/target_CH3_1'
     *  Sum: '<S2209>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH3_1 - (8191.0F * rtU.circle_CH3_1 +
      rtU.ecd_CH3_1);

    /* Abs: '<S2209>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S2209>/Switch2' incorporates:
     *  Constant: '<S2209>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH3_1)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S2209>/Switch2' */

    /* Gain: '<S2350>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2342>/Filter'
     *  Gain: '<S2340>/Derivative Gain'
     *  Sum: '<S2342>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH3_1 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_e4) * 100.0F;

    /* Switch: '<S2209>/Switch1' incorporates:
     *  Constant: '<S2209>/Constant'
     *  Gain: '<S2209>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_1'
     *  Saturate: '<S2354>/Saturation'
     *  Sum: '<S2209>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH3_1) {
      /* Sum: '<S2356>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2347>/Integrator'
       *  Gain: '<S2352>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_1 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_ly) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S2354>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH3_1 * u0 - rtU.speed_rpm_CH3_1;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2209>/Switch1' */

    /* DiscreteIntegrator: '<S2292>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_1'
     */
    if (((rtU.reset_status3_1 > 0.0F) && (rtDW.Filter_PrevResetState_p0 <= 0)) ||
        ((rtU.reset_status3_1 <= 0.0F) && (rtDW.Filter_PrevResetState_p0 == 1)))
    {
      rtDW.Filter_DSTATE_fh = 0.0F;
    }

    /* Gain: '<S2300>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2292>/Filter'
     *  Gain: '<S2290>/Derivative Gain'
     *  Sum: '<S2292>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH3_1 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_fh) * 100.0F;

    /* DiscreteIntegrator: '<S2297>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_1'
     */
    if (((rtU.reset_status3_1 > 0.0F) && (rtDW.Integrator_PrevResetState_c <= 0))
        || ((rtU.reset_status3_1 <= 0.0F) && (rtDW.Integrator_PrevResetState_c ==
          1))) {
      rtDW.Integrator_DSTATE_ju = 0.0F;
    }

    /* Sum: '<S2306>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2297>/Integrator'
     *  Gain: '<S2302>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_1 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_ju) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S2304>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_1' */
      rtY.ANG_OUT_CH3_1 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_1' */
      rtY.ANG_OUT_CH3_1 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH3_1' */
      rtY.ANG_OUT_CH3_1 = u0;
    }

    /* End of Saturate: '<S2304>/Saturation' */

    /* Chart: '<S2209>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_1'
     *  Inport: '<Root>/last_ecd_CH3_1'
     *  Sum: '<S2209>/Sum3'
     */
    Chart1(rtU.ecd_CH3_1 - rtU.last_ecd_CH3_1, &rtDW.u2_jx, &rtDW.sf_Chart1_hq);

    /* Outport: '<Root>/circle_out_CH3_1' incorporates:
     *  Inport: '<Root>/circle_CH3_1'
     *  Sum: '<S2209>/Sum4'
     */
    rtY.circle_out_CH3_1 = rtDW.u2_jx + rtU.circle_CH3_1;

    /* Update for DiscreteIntegrator: '<S2347>/Integrator' incorporates:
     *  Gain: '<S2344>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ly += rtP.ANG_A_I_CH3_1 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2342>/Filter' */
    rtDW.Filter_DSTATE_e4 += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S2292>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2297>/Integrator'
     *  Inport: '<Root>/reset_status3_1'
     */
    rtDW.Filter_DSTATE_fh += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status3_1 > 0.0F) {
      rtDW.Filter_PrevResetState_p0 = 1;
      rtDW.Integrator_PrevResetState_c = 1;
    } else {
      if (rtU.reset_status3_1 < 0.0F) {
        rtDW.Filter_PrevResetState_p0 = -1;
      } else if (rtU.reset_status3_1 == 0.0F) {
        rtDW.Filter_PrevResetState_p0 = 0;
      } else {
        rtDW.Filter_PrevResetState_p0 = 2;
      }

      if (rtU.reset_status3_1 < 0.0F) {
        rtDW.Integrator_PrevResetState_c = -1;
      } else if (rtU.reset_status3_1 == 0.0F) {
        rtDW.Integrator_PrevResetState_c = 0;
      } else {
        rtDW.Integrator_PrevResetState_c = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2292>/Filter' */

    /* Update for DiscreteIntegrator: '<S2297>/Integrator' incorporates:
     *  Gain: '<S2294>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ju += rtP.ANG_S_I_CH3_1 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S15>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S15>/Switch Case' */

  /* SwitchCase: '<S16>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH3_2'
   */
  switch ((int32_T)rtU.status_CH3_2) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S16>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S2364>/Action Port'
     */
    /* Sum: '<S2364>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_2'
     *  Inport: '<Root>/target_CH3_2'
     */
    rtb_Switch2_ft = rtU.target_CH3_2 - rtU.speed_rpm_CH3_2;

    /* Switch: '<S2364>/Switch2' incorporates:
     *  Abs: '<S2364>/Abs'
     *  Constant: '<S2364>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH3_2)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2364>/Switch2' */

    /* DiscreteIntegrator: '<S2395>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_2'
     */
    if (((rtU.reset_status3_2 > 0.0F) && (rtDW.Filter_PrevResetState_hr <= 0)) ||
        ((rtU.reset_status3_2 <= 0.0F) && (rtDW.Filter_PrevResetState_hr == 1)))
    {
      rtDW.Filter_DSTATE_pz = 0.0F;
    }

    /* Gain: '<S2403>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2395>/Filter'
     *  Gain: '<S2393>/Derivative Gain'
     *  Sum: '<S2395>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH3_2 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_pz) * 100.0F;

    /* DiscreteIntegrator: '<S2400>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_2'
     */
    if (((rtU.reset_status3_2 > 0.0F) && (rtDW.Integrator_PrevResetState_e1 <= 0))
        || ((rtU.reset_status3_2 <= 0.0F) && (rtDW.Integrator_PrevResetState_e1 ==
          1))) {
      rtDW.Integrator_DSTATE_eb = 0.0F;
    }

    /* Sum: '<S2409>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2400>/Integrator'
     *  Gain: '<S2405>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_2 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_eb) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S2407>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_2' */
      rtY.SPD_OUT_CH3_2 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_2' */
      rtY.SPD_OUT_CH3_2 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH3_2' */
      rtY.SPD_OUT_CH3_2 = u0;
    }

    /* End of Saturate: '<S2407>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2395>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2400>/Integrator'
     *  Inport: '<Root>/reset_status3_2'
     */
    rtDW.Filter_DSTATE_pz += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status3_2 > 0.0F) {
      rtDW.Filter_PrevResetState_hr = 1;
      rtDW.Integrator_PrevResetState_e1 = 1;
    } else {
      if (rtU.reset_status3_2 < 0.0F) {
        rtDW.Filter_PrevResetState_hr = -1;
      } else if (rtU.reset_status3_2 == 0.0F) {
        rtDW.Filter_PrevResetState_hr = 0;
      } else {
        rtDW.Filter_PrevResetState_hr = 2;
      }

      if (rtU.reset_status3_2 < 0.0F) {
        rtDW.Integrator_PrevResetState_e1 = -1;
      } else if (rtU.reset_status3_2 == 0.0F) {
        rtDW.Integrator_PrevResetState_e1 = 0;
      } else {
        rtDW.Integrator_PrevResetState_e1 = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2395>/Filter' */

    /* Update for DiscreteIntegrator: '<S2400>/Integrator' incorporates:
     *  Gain: '<S2397>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_eb += rtP.SPD_I_CH3_2 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S16>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S16>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2365>/Action Port'
     */
    /* Sum: '<S2365>/Sum' incorporates:
     *  Gain: '<S2365>/Gain'
     *  Inport: '<Root>/circle_CH3_2'
     *  Inport: '<Root>/ecd_CH3_2'
     *  Inport: '<Root>/target_CH3_2'
     *  Sum: '<S2365>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH3_2 - (8191.0F * rtU.circle_CH3_2 +
      rtU.ecd_CH3_2);

    /* Abs: '<S2365>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S2365>/Switch2' incorporates:
     *  Constant: '<S2365>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH3_2)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S2365>/Switch2' */

    /* Gain: '<S2506>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2498>/Filter'
     *  Gain: '<S2496>/Derivative Gain'
     *  Sum: '<S2498>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH3_2 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_id) * 100.0F;

    /* Switch: '<S2365>/Switch1' incorporates:
     *  Constant: '<S2365>/Constant'
     *  Gain: '<S2365>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_2'
     *  Saturate: '<S2510>/Saturation'
     *  Sum: '<S2365>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH3_2) {
      /* Sum: '<S2512>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2503>/Integrator'
       *  Gain: '<S2508>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_2 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_d) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S2510>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH3_2 * u0 - rtU.speed_rpm_CH3_2;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2365>/Switch1' */

    /* DiscreteIntegrator: '<S2448>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_2'
     */
    if (((rtU.reset_status3_2 > 0.0F) && (rtDW.Filter_PrevResetState_b <= 0)) ||
        ((rtU.reset_status3_2 <= 0.0F) && (rtDW.Filter_PrevResetState_b == 1)))
    {
      rtDW.Filter_DSTATE_iu = 0.0F;
    }

    /* Gain: '<S2456>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2448>/Filter'
     *  Gain: '<S2446>/Derivative Gain'
     *  Sum: '<S2448>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH3_2 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_iu) * 100.0F;

    /* DiscreteIntegrator: '<S2453>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_2'
     */
    if (((rtU.reset_status3_2 > 0.0F) && (rtDW.Integrator_PrevResetState_mv <= 0))
        || ((rtU.reset_status3_2 <= 0.0F) && (rtDW.Integrator_PrevResetState_mv ==
          1))) {
      rtDW.Integrator_DSTATE_po = 0.0F;
    }

    /* Sum: '<S2462>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2453>/Integrator'
     *  Gain: '<S2458>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_2 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_po) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S2460>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_2' */
      rtY.ANG_OUT_CH3_2 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_2' */
      rtY.ANG_OUT_CH3_2 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH3_2' */
      rtY.ANG_OUT_CH3_2 = u0;
    }

    /* End of Saturate: '<S2460>/Saturation' */

    /* Chart: '<S2365>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_2'
     *  Inport: '<Root>/last_ecd_CH3_2'
     *  Sum: '<S2365>/Sum3'
     */
    Chart1(rtU.ecd_CH3_2 - rtU.last_ecd_CH3_2, &rtDW.u2_m, &rtDW.sf_Chart1_ar);

    /* Outport: '<Root>/circle_out_CH3_2' incorporates:
     *  Inport: '<Root>/circle_CH3_2'
     *  Sum: '<S2365>/Sum4'
     */
    rtY.circle_out_CH3_2 = rtDW.u2_m + rtU.circle_CH3_2;

    /* Update for DiscreteIntegrator: '<S2503>/Integrator' incorporates:
     *  Gain: '<S2500>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_d += rtP.ANG_A_I_CH3_2 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2498>/Filter' */
    rtDW.Filter_DSTATE_id += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S2448>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2453>/Integrator'
     *  Inport: '<Root>/reset_status3_2'
     */
    rtDW.Filter_DSTATE_iu += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status3_2 > 0.0F) {
      rtDW.Filter_PrevResetState_b = 1;
      rtDW.Integrator_PrevResetState_mv = 1;
    } else {
      if (rtU.reset_status3_2 < 0.0F) {
        rtDW.Filter_PrevResetState_b = -1;
      } else if (rtU.reset_status3_2 == 0.0F) {
        rtDW.Filter_PrevResetState_b = 0;
      } else {
        rtDW.Filter_PrevResetState_b = 2;
      }

      if (rtU.reset_status3_2 < 0.0F) {
        rtDW.Integrator_PrevResetState_mv = -1;
      } else if (rtU.reset_status3_2 == 0.0F) {
        rtDW.Integrator_PrevResetState_mv = 0;
      } else {
        rtDW.Integrator_PrevResetState_mv = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2448>/Filter' */

    /* Update for DiscreteIntegrator: '<S2453>/Integrator' incorporates:
     *  Gain: '<S2450>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_po += rtP.ANG_S_I_CH3_2 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S16>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S16>/Switch Case' */

  /* SwitchCase: '<S17>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH3_3'
   */
  switch ((int32_T)rtU.status_CH3_3) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S17>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S2520>/Action Port'
     */
    /* Sum: '<S2520>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_3'
     *  Inport: '<Root>/target_CH3_3'
     */
    rtb_Switch2_ft = rtU.target_CH3_3 - rtU.speed_rpm_CH3_3;

    /* Switch: '<S2520>/Switch2' incorporates:
     *  Abs: '<S2520>/Abs'
     *  Constant: '<S2520>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH3_3)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2520>/Switch2' */

    /* DiscreteIntegrator: '<S2551>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_3'
     */
    if (((rtU.reset_status3_3 > 0.0F) && (rtDW.Filter_PrevResetState_j <= 0)) ||
        ((rtU.reset_status3_3 <= 0.0F) && (rtDW.Filter_PrevResetState_j == 1)))
    {
      rtDW.Filter_DSTATE_ps = 0.0F;
    }

    /* Gain: '<S2559>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2551>/Filter'
     *  Gain: '<S2549>/Derivative Gain'
     *  Sum: '<S2551>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH3_3 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_ps) * 100.0F;

    /* DiscreteIntegrator: '<S2556>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_3'
     */
    if (((rtU.reset_status3_3 > 0.0F) && (rtDW.Integrator_PrevResetState_b0 <= 0))
        || ((rtU.reset_status3_3 <= 0.0F) && (rtDW.Integrator_PrevResetState_b0 ==
          1))) {
      rtDW.Integrator_DSTATE_ij = 0.0F;
    }

    /* Sum: '<S2565>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2556>/Integrator'
     *  Gain: '<S2561>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_3 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_ij) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S2563>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_3' */
      rtY.SPD_OUT_CH3_3 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_3' */
      rtY.SPD_OUT_CH3_3 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH3_3' */
      rtY.SPD_OUT_CH3_3 = u0;
    }

    /* End of Saturate: '<S2563>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2551>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2556>/Integrator'
     *  Inport: '<Root>/reset_status3_3'
     */
    rtDW.Filter_DSTATE_ps += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status3_3 > 0.0F) {
      rtDW.Filter_PrevResetState_j = 1;
      rtDW.Integrator_PrevResetState_b0 = 1;
    } else {
      if (rtU.reset_status3_3 < 0.0F) {
        rtDW.Filter_PrevResetState_j = -1;
      } else if (rtU.reset_status3_3 == 0.0F) {
        rtDW.Filter_PrevResetState_j = 0;
      } else {
        rtDW.Filter_PrevResetState_j = 2;
      }

      if (rtU.reset_status3_3 < 0.0F) {
        rtDW.Integrator_PrevResetState_b0 = -1;
      } else if (rtU.reset_status3_3 == 0.0F) {
        rtDW.Integrator_PrevResetState_b0 = 0;
      } else {
        rtDW.Integrator_PrevResetState_b0 = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2551>/Filter' */

    /* Update for DiscreteIntegrator: '<S2556>/Integrator' incorporates:
     *  Gain: '<S2553>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ij += rtP.SPD_I_CH3_3 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S17>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S17>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2521>/Action Port'
     */
    /* Sum: '<S2521>/Sum' incorporates:
     *  Gain: '<S2521>/Gain'
     *  Inport: '<Root>/circle_CH3_3'
     *  Inport: '<Root>/ecd_CH3_3'
     *  Inport: '<Root>/target_CH3_3'
     *  Sum: '<S2521>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH3_3 - (8191.0F * rtU.circle_CH3_3 +
      rtU.ecd_CH3_3);

    /* Abs: '<S2521>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S2521>/Switch2' incorporates:
     *  Constant: '<S2521>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH3_3)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S2521>/Switch2' */

    /* Gain: '<S2662>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2654>/Filter'
     *  Gain: '<S2652>/Derivative Gain'
     *  Sum: '<S2654>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH3_3 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_a) * 100.0F;

    /* Switch: '<S2521>/Switch1' incorporates:
     *  Constant: '<S2521>/Constant'
     *  Gain: '<S2521>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_3'
     *  Saturate: '<S2666>/Saturation'
     *  Sum: '<S2521>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH3_3) {
      /* Sum: '<S2668>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2659>/Integrator'
       *  Gain: '<S2664>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_3 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_pf) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S2666>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH3_3 * u0 - rtU.speed_rpm_CH3_3;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2521>/Switch1' */

    /* DiscreteIntegrator: '<S2604>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_3'
     */
    if (((rtU.reset_status3_3 > 0.0F) && (rtDW.Filter_PrevResetState_el <= 0)) ||
        ((rtU.reset_status3_3 <= 0.0F) && (rtDW.Filter_PrevResetState_el == 1)))
    {
      rtDW.Filter_DSTATE_of = 0.0F;
    }

    /* Gain: '<S2612>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2604>/Filter'
     *  Gain: '<S2602>/Derivative Gain'
     *  Sum: '<S2604>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH3_3 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_of) * 100.0F;

    /* DiscreteIntegrator: '<S2609>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_3'
     */
    if (((rtU.reset_status3_3 > 0.0F) && (rtDW.Integrator_PrevResetState_e <= 0))
        || ((rtU.reset_status3_3 <= 0.0F) && (rtDW.Integrator_PrevResetState_e ==
          1))) {
      rtDW.Integrator_DSTATE_ka = 0.0F;
    }

    /* Sum: '<S2618>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2609>/Integrator'
     *  Gain: '<S2614>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_3 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_ka) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S2616>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_3' */
      rtY.ANG_OUT_CH3_3 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_3' */
      rtY.ANG_OUT_CH3_3 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH3_3' */
      rtY.ANG_OUT_CH3_3 = u0;
    }

    /* End of Saturate: '<S2616>/Saturation' */

    /* Chart: '<S2521>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_3'
     *  Inport: '<Root>/last_ecd_CH3_3'
     *  Sum: '<S2521>/Sum3'
     */
    Chart1(rtU.ecd_CH3_3 - rtU.last_ecd_CH3_3, &rtDW.u2_n, &rtDW.sf_Chart1_kh);

    /* Outport: '<Root>/circle_out_CH3_3' incorporates:
     *  Inport: '<Root>/circle_CH3_3'
     *  Sum: '<S2521>/Sum4'
     */
    rtY.circle_out_CH3_3 = rtDW.u2_n + rtU.circle_CH3_3;

    /* Update for DiscreteIntegrator: '<S2659>/Integrator' incorporates:
     *  Gain: '<S2656>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_pf += rtP.ANG_A_I_CH3_3 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2654>/Filter' */
    rtDW.Filter_DSTATE_a += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S2604>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2609>/Integrator'
     *  Inport: '<Root>/reset_status3_3'
     */
    rtDW.Filter_DSTATE_of += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status3_3 > 0.0F) {
      rtDW.Filter_PrevResetState_el = 1;
      rtDW.Integrator_PrevResetState_e = 1;
    } else {
      if (rtU.reset_status3_3 < 0.0F) {
        rtDW.Filter_PrevResetState_el = -1;
      } else if (rtU.reset_status3_3 == 0.0F) {
        rtDW.Filter_PrevResetState_el = 0;
      } else {
        rtDW.Filter_PrevResetState_el = 2;
      }

      if (rtU.reset_status3_3 < 0.0F) {
        rtDW.Integrator_PrevResetState_e = -1;
      } else if (rtU.reset_status3_3 == 0.0F) {
        rtDW.Integrator_PrevResetState_e = 0;
      } else {
        rtDW.Integrator_PrevResetState_e = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2604>/Filter' */

    /* Update for DiscreteIntegrator: '<S2609>/Integrator' incorporates:
     *  Gain: '<S2606>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ka += rtP.ANG_S_I_CH3_3 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S17>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S17>/Switch Case' */

  /* SwitchCase: '<S18>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH3_4'
   */
  switch ((int32_T)rtU.status_CH3_4) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S18>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S2676>/Action Port'
     */
    /* Sum: '<S2676>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_4'
     *  Inport: '<Root>/target_CH3_4'
     */
    rtb_Switch2_ft = rtU.target_CH3_4 - rtU.speed_rpm_CH3_4;

    /* Switch: '<S2676>/Switch2' incorporates:
     *  Abs: '<S2676>/Abs'
     *  Constant: '<S2676>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH3_4)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2676>/Switch2' */

    /* DiscreteIntegrator: '<S2707>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_4'
     */
    if (((rtU.reset_status3_4 > 0.0F) && (rtDW.Filter_PrevResetState_g <= 0)) ||
        ((rtU.reset_status3_4 <= 0.0F) && (rtDW.Filter_PrevResetState_g == 1)))
    {
      rtDW.Filter_DSTATE_g = 0.0F;
    }

    /* Gain: '<S2715>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2707>/Filter'
     *  Gain: '<S2705>/Derivative Gain'
     *  Sum: '<S2707>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH3_4 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_g) * 100.0F;

    /* DiscreteIntegrator: '<S2712>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_4'
     */
    if (((rtU.reset_status3_4 > 0.0F) && (rtDW.Integrator_PrevResetState_i <= 0))
        || ((rtU.reset_status3_4 <= 0.0F) && (rtDW.Integrator_PrevResetState_i ==
          1))) {
      rtDW.Integrator_DSTATE_oh = 0.0F;
    }

    /* Sum: '<S2721>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2712>/Integrator'
     *  Gain: '<S2717>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_4 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_oh) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S2719>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_4' */
      rtY.SPD_OUT_CH3_4 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_4' */
      rtY.SPD_OUT_CH3_4 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH3_4' */
      rtY.SPD_OUT_CH3_4 = u0;
    }

    /* End of Saturate: '<S2719>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2707>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2712>/Integrator'
     *  Inport: '<Root>/reset_status3_4'
     */
    rtDW.Filter_DSTATE_g += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status3_4 > 0.0F) {
      rtDW.Filter_PrevResetState_g = 1;
      rtDW.Integrator_PrevResetState_i = 1;
    } else {
      if (rtU.reset_status3_4 < 0.0F) {
        rtDW.Filter_PrevResetState_g = -1;
      } else if (rtU.reset_status3_4 == 0.0F) {
        rtDW.Filter_PrevResetState_g = 0;
      } else {
        rtDW.Filter_PrevResetState_g = 2;
      }

      if (rtU.reset_status3_4 < 0.0F) {
        rtDW.Integrator_PrevResetState_i = -1;
      } else if (rtU.reset_status3_4 == 0.0F) {
        rtDW.Integrator_PrevResetState_i = 0;
      } else {
        rtDW.Integrator_PrevResetState_i = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2707>/Filter' */

    /* Update for DiscreteIntegrator: '<S2712>/Integrator' incorporates:
     *  Gain: '<S2709>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_oh += rtP.SPD_I_CH3_4 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S18>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S18>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2677>/Action Port'
     */
    /* Sum: '<S2677>/Sum' incorporates:
     *  Gain: '<S2677>/Gain'
     *  Inport: '<Root>/circle_CH3_4'
     *  Inport: '<Root>/ecd_CH3_4'
     *  Inport: '<Root>/target_CH3_4'
     *  Sum: '<S2677>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH3_4 - (8191.0F * rtU.circle_CH3_4 +
      rtU.ecd_CH3_4);

    /* Abs: '<S2677>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S2677>/Switch2' incorporates:
     *  Constant: '<S2677>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH3_4)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S2677>/Switch2' */

    /* Gain: '<S2818>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2810>/Filter'
     *  Gain: '<S2808>/Derivative Gain'
     *  Sum: '<S2810>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH3_4 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_ip) * 100.0F;

    /* Switch: '<S2677>/Switch1' incorporates:
     *  Constant: '<S2677>/Constant'
     *  Gain: '<S2677>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_4'
     *  Saturate: '<S2822>/Saturation'
     *  Sum: '<S2677>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH3_4) {
      /* Sum: '<S2824>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2815>/Integrator'
       *  Gain: '<S2820>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_4 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_j) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S2822>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH3_4 * u0 - rtU.speed_rpm_CH3_4;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2677>/Switch1' */

    /* DiscreteIntegrator: '<S2760>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_4'
     */
    if (((rtU.reset_status3_4 > 0.0F) && (rtDW.Filter_PrevResetState_d3 <= 0)) ||
        ((rtU.reset_status3_4 <= 0.0F) && (rtDW.Filter_PrevResetState_d3 == 1)))
    {
      rtDW.Filter_DSTATE_f = 0.0F;
    }

    /* Gain: '<S2768>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2760>/Filter'
     *  Gain: '<S2758>/Derivative Gain'
     *  Sum: '<S2760>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH3_4 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_f) * 100.0F;

    /* DiscreteIntegrator: '<S2765>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_4'
     */
    if (((rtU.reset_status3_4 > 0.0F) && (rtDW.Integrator_PrevResetState_g <= 0))
        || ((rtU.reset_status3_4 <= 0.0F) && (rtDW.Integrator_PrevResetState_g ==
          1))) {
      rtDW.Integrator_DSTATE_l = 0.0F;
    }

    /* Sum: '<S2774>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2765>/Integrator'
     *  Gain: '<S2770>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_4 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_l) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S2772>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_4' */
      rtY.ANG_OUT_CH3_4 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_4' */
      rtY.ANG_OUT_CH3_4 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH3_4' */
      rtY.ANG_OUT_CH3_4 = u0;
    }

    /* End of Saturate: '<S2772>/Saturation' */

    /* Chart: '<S2677>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_4'
     *  Inport: '<Root>/last_ecd_CH3_4'
     *  Sum: '<S2677>/Sum3'
     */
    Chart1(rtU.ecd_CH3_4 - rtU.last_ecd_CH3_4, &rtDW.u2_j, &rtDW.sf_Chart1_i);

    /* Outport: '<Root>/circle_out_CH3_4' incorporates:
     *  Inport: '<Root>/circle_CH3_4'
     *  Sum: '<S2677>/Sum4'
     */
    rtY.circle_out_CH3_4 = rtDW.u2_j + rtU.circle_CH3_4;

    /* Update for DiscreteIntegrator: '<S2815>/Integrator' incorporates:
     *  Gain: '<S2812>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_j += rtP.ANG_A_I_CH3_4 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2810>/Filter' */
    rtDW.Filter_DSTATE_ip += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S2760>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2765>/Integrator'
     *  Inport: '<Root>/reset_status3_4'
     */
    rtDW.Filter_DSTATE_f += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status3_4 > 0.0F) {
      rtDW.Filter_PrevResetState_d3 = 1;
      rtDW.Integrator_PrevResetState_g = 1;
    } else {
      if (rtU.reset_status3_4 < 0.0F) {
        rtDW.Filter_PrevResetState_d3 = -1;
      } else if (rtU.reset_status3_4 == 0.0F) {
        rtDW.Filter_PrevResetState_d3 = 0;
      } else {
        rtDW.Filter_PrevResetState_d3 = 2;
      }

      if (rtU.reset_status3_4 < 0.0F) {
        rtDW.Integrator_PrevResetState_g = -1;
      } else if (rtU.reset_status3_4 == 0.0F) {
        rtDW.Integrator_PrevResetState_g = 0;
      } else {
        rtDW.Integrator_PrevResetState_g = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2760>/Filter' */

    /* Update for DiscreteIntegrator: '<S2765>/Integrator' incorporates:
     *  Gain: '<S2762>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_l += rtP.ANG_S_I_CH3_4 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S18>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S18>/Switch Case' */

  /* SwitchCase: '<S19>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH3_5'
   */
  switch ((int32_T)rtU.status_CH3_5) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S19>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S2832>/Action Port'
     */
    /* Sum: '<S2832>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_5'
     *  Inport: '<Root>/target_CH3_5'
     */
    rtb_Switch2_ft = rtU.target_CH3_5 - rtU.speed_rpm_CH3_5;

    /* Switch: '<S2832>/Switch2' incorporates:
     *  Abs: '<S2832>/Abs'
     *  Constant: '<S2832>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH3_5)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2832>/Switch2' */

    /* DiscreteIntegrator: '<S2863>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_5'
     */
    if (((rtU.reset_status3_5 > 0.0F) && (rtDW.Filter_PrevResetState_hn <= 0)) ||
        ((rtU.reset_status3_5 <= 0.0F) && (rtDW.Filter_PrevResetState_hn == 1)))
    {
      rtDW.Filter_DSTATE_eb = 0.0F;
    }

    /* Gain: '<S2871>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2863>/Filter'
     *  Gain: '<S2861>/Derivative Gain'
     *  Sum: '<S2863>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH3_5 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_eb) * 100.0F;

    /* DiscreteIntegrator: '<S2868>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_5'
     */
    if (((rtU.reset_status3_5 > 0.0F) && (rtDW.Integrator_PrevResetState_my <= 0))
        || ((rtU.reset_status3_5 <= 0.0F) && (rtDW.Integrator_PrevResetState_my ==
          1))) {
      rtDW.Integrator_DSTATE_p = 0.0F;
    }

    /* Sum: '<S2877>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2868>/Integrator'
     *  Gain: '<S2873>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_5 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_p) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S2875>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_5' */
      rtY.SPD_OUT_CH3_5 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_5' */
      rtY.SPD_OUT_CH3_5 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH3_5' */
      rtY.SPD_OUT_CH3_5 = u0;
    }

    /* End of Saturate: '<S2875>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2863>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2868>/Integrator'
     *  Inport: '<Root>/reset_status3_5'
     */
    rtDW.Filter_DSTATE_eb += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status3_5 > 0.0F) {
      rtDW.Filter_PrevResetState_hn = 1;
      rtDW.Integrator_PrevResetState_my = 1;
    } else {
      if (rtU.reset_status3_5 < 0.0F) {
        rtDW.Filter_PrevResetState_hn = -1;
      } else if (rtU.reset_status3_5 == 0.0F) {
        rtDW.Filter_PrevResetState_hn = 0;
      } else {
        rtDW.Filter_PrevResetState_hn = 2;
      }

      if (rtU.reset_status3_5 < 0.0F) {
        rtDW.Integrator_PrevResetState_my = -1;
      } else if (rtU.reset_status3_5 == 0.0F) {
        rtDW.Integrator_PrevResetState_my = 0;
      } else {
        rtDW.Integrator_PrevResetState_my = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2863>/Filter' */

    /* Update for DiscreteIntegrator: '<S2868>/Integrator' incorporates:
     *  Gain: '<S2865>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_p += rtP.SPD_I_CH3_5 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S19>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S19>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2833>/Action Port'
     */
    /* Sum: '<S2833>/Sum' incorporates:
     *  Gain: '<S2833>/Gain'
     *  Inport: '<Root>/circle_CH3_5'
     *  Inport: '<Root>/ecd_CH3_5'
     *  Inport: '<Root>/target_CH3_5'
     *  Sum: '<S2833>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH3_5 - (8191.0F * rtU.circle_CH3_5 +
      rtU.ecd_CH3_5);

    /* Abs: '<S2833>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S2833>/Switch2' incorporates:
     *  Constant: '<S2833>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH3_5)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S2833>/Switch2' */

    /* Gain: '<S2974>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2966>/Filter'
     *  Gain: '<S2964>/Derivative Gain'
     *  Sum: '<S2966>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH3_5 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_e) * 100.0F;

    /* Switch: '<S2833>/Switch1' incorporates:
     *  Constant: '<S2833>/Constant'
     *  Gain: '<S2833>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_5'
     *  Saturate: '<S2978>/Saturation'
     *  Sum: '<S2833>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH3_5) {
      /* Sum: '<S2980>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2971>/Integrator'
       *  Gain: '<S2976>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_5 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_i0) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S2978>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH3_5 * u0 - rtU.speed_rpm_CH3_5;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2833>/Switch1' */

    /* DiscreteIntegrator: '<S2916>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_5'
     */
    if (((rtU.reset_status3_5 > 0.0F) && (rtDW.Filter_PrevResetState_e <= 0)) ||
        ((rtU.reset_status3_5 <= 0.0F) && (rtDW.Filter_PrevResetState_e == 1)))
    {
      rtDW.Filter_DSTATE_o = 0.0F;
    }

    /* Gain: '<S2924>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2916>/Filter'
     *  Gain: '<S2914>/Derivative Gain'
     *  Sum: '<S2916>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH3_5 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_o) * 100.0F;

    /* DiscreteIntegrator: '<S2921>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_5'
     */
    if (((rtU.reset_status3_5 > 0.0F) && (rtDW.Integrator_PrevResetState_m <= 0))
        || ((rtU.reset_status3_5 <= 0.0F) && (rtDW.Integrator_PrevResetState_m ==
          1))) {
      rtDW.Integrator_DSTATE_oc = 0.0F;
    }

    /* Sum: '<S2930>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2921>/Integrator'
     *  Gain: '<S2926>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_5 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_oc) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S2928>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_5' */
      rtY.ANG_OUT_CH3_5 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_5' */
      rtY.ANG_OUT_CH3_5 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH3_5' */
      rtY.ANG_OUT_CH3_5 = u0;
    }

    /* End of Saturate: '<S2928>/Saturation' */

    /* Chart: '<S2833>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_5'
     *  Inport: '<Root>/last_ecd_CH3_5'
     *  Sum: '<S2833>/Sum3'
     */
    Chart1(rtU.ecd_CH3_5 - rtU.last_ecd_CH3_5, &rtDW.u2_p, &rtDW.sf_Chart1_df);

    /* Outport: '<Root>/circle_out_CH3_5' incorporates:
     *  Inport: '<Root>/circle_CH3_5'
     *  Sum: '<S2833>/Sum4'
     */
    rtY.circle_out_CH3_5 = rtDW.u2_p + rtU.circle_CH3_5;

    /* Update for DiscreteIntegrator: '<S2971>/Integrator' incorporates:
     *  Gain: '<S2968>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_i0 += rtP.ANG_A_I_CH3_5 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2966>/Filter' */
    rtDW.Filter_DSTATE_e += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S2916>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2921>/Integrator'
     *  Inport: '<Root>/reset_status3_5'
     */
    rtDW.Filter_DSTATE_o += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status3_5 > 0.0F) {
      rtDW.Filter_PrevResetState_e = 1;
      rtDW.Integrator_PrevResetState_m = 1;
    } else {
      if (rtU.reset_status3_5 < 0.0F) {
        rtDW.Filter_PrevResetState_e = -1;
      } else if (rtU.reset_status3_5 == 0.0F) {
        rtDW.Filter_PrevResetState_e = 0;
      } else {
        rtDW.Filter_PrevResetState_e = 2;
      }

      if (rtU.reset_status3_5 < 0.0F) {
        rtDW.Integrator_PrevResetState_m = -1;
      } else if (rtU.reset_status3_5 == 0.0F) {
        rtDW.Integrator_PrevResetState_m = 0;
      } else {
        rtDW.Integrator_PrevResetState_m = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2916>/Filter' */

    /* Update for DiscreteIntegrator: '<S2921>/Integrator' incorporates:
     *  Gain: '<S2918>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_oc += rtP.ANG_S_I_CH3_5 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S19>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S19>/Switch Case' */

  /* SwitchCase: '<S20>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH3_6'
   */
  switch ((int32_T)rtU.status_CH3_6) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S20>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S2988>/Action Port'
     */
    /* Sum: '<S2988>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_6'
     *  Inport: '<Root>/target_CH3_6'
     */
    rtb_Switch2_ft = rtU.target_CH3_6 - rtU.speed_rpm_CH3_6;

    /* Switch: '<S2988>/Switch2' incorporates:
     *  Abs: '<S2988>/Abs'
     *  Constant: '<S2988>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH3_6)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2988>/Switch2' */

    /* DiscreteIntegrator: '<S3019>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_6'
     */
    if (((rtU.reset_status3_6 > 0.0F) && (rtDW.Filter_PrevResetState_c4 <= 0)) ||
        ((rtU.reset_status3_6 <= 0.0F) && (rtDW.Filter_PrevResetState_c4 == 1)))
    {
      rtDW.Filter_DSTATE_p0 = 0.0F;
    }

    /* Gain: '<S3027>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S3019>/Filter'
     *  Gain: '<S3017>/Derivative Gain'
     *  Sum: '<S3019>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH3_6 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_p0) * 100.0F;

    /* DiscreteIntegrator: '<S3024>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_6'
     */
    if (((rtU.reset_status3_6 > 0.0F) && (rtDW.Integrator_PrevResetState_h <= 0))
        || ((rtU.reset_status3_6 <= 0.0F) && (rtDW.Integrator_PrevResetState_h ==
          1))) {
      rtDW.Integrator_DSTATE_ig = 0.0F;
    }

    /* Sum: '<S3033>/Sum' incorporates:
     *  DiscreteIntegrator: '<S3024>/Integrator'
     *  Gain: '<S3029>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_6 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_ig) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S3031>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_6' */
      rtY.SPD_OUT_CH3_6 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_6' */
      rtY.SPD_OUT_CH3_6 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH3_6' */
      rtY.SPD_OUT_CH3_6 = u0;
    }

    /* End of Saturate: '<S3031>/Saturation' */

    /* Update for DiscreteIntegrator: '<S3019>/Filter' incorporates:
     *  DiscreteIntegrator: '<S3024>/Integrator'
     *  Inport: '<Root>/reset_status3_6'
     */
    rtDW.Filter_DSTATE_p0 += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status3_6 > 0.0F) {
      rtDW.Filter_PrevResetState_c4 = 1;
      rtDW.Integrator_PrevResetState_h = 1;
    } else {
      if (rtU.reset_status3_6 < 0.0F) {
        rtDW.Filter_PrevResetState_c4 = -1;
      } else if (rtU.reset_status3_6 == 0.0F) {
        rtDW.Filter_PrevResetState_c4 = 0;
      } else {
        rtDW.Filter_PrevResetState_c4 = 2;
      }

      if (rtU.reset_status3_6 < 0.0F) {
        rtDW.Integrator_PrevResetState_h = -1;
      } else if (rtU.reset_status3_6 == 0.0F) {
        rtDW.Integrator_PrevResetState_h = 0;
      } else {
        rtDW.Integrator_PrevResetState_h = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S3019>/Filter' */

    /* Update for DiscreteIntegrator: '<S3024>/Integrator' incorporates:
     *  Gain: '<S3021>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ig += rtP.SPD_I_CH3_6 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S20>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S20>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2989>/Action Port'
     */
    /* Sum: '<S2989>/Sum' incorporates:
     *  Gain: '<S2989>/Gain'
     *  Inport: '<Root>/circle_CH3_6'
     *  Inport: '<Root>/ecd_CH3_6'
     *  Inport: '<Root>/target_CH3_6'
     *  Sum: '<S2989>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH3_6 - (8191.0F * rtU.circle_CH3_6 +
      rtU.ecd_CH3_6);

    /* Abs: '<S2989>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S2989>/Switch2' incorporates:
     *  Constant: '<S2989>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH3_6)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S2989>/Switch2' */

    /* Gain: '<S3130>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S3122>/Filter'
     *  Gain: '<S3120>/Derivative Gain'
     *  Sum: '<S3122>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH3_6 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_m) * 100.0F;

    /* Switch: '<S2989>/Switch1' incorporates:
     *  Constant: '<S2989>/Constant'
     *  Gain: '<S2989>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_6'
     *  Saturate: '<S3134>/Saturation'
     *  Sum: '<S2989>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH3_6) {
      /* Sum: '<S3136>/Sum' incorporates:
       *  DiscreteIntegrator: '<S3127>/Integrator'
       *  Gain: '<S3132>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_6 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_cg) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S3134>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH3_6 * u0 - rtU.speed_rpm_CH3_6;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S2989>/Switch1' */

    /* DiscreteIntegrator: '<S3072>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_6'
     */
    if (((rtU.reset_status3_6 > 0.0F) && (rtDW.Filter_PrevResetState_c <= 0)) ||
        ((rtU.reset_status3_6 <= 0.0F) && (rtDW.Filter_PrevResetState_c == 1)))
    {
      rtDW.Filter_DSTATE_n = 0.0F;
    }

    /* Gain: '<S3080>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S3072>/Filter'
     *  Gain: '<S3070>/Derivative Gain'
     *  Sum: '<S3072>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH3_6 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_n) * 100.0F;

    /* DiscreteIntegrator: '<S3077>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_6'
     */
    if (((rtU.reset_status3_6 > 0.0F) && (rtDW.Integrator_PrevResetState_b <= 0))
        || ((rtU.reset_status3_6 <= 0.0F) && (rtDW.Integrator_PrevResetState_b ==
          1))) {
      rtDW.Integrator_DSTATE_k = 0.0F;
    }

    /* Sum: '<S3086>/Sum' incorporates:
     *  DiscreteIntegrator: '<S3077>/Integrator'
     *  Gain: '<S3082>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_6 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_k) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S3084>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_6' */
      rtY.ANG_OUT_CH3_6 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_6' */
      rtY.ANG_OUT_CH3_6 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH3_6' */
      rtY.ANG_OUT_CH3_6 = u0;
    }

    /* End of Saturate: '<S3084>/Saturation' */

    /* Chart: '<S2989>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_6'
     *  Inport: '<Root>/last_ecd_CH3_6'
     *  Sum: '<S2989>/Sum3'
     */
    Chart1(rtU.ecd_CH3_6 - rtU.last_ecd_CH3_6, &rtDW.u2_b, &rtDW.sf_Chart1_c);

    /* Outport: '<Root>/circle_out_CH3_6' incorporates:
     *  Inport: '<Root>/circle_CH3_6'
     *  Sum: '<S2989>/Sum4'
     */
    rtY.circle_out_CH3_6 = rtDW.u2_b + rtU.circle_CH3_6;

    /* Update for DiscreteIntegrator: '<S3127>/Integrator' incorporates:
     *  Gain: '<S3124>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_cg += rtP.ANG_A_I_CH3_6 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S3122>/Filter' */
    rtDW.Filter_DSTATE_m += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S3072>/Filter' incorporates:
     *  DiscreteIntegrator: '<S3077>/Integrator'
     *  Inport: '<Root>/reset_status3_6'
     */
    rtDW.Filter_DSTATE_n += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status3_6 > 0.0F) {
      rtDW.Filter_PrevResetState_c = 1;
      rtDW.Integrator_PrevResetState_b = 1;
    } else {
      if (rtU.reset_status3_6 < 0.0F) {
        rtDW.Filter_PrevResetState_c = -1;
      } else if (rtU.reset_status3_6 == 0.0F) {
        rtDW.Filter_PrevResetState_c = 0;
      } else {
        rtDW.Filter_PrevResetState_c = 2;
      }

      if (rtU.reset_status3_6 < 0.0F) {
        rtDW.Integrator_PrevResetState_b = -1;
      } else if (rtU.reset_status3_6 == 0.0F) {
        rtDW.Integrator_PrevResetState_b = 0;
      } else {
        rtDW.Integrator_PrevResetState_b = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S3072>/Filter' */

    /* Update for DiscreteIntegrator: '<S3077>/Integrator' incorporates:
     *  Gain: '<S3074>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_k += rtP.ANG_S_I_CH3_6 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S20>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S20>/Switch Case' */

  /* SwitchCase: '<S21>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH3_7'
   */
  switch ((int32_T)rtU.status_CH3_7) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S21>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S3144>/Action Port'
     */
    /* Sum: '<S3144>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_7'
     *  Inport: '<Root>/target_CH3_7'
     */
    rtb_Switch2_ft = rtU.target_CH3_7 - rtU.speed_rpm_CH3_7;

    /* Switch: '<S3144>/Switch2' incorporates:
     *  Abs: '<S3144>/Abs'
     *  Constant: '<S3144>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH3_7)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S3144>/Switch2' */

    /* DiscreteIntegrator: '<S3175>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_7'
     */
    if (((rtU.reset_status3_7 > 0.0F) && (rtDW.Filter_PrevResetState_h <= 0)) ||
        ((rtU.reset_status3_7 <= 0.0F) && (rtDW.Filter_PrevResetState_h == 1)))
    {
      rtDW.Filter_DSTATE_k = 0.0F;
    }

    /* Gain: '<S3183>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S3175>/Filter'
     *  Gain: '<S3173>/Derivative Gain'
     *  Sum: '<S3175>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH3_7 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_k) * 100.0F;

    /* DiscreteIntegrator: '<S3180>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_7'
     */
    if (((rtU.reset_status3_7 > 0.0F) && (rtDW.Integrator_PrevResetState_a <= 0))
        || ((rtU.reset_status3_7 <= 0.0F) && (rtDW.Integrator_PrevResetState_a ==
          1))) {
      rtDW.Integrator_DSTATE_c = 0.0F;
    }

    /* Sum: '<S3189>/Sum' incorporates:
     *  DiscreteIntegrator: '<S3180>/Integrator'
     *  Gain: '<S3185>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_7 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_c) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S3187>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_7' */
      rtY.SPD_OUT_CH3_7 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH3_7' */
      rtY.SPD_OUT_CH3_7 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH3_7' */
      rtY.SPD_OUT_CH3_7 = u0;
    }

    /* End of Saturate: '<S3187>/Saturation' */

    /* Update for DiscreteIntegrator: '<S3175>/Filter' incorporates:
     *  DiscreteIntegrator: '<S3180>/Integrator'
     *  Inport: '<Root>/reset_status3_7'
     */
    rtDW.Filter_DSTATE_k += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status3_7 > 0.0F) {
      rtDW.Filter_PrevResetState_h = 1;
      rtDW.Integrator_PrevResetState_a = 1;
    } else {
      if (rtU.reset_status3_7 < 0.0F) {
        rtDW.Filter_PrevResetState_h = -1;
      } else if (rtU.reset_status3_7 == 0.0F) {
        rtDW.Filter_PrevResetState_h = 0;
      } else {
        rtDW.Filter_PrevResetState_h = 2;
      }

      if (rtU.reset_status3_7 < 0.0F) {
        rtDW.Integrator_PrevResetState_a = -1;
      } else if (rtU.reset_status3_7 == 0.0F) {
        rtDW.Integrator_PrevResetState_a = 0;
      } else {
        rtDW.Integrator_PrevResetState_a = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S3175>/Filter' */

    /* Update for DiscreteIntegrator: '<S3180>/Integrator' incorporates:
     *  Gain: '<S3177>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_c += rtP.SPD_I_CH3_7 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S21>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S21>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S3145>/Action Port'
     */
    /* Sum: '<S3145>/Sum' incorporates:
     *  Gain: '<S3145>/Gain'
     *  Inport: '<Root>/circle_CH3_7'
     *  Inport: '<Root>/ecd_CH3_7'
     *  Inport: '<Root>/target_CH3_7'
     *  Sum: '<S3145>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH3_7 - (8191.0F * rtU.circle_CH3_7 +
      rtU.ecd_CH3_7);

    /* Abs: '<S3145>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S3145>/Switch2' incorporates:
     *  Constant: '<S3145>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH3_7)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S3145>/Switch2' */

    /* Gain: '<S3286>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S3278>/Filter'
     *  Gain: '<S3276>/Derivative Gain'
     *  Sum: '<S3278>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH3_7 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_p) * 100.0F;

    /* Switch: '<S3145>/Switch1' incorporates:
     *  Constant: '<S3145>/Constant'
     *  Gain: '<S3145>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_7'
     *  Saturate: '<S3290>/Saturation'
     *  Sum: '<S3145>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH3_7) {
      /* Sum: '<S3292>/Sum' incorporates:
       *  DiscreteIntegrator: '<S3283>/Integrator'
       *  Gain: '<S3288>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_7 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_i) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S3290>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH3_7 * u0 - rtU.speed_rpm_CH3_7;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S3145>/Switch1' */

    /* DiscreteIntegrator: '<S3228>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_7'
     */
    if (((rtU.reset_status3_7 > 0.0F) && (rtDW.Filter_PrevResetState_d <= 0)) ||
        ((rtU.reset_status3_7 <= 0.0F) && (rtDW.Filter_PrevResetState_d == 1)))
    {
      rtDW.Filter_DSTATE_i = 0.0F;
    }

    /* Gain: '<S3236>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S3228>/Filter'
     *  Gain: '<S3226>/Derivative Gain'
     *  Sum: '<S3228>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH3_7 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_i) * 100.0F;

    /* DiscreteIntegrator: '<S3233>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_7'
     */
    if (((rtU.reset_status3_7 > 0.0F) && (rtDW.Integrator_PrevResetState_o <= 0))
        || ((rtU.reset_status3_7 <= 0.0F) && (rtDW.Integrator_PrevResetState_o ==
          1))) {
      rtDW.Integrator_DSTATE_o = 0.0F;
    }

    /* Sum: '<S3242>/Sum' incorporates:
     *  DiscreteIntegrator: '<S3233>/Integrator'
     *  Gain: '<S3238>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_7 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_o) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S3240>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_7' */
      rtY.ANG_OUT_CH3_7 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH3_7' */
      rtY.ANG_OUT_CH3_7 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH3_7' */
      rtY.ANG_OUT_CH3_7 = u0;
    }

    /* End of Saturate: '<S3240>/Saturation' */

    /* Chart: '<S3145>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_7'
     *  Inport: '<Root>/last_ecd_CH3_7'
     *  Sum: '<S3145>/Sum3'
     */
    Chart1(rtU.ecd_CH3_7 - rtU.last_ecd_CH3_7, &rtDW.u2, &rtDW.sf_Chart1_br);

    /* Outport: '<Root>/circle_out_CH3_7' incorporates:
     *  Inport: '<Root>/circle_CH3_7'
     *  Sum: '<S3145>/Sum4'
     */
    rtY.circle_out_CH3_7 = rtDW.u2 + rtU.circle_CH3_7;

    /* Update for DiscreteIntegrator: '<S3283>/Integrator' incorporates:
     *  Gain: '<S3280>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_i += rtP.ANG_A_I_CH3_7 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S3278>/Filter' */
    rtDW.Filter_DSTATE_p += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S3228>/Filter' incorporates:
     *  DiscreteIntegrator: '<S3233>/Integrator'
     *  Inport: '<Root>/reset_status3_7'
     */
    rtDW.Filter_DSTATE_i += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status3_7 > 0.0F) {
      rtDW.Filter_PrevResetState_d = 1;
      rtDW.Integrator_PrevResetState_o = 1;
    } else {
      if (rtU.reset_status3_7 < 0.0F) {
        rtDW.Filter_PrevResetState_d = -1;
      } else if (rtU.reset_status3_7 == 0.0F) {
        rtDW.Filter_PrevResetState_d = 0;
      } else {
        rtDW.Filter_PrevResetState_d = 2;
      }

      if (rtU.reset_status3_7 < 0.0F) {
        rtDW.Integrator_PrevResetState_o = -1;
      } else if (rtU.reset_status3_7 == 0.0F) {
        rtDW.Integrator_PrevResetState_o = 0;
      } else {
        rtDW.Integrator_PrevResetState_o = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S3228>/Filter' */

    /* Update for DiscreteIntegrator: '<S3233>/Integrator' incorporates:
     *  Gain: '<S3230>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_o += rtP.ANG_S_I_CH3_7 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S21>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S21>/Switch Case' */

  /* SwitchCase: '<S8>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH2_1'
   */
  switch ((int32_T)rtU.status_CH2_1) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S8>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1116>/Action Port'
     */
    /* Sum: '<S1116>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_1'
     *  Inport: '<Root>/target_CH2_1'
     */
    rtb_Switch2_ft = rtU.target_CH2_1 - rtU.speed_rpm_CH2_1;

    /* Switch: '<S1116>/Switch2' incorporates:
     *  Abs: '<S1116>/Abs'
     *  Constant: '<S1116>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH2_1)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S1116>/Switch2' */

    /* DiscreteIntegrator: '<S1147>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_1'
     */
    if (((rtU.reset_status2_1 > 0.0F) && (rtDW.Filter_PrevResetState_do <= 0)) ||
        ((rtU.reset_status2_1 <= 0.0F) && (rtDW.Filter_PrevResetState_do == 1)))
    {
      rtDW.Filter_DSTATE_h = 0.0F;
    }

    /* Gain: '<S1155>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1147>/Filter'
     *  Gain: '<S1145>/Derivative Gain'
     *  Sum: '<S1147>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH2_1 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_h) * 100.0F;

    /* DiscreteIntegrator: '<S1152>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_1'
     */
    if (((rtU.reset_status2_1 > 0.0F) && (rtDW.Integrator_PrevResetState_o4 <= 0))
        || ((rtU.reset_status2_1 <= 0.0F) && (rtDW.Integrator_PrevResetState_o4 ==
          1))) {
      rtDW.Integrator_DSTATE_i5 = 0.0F;
    }

    /* Sum: '<S1161>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1152>/Integrator'
     *  Gain: '<S1157>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_1 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_i5) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S1159>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_1' */
      rtY.SPD_OUT_CH2_1 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_1' */
      rtY.SPD_OUT_CH2_1 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH2_1' */
      rtY.SPD_OUT_CH2_1 = u0;
    }

    /* End of Saturate: '<S1159>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1147>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1152>/Integrator'
     *  Inport: '<Root>/reset_status2_1'
     */
    rtDW.Filter_DSTATE_h += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status2_1 > 0.0F) {
      rtDW.Filter_PrevResetState_do = 1;
      rtDW.Integrator_PrevResetState_o4 = 1;
    } else {
      if (rtU.reset_status2_1 < 0.0F) {
        rtDW.Filter_PrevResetState_do = -1;
      } else if (rtU.reset_status2_1 == 0.0F) {
        rtDW.Filter_PrevResetState_do = 0;
      } else {
        rtDW.Filter_PrevResetState_do = 2;
      }

      if (rtU.reset_status2_1 < 0.0F) {
        rtDW.Integrator_PrevResetState_o4 = -1;
      } else if (rtU.reset_status2_1 == 0.0F) {
        rtDW.Integrator_PrevResetState_o4 = 0;
      } else {
        rtDW.Integrator_PrevResetState_o4 = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1147>/Filter' */

    /* Update for DiscreteIntegrator: '<S1152>/Integrator' incorporates:
     *  Gain: '<S1149>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_i5 += rtP.SPD_I_CH2_1 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S8>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S8>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1117>/Action Port'
     */
    /* Sum: '<S1117>/Sum' incorporates:
     *  Gain: '<S1117>/Gain'
     *  Inport: '<Root>/circle_CH2_1'
     *  Inport: '<Root>/ecd_CH2_1'
     *  Inport: '<Root>/target_CH2_1'
     *  Sum: '<S1117>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH2_1 - (8191.0F * rtU.circle_CH2_1 +
      rtU.ecd_CH2_1);

    /* Abs: '<S1117>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S1117>/Switch2' incorporates:
     *  Constant: '<S1117>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH2_1)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S1117>/Switch2' */

    /* Gain: '<S1258>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1250>/Filter'
     *  Gain: '<S1248>/Derivative Gain'
     *  Sum: '<S1250>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH2_1 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_d3) * 100.0F;

    /* Switch: '<S1117>/Switch1' incorporates:
     *  Constant: '<S1117>/Constant'
     *  Gain: '<S1117>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_1'
     *  Saturate: '<S1262>/Saturation'
     *  Sum: '<S1117>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH2_1) {
      /* Sum: '<S1264>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1255>/Integrator'
       *  Gain: '<S1260>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_1 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_cs) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S1262>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH2_1 * u0 - rtU.speed_rpm_CH2_1;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S1117>/Switch1' */

    /* DiscreteIntegrator: '<S1200>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_1'
     */
    if (((rtU.reset_status2_1 > 0.0F) && (rtDW.Filter_PrevResetState_o <= 0)) ||
        ((rtU.reset_status2_1 <= 0.0F) && (rtDW.Filter_PrevResetState_o == 1)))
    {
      rtDW.Filter_DSTATE_mi = 0.0F;
    }

    /* Gain: '<S1208>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1200>/Filter'
     *  Gain: '<S1198>/Derivative Gain'
     *  Sum: '<S1200>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH2_1 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_mi) * 100.0F;

    /* DiscreteIntegrator: '<S1205>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_1'
     */
    if (((rtU.reset_status2_1 > 0.0F) && (rtDW.Integrator_PrevResetState_io <= 0))
        || ((rtU.reset_status2_1 <= 0.0F) && (rtDW.Integrator_PrevResetState_io ==
          1))) {
      rtDW.Integrator_DSTATE_ib = 0.0F;
    }

    /* Sum: '<S1214>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1205>/Integrator'
     *  Gain: '<S1210>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_1 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_ib) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S1212>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_1' */
      rtY.ANG_OUT_CH2_1 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_1' */
      rtY.ANG_OUT_CH2_1 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH2_1' */
      rtY.ANG_OUT_CH2_1 = u0;
    }

    /* End of Saturate: '<S1212>/Saturation' */

    /* Chart: '<S1117>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_1'
     *  Inport: '<Root>/last_ecd_CH2_1'
     *  Sum: '<S1117>/Sum3'
     */
    Chart1(rtU.ecd_CH2_1 - rtU.last_ecd_CH2_1, &rtDW.u2_fb, &rtDW.sf_Chart1_b);

    /* Outport: '<Root>/circle_out_CH2_1' incorporates:
     *  Inport: '<Root>/circle_CH2_1'
     *  Sum: '<S1117>/Sum4'
     */
    rtY.circle_out_CH2_1 = rtDW.u2_fb + rtU.circle_CH2_1;

    /* Update for DiscreteIntegrator: '<S1255>/Integrator' incorporates:
     *  Gain: '<S1252>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_cs += rtP.ANG_A_I_CH2_1 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1250>/Filter' */
    rtDW.Filter_DSTATE_d3 += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S1200>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1205>/Integrator'
     *  Inport: '<Root>/reset_status2_1'
     */
    rtDW.Filter_DSTATE_mi += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status2_1 > 0.0F) {
      rtDW.Filter_PrevResetState_o = 1;
      rtDW.Integrator_PrevResetState_io = 1;
    } else {
      if (rtU.reset_status2_1 < 0.0F) {
        rtDW.Filter_PrevResetState_o = -1;
      } else if (rtU.reset_status2_1 == 0.0F) {
        rtDW.Filter_PrevResetState_o = 0;
      } else {
        rtDW.Filter_PrevResetState_o = 2;
      }

      if (rtU.reset_status2_1 < 0.0F) {
        rtDW.Integrator_PrevResetState_io = -1;
      } else if (rtU.reset_status2_1 == 0.0F) {
        rtDW.Integrator_PrevResetState_io = 0;
      } else {
        rtDW.Integrator_PrevResetState_io = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1200>/Filter' */

    /* Update for DiscreteIntegrator: '<S1205>/Integrator' incorporates:
     *  Gain: '<S1202>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ib += rtP.ANG_S_I_CH2_1 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S8>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S8>/Switch Case' */

  /* SwitchCase: '<S9>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH2_2'
   */
  switch ((int32_T)rtU.status_CH2_2) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S9>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1272>/Action Port'
     */
    /* Sum: '<S1272>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_2'
     *  Inport: '<Root>/target_CH2_2'
     */
    rtb_Switch2_ft = rtU.target_CH2_2 - rtU.speed_rpm_CH2_2;

    /* Switch: '<S1272>/Switch2' incorporates:
     *  Abs: '<S1272>/Abs'
     *  Constant: '<S1272>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH2_2)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S1272>/Switch2' */

    /* DiscreteIntegrator: '<S1303>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_2'
     */
    if (((rtU.reset_status2_2 > 0.0F) && (rtDW.Filter_PrevResetState_af <= 0)) ||
        ((rtU.reset_status2_2 <= 0.0F) && (rtDW.Filter_PrevResetState_af == 1)))
    {
      rtDW.Filter_DSTATE_ds = 0.0F;
    }

    /* Gain: '<S1311>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1303>/Filter'
     *  Gain: '<S1301>/Derivative Gain'
     *  Sum: '<S1303>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH2_2 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_ds) * 100.0F;

    /* DiscreteIntegrator: '<S1308>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_2'
     */
    if (((rtU.reset_status2_2 > 0.0F) && (rtDW.Integrator_PrevResetState_c3 <= 0))
        || ((rtU.reset_status2_2 <= 0.0F) && (rtDW.Integrator_PrevResetState_c3 ==
          1))) {
      rtDW.Integrator_DSTATE_n = 0.0F;
    }

    /* Sum: '<S1317>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1308>/Integrator'
     *  Gain: '<S1313>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_2 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_n) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S1315>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_2' */
      rtY.SPD_OUT_CH2_2 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_2' */
      rtY.SPD_OUT_CH2_2 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH2_2' */
      rtY.SPD_OUT_CH2_2 = u0;
    }

    /* End of Saturate: '<S1315>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1303>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1308>/Integrator'
     *  Inport: '<Root>/reset_status2_2'
     */
    rtDW.Filter_DSTATE_ds += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status2_2 > 0.0F) {
      rtDW.Filter_PrevResetState_af = 1;
      rtDW.Integrator_PrevResetState_c3 = 1;
    } else {
      if (rtU.reset_status2_2 < 0.0F) {
        rtDW.Filter_PrevResetState_af = -1;
      } else if (rtU.reset_status2_2 == 0.0F) {
        rtDW.Filter_PrevResetState_af = 0;
      } else {
        rtDW.Filter_PrevResetState_af = 2;
      }

      if (rtU.reset_status2_2 < 0.0F) {
        rtDW.Integrator_PrevResetState_c3 = -1;
      } else if (rtU.reset_status2_2 == 0.0F) {
        rtDW.Integrator_PrevResetState_c3 = 0;
      } else {
        rtDW.Integrator_PrevResetState_c3 = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1303>/Filter' */

    /* Update for DiscreteIntegrator: '<S1308>/Integrator' incorporates:
     *  Gain: '<S1305>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_n += rtP.SPD_I_CH2_2 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S9>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S9>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1273>/Action Port'
     */
    /* Sum: '<S1273>/Sum' incorporates:
     *  Gain: '<S1273>/Gain'
     *  Inport: '<Root>/circle_CH2_2'
     *  Inport: '<Root>/ecd_CH2_2'
     *  Inport: '<Root>/target_CH2_2'
     *  Sum: '<S1273>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH2_2 - (8191.0F * rtU.circle_CH2_2 +
      rtU.ecd_CH2_2);

    /* Abs: '<S1273>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S1273>/Switch2' incorporates:
     *  Constant: '<S1273>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH2_2)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S1273>/Switch2' */

    /* Gain: '<S1414>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1406>/Filter'
     *  Gain: '<S1404>/Derivative Gain'
     *  Sum: '<S1406>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH2_2 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_bt) * 100.0F;

    /* Switch: '<S1273>/Switch1' incorporates:
     *  Constant: '<S1273>/Constant'
     *  Gain: '<S1273>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_2'
     *  Saturate: '<S1418>/Saturation'
     *  Sum: '<S1273>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH2_2) {
      /* Sum: '<S1420>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1411>/Integrator'
       *  Gain: '<S1416>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_2 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_cj) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S1418>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH2_2 * u0 - rtU.speed_rpm_CH2_2;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S1273>/Switch1' */

    /* DiscreteIntegrator: '<S1356>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_2'
     */
    if (((rtU.reset_status2_2 > 0.0F) && (rtDW.Filter_PrevResetState_bl <= 0)) ||
        ((rtU.reset_status2_2 <= 0.0F) && (rtDW.Filter_PrevResetState_bl == 1)))
    {
      rtDW.Filter_DSTATE_ec = 0.0F;
    }

    /* Gain: '<S1364>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1356>/Filter'
     *  Gain: '<S1354>/Derivative Gain'
     *  Sum: '<S1356>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH2_2 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_ec) * 100.0F;

    /* DiscreteIntegrator: '<S1361>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_2'
     */
    if (((rtU.reset_status2_2 > 0.0F) && (rtDW.Integrator_PrevResetState_cl <= 0))
        || ((rtU.reset_status2_2 <= 0.0F) && (rtDW.Integrator_PrevResetState_cl ==
          1))) {
      rtDW.Integrator_DSTATE_ki = 0.0F;
    }

    /* Sum: '<S1370>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1361>/Integrator'
     *  Gain: '<S1366>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_2 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_ki) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S1368>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_2' */
      rtY.ANG_OUT_CH2_2 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_2' */
      rtY.ANG_OUT_CH2_2 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH2_2' */
      rtY.ANG_OUT_CH2_2 = u0;
    }

    /* End of Saturate: '<S1368>/Saturation' */

    /* Chart: '<S1273>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_2'
     *  Inport: '<Root>/last_ecd_CH2_2'
     *  Sum: '<S1273>/Sum3'
     */
    Chart1(rtU.ecd_CH2_2 - rtU.last_ecd_CH2_2, &rtDW.u2_l, &rtDW.sf_Chart1_a);

    /* Outport: '<Root>/circle_out_CH2_2' incorporates:
     *  Inport: '<Root>/circle_CH2_2'
     *  Sum: '<S1273>/Sum4'
     */
    rtY.circle_out_CH2_2 = rtDW.u2_l + rtU.circle_CH2_2;

    /* Update for DiscreteIntegrator: '<S1411>/Integrator' incorporates:
     *  Gain: '<S1408>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_cj += rtP.ANG_A_I_CH2_2 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1406>/Filter' */
    rtDW.Filter_DSTATE_bt += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S1356>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1361>/Integrator'
     *  Inport: '<Root>/reset_status2_2'
     */
    rtDW.Filter_DSTATE_ec += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status2_2 > 0.0F) {
      rtDW.Filter_PrevResetState_bl = 1;
      rtDW.Integrator_PrevResetState_cl = 1;
    } else {
      if (rtU.reset_status2_2 < 0.0F) {
        rtDW.Filter_PrevResetState_bl = -1;
      } else if (rtU.reset_status2_2 == 0.0F) {
        rtDW.Filter_PrevResetState_bl = 0;
      } else {
        rtDW.Filter_PrevResetState_bl = 2;
      }

      if (rtU.reset_status2_2 < 0.0F) {
        rtDW.Integrator_PrevResetState_cl = -1;
      } else if (rtU.reset_status2_2 == 0.0F) {
        rtDW.Integrator_PrevResetState_cl = 0;
      } else {
        rtDW.Integrator_PrevResetState_cl = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1356>/Filter' */

    /* Update for DiscreteIntegrator: '<S1361>/Integrator' incorporates:
     *  Gain: '<S1358>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ki += rtP.ANG_S_I_CH2_2 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S9>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S9>/Switch Case' */

  /* SwitchCase: '<S10>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH2_3'
   */
  switch ((int32_T)rtU.status_CH2_3) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S10>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1428>/Action Port'
     */
    /* Sum: '<S1428>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_3'
     *  Inport: '<Root>/target_CH2_3'
     */
    rtb_Switch2_ft = rtU.target_CH2_3 - rtU.speed_rpm_CH2_3;

    /* Switch: '<S1428>/Switch2' incorporates:
     *  Abs: '<S1428>/Abs'
     *  Constant: '<S1428>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH2_3)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S1428>/Switch2' */

    /* DiscreteIntegrator: '<S1459>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_3'
     */
    if (((rtU.reset_status2_3 > 0.0F) && (rtDW.Filter_PrevResetState_jt <= 0)) ||
        ((rtU.reset_status2_3 <= 0.0F) && (rtDW.Filter_PrevResetState_jt == 1)))
    {
      rtDW.Filter_DSTATE_f5 = 0.0F;
    }

    /* Gain: '<S1467>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1459>/Filter'
     *  Gain: '<S1457>/Derivative Gain'
     *  Sum: '<S1459>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH2_3 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_f5) * 100.0F;

    /* DiscreteIntegrator: '<S1464>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_3'
     */
    if (((rtU.reset_status2_3 > 0.0F) && (rtDW.Integrator_PrevResetState_on <= 0))
        || ((rtU.reset_status2_3 <= 0.0F) && (rtDW.Integrator_PrevResetState_on ==
          1))) {
      rtDW.Integrator_DSTATE_ex = 0.0F;
    }

    /* Sum: '<S1473>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1464>/Integrator'
     *  Gain: '<S1469>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_3 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_ex) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S1471>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_3' */
      rtY.SPD_OUT_CH2_3 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_3' */
      rtY.SPD_OUT_CH2_3 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH2_3' */
      rtY.SPD_OUT_CH2_3 = u0;
    }

    /* End of Saturate: '<S1471>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1459>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1464>/Integrator'
     *  Inport: '<Root>/reset_status2_3'
     */
    rtDW.Filter_DSTATE_f5 += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status2_3 > 0.0F) {
      rtDW.Filter_PrevResetState_jt = 1;
      rtDW.Integrator_PrevResetState_on = 1;
    } else {
      if (rtU.reset_status2_3 < 0.0F) {
        rtDW.Filter_PrevResetState_jt = -1;
      } else if (rtU.reset_status2_3 == 0.0F) {
        rtDW.Filter_PrevResetState_jt = 0;
      } else {
        rtDW.Filter_PrevResetState_jt = 2;
      }

      if (rtU.reset_status2_3 < 0.0F) {
        rtDW.Integrator_PrevResetState_on = -1;
      } else if (rtU.reset_status2_3 == 0.0F) {
        rtDW.Integrator_PrevResetState_on = 0;
      } else {
        rtDW.Integrator_PrevResetState_on = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1459>/Filter' */

    /* Update for DiscreteIntegrator: '<S1464>/Integrator' incorporates:
     *  Gain: '<S1461>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ex += rtP.SPD_I_CH2_3 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S10>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S10>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1429>/Action Port'
     */
    /* Sum: '<S1429>/Sum' incorporates:
     *  Gain: '<S1429>/Gain'
     *  Inport: '<Root>/circle_CH2_3'
     *  Inport: '<Root>/ecd_CH2_3'
     *  Inport: '<Root>/target_CH2_3'
     *  Sum: '<S1429>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH2_3 - (8191.0F * rtU.circle_CH2_3 +
      rtU.ecd_CH2_3);

    /* Abs: '<S1429>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S1429>/Switch2' incorporates:
     *  Constant: '<S1429>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH2_3)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S1429>/Switch2' */

    /* Gain: '<S1570>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1562>/Filter'
     *  Gain: '<S1560>/Derivative Gain'
     *  Sum: '<S1562>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH2_3 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_m3) * 100.0F;

    /* Switch: '<S1429>/Switch1' incorporates:
     *  Constant: '<S1429>/Constant'
     *  Gain: '<S1429>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_3'
     *  Saturate: '<S1574>/Saturation'
     *  Sum: '<S1429>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH2_3) {
      /* Sum: '<S1576>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1567>/Integrator'
       *  Gain: '<S1572>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_3 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_m) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S1574>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH2_3 * u0 - rtU.speed_rpm_CH2_3;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S1429>/Switch1' */

    /* DiscreteIntegrator: '<S1512>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_3'
     */
    if (((rtU.reset_status2_3 > 0.0F) && (rtDW.Filter_PrevResetState_a <= 0)) ||
        ((rtU.reset_status2_3 <= 0.0F) && (rtDW.Filter_PrevResetState_a == 1)))
    {
      rtDW.Filter_DSTATE_fhy = 0.0F;
    }

    /* Gain: '<S1520>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1512>/Filter'
     *  Gain: '<S1510>/Derivative Gain'
     *  Sum: '<S1512>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH2_3 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_fhy) * 100.0F;

    /* DiscreteIntegrator: '<S1517>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_3'
     */
    if (((rtU.reset_status2_3 > 0.0F) && (rtDW.Integrator_PrevResetState_p <= 0))
        || ((rtU.reset_status2_3 <= 0.0F) && (rtDW.Integrator_PrevResetState_p ==
          1))) {
      rtDW.Integrator_DSTATE_im = 0.0F;
    }

    /* Sum: '<S1526>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1517>/Integrator'
     *  Gain: '<S1522>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_3 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_im) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S1524>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_3' */
      rtY.ANG_OUT_CH2_3 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_3' */
      rtY.ANG_OUT_CH2_3 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH2_3' */
      rtY.ANG_OUT_CH2_3 = u0;
    }

    /* End of Saturate: '<S1524>/Saturation' */

    /* Chart: '<S1429>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_3'
     *  Inport: '<Root>/last_ecd_CH2_3'
     *  Sum: '<S1429>/Sum3'
     */
    Chart1(rtU.ecd_CH2_3 - rtU.last_ecd_CH2_3, &rtDW.u2_f, &rtDW.sf_Chart1_aw);

    /* Outport: '<Root>/circle_out_CH2_3' incorporates:
     *  Inport: '<Root>/circle_CH2_3'
     *  Sum: '<S1429>/Sum4'
     */
    rtY.circle_out_CH2_3 = rtDW.u2_f + rtU.circle_CH2_3;

    /* Update for DiscreteIntegrator: '<S1567>/Integrator' incorporates:
     *  Gain: '<S1564>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_m += rtP.ANG_A_I_CH2_3 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1562>/Filter' */
    rtDW.Filter_DSTATE_m3 += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S1512>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1517>/Integrator'
     *  Inport: '<Root>/reset_status2_3'
     */
    rtDW.Filter_DSTATE_fhy += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status2_3 > 0.0F) {
      rtDW.Filter_PrevResetState_a = 1;
      rtDW.Integrator_PrevResetState_p = 1;
    } else {
      if (rtU.reset_status2_3 < 0.0F) {
        rtDW.Filter_PrevResetState_a = -1;
      } else if (rtU.reset_status2_3 == 0.0F) {
        rtDW.Filter_PrevResetState_a = 0;
      } else {
        rtDW.Filter_PrevResetState_a = 2;
      }

      if (rtU.reset_status2_3 < 0.0F) {
        rtDW.Integrator_PrevResetState_p = -1;
      } else if (rtU.reset_status2_3 == 0.0F) {
        rtDW.Integrator_PrevResetState_p = 0;
      } else {
        rtDW.Integrator_PrevResetState_p = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1512>/Filter' */

    /* Update for DiscreteIntegrator: '<S1517>/Integrator' incorporates:
     *  Gain: '<S1514>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_im += rtP.ANG_S_I_CH2_3 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S10>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S10>/Switch Case' */

  /* SwitchCase: '<S11>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH2_4'
   */
  switch ((int32_T)rtU.status_CH2_4) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S11>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1584>/Action Port'
     */
    /* Sum: '<S1584>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_4'
     *  Inport: '<Root>/target_CH2_4'
     */
    rtb_Switch2_ft = rtU.target_CH2_4 - rtU.speed_rpm_CH2_4;

    /* Switch: '<S1584>/Switch2' incorporates:
     *  Abs: '<S1584>/Abs'
     *  Constant: '<S1584>/Constant'
     */
    if (!((real32_T)fabs(rtb_Switch2_ft) > rtP.DEADBAND_spr_CH2_4)) {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S1584>/Switch2' */

    /* DiscreteIntegrator: '<S1615>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_4'
     */
    if (((rtU.reset_status2_4 > 0.0F) && (rtDW.Filter_PrevResetState_lb <= 0)) ||
        ((rtU.reset_status2_4 <= 0.0F) && (rtDW.Filter_PrevResetState_lb == 1)))
    {
      rtDW.Filter_DSTATE_d = 0.0F;
    }

    /* Gain: '<S1623>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1615>/Filter'
     *  Gain: '<S1613>/Derivative Gain'
     *  Sum: '<S1615>/SumD'
     */
    rtb_FilterCoefficient_jq = (rtP.SPD_D_CH2_4 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_d) * 100.0F;

    /* DiscreteIntegrator: '<S1620>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_4'
     */
    if (((rtU.reset_status2_4 > 0.0F) && (rtDW.Integrator_PrevResetState_kd <= 0))
        || ((rtU.reset_status2_4 <= 0.0F) && (rtDW.Integrator_PrevResetState_kd ==
          1))) {
      rtDW.Integrator_DSTATE_e5 = 0.0F;
    }

    /* Sum: '<S1629>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1620>/Integrator'
     *  Gain: '<S1625>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_4 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_e5) +
      rtb_FilterCoefficient_jq;

    /* Saturate: '<S1627>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_4' */
      rtY.SPD_OUT_CH2_4 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_4' */
      rtY.SPD_OUT_CH2_4 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH2_4' */
      rtY.SPD_OUT_CH2_4 = u0;
    }

    /* End of Saturate: '<S1627>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1615>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1620>/Integrator'
     *  Inport: '<Root>/reset_status2_4'
     */
    rtDW.Filter_DSTATE_d += 0.001F * rtb_FilterCoefficient_jq;
    if (rtU.reset_status2_4 > 0.0F) {
      rtDW.Filter_PrevResetState_lb = 1;
      rtDW.Integrator_PrevResetState_kd = 1;
    } else {
      if (rtU.reset_status2_4 < 0.0F) {
        rtDW.Filter_PrevResetState_lb = -1;
      } else if (rtU.reset_status2_4 == 0.0F) {
        rtDW.Filter_PrevResetState_lb = 0;
      } else {
        rtDW.Filter_PrevResetState_lb = 2;
      }

      if (rtU.reset_status2_4 < 0.0F) {
        rtDW.Integrator_PrevResetState_kd = -1;
      } else if (rtU.reset_status2_4 == 0.0F) {
        rtDW.Integrator_PrevResetState_kd = 0;
      } else {
        rtDW.Integrator_PrevResetState_kd = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1615>/Filter' */

    /* Update for DiscreteIntegrator: '<S1620>/Integrator' incorporates:
     *  Gain: '<S1617>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_e5 += rtP.SPD_I_CH2_4 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S11>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S11>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1585>/Action Port'
     */
    /* Sum: '<S1585>/Sum' incorporates:
     *  Gain: '<S1585>/Gain'
     *  Inport: '<Root>/circle_CH2_4'
     *  Inport: '<Root>/ecd_CH2_4'
     *  Inport: '<Root>/target_CH2_4'
     *  Sum: '<S1585>/Sum2'
     */
    rtb_FilterCoefficient_jq = rtU.target_CH2_4 - (8191.0F * rtU.circle_CH2_4 +
      rtU.ecd_CH2_4);

    /* Abs: '<S1585>/Abs' */
    rtb_Switch2_ft = (real32_T)fabs(rtb_FilterCoefficient_jq);

    /* Switch: '<S1585>/Switch2' incorporates:
     *  Constant: '<S1585>/Constant'
     */
    if (!(rtb_Switch2_ft > rtP.DEADBAND_CH2_4)) {
      rtb_FilterCoefficient_jq = 0.0F;
    }

    /* End of Switch: '<S1585>/Switch2' */

    /* Gain: '<S1726>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1718>/Filter'
     *  Gain: '<S1716>/Derivative Gain'
     *  Sum: '<S1718>/SumD'
     */
    rtb_FilterCoefficient_hh = (rtP.ANG_A_D_CH2_4 * rtb_FilterCoefficient_jq -
      rtDW.Filter_DSTATE_c) * 100.0F;

    /* Switch: '<S1585>/Switch1' incorporates:
     *  Constant: '<S1585>/Constant'
     *  Gain: '<S1585>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_4'
     *  Saturate: '<S1730>/Saturation'
     *  Sum: '<S1585>/Sum1'
     */
    if (rtb_Switch2_ft > rtP.DEADBAND_CH2_4) {
      /* Sum: '<S1732>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1723>/Integrator'
       *  Gain: '<S1728>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_4 * rtb_FilterCoefficient_jq +
            rtDW.Integrator_DSTATE_a2) + rtb_FilterCoefficient_hh;

      /* Saturate: '<S1730>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Switch2_ft = rtP.TRANS_CH2_4 * u0 - rtU.speed_rpm_CH2_4;
    } else {
      rtb_Switch2_ft = 0.0F;
    }

    /* End of Switch: '<S1585>/Switch1' */

    /* DiscreteIntegrator: '<S1668>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_4'
     */
    if (((rtU.reset_status2_4 > 0.0F) && (rtDW.Filter_PrevResetState_jc <= 0)) ||
        ((rtU.reset_status2_4 <= 0.0F) && (rtDW.Filter_PrevResetState_jc == 1)))
    {
      rtDW.Filter_DSTATE_m1 = 0.0F;
    }

    /* Gain: '<S1676>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1668>/Filter'
     *  Gain: '<S1666>/Derivative Gain'
     *  Sum: '<S1668>/SumD'
     */
    rtb_FilterCoefficient_ba = (rtP.ANG_S_D_CH2_4 * rtb_Switch2_ft -
      rtDW.Filter_DSTATE_m1) * 100.0F;

    /* DiscreteIntegrator: '<S1673>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_4'
     */
    if (((rtU.reset_status2_4 > 0.0F) && (rtDW.Integrator_PrevResetState_od <= 0))
        || ((rtU.reset_status2_4 <= 0.0F) && (rtDW.Integrator_PrevResetState_od ==
          1))) {
      rtDW.Integrator_DSTATE_os = 0.0F;
    }

    /* Sum: '<S1682>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1673>/Integrator'
     *  Gain: '<S1678>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_4 * rtb_Switch2_ft + rtDW.Integrator_DSTATE_os) +
      rtb_FilterCoefficient_ba;

    /* Saturate: '<S1680>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_4' */
      rtY.ANG_OUT_CH2_4 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_4' */
      rtY.ANG_OUT_CH2_4 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH2_4' */
      rtY.ANG_OUT_CH2_4 = u0;
    }

    /* End of Saturate: '<S1680>/Saturation' */

    /* Chart: '<S1585>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_4'
     *  Inport: '<Root>/last_ecd_CH2_4'
     *  Sum: '<S1585>/Sum3'
     */
    Chart1(rtU.ecd_CH2_4 - rtU.last_ecd_CH2_4, &rtDW.u2_o, &rtDW.sf_Chart1_e);

    /* Outport: '<Root>/circle_out_CH2_4' incorporates:
     *  Inport: '<Root>/circle_CH2_4'
     *  Sum: '<S1585>/Sum4'
     */
    rtY.circle_out_CH2_4 = rtDW.u2_o + rtU.circle_CH2_4;

    /* Update for DiscreteIntegrator: '<S1723>/Integrator' incorporates:
     *  Gain: '<S1720>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_a2 += rtP.ANG_A_I_CH2_4 * rtb_FilterCoefficient_jq *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1718>/Filter' */
    rtDW.Filter_DSTATE_c += 0.001F * rtb_FilterCoefficient_hh;

    /* Update for DiscreteIntegrator: '<S1668>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1673>/Integrator'
     *  Inport: '<Root>/reset_status2_4'
     */
    rtDW.Filter_DSTATE_m1 += 0.001F * rtb_FilterCoefficient_ba;
    if (rtU.reset_status2_4 > 0.0F) {
      rtDW.Filter_PrevResetState_jc = 1;
      rtDW.Integrator_PrevResetState_od = 1;
    } else {
      if (rtU.reset_status2_4 < 0.0F) {
        rtDW.Filter_PrevResetState_jc = -1;
      } else if (rtU.reset_status2_4 == 0.0F) {
        rtDW.Filter_PrevResetState_jc = 0;
      } else {
        rtDW.Filter_PrevResetState_jc = 2;
      }

      if (rtU.reset_status2_4 < 0.0F) {
        rtDW.Integrator_PrevResetState_od = -1;
      } else if (rtU.reset_status2_4 == 0.0F) {
        rtDW.Integrator_PrevResetState_od = 0;
      } else {
        rtDW.Integrator_PrevResetState_od = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1668>/Filter' */

    /* Update for DiscreteIntegrator: '<S1673>/Integrator' incorporates:
     *  Gain: '<S1670>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_os += rtP.ANG_S_I_CH2_4 * rtb_Switch2_ft * 0.001F;

    /* End of Outputs for SubSystem: '<S11>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S11>/Switch Case' */

  /* Update for DiscreteIntegrator: '<S3333>/Integrator' incorporates:
   *  DiscreteIntegrator: '<S3328>/Filter'
   *  Gain: '<S3330>/Integral Gain'
   *  Inport: '<Root>/reset_status_dist'
   */
  rtDW.Integrator_DSTATE += rtP.POS_I * rtb_Integrator_ow * 0.001F;
  if (rtU.reset_status_dist > 0.0F) {
    rtDW.Integrator_PrevResetState = 1;
    rtDW.Filter_PrevResetState = 1;
  } else {
    if (rtU.reset_status_dist < 0.0F) {
      rtDW.Integrator_PrevResetState = -1;
    } else if (rtU.reset_status_dist == 0.0F) {
      rtDW.Integrator_PrevResetState = 0;
    } else {
      rtDW.Integrator_PrevResetState = 2;
    }

    if (rtU.reset_status_dist < 0.0F) {
      rtDW.Filter_PrevResetState = -1;
    } else if (rtU.reset_status_dist == 0.0F) {
      rtDW.Filter_PrevResetState = 0;
    } else {
      rtDW.Filter_PrevResetState = 2;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S3333>/Integrator' */

  /* Update for DiscreteIntegrator: '<S3328>/Filter' */
  rtDW.Filter_DSTATE += 0.001F * rtb_FilterCoefficient;

  /* Update for DiscreteIntegrator: '<S3383>/Integrator' incorporates:
   *  DiscreteIntegrator: '<S3378>/Filter'
   *  Gain: '<S3380>/Integral Gain'
   *  Inport: '<Root>/reset_status_ang'
   */
  rtDW.Integrator_DSTATE_e += rtP.POS_A_I * rtb_Switch1_bt * 0.001F;
  if (rtU.reset_status_ang > 0.0F) {
    rtDW.Integrator_PrevResetState_k = 1;
    rtDW.Filter_PrevResetState_p = 1;
  } else {
    if (rtU.reset_status_ang < 0.0F) {
      rtDW.Integrator_PrevResetState_k = -1;
    } else if (rtU.reset_status_ang == 0.0F) {
      rtDW.Integrator_PrevResetState_k = 0;
    } else {
      rtDW.Integrator_PrevResetState_k = 2;
    }

    if (rtU.reset_status_ang < 0.0F) {
      rtDW.Filter_PrevResetState_p = -1;
    } else if (rtU.reset_status_ang == 0.0F) {
      rtDW.Filter_PrevResetState_p = 0;
    } else {
      rtDW.Filter_PrevResetState_p = 2;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S3383>/Integrator' */

  /* Update for DiscreteIntegrator: '<S3378>/Filter' */
  rtDW.Filter_DSTATE_l += 0.001F * rtb_FilterCoefficient_lb;
}

/* Model initialize function */
void PID_MODEL_initialize(void)
{
  /* InitializeConditions for DiscreteIntegrator: '<S3333>/Integrator' */
  rtDW.Integrator_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S3328>/Filter' */
  rtDW.Filter_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S3383>/Integrator' */
  rtDW.Integrator_PrevResetState_k = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S3378>/Filter' */
  rtDW.Filter_PrevResetState_p = 2;

  /* SystemInitialize for IfAction SubSystem: '<S1>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S55>/Filter' */
  rtDW.Filter_PrevResetState_bi = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S60>/Integrator' */
  rtDW.Integrator_PrevResetState_a2a = 2;

  /* End of SystemInitialize for SubSystem: '<S1>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S1>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S108>/Filter' */
  rtDW.Filter_PrevResetState_hk = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S113>/Integrator' */
  rtDW.Integrator_PrevResetState_mx = 2;

  /* SystemInitialize for Chart: '<S25>/Chart1' */
  Chart1_Init(&rtDW.u2_nnb);

  /* End of SystemInitialize for SubSystem: '<S1>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S2>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S211>/Filter' */
  rtDW.Filter_PrevResetState_o2 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S216>/Integrator' */
  rtDW.Integrator_PrevResetState_ar = 2;

  /* End of SystemInitialize for SubSystem: '<S2>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S2>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S264>/Filter' */
  rtDW.Filter_PrevResetState_a2 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S269>/Integrator' */
  rtDW.Integrator_PrevResetState_d = 2;

  /* SystemInitialize for Chart: '<S181>/Chart1' */
  Chart1_Init(&rtDW.u2_jxj);

  /* End of SystemInitialize for SubSystem: '<S2>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S3>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S367>/Filter' */
  rtDW.Filter_PrevResetState_pr = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S372>/Integrator' */
  rtDW.Integrator_PrevResetState_g1 = 2;

  /* End of SystemInitialize for SubSystem: '<S3>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S3>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S420>/Filter' */
  rtDW.Filter_PrevResetState_na = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S425>/Integrator' */
  rtDW.Integrator_PrevResetState_pi = 2;

  /* SystemInitialize for Chart: '<S337>/Chart1' */
  Chart1_Init(&rtDW.u2_j2);

  /* End of SystemInitialize for SubSystem: '<S3>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S4>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S523>/Filter' */
  rtDW.Filter_PrevResetState_pt = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S528>/Integrator' */
  rtDW.Integrator_PrevResetState_j3 = 2;

  /* End of SystemInitialize for SubSystem: '<S4>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S4>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S576>/Filter' */
  rtDW.Filter_PrevResetState_gs = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S581>/Integrator' */
  rtDW.Integrator_PrevResetState_f = 2;

  /* SystemInitialize for Chart: '<S493>/Chart1' */
  Chart1_Init(&rtDW.u2_a);

  /* End of SystemInitialize for SubSystem: '<S4>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S5>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S679>/Filter' */
  rtDW.Filter_PrevResetState_ds = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S684>/Integrator' */
  rtDW.Integrator_PrevResetState_jx = 2;

  /* End of SystemInitialize for SubSystem: '<S5>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S5>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S732>/Filter' */
  rtDW.Filter_PrevResetState_k = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S737>/Integrator' */
  rtDW.Integrator_PrevResetState_a2 = 2;

  /* SystemInitialize for Chart: '<S649>/Chart1' */
  Chart1_Init(&rtDW.u2_c);

  /* End of SystemInitialize for SubSystem: '<S5>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S6>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S835>/Filter' */
  rtDW.Filter_PrevResetState_i = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S840>/Integrator' */
  rtDW.Integrator_PrevResetState_nb = 2;

  /* End of SystemInitialize for SubSystem: '<S6>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S6>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S888>/Filter' */
  rtDW.Filter_PrevResetState_lp = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S893>/Integrator' */
  rtDW.Integrator_PrevResetState_j = 2;

  /* SystemInitialize for Chart: '<S805>/Chart1' */
  Chart1_Init(&rtDW.u2_nn);

  /* End of SystemInitialize for SubSystem: '<S6>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S7>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S991>/Filter' */
  rtDW.Filter_PrevResetState_am = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S996>/Integrator' */
  rtDW.Integrator_PrevResetState_ed = 2;

  /* End of SystemInitialize for SubSystem: '<S7>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S7>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1044>/Filter' */
  rtDW.Filter_PrevResetState_nc = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1049>/Integrator' */
  rtDW.Integrator_PrevResetState_gr = 2;

  /* SystemInitialize for Chart: '<S961>/Chart1' */
  Chart1_Init(&rtDW.u2_f4);

  /* End of SystemInitialize for SubSystem: '<S7>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S12>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S1771>/Filter' */
  rtDW.Filter_PrevResetState_n = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1776>/Integrator' */
  rtDW.Integrator_PrevResetState_km = 2;

  /* End of SystemInitialize for SubSystem: '<S12>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S12>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1824>/Filter' */
  rtDW.Filter_PrevResetState_f3 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1829>/Integrator' */
  rtDW.Integrator_PrevResetState_bs = 2;

  /* SystemInitialize for Chart: '<S1741>/Chart1' */
  Chart1_Init(&rtDW.u2_n2);

  /* End of SystemInitialize for SubSystem: '<S12>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S13>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S1927>/Filter' */
  rtDW.Filter_PrevResetState_jv = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1932>/Integrator' */
  rtDW.Integrator_PrevResetState_gl = 2;

  /* End of SystemInitialize for SubSystem: '<S13>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S13>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1980>/Filter' */
  rtDW.Filter_PrevResetState_f = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1985>/Integrator' */
  rtDW.Integrator_PrevResetState_n = 2;

  /* SystemInitialize for Chart: '<S1897>/Chart1' */
  Chart1_Init(&rtDW.u2_h);

  /* End of SystemInitialize for SubSystem: '<S13>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S14>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S2083>/Filter' */
  rtDW.Filter_PrevResetState_he = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2088>/Integrator' */
  rtDW.Integrator_PrevResetState_ik = 2;

  /* End of SystemInitialize for SubSystem: '<S14>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S14>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S2136>/Filter' */
  rtDW.Filter_PrevResetState_l = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2141>/Integrator' */
  rtDW.Integrator_PrevResetState_kl = 2;

  /* SystemInitialize for Chart: '<S2053>/Chart1' */
  Chart1_Init(&rtDW.u2_e);

  /* End of SystemInitialize for SubSystem: '<S14>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S15>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S2239>/Filter' */
  rtDW.Filter_PrevResetState_dp = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2244>/Integrator' */
  rtDW.Integrator_PrevResetState_e1k = 2;

  /* End of SystemInitialize for SubSystem: '<S15>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S15>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S2292>/Filter' */
  rtDW.Filter_PrevResetState_p0 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2297>/Integrator' */
  rtDW.Integrator_PrevResetState_c = 2;

  /* SystemInitialize for Chart: '<S2209>/Chart1' */
  Chart1_Init(&rtDW.u2_jx);

  /* End of SystemInitialize for SubSystem: '<S15>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S16>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S2395>/Filter' */
  rtDW.Filter_PrevResetState_hr = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2400>/Integrator' */
  rtDW.Integrator_PrevResetState_e1 = 2;

  /* End of SystemInitialize for SubSystem: '<S16>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S16>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S2448>/Filter' */
  rtDW.Filter_PrevResetState_b = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2453>/Integrator' */
  rtDW.Integrator_PrevResetState_mv = 2;

  /* SystemInitialize for Chart: '<S2365>/Chart1' */
  Chart1_Init(&rtDW.u2_m);

  /* End of SystemInitialize for SubSystem: '<S16>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S17>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S2551>/Filter' */
  rtDW.Filter_PrevResetState_j = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2556>/Integrator' */
  rtDW.Integrator_PrevResetState_b0 = 2;

  /* End of SystemInitialize for SubSystem: '<S17>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S17>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S2604>/Filter' */
  rtDW.Filter_PrevResetState_el = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2609>/Integrator' */
  rtDW.Integrator_PrevResetState_e = 2;

  /* SystemInitialize for Chart: '<S2521>/Chart1' */
  Chart1_Init(&rtDW.u2_n);

  /* End of SystemInitialize for SubSystem: '<S17>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S18>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S2707>/Filter' */
  rtDW.Filter_PrevResetState_g = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2712>/Integrator' */
  rtDW.Integrator_PrevResetState_i = 2;

  /* End of SystemInitialize for SubSystem: '<S18>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S18>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S2760>/Filter' */
  rtDW.Filter_PrevResetState_d3 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2765>/Integrator' */
  rtDW.Integrator_PrevResetState_g = 2;

  /* SystemInitialize for Chart: '<S2677>/Chart1' */
  Chart1_Init(&rtDW.u2_j);

  /* End of SystemInitialize for SubSystem: '<S18>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S19>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S2863>/Filter' */
  rtDW.Filter_PrevResetState_hn = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2868>/Integrator' */
  rtDW.Integrator_PrevResetState_my = 2;

  /* End of SystemInitialize for SubSystem: '<S19>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S19>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S2916>/Filter' */
  rtDW.Filter_PrevResetState_e = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2921>/Integrator' */
  rtDW.Integrator_PrevResetState_m = 2;

  /* SystemInitialize for Chart: '<S2833>/Chart1' */
  Chart1_Init(&rtDW.u2_p);

  /* End of SystemInitialize for SubSystem: '<S19>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S20>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S3019>/Filter' */
  rtDW.Filter_PrevResetState_c4 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S3024>/Integrator' */
  rtDW.Integrator_PrevResetState_h = 2;

  /* End of SystemInitialize for SubSystem: '<S20>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S20>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S3072>/Filter' */
  rtDW.Filter_PrevResetState_c = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S3077>/Integrator' */
  rtDW.Integrator_PrevResetState_b = 2;

  /* SystemInitialize for Chart: '<S2989>/Chart1' */
  Chart1_Init(&rtDW.u2_b);

  /* End of SystemInitialize for SubSystem: '<S20>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S21>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S3175>/Filter' */
  rtDW.Filter_PrevResetState_h = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S3180>/Integrator' */
  rtDW.Integrator_PrevResetState_a = 2;

  /* End of SystemInitialize for SubSystem: '<S21>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S21>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S3228>/Filter' */
  rtDW.Filter_PrevResetState_d = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S3233>/Integrator' */
  rtDW.Integrator_PrevResetState_o = 2;

  /* SystemInitialize for Chart: '<S3145>/Chart1' */
  Chart1_Init(&rtDW.u2);

  /* End of SystemInitialize for SubSystem: '<S21>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S8>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S1147>/Filter' */
  rtDW.Filter_PrevResetState_do = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1152>/Integrator' */
  rtDW.Integrator_PrevResetState_o4 = 2;

  /* End of SystemInitialize for SubSystem: '<S8>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S8>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1200>/Filter' */
  rtDW.Filter_PrevResetState_o = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1205>/Integrator' */
  rtDW.Integrator_PrevResetState_io = 2;

  /* SystemInitialize for Chart: '<S1117>/Chart1' */
  Chart1_Init(&rtDW.u2_fb);

  /* End of SystemInitialize for SubSystem: '<S8>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S9>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S1303>/Filter' */
  rtDW.Filter_PrevResetState_af = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1308>/Integrator' */
  rtDW.Integrator_PrevResetState_c3 = 2;

  /* End of SystemInitialize for SubSystem: '<S9>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S9>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1356>/Filter' */
  rtDW.Filter_PrevResetState_bl = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1361>/Integrator' */
  rtDW.Integrator_PrevResetState_cl = 2;

  /* SystemInitialize for Chart: '<S1273>/Chart1' */
  Chart1_Init(&rtDW.u2_l);

  /* End of SystemInitialize for SubSystem: '<S9>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S10>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S1459>/Filter' */
  rtDW.Filter_PrevResetState_jt = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1464>/Integrator' */
  rtDW.Integrator_PrevResetState_on = 2;

  /* End of SystemInitialize for SubSystem: '<S10>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S10>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1512>/Filter' */
  rtDW.Filter_PrevResetState_a = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1517>/Integrator' */
  rtDW.Integrator_PrevResetState_p = 2;

  /* SystemInitialize for Chart: '<S1429>/Chart1' */
  Chart1_Init(&rtDW.u2_f);

  /* End of SystemInitialize for SubSystem: '<S10>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S11>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S1615>/Filter' */
  rtDW.Filter_PrevResetState_lb = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1620>/Integrator' */
  rtDW.Integrator_PrevResetState_kd = 2;

  /* End of SystemInitialize for SubSystem: '<S11>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S11>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1668>/Filter' */
  rtDW.Filter_PrevResetState_jc = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1673>/Integrator' */
  rtDW.Integrator_PrevResetState_od = 2;

  /* SystemInitialize for Chart: '<S1585>/Chart1' */
  Chart1_Init(&rtDW.u2_o);

  /* End of SystemInitialize for SubSystem: '<S11>/If Action_speed Subsystem1' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
