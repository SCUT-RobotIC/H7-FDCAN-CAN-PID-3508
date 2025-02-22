/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PID_MODEL.c
 *
 * Code generated for Simulink model 'PID_MODEL'.
 *
 * Model version                  : 4.4
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Sat Feb 22 20:33:40 2025
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

/* Named constants for Chart: '<S24>/Chart1' */
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
 *    '<S24>/Chart1'
 *    '<S180>/Chart1'
 *    '<S336>/Chart1'
 *    '<S492>/Chart1'
 *    '<S648>/Chart1'
 *    '<S804>/Chart1'
 *    '<S960>/Chart1'
 *    '<S1116>/Chart1'
 *    '<S1272>/Chart1'
 *    '<S1428>/Chart1'
 *    ...
 */
static void Chart1_Init(real32_T *rty_u2)
{
  *rty_u2 = 0.0F;
}

/*
 * Output and update for atomic system:
 *    '<S24>/Chart1'
 *    '<S180>/Chart1'
 *    '<S336>/Chart1'
 *    '<S492>/Chart1'
 *    '<S648>/Chart1'
 *    '<S804>/Chart1'
 *    '<S960>/Chart1'
 *    '<S1116>/Chart1'
 *    '<S1272>/Chart1'
 *    '<S1428>/Chart1'
 *    ...
 */
static void Chart1(real32_T rtu_u1, real32_T *rty_u2, DW_Chart1 *localDW)
{
  /* Chart: '<S24>/Chart1' */
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

  /* End of Chart: '<S24>/Chart1' */
}

