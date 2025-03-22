/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PID_MODEL_data.c
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

/* Block parameters (default storage) */
P rtP = {
  /* Variable: ANG_A_D_CH1_1
   * Referenced by: '<S156>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH1_2
   * Referenced by: '<S312>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH1_3
   * Referenced by: '<S468>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH1_4
   * Referenced by: '<S624>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH1_5
   * Referenced by: '<S780>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH1_6
   * Referenced by: '<S936>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH1_7
   * Referenced by: '<S1092>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_1
   * Referenced by: '<S1248>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_2
   * Referenced by: '<S1404>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_3
   * Referenced by: '<S1560>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_4
   * Referenced by: '<S1716>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_5
   * Referenced by: '<S1872>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_6
   * Referenced by: '<S2028>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_7
   * Referenced by: '<S2184>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_1
   * Referenced by: '<S2340>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_2
   * Referenced by: '<S2496>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_3
   * Referenced by: '<S2652>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_4
   * Referenced by: '<S2808>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_5
   * Referenced by: '<S2964>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_6
   * Referenced by: '<S3120>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_7
   * Referenced by: '<S3276>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_1
   * Referenced by: '<S160>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_2
   * Referenced by: '<S316>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_3
   * Referenced by: '<S472>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_4
   * Referenced by: '<S628>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_5
   * Referenced by: '<S784>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_6
   * Referenced by: '<S940>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_7
   * Referenced by: '<S1096>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_1
   * Referenced by: '<S1252>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_2
   * Referenced by: '<S1408>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_3
   * Referenced by: '<S1564>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_4
   * Referenced by: '<S1720>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_5
   * Referenced by: '<S1876>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_6
   * Referenced by: '<S2032>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_7
   * Referenced by: '<S2188>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_1
   * Referenced by: '<S2344>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_2
   * Referenced by: '<S2500>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_3
   * Referenced by: '<S2656>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_4
   * Referenced by: '<S2812>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_5
   * Referenced by: '<S2968>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_6
   * Referenced by: '<S3124>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_7
   * Referenced by: '<S3280>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_1
   * Referenced by: '<S168>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_2
   * Referenced by: '<S324>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_3
   * Referenced by: '<S480>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_4
   * Referenced by: '<S636>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_5
   * Referenced by: '<S792>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_6
   * Referenced by: '<S948>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_7
   * Referenced by: '<S1104>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_1
   * Referenced by: '<S1260>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_2
   * Referenced by: '<S1416>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_3
   * Referenced by: '<S1572>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_4
   * Referenced by: '<S1728>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_5
   * Referenced by: '<S1884>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_6
   * Referenced by: '<S2040>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_7
   * Referenced by: '<S2196>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_1
   * Referenced by: '<S2352>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_2
   * Referenced by: '<S2508>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_3
   * Referenced by: '<S2664>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_4
   * Referenced by: '<S2820>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_5
   * Referenced by: '<S2976>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_6
   * Referenced by: '<S3132>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_7
   * Referenced by: '<S3288>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_1
   * Referenced by: '<S106>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_2
   * Referenced by: '<S262>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_3
   * Referenced by: '<S418>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_4
   * Referenced by: '<S574>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_5
   * Referenced by: '<S730>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_6
   * Referenced by: '<S886>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_7
   * Referenced by: '<S1042>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_1
   * Referenced by: '<S1198>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_2
   * Referenced by: '<S1354>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_3
   * Referenced by: '<S1510>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_4
   * Referenced by: '<S1666>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_5
   * Referenced by: '<S1822>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_6
   * Referenced by: '<S1978>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_7
   * Referenced by: '<S2134>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_1
   * Referenced by: '<S2290>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_2
   * Referenced by: '<S2446>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_3
   * Referenced by: '<S2602>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_4
   * Referenced by: '<S2758>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_5
   * Referenced by: '<S2914>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_6
   * Referenced by: '<S3070>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_7
   * Referenced by: '<S3226>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_1
   * Referenced by: '<S110>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_2
   * Referenced by: '<S266>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_3
   * Referenced by: '<S422>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_4
   * Referenced by: '<S578>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_5
   * Referenced by: '<S734>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_6
   * Referenced by: '<S890>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_7
   * Referenced by: '<S1046>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_1
   * Referenced by: '<S1202>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_2
   * Referenced by: '<S1358>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_3
   * Referenced by: '<S1514>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_4
   * Referenced by: '<S1670>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_5
   * Referenced by: '<S1826>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_6
   * Referenced by: '<S1982>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_7
   * Referenced by: '<S2138>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_1
   * Referenced by: '<S2294>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_2
   * Referenced by: '<S2450>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_3
   * Referenced by: '<S2606>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_4
   * Referenced by: '<S2762>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_5
   * Referenced by: '<S2918>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_6
   * Referenced by: '<S3074>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_7
   * Referenced by: '<S3230>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_1
   * Referenced by: '<S118>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_2
   * Referenced by: '<S274>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_3
   * Referenced by: '<S430>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_4
   * Referenced by: '<S586>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_5
   * Referenced by: '<S742>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_6
   * Referenced by: '<S898>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_7
   * Referenced by: '<S1054>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_1
   * Referenced by: '<S1210>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_2
   * Referenced by: '<S1366>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_3
   * Referenced by: '<S1522>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_4
   * Referenced by: '<S1678>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_5
   * Referenced by: '<S1834>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_6
   * Referenced by: '<S1990>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_7
   * Referenced by: '<S2146>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_1
   * Referenced by: '<S2302>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_2
   * Referenced by: '<S2458>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_3
   * Referenced by: '<S2614>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_4
   * Referenced by: '<S2770>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_5
   * Referenced by: '<S2926>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_6
   * Referenced by: '<S3082>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_7
   * Referenced by: '<S3238>/Proportional Gain'
   */
  0.0F,

  /* Variable: DEADBAND_ANG
   * Referenced by: '<Root>/Switch1'
   */
  20.0F,

  /* Variable: DEADBAND_CH1_1
   * Referenced by:
   *   '<S25>/Switch1'
   *   '<S25>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH1_2
   * Referenced by:
   *   '<S181>/Switch1'
   *   '<S181>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH1_3
   * Referenced by:
   *   '<S337>/Switch1'
   *   '<S337>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH1_4
   * Referenced by:
   *   '<S493>/Switch1'
   *   '<S493>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH1_5
   * Referenced by:
   *   '<S649>/Switch1'
   *   '<S649>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH1_6
   * Referenced by:
   *   '<S805>/Switch1'
   *   '<S805>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH1_7
   * Referenced by:
   *   '<S961>/Switch1'
   *   '<S961>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH2_1
   * Referenced by:
   *   '<S1117>/Switch1'
   *   '<S1117>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH2_2
   * Referenced by:
   *   '<S1273>/Switch1'
   *   '<S1273>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH2_3
   * Referenced by:
   *   '<S1429>/Switch1'
   *   '<S1429>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH2_4
   * Referenced by:
   *   '<S1585>/Switch1'
   *   '<S1585>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH2_5
   * Referenced by:
   *   '<S1741>/Switch1'
   *   '<S1741>/Switch2'
   */
  5.0F,

  /* Variable: DEADBAND_CH2_6
   * Referenced by:
   *   '<S1897>/Switch1'
   *   '<S1897>/Switch2'
   */
  5.0F,

  /* Variable: DEADBAND_CH2_7
   * Referenced by:
   *   '<S2053>/Switch1'
   *   '<S2053>/Switch2'
   */
  5.0F,

  /* Variable: DEADBAND_CH3_1
   * Referenced by:
   *   '<S2209>/Switch1'
   *   '<S2209>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH3_2
   * Referenced by:
   *   '<S2365>/Switch1'
   *   '<S2365>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH3_3
   * Referenced by:
   *   '<S2521>/Switch1'
   *   '<S2521>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH3_4
   * Referenced by:
   *   '<S2677>/Switch1'
   *   '<S2677>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH3_5
   * Referenced by:
   *   '<S2833>/Switch1'
   *   '<S2833>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH3_6
   * Referenced by:
   *   '<S2989>/Switch1'
   *   '<S2989>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_CH3_7
   * Referenced by:
   *   '<S3145>/Switch1'
   *   '<S3145>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_POS
   * Referenced by: '<Root>/Switch2'
   */
  10.0F,

  /* Variable: DEADBAND_spr_CH1_1
   * Referenced by: '<S24>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH1_2
   * Referenced by: '<S180>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH1_3
   * Referenced by: '<S336>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH1_4
   * Referenced by: '<S492>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH1_5
   * Referenced by: '<S648>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH1_6
   * Referenced by: '<S804>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH1_7
   * Referenced by: '<S960>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH2_1
   * Referenced by: '<S1116>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH2_2
   * Referenced by: '<S1272>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH2_3
   * Referenced by: '<S1428>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH2_4
   * Referenced by: '<S1584>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH2_5
   * Referenced by:
   *   '<S1740>/Switch2'
   *   '<S2052>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH2_6
   * Referenced by: '<S1896>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH3_1
   * Referenced by: '<S2208>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH3_2
   * Referenced by: '<S2364>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH3_3
   * Referenced by: '<S2520>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH3_4
   * Referenced by: '<S2676>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH3_5
   * Referenced by: '<S2832>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH3_6
   * Referenced by: '<S2988>/Switch2'
   */
  20.0F,

  /* Variable: DEADBAND_spr_CH3_7
   * Referenced by: '<S3144>/Switch2'
   */
  20.0F,

  /* Variable: POS_A_D
   * Referenced by: '<S3376>/Derivative Gain'
   */
  0.0F,

  /* Variable: POS_A_I
   * Referenced by: '<S3380>/Integral Gain'
   */
  0.0F,

  /* Variable: POS_A_P
   * Referenced by: '<S3388>/Proportional Gain'
   */
  0.0F,

  /* Variable: POS_D
   * Referenced by: '<S3326>/Derivative Gain'
   */
  0.0F,

  /* Variable: POS_I
   * Referenced by: '<S3330>/Integral Gain'
   */
  0.0F,

  /* Variable: POS_P
   * Referenced by: '<S3338>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_1
   * Referenced by: '<S53>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_2
   * Referenced by: '<S209>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_3
   * Referenced by: '<S365>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_4
   * Referenced by: '<S521>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_5
   * Referenced by: '<S677>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_6
   * Referenced by: '<S833>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_7
   * Referenced by: '<S989>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_1
   * Referenced by: '<S1145>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_2
   * Referenced by: '<S1301>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_3
   * Referenced by: '<S1457>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_4
   * Referenced by: '<S1613>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_5
   * Referenced by: '<S1769>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_6
   * Referenced by: '<S1925>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_7
   * Referenced by: '<S2081>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_1
   * Referenced by: '<S2237>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_2
   * Referenced by: '<S2393>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_3
   * Referenced by: '<S2549>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_4
   * Referenced by: '<S2705>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_5
   * Referenced by: '<S2861>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_6
   * Referenced by: '<S3017>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_7
   * Referenced by: '<S3173>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_1
   * Referenced by: '<S57>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_2
   * Referenced by: '<S213>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_3
   * Referenced by: '<S369>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_4
   * Referenced by: '<S525>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_5
   * Referenced by: '<S681>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_6
   * Referenced by: '<S837>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_7
   * Referenced by: '<S993>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_1
   * Referenced by: '<S1149>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_2
   * Referenced by: '<S1305>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_3
   * Referenced by: '<S1461>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_4
   * Referenced by: '<S1617>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_5
   * Referenced by: '<S1773>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_6
   * Referenced by: '<S1929>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_7
   * Referenced by: '<S2085>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_1
   * Referenced by: '<S2241>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_2
   * Referenced by: '<S2397>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_3
   * Referenced by: '<S2553>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_4
   * Referenced by: '<S2709>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_5
   * Referenced by: '<S2865>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_6
   * Referenced by: '<S3021>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_7
   * Referenced by: '<S3177>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_1
   * Referenced by: '<S65>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_2
   * Referenced by: '<S221>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_3
   * Referenced by: '<S377>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_4
   * Referenced by: '<S533>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_5
   * Referenced by: '<S689>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_6
   * Referenced by: '<S845>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_7
   * Referenced by: '<S1001>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_1
   * Referenced by: '<S1157>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_2
   * Referenced by: '<S1313>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_3
   * Referenced by: '<S1469>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_4
   * Referenced by: '<S1625>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_5
   * Referenced by: '<S1781>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_6
   * Referenced by: '<S1937>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_7
   * Referenced by: '<S2093>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_1
   * Referenced by: '<S2249>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_2
   * Referenced by: '<S2405>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_3
   * Referenced by: '<S2561>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_4
   * Referenced by: '<S2717>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_5
   * Referenced by: '<S2873>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_6
   * Referenced by: '<S3029>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_7
   * Referenced by: '<S3185>/Proportional Gain'
   */
  0.0F,

  /* Variable: TRANS_CH1_1
   * Referenced by: '<S25>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH1_2
   * Referenced by: '<S181>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH1_3
   * Referenced by: '<S337>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH1_4
   * Referenced by: '<S493>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH1_5
   * Referenced by: '<S649>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH1_6
   * Referenced by: '<S805>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH1_7
   * Referenced by: '<S961>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_1
   * Referenced by: '<S1117>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_2
   * Referenced by: '<S1273>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_3
   * Referenced by: '<S1429>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_4
   * Referenced by: '<S1585>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_5
   * Referenced by: '<S1741>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_6
   * Referenced by: '<S1897>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_7
   * Referenced by: '<S2053>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_1
   * Referenced by: '<S2209>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_2
   * Referenced by: '<S2365>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_3
   * Referenced by: '<S2521>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_4
   * Referenced by: '<S2677>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_5
   * Referenced by: '<S2833>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_6
   * Referenced by: '<S2989>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_7
   * Referenced by: '<S3145>/Multiply'
   */
  0.5F
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
