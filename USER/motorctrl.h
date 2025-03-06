#ifndef MOTORCTRL_H
#define MOTORCTRL_H
#include "main.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "PID_MODEL.h"
#include "bsp_fdcan.h"
#include "motorctrl.h"
#include "stdio.h"
#include "math.h"

typedef enum
{
	CH1_1,
	CH1_2,
	CH1_3,
	CH1_4,
	CH1_5,
	CH1_6,
	CH1_7,
			
	CH2_1,
	CH2_2,
	CH2_3,
	CH2_4,
	CH2_5,
	CH2_6,
	CH2_7,
	
	CH3_1,
	CH3_2,
	CH3_3,
	CH3_4,
	CH3_5,
	CH3_6,
	CH3_7
	
}chennel;
extern double tor_output[3*8];
typedef struct
{
	int dir;
	double thetal;
	double thetan_cal_last;
	double thetan_cal;
	double thetan;
	double thetas;
	double err;
	double err1;
	double err2;
	double errl;
	
} ang_dir;

typedef struct
{
  double Vx;
	double Vy;
	double omega;
	double Park;
} vehicle_state;

void get_msgn(void);
void assign_output(void);
void set_mode(int mode_CH1_1, int mode_CH1_2, int mode_CH1_3, int mode_CH1_4, int mode_CH1_5, int mode_CH1_6, int mode_CH1_7,
              int mode_CH2_1, int mode_CH2_2, int mode_CH2_3, int mode_CH2_4, int mode_CH2_5, int mode_CH2_6, int mode_CH2_7,
							int mode_CH3_1, int mode_CH3_2, int mode_CH3_3, int mode_CH3_4, int mode_CH3_5, int mode_CH3_6, int mode_CH3_7);
void set_reset_status(void);
void cala_d(int i);
void ctrlmotor(double Vx, double Vy, double omega,int brake) ;
void set_target(uint8_t channel,uint8_t id,int target);
void PID_Speed_Para_Init(int channel, int motor, double kp, double ki, double kd);
void PID_Angle_S_Para_Init(int channel, int motor, double kp, double ki, double kd);
void PID_Angle_A_Para_Init(int channel, int motor, double kp, double ki, double kd);


#endif
