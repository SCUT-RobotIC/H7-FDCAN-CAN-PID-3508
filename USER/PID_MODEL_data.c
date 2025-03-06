/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PID_MODEL_data.c
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

/* Block parameters (default storage) */
P rtP = {
  /* Variable: ANG_A_D_CH1_1
   * Referenced by: '<S155>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH1_2
   * Referenced by: '<S311>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH1_3
   * Referenced by: '<S467>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH1_4
   * Referenced by: '<S623>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH1_5
   * Referenced by: '<S779>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH1_6
   * Referenced by: '<S935>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH1_7
   * Referenced by: '<S1091>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_1
   * Referenced by: '<S1247>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_2
   * Referenced by: '<S1403>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_3
   * Referenced by: '<S1559>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_4
   * Referenced by: '<S1715>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_5
   * Referenced by: '<S1871>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_6
   * Referenced by: '<S2027>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH2_7
   * Referenced by: '<S2183>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_1
   * Referenced by: '<S2339>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_2
   * Referenced by: '<S2495>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_3
   * Referenced by: '<S2651>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_4
   * Referenced by: '<S2807>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_5
   * Referenced by: '<S2963>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_6
   * Referenced by: '<S3119>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_D_CH3_7
   * Referenced by: '<S3275>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_1
   * Referenced by: '<S159>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_2
   * Referenced by: '<S315>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_3
   * Referenced by: '<S471>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_4
   * Referenced by: '<S627>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_5
   * Referenced by: '<S783>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_6
   * Referenced by: '<S939>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH1_7
   * Referenced by: '<S1095>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_1
   * Referenced by: '<S1251>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_2
   * Referenced by: '<S1407>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_3
   * Referenced by: '<S1563>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_4
   * Referenced by: '<S1719>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_5
   * Referenced by: '<S1875>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_6
   * Referenced by: '<S2031>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH2_7
   * Referenced by: '<S2187>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_1
   * Referenced by: '<S2343>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_2
   * Referenced by: '<S2499>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_3
   * Referenced by: '<S2655>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_4
   * Referenced by: '<S2811>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_5
   * Referenced by: '<S2967>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_6
   * Referenced by: '<S3123>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_I_CH3_7
   * Referenced by: '<S3279>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_1
   * Referenced by: '<S167>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_2
   * Referenced by: '<S323>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_3
   * Referenced by: '<S479>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_4
   * Referenced by: '<S635>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_5
   * Referenced by: '<S791>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_6
   * Referenced by: '<S947>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH1_7
   * Referenced by: '<S1103>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_1
   * Referenced by: '<S1259>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_2
   * Referenced by: '<S1415>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_3
   * Referenced by: '<S1571>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_4
   * Referenced by: '<S1727>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_5
   * Referenced by: '<S1883>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_6
   * Referenced by: '<S2039>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH2_7
   * Referenced by: '<S2195>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_1
   * Referenced by: '<S2351>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_2
   * Referenced by: '<S2507>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_3
   * Referenced by: '<S2663>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_4
   * Referenced by: '<S2819>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_5
   * Referenced by: '<S2975>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_6
   * Referenced by: '<S3131>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_A_P_CH3_7
   * Referenced by: '<S3287>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_1
   * Referenced by: '<S105>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_2
   * Referenced by: '<S261>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_3
   * Referenced by: '<S417>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_4
   * Referenced by: '<S573>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_5
   * Referenced by: '<S729>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_6
   * Referenced by: '<S885>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH1_7
   * Referenced by: '<S1041>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_1
   * Referenced by: '<S1197>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_2
   * Referenced by: '<S1353>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_3
   * Referenced by: '<S1509>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_4
   * Referenced by: '<S1665>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_5
   * Referenced by: '<S1821>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_6
   * Referenced by: '<S1977>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH2_7
   * Referenced by: '<S2133>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_1
   * Referenced by: '<S2289>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_2
   * Referenced by: '<S2445>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_3
   * Referenced by: '<S2601>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_4
   * Referenced by: '<S2757>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_5
   * Referenced by: '<S2913>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_6
   * Referenced by: '<S3069>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_D_CH3_7
   * Referenced by: '<S3225>/Derivative Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_1
   * Referenced by: '<S109>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_2
   * Referenced by: '<S265>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_3
   * Referenced by: '<S421>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_4
   * Referenced by: '<S577>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_5
   * Referenced by: '<S733>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_6
   * Referenced by: '<S889>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH1_7
   * Referenced by: '<S1045>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_1
   * Referenced by: '<S1201>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_2
   * Referenced by: '<S1357>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_3
   * Referenced by: '<S1513>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_4
   * Referenced by: '<S1669>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_5
   * Referenced by: '<S1825>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_6
   * Referenced by: '<S1981>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH2_7
   * Referenced by: '<S2137>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_1
   * Referenced by: '<S2293>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_2
   * Referenced by: '<S2449>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_3
   * Referenced by: '<S2605>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_4
   * Referenced by: '<S2761>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_5
   * Referenced by: '<S2917>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_6
   * Referenced by: '<S3073>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_I_CH3_7
   * Referenced by: '<S3229>/Integral Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_1
   * Referenced by: '<S117>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_2
   * Referenced by: '<S273>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_3
   * Referenced by: '<S429>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_4
   * Referenced by: '<S585>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_5
   * Referenced by: '<S741>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_6
   * Referenced by: '<S897>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH1_7
   * Referenced by: '<S1053>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_1
   * Referenced by: '<S1209>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_2
   * Referenced by: '<S1365>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_3
   * Referenced by: '<S1521>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_4
   * Referenced by: '<S1677>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_5
   * Referenced by: '<S1833>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_6
   * Referenced by: '<S1989>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH2_7
   * Referenced by: '<S2145>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_1
   * Referenced by: '<S2301>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_2
   * Referenced by: '<S2457>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_3
   * Referenced by: '<S2613>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_4
   * Referenced by: '<S2769>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_5
   * Referenced by: '<S2925>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_6
   * Referenced by: '<S3081>/Proportional Gain'
   */
  0.0F,

  /* Variable: ANG_S_P_CH3_7
   * Referenced by: '<S3237>/Proportional Gain'
   */
  0.0F,

  /* Variable: DEADBAND_CH1_1
   * Referenced by:
   *   '<S24>/Switch1'
   *   '<S24>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH1_2
   * Referenced by:
   *   '<S180>/Switch1'
   *   '<S180>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH1_3
   * Referenced by:
   *   '<S336>/Switch1'
   *   '<S336>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH1_4
   * Referenced by:
   *   '<S492>/Switch1'
   *   '<S492>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH1_5
   * Referenced by:
   *   '<S648>/Switch1'
   *   '<S648>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH1_6
   * Referenced by:
   *   '<S804>/Switch1'
   *   '<S804>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH1_7
   * Referenced by:
   *   '<S960>/Switch1'
   *   '<S960>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH2_1
   * Referenced by:
   *   '<S1116>/Switch1'
   *   '<S1116>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH2_2
   * Referenced by:
   *   '<S1272>/Switch1'
   *   '<S1272>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH2_3
   * Referenced by:
   *   '<S1428>/Switch1'
   *   '<S1428>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH2_4
   * Referenced by:
   *   '<S1584>/Switch1'
   *   '<S1584>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH2_5
   * Referenced by:
   *   '<S1740>/Switch1'
   *   '<S1740>/Switch2'
   */
  10.0F,

  /* Variable: DEADBAND_CH2_6
   * Referenced by:
   *   '<S1896>/Switch1'
   *   '<S1896>/Switch2'
   */
  10.0F,

  /* Variable: DEADBAND_CH2_7
   * Referenced by:
   *   '<S2052>/Switch1'
   *   '<S2052>/Switch2'
   */
  10.0F,

  /* Variable: DEADBAND_CH3_1
   * Referenced by:
   *   '<S2208>/Switch1'
   *   '<S2208>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH3_2
   * Referenced by:
   *   '<S2364>/Switch1'
   *   '<S2364>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH3_3
   * Referenced by:
   *   '<S2520>/Switch1'
   *   '<S2520>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH3_4
   * Referenced by:
   *   '<S2676>/Switch1'
   *   '<S2676>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH3_5
   * Referenced by:
   *   '<S2832>/Switch1'
   *   '<S2832>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH3_6
   * Referenced by:
   *   '<S2988>/Switch1'
   *   '<S2988>/Switch2'
   */
  500.0F,

  /* Variable: DEADBAND_CH3_7
   * Referenced by:
   *   '<S3144>/Switch1'
   *   '<S3144>/Switch2'
   */
  500.0F,

  /* Variable: POS_D
   * Referenced by: '<S3325>/Derivative Gain'
   */
  0.0F,

  /* Variable: POS_I
   * Referenced by: '<S3329>/Integral Gain'
   */
  0.0F,

  /* Variable: POS_P
   * Referenced by: '<S3337>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_1
   * Referenced by: '<S52>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_2
   * Referenced by: '<S208>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_3
   * Referenced by: '<S364>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_4
   * Referenced by: '<S520>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_5
   * Referenced by: '<S676>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_6
   * Referenced by: '<S832>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH1_7
   * Referenced by: '<S988>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_1
   * Referenced by: '<S1144>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_2
   * Referenced by: '<S1300>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_3
   * Referenced by: '<S1456>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_4
   * Referenced by: '<S1612>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_5
   * Referenced by: '<S1768>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_6
   * Referenced by: '<S1924>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH2_7
   * Referenced by: '<S2080>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_1
   * Referenced by: '<S2236>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_2
   * Referenced by: '<S2392>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_3
   * Referenced by: '<S2548>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_4
   * Referenced by: '<S2704>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_5
   * Referenced by: '<S2860>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_6
   * Referenced by: '<S3016>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_D_CH3_7
   * Referenced by: '<S3172>/Derivative Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_1
   * Referenced by: '<S56>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_2
   * Referenced by: '<S212>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_3
   * Referenced by: '<S368>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_4
   * Referenced by: '<S524>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_5
   * Referenced by: '<S680>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_6
   * Referenced by: '<S836>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH1_7
   * Referenced by: '<S992>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_1
   * Referenced by: '<S1148>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_2
   * Referenced by: '<S1304>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_3
   * Referenced by: '<S1460>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_4
   * Referenced by: '<S1616>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_5
   * Referenced by: '<S1772>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_6
   * Referenced by: '<S1928>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH2_7
   * Referenced by: '<S2084>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_1
   * Referenced by: '<S2240>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_2
   * Referenced by: '<S2396>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_3
   * Referenced by: '<S2552>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_4
   * Referenced by: '<S2708>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_5
   * Referenced by: '<S2864>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_6
   * Referenced by: '<S3020>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_I_CH3_7
   * Referenced by: '<S3176>/Integral Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_1
   * Referenced by: '<S64>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_2
   * Referenced by: '<S220>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_3
   * Referenced by: '<S376>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_4
   * Referenced by: '<S532>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_5
   * Referenced by: '<S688>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_6
   * Referenced by: '<S844>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH1_7
   * Referenced by: '<S1000>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_1
   * Referenced by: '<S1156>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_2
   * Referenced by: '<S1312>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_3
   * Referenced by: '<S1468>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_4
   * Referenced by: '<S1624>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_5
   * Referenced by: '<S1780>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_6
   * Referenced by: '<S1936>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH2_7
   * Referenced by: '<S2092>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_1
   * Referenced by: '<S2248>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_2
   * Referenced by: '<S2404>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_3
   * Referenced by: '<S2560>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_4
   * Referenced by: '<S2716>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_5
   * Referenced by: '<S2872>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_6
   * Referenced by: '<S3028>/Proportional Gain'
   */
  0.0F,

  /* Variable: SPD_P_CH3_7
   * Referenced by: '<S3184>/Proportional Gain'
   */
  0.0F,

  /* Variable: TRANS_CH1_1
   * Referenced by: '<S24>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH1_2
   * Referenced by: '<S180>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH1_3
   * Referenced by: '<S336>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH1_4
   * Referenced by: '<S492>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH1_5
   * Referenced by: '<S648>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH1_6
   * Referenced by: '<S804>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH1_7
   * Referenced by: '<S960>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_1
   * Referenced by: '<S1116>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_2
   * Referenced by: '<S1272>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_3
   * Referenced by: '<S1428>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_4
   * Referenced by: '<S1584>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_5
   * Referenced by: '<S1740>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_6
   * Referenced by: '<S1896>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH2_7
   * Referenced by: '<S2052>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_1
   * Referenced by: '<S2208>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_2
   * Referenced by: '<S2364>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_3
   * Referenced by: '<S2520>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_4
   * Referenced by: '<S2676>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_5
   * Referenced by: '<S2832>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_6
   * Referenced by: '<S2988>/Multiply'
   */
  0.5F,

  /* Variable: TRANS_CH3_7
   * Referenced by: '<S3144>/Multiply'
   */
  0.5F
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