/* Model step function */
void PID_MODEL_step(void)
{
  real32_T rtb_FilterCoefficient;
  real32_T rtb_FilterCoefficient_ch;
  real32_T rtb_FilterCoefficient_eu;
  real32_T rtb_FilterCoefficient_nkj;
  real32_T rtb_Sum_cz;
  real32_T u0;

  /* Gain: '<S3335>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S3327>/Filter'
   *  Gain: '<S3325>/Derivative Gain'
   *  Inport: '<Root>/distance'
   *  Sum: '<S3327>/SumD'
   */
  rtb_FilterCoefficient = (rtP.POS_D * rtU.distance - rtDW.Filter_DSTATE) *
    100.0F;

  /* Sum: '<S3341>/Sum' incorporates:
   *  DiscreteIntegrator: '<S3332>/Integrator'
   *  Gain: '<S3337>/Proportional Gain'
   *  Inport: '<Root>/distance'
   */
  u0 = (rtP.POS_P * rtU.distance + rtDW.Integrator_DSTATE) +
    rtb_FilterCoefficient;

  /* Saturate: '<S3339>/Saturation' */
  if (u0 > 16384.0F) {
    /* Outport: '<Root>/vel_out' */
    rtY.vel_out = 16384.0F;
  } else if (u0 < -16384.0F) {
    /* Outport: '<Root>/vel_out' */
    rtY.vel_out = -16384.0F;
  } else {
    /* Outport: '<Root>/vel_out' */
    rtY.vel_out = u0;
  }

  /* End of Saturate: '<S3339>/Saturation' */

  /* SwitchCase: '<S1>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH1_1'
   */
  switch ((int32_T)rtU.status_CH1_1) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S1>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S23>/Action Port'
     */
    /* Sum: '<S23>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_1'
     *  Inport: '<Root>/target_CH1_1'
     */
    rtb_Sum_cz = rtU.target_CH1_1 - rtU.speed_rpm_CH1_1;

    /* DiscreteIntegrator: '<S54>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_1'
     */
    if (((rtU.reset_status1_1 > 0.0F) && (rtDW.Filter_PrevResetState_bi <= 0)) ||
        ((rtU.reset_status1_1 <= 0.0F) && (rtDW.Filter_PrevResetState_bi == 1)))
    {
      rtDW.Filter_DSTATE_ks = 0.0F;
    }

    /* Gain: '<S62>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S54>/Filter'
     *  Gain: '<S52>/Derivative Gain'
     *  Sum: '<S54>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH1_1 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_ks) * 100.0F;

    /* DiscreteIntegrator: '<S59>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_1'
     */
    if (((rtU.reset_status1_1 > 0.0F) && (rtDW.Integrator_PrevResetState_a2 <= 0))
        || ((rtU.reset_status1_1 <= 0.0F) && (rtDW.Integrator_PrevResetState_a2 ==
          1))) {
      rtDW.Integrator_DSTATE_lm = 0.0F;
    }

    /* Sum: '<S68>/Sum' incorporates:
     *  DiscreteIntegrator: '<S59>/Integrator'
     *  Gain: '<S64>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_1 * rtb_Sum_cz + rtDW.Integrator_DSTATE_lm) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S66>/Saturation' */
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

    /* End of Saturate: '<S66>/Saturation' */

    /* Update for DiscreteIntegrator: '<S54>/Filter' incorporates:
     *  DiscreteIntegrator: '<S59>/Integrator'
     *  Inport: '<Root>/reset_status1_1'
     */
    rtDW.Filter_DSTATE_ks += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status1_1 > 0.0F) {
      rtDW.Filter_PrevResetState_bi = 1;
      rtDW.Integrator_PrevResetState_a2 = 1;
    } else {
      if (rtU.reset_status1_1 < 0.0F) {
        rtDW.Filter_PrevResetState_bi = -1;
      } else if (rtU.reset_status1_1 == 0.0F) {
        rtDW.Filter_PrevResetState_bi = 0;
      } else {
        rtDW.Filter_PrevResetState_bi = 2;
      }

      if (rtU.reset_status1_1 < 0.0F) {
        rtDW.Integrator_PrevResetState_a2 = -1;
      } else if (rtU.reset_status1_1 == 0.0F) {
        rtDW.Integrator_PrevResetState_a2 = 0;
      } else {
        rtDW.Integrator_PrevResetState_a2 = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S54>/Filter' */

    /* Update for DiscreteIntegrator: '<S59>/Integrator' incorporates:
     *  Gain: '<S56>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_lm += rtP.SPD_I_CH1_1 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S1>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S1>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S24>/Action Port'
     */
    /* Sum: '<S24>/Sum' incorporates:
     *  Gain: '<S24>/Gain'
     *  Inport: '<Root>/circle_CH1_1'
     *  Inport: '<Root>/ecd_CH1_1'
     *  Inport: '<Root>/target_CH1_1'
     *  Sum: '<S24>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH1_1 - (8191.0F * rtU.circle_CH1_1 +
      rtU.ecd_CH1_1);

    /* Abs: '<S24>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S24>/Switch2' incorporates:
     *  Constant: '<S24>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH1_1)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S24>/Switch2' */

    /* Gain: '<S165>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S157>/Filter'
     *  Gain: '<S155>/Derivative Gain'
     *  Sum: '<S157>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH1_1 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_hs) * 100.0F;

    /* Switch: '<S24>/Switch1' incorporates:
     *  Constant: '<S24>/Constant'
     *  Gain: '<S24>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_1'
     *  Saturate: '<S169>/Saturation'
     *  Sum: '<S24>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH1_1) {
      /* Sum: '<S171>/Sum' incorporates:
       *  DiscreteIntegrator: '<S162>/Integrator'
       *  Gain: '<S167>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_1 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_ag) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S169>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH1_1 * u0 - rtU.speed_rpm_CH1_1;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S24>/Switch1' */

    /* DiscreteIntegrator: '<S107>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_1'
     */
    if (((rtU.reset_status1_1 > 0.0F) && (rtDW.Filter_PrevResetState_hk <= 0)) ||
        ((rtU.reset_status1_1 <= 0.0F) && (rtDW.Filter_PrevResetState_hk == 1)))
    {
      rtDW.Filter_DSTATE_jw = 0.0F;
    }

    /* Gain: '<S115>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S107>/Filter'
     *  Gain: '<S105>/Derivative Gain'
     *  Sum: '<S107>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH1_1 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_jw) * 100.0F;

    /* DiscreteIntegrator: '<S112>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_1'
     */
    if (((rtU.reset_status1_1 > 0.0F) && (rtDW.Integrator_PrevResetState_mx <= 0))
        || ((rtU.reset_status1_1 <= 0.0F) && (rtDW.Integrator_PrevResetState_mx ==
          1))) {
      rtDW.Integrator_DSTATE_l4 = 0.0F;
    }

    /* Sum: '<S121>/Sum' incorporates:
     *  DiscreteIntegrator: '<S112>/Integrator'
     *  Gain: '<S117>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_1 * rtb_Sum_cz + rtDW.Integrator_DSTATE_l4) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S119>/Saturation' */
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

    /* End of Saturate: '<S119>/Saturation' */

    /* Chart: '<S24>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_1'
     *  Inport: '<Root>/last_ecd_CH1_1'
     *  Sum: '<S24>/Sum3'
     */
    Chart1(rtU.ecd_CH1_1 - rtU.last_ecd_CH1_1, &rtDW.u2_nnb, &rtDW.sf_Chart1);

    /* Outport: '<Root>/circle_out_CH1_1' incorporates:
     *  Inport: '<Root>/circle_CH1_1'
     *  Sum: '<S24>/Sum4'
     */
    rtY.circle_out_CH1_1 = rtDW.u2_nnb + rtU.circle_CH1_1;

    /* Update for DiscreteIntegrator: '<S162>/Integrator' incorporates:
     *  Gain: '<S159>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ag += rtP.ANG_A_I_CH1_1 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S157>/Filter' */
    rtDW.Filter_DSTATE_hs += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S107>/Filter' incorporates:
     *  DiscreteIntegrator: '<S112>/Integrator'
     *  Inport: '<Root>/reset_status1_1'
     */
    rtDW.Filter_DSTATE_jw += 0.001F * rtb_FilterCoefficient_nkj;
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

    /* End of Update for DiscreteIntegrator: '<S107>/Filter' */

    /* Update for DiscreteIntegrator: '<S112>/Integrator' incorporates:
     *  Gain: '<S109>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_l4 += rtP.ANG_S_I_CH1_1 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S179>/Action Port'
     */
    /* Sum: '<S179>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_2'
     *  Inport: '<Root>/target_CH1_2'
     */
    rtb_Sum_cz = rtU.target_CH1_2 - rtU.speed_rpm_CH1_2;

    /* DiscreteIntegrator: '<S210>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_2'
     */
    if (((rtU.reset_status1_2 > 0.0F) && (rtDW.Filter_PrevResetState_eo <= 0)) ||
        ((rtU.reset_status1_2 <= 0.0F) && (rtDW.Filter_PrevResetState_eo == 1)))
    {
      rtDW.Filter_DSTATE_de = 0.0F;
    }

    /* Gain: '<S218>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S210>/Filter'
     *  Gain: '<S208>/Derivative Gain'
     *  Sum: '<S210>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH1_2 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_de) * 100.0F;

    /* DiscreteIntegrator: '<S215>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_2'
     */
    if (((rtU.reset_status1_2 > 0.0F) && (rtDW.Integrator_PrevResetState_np <= 0))
        || ((rtU.reset_status1_2 <= 0.0F) && (rtDW.Integrator_PrevResetState_np ==
          1))) {
      rtDW.Integrator_DSTATE_bv = 0.0F;
    }

    /* Sum: '<S224>/Sum' incorporates:
     *  DiscreteIntegrator: '<S215>/Integrator'
     *  Gain: '<S220>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_2 * rtb_Sum_cz + rtDW.Integrator_DSTATE_bv) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S222>/Saturation' */
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

    /* End of Saturate: '<S222>/Saturation' */

    /* Update for DiscreteIntegrator: '<S210>/Filter' incorporates:
     *  DiscreteIntegrator: '<S215>/Integrator'
     *  Inport: '<Root>/reset_status1_2'
     */
    rtDW.Filter_DSTATE_de += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status1_2 > 0.0F) {
      rtDW.Filter_PrevResetState_eo = 1;
      rtDW.Integrator_PrevResetState_np = 1;
    } else {
      if (rtU.reset_status1_2 < 0.0F) {
        rtDW.Filter_PrevResetState_eo = -1;
      } else if (rtU.reset_status1_2 == 0.0F) {
        rtDW.Filter_PrevResetState_eo = 0;
      } else {
        rtDW.Filter_PrevResetState_eo = 2;
      }

      if (rtU.reset_status1_2 < 0.0F) {
        rtDW.Integrator_PrevResetState_np = -1;
      } else if (rtU.reset_status1_2 == 0.0F) {
        rtDW.Integrator_PrevResetState_np = 0;
      } else {
        rtDW.Integrator_PrevResetState_np = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S210>/Filter' */

    /* Update for DiscreteIntegrator: '<S215>/Integrator' incorporates:
     *  Gain: '<S212>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_bv += rtP.SPD_I_CH1_2 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S2>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S2>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S180>/Action Port'
     */
    /* Sum: '<S180>/Sum' incorporates:
     *  Gain: '<S180>/Gain'
     *  Inport: '<Root>/circle_CH1_2'
     *  Inport: '<Root>/ecd_CH1_2'
     *  Inport: '<Root>/target_CH1_2'
     *  Sum: '<S180>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH1_2 - (8191.0F * rtU.circle_CH1_2 +
      rtU.ecd_CH1_2);

    /* Abs: '<S180>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S180>/Switch2' incorporates:
     *  Constant: '<S180>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH1_2)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S180>/Switch2' */

    /* Gain: '<S321>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S313>/Filter'
     *  Gain: '<S311>/Derivative Gain'
     *  Sum: '<S313>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH1_2 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_kn) * 100.0F;

    /* Switch: '<S180>/Switch1' incorporates:
     *  Constant: '<S180>/Constant'
     *  Gain: '<S180>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_2'
     *  Saturate: '<S325>/Saturation'
     *  Sum: '<S180>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH1_2) {
      /* Sum: '<S327>/Sum' incorporates:
       *  DiscreteIntegrator: '<S318>/Integrator'
       *  Gain: '<S323>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_2 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_j0) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S325>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH1_2 * u0 - rtU.speed_rpm_CH1_2;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S180>/Switch1' */

    /* DiscreteIntegrator: '<S263>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_2'
     */
    if (((rtU.reset_status1_2 > 0.0F) && (rtDW.Filter_PrevResetState_a2 <= 0)) ||
        ((rtU.reset_status1_2 <= 0.0F) && (rtDW.Filter_PrevResetState_a2 == 1)))
    {
      rtDW.Filter_DSTATE_ne = 0.0F;
    }

    /* Gain: '<S271>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S263>/Filter'
     *  Gain: '<S261>/Derivative Gain'
     *  Sum: '<S263>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH1_2 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_ne) * 100.0F;

    /* DiscreteIntegrator: '<S268>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_2'
     */
    if (((rtU.reset_status1_2 > 0.0F) && (rtDW.Integrator_PrevResetState_dc <= 0))
        || ((rtU.reset_status1_2 <= 0.0F) && (rtDW.Integrator_PrevResetState_dc ==
          1))) {
      rtDW.Integrator_DSTATE_k1 = 0.0F;
    }

    /* Sum: '<S277>/Sum' incorporates:
     *  DiscreteIntegrator: '<S268>/Integrator'
     *  Gain: '<S273>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_2 * rtb_Sum_cz + rtDW.Integrator_DSTATE_k1) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S275>/Saturation' */
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

    /* End of Saturate: '<S275>/Saturation' */

    /* Chart: '<S180>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_2'
     *  Inport: '<Root>/last_ecd_CH1_2'
     *  Sum: '<S180>/Sum3'
     */
    Chart1(rtU.ecd_CH1_2 - rtU.last_ecd_CH1_2, &rtDW.u2_jxj, &rtDW.sf_Chart1_m);

    /* Outport: '<Root>/circle_out_CH1_2' incorporates:
     *  Inport: '<Root>/circle_CH1_2'
     *  Sum: '<S180>/Sum4'
     */
    rtY.circle_out_CH1_2 = rtDW.u2_jxj + rtU.circle_CH1_2;

    /* Update for DiscreteIntegrator: '<S318>/Integrator' incorporates:
     *  Gain: '<S315>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_j0 += rtP.ANG_A_I_CH1_2 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S313>/Filter' */
    rtDW.Filter_DSTATE_kn += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S263>/Filter' incorporates:
     *  DiscreteIntegrator: '<S268>/Integrator'
     *  Inport: '<Root>/reset_status1_2'
     */
    rtDW.Filter_DSTATE_ne += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status1_2 > 0.0F) {
      rtDW.Filter_PrevResetState_a2 = 1;
      rtDW.Integrator_PrevResetState_dc = 1;
    } else {
      if (rtU.reset_status1_2 < 0.0F) {
        rtDW.Filter_PrevResetState_a2 = -1;
      } else if (rtU.reset_status1_2 == 0.0F) {
        rtDW.Filter_PrevResetState_a2 = 0;
      } else {
        rtDW.Filter_PrevResetState_a2 = 2;
      }

      if (rtU.reset_status1_2 < 0.0F) {
        rtDW.Integrator_PrevResetState_dc = -1;
      } else if (rtU.reset_status1_2 == 0.0F) {
        rtDW.Integrator_PrevResetState_dc = 0;
      } else {
        rtDW.Integrator_PrevResetState_dc = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S263>/Filter' */

    /* Update for DiscreteIntegrator: '<S268>/Integrator' incorporates:
     *  Gain: '<S265>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_k1 += rtP.ANG_S_I_CH1_2 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S335>/Action Port'
     */
    /* Sum: '<S335>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_3'
     *  Inport: '<Root>/target_CH1_3'
     */
    rtb_Sum_cz = rtU.target_CH1_3 - rtU.speed_rpm_CH1_3;

    /* DiscreteIntegrator: '<S366>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_3'
     */
    if (((rtU.reset_status1_3 > 0.0F) && (rtDW.Filter_PrevResetState_ev <= 0)) ||
        ((rtU.reset_status1_3 <= 0.0F) && (rtDW.Filter_PrevResetState_ev == 1)))
    {
      rtDW.Filter_DSTATE_jq = 0.0F;
    }

    /* Gain: '<S374>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S366>/Filter'
     *  Gain: '<S364>/Derivative Gain'
     *  Sum: '<S366>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH1_3 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_jq) * 100.0F;

    /* DiscreteIntegrator: '<S371>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_3'
     */
    if (((rtU.reset_status1_3 > 0.0F) && (rtDW.Integrator_PrevResetState_l1 <= 0))
        || ((rtU.reset_status1_3 <= 0.0F) && (rtDW.Integrator_PrevResetState_l1 ==
          1))) {
      rtDW.Integrator_DSTATE_ke = 0.0F;
    }

    /* Sum: '<S380>/Sum' incorporates:
     *  DiscreteIntegrator: '<S371>/Integrator'
     *  Gain: '<S376>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_3 * rtb_Sum_cz + rtDW.Integrator_DSTATE_ke) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S378>/Saturation' */
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

    /* End of Saturate: '<S378>/Saturation' */

    /* Update for DiscreteIntegrator: '<S366>/Filter' incorporates:
     *  DiscreteIntegrator: '<S371>/Integrator'
     *  Inport: '<Root>/reset_status1_3'
     */
    rtDW.Filter_DSTATE_jq += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status1_3 > 0.0F) {
      rtDW.Filter_PrevResetState_ev = 1;
      rtDW.Integrator_PrevResetState_l1 = 1;
    } else {
      if (rtU.reset_status1_3 < 0.0F) {
        rtDW.Filter_PrevResetState_ev = -1;
      } else if (rtU.reset_status1_3 == 0.0F) {
        rtDW.Filter_PrevResetState_ev = 0;
      } else {
        rtDW.Filter_PrevResetState_ev = 2;
      }

      if (rtU.reset_status1_3 < 0.0F) {
        rtDW.Integrator_PrevResetState_l1 = -1;
      } else if (rtU.reset_status1_3 == 0.0F) {
        rtDW.Integrator_PrevResetState_l1 = 0;
      } else {
        rtDW.Integrator_PrevResetState_l1 = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S366>/Filter' */

    /* Update for DiscreteIntegrator: '<S371>/Integrator' incorporates:
     *  Gain: '<S368>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ke += rtP.SPD_I_CH1_3 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S3>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S3>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S336>/Action Port'
     */
    /* Sum: '<S336>/Sum' incorporates:
     *  Gain: '<S336>/Gain'
     *  Inport: '<Root>/circle_CH1_3'
     *  Inport: '<Root>/ecd_CH1_3'
     *  Inport: '<Root>/target_CH1_3'
     *  Sum: '<S336>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH1_3 - (8191.0F * rtU.circle_CH1_3 +
      rtU.ecd_CH1_3);

    /* Abs: '<S336>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S336>/Switch2' incorporates:
     *  Constant: '<S336>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH1_3)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S336>/Switch2' */

    /* Gain: '<S477>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S469>/Filter'
     *  Gain: '<S467>/Derivative Gain'
     *  Sum: '<S469>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH1_3 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_gs) * 100.0F;

    /* Switch: '<S336>/Switch1' incorporates:
     *  Constant: '<S336>/Constant'
     *  Gain: '<S336>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_3'
     *  Saturate: '<S481>/Saturation'
     *  Sum: '<S336>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH1_3) {
      /* Sum: '<S483>/Sum' incorporates:
       *  DiscreteIntegrator: '<S474>/Integrator'
       *  Gain: '<S479>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_3 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_ik) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S481>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH1_3 * u0 - rtU.speed_rpm_CH1_3;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S336>/Switch1' */

    /* DiscreteIntegrator: '<S419>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_3'
     */
    if (((rtU.reset_status1_3 > 0.0F) && (rtDW.Filter_PrevResetState_na <= 0)) ||
        ((rtU.reset_status1_3 <= 0.0F) && (rtDW.Filter_PrevResetState_na == 1)))
    {
      rtDW.Filter_DSTATE_f5 = 0.0F;
    }

    /* Gain: '<S427>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S419>/Filter'
     *  Gain: '<S417>/Derivative Gain'
     *  Sum: '<S419>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH1_3 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_f5) * 100.0F;

    /* DiscreteIntegrator: '<S424>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_3'
     */
    if (((rtU.reset_status1_3 > 0.0F) && (rtDW.Integrator_PrevResetState_pi <= 0))
        || ((rtU.reset_status1_3 <= 0.0F) && (rtDW.Integrator_PrevResetState_pi ==
          1))) {
      rtDW.Integrator_DSTATE_l3w = 0.0F;
    }

    /* Sum: '<S433>/Sum' incorporates:
     *  DiscreteIntegrator: '<S424>/Integrator'
     *  Gain: '<S429>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_3 * rtb_Sum_cz + rtDW.Integrator_DSTATE_l3w) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S431>/Saturation' */
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

    /* End of Saturate: '<S431>/Saturation' */

    /* Chart: '<S336>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_3'
     *  Inport: '<Root>/last_ecd_CH1_3'
     *  Sum: '<S336>/Sum3'
     */
    Chart1(rtU.ecd_CH1_3 - rtU.last_ecd_CH1_3, &rtDW.u2_j2, &rtDW.sf_Chart1_h);

    /* Outport: '<Root>/circle_out_CH1_3' incorporates:
     *  Inport: '<Root>/circle_CH1_3'
     *  Sum: '<S336>/Sum4'
     */
    rtY.circle_out_CH1_3 = rtDW.u2_j2 + rtU.circle_CH1_3;

    /* Update for DiscreteIntegrator: '<S474>/Integrator' incorporates:
     *  Gain: '<S471>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ik += rtP.ANG_A_I_CH1_3 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S469>/Filter' */
    rtDW.Filter_DSTATE_gs += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S419>/Filter' incorporates:
     *  DiscreteIntegrator: '<S424>/Integrator'
     *  Inport: '<Root>/reset_status1_3'
     */
    rtDW.Filter_DSTATE_f5 += 0.001F * rtb_FilterCoefficient_nkj;
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

    /* End of Update for DiscreteIntegrator: '<S419>/Filter' */

    /* Update for DiscreteIntegrator: '<S424>/Integrator' incorporates:
     *  Gain: '<S421>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_l3w += rtP.ANG_S_I_CH1_3 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S491>/Action Port'
     */
    /* Sum: '<S491>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_4'
     *  Inport: '<Root>/target_CH1_4'
     */
    rtb_Sum_cz = rtU.target_CH1_4 - rtU.speed_rpm_CH1_4;

    /* DiscreteIntegrator: '<S522>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_4'
     */
    if (((rtU.reset_status1_4 > 0.0F) && (rtDW.Filter_PrevResetState_b0 <= 0)) ||
        ((rtU.reset_status1_4 <= 0.0F) && (rtDW.Filter_PrevResetState_b0 == 1)))
    {
      rtDW.Filter_DSTATE_in = 0.0F;
    }

    /* Gain: '<S530>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S522>/Filter'
     *  Gain: '<S520>/Derivative Gain'
     *  Sum: '<S522>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH1_4 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_in) * 100.0F;

    /* DiscreteIntegrator: '<S527>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_4'
     */
    if (((rtU.reset_status1_4 > 0.0F) && (rtDW.Integrator_PrevResetState_fz <= 0))
        || ((rtU.reset_status1_4 <= 0.0F) && (rtDW.Integrator_PrevResetState_fz ==
          1))) {
      rtDW.Integrator_DSTATE_ok = 0.0F;
    }

    /* Sum: '<S536>/Sum' incorporates:
     *  DiscreteIntegrator: '<S527>/Integrator'
     *  Gain: '<S532>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_4 * rtb_Sum_cz + rtDW.Integrator_DSTATE_ok) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S534>/Saturation' */
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

    /* End of Saturate: '<S534>/Saturation' */

    /* Update for DiscreteIntegrator: '<S522>/Filter' incorporates:
     *  DiscreteIntegrator: '<S527>/Integrator'
     *  Inport: '<Root>/reset_status1_4'
     */
    rtDW.Filter_DSTATE_in += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status1_4 > 0.0F) {
      rtDW.Filter_PrevResetState_b0 = 1;
      rtDW.Integrator_PrevResetState_fz = 1;
    } else {
      if (rtU.reset_status1_4 < 0.0F) {
        rtDW.Filter_PrevResetState_b0 = -1;
      } else if (rtU.reset_status1_4 == 0.0F) {
        rtDW.Filter_PrevResetState_b0 = 0;
      } else {
        rtDW.Filter_PrevResetState_b0 = 2;
      }

      if (rtU.reset_status1_4 < 0.0F) {
        rtDW.Integrator_PrevResetState_fz = -1;
      } else if (rtU.reset_status1_4 == 0.0F) {
        rtDW.Integrator_PrevResetState_fz = 0;
      } else {
        rtDW.Integrator_PrevResetState_fz = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S522>/Filter' */

    /* Update for DiscreteIntegrator: '<S527>/Integrator' incorporates:
     *  Gain: '<S524>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ok += rtP.SPD_I_CH1_4 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S4>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S4>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S492>/Action Port'
     */
    /* Sum: '<S492>/Sum' incorporates:
     *  Gain: '<S492>/Gain'
     *  Inport: '<Root>/circle_CH1_4'
     *  Inport: '<Root>/ecd_CH1_4'
     *  Inport: '<Root>/target_CH1_4'
     *  Sum: '<S492>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH1_4 - (8191.0F * rtU.circle_CH1_4 +
      rtU.ecd_CH1_4);

    /* Abs: '<S492>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S492>/Switch2' incorporates:
     *  Constant: '<S492>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH1_4)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S492>/Switch2' */

    /* Gain: '<S633>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S625>/Filter'
     *  Gain: '<S623>/Derivative Gain'
     *  Sum: '<S625>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH1_4 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_m1) * 100.0F;

    /* Switch: '<S492>/Switch1' incorporates:
     *  Constant: '<S492>/Constant'
     *  Gain: '<S492>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_4'
     *  Saturate: '<S637>/Saturation'
     *  Sum: '<S492>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH1_4) {
      /* Sum: '<S639>/Sum' incorporates:
       *  DiscreteIntegrator: '<S630>/Integrator'
       *  Gain: '<S635>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_4 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_jp) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S637>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH1_4 * u0 - rtU.speed_rpm_CH1_4;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S492>/Switch1' */

    /* DiscreteIntegrator: '<S575>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_4'
     */
    if (((rtU.reset_status1_4 > 0.0F) && (rtDW.Filter_PrevResetState_gs <= 0)) ||
        ((rtU.reset_status1_4 <= 0.0F) && (rtDW.Filter_PrevResetState_gs == 1)))
    {
      rtDW.Filter_DSTATE_lm = 0.0F;
    }

    /* Gain: '<S583>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S575>/Filter'
     *  Gain: '<S573>/Derivative Gain'
     *  Sum: '<S575>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH1_4 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_lm) * 100.0F;

    /* DiscreteIntegrator: '<S580>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_4'
     */
    if (((rtU.reset_status1_4 > 0.0F) && (rtDW.Integrator_PrevResetState_fb <= 0))
        || ((rtU.reset_status1_4 <= 0.0F) && (rtDW.Integrator_PrevResetState_fb ==
          1))) {
      rtDW.Integrator_DSTATE_nn = 0.0F;
    }

    /* Sum: '<S589>/Sum' incorporates:
     *  DiscreteIntegrator: '<S580>/Integrator'
     *  Gain: '<S585>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_4 * rtb_Sum_cz + rtDW.Integrator_DSTATE_nn) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S587>/Saturation' */
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

    /* End of Saturate: '<S587>/Saturation' */

    /* Chart: '<S492>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_4'
     *  Inport: '<Root>/last_ecd_CH1_4'
     *  Sum: '<S492>/Sum3'
     */
    Chart1(rtU.ecd_CH1_4 - rtU.last_ecd_CH1_4, &rtDW.u2_a, &rtDW.sf_Chart1_d);

    /* Outport: '<Root>/circle_out_CH1_4' incorporates:
     *  Inport: '<Root>/circle_CH1_4'
     *  Sum: '<S492>/Sum4'
     */
    rtY.circle_out_CH1_4 = rtDW.u2_a + rtU.circle_CH1_4;

    /* Update for DiscreteIntegrator: '<S630>/Integrator' incorporates:
     *  Gain: '<S627>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_jp += rtP.ANG_A_I_CH1_4 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S625>/Filter' */
    rtDW.Filter_DSTATE_m1 += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S575>/Filter' incorporates:
     *  DiscreteIntegrator: '<S580>/Integrator'
     *  Inport: '<Root>/reset_status1_4'
     */
    rtDW.Filter_DSTATE_lm += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status1_4 > 0.0F) {
      rtDW.Filter_PrevResetState_gs = 1;
      rtDW.Integrator_PrevResetState_fb = 1;
    } else {
      if (rtU.reset_status1_4 < 0.0F) {
        rtDW.Filter_PrevResetState_gs = -1;
      } else if (rtU.reset_status1_4 == 0.0F) {
        rtDW.Filter_PrevResetState_gs = 0;
      } else {
        rtDW.Filter_PrevResetState_gs = 2;
      }

      if (rtU.reset_status1_4 < 0.0F) {
        rtDW.Integrator_PrevResetState_fb = -1;
      } else if (rtU.reset_status1_4 == 0.0F) {
        rtDW.Integrator_PrevResetState_fb = 0;
      } else {
        rtDW.Integrator_PrevResetState_fb = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S575>/Filter' */

    /* Update for DiscreteIntegrator: '<S580>/Integrator' incorporates:
     *  Gain: '<S577>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_nn += rtP.ANG_S_I_CH1_4 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S647>/Action Port'
     */
    /* Sum: '<S647>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_5'
     *  Inport: '<Root>/target_CH1_5'
     */
    rtb_Sum_cz = rtU.target_CH1_5 - rtU.speed_rpm_CH1_5;

    /* DiscreteIntegrator: '<S678>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_5'
     */
    if (((rtU.reset_status1_5 > 0.0F) && (rtDW.Filter_PrevResetState_h <= 0)) ||
        ((rtU.reset_status1_5 <= 0.0F) && (rtDW.Filter_PrevResetState_h == 1)))
    {
      rtDW.Filter_DSTATE_ci = 0.0F;
    }

    /* Gain: '<S686>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S678>/Filter'
     *  Gain: '<S676>/Derivative Gain'
     *  Sum: '<S678>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH1_5 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_ci) * 100.0F;

    /* DiscreteIntegrator: '<S683>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_5'
     */
    if (((rtU.reset_status1_5 > 0.0F) && (rtDW.Integrator_PrevResetState_l <= 0))
        || ((rtU.reset_status1_5 <= 0.0F) && (rtDW.Integrator_PrevResetState_l ==
          1))) {
      rtDW.Integrator_DSTATE_el = 0.0F;
    }

    /* Sum: '<S692>/Sum' incorporates:
     *  DiscreteIntegrator: '<S683>/Integrator'
     *  Gain: '<S688>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_5 * rtb_Sum_cz + rtDW.Integrator_DSTATE_el) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S690>/Saturation' */
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

    /* End of Saturate: '<S690>/Saturation' */

    /* Update for DiscreteIntegrator: '<S678>/Filter' incorporates:
     *  DiscreteIntegrator: '<S683>/Integrator'
     *  Inport: '<Root>/reset_status1_5'
     */
    rtDW.Filter_DSTATE_ci += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status1_5 > 0.0F) {
      rtDW.Filter_PrevResetState_h = 1;
      rtDW.Integrator_PrevResetState_l = 1;
    } else {
      if (rtU.reset_status1_5 < 0.0F) {
        rtDW.Filter_PrevResetState_h = -1;
      } else if (rtU.reset_status1_5 == 0.0F) {
        rtDW.Filter_PrevResetState_h = 0;
      } else {
        rtDW.Filter_PrevResetState_h = 2;
      }

      if (rtU.reset_status1_5 < 0.0F) {
        rtDW.Integrator_PrevResetState_l = -1;
      } else if (rtU.reset_status1_5 == 0.0F) {
        rtDW.Integrator_PrevResetState_l = 0;
      } else {
        rtDW.Integrator_PrevResetState_l = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S678>/Filter' */

    /* Update for DiscreteIntegrator: '<S683>/Integrator' incorporates:
     *  Gain: '<S680>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_el += rtP.SPD_I_CH1_5 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S5>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S5>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S648>/Action Port'
     */
    /* Sum: '<S648>/Sum' incorporates:
     *  Gain: '<S648>/Gain'
     *  Inport: '<Root>/circle_CH1_5'
     *  Inport: '<Root>/ecd_CH1_5'
     *  Inport: '<Root>/target_CH1_5'
     *  Sum: '<S648>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH1_5 - (8191.0F * rtU.circle_CH1_5 +
      rtU.ecd_CH1_5);

    /* Abs: '<S648>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S648>/Switch2' incorporates:
     *  Constant: '<S648>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH1_5)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S648>/Switch2' */

    /* Gain: '<S789>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S781>/Filter'
     *  Gain: '<S779>/Derivative Gain'
     *  Sum: '<S781>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH1_5 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_nq) * 100.0F;

    /* Switch: '<S648>/Switch1' incorporates:
     *  Constant: '<S648>/Constant'
     *  Gain: '<S648>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_5'
     *  Saturate: '<S793>/Saturation'
     *  Sum: '<S648>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH1_5) {
      /* Sum: '<S795>/Sum' incorporates:
       *  DiscreteIntegrator: '<S786>/Integrator'
       *  Gain: '<S791>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_5 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_gp) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S793>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH1_5 * u0 - rtU.speed_rpm_CH1_5;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S648>/Switch1' */

    /* DiscreteIntegrator: '<S731>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_5'
     */
    if (((rtU.reset_status1_5 > 0.0F) && (rtDW.Filter_PrevResetState_kt <= 0)) ||
        ((rtU.reset_status1_5 <= 0.0F) && (rtDW.Filter_PrevResetState_kt == 1)))
    {
      rtDW.Filter_DSTATE_day = 0.0F;
    }

    /* Gain: '<S739>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S731>/Filter'
     *  Gain: '<S729>/Derivative Gain'
     *  Sum: '<S731>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH1_5 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_day) * 100.0F;

    /* DiscreteIntegrator: '<S736>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_5'
     */
    if (((rtU.reset_status1_5 > 0.0F) && (rtDW.Integrator_PrevResetState_a <= 0))
        || ((rtU.reset_status1_5 <= 0.0F) && (rtDW.Integrator_PrevResetState_a ==
          1))) {
      rtDW.Integrator_DSTATE_ih = 0.0F;
    }

    /* Sum: '<S745>/Sum' incorporates:
     *  DiscreteIntegrator: '<S736>/Integrator'
     *  Gain: '<S741>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_5 * rtb_Sum_cz + rtDW.Integrator_DSTATE_ih) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S743>/Saturation' */
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

    /* End of Saturate: '<S743>/Saturation' */

    /* Chart: '<S648>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_5'
     *  Inport: '<Root>/last_ecd_CH1_5'
     *  Sum: '<S648>/Sum3'
     */
    Chart1(rtU.ecd_CH1_5 - rtU.last_ecd_CH1_5, &rtDW.u2_c, &rtDW.sf_Chart1_p);

    /* Outport: '<Root>/circle_out_CH1_5' incorporates:
     *  Inport: '<Root>/circle_CH1_5'
     *  Sum: '<S648>/Sum4'
     */
    rtY.circle_out_CH1_5 = rtDW.u2_c + rtU.circle_CH1_5;

    /* Update for DiscreteIntegrator: '<S786>/Integrator' incorporates:
     *  Gain: '<S783>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_gp += rtP.ANG_A_I_CH1_5 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S781>/Filter' */
    rtDW.Filter_DSTATE_nq += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S731>/Filter' incorporates:
     *  DiscreteIntegrator: '<S736>/Integrator'
     *  Inport: '<Root>/reset_status1_5'
     */
    rtDW.Filter_DSTATE_day += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status1_5 > 0.0F) {
      rtDW.Filter_PrevResetState_kt = 1;
      rtDW.Integrator_PrevResetState_a = 1;
    } else {
      if (rtU.reset_status1_5 < 0.0F) {
        rtDW.Filter_PrevResetState_kt = -1;
      } else if (rtU.reset_status1_5 == 0.0F) {
        rtDW.Filter_PrevResetState_kt = 0;
      } else {
        rtDW.Filter_PrevResetState_kt = 2;
      }

      if (rtU.reset_status1_5 < 0.0F) {
        rtDW.Integrator_PrevResetState_a = -1;
      } else if (rtU.reset_status1_5 == 0.0F) {
        rtDW.Integrator_PrevResetState_a = 0;
      } else {
        rtDW.Integrator_PrevResetState_a = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S731>/Filter' */

    /* Update for DiscreteIntegrator: '<S736>/Integrator' incorporates:
     *  Gain: '<S733>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ih += rtP.ANG_S_I_CH1_5 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S803>/Action Port'
     */
    /* Sum: '<S803>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_6'
     *  Inport: '<Root>/target_CH1_6'
     */
    rtb_Sum_cz = rtU.target_CH1_6 - rtU.speed_rpm_CH1_6;

    /* DiscreteIntegrator: '<S834>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_6'
     */
    if (((rtU.reset_status1_6 > 0.0F) && (rtDW.Filter_PrevResetState_fp <= 0)) ||
        ((rtU.reset_status1_6 <= 0.0F) && (rtDW.Filter_PrevResetState_fp == 1)))
    {
      rtDW.Filter_DSTATE_c = 0.0F;
    }

    /* Gain: '<S842>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S834>/Filter'
     *  Gain: '<S832>/Derivative Gain'
     *  Sum: '<S834>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH1_6 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_c) * 100.0F;

    /* DiscreteIntegrator: '<S839>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_6'
     */
    if (((rtU.reset_status1_6 > 0.0F) && (rtDW.Integrator_PrevResetState_ds <= 0))
        || ((rtU.reset_status1_6 <= 0.0F) && (rtDW.Integrator_PrevResetState_ds ==
          1))) {
      rtDW.Integrator_DSTATE_b = 0.0F;
    }

    /* Sum: '<S848>/Sum' incorporates:
     *  DiscreteIntegrator: '<S839>/Integrator'
     *  Gain: '<S844>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_6 * rtb_Sum_cz + rtDW.Integrator_DSTATE_b) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S846>/Saturation' */
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

    /* End of Saturate: '<S846>/Saturation' */

    /* Update for DiscreteIntegrator: '<S834>/Filter' incorporates:
     *  DiscreteIntegrator: '<S839>/Integrator'
     *  Inport: '<Root>/reset_status1_6'
     */
    rtDW.Filter_DSTATE_c += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status1_6 > 0.0F) {
      rtDW.Filter_PrevResetState_fp = 1;
      rtDW.Integrator_PrevResetState_ds = 1;
    } else {
      if (rtU.reset_status1_6 < 0.0F) {
        rtDW.Filter_PrevResetState_fp = -1;
      } else if (rtU.reset_status1_6 == 0.0F) {
        rtDW.Filter_PrevResetState_fp = 0;
      } else {
        rtDW.Filter_PrevResetState_fp = 2;
      }

      if (rtU.reset_status1_6 < 0.0F) {
        rtDW.Integrator_PrevResetState_ds = -1;
      } else if (rtU.reset_status1_6 == 0.0F) {
        rtDW.Integrator_PrevResetState_ds = 0;
      } else {
        rtDW.Integrator_PrevResetState_ds = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S834>/Filter' */

    /* Update for DiscreteIntegrator: '<S839>/Integrator' incorporates:
     *  Gain: '<S836>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_b += rtP.SPD_I_CH1_6 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S6>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S6>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S804>/Action Port'
     */
    /* Sum: '<S804>/Sum' incorporates:
     *  Gain: '<S804>/Gain'
     *  Inport: '<Root>/circle_CH1_6'
     *  Inport: '<Root>/ecd_CH1_6'
     *  Inport: '<Root>/target_CH1_6'
     *  Sum: '<S804>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH1_6 - (8191.0F * rtU.circle_CH1_6 +
      rtU.ecd_CH1_6);

    /* Abs: '<S804>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S804>/Switch2' incorporates:
     *  Constant: '<S804>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH1_6)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S804>/Switch2' */

    /* Gain: '<S945>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S937>/Filter'
     *  Gain: '<S935>/Derivative Gain'
     *  Sum: '<S937>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH1_6 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_pn) * 100.0F;

    /* Switch: '<S804>/Switch1' incorporates:
     *  Constant: '<S804>/Constant'
     *  Gain: '<S804>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_6'
     *  Saturate: '<S949>/Saturation'
     *  Sum: '<S804>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH1_6) {
      /* Sum: '<S951>/Sum' incorporates:
       *  DiscreteIntegrator: '<S942>/Integrator'
       *  Gain: '<S947>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_6 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_m) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S949>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH1_6 * u0 - rtU.speed_rpm_CH1_6;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S804>/Switch1' */

    /* DiscreteIntegrator: '<S887>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_6'
     */
    if (((rtU.reset_status1_6 > 0.0F) && (rtDW.Filter_PrevResetState_lp <= 0)) ||
        ((rtU.reset_status1_6 <= 0.0F) && (rtDW.Filter_PrevResetState_lp == 1)))
    {
      rtDW.Filter_DSTATE_da = 0.0F;
    }

    /* Gain: '<S895>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S887>/Filter'
     *  Gain: '<S885>/Derivative Gain'
     *  Sum: '<S887>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH1_6 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_da) * 100.0F;

    /* DiscreteIntegrator: '<S892>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_6'
     */
    if (((rtU.reset_status1_6 > 0.0F) && (rtDW.Integrator_PrevResetState_je <= 0))
        || ((rtU.reset_status1_6 <= 0.0F) && (rtDW.Integrator_PrevResetState_je ==
          1))) {
      rtDW.Integrator_DSTATE_oo = 0.0F;
    }

    /* Sum: '<S901>/Sum' incorporates:
     *  DiscreteIntegrator: '<S892>/Integrator'
     *  Gain: '<S897>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_6 * rtb_Sum_cz + rtDW.Integrator_DSTATE_oo) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S899>/Saturation' */
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

    /* End of Saturate: '<S899>/Saturation' */

    /* Chart: '<S804>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_6'
     *  Inport: '<Root>/last_ecd_CH1_6'
     *  Sum: '<S804>/Sum3'
     */
    Chart1(rtU.ecd_CH1_6 - rtU.last_ecd_CH1_6, &rtDW.u2_nn, &rtDW.sf_Chart1_j);

    /* Outport: '<Root>/circle_out_CH1_6' incorporates:
     *  Inport: '<Root>/circle_CH1_6'
     *  Sum: '<S804>/Sum4'
     */
    rtY.circle_out_CH1_6 = rtDW.u2_nn + rtU.circle_CH1_6;

    /* Update for DiscreteIntegrator: '<S942>/Integrator' incorporates:
     *  Gain: '<S939>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_m += rtP.ANG_A_I_CH1_6 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S937>/Filter' */
    rtDW.Filter_DSTATE_pn += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S887>/Filter' incorporates:
     *  DiscreteIntegrator: '<S892>/Integrator'
     *  Inport: '<Root>/reset_status1_6'
     */
    rtDW.Filter_DSTATE_da += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status1_6 > 0.0F) {
      rtDW.Filter_PrevResetState_lp = 1;
      rtDW.Integrator_PrevResetState_je = 1;
    } else {
      if (rtU.reset_status1_6 < 0.0F) {
        rtDW.Filter_PrevResetState_lp = -1;
      } else if (rtU.reset_status1_6 == 0.0F) {
        rtDW.Filter_PrevResetState_lp = 0;
      } else {
        rtDW.Filter_PrevResetState_lp = 2;
      }

      if (rtU.reset_status1_6 < 0.0F) {
        rtDW.Integrator_PrevResetState_je = -1;
      } else if (rtU.reset_status1_6 == 0.0F) {
        rtDW.Integrator_PrevResetState_je = 0;
      } else {
        rtDW.Integrator_PrevResetState_je = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S887>/Filter' */

    /* Update for DiscreteIntegrator: '<S892>/Integrator' incorporates:
     *  Gain: '<S889>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_oo += rtP.ANG_S_I_CH1_6 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S959>/Action Port'
     */
    /* Sum: '<S959>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH1_7'
     *  Inport: '<Root>/target_CH1_7'
     */
    rtb_Sum_cz = rtU.target_CH1_7 - rtU.speed_rpm_CH1_7;

    /* DiscreteIntegrator: '<S990>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_7'
     */
    if (((rtU.reset_status1_7 > 0.0F) && (rtDW.Filter_PrevResetState_kk <= 0)) ||
        ((rtU.reset_status1_7 <= 0.0F) && (rtDW.Filter_PrevResetState_kk == 1)))
    {
      rtDW.Filter_DSTATE_kg = 0.0F;
    }

    /* Gain: '<S998>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S990>/Filter'
     *  Gain: '<S988>/Derivative Gain'
     *  Sum: '<S990>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH1_7 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_kg) * 100.0F;

    /* DiscreteIntegrator: '<S995>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_7'
     */
    if (((rtU.reset_status1_7 > 0.0F) && (rtDW.Integrator_PrevResetState_od <= 0))
        || ((rtU.reset_status1_7 <= 0.0F) && (rtDW.Integrator_PrevResetState_od ==
          1))) {
      rtDW.Integrator_DSTATE_cb = 0.0F;
    }

    /* Sum: '<S1004>/Sum' incorporates:
     *  DiscreteIntegrator: '<S995>/Integrator'
     *  Gain: '<S1000>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH1_7 * rtb_Sum_cz + rtDW.Integrator_DSTATE_cb) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S1002>/Saturation' */
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

    /* End of Saturate: '<S1002>/Saturation' */

    /* Update for DiscreteIntegrator: '<S990>/Filter' incorporates:
     *  DiscreteIntegrator: '<S995>/Integrator'
     *  Inport: '<Root>/reset_status1_7'
     */
    rtDW.Filter_DSTATE_kg += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status1_7 > 0.0F) {
      rtDW.Filter_PrevResetState_kk = 1;
      rtDW.Integrator_PrevResetState_od = 1;
    } else {
      if (rtU.reset_status1_7 < 0.0F) {
        rtDW.Filter_PrevResetState_kk = -1;
      } else if (rtU.reset_status1_7 == 0.0F) {
        rtDW.Filter_PrevResetState_kk = 0;
      } else {
        rtDW.Filter_PrevResetState_kk = 2;
      }

      if (rtU.reset_status1_7 < 0.0F) {
        rtDW.Integrator_PrevResetState_od = -1;
      } else if (rtU.reset_status1_7 == 0.0F) {
        rtDW.Integrator_PrevResetState_od = 0;
      } else {
        rtDW.Integrator_PrevResetState_od = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S990>/Filter' */

    /* Update for DiscreteIntegrator: '<S995>/Integrator' incorporates:
     *  Gain: '<S992>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_cb += rtP.SPD_I_CH1_7 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S7>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S7>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S960>/Action Port'
     */
    /* Sum: '<S960>/Sum' incorporates:
     *  Gain: '<S960>/Gain'
     *  Inport: '<Root>/circle_CH1_7'
     *  Inport: '<Root>/ecd_CH1_7'
     *  Inport: '<Root>/target_CH1_7'
     *  Sum: '<S960>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH1_7 - (8191.0F * rtU.circle_CH1_7 +
      rtU.ecd_CH1_7);

    /* Abs: '<S960>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S960>/Switch2' incorporates:
     *  Constant: '<S960>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH1_7)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S960>/Switch2' */

    /* Gain: '<S1101>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1093>/Filter'
     *  Gain: '<S1091>/Derivative Gain'
     *  Sum: '<S1093>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH1_7 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_hk) * 100.0F;

    /* Switch: '<S960>/Switch1' incorporates:
     *  Constant: '<S960>/Constant'
     *  Gain: '<S960>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH1_7'
     *  Saturate: '<S1105>/Saturation'
     *  Sum: '<S960>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH1_7) {
      /* Sum: '<S1107>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1098>/Integrator'
       *  Gain: '<S1103>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH1_7 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_g) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S1105>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH1_7 * u0 - rtU.speed_rpm_CH1_7;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S960>/Switch1' */

    /* DiscreteIntegrator: '<S1043>/Filter' incorporates:
     *  Inport: '<Root>/reset_status1_7'
     */
    if (((rtU.reset_status1_7 > 0.0F) && (rtDW.Filter_PrevResetState_nc <= 0)) ||
        ((rtU.reset_status1_7 <= 0.0F) && (rtDW.Filter_PrevResetState_nc == 1)))
    {
      rtDW.Filter_DSTATE_ax = 0.0F;
    }

    /* Gain: '<S1051>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1043>/Filter'
     *  Gain: '<S1041>/Derivative Gain'
     *  Sum: '<S1043>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH1_7 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_ax) * 100.0F;

    /* DiscreteIntegrator: '<S1048>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status1_7'
     */
    if (((rtU.reset_status1_7 > 0.0F) && (rtDW.Integrator_PrevResetState_gr <= 0))
        || ((rtU.reset_status1_7 <= 0.0F) && (rtDW.Integrator_PrevResetState_gr ==
          1))) {
      rtDW.Integrator_DSTATE_jo = 0.0F;
    }

    /* Sum: '<S1057>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1048>/Integrator'
     *  Gain: '<S1053>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH1_7 * rtb_Sum_cz + rtDW.Integrator_DSTATE_jo) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S1055>/Saturation' */
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

    /* End of Saturate: '<S1055>/Saturation' */

    /* Chart: '<S960>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH1_7'
     *  Inport: '<Root>/last_ecd_CH1_7'
     *  Sum: '<S960>/Sum3'
     */
    Chart1(rtU.ecd_CH1_7 - rtU.last_ecd_CH1_7, &rtDW.u2_f4, &rtDW.sf_Chart1_o);

    /* Outport: '<Root>/circle_out_CH1_7' incorporates:
     *  Inport: '<Root>/circle_CH1_7'
     *  Sum: '<S960>/Sum4'
     */
    rtY.circle_out_CH1_7 = rtDW.u2_f4 + rtU.circle_CH1_7;

    /* Update for DiscreteIntegrator: '<S1098>/Integrator' incorporates:
     *  Gain: '<S1095>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_g += rtP.ANG_A_I_CH1_7 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1093>/Filter' */
    rtDW.Filter_DSTATE_hk += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S1043>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1048>/Integrator'
     *  Inport: '<Root>/reset_status1_7'
     */
    rtDW.Filter_DSTATE_ax += 0.001F * rtb_FilterCoefficient_nkj;
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

    /* End of Update for DiscreteIntegrator: '<S1043>/Filter' */

    /* Update for DiscreteIntegrator: '<S1048>/Integrator' incorporates:
     *  Gain: '<S1045>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_jo += rtP.ANG_S_I_CH1_7 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S7>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S7>/Switch Case' */

  /* SwitchCase: '<S8>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH2_1'
   */
  switch ((int32_T)rtU.status_CH2_1) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S8>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1115>/Action Port'
     */
    /* Sum: '<S1115>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_1'
     *  Inport: '<Root>/target_CH2_1'
     */
    rtb_Sum_cz = rtU.target_CH2_1 - rtU.speed_rpm_CH2_1;

    /* DiscreteIntegrator: '<S1146>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_1'
     */
    if (((rtU.reset_status2_1 > 0.0F) && (rtDW.Filter_PrevResetState_a <= 0)) ||
        ((rtU.reset_status2_1 <= 0.0F) && (rtDW.Filter_PrevResetState_a == 1)))
    {
      rtDW.Filter_DSTATE_gl = 0.0F;
    }

    /* Gain: '<S1154>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1146>/Filter'
     *  Gain: '<S1144>/Derivative Gain'
     *  Sum: '<S1146>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH2_1 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_gl) * 100.0F;

    /* DiscreteIntegrator: '<S1151>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_1'
     */
    if (((rtU.reset_status2_1 > 0.0F) && (rtDW.Integrator_PrevResetState_j <= 0))
        || ((rtU.reset_status2_1 <= 0.0F) && (rtDW.Integrator_PrevResetState_j ==
          1))) {
      rtDW.Integrator_DSTATE_pft = 0.0F;
    }

    /* Sum: '<S1160>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1151>/Integrator'
     *  Gain: '<S1156>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_1 * rtb_Sum_cz + rtDW.Integrator_DSTATE_pft) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S1158>/Saturation' */
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

    /* End of Saturate: '<S1158>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1146>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1151>/Integrator'
     *  Inport: '<Root>/reset_status2_1'
     */
    rtDW.Filter_DSTATE_gl += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status2_1 > 0.0F) {
      rtDW.Filter_PrevResetState_a = 1;
      rtDW.Integrator_PrevResetState_j = 1;
    } else {
      if (rtU.reset_status2_1 < 0.0F) {
        rtDW.Filter_PrevResetState_a = -1;
      } else if (rtU.reset_status2_1 == 0.0F) {
        rtDW.Filter_PrevResetState_a = 0;
      } else {
        rtDW.Filter_PrevResetState_a = 2;
      }

      if (rtU.reset_status2_1 < 0.0F) {
        rtDW.Integrator_PrevResetState_j = -1;
      } else if (rtU.reset_status2_1 == 0.0F) {
        rtDW.Integrator_PrevResetState_j = 0;
      } else {
        rtDW.Integrator_PrevResetState_j = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1146>/Filter' */

    /* Update for DiscreteIntegrator: '<S1151>/Integrator' incorporates:
     *  Gain: '<S1148>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_pft += rtP.SPD_I_CH2_1 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S8>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S8>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1116>/Action Port'
     */
    /* Sum: '<S1116>/Sum' incorporates:
     *  Gain: '<S1116>/Gain'
     *  Inport: '<Root>/circle_CH2_1'
     *  Inport: '<Root>/ecd_CH2_1'
     *  Inport: '<Root>/target_CH2_1'
     *  Sum: '<S1116>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH2_1 - (8191.0F * rtU.circle_CH2_1 +
      rtU.ecd_CH2_1);

    /* Abs: '<S1116>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S1116>/Switch2' incorporates:
     *  Constant: '<S1116>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH2_1)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S1116>/Switch2' */

    /* Gain: '<S1257>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1249>/Filter'
     *  Gain: '<S1247>/Derivative Gain'
     *  Sum: '<S1249>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH2_1 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_g) * 100.0F;

    /* Switch: '<S1116>/Switch1' incorporates:
     *  Constant: '<S1116>/Constant'
     *  Gain: '<S1116>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_1'
     *  Saturate: '<S1261>/Saturation'
     *  Sum: '<S1116>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH2_1) {
      /* Sum: '<S1263>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1254>/Integrator'
       *  Gain: '<S1259>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_1 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_ap) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S1261>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH2_1 * u0 - rtU.speed_rpm_CH2_1;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S1116>/Switch1' */

    /* DiscreteIntegrator: '<S1199>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_1'
     */
    if (((rtU.reset_status2_1 > 0.0F) && (rtDW.Filter_PrevResetState_k3 <= 0)) ||
        ((rtU.reset_status2_1 <= 0.0F) && (rtDW.Filter_PrevResetState_k3 == 1)))
    {
      rtDW.Filter_DSTATE_h = 0.0F;
    }

    /* Gain: '<S1207>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1199>/Filter'
     *  Gain: '<S1197>/Derivative Gain'
     *  Sum: '<S1199>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH2_1 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_h) * 100.0F;

    /* DiscreteIntegrator: '<S1204>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_1'
     */
    if (((rtU.reset_status2_1 > 0.0F) && (rtDW.Integrator_PrevResetState_k5 <= 0))
        || ((rtU.reset_status2_1 <= 0.0F) && (rtDW.Integrator_PrevResetState_k5 ==
          1))) {
      rtDW.Integrator_DSTATE_lj = 0.0F;
    }

    /* Sum: '<S1213>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1204>/Integrator'
     *  Gain: '<S1209>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_1 * rtb_Sum_cz + rtDW.Integrator_DSTATE_lj) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S1211>/Saturation' */
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

    /* End of Saturate: '<S1211>/Saturation' */

    /* Chart: '<S1116>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_1'
     *  Inport: '<Root>/last_ecd_CH2_1'
     *  Sum: '<S1116>/Sum3'
     */
    Chart1(rtU.ecd_CH2_1 - rtU.last_ecd_CH2_1, &rtDW.u2_f, &rtDW.sf_Chart1_k);

    /* Outport: '<Root>/circle_out_CH2_1' incorporates:
     *  Inport: '<Root>/circle_CH2_1'
     *  Sum: '<S1116>/Sum4'
     */
    rtY.circle_out_CH2_1 = rtDW.u2_f + rtU.circle_CH2_1;

    /* Update for DiscreteIntegrator: '<S1254>/Integrator' incorporates:
     *  Gain: '<S1251>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ap += rtP.ANG_A_I_CH2_1 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1249>/Filter' */
    rtDW.Filter_DSTATE_g += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S1199>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1204>/Integrator'
     *  Inport: '<Root>/reset_status2_1'
     */
    rtDW.Filter_DSTATE_h += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status2_1 > 0.0F) {
      rtDW.Filter_PrevResetState_k3 = 1;
      rtDW.Integrator_PrevResetState_k5 = 1;
    } else {
      if (rtU.reset_status2_1 < 0.0F) {
        rtDW.Filter_PrevResetState_k3 = -1;
      } else if (rtU.reset_status2_1 == 0.0F) {
        rtDW.Filter_PrevResetState_k3 = 0;
      } else {
        rtDW.Filter_PrevResetState_k3 = 2;
      }

      if (rtU.reset_status2_1 < 0.0F) {
        rtDW.Integrator_PrevResetState_k5 = -1;
      } else if (rtU.reset_status2_1 == 0.0F) {
        rtDW.Integrator_PrevResetState_k5 = 0;
      } else {
        rtDW.Integrator_PrevResetState_k5 = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1199>/Filter' */

    /* Update for DiscreteIntegrator: '<S1204>/Integrator' incorporates:
     *  Gain: '<S1201>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_lj += rtP.ANG_S_I_CH2_1 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S1271>/Action Port'
     */
    /* Sum: '<S1271>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_2'
     *  Inport: '<Root>/target_CH2_2'
     */
    rtb_Sum_cz = rtU.target_CH2_2 - rtU.speed_rpm_CH2_2;

    /* DiscreteIntegrator: '<S1302>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_2'
     */
    if (((rtU.reset_status2_2 > 0.0F) && (rtDW.Filter_PrevResetState_lr <= 0)) ||
        ((rtU.reset_status2_2 <= 0.0F) && (rtDW.Filter_PrevResetState_lr == 1)))
    {
      rtDW.Filter_DSTATE_ix = 0.0F;
    }

    /* Gain: '<S1310>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1302>/Filter'
     *  Gain: '<S1300>/Derivative Gain'
     *  Sum: '<S1302>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH2_2 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_ix) * 100.0F;

    /* DiscreteIntegrator: '<S1307>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_2'
     */
    if (((rtU.reset_status2_2 > 0.0F) && (rtDW.Integrator_PrevResetState_dv <= 0))
        || ((rtU.reset_status2_2 <= 0.0F) && (rtDW.Integrator_PrevResetState_dv ==
          1))) {
      rtDW.Integrator_DSTATE_cc = 0.0F;
    }

    /* Sum: '<S1316>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1307>/Integrator'
     *  Gain: '<S1312>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_2 * rtb_Sum_cz + rtDW.Integrator_DSTATE_cc) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S1314>/Saturation' */
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

    /* End of Saturate: '<S1314>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1302>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1307>/Integrator'
     *  Inport: '<Root>/reset_status2_2'
     */
    rtDW.Filter_DSTATE_ix += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status2_2 > 0.0F) {
      rtDW.Filter_PrevResetState_lr = 1;
      rtDW.Integrator_PrevResetState_dv = 1;
    } else {
      if (rtU.reset_status2_2 < 0.0F) {
        rtDW.Filter_PrevResetState_lr = -1;
      } else if (rtU.reset_status2_2 == 0.0F) {
        rtDW.Filter_PrevResetState_lr = 0;
      } else {
        rtDW.Filter_PrevResetState_lr = 2;
      }

      if (rtU.reset_status2_2 < 0.0F) {
        rtDW.Integrator_PrevResetState_dv = -1;
      } else if (rtU.reset_status2_2 == 0.0F) {
        rtDW.Integrator_PrevResetState_dv = 0;
      } else {
        rtDW.Integrator_PrevResetState_dv = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1302>/Filter' */

    /* Update for DiscreteIntegrator: '<S1307>/Integrator' incorporates:
     *  Gain: '<S1304>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_cc += rtP.SPD_I_CH2_2 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S9>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S9>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1272>/Action Port'
     */
    /* Sum: '<S1272>/Sum' incorporates:
     *  Gain: '<S1272>/Gain'
     *  Inport: '<Root>/circle_CH2_2'
     *  Inport: '<Root>/ecd_CH2_2'
     *  Inport: '<Root>/target_CH2_2'
     *  Sum: '<S1272>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH2_2 - (8191.0F * rtU.circle_CH2_2 +
      rtU.ecd_CH2_2);

    /* Abs: '<S1272>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S1272>/Switch2' incorporates:
     *  Constant: '<S1272>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH2_2)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S1272>/Switch2' */

    /* Gain: '<S1413>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1405>/Filter'
     *  Gain: '<S1403>/Derivative Gain'
     *  Sum: '<S1405>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH2_2 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_ie) * 100.0F;

    /* Switch: '<S1272>/Switch1' incorporates:
     *  Constant: '<S1272>/Constant'
     *  Gain: '<S1272>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_2'
     *  Saturate: '<S1417>/Saturation'
     *  Sum: '<S1272>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH2_2) {
      /* Sum: '<S1419>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1410>/Integrator'
       *  Gain: '<S1415>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_2 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_fn) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S1417>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH2_2 * u0 - rtU.speed_rpm_CH2_2;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S1272>/Switch1' */

    /* DiscreteIntegrator: '<S1355>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_2'
     */
    if (((rtU.reset_status2_2 > 0.0F) && (rtDW.Filter_PrevResetState_mx <= 0)) ||
        ((rtU.reset_status2_2 <= 0.0F) && (rtDW.Filter_PrevResetState_mx == 1)))
    {
      rtDW.Filter_DSTATE_j1 = 0.0F;
    }

    /* Gain: '<S1363>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1355>/Filter'
     *  Gain: '<S1353>/Derivative Gain'
     *  Sum: '<S1355>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH2_2 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_j1) * 100.0F;

    /* DiscreteIntegrator: '<S1360>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_2'
     */
    if (((rtU.reset_status2_2 > 0.0F) && (rtDW.Integrator_PrevResetState_d0 <= 0))
        || ((rtU.reset_status2_2 <= 0.0F) && (rtDW.Integrator_PrevResetState_d0 ==
          1))) {
      rtDW.Integrator_DSTATE_a = 0.0F;
    }

    /* Sum: '<S1369>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1360>/Integrator'
     *  Gain: '<S1365>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_2 * rtb_Sum_cz + rtDW.Integrator_DSTATE_a) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S1367>/Saturation' */
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

    /* End of Saturate: '<S1367>/Saturation' */

    /* Chart: '<S1272>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_2'
     *  Inport: '<Root>/last_ecd_CH2_2'
     *  Sum: '<S1272>/Sum3'
     */
    Chart1(rtU.ecd_CH2_2 - rtU.last_ecd_CH2_2, &rtDW.u2_k, &rtDW.sf_Chart1_l);

    /* Outport: '<Root>/circle_out_CH2_2' incorporates:
     *  Inport: '<Root>/circle_CH2_2'
     *  Sum: '<S1272>/Sum4'
     */
    rtY.circle_out_CH2_2 = rtDW.u2_k + rtU.circle_CH2_2;

    /* Update for DiscreteIntegrator: '<S1410>/Integrator' incorporates:
     *  Gain: '<S1407>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_fn += rtP.ANG_A_I_CH2_2 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1405>/Filter' */
    rtDW.Filter_DSTATE_ie += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S1355>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1360>/Integrator'
     *  Inport: '<Root>/reset_status2_2'
     */
    rtDW.Filter_DSTATE_j1 += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status2_2 > 0.0F) {
      rtDW.Filter_PrevResetState_mx = 1;
      rtDW.Integrator_PrevResetState_d0 = 1;
    } else {
      if (rtU.reset_status2_2 < 0.0F) {
        rtDW.Filter_PrevResetState_mx = -1;
      } else if (rtU.reset_status2_2 == 0.0F) {
        rtDW.Filter_PrevResetState_mx = 0;
      } else {
        rtDW.Filter_PrevResetState_mx = 2;
      }

      if (rtU.reset_status2_2 < 0.0F) {
        rtDW.Integrator_PrevResetState_d0 = -1;
      } else if (rtU.reset_status2_2 == 0.0F) {
        rtDW.Integrator_PrevResetState_d0 = 0;
      } else {
        rtDW.Integrator_PrevResetState_d0 = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1355>/Filter' */

    /* Update for DiscreteIntegrator: '<S1360>/Integrator' incorporates:
     *  Gain: '<S1357>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_a += rtP.ANG_S_I_CH2_2 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S1427>/Action Port'
     */
    /* Sum: '<S1427>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_3'
     *  Inport: '<Root>/target_CH2_3'
     */
    rtb_Sum_cz = rtU.target_CH2_3 - rtU.speed_rpm_CH2_3;

    /* DiscreteIntegrator: '<S1458>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_3'
     */
    if (((rtU.reset_status2_3 > 0.0F) && (rtDW.Filter_PrevResetState_k <= 0)) ||
        ((rtU.reset_status2_3 <= 0.0F) && (rtDW.Filter_PrevResetState_k == 1)))
    {
      rtDW.Filter_DSTATE_nob = 0.0F;
    }

    /* Gain: '<S1466>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1458>/Filter'
     *  Gain: '<S1456>/Derivative Gain'
     *  Sum: '<S1458>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH2_3 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_nob) * 100.0F;

    /* DiscreteIntegrator: '<S1463>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_3'
     */
    if (((rtU.reset_status2_3 > 0.0F) && (rtDW.Integrator_PrevResetState_o2 <= 0))
        || ((rtU.reset_status2_3 <= 0.0F) && (rtDW.Integrator_PrevResetState_o2 ==
          1))) {
      rtDW.Integrator_DSTATE_c2 = 0.0F;
    }

    /* Sum: '<S1472>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1463>/Integrator'
     *  Gain: '<S1468>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_3 * rtb_Sum_cz + rtDW.Integrator_DSTATE_c2) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S1470>/Saturation' */
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

    /* End of Saturate: '<S1470>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1458>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1463>/Integrator'
     *  Inport: '<Root>/reset_status2_3'
     */
    rtDW.Filter_DSTATE_nob += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status2_3 > 0.0F) {
      rtDW.Filter_PrevResetState_k = 1;
      rtDW.Integrator_PrevResetState_o2 = 1;
    } else {
      if (rtU.reset_status2_3 < 0.0F) {
        rtDW.Filter_PrevResetState_k = -1;
      } else if (rtU.reset_status2_3 == 0.0F) {
        rtDW.Filter_PrevResetState_k = 0;
      } else {
        rtDW.Filter_PrevResetState_k = 2;
      }

      if (rtU.reset_status2_3 < 0.0F) {
        rtDW.Integrator_PrevResetState_o2 = -1;
      } else if (rtU.reset_status2_3 == 0.0F) {
        rtDW.Integrator_PrevResetState_o2 = 0;
      } else {
        rtDW.Integrator_PrevResetState_o2 = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1458>/Filter' */

    /* Update for DiscreteIntegrator: '<S1463>/Integrator' incorporates:
     *  Gain: '<S1460>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_c2 += rtP.SPD_I_CH2_3 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S10>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S10>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1428>/Action Port'
     */
    /* Sum: '<S1428>/Sum' incorporates:
     *  Gain: '<S1428>/Gain'
     *  Inport: '<Root>/circle_CH2_3'
     *  Inport: '<Root>/ecd_CH2_3'
     *  Inport: '<Root>/target_CH2_3'
     *  Sum: '<S1428>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH2_3 - (8191.0F * rtU.circle_CH2_3 +
      rtU.ecd_CH2_3);

    /* Abs: '<S1428>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S1428>/Switch2' incorporates:
     *  Constant: '<S1428>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH2_3)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S1428>/Switch2' */

    /* Gain: '<S1569>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1561>/Filter'
     *  Gain: '<S1559>/Derivative Gain'
     *  Sum: '<S1561>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH2_3 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_ag) * 100.0F;

    /* Switch: '<S1428>/Switch1' incorporates:
     *  Constant: '<S1428>/Constant'
     *  Gain: '<S1428>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_3'
     *  Saturate: '<S1573>/Saturation'
     *  Sum: '<S1428>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH2_3) {
      /* Sum: '<S1575>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1566>/Integrator'
       *  Gain: '<S1571>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_3 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_pf) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S1573>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH2_3 * u0 - rtU.speed_rpm_CH2_3;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S1428>/Switch1' */

    /* DiscreteIntegrator: '<S1511>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_3'
     */
    if (((rtU.reset_status2_3 > 0.0F) && (rtDW.Filter_PrevResetState_m <= 0)) ||
        ((rtU.reset_status2_3 <= 0.0F) && (rtDW.Filter_PrevResetState_m == 1)))
    {
      rtDW.Filter_DSTATE_aw = 0.0F;
    }

    /* Gain: '<S1519>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1511>/Filter'
     *  Gain: '<S1509>/Derivative Gain'
     *  Sum: '<S1511>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH2_3 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_aw) * 100.0F;

    /* DiscreteIntegrator: '<S1516>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_3'
     */
    if (((rtU.reset_status2_3 > 0.0F) && (rtDW.Integrator_PrevResetState_dj <= 0))
        || ((rtU.reset_status2_3 <= 0.0F) && (rtDW.Integrator_PrevResetState_dj ==
          1))) {
      rtDW.Integrator_DSTATE_no = 0.0F;
    }

    /* Sum: '<S1525>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1516>/Integrator'
     *  Gain: '<S1521>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_3 * rtb_Sum_cz + rtDW.Integrator_DSTATE_no) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S1523>/Saturation' */
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

    /* End of Saturate: '<S1523>/Saturation' */

    /* Chart: '<S1428>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_3'
     *  Inport: '<Root>/last_ecd_CH2_3'
     *  Sum: '<S1428>/Sum3'
     */
    Chart1(rtU.ecd_CH2_3 - rtU.last_ecd_CH2_3, &rtDW.u2_or, &rtDW.sf_Chart1_mk);

    /* Outport: '<Root>/circle_out_CH2_3' incorporates:
     *  Inport: '<Root>/circle_CH2_3'
     *  Sum: '<S1428>/Sum4'
     */
    rtY.circle_out_CH2_3 = rtDW.u2_or + rtU.circle_CH2_3;

    /* Update for DiscreteIntegrator: '<S1566>/Integrator' incorporates:
     *  Gain: '<S1563>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_pf += rtP.ANG_A_I_CH2_3 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1561>/Filter' */
    rtDW.Filter_DSTATE_ag += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S1511>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1516>/Integrator'
     *  Inport: '<Root>/reset_status2_3'
     */
    rtDW.Filter_DSTATE_aw += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status2_3 > 0.0F) {
      rtDW.Filter_PrevResetState_m = 1;
      rtDW.Integrator_PrevResetState_dj = 1;
    } else {
      if (rtU.reset_status2_3 < 0.0F) {
        rtDW.Filter_PrevResetState_m = -1;
      } else if (rtU.reset_status2_3 == 0.0F) {
        rtDW.Filter_PrevResetState_m = 0;
      } else {
        rtDW.Filter_PrevResetState_m = 2;
      }

      if (rtU.reset_status2_3 < 0.0F) {
        rtDW.Integrator_PrevResetState_dj = -1;
      } else if (rtU.reset_status2_3 == 0.0F) {
        rtDW.Integrator_PrevResetState_dj = 0;
      } else {
        rtDW.Integrator_PrevResetState_dj = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1511>/Filter' */

    /* Update for DiscreteIntegrator: '<S1516>/Integrator' incorporates:
     *  Gain: '<S1513>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_no += rtP.ANG_S_I_CH2_3 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S1583>/Action Port'
     */
    /* Sum: '<S1583>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_4'
     *  Inport: '<Root>/target_CH2_4'
     */
    rtb_Sum_cz = rtU.target_CH2_4 - rtU.speed_rpm_CH2_4;

    /* DiscreteIntegrator: '<S1614>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_4'
     */
    if (((rtU.reset_status2_4 > 0.0F) && (rtDW.Filter_PrevResetState_lf <= 0)) ||
        ((rtU.reset_status2_4 <= 0.0F) && (rtDW.Filter_PrevResetState_lf == 1)))
    {
      rtDW.Filter_DSTATE_mi = 0.0F;
    }

    /* Gain: '<S1622>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1614>/Filter'
     *  Gain: '<S1612>/Derivative Gain'
     *  Sum: '<S1614>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH2_4 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_mi) * 100.0F;

    /* DiscreteIntegrator: '<S1619>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_4'
     */
    if (((rtU.reset_status2_4 > 0.0F) && (rtDW.Integrator_PrevResetState_d <= 0))
        || ((rtU.reset_status2_4 <= 0.0F) && (rtDW.Integrator_PrevResetState_d ==
          1))) {
      rtDW.Integrator_DSTATE_n0 = 0.0F;
    }

    /* Sum: '<S1628>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1619>/Integrator'
     *  Gain: '<S1624>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_4 * rtb_Sum_cz + rtDW.Integrator_DSTATE_n0) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S1626>/Saturation' */
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

    /* End of Saturate: '<S1626>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1614>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1619>/Integrator'
     *  Inport: '<Root>/reset_status2_4'
     */
    rtDW.Filter_DSTATE_mi += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status2_4 > 0.0F) {
      rtDW.Filter_PrevResetState_lf = 1;
      rtDW.Integrator_PrevResetState_d = 1;
    } else {
      if (rtU.reset_status2_4 < 0.0F) {
        rtDW.Filter_PrevResetState_lf = -1;
      } else if (rtU.reset_status2_4 == 0.0F) {
        rtDW.Filter_PrevResetState_lf = 0;
      } else {
        rtDW.Filter_PrevResetState_lf = 2;
      }

      if (rtU.reset_status2_4 < 0.0F) {
        rtDW.Integrator_PrevResetState_d = -1;
      } else if (rtU.reset_status2_4 == 0.0F) {
        rtDW.Integrator_PrevResetState_d = 0;
      } else {
        rtDW.Integrator_PrevResetState_d = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1614>/Filter' */

    /* Update for DiscreteIntegrator: '<S1619>/Integrator' incorporates:
     *  Gain: '<S1616>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_n0 += rtP.SPD_I_CH2_4 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S11>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S11>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1584>/Action Port'
     */
    /* Sum: '<S1584>/Sum' incorporates:
     *  Gain: '<S1584>/Gain'
     *  Inport: '<Root>/circle_CH2_4'
     *  Inport: '<Root>/ecd_CH2_4'
     *  Inport: '<Root>/target_CH2_4'
     *  Sum: '<S1584>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH2_4 - (8191.0F * rtU.circle_CH2_4 +
      rtU.ecd_CH2_4);

    /* Abs: '<S1584>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S1584>/Switch2' incorporates:
     *  Constant: '<S1584>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH2_4)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S1584>/Switch2' */

    /* Gain: '<S1725>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1717>/Filter'
     *  Gain: '<S1715>/Derivative Gain'
     *  Sum: '<S1717>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH2_4 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_a4) * 100.0F;

    /* Switch: '<S1584>/Switch1' incorporates:
     *  Constant: '<S1584>/Constant'
     *  Gain: '<S1584>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_4'
     *  Saturate: '<S1729>/Saturation'
     *  Sum: '<S1584>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH2_4) {
      /* Sum: '<S1731>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1722>/Integrator'
       *  Gain: '<S1727>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_4 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_oqb) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S1729>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH2_4 * u0 - rtU.speed_rpm_CH2_4;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S1584>/Switch1' */

    /* DiscreteIntegrator: '<S1667>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_4'
     */
    if (((rtU.reset_status2_4 > 0.0F) && (rtDW.Filter_PrevResetState_i <= 0)) ||
        ((rtU.reset_status2_4 <= 0.0F) && (rtDW.Filter_PrevResetState_i == 1)))
    {
      rtDW.Filter_DSTATE_lg = 0.0F;
    }

    /* Gain: '<S1675>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1667>/Filter'
     *  Gain: '<S1665>/Derivative Gain'
     *  Sum: '<S1667>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH2_4 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_lg) * 100.0F;

    /* DiscreteIntegrator: '<S1672>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_4'
     */
    if (((rtU.reset_status2_4 > 0.0F) && (rtDW.Integrator_PrevResetState_ih <= 0))
        || ((rtU.reset_status2_4 <= 0.0F) && (rtDW.Integrator_PrevResetState_ih ==
          1))) {
      rtDW.Integrator_DSTATE_pv = 0.0F;
    }

    /* Sum: '<S1681>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1672>/Integrator'
     *  Gain: '<S1677>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_4 * rtb_Sum_cz + rtDW.Integrator_DSTATE_pv) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S1679>/Saturation' */
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

    /* End of Saturate: '<S1679>/Saturation' */

    /* Chart: '<S1584>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_4'
     *  Inport: '<Root>/last_ecd_CH2_4'
     *  Sum: '<S1584>/Sum3'
     */
    Chart1(rtU.ecd_CH2_4 - rtU.last_ecd_CH2_4, &rtDW.u2_o, &rtDW.sf_Chart1_n);

    /* Outport: '<Root>/circle_out_CH2_4' incorporates:
     *  Inport: '<Root>/circle_CH2_4'
     *  Sum: '<S1584>/Sum4'
     */
    rtY.circle_out_CH2_4 = rtDW.u2_o + rtU.circle_CH2_4;

    /* Update for DiscreteIntegrator: '<S1722>/Integrator' incorporates:
     *  Gain: '<S1719>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_oqb += rtP.ANG_A_I_CH2_4 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1717>/Filter' */
    rtDW.Filter_DSTATE_a4 += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S1667>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1672>/Integrator'
     *  Inport: '<Root>/reset_status2_4'
     */
    rtDW.Filter_DSTATE_lg += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status2_4 > 0.0F) {
      rtDW.Filter_PrevResetState_i = 1;
      rtDW.Integrator_PrevResetState_ih = 1;
    } else {
      if (rtU.reset_status2_4 < 0.0F) {
        rtDW.Filter_PrevResetState_i = -1;
      } else if (rtU.reset_status2_4 == 0.0F) {
        rtDW.Filter_PrevResetState_i = 0;
      } else {
        rtDW.Filter_PrevResetState_i = 2;
      }

      if (rtU.reset_status2_4 < 0.0F) {
        rtDW.Integrator_PrevResetState_ih = -1;
      } else if (rtU.reset_status2_4 == 0.0F) {
        rtDW.Integrator_PrevResetState_ih = 0;
      } else {
        rtDW.Integrator_PrevResetState_ih = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1667>/Filter' */

    /* Update for DiscreteIntegrator: '<S1672>/Integrator' incorporates:
     *  Gain: '<S1669>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_pv += rtP.ANG_S_I_CH2_4 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S11>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S11>/Switch Case' */

  /* SwitchCase: '<S12>/Switch Case' incorporates:
   *  Inport: '<Root>/status_CH2_5'
   */
  switch ((int32_T)rtU.status_CH2_5) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S12>/If Action_speed Subsystem' incorporates:
     *  ActionPort: '<S1739>/Action Port'
     */
    /* Sum: '<S1739>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_5'
     *  Inport: '<Root>/target_CH2_5'
     */
    rtb_Sum_cz = rtU.target_CH2_5 - rtU.speed_rpm_CH2_5;

    /* DiscreteIntegrator: '<S1770>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_5'
     */
    if (((rtU.reset_status2_5 > 0.0F) && (rtDW.Filter_PrevResetState_o <= 0)) ||
        ((rtU.reset_status2_5 <= 0.0F) && (rtDW.Filter_PrevResetState_o == 1)))
    {
      rtDW.Filter_DSTATE_d = 0.0F;
    }

    /* Gain: '<S1778>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1770>/Filter'
     *  Gain: '<S1768>/Derivative Gain'
     *  Sum: '<S1770>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH2_5 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_d) * 100.0F;

    /* DiscreteIntegrator: '<S1775>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_5'
     */
    if (((rtU.reset_status2_5 > 0.0F) && (rtDW.Integrator_PrevResetState_f <= 0))
        || ((rtU.reset_status2_5 <= 0.0F) && (rtDW.Integrator_PrevResetState_f ==
          1))) {
      rtDW.Integrator_DSTATE_hm = 0.0F;
    }

    /* Sum: '<S1784>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1775>/Integrator'
     *  Gain: '<S1780>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_5 * rtb_Sum_cz + rtDW.Integrator_DSTATE_hm) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S1782>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_5' */
      rtY.SPD_OUT_CH2_5 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_5' */
      rtY.SPD_OUT_CH2_5 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH2_5' */
      rtY.SPD_OUT_CH2_5 = u0;
    }

    /* End of Saturate: '<S1782>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1770>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1775>/Integrator'
     *  Inport: '<Root>/reset_status2_5'
     */
    rtDW.Filter_DSTATE_d += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status2_5 > 0.0F) {
      rtDW.Filter_PrevResetState_o = 1;
      rtDW.Integrator_PrevResetState_f = 1;
    } else {
      if (rtU.reset_status2_5 < 0.0F) {
        rtDW.Filter_PrevResetState_o = -1;
      } else if (rtU.reset_status2_5 == 0.0F) {
        rtDW.Filter_PrevResetState_o = 0;
      } else {
        rtDW.Filter_PrevResetState_o = 2;
      }

      if (rtU.reset_status2_5 < 0.0F) {
        rtDW.Integrator_PrevResetState_f = -1;
      } else if (rtU.reset_status2_5 == 0.0F) {
        rtDW.Integrator_PrevResetState_f = 0;
      } else {
        rtDW.Integrator_PrevResetState_f = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1770>/Filter' */

    /* Update for DiscreteIntegrator: '<S1775>/Integrator' incorporates:
     *  Gain: '<S1772>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_hm += rtP.SPD_I_CH2_5 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S12>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S12>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1740>/Action Port'
     */
    /* Sum: '<S1740>/Sum' incorporates:
     *  Gain: '<S1740>/Gain'
     *  Inport: '<Root>/circle_CH2_5'
     *  Inport: '<Root>/ecd_CH2_5'
     *  Inport: '<Root>/target_CH2_5'
     *  Sum: '<S1740>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH2_5 - (8191.0F * rtU.circle_CH2_5 +
      rtU.ecd_CH2_5);

    /* Abs: '<S1740>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S1740>/Switch2' incorporates:
     *  Constant: '<S1740>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH2_5)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S1740>/Switch2' */

    /* Gain: '<S1881>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1873>/Filter'
     *  Gain: '<S1871>/Derivative Gain'
     *  Sum: '<S1873>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH2_5 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_o0) * 100.0F;

    /* Switch: '<S1740>/Switch1' incorporates:
     *  Constant: '<S1740>/Constant'
     *  Gain: '<S1740>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_5'
     *  Saturate: '<S1885>/Saturation'
     *  Sum: '<S1740>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH2_5) {
      /* Sum: '<S1887>/Sum' incorporates:
       *  DiscreteIntegrator: '<S1878>/Integrator'
       *  Gain: '<S1883>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_5 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_oq) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S1885>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH2_5 * u0 - rtU.speed_rpm_CH2_5;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S1740>/Switch1' */

    /* DiscreteIntegrator: '<S1823>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_5'
     */
    if (((rtU.reset_status2_5 > 0.0F) && (rtDW.Filter_PrevResetState_f3 <= 0)) ||
        ((rtU.reset_status2_5 <= 0.0F) && (rtDW.Filter_PrevResetState_f3 == 1)))
    {
      rtDW.Filter_DSTATE_l = 0.0F;
    }

    /* Gain: '<S1831>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1823>/Filter'
     *  Gain: '<S1821>/Derivative Gain'
     *  Sum: '<S1823>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH2_5 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_l) * 100.0F;

    /* DiscreteIntegrator: '<S1828>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_5'
     */
    if (((rtU.reset_status2_5 > 0.0F) && (rtDW.Integrator_PrevResetState_bsc <=
          0)) || ((rtU.reset_status2_5 <= 0.0F) &&
                  (rtDW.Integrator_PrevResetState_bsc == 1))) {
      rtDW.Integrator_DSTATE_o1 = 0.0F;
    }

    /* Sum: '<S1837>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1828>/Integrator'
     *  Gain: '<S1833>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_5 * rtb_Sum_cz + rtDW.Integrator_DSTATE_o1) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S1835>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_5' */
      rtY.ANG_OUT_CH2_5 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_5' */
      rtY.ANG_OUT_CH2_5 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH2_5' */
      rtY.ANG_OUT_CH2_5 = u0;
    }

    /* End of Saturate: '<S1835>/Saturation' */

    /* Chart: '<S1740>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_5'
     *  Inport: '<Root>/last_ecd_CH2_5'
     *  Sum: '<S1740>/Sum3'
     */
    Chart1(rtU.ecd_CH2_5 - rtU.last_ecd_CH2_5, &rtDW.u2_n2, &rtDW.sf_Chart1_dt);

    /* Outport: '<Root>/circle_out_CH2_5' incorporates:
     *  Inport: '<Root>/circle_CH2_5'
     *  Sum: '<S1740>/Sum4'
     */
    rtY.circle_out_CH2_5 = rtDW.u2_n2 + rtU.circle_CH2_5;

    /* Update for DiscreteIntegrator: '<S1878>/Integrator' incorporates:
     *  Gain: '<S1875>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_oq += rtP.ANG_A_I_CH2_5 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S1873>/Filter' */
    rtDW.Filter_DSTATE_o0 += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S1823>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1828>/Integrator'
     *  Inport: '<Root>/reset_status2_5'
     */
    rtDW.Filter_DSTATE_l += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status2_5 > 0.0F) {
      rtDW.Filter_PrevResetState_f3 = 1;
      rtDW.Integrator_PrevResetState_bsc = 1;
    } else {
      if (rtU.reset_status2_5 < 0.0F) {
        rtDW.Filter_PrevResetState_f3 = -1;
      } else if (rtU.reset_status2_5 == 0.0F) {
        rtDW.Filter_PrevResetState_f3 = 0;
      } else {
        rtDW.Filter_PrevResetState_f3 = 2;
      }

      if (rtU.reset_status2_5 < 0.0F) {
        rtDW.Integrator_PrevResetState_bsc = -1;
      } else if (rtU.reset_status2_5 == 0.0F) {
        rtDW.Integrator_PrevResetState_bsc = 0;
      } else {
        rtDW.Integrator_PrevResetState_bsc = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1823>/Filter' */

    /* Update for DiscreteIntegrator: '<S1828>/Integrator' incorporates:
     *  Gain: '<S1825>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_o1 += rtP.ANG_S_I_CH2_5 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S1895>/Action Port'
     */
    /* Sum: '<S1895>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_6'
     *  Inport: '<Root>/target_CH2_6'
     */
    rtb_Sum_cz = rtU.target_CH2_6 - rtU.speed_rpm_CH2_6;

    /* DiscreteIntegrator: '<S1926>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_6'
     */
    if (((rtU.reset_status2_6 > 0.0F) && (rtDW.Filter_PrevResetState_g <= 0)) ||
        ((rtU.reset_status2_6 <= 0.0F) && (rtDW.Filter_PrevResetState_g == 1)))
    {
      rtDW.Filter_DSTATE_ab = 0.0F;
    }

    /* Gain: '<S1934>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1926>/Filter'
     *  Gain: '<S1924>/Derivative Gain'
     *  Sum: '<S1926>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH2_6 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_ab) * 100.0F;

    /* DiscreteIntegrator: '<S1931>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_6'
     */
    if (((rtU.reset_status2_6 > 0.0F) && (rtDW.Integrator_PrevResetState_mq <= 0))
        || ((rtU.reset_status2_6 <= 0.0F) && (rtDW.Integrator_PrevResetState_mq ==
          1))) {
      rtDW.Integrator_DSTATE_hz = 0.0F;
    }

    /* Sum: '<S1940>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1931>/Integrator'
     *  Gain: '<S1936>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_6 * rtb_Sum_cz + rtDW.Integrator_DSTATE_hz) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S1938>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_6' */
      rtY.SPD_OUT_CH2_6 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_6' */
      rtY.SPD_OUT_CH2_6 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH2_6' */
      rtY.SPD_OUT_CH2_6 = u0;
    }

    /* End of Saturate: '<S1938>/Saturation' */

    /* Update for DiscreteIntegrator: '<S1926>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1931>/Integrator'
     *  Inport: '<Root>/reset_status2_6'
     */
    rtDW.Filter_DSTATE_ab += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status2_6 > 0.0F) {
      rtDW.Filter_PrevResetState_g = 1;
      rtDW.Integrator_PrevResetState_mq = 1;
    } else {
      if (rtU.reset_status2_6 < 0.0F) {
        rtDW.Filter_PrevResetState_g = -1;
      } else if (rtU.reset_status2_6 == 0.0F) {
        rtDW.Filter_PrevResetState_g = 0;
      } else {
        rtDW.Filter_PrevResetState_g = 2;
      }

      if (rtU.reset_status2_6 < 0.0F) {
        rtDW.Integrator_PrevResetState_mq = -1;
      } else if (rtU.reset_status2_6 == 0.0F) {
        rtDW.Integrator_PrevResetState_mq = 0;
      } else {
        rtDW.Integrator_PrevResetState_mq = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1926>/Filter' */

    /* Update for DiscreteIntegrator: '<S1931>/Integrator' incorporates:
     *  Gain: '<S1928>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_hz += rtP.SPD_I_CH2_6 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S13>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S13>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S1896>/Action Port'
     */
    /* Sum: '<S1896>/Sum' incorporates:
     *  Gain: '<S1896>/Gain'
     *  Inport: '<Root>/circle_CH2_6'
     *  Inport: '<Root>/ecd_CH2_6'
     *  Inport: '<Root>/target_CH2_6'
     *  Sum: '<S1896>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH2_6 - (8191.0F * rtU.circle_CH2_6 +
      rtU.ecd_CH2_6);

    /* Abs: '<S1896>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S1896>/Switch2' incorporates:
     *  Constant: '<S1896>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH2_6)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S1896>/Switch2' */

    /* Gain: '<S2037>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2029>/Filter'
     *  Gain: '<S2027>/Derivative Gain'
     *  Sum: '<S2029>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH2_6 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_oz) * 100.0F;

    /* Switch: '<S1896>/Switch1' incorporates:
     *  Constant: '<S1896>/Constant'
     *  Gain: '<S1896>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_6'
     *  Saturate: '<S2041>/Saturation'
     *  Sum: '<S1896>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH2_6) {
      /* Sum: '<S2043>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2034>/Integrator'
       *  Gain: '<S2039>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_6 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_hd) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S2041>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH2_6 * u0 - rtU.speed_rpm_CH2_6;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S1896>/Switch1' */

    /* DiscreteIntegrator: '<S1979>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_6'
     */
    if (((rtU.reset_status2_6 > 0.0F) && (rtDW.Filter_PrevResetState_f <= 0)) ||
        ((rtU.reset_status2_6 <= 0.0F) && (rtDW.Filter_PrevResetState_f == 1)))
    {
      rtDW.Filter_DSTATE_ny = 0.0F;
    }

    /* Gain: '<S1987>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S1979>/Filter'
     *  Gain: '<S1977>/Derivative Gain'
     *  Sum: '<S1979>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH2_6 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_ny) * 100.0F;

    /* DiscreteIntegrator: '<S1984>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_6'
     */
    if (((rtU.reset_status2_6 > 0.0F) && (rtDW.Integrator_PrevResetState_ny <= 0))
        || ((rtU.reset_status2_6 <= 0.0F) && (rtDW.Integrator_PrevResetState_ny ==
          1))) {
      rtDW.Integrator_DSTATE_e = 0.0F;
    }

    /* Sum: '<S1993>/Sum' incorporates:
     *  DiscreteIntegrator: '<S1984>/Integrator'
     *  Gain: '<S1989>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_6 * rtb_Sum_cz + rtDW.Integrator_DSTATE_e) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S1991>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_6' */
      rtY.ANG_OUT_CH2_6 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_6' */
      rtY.ANG_OUT_CH2_6 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH2_6' */
      rtY.ANG_OUT_CH2_6 = u0;
    }

    /* End of Saturate: '<S1991>/Saturation' */

    /* Chart: '<S1896>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_6'
     *  Inport: '<Root>/last_ecd_CH2_6'
     *  Sum: '<S1896>/Sum3'
     */
    Chart1(rtU.ecd_CH2_6 - rtU.last_ecd_CH2_6, &rtDW.u2_h, &rtDW.sf_Chart1_nl);

    /* Outport: '<Root>/circle_out_CH2_6' incorporates:
     *  Inport: '<Root>/circle_CH2_6'
     *  Sum: '<S1896>/Sum4'
     */
    rtY.circle_out_CH2_6 = rtDW.u2_h + rtU.circle_CH2_6;

    /* Update for DiscreteIntegrator: '<S2034>/Integrator' incorporates:
     *  Gain: '<S2031>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_hd += rtP.ANG_A_I_CH2_6 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2029>/Filter' */
    rtDW.Filter_DSTATE_oz += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S1979>/Filter' incorporates:
     *  DiscreteIntegrator: '<S1984>/Integrator'
     *  Inport: '<Root>/reset_status2_6'
     */
    rtDW.Filter_DSTATE_ny += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status2_6 > 0.0F) {
      rtDW.Filter_PrevResetState_f = 1;
      rtDW.Integrator_PrevResetState_ny = 1;
    } else {
      if (rtU.reset_status2_6 < 0.0F) {
        rtDW.Filter_PrevResetState_f = -1;
      } else if (rtU.reset_status2_6 == 0.0F) {
        rtDW.Filter_PrevResetState_f = 0;
      } else {
        rtDW.Filter_PrevResetState_f = 2;
      }

      if (rtU.reset_status2_6 < 0.0F) {
        rtDW.Integrator_PrevResetState_ny = -1;
      } else if (rtU.reset_status2_6 == 0.0F) {
        rtDW.Integrator_PrevResetState_ny = 0;
      } else {
        rtDW.Integrator_PrevResetState_ny = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S1979>/Filter' */

    /* Update for DiscreteIntegrator: '<S1984>/Integrator' incorporates:
     *  Gain: '<S1981>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_e += rtP.ANG_S_I_CH2_6 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S2051>/Action Port'
     */
    /* Sum: '<S2051>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH2_7'
     *  Inport: '<Root>/target_CH2_7'
     */
    rtb_Sum_cz = rtU.target_CH2_7 - rtU.speed_rpm_CH2_7;

    /* DiscreteIntegrator: '<S2082>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_7'
     */
    if (((rtU.reset_status2_7 > 0.0F) && (rtDW.Filter_PrevResetState_ng <= 0)) ||
        ((rtU.reset_status2_7 <= 0.0F) && (rtDW.Filter_PrevResetState_ng == 1)))
    {
      rtDW.Filter_DSTATE_e2 = 0.0F;
    }

    /* Gain: '<S2090>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2082>/Filter'
     *  Gain: '<S2080>/Derivative Gain'
     *  Sum: '<S2082>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH2_7 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_e2) * 100.0F;

    /* DiscreteIntegrator: '<S2087>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_7'
     */
    if (((rtU.reset_status2_7 > 0.0F) && (rtDW.Integrator_PrevResetState_i <= 0))
        || ((rtU.reset_status2_7 <= 0.0F) && (rtDW.Integrator_PrevResetState_i ==
          1))) {
      rtDW.Integrator_DSTATE_pt = 0.0F;
    }

    /* Sum: '<S2096>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2087>/Integrator'
     *  Gain: '<S2092>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH2_7 * rtb_Sum_cz + rtDW.Integrator_DSTATE_pt) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S2094>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_7' */
      rtY.SPD_OUT_CH2_7 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/SPD_OUT_CH2_7' */
      rtY.SPD_OUT_CH2_7 = -16384.0F;
    } else {
      /* Outport: '<Root>/SPD_OUT_CH2_7' */
      rtY.SPD_OUT_CH2_7 = u0;
    }

    /* End of Saturate: '<S2094>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2082>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2087>/Integrator'
     *  Inport: '<Root>/reset_status2_7'
     */
    rtDW.Filter_DSTATE_e2 += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status2_7 > 0.0F) {
      rtDW.Filter_PrevResetState_ng = 1;
      rtDW.Integrator_PrevResetState_i = 1;
    } else {
      if (rtU.reset_status2_7 < 0.0F) {
        rtDW.Filter_PrevResetState_ng = -1;
      } else if (rtU.reset_status2_7 == 0.0F) {
        rtDW.Filter_PrevResetState_ng = 0;
      } else {
        rtDW.Filter_PrevResetState_ng = 2;
      }

      if (rtU.reset_status2_7 < 0.0F) {
        rtDW.Integrator_PrevResetState_i = -1;
      } else if (rtU.reset_status2_7 == 0.0F) {
        rtDW.Integrator_PrevResetState_i = 0;
      } else {
        rtDW.Integrator_PrevResetState_i = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2082>/Filter' */

    /* Update for DiscreteIntegrator: '<S2087>/Integrator' incorporates:
     *  Gain: '<S2084>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_pt += rtP.SPD_I_CH2_7 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S14>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S14>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2052>/Action Port'
     */
    /* Sum: '<S2052>/Sum' incorporates:
     *  Gain: '<S2052>/Gain'
     *  Inport: '<Root>/circle_CH2_7'
     *  Inport: '<Root>/ecd_CH2_7'
     *  Inport: '<Root>/target_CH2_7'
     *  Sum: '<S2052>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH2_7 - (8191.0F * rtU.circle_CH2_7 +
      rtU.ecd_CH2_7);

    /* Abs: '<S2052>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S2052>/Switch2' incorporates:
     *  Constant: '<S2052>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH2_7)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S2052>/Switch2' */

    /* Gain: '<S2193>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2185>/Filter'
     *  Gain: '<S2183>/Derivative Gain'
     *  Sum: '<S2185>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH2_7 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_bs) * 100.0F;

    /* Switch: '<S2052>/Switch1' incorporates:
     *  Constant: '<S2052>/Constant'
     *  Gain: '<S2052>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH2_7'
     *  Saturate: '<S2197>/Saturation'
     *  Sum: '<S2052>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH2_7) {
      /* Sum: '<S2199>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2190>/Integrator'
       *  Gain: '<S2195>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH2_7 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_l3) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S2197>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH2_7 * u0 - rtU.speed_rpm_CH2_7;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S2052>/Switch1' */

    /* DiscreteIntegrator: '<S2135>/Filter' incorporates:
     *  Inport: '<Root>/reset_status2_7'
     */
    if (((rtU.reset_status2_7 > 0.0F) && (rtDW.Filter_PrevResetState_lt <= 0)) ||
        ((rtU.reset_status2_7 <= 0.0F) && (rtDW.Filter_PrevResetState_lt == 1)))
    {
      rtDW.Filter_DSTATE_op = 0.0F;
    }

    /* Gain: '<S2143>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2135>/Filter'
     *  Gain: '<S2133>/Derivative Gain'
     *  Sum: '<S2135>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH2_7 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_op) * 100.0F;

    /* DiscreteIntegrator: '<S2140>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status2_7'
     */
    if (((rtU.reset_status2_7 > 0.0F) && (rtDW.Integrator_PrevResetState_k <= 0))
        || ((rtU.reset_status2_7 <= 0.0F) && (rtDW.Integrator_PrevResetState_k ==
          1))) {
      rtDW.Integrator_DSTATE_dz = 0.0F;
    }

    /* Sum: '<S2149>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2140>/Integrator'
     *  Gain: '<S2145>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH2_7 * rtb_Sum_cz + rtDW.Integrator_DSTATE_dz) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S2147>/Saturation' */
    if (u0 > 16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_7' */
      rtY.ANG_OUT_CH2_7 = 16384.0F;
    } else if (u0 < -16384.0F) {
      /* Outport: '<Root>/ANG_OUT_CH2_7' */
      rtY.ANG_OUT_CH2_7 = -16384.0F;
    } else {
      /* Outport: '<Root>/ANG_OUT_CH2_7' */
      rtY.ANG_OUT_CH2_7 = u0;
    }

    /* End of Saturate: '<S2147>/Saturation' */

    /* Chart: '<S2052>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH2_7'
     *  Inport: '<Root>/last_ecd_CH2_7'
     *  Sum: '<S2052>/Sum3'
     */
    Chart1(rtU.ecd_CH2_7 - rtU.last_ecd_CH2_7, &rtDW.u2_e, &rtDW.sf_Chart1_ke);

    /* Outport: '<Root>/circle_out_CH2_7' incorporates:
     *  Inport: '<Root>/circle_CH2_7'
     *  Sum: '<S2052>/Sum4'
     */
    rtY.circle_out_CH2_7 = rtDW.u2_e + rtU.circle_CH2_7;

    /* Update for DiscreteIntegrator: '<S2190>/Integrator' incorporates:
     *  Gain: '<S2187>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_l3 += rtP.ANG_A_I_CH2_7 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2185>/Filter' */
    rtDW.Filter_DSTATE_bs += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S2135>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2140>/Integrator'
     *  Inport: '<Root>/reset_status2_7'
     */
    rtDW.Filter_DSTATE_op += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status2_7 > 0.0F) {
      rtDW.Filter_PrevResetState_lt = 1;
      rtDW.Integrator_PrevResetState_k = 1;
    } else {
      if (rtU.reset_status2_7 < 0.0F) {
        rtDW.Filter_PrevResetState_lt = -1;
      } else if (rtU.reset_status2_7 == 0.0F) {
        rtDW.Filter_PrevResetState_lt = 0;
      } else {
        rtDW.Filter_PrevResetState_lt = 2;
      }

      if (rtU.reset_status2_7 < 0.0F) {
        rtDW.Integrator_PrevResetState_k = -1;
      } else if (rtU.reset_status2_7 == 0.0F) {
        rtDW.Integrator_PrevResetState_k = 0;
      } else {
        rtDW.Integrator_PrevResetState_k = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2135>/Filter' */

    /* Update for DiscreteIntegrator: '<S2140>/Integrator' incorporates:
     *  Gain: '<S2137>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_dz += rtP.ANG_S_I_CH2_7 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S2207>/Action Port'
     */
    /* Sum: '<S2207>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_1'
     *  Inport: '<Root>/target_CH3_1'
     */
    rtb_Sum_cz = rtU.target_CH3_1 - rtU.speed_rpm_CH3_1;

    /* DiscreteIntegrator: '<S2238>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_1'
     */
    if (((rtU.reset_status3_1 > 0.0F) && (rtDW.Filter_PrevResetState_b5 <= 0)) ||
        ((rtU.reset_status3_1 <= 0.0F) && (rtDW.Filter_PrevResetState_b5 == 1)))
    {
      rtDW.Filter_DSTATE_et = 0.0F;
    }

    /* Gain: '<S2246>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2238>/Filter'
     *  Gain: '<S2236>/Derivative Gain'
     *  Sum: '<S2238>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH3_1 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_et) * 100.0F;

    /* DiscreteIntegrator: '<S2243>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_1'
     */
    if (((rtU.reset_status3_1 > 0.0F) && (rtDW.Integrator_PrevResetState_ge <= 0))
        || ((rtU.reset_status3_1 <= 0.0F) && (rtDW.Integrator_PrevResetState_ge ==
          1))) {
      rtDW.Integrator_DSTATE_op = 0.0F;
    }

    /* Sum: '<S2252>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2243>/Integrator'
     *  Gain: '<S2248>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_1 * rtb_Sum_cz + rtDW.Integrator_DSTATE_op) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S2250>/Saturation' */
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

    /* End of Saturate: '<S2250>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2238>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2243>/Integrator'
     *  Inport: '<Root>/reset_status3_1'
     */
    rtDW.Filter_DSTATE_et += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status3_1 > 0.0F) {
      rtDW.Filter_PrevResetState_b5 = 1;
      rtDW.Integrator_PrevResetState_ge = 1;
    } else {
      if (rtU.reset_status3_1 < 0.0F) {
        rtDW.Filter_PrevResetState_b5 = -1;
      } else if (rtU.reset_status3_1 == 0.0F) {
        rtDW.Filter_PrevResetState_b5 = 0;
      } else {
        rtDW.Filter_PrevResetState_b5 = 2;
      }

      if (rtU.reset_status3_1 < 0.0F) {
        rtDW.Integrator_PrevResetState_ge = -1;
      } else if (rtU.reset_status3_1 == 0.0F) {
        rtDW.Integrator_PrevResetState_ge = 0;
      } else {
        rtDW.Integrator_PrevResetState_ge = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2238>/Filter' */

    /* Update for DiscreteIntegrator: '<S2243>/Integrator' incorporates:
     *  Gain: '<S2240>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_op += rtP.SPD_I_CH3_1 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S15>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S15>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2208>/Action Port'
     */
    /* Sum: '<S2208>/Sum' incorporates:
     *  Gain: '<S2208>/Gain'
     *  Inport: '<Root>/circle_CH3_1'
     *  Inport: '<Root>/ecd_CH3_1'
     *  Inport: '<Root>/target_CH3_1'
     *  Sum: '<S2208>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH3_1 - (8191.0F * rtU.circle_CH3_1 +
      rtU.ecd_CH3_1);

    /* Abs: '<S2208>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S2208>/Switch2' incorporates:
     *  Constant: '<S2208>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH3_1)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S2208>/Switch2' */

    /* Gain: '<S2349>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2341>/Filter'
     *  Gain: '<S2339>/Derivative Gain'
     *  Sum: '<S2341>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH3_1 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_e4) * 100.0F;

    /* Switch: '<S2208>/Switch1' incorporates:
     *  Constant: '<S2208>/Constant'
     *  Gain: '<S2208>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_1'
     *  Saturate: '<S2353>/Saturation'
     *  Sum: '<S2208>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH3_1) {
      /* Sum: '<S2355>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2346>/Integrator'
       *  Gain: '<S2351>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_1 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_ly) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S2353>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH3_1 * u0 - rtU.speed_rpm_CH3_1;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S2208>/Switch1' */

    /* DiscreteIntegrator: '<S2291>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_1'
     */
    if (((rtU.reset_status3_1 > 0.0F) && (rtDW.Filter_PrevResetState_p <= 0)) ||
        ((rtU.reset_status3_1 <= 0.0F) && (rtDW.Filter_PrevResetState_p == 1)))
    {
      rtDW.Filter_DSTATE_fh = 0.0F;
    }

    /* Gain: '<S2299>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2291>/Filter'
     *  Gain: '<S2289>/Derivative Gain'
     *  Sum: '<S2291>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH3_1 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_fh) * 100.0F;

    /* DiscreteIntegrator: '<S2296>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_1'
     */
    if (((rtU.reset_status3_1 > 0.0F) && (rtDW.Integrator_PrevResetState_c <= 0))
        || ((rtU.reset_status3_1 <= 0.0F) && (rtDW.Integrator_PrevResetState_c ==
          1))) {
      rtDW.Integrator_DSTATE_ju = 0.0F;
    }

    /* Sum: '<S2305>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2296>/Integrator'
     *  Gain: '<S2301>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_1 * rtb_Sum_cz + rtDW.Integrator_DSTATE_ju) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S2303>/Saturation' */
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

    /* End of Saturate: '<S2303>/Saturation' */

    /* Chart: '<S2208>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_1'
     *  Inport: '<Root>/last_ecd_CH3_1'
     *  Sum: '<S2208>/Sum3'
     */
    Chart1(rtU.ecd_CH3_1 - rtU.last_ecd_CH3_1, &rtDW.u2_jx, &rtDW.sf_Chart1_hq);

    /* Outport: '<Root>/circle_out_CH3_1' incorporates:
     *  Inport: '<Root>/circle_CH3_1'
     *  Sum: '<S2208>/Sum4'
     */
    rtY.circle_out_CH3_1 = rtDW.u2_jx + rtU.circle_CH3_1;

    /* Update for DiscreteIntegrator: '<S2346>/Integrator' incorporates:
     *  Gain: '<S2343>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ly += rtP.ANG_A_I_CH3_1 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2341>/Filter' */
    rtDW.Filter_DSTATE_e4 += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S2291>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2296>/Integrator'
     *  Inport: '<Root>/reset_status3_1'
     */
    rtDW.Filter_DSTATE_fh += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status3_1 > 0.0F) {
      rtDW.Filter_PrevResetState_p = 1;
      rtDW.Integrator_PrevResetState_c = 1;
    } else {
      if (rtU.reset_status3_1 < 0.0F) {
        rtDW.Filter_PrevResetState_p = -1;
      } else if (rtU.reset_status3_1 == 0.0F) {
        rtDW.Filter_PrevResetState_p = 0;
      } else {
        rtDW.Filter_PrevResetState_p = 2;
      }

      if (rtU.reset_status3_1 < 0.0F) {
        rtDW.Integrator_PrevResetState_c = -1;
      } else if (rtU.reset_status3_1 == 0.0F) {
        rtDW.Integrator_PrevResetState_c = 0;
      } else {
        rtDW.Integrator_PrevResetState_c = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2291>/Filter' */

    /* Update for DiscreteIntegrator: '<S2296>/Integrator' incorporates:
     *  Gain: '<S2293>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ju += rtP.ANG_S_I_CH3_1 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S2363>/Action Port'
     */
    /* Sum: '<S2363>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_2'
     *  Inport: '<Root>/target_CH3_2'
     */
    rtb_Sum_cz = rtU.target_CH3_2 - rtU.speed_rpm_CH3_2;

    /* DiscreteIntegrator: '<S2394>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_2'
     */
    if (((rtU.reset_status3_2 > 0.0F) && (rtDW.Filter_PrevResetState_j2 <= 0)) ||
        ((rtU.reset_status3_2 <= 0.0F) && (rtDW.Filter_PrevResetState_j2 == 1)))
    {
      rtDW.Filter_DSTATE_no = 0.0F;
    }

    /* Gain: '<S2402>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2394>/Filter'
     *  Gain: '<S2392>/Derivative Gain'
     *  Sum: '<S2394>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH3_2 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_no) * 100.0F;

    /* DiscreteIntegrator: '<S2399>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_2'
     */
    if (((rtU.reset_status3_2 > 0.0F) && (rtDW.Integrator_PrevResetState_bq <= 0))
        || ((rtU.reset_status3_2 <= 0.0F) && (rtDW.Integrator_PrevResetState_bq ==
          1))) {
      rtDW.Integrator_DSTATE_h = 0.0F;
    }

    /* Sum: '<S2408>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2399>/Integrator'
     *  Gain: '<S2404>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_2 * rtb_Sum_cz + rtDW.Integrator_DSTATE_h) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S2406>/Saturation' */
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

    /* End of Saturate: '<S2406>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2394>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2399>/Integrator'
     *  Inport: '<Root>/reset_status3_2'
     */
    rtDW.Filter_DSTATE_no += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status3_2 > 0.0F) {
      rtDW.Filter_PrevResetState_j2 = 1;
      rtDW.Integrator_PrevResetState_bq = 1;
    } else {
      if (rtU.reset_status3_2 < 0.0F) {
        rtDW.Filter_PrevResetState_j2 = -1;
      } else if (rtU.reset_status3_2 == 0.0F) {
        rtDW.Filter_PrevResetState_j2 = 0;
      } else {
        rtDW.Filter_PrevResetState_j2 = 2;
      }

      if (rtU.reset_status3_2 < 0.0F) {
        rtDW.Integrator_PrevResetState_bq = -1;
      } else if (rtU.reset_status3_2 == 0.0F) {
        rtDW.Integrator_PrevResetState_bq = 0;
      } else {
        rtDW.Integrator_PrevResetState_bq = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2394>/Filter' */

    /* Update for DiscreteIntegrator: '<S2399>/Integrator' incorporates:
     *  Gain: '<S2396>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_h += rtP.SPD_I_CH3_2 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S16>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S16>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2364>/Action Port'
     */
    /* Sum: '<S2364>/Sum' incorporates:
     *  Gain: '<S2364>/Gain'
     *  Inport: '<Root>/circle_CH3_2'
     *  Inport: '<Root>/ecd_CH3_2'
     *  Inport: '<Root>/target_CH3_2'
     *  Sum: '<S2364>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH3_2 - (8191.0F * rtU.circle_CH3_2 +
      rtU.ecd_CH3_2);

    /* Abs: '<S2364>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S2364>/Switch2' incorporates:
     *  Constant: '<S2364>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH3_2)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S2364>/Switch2' */

    /* Gain: '<S2505>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2497>/Filter'
     *  Gain: '<S2495>/Derivative Gain'
     *  Sum: '<S2497>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH3_2 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_id) * 100.0F;

    /* Switch: '<S2364>/Switch1' incorporates:
     *  Constant: '<S2364>/Constant'
     *  Gain: '<S2364>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_2'
     *  Saturate: '<S2509>/Saturation'
     *  Sum: '<S2364>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH3_2) {
      /* Sum: '<S2511>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2502>/Integrator'
       *  Gain: '<S2507>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_2 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_du) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S2509>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH3_2 * u0 - rtU.speed_rpm_CH3_2;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S2364>/Switch1' */

    /* DiscreteIntegrator: '<S2447>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_2'
     */
    if (((rtU.reset_status3_2 > 0.0F) && (rtDW.Filter_PrevResetState_b <= 0)) ||
        ((rtU.reset_status3_2 <= 0.0F) && (rtDW.Filter_PrevResetState_b == 1)))
    {
      rtDW.Filter_DSTATE_iu = 0.0F;
    }

    /* Gain: '<S2455>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2447>/Filter'
     *  Gain: '<S2445>/Derivative Gain'
     *  Sum: '<S2447>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH3_2 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_iu) * 100.0F;

    /* DiscreteIntegrator: '<S2452>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_2'
     */
    if (((rtU.reset_status3_2 > 0.0F) && (rtDW.Integrator_PrevResetState_mv <= 0))
        || ((rtU.reset_status3_2 <= 0.0F) && (rtDW.Integrator_PrevResetState_mv ==
          1))) {
      rtDW.Integrator_DSTATE_po = 0.0F;
    }

    /* Sum: '<S2461>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2452>/Integrator'
     *  Gain: '<S2457>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_2 * rtb_Sum_cz + rtDW.Integrator_DSTATE_po) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S2459>/Saturation' */
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

    /* End of Saturate: '<S2459>/Saturation' */

    /* Chart: '<S2364>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_2'
     *  Inport: '<Root>/last_ecd_CH3_2'
     *  Sum: '<S2364>/Sum3'
     */
    Chart1(rtU.ecd_CH3_2 - rtU.last_ecd_CH3_2, &rtDW.u2_m, &rtDW.sf_Chart1_a);

    /* Outport: '<Root>/circle_out_CH3_2' incorporates:
     *  Inport: '<Root>/circle_CH3_2'
     *  Sum: '<S2364>/Sum4'
     */
    rtY.circle_out_CH3_2 = rtDW.u2_m + rtU.circle_CH3_2;

    /* Update for DiscreteIntegrator: '<S2502>/Integrator' incorporates:
     *  Gain: '<S2499>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_du += rtP.ANG_A_I_CH3_2 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2497>/Filter' */
    rtDW.Filter_DSTATE_id += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S2447>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2452>/Integrator'
     *  Inport: '<Root>/reset_status3_2'
     */
    rtDW.Filter_DSTATE_iu += 0.001F * rtb_FilterCoefficient_nkj;
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

    /* End of Update for DiscreteIntegrator: '<S2447>/Filter' */

    /* Update for DiscreteIntegrator: '<S2452>/Integrator' incorporates:
     *  Gain: '<S2449>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_po += rtP.ANG_S_I_CH3_2 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S2519>/Action Port'
     */
    /* Sum: '<S2519>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_3'
     *  Inport: '<Root>/target_CH3_3'
     */
    rtb_Sum_cz = rtU.target_CH3_3 - rtU.speed_rpm_CH3_3;

    /* DiscreteIntegrator: '<S2550>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_3'
     */
    if (((rtU.reset_status3_3 > 0.0F) && (rtDW.Filter_PrevResetState_j <= 0)) ||
        ((rtU.reset_status3_3 <= 0.0F) && (rtDW.Filter_PrevResetState_j == 1)))
    {
      rtDW.Filter_DSTATE_b = 0.0F;
    }

    /* Gain: '<S2558>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2550>/Filter'
     *  Gain: '<S2548>/Derivative Gain'
     *  Sum: '<S2550>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH3_3 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_b) * 100.0F;

    /* DiscreteIntegrator: '<S2555>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_3'
     */
    if (((rtU.reset_status3_3 > 0.0F) && (rtDW.Integrator_PrevResetState_bs <= 0))
        || ((rtU.reset_status3_3 <= 0.0F) && (rtDW.Integrator_PrevResetState_bs ==
          1))) {
      rtDW.Integrator_DSTATE_d = 0.0F;
    }

    /* Sum: '<S2564>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2555>/Integrator'
     *  Gain: '<S2560>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_3 * rtb_Sum_cz + rtDW.Integrator_DSTATE_d) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S2562>/Saturation' */
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

    /* End of Saturate: '<S2562>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2550>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2555>/Integrator'
     *  Inport: '<Root>/reset_status3_3'
     */
    rtDW.Filter_DSTATE_b += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status3_3 > 0.0F) {
      rtDW.Filter_PrevResetState_j = 1;
      rtDW.Integrator_PrevResetState_bs = 1;
    } else {
      if (rtU.reset_status3_3 < 0.0F) {
        rtDW.Filter_PrevResetState_j = -1;
      } else if (rtU.reset_status3_3 == 0.0F) {
        rtDW.Filter_PrevResetState_j = 0;
      } else {
        rtDW.Filter_PrevResetState_j = 2;
      }

      if (rtU.reset_status3_3 < 0.0F) {
        rtDW.Integrator_PrevResetState_bs = -1;
      } else if (rtU.reset_status3_3 == 0.0F) {
        rtDW.Integrator_PrevResetState_bs = 0;
      } else {
        rtDW.Integrator_PrevResetState_bs = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2550>/Filter' */

    /* Update for DiscreteIntegrator: '<S2555>/Integrator' incorporates:
     *  Gain: '<S2552>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_d += rtP.SPD_I_CH3_3 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S17>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S17>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2520>/Action Port'
     */
    /* Sum: '<S2520>/Sum' incorporates:
     *  Gain: '<S2520>/Gain'
     *  Inport: '<Root>/circle_CH3_3'
     *  Inport: '<Root>/ecd_CH3_3'
     *  Inport: '<Root>/target_CH3_3'
     *  Sum: '<S2520>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH3_3 - (8191.0F * rtU.circle_CH3_3 +
      rtU.ecd_CH3_3);

    /* Abs: '<S2520>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S2520>/Switch2' incorporates:
     *  Constant: '<S2520>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH3_3)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S2520>/Switch2' */

    /* Gain: '<S2661>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2653>/Filter'
     *  Gain: '<S2651>/Derivative Gain'
     *  Sum: '<S2653>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH3_3 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_a) * 100.0F;

    /* Switch: '<S2520>/Switch1' incorporates:
     *  Constant: '<S2520>/Constant'
     *  Gain: '<S2520>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_3'
     *  Saturate: '<S2665>/Saturation'
     *  Sum: '<S2520>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH3_3) {
      /* Sum: '<S2667>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2658>/Integrator'
       *  Gain: '<S2663>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_3 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_p) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S2665>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH3_3 * u0 - rtU.speed_rpm_CH3_3;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S2520>/Switch1' */

    /* DiscreteIntegrator: '<S2603>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_3'
     */
    if (((rtU.reset_status3_3 > 0.0F) && (rtDW.Filter_PrevResetState_el <= 0)) ||
        ((rtU.reset_status3_3 <= 0.0F) && (rtDW.Filter_PrevResetState_el == 1)))
    {
      rtDW.Filter_DSTATE_of = 0.0F;
    }

    /* Gain: '<S2611>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2603>/Filter'
     *  Gain: '<S2601>/Derivative Gain'
     *  Sum: '<S2603>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH3_3 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_of) * 100.0F;

    /* DiscreteIntegrator: '<S2608>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_3'
     */
    if (((rtU.reset_status3_3 > 0.0F) && (rtDW.Integrator_PrevResetState_e <= 0))
        || ((rtU.reset_status3_3 <= 0.0F) && (rtDW.Integrator_PrevResetState_e ==
          1))) {
      rtDW.Integrator_DSTATE_ka = 0.0F;
    }

    /* Sum: '<S2617>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2608>/Integrator'
     *  Gain: '<S2613>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_3 * rtb_Sum_cz + rtDW.Integrator_DSTATE_ka) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S2615>/Saturation' */
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

    /* End of Saturate: '<S2615>/Saturation' */

    /* Chart: '<S2520>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_3'
     *  Inport: '<Root>/last_ecd_CH3_3'
     *  Sum: '<S2520>/Sum3'
     */
    Chart1(rtU.ecd_CH3_3 - rtU.last_ecd_CH3_3, &rtDW.u2_n, &rtDW.sf_Chart1_kh);

    /* Outport: '<Root>/circle_out_CH3_3' incorporates:
     *  Inport: '<Root>/circle_CH3_3'
     *  Sum: '<S2520>/Sum4'
     */
    rtY.circle_out_CH3_3 = rtDW.u2_n + rtU.circle_CH3_3;

    /* Update for DiscreteIntegrator: '<S2658>/Integrator' incorporates:
     *  Gain: '<S2655>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_p += rtP.ANG_A_I_CH3_3 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2653>/Filter' */
    rtDW.Filter_DSTATE_a += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S2603>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2608>/Integrator'
     *  Inport: '<Root>/reset_status3_3'
     */
    rtDW.Filter_DSTATE_of += 0.001F * rtb_FilterCoefficient_nkj;
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

    /* End of Update for DiscreteIntegrator: '<S2603>/Filter' */

    /* Update for DiscreteIntegrator: '<S2608>/Integrator' incorporates:
     *  Gain: '<S2605>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_ka += rtP.ANG_S_I_CH3_3 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S2675>/Action Port'
     */
    /* Sum: '<S2675>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_4'
     *  Inport: '<Root>/target_CH3_4'
     */
    rtb_Sum_cz = rtU.target_CH3_4 - rtU.speed_rpm_CH3_4;

    /* DiscreteIntegrator: '<S2706>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_4'
     */
    if (((rtU.reset_status3_4 > 0.0F) && (rtDW.Filter_PrevResetState_e2 <= 0)) ||
        ((rtU.reset_status3_4 <= 0.0F) && (rtDW.Filter_PrevResetState_e2 == 1)))
    {
      rtDW.Filter_DSTATE_k = 0.0F;
    }

    /* Gain: '<S2714>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2706>/Filter'
     *  Gain: '<S2704>/Derivative Gain'
     *  Sum: '<S2706>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH3_4 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_k) * 100.0F;

    /* DiscreteIntegrator: '<S2711>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_4'
     */
    if (((rtU.reset_status3_4 > 0.0F) && (rtDW.Integrator_PrevResetState_n <= 0))
        || ((rtU.reset_status3_4 <= 0.0F) && (rtDW.Integrator_PrevResetState_n ==
          1))) {
      rtDW.Integrator_DSTATE_nm = 0.0F;
    }

    /* Sum: '<S2720>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2711>/Integrator'
     *  Gain: '<S2716>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_4 * rtb_Sum_cz + rtDW.Integrator_DSTATE_nm) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S2718>/Saturation' */
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

    /* End of Saturate: '<S2718>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2706>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2711>/Integrator'
     *  Inport: '<Root>/reset_status3_4'
     */
    rtDW.Filter_DSTATE_k += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status3_4 > 0.0F) {
      rtDW.Filter_PrevResetState_e2 = 1;
      rtDW.Integrator_PrevResetState_n = 1;
    } else {
      if (rtU.reset_status3_4 < 0.0F) {
        rtDW.Filter_PrevResetState_e2 = -1;
      } else if (rtU.reset_status3_4 == 0.0F) {
        rtDW.Filter_PrevResetState_e2 = 0;
      } else {
        rtDW.Filter_PrevResetState_e2 = 2;
      }

      if (rtU.reset_status3_4 < 0.0F) {
        rtDW.Integrator_PrevResetState_n = -1;
      } else if (rtU.reset_status3_4 == 0.0F) {
        rtDW.Integrator_PrevResetState_n = 0;
      } else {
        rtDW.Integrator_PrevResetState_n = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2706>/Filter' */

    /* Update for DiscreteIntegrator: '<S2711>/Integrator' incorporates:
     *  Gain: '<S2708>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_nm += rtP.SPD_I_CH3_4 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S18>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S18>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2676>/Action Port'
     */
    /* Sum: '<S2676>/Sum' incorporates:
     *  Gain: '<S2676>/Gain'
     *  Inport: '<Root>/circle_CH3_4'
     *  Inport: '<Root>/ecd_CH3_4'
     *  Inport: '<Root>/target_CH3_4'
     *  Sum: '<S2676>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH3_4 - (8191.0F * rtU.circle_CH3_4 +
      rtU.ecd_CH3_4);

    /* Abs: '<S2676>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S2676>/Switch2' incorporates:
     *  Constant: '<S2676>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH3_4)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S2676>/Switch2' */

    /* Gain: '<S2817>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2809>/Filter'
     *  Gain: '<S2807>/Derivative Gain'
     *  Sum: '<S2809>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH3_4 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_ip) * 100.0F;

    /* Switch: '<S2676>/Switch1' incorporates:
     *  Constant: '<S2676>/Constant'
     *  Gain: '<S2676>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_4'
     *  Saturate: '<S2821>/Saturation'
     *  Sum: '<S2676>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH3_4) {
      /* Sum: '<S2823>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2814>/Integrator'
       *  Gain: '<S2819>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_4 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_j) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S2821>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH3_4 * u0 - rtU.speed_rpm_CH3_4;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S2676>/Switch1' */

    /* DiscreteIntegrator: '<S2759>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_4'
     */
    if (((rtU.reset_status3_4 > 0.0F) && (rtDW.Filter_PrevResetState_d <= 0)) ||
        ((rtU.reset_status3_4 <= 0.0F) && (rtDW.Filter_PrevResetState_d == 1)))
    {
      rtDW.Filter_DSTATE_f = 0.0F;
    }

    /* Gain: '<S2767>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2759>/Filter'
     *  Gain: '<S2757>/Derivative Gain'
     *  Sum: '<S2759>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH3_4 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_f) * 100.0F;

    /* DiscreteIntegrator: '<S2764>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_4'
     */
    if (((rtU.reset_status3_4 > 0.0F) && (rtDW.Integrator_PrevResetState_g <= 0))
        || ((rtU.reset_status3_4 <= 0.0F) && (rtDW.Integrator_PrevResetState_g ==
          1))) {
      rtDW.Integrator_DSTATE_l = 0.0F;
    }

    /* Sum: '<S2773>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2764>/Integrator'
     *  Gain: '<S2769>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_4 * rtb_Sum_cz + rtDW.Integrator_DSTATE_l) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S2771>/Saturation' */
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

    /* End of Saturate: '<S2771>/Saturation' */

    /* Chart: '<S2676>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_4'
     *  Inport: '<Root>/last_ecd_CH3_4'
     *  Sum: '<S2676>/Sum3'
     */
    Chart1(rtU.ecd_CH3_4 - rtU.last_ecd_CH3_4, &rtDW.u2_j, &rtDW.sf_Chart1_i);

    /* Outport: '<Root>/circle_out_CH3_4' incorporates:
     *  Inport: '<Root>/circle_CH3_4'
     *  Sum: '<S2676>/Sum4'
     */
    rtY.circle_out_CH3_4 = rtDW.u2_j + rtU.circle_CH3_4;

    /* Update for DiscreteIntegrator: '<S2814>/Integrator' incorporates:
     *  Gain: '<S2811>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_j += rtP.ANG_A_I_CH3_4 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2809>/Filter' */
    rtDW.Filter_DSTATE_ip += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S2759>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2764>/Integrator'
     *  Inport: '<Root>/reset_status3_4'
     */
    rtDW.Filter_DSTATE_f += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status3_4 > 0.0F) {
      rtDW.Filter_PrevResetState_d = 1;
      rtDW.Integrator_PrevResetState_g = 1;
    } else {
      if (rtU.reset_status3_4 < 0.0F) {
        rtDW.Filter_PrevResetState_d = -1;
      } else if (rtU.reset_status3_4 == 0.0F) {
        rtDW.Filter_PrevResetState_d = 0;
      } else {
        rtDW.Filter_PrevResetState_d = 2;
      }

      if (rtU.reset_status3_4 < 0.0F) {
        rtDW.Integrator_PrevResetState_g = -1;
      } else if (rtU.reset_status3_4 == 0.0F) {
        rtDW.Integrator_PrevResetState_g = 0;
      } else {
        rtDW.Integrator_PrevResetState_g = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2759>/Filter' */

    /* Update for DiscreteIntegrator: '<S2764>/Integrator' incorporates:
     *  Gain: '<S2761>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_l += rtP.ANG_S_I_CH3_4 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S2831>/Action Port'
     */
    /* Sum: '<S2831>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_5'
     *  Inport: '<Root>/target_CH3_5'
     */
    rtb_Sum_cz = rtU.target_CH3_5 - rtU.speed_rpm_CH3_5;

    /* DiscreteIntegrator: '<S2862>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_5'
     */
    if (((rtU.reset_status3_5 > 0.0F) && (rtDW.Filter_PrevResetState_n <= 0)) ||
        ((rtU.reset_status3_5 <= 0.0F) && (rtDW.Filter_PrevResetState_n == 1)))
    {
      rtDW.Filter_DSTATE_jy = 0.0F;
    }

    /* Gain: '<S2870>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2862>/Filter'
     *  Gain: '<S2860>/Derivative Gain'
     *  Sum: '<S2862>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH3_5 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_jy) * 100.0F;

    /* DiscreteIntegrator: '<S2867>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_5'
     */
    if (((rtU.reset_status3_5 > 0.0F) && (rtDW.Integrator_PrevResetState_py <= 0))
        || ((rtU.reset_status3_5 <= 0.0F) && (rtDW.Integrator_PrevResetState_py ==
          1))) {
      rtDW.Integrator_DSTATE_f = 0.0F;
    }

    /* Sum: '<S2876>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2867>/Integrator'
     *  Gain: '<S2872>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_5 * rtb_Sum_cz + rtDW.Integrator_DSTATE_f) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S2874>/Saturation' */
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

    /* End of Saturate: '<S2874>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2862>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2867>/Integrator'
     *  Inport: '<Root>/reset_status3_5'
     */
    rtDW.Filter_DSTATE_jy += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status3_5 > 0.0F) {
      rtDW.Filter_PrevResetState_n = 1;
      rtDW.Integrator_PrevResetState_py = 1;
    } else {
      if (rtU.reset_status3_5 < 0.0F) {
        rtDW.Filter_PrevResetState_n = -1;
      } else if (rtU.reset_status3_5 == 0.0F) {
        rtDW.Filter_PrevResetState_n = 0;
      } else {
        rtDW.Filter_PrevResetState_n = 2;
      }

      if (rtU.reset_status3_5 < 0.0F) {
        rtDW.Integrator_PrevResetState_py = -1;
      } else if (rtU.reset_status3_5 == 0.0F) {
        rtDW.Integrator_PrevResetState_py = 0;
      } else {
        rtDW.Integrator_PrevResetState_py = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S2862>/Filter' */

    /* Update for DiscreteIntegrator: '<S2867>/Integrator' incorporates:
     *  Gain: '<S2864>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_f += rtP.SPD_I_CH3_5 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S19>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S19>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2832>/Action Port'
     */
    /* Sum: '<S2832>/Sum' incorporates:
     *  Gain: '<S2832>/Gain'
     *  Inport: '<Root>/circle_CH3_5'
     *  Inport: '<Root>/ecd_CH3_5'
     *  Inport: '<Root>/target_CH3_5'
     *  Sum: '<S2832>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH3_5 - (8191.0F * rtU.circle_CH3_5 +
      rtU.ecd_CH3_5);

    /* Abs: '<S2832>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S2832>/Switch2' incorporates:
     *  Constant: '<S2832>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH3_5)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S2832>/Switch2' */

    /* Gain: '<S2973>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2965>/Filter'
     *  Gain: '<S2963>/Derivative Gain'
     *  Sum: '<S2965>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH3_5 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_e) * 100.0F;

    /* Switch: '<S2832>/Switch1' incorporates:
     *  Constant: '<S2832>/Constant'
     *  Gain: '<S2832>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_5'
     *  Saturate: '<S2977>/Saturation'
     *  Sum: '<S2832>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH3_5) {
      /* Sum: '<S2979>/Sum' incorporates:
       *  DiscreteIntegrator: '<S2970>/Integrator'
       *  Gain: '<S2975>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_5 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_i0) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S2977>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH3_5 * u0 - rtU.speed_rpm_CH3_5;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S2832>/Switch1' */

    /* DiscreteIntegrator: '<S2915>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_5'
     */
    if (((rtU.reset_status3_5 > 0.0F) && (rtDW.Filter_PrevResetState_e <= 0)) ||
        ((rtU.reset_status3_5 <= 0.0F) && (rtDW.Filter_PrevResetState_e == 1)))
    {
      rtDW.Filter_DSTATE_o = 0.0F;
    }

    /* Gain: '<S2923>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S2915>/Filter'
     *  Gain: '<S2913>/Derivative Gain'
     *  Sum: '<S2915>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH3_5 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_o) * 100.0F;

    /* DiscreteIntegrator: '<S2920>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_5'
     */
    if (((rtU.reset_status3_5 > 0.0F) && (rtDW.Integrator_PrevResetState_m <= 0))
        || ((rtU.reset_status3_5 <= 0.0F) && (rtDW.Integrator_PrevResetState_m ==
          1))) {
      rtDW.Integrator_DSTATE_oc = 0.0F;
    }

    /* Sum: '<S2929>/Sum' incorporates:
     *  DiscreteIntegrator: '<S2920>/Integrator'
     *  Gain: '<S2925>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_5 * rtb_Sum_cz + rtDW.Integrator_DSTATE_oc) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S2927>/Saturation' */
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

    /* End of Saturate: '<S2927>/Saturation' */

    /* Chart: '<S2832>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_5'
     *  Inport: '<Root>/last_ecd_CH3_5'
     *  Sum: '<S2832>/Sum3'
     */
    Chart1(rtU.ecd_CH3_5 - rtU.last_ecd_CH3_5, &rtDW.u2_p, &rtDW.sf_Chart1_df);

    /* Outport: '<Root>/circle_out_CH3_5' incorporates:
     *  Inport: '<Root>/circle_CH3_5'
     *  Sum: '<S2832>/Sum4'
     */
    rtY.circle_out_CH3_5 = rtDW.u2_p + rtU.circle_CH3_5;

    /* Update for DiscreteIntegrator: '<S2970>/Integrator' incorporates:
     *  Gain: '<S2967>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_i0 += rtP.ANG_A_I_CH3_5 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S2965>/Filter' */
    rtDW.Filter_DSTATE_e += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S2915>/Filter' incorporates:
     *  DiscreteIntegrator: '<S2920>/Integrator'
     *  Inport: '<Root>/reset_status3_5'
     */
    rtDW.Filter_DSTATE_o += 0.001F * rtb_FilterCoefficient_nkj;
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

    /* End of Update for DiscreteIntegrator: '<S2915>/Filter' */

    /* Update for DiscreteIntegrator: '<S2920>/Integrator' incorporates:
     *  Gain: '<S2917>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_oc += rtP.ANG_S_I_CH3_5 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S2987>/Action Port'
     */
    /* Sum: '<S2987>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_6'
     *  Inport: '<Root>/target_CH3_6'
     */
    rtb_Sum_cz = rtU.target_CH3_6 - rtU.speed_rpm_CH3_6;

    /* DiscreteIntegrator: '<S3018>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_6'
     */
    if (((rtU.reset_status3_6 > 0.0F) && (rtDW.Filter_PrevResetState_lk <= 0)) ||
        ((rtU.reset_status3_6 <= 0.0F) && (rtDW.Filter_PrevResetState_lk == 1)))
    {
      rtDW.Filter_DSTATE_jo = 0.0F;
    }

    /* Gain: '<S3026>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S3018>/Filter'
     *  Gain: '<S3016>/Derivative Gain'
     *  Sum: '<S3018>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH3_6 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_jo) * 100.0F;

    /* DiscreteIntegrator: '<S3023>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_6'
     */
    if (((rtU.reset_status3_6 > 0.0F) && (rtDW.Integrator_PrevResetState_o <= 0))
        || ((rtU.reset_status3_6 <= 0.0F) && (rtDW.Integrator_PrevResetState_o ==
          1))) {
      rtDW.Integrator_DSTATE_n = 0.0F;
    }

    /* Sum: '<S3032>/Sum' incorporates:
     *  DiscreteIntegrator: '<S3023>/Integrator'
     *  Gain: '<S3028>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_6 * rtb_Sum_cz + rtDW.Integrator_DSTATE_n) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S3030>/Saturation' */
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

    /* End of Saturate: '<S3030>/Saturation' */

    /* Update for DiscreteIntegrator: '<S3018>/Filter' incorporates:
     *  DiscreteIntegrator: '<S3023>/Integrator'
     *  Inport: '<Root>/reset_status3_6'
     */
    rtDW.Filter_DSTATE_jo += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status3_6 > 0.0F) {
      rtDW.Filter_PrevResetState_lk = 1;
      rtDW.Integrator_PrevResetState_o = 1;
    } else {
      if (rtU.reset_status3_6 < 0.0F) {
        rtDW.Filter_PrevResetState_lk = -1;
      } else if (rtU.reset_status3_6 == 0.0F) {
        rtDW.Filter_PrevResetState_lk = 0;
      } else {
        rtDW.Filter_PrevResetState_lk = 2;
      }

      if (rtU.reset_status3_6 < 0.0F) {
        rtDW.Integrator_PrevResetState_o = -1;
      } else if (rtU.reset_status3_6 == 0.0F) {
        rtDW.Integrator_PrevResetState_o = 0;
      } else {
        rtDW.Integrator_PrevResetState_o = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S3018>/Filter' */

    /* Update for DiscreteIntegrator: '<S3023>/Integrator' incorporates:
     *  Gain: '<S3020>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_n += rtP.SPD_I_CH3_6 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S20>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S20>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S2988>/Action Port'
     */
    /* Sum: '<S2988>/Sum' incorporates:
     *  Gain: '<S2988>/Gain'
     *  Inport: '<Root>/circle_CH3_6'
     *  Inport: '<Root>/ecd_CH3_6'
     *  Inport: '<Root>/target_CH3_6'
     *  Sum: '<S2988>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH3_6 - (8191.0F * rtU.circle_CH3_6 +
      rtU.ecd_CH3_6);

    /* Abs: '<S2988>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S2988>/Switch2' incorporates:
     *  Constant: '<S2988>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH3_6)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S2988>/Switch2' */

    /* Gain: '<S3129>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S3121>/Filter'
     *  Gain: '<S3119>/Derivative Gain'
     *  Sum: '<S3121>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH3_6 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_m) * 100.0F;

    /* Switch: '<S2988>/Switch1' incorporates:
     *  Constant: '<S2988>/Constant'
     *  Gain: '<S2988>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_6'
     *  Saturate: '<S3133>/Saturation'
     *  Sum: '<S2988>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH3_6) {
      /* Sum: '<S3135>/Sum' incorporates:
       *  DiscreteIntegrator: '<S3126>/Integrator'
       *  Gain: '<S3131>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_6 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_c) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S3133>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH3_6 * u0 - rtU.speed_rpm_CH3_6;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S2988>/Switch1' */

    /* DiscreteIntegrator: '<S3071>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_6'
     */
    if (((rtU.reset_status3_6 > 0.0F) && (rtDW.Filter_PrevResetState_c <= 0)) ||
        ((rtU.reset_status3_6 <= 0.0F) && (rtDW.Filter_PrevResetState_c == 1)))
    {
      rtDW.Filter_DSTATE_n = 0.0F;
    }

    /* Gain: '<S3079>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S3071>/Filter'
     *  Gain: '<S3069>/Derivative Gain'
     *  Sum: '<S3071>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH3_6 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_n) * 100.0F;

    /* DiscreteIntegrator: '<S3076>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_6'
     */
    if (((rtU.reset_status3_6 > 0.0F) && (rtDW.Integrator_PrevResetState_b <= 0))
        || ((rtU.reset_status3_6 <= 0.0F) && (rtDW.Integrator_PrevResetState_b ==
          1))) {
      rtDW.Integrator_DSTATE_k = 0.0F;
    }

    /* Sum: '<S3085>/Sum' incorporates:
     *  DiscreteIntegrator: '<S3076>/Integrator'
     *  Gain: '<S3081>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_6 * rtb_Sum_cz + rtDW.Integrator_DSTATE_k) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S3083>/Saturation' */
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

    /* End of Saturate: '<S3083>/Saturation' */

    /* Chart: '<S2988>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_6'
     *  Inport: '<Root>/last_ecd_CH3_6'
     *  Sum: '<S2988>/Sum3'
     */
    Chart1(rtU.ecd_CH3_6 - rtU.last_ecd_CH3_6, &rtDW.u2_b, &rtDW.sf_Chart1_c);

    /* Outport: '<Root>/circle_out_CH3_6' incorporates:
     *  Inport: '<Root>/circle_CH3_6'
     *  Sum: '<S2988>/Sum4'
     */
    rtY.circle_out_CH3_6 = rtDW.u2_b + rtU.circle_CH3_6;

    /* Update for DiscreteIntegrator: '<S3126>/Integrator' incorporates:
     *  Gain: '<S3123>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_c += rtP.ANG_A_I_CH3_6 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S3121>/Filter' */
    rtDW.Filter_DSTATE_m += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S3071>/Filter' incorporates:
     *  DiscreteIntegrator: '<S3076>/Integrator'
     *  Inport: '<Root>/reset_status3_6'
     */
    rtDW.Filter_DSTATE_n += 0.001F * rtb_FilterCoefficient_nkj;
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

    /* End of Update for DiscreteIntegrator: '<S3071>/Filter' */

    /* Update for DiscreteIntegrator: '<S3076>/Integrator' incorporates:
     *  Gain: '<S3073>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_k += rtP.ANG_S_I_CH3_6 * rtb_Sum_cz * 0.001F;

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
     *  ActionPort: '<S3143>/Action Port'
     */
    /* Sum: '<S3143>/Sum' incorporates:
     *  Inport: '<Root>/speed_rpm_CH3_7'
     *  Inport: '<Root>/target_CH3_7'
     */
    rtb_Sum_cz = rtU.target_CH3_7 - rtU.speed_rpm_CH3_7;

    /* DiscreteIntegrator: '<S3174>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_7'
     */
    if (((rtU.reset_status3_7 > 0.0F) && (rtDW.Filter_PrevResetState_l <= 0)) ||
        ((rtU.reset_status3_7 <= 0.0F) && (rtDW.Filter_PrevResetState_l == 1)))
    {
      rtDW.Filter_DSTATE_j = 0.0F;
    }

    /* Gain: '<S3182>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S3174>/Filter'
     *  Gain: '<S3172>/Derivative Gain'
     *  Sum: '<S3174>/SumD'
     */
    rtb_FilterCoefficient_eu = (rtP.SPD_D_CH3_7 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_j) * 100.0F;

    /* DiscreteIntegrator: '<S3179>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_7'
     */
    if (((rtU.reset_status3_7 > 0.0F) && (rtDW.Integrator_PrevResetState_p <= 0))
        || ((rtU.reset_status3_7 <= 0.0F) && (rtDW.Integrator_PrevResetState_p ==
          1))) {
      rtDW.Integrator_DSTATE_if = 0.0F;
    }

    /* Sum: '<S3188>/Sum' incorporates:
     *  DiscreteIntegrator: '<S3179>/Integrator'
     *  Gain: '<S3184>/Proportional Gain'
     */
    u0 = (rtP.SPD_P_CH3_7 * rtb_Sum_cz + rtDW.Integrator_DSTATE_if) +
      rtb_FilterCoefficient_eu;

    /* Saturate: '<S3186>/Saturation' */
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

    /* End of Saturate: '<S3186>/Saturation' */

    /* Update for DiscreteIntegrator: '<S3174>/Filter' incorporates:
     *  DiscreteIntegrator: '<S3179>/Integrator'
     *  Inport: '<Root>/reset_status3_7'
     */
    rtDW.Filter_DSTATE_j += 0.001F * rtb_FilterCoefficient_eu;
    if (rtU.reset_status3_7 > 0.0F) {
      rtDW.Filter_PrevResetState_l = 1;
      rtDW.Integrator_PrevResetState_p = 1;
    } else {
      if (rtU.reset_status3_7 < 0.0F) {
        rtDW.Filter_PrevResetState_l = -1;
      } else if (rtU.reset_status3_7 == 0.0F) {
        rtDW.Filter_PrevResetState_l = 0;
      } else {
        rtDW.Filter_PrevResetState_l = 2;
      }

      if (rtU.reset_status3_7 < 0.0F) {
        rtDW.Integrator_PrevResetState_p = -1;
      } else if (rtU.reset_status3_7 == 0.0F) {
        rtDW.Integrator_PrevResetState_p = 0;
      } else {
        rtDW.Integrator_PrevResetState_p = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S3174>/Filter' */

    /* Update for DiscreteIntegrator: '<S3179>/Integrator' incorporates:
     *  Gain: '<S3176>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_if += rtP.SPD_I_CH3_7 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S21>/If Action_speed Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S21>/If Action_speed Subsystem1' incorporates:
     *  ActionPort: '<S3144>/Action Port'
     */
    /* Sum: '<S3144>/Sum' incorporates:
     *  Gain: '<S3144>/Gain'
     *  Inport: '<Root>/circle_CH3_7'
     *  Inport: '<Root>/ecd_CH3_7'
     *  Inport: '<Root>/target_CH3_7'
     *  Sum: '<S3144>/Sum2'
     */
    rtb_FilterCoefficient_eu = rtU.target_CH3_7 - (8191.0F * rtU.circle_CH3_7 +
      rtU.ecd_CH3_7);

    /* Abs: '<S3144>/Abs' */
    rtb_Sum_cz = (real32_T)fabs(rtb_FilterCoefficient_eu);

    /* Switch: '<S3144>/Switch2' incorporates:
     *  Constant: '<S3144>/Constant'
     */
    if (!(rtb_Sum_cz > rtP.DEADBAND_CH3_7)) {
      rtb_FilterCoefficient_eu = 0.0F;
    }

    /* End of Switch: '<S3144>/Switch2' */

    /* Gain: '<S3285>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S3277>/Filter'
     *  Gain: '<S3275>/Derivative Gain'
     *  Sum: '<S3277>/SumD'
     */
    rtb_FilterCoefficient_ch = (rtP.ANG_A_D_CH3_7 * rtb_FilterCoefficient_eu -
      rtDW.Filter_DSTATE_p) * 100.0F;

    /* Switch: '<S3144>/Switch1' incorporates:
     *  Constant: '<S3144>/Constant'
     *  Gain: '<S3144>/Multiply'
     *  Inport: '<Root>/speed_rpm_CH3_7'
     *  Saturate: '<S3289>/Saturation'
     *  Sum: '<S3144>/Sum1'
     */
    if (rtb_Sum_cz > rtP.DEADBAND_CH3_7) {
      /* Sum: '<S3291>/Sum' incorporates:
       *  DiscreteIntegrator: '<S3282>/Integrator'
       *  Gain: '<S3287>/Proportional Gain'
       */
      u0 = (rtP.ANG_A_P_CH3_7 * rtb_FilterCoefficient_eu +
            rtDW.Integrator_DSTATE_i) + rtb_FilterCoefficient_ch;

      /* Saturate: '<S3289>/Saturation' */
      if (u0 > 16384.0F) {
        u0 = 16384.0F;
      } else if (u0 < -16384.0F) {
        u0 = -16384.0F;
      }

      rtb_Sum_cz = rtP.TRANS_CH3_7 * u0 - rtU.speed_rpm_CH3_7;
    } else {
      rtb_Sum_cz = 0.0F;
    }

    /* End of Switch: '<S3144>/Switch1' */

    /* DiscreteIntegrator: '<S3227>/Filter' incorporates:
     *  Inport: '<Root>/reset_status3_7'
     */
    if (((rtU.reset_status3_7 > 0.0F) && (rtDW.Filter_PrevResetState <= 0)) ||
        ((rtU.reset_status3_7 <= 0.0F) && (rtDW.Filter_PrevResetState == 1))) {
      rtDW.Filter_DSTATE_i = 0.0F;
    }

    /* Gain: '<S3235>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S3227>/Filter'
     *  Gain: '<S3225>/Derivative Gain'
     *  Sum: '<S3227>/SumD'
     */
    rtb_FilterCoefficient_nkj = (rtP.ANG_S_D_CH3_7 * rtb_Sum_cz -
      rtDW.Filter_DSTATE_i) * 100.0F;

    /* DiscreteIntegrator: '<S3232>/Integrator' incorporates:
     *  Inport: '<Root>/reset_status3_7'
     */
    if (((rtU.reset_status3_7 > 0.0F) && (rtDW.Integrator_PrevResetState <= 0)) ||
        ((rtU.reset_status3_7 <= 0.0F) && (rtDW.Integrator_PrevResetState == 1)))
    {
      rtDW.Integrator_DSTATE_o = 0.0F;
    }

    /* Sum: '<S3241>/Sum' incorporates:
     *  DiscreteIntegrator: '<S3232>/Integrator'
     *  Gain: '<S3237>/Proportional Gain'
     */
    u0 = (rtP.ANG_S_P_CH3_7 * rtb_Sum_cz + rtDW.Integrator_DSTATE_o) +
      rtb_FilterCoefficient_nkj;

    /* Saturate: '<S3239>/Saturation' */
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

    /* End of Saturate: '<S3239>/Saturation' */

    /* Chart: '<S3144>/Chart1' incorporates:
     *  Inport: '<Root>/ecd_CH3_7'
     *  Inport: '<Root>/last_ecd_CH3_7'
     *  Sum: '<S3144>/Sum3'
     */
    Chart1(rtU.ecd_CH3_7 - rtU.last_ecd_CH3_7, &rtDW.u2, &rtDW.sf_Chart1_b);

    /* Outport: '<Root>/circle_out_CH3_7' incorporates:
     *  Inport: '<Root>/circle_CH3_7'
     *  Sum: '<S3144>/Sum4'
     */
    rtY.circle_out_CH3_7 = rtDW.u2 + rtU.circle_CH3_7;

    /* Update for DiscreteIntegrator: '<S3282>/Integrator' incorporates:
     *  Gain: '<S3279>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_i += rtP.ANG_A_I_CH3_7 * rtb_FilterCoefficient_eu *
      0.001F;

    /* Update for DiscreteIntegrator: '<S3277>/Filter' */
    rtDW.Filter_DSTATE_p += 0.001F * rtb_FilterCoefficient_ch;

    /* Update for DiscreteIntegrator: '<S3227>/Filter' incorporates:
     *  DiscreteIntegrator: '<S3232>/Integrator'
     *  Inport: '<Root>/reset_status3_7'
     */
    rtDW.Filter_DSTATE_i += 0.001F * rtb_FilterCoefficient_nkj;
    if (rtU.reset_status3_7 > 0.0F) {
      rtDW.Filter_PrevResetState = 1;
      rtDW.Integrator_PrevResetState = 1;
    } else {
      if (rtU.reset_status3_7 < 0.0F) {
        rtDW.Filter_PrevResetState = -1;
      } else if (rtU.reset_status3_7 == 0.0F) {
        rtDW.Filter_PrevResetState = 0;
      } else {
        rtDW.Filter_PrevResetState = 2;
      }

      if (rtU.reset_status3_7 < 0.0F) {
        rtDW.Integrator_PrevResetState = -1;
      } else if (rtU.reset_status3_7 == 0.0F) {
        rtDW.Integrator_PrevResetState = 0;
      } else {
        rtDW.Integrator_PrevResetState = 2;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S3227>/Filter' */

    /* Update for DiscreteIntegrator: '<S3232>/Integrator' incorporates:
     *  Gain: '<S3229>/Integral Gain'
     */
    rtDW.Integrator_DSTATE_o += rtP.ANG_S_I_CH3_7 * rtb_Sum_cz * 0.001F;

    /* End of Outputs for SubSystem: '<S21>/If Action_speed Subsystem1' */
    break;
  }

  /* End of SwitchCase: '<S21>/Switch Case' */

  /* Update for DiscreteIntegrator: '<S3332>/Integrator' incorporates:
   *  Gain: '<S3329>/Integral Gain'
   *  Inport: '<Root>/distance'
   */
  rtDW.Integrator_DSTATE += rtP.POS_I * rtU.distance * 0.001F;

  /* Update for DiscreteIntegrator: '<S3327>/Filter' */
  rtDW.Filter_DSTATE += 0.001F * rtb_FilterCoefficient;
}

/* Model initialize function */
void PID_MODEL_initialize(void)
{
  /* SystemInitialize for IfAction SubSystem: '<S1>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S54>/Filter' */
  rtDW.Filter_PrevResetState_bi = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S59>/Integrator' */
  rtDW.Integrator_PrevResetState_a2 = 2;

  /* End of SystemInitialize for SubSystem: '<S1>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S1>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S107>/Filter' */
  rtDW.Filter_PrevResetState_hk = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S112>/Integrator' */
  rtDW.Integrator_PrevResetState_mx = 2;

  /* SystemInitialize for Chart: '<S24>/Chart1' */
  Chart1_Init(&rtDW.u2_nnb);

  /* End of SystemInitialize for SubSystem: '<S1>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S2>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S210>/Filter' */
  rtDW.Filter_PrevResetState_eo = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S215>/Integrator' */
  rtDW.Integrator_PrevResetState_np = 2;

  /* End of SystemInitialize for SubSystem: '<S2>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S2>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S263>/Filter' */
  rtDW.Filter_PrevResetState_a2 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S268>/Integrator' */
  rtDW.Integrator_PrevResetState_dc = 2;

  /* SystemInitialize for Chart: '<S180>/Chart1' */
  Chart1_Init(&rtDW.u2_jxj);

  /* End of SystemInitialize for SubSystem: '<S2>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S3>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S366>/Filter' */
  rtDW.Filter_PrevResetState_ev = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S371>/Integrator' */
  rtDW.Integrator_PrevResetState_l1 = 2;

  /* End of SystemInitialize for SubSystem: '<S3>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S3>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S419>/Filter' */
  rtDW.Filter_PrevResetState_na = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S424>/Integrator' */
  rtDW.Integrator_PrevResetState_pi = 2;

  /* SystemInitialize for Chart: '<S336>/Chart1' */
  Chart1_Init(&rtDW.u2_j2);

  /* End of SystemInitialize for SubSystem: '<S3>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S4>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S522>/Filter' */
  rtDW.Filter_PrevResetState_b0 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S527>/Integrator' */
  rtDW.Integrator_PrevResetState_fz = 2;

  /* End of SystemInitialize for SubSystem: '<S4>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S4>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S575>/Filter' */
  rtDW.Filter_PrevResetState_gs = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S580>/Integrator' */
  rtDW.Integrator_PrevResetState_fb = 2;

  /* SystemInitialize for Chart: '<S492>/Chart1' */
  Chart1_Init(&rtDW.u2_a);

  /* End of SystemInitialize for SubSystem: '<S4>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S5>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S678>/Filter' */
  rtDW.Filter_PrevResetState_h = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S683>/Integrator' */
  rtDW.Integrator_PrevResetState_l = 2;

  /* End of SystemInitialize for SubSystem: '<S5>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S5>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S731>/Filter' */
  rtDW.Filter_PrevResetState_kt = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S736>/Integrator' */
  rtDW.Integrator_PrevResetState_a = 2;

  /* SystemInitialize for Chart: '<S648>/Chart1' */
  Chart1_Init(&rtDW.u2_c);

  /* End of SystemInitialize for SubSystem: '<S5>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S6>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S834>/Filter' */
  rtDW.Filter_PrevResetState_fp = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S839>/Integrator' */
  rtDW.Integrator_PrevResetState_ds = 2;

  /* End of SystemInitialize for SubSystem: '<S6>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S6>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S887>/Filter' */
  rtDW.Filter_PrevResetState_lp = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S892>/Integrator' */
  rtDW.Integrator_PrevResetState_je = 2;

  /* SystemInitialize for Chart: '<S804>/Chart1' */
  Chart1_Init(&rtDW.u2_nn);

  /* End of SystemInitialize for SubSystem: '<S6>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S7>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S990>/Filter' */
  rtDW.Filter_PrevResetState_kk = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S995>/Integrator' */
  rtDW.Integrator_PrevResetState_od = 2;

  /* End of SystemInitialize for SubSystem: '<S7>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S7>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1043>/Filter' */
  rtDW.Filter_PrevResetState_nc = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1048>/Integrator' */
  rtDW.Integrator_PrevResetState_gr = 2;

  /* SystemInitialize for Chart: '<S960>/Chart1' */
  Chart1_Init(&rtDW.u2_f4);

  /* End of SystemInitialize for SubSystem: '<S7>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S8>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S1146>/Filter' */
  rtDW.Filter_PrevResetState_a = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1151>/Integrator' */
  rtDW.Integrator_PrevResetState_j = 2;

  /* End of SystemInitialize for SubSystem: '<S8>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S8>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1199>/Filter' */
  rtDW.Filter_PrevResetState_k3 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1204>/Integrator' */
  rtDW.Integrator_PrevResetState_k5 = 2;

  /* SystemInitialize for Chart: '<S1116>/Chart1' */
  Chart1_Init(&rtDW.u2_f);

  /* End of SystemInitialize for SubSystem: '<S8>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S9>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S1302>/Filter' */
  rtDW.Filter_PrevResetState_lr = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1307>/Integrator' */
  rtDW.Integrator_PrevResetState_dv = 2;

  /* End of SystemInitialize for SubSystem: '<S9>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S9>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1355>/Filter' */
  rtDW.Filter_PrevResetState_mx = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1360>/Integrator' */
  rtDW.Integrator_PrevResetState_d0 = 2;

  /* SystemInitialize for Chart: '<S1272>/Chart1' */
  Chart1_Init(&rtDW.u2_k);

  /* End of SystemInitialize for SubSystem: '<S9>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S10>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S1458>/Filter' */
  rtDW.Filter_PrevResetState_k = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1463>/Integrator' */
  rtDW.Integrator_PrevResetState_o2 = 2;

  /* End of SystemInitialize for SubSystem: '<S10>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S10>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1511>/Filter' */
  rtDW.Filter_PrevResetState_m = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1516>/Integrator' */
  rtDW.Integrator_PrevResetState_dj = 2;

  /* SystemInitialize for Chart: '<S1428>/Chart1' */
  Chart1_Init(&rtDW.u2_or);

  /* End of SystemInitialize for SubSystem: '<S10>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S11>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S1614>/Filter' */
  rtDW.Filter_PrevResetState_lf = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1619>/Integrator' */
  rtDW.Integrator_PrevResetState_d = 2;

  /* End of SystemInitialize for SubSystem: '<S11>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S11>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1667>/Filter' */
  rtDW.Filter_PrevResetState_i = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1672>/Integrator' */
  rtDW.Integrator_PrevResetState_ih = 2;

  /* SystemInitialize for Chart: '<S1584>/Chart1' */
  Chart1_Init(&rtDW.u2_o);

  /* End of SystemInitialize for SubSystem: '<S11>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S12>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S1770>/Filter' */
  rtDW.Filter_PrevResetState_o = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1775>/Integrator' */
  rtDW.Integrator_PrevResetState_f = 2;

  /* End of SystemInitialize for SubSystem: '<S12>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S12>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1823>/Filter' */
  rtDW.Filter_PrevResetState_f3 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1828>/Integrator' */
  rtDW.Integrator_PrevResetState_bsc = 2;

  /* SystemInitialize for Chart: '<S1740>/Chart1' */
  Chart1_Init(&rtDW.u2_n2);

  /* End of SystemInitialize for SubSystem: '<S12>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S13>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S1926>/Filter' */
  rtDW.Filter_PrevResetState_g = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1931>/Integrator' */
  rtDW.Integrator_PrevResetState_mq = 2;

  /* End of SystemInitialize for SubSystem: '<S13>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S13>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S1979>/Filter' */
  rtDW.Filter_PrevResetState_f = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S1984>/Integrator' */
  rtDW.Integrator_PrevResetState_ny = 2;

  /* SystemInitialize for Chart: '<S1896>/Chart1' */
  Chart1_Init(&rtDW.u2_h);

  /* End of SystemInitialize for SubSystem: '<S13>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S14>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S2082>/Filter' */
  rtDW.Filter_PrevResetState_ng = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2087>/Integrator' */
  rtDW.Integrator_PrevResetState_i = 2;

  /* End of SystemInitialize for SubSystem: '<S14>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S14>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S2135>/Filter' */
  rtDW.Filter_PrevResetState_lt = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2140>/Integrator' */
  rtDW.Integrator_PrevResetState_k = 2;

  /* SystemInitialize for Chart: '<S2052>/Chart1' */
  Chart1_Init(&rtDW.u2_e);

  /* End of SystemInitialize for SubSystem: '<S14>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S15>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S2238>/Filter' */
  rtDW.Filter_PrevResetState_b5 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2243>/Integrator' */
  rtDW.Integrator_PrevResetState_ge = 2;

  /* End of SystemInitialize for SubSystem: '<S15>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S15>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S2291>/Filter' */
  rtDW.Filter_PrevResetState_p = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2296>/Integrator' */
  rtDW.Integrator_PrevResetState_c = 2;

  /* SystemInitialize for Chart: '<S2208>/Chart1' */
  Chart1_Init(&rtDW.u2_jx);

  /* End of SystemInitialize for SubSystem: '<S15>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S16>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S2394>/Filter' */
  rtDW.Filter_PrevResetState_j2 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2399>/Integrator' */
  rtDW.Integrator_PrevResetState_bq = 2;

  /* End of SystemInitialize for SubSystem: '<S16>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S16>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S2447>/Filter' */
  rtDW.Filter_PrevResetState_b = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2452>/Integrator' */
  rtDW.Integrator_PrevResetState_mv = 2;

  /* SystemInitialize for Chart: '<S2364>/Chart1' */
  Chart1_Init(&rtDW.u2_m);

  /* End of SystemInitialize for SubSystem: '<S16>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S17>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S2550>/Filter' */
  rtDW.Filter_PrevResetState_j = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2555>/Integrator' */
  rtDW.Integrator_PrevResetState_bs = 2;

  /* End of SystemInitialize for SubSystem: '<S17>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S17>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S2603>/Filter' */
  rtDW.Filter_PrevResetState_el = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2608>/Integrator' */
  rtDW.Integrator_PrevResetState_e = 2;

  /* SystemInitialize for Chart: '<S2520>/Chart1' */
  Chart1_Init(&rtDW.u2_n);

  /* End of SystemInitialize for SubSystem: '<S17>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S18>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S2706>/Filter' */
  rtDW.Filter_PrevResetState_e2 = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2711>/Integrator' */
  rtDW.Integrator_PrevResetState_n = 2;

  /* End of SystemInitialize for SubSystem: '<S18>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S18>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S2759>/Filter' */
  rtDW.Filter_PrevResetState_d = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2764>/Integrator' */
  rtDW.Integrator_PrevResetState_g = 2;

  /* SystemInitialize for Chart: '<S2676>/Chart1' */
  Chart1_Init(&rtDW.u2_j);

  /* End of SystemInitialize for SubSystem: '<S18>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S19>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S2862>/Filter' */
  rtDW.Filter_PrevResetState_n = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2867>/Integrator' */
  rtDW.Integrator_PrevResetState_py = 2;

  /* End of SystemInitialize for SubSystem: '<S19>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S19>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S2915>/Filter' */
  rtDW.Filter_PrevResetState_e = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S2920>/Integrator' */
  rtDW.Integrator_PrevResetState_m = 2;

  /* SystemInitialize for Chart: '<S2832>/Chart1' */
  Chart1_Init(&rtDW.u2_p);

  /* End of SystemInitialize for SubSystem: '<S19>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S20>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S3018>/Filter' */
  rtDW.Filter_PrevResetState_lk = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S3023>/Integrator' */
  rtDW.Integrator_PrevResetState_o = 2;

  /* End of SystemInitialize for SubSystem: '<S20>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S20>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S3071>/Filter' */
  rtDW.Filter_PrevResetState_c = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S3076>/Integrator' */
  rtDW.Integrator_PrevResetState_b = 2;

  /* SystemInitialize for Chart: '<S2988>/Chart1' */
  Chart1_Init(&rtDW.u2_b);

  /* End of SystemInitialize for SubSystem: '<S20>/If Action_speed Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S21>/If Action_speed Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S3174>/Filter' */
  rtDW.Filter_PrevResetState_l = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S3179>/Integrator' */
  rtDW.Integrator_PrevResetState_p = 2;

  /* End of SystemInitialize for SubSystem: '<S21>/If Action_speed Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S21>/If Action_speed Subsystem1' */
  /* InitializeConditions for DiscreteIntegrator: '<S3227>/Filter' */
  rtDW.Filter_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S3232>/Integrator' */
  rtDW.Integrator_PrevResetState = 2;

  /* SystemInitialize for Chart: '<S3144>/Chart1' */
  Chart1_Init(&rtDW.u2);

  /* End of SystemInitialize for SubSystem: '<S21>/If Action_speed Subsystem1' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
