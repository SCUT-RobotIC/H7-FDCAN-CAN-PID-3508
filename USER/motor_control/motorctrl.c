#include "motorctrl.h"
#include "UPPER_LOCATION.h"
#define PI 3.1415926
#define MAXVEL 6000
ang_dir MotorSignal[3];
extern motor_measure_t *motor_data_can1[8];
extern motor_measure_t *motor_data_can2[8];
extern uint8_t mode_6020;
double output[16] = {0};
int BrakeAng[4] = {0};
double mult = 1;
int dirflag=0;


void ctrlmotor(double Vx, double Vy, double omega,int flag) {
  MotorSignal[0].thetan = atan2(Vy, Vx + omega) * 180 / PI;
  MotorSignal[1].thetan = atan2(Vy - omega * cos(30.0 * PI / 180.0), Vx + omega * sin(30.0 * PI / 180.0)) * 180 / PI;
  MotorSignal[2].thetan = atan2(Vy + omega * cos(30.0 * PI / 180.0), Vx + omega * sin(30.0 * PI / 180.0)) * 180 / PI;
	for(int i=0;i<3;i++){
	if(fabs(MotorSignal[i].thetan-90)<1)
			MotorSignal[i].thetan=91;
	if(fabs(MotorSignal[i].thetan+90)<1)
			MotorSignal[i].thetan=-89;}
	
	for(int i=0;i<3;i++){
        cala_d(i);
		    MotorSignal[i].thetal=MotorSignal[i].thetan;
	 			if(fabs((double)((int)MotorSignal[i].thetas%360-90))<1)
	 				MotorSignal[i].thetas=90+(int)MotorSignal[i].thetas/360*360;
	 			if(fabs((double)((int)MotorSignal[i].thetas%360+90))<1)
	 				MotorSignal[i].thetas=-90+(int)MotorSignal[i].thetas/360*360;
	 			if(fabs((double)((int)MotorSignal[i].thetas%360-270))<1)
	 				MotorSignal[i].thetas=270+(int)MotorSignal[i].thetas/360*360;
	 			if(fabs((double)((int)MotorSignal[i].thetas%360+270))<1)
	 				MotorSignal[i].thetas=-270+(int)MotorSignal[i].thetas/360*360;
				
	 }

	 
	 	if(flag==0)
    {
			rtU.yaw_target_CH2_5 = MotorSignal[0].thetas*8191/(360);
			rtU.yaw_target_CH2_6 = MotorSignal[1].thetas*8191/(360);
			rtU.yaw_target_CH2_7 = MotorSignal[2].thetas*8191/(360);
	 		while( (fabs(sqrt(pow(Vx-omega,2)+pow(Vy,2))*mult)>MAXVEL)||
	 					(fabs(sqrt(pow((Vx+omega*sin(30.0*PI/180.0)),2)+pow((Vy-omega*cos(30.0*PI/180.0)),2))*mult)>MAXVEL)||
	 					(fabs(sqrt(pow((Vx+omega*sin(30.0*PI/180.0)),2)+pow((Vy+omega*cos(30.0*PI/180.0)),2))*mult)>MAXVEL))
	 		{
	 			mult=0.98*mult;
	 		}
	 		rtU.yaw_status_CH1_1=1;
	 		rtU.yaw_status_CH1_2=1;
	 		rtU.yaw_status_CH1_3=1;
	 		if(fabs(motor_data_can2[4]->ecd+motor_data_can2[4]->circle*8191-rtU.yaw_target_CH2_5)<45*8191/360&&
		 fabs(motor_data_can2[5]->ecd+motor_data_can2[5]->circle*8191-rtU.yaw_target_CH2_6)<45*8191/360&&
		 fabs(motor_data_can2[6]->ecd+motor_data_can2[6]->circle*8191-rtU.yaw_target_CH2_7)<45*8191/360
		 ||omega!=0){
				if(MotorSignal[0].dir==1)
					rtU.yaw_target_CH1_1= -sqrt(pow(Vx-omega,2)+pow(Vy,2))*mult;
				else
					rtU.yaw_target_CH1_1= sqrt(pow(Vx-omega,2)+pow(Vy,2))*mult;
		
				if(MotorSignal[1].dir==1)	
					rtU.yaw_target_CH1_2 =-sqrt(pow((Vx+omega*sin(30.0*PI/180.0)),2)+pow((Vy-omega*cos(30.0*PI/180.0)),2))*mult;
				else
					rtU.yaw_target_CH1_2 =sqrt(pow((Vx+omega*sin(30.0*PI/180.0)),2)+pow((Vy-omega*cos(30.0*PI/180.0)),2))*mult;
		
				if(MotorSignal[2].dir==1)
					rtU.yaw_target_CH1_3= -sqrt(pow((Vx+omega*sin(30.0*PI/180.0)),2)+pow((Vy+omega*cos(30.0*PI/180.0)),2))*mult;	
				else
					rtU.yaw_target_CH1_3= sqrt(pow((Vx+omega*sin(30.0*PI/180.0)),2)+pow((Vy+omega*cos(30.0*PI/180.0)),2))*mult;	
			}
	
	 	}
	 		else
	 		{
        rtU.yaw_target_CH1_1=0;
				rtU.yaw_target_CH1_2=0;
				rtU.yaw_target_CH1_3=0;//驻停必要操作
				rtU.yaw_target_CH2_5 =(((int)MotorSignal[0].thetas)/360)*360*8191/(360);
				rtU.yaw_target_CH2_6 =((((int)MotorSignal[0].thetas)/360)*360+120)*8191/(360);
	 		  rtU.yaw_target_CH2_7 =((((int)MotorSignal[0].thetas)/360)*360+60)*8191/(360);
	 		}
	
	 mult=1;
}

void cala_d(int i){
	
		if((MotorSignal[i].thetan>90)||(MotorSignal[i].thetan<-90))
				MotorSignal[i].dir=1;
			else
				MotorSignal[i].dir=0;
		if(MotorSignal[i].thetan<-90&&MotorSignal[i].thetan>-180)
		 {
			 MotorSignal[i].thetan=MotorSignal[i].thetan+180;

		 }
		 else if(MotorSignal[i].thetan<=180&&MotorSignal[i].thetan>90)
		 {
			 MotorSignal[i].thetan=MotorSignal[i].thetan-180;

		 }

		 MotorSignal[i].err=MotorSignal[i].thetan-MotorSignal[i].thetal;
		 
//		 if(i==0){
//		 if(MotorSignal[0].err>0&&fabs(motor_data_can2[4]->ecd+motor_data_can2[4]->circle*8191-rtU.yaw_target_CH2_5)>50)
//		 {
//				MotorSignal[0].err=MotorSignal[0].err+2.5;
//		 }else if(MotorSignal[0].err<0&&fabs(motor_data_can2[4]->ecd+motor_data_can2[4]->circle*8191-rtU.yaw_target_CH2_5)>50)
//		 {
//				MotorSignal[0].err=MotorSignal[0].err-2.5;
//		 }
//		}
//		 	if(i==1){
//		 if(MotorSignal[1].err>0&&fabs(motor_data_can2[5]->ecd+motor_data_can2[5]->circle*8191-rtU.yaw_target_CH2_6)>50)
//		 {
//				MotorSignal[1].err=MotorSignal[1].err+2.5;
//		 }else if(MotorSignal[1].err<0&&fabs(motor_data_can2[5]->ecd+motor_data_can2[5]->circle*8191-rtU.yaw_target_CH2_6)>50)
//		 {
//				MotorSignal[1].err=MotorSignal[1].err-2.5;
//		 }
//		}
//			if(i==2){
//		 if(MotorSignal[2].err>0&&fabs(motor_data_can2[6]->ecd+motor_data_can2[6]->circle*8191-rtU.yaw_target_CH2_7)>50)
//		 {
//				MotorSignal[2].err=MotorSignal[2].err+2.5;
//		 }else if(MotorSignal[2].err<0&&fabs(motor_data_can2[6]->ecd+motor_data_can2[6]->circle*8191-rtU.yaw_target_CH2_7)>50)
//		 {
//				MotorSignal[2].err=MotorSignal[2].err-2.5;
//		 }
//		}
//			
      if(MotorSignal[i].thetan-MotorSignal[i].thetal<0)
			{
				MotorSignal[i].err1=MotorSignal[i].err+180;
				MotorSignal[i].err2=MotorSignal[i].err;
				
			}
			else if(MotorSignal[i].thetal-MotorSignal[i].thetan<=0)
			{
				MotorSignal[i].err1=MotorSignal[i].err-180;
				MotorSignal[i].err2=MotorSignal[i].err;
				
			}
			if(fabs(MotorSignal[i].err1)>=fabs(MotorSignal[i].err2)){
				MotorSignal[i].err=MotorSignal[i].err2;
			}
			else{
				MotorSignal[i].err=MotorSignal[i].err1;
        MotorSignal[i].dir=1-MotorSignal[i].dir;
			}
			MotorSignal[i].thetas+=MotorSignal[i].err;

			if((((int)MotorSignal[i].thetas%360<=270&&(int)MotorSignal[i].thetas%360>=90)
      ||((int)MotorSignal[i].thetas%360<=-90&&(int)MotorSignal[i].thetas%360>=-270))){
					MotorSignal[i].dir=1-MotorSignal[i].dir;
				}


}


void get_msgn(void)
{
  rtU.yaw_speed_rpm_CH1_1 = motor_data_can1[0]->speed_rpm;
  rtU.yaw_ecd_CH1_1 = motor_data_can1[0]->ecd;
  rtU.yaw_last_ecd_CH1_1 = motor_data_can1[0]->last_ecd;
  rtU.yaw_circle_CH1_1 = motor_data_can1[0]->circle;

  rtU.yaw_speed_rpm_CH1_2 = motor_data_can1[1]->speed_rpm;
  rtU.yaw_ecd_CH1_2 = motor_data_can1[1]->ecd;
  rtU.yaw_last_ecd_CH1_2 = motor_data_can1[1]->last_ecd;
  rtU.yaw_circle_CH1_2 = motor_data_can1[1]->circle;

  rtU.yaw_speed_rpm_CH1_3 = motor_data_can1[2]->speed_rpm;
  rtU.yaw_ecd_CH1_3 = motor_data_can1[2]->ecd;
  rtU.yaw_last_ecd_CH1_3 = motor_data_can1[2]->last_ecd;
  rtU.yaw_circle_CH1_3 = motor_data_can1[2]->circle;

  rtU.yaw_speed_rpm_CH1_4 = motor_data_can1[3]->speed_rpm;
  rtU.yaw_ecd_CH1_4 = motor_data_can1[3]->ecd;
  rtU.yaw_last_ecd_CH1_4 = motor_data_can1[3]->last_ecd;
  rtU.yaw_circle_CH1_4 = motor_data_can1[3]->circle;

  rtU.yaw_speed_rpm_CH1_5 = motor_data_can1[4]->speed_rpm;
  rtU.yaw_ecd_CH1_5 = motor_data_can1[4]->ecd;
  rtU.yaw_last_ecd_CH1_5 = motor_data_can1[4]->last_ecd;
  rtU.yaw_circle_CH1_5 = motor_data_can1[4]->circle;

  rtU.yaw_speed_rpm_CH1_6 = motor_data_can1[5]->speed_rpm;
  rtU.yaw_ecd_CH1_6 = motor_data_can1[5]->ecd;
  rtU.yaw_last_ecd_CH1_6 = motor_data_can1[5]->last_ecd;
  rtU.yaw_circle_CH1_6 = motor_data_can1[5]->circle;

  rtU.yaw_speed_rpm_CH1_7 = motor_data_can1[6]->speed_rpm;
  rtU.yaw_ecd_CH1_7 = motor_data_can1[6]->ecd;
  rtU.yaw_last_ecd_CH1_7 = motor_data_can1[6]->last_ecd;
  rtU.yaw_circle_CH1_7 = motor_data_can1[6]->circle;

  rtU.yaw_speed_rpm_CH2_1 = motor_data_can2[0]->speed_rpm;
  rtU.yaw_ecd_CH2_1 = motor_data_can2[0]->ecd;
  rtU.yaw_last_ecd_CH2_1 = motor_data_can2[0]->last_ecd;
  rtU.yaw_circle_CH2_1 = motor_data_can2[0]->circle;

  rtU.yaw_speed_rpm_CH2_2 = motor_data_can2[1]->speed_rpm;
  rtU.yaw_ecd_CH2_2 = motor_data_can2[1]->ecd;
  rtU.yaw_last_ecd_CH2_2 = motor_data_can2[1]->last_ecd;
  rtU.yaw_circle_CH2_2 = motor_data_can2[1]->circle;

  rtU.yaw_speed_rpm_CH2_3 = motor_data_can2[2]->speed_rpm;
  rtU.yaw_ecd_CH2_3 = motor_data_can2[2]->ecd;
  rtU.yaw_last_ecd_CH2_3 = motor_data_can2[2]->last_ecd;
  rtU.yaw_circle_CH2_3 = motor_data_can2[2]->circle;

  rtU.yaw_speed_rpm_CH2_4 = motor_data_can2[3]->speed_rpm;
  rtU.yaw_ecd_CH2_4 = motor_data_can2[3]->ecd;
  rtU.yaw_last_ecd_CH2_4 = motor_data_can2[3]->last_ecd;
  rtU.yaw_circle_CH2_4 = motor_data_can2[3]->circle;

  rtU.yaw_speed_rpm_CH2_5 = motor_data_can2[4]->speed_rpm;
  rtU.yaw_ecd_CH2_5 = motor_data_can2[4]->ecd;
  rtU.yaw_last_ecd_CH2_5 = motor_data_can2[4]->last_ecd;
  rtU.yaw_circle_CH2_5 = motor_data_can2[4]->circle;

  rtU.yaw_speed_rpm_CH2_6 = motor_data_can2[5]->speed_rpm;
  rtU.yaw_ecd_CH2_6 = motor_data_can2[5]->ecd;
  rtU.yaw_last_ecd_CH2_6 = motor_data_can2[5]->last_ecd;
  rtU.yaw_circle_CH2_6 = motor_data_can2[5]->circle;

  rtU.yaw_speed_rpm_CH2_7 = motor_data_can2[6]->speed_rpm;
  rtU.yaw_ecd_CH2_7 = motor_data_can2[6]->ecd;
  rtU.yaw_last_ecd_CH2_7 = motor_data_can2[6]->last_ecd;
  rtU.yaw_circle_CH2_7 = motor_data_can2[6]->circle;
}

void assign_output(void)
{
  if (rtU.yaw_status_CH1_1 == 1)
    output[CH1_1] = rtY.yaw_SPD_OUT_CH1_1 + 100;
  else
    output[CH1_1] = rtY.yaw_ANG_OUT_CH1_1;

  if (rtU.yaw_status_CH1_2 == 1)
    output[CH1_2] = rtY.yaw_SPD_OUT_CH1_2 + 100;
  else
    output[CH1_2] = rtY.yaw_ANG_OUT_CH1_2;

  if (rtU.yaw_status_CH1_3 == 1)
    output[CH1_3] = rtY.yaw_SPD_OUT_CH1_3 + 100;
  else
    output[CH1_3] = rtY.yaw_ANG_OUT_CH1_3;

  if (rtU.yaw_status_CH1_4 == 1)
    output[CH1_4] = rtY.yaw_SPD_OUT_CH1_4 + 100;
  else
    output[CH1_4] = rtY.yaw_ANG_OUT_CH1_4;

  if (rtU.yaw_status_CH1_5 == 1)
    output[CH1_5] = rtY.yaw_SPD_OUT_CH1_5;
  else
    output[CH1_5] = rtY.yaw_ANG_OUT_CH1_5;

  if (rtU.yaw_status_CH1_6 == 1)
    output[CH1_6] = rtY.yaw_SPD_OUT_CH1_6;
  else
    output[CH1_6] = rtY.yaw_ANG_OUT_CH1_6;

  if (rtU.yaw_status_CH1_7 == 1)
    output[CH1_7] = rtY.yaw_SPD_OUT_CH1_7;
  else
    output[CH1_7] = rtY.yaw_ANG_OUT_CH1_7;

  if (rtU.yaw_status_CH2_1 == 1)
    output[CH2_1] = rtY.yaw_SPD_OUT_CH2_1;
  else
    output[CH2_1] = rtY.yaw_ANG_OUT_CH2_1;

  if (rtU.yaw_status_CH2_2 == 1)
    output[CH2_2] = rtY.yaw_SPD_OUT_CH2_2;
  else
    output[CH2_2] = rtY.yaw_ANG_OUT_CH2_2;

  if (rtU.yaw_status_CH2_3 == 1)
    output[CH2_3] = rtY.yaw_SPD_OUT_CH2_3;
  else
    output[CH2_3] = rtY.yaw_ANG_OUT_CH2_3;

  if (rtU.yaw_status_CH2_4 == 1)
    output[CH2_4] = rtY.yaw_SPD_OUT_CH2_4;
  else
    output[CH2_4] = rtY.yaw_ANG_OUT_CH2_4;

  if (rtU.yaw_status_CH2_5 == 1)
    output[CH2_5] = rtY.yaw_SPD_OUT_CH2_5;
  else
    output[CH2_5] = rtY.yaw_ANG_OUT_CH2_5;

  if (rtU.yaw_status_CH2_6 == 1)
    output[CH2_6] = rtY.yaw_SPD_OUT_CH2_6;
  else
    output[CH2_6] = rtY.yaw_ANG_OUT_CH2_6;

  if (rtU.yaw_status_CH2_7 == 1)
    output[CH2_7] = rtY.yaw_SPD_OUT_CH2_7;
  else
    output[CH2_7] = rtY.yaw_ANG_OUT_CH2_7;
	
	if((mode_6020 & 0b100)==0){
		CAN1_cmd_motor(output[CH1_1], output[CH1_2], output[CH1_3], output[CH1_4]);
		CAN1_cmd_motor_last(output[CH1_5], output[CH1_6], output[CH1_7], 0);
	}
		else{
//		CAN1_cmd_motor(output[CH1_1], output[CH1_2], output[CH1_3], output[CH1_4]);
		CAN1_cmd_motor6020(output[CH1_1], output[CH1_2], output[CH1_3], output[CH1_4], output[CH1_5], output[CH1_6], output[CH1_7]);
	}
	if((mode_6020 & 0b010)==0)
	{
		CAN2_cmd_motor(output[CH2_1], output[CH2_2], output[CH2_3], output[CH2_4]);
		CAN2_cmd_motor_last(output[CH2_5], output[CH2_6], output[CH2_7], 0);
	}
		else{
//		CAN2_cmd_motor(output[CH2_1], output[CH2_2], output[CH2_3], output[CH2_4]);
		CAN2_cmd_motor6020(output[CH2_1], output[CH2_2], output[CH2_3], output[CH2_4], output[CH2_5], output[CH2_6], output[CH2_7]);
		}
}
void set_mode(int mode_CH1_1, int mode_CH1_2, int mode_CH1_3, int mode_CH1_4, int mode_CH1_5, int mode_CH1_6, int mode_CH1_7,
              int mode_CH2_1, int mode_CH2_2, int mode_CH2_3, int mode_CH2_4, int mode_CH2_5, int mode_CH2_6, int mode_CH2_7)
{
  rtU.yaw_status_CH1_1 = mode_CH1_1;
  rtU.yaw_status_CH1_2 = mode_CH1_2;
  rtU.yaw_status_CH1_3 = mode_CH1_3;
  rtU.yaw_status_CH1_4 = mode_CH1_4;
  rtU.yaw_status_CH1_5 = mode_CH1_5;
  rtU.yaw_status_CH1_6 = mode_CH1_6;
  rtU.yaw_status_CH1_7 = mode_CH1_7;

  rtU.yaw_status_CH2_1 = mode_CH2_1;
  rtU.yaw_status_CH2_2 = mode_CH2_2;
  rtU.yaw_status_CH2_3 = mode_CH2_3;
  rtU.yaw_status_CH2_4 = mode_CH2_4;
  rtU.yaw_status_CH2_5 = mode_CH2_5;
  rtU.yaw_status_CH2_6 = mode_CH2_6;
  rtU.yaw_status_CH2_7 = mode_CH2_7;
}
void PID_Speed_Para_Init(int channel, int motor, double kp, double ki, double kd)
{
  switch (channel)
  {
  case 1:
    switch (motor)
    {
    case 1:
      rtP.SPD_D_CH1_1 = kd;
      rtP.SPD_I_CH1_1 = ki;
      rtP.SPD_P_CH1_1 = kp;
      break;
    case 2:
      rtP.SPD_D_CH1_2 = kd;
      rtP.SPD_I_CH1_2 = ki;
      rtP.SPD_P_CH1_2 = kp;
      break;
    case 3:
      rtP.SPD_D_CH1_3 = kd;
      rtP.SPD_I_CH1_3 = ki;
      rtP.SPD_P_CH1_3 = kp;
      break;
    case 4:
      rtP.SPD_D_CH1_4 = kd;
      rtP.SPD_I_CH1_4 = ki;
      rtP.SPD_P_CH1_4 = kp;
      break;
    case 5:
      rtP.SPD_D_CH1_5 = kd;
      rtP.SPD_I_CH1_5 = ki;
      rtP.SPD_P_CH1_5 = kp;
      break;
    case 6:
      rtP.SPD_D_CH1_6 = kd;
      rtP.SPD_I_CH1_6 = ki;
      rtP.SPD_P_CH1_6 = kp;
      break;
    case 7:
      rtP.SPD_D_CH1_7 = kd;
      rtP.SPD_I_CH1_7 = ki;
      rtP.SPD_P_CH1_7 = kp;
      break;
    }
    break;
  case 2:
    switch (motor)
    {
    case 1:
      rtP.SPD_D_CH2_1 = kd;
      rtP.SPD_I_CH2_1 = ki;
      rtP.SPD_P_CH2_1 = kp;
      break;
    case 2:
      rtP.SPD_D_CH2_2 = kd;
      rtP.SPD_I_CH2_2 = ki;
      rtP.SPD_P_CH2_2 = kp;
      break;
    case 3:
      rtP.SPD_D_CH2_3 = kd;
      rtP.SPD_I_CH2_3 = ki;
      rtP.SPD_P_CH2_3 = kp;
      break;
    case 4:
      rtP.SPD_D_CH2_4 = kd;
      rtP.SPD_I_CH2_4 = ki;
      rtP.SPD_P_CH2_4 = kp;
      break;
    case 5:
      rtP.SPD_D_CH2_5 = kd;
      rtP.SPD_I_CH2_5 = ki;
      rtP.SPD_P_CH2_5 = kp;
      break;
    case 6:
      rtP.SPD_D_CH2_6 = kd;
      rtP.SPD_I_CH2_6 = ki;
      rtP.SPD_P_CH2_6 = kp;
      break;
    case 7:
      rtP.SPD_D_CH2_7 = kd;
      rtP.SPD_I_CH2_7 = ki;
      rtP.SPD_P_CH2_7 = kp;
      break;
    }
    break;
  }
}

void PID_Angle_S_Para_Init(int channel, int motor, double kp, double ki, double kd)
{
  switch (channel)
  {
  case 1:
    switch (motor)
    {
    case 1:
      rtP.ANG_S_P_CH1_1 = kp;
      rtP.ANG_S_I_CH1_1 = ki;
      rtP.ANG_S_D_CH1_1 = kd;
      break;
    case 2:
      rtP.ANG_S_P_CH1_2 = kp;
      rtP.ANG_S_I_CH1_2 = ki;
      rtP.ANG_S_D_CH1_2 = kd;
      break;
    case 3:
      rtP.ANG_S_P_CH1_3 = kp;
      rtP.ANG_S_I_CH1_3 = ki;
      rtP.ANG_S_D_CH1_3 = kd;
      break;
    case 4:
      rtP.ANG_S_P_CH1_4 = kp;
      rtP.ANG_S_I_CH1_4 = ki;
      rtP.ANG_S_D_CH1_4 = kd;
      break;
    case 5:
      rtP.ANG_S_P_CH1_5 = kp;
      rtP.ANG_S_I_CH1_5 = ki;
      rtP.ANG_S_D_CH1_5 = kd;
      break;
    case 6:
      rtP.ANG_S_P_CH1_6 = kp;
      rtP.ANG_S_I_CH1_6 = ki;
      rtP.ANG_S_D_CH1_6 = kd;
      break;
    case 7:
      rtP.ANG_S_P_CH1_7 = kp;
      rtP.ANG_S_I_CH1_7 = ki;
      rtP.ANG_S_D_CH1_7 = kd;
      break;
    }
    break;
  case 2:
    switch (motor)
    {
    case 1:
      rtP.ANG_S_P_CH2_1 = kp;
      rtP.ANG_S_I_CH2_1 = ki;
      rtP.ANG_S_D_CH2_1 = kd;
      break;
    case 2:
      rtP.ANG_S_P_CH2_2 = kp;
      rtP.ANG_S_I_CH2_2 = ki;
      rtP.ANG_S_D_CH2_2 = kd;
      break;
    case 3:
      rtP.ANG_S_P_CH2_3 = kp;
      rtP.ANG_S_I_CH2_3 = ki;
      rtP.ANG_S_D_CH2_3 = kd;
      break;
    case 4:
      rtP.ANG_S_P_CH2_4 = kp;
      rtP.ANG_S_I_CH2_4 = ki;
      rtP.ANG_S_D_CH2_4 = kd;
      break;
    case 5:
      rtP.ANG_S_P_CH2_5 = kp;
      rtP.ANG_S_I_CH2_5 = ki;
      rtP.ANG_S_D_CH2_5 = kd;
      break;
    case 6:
      rtP.ANG_S_P_CH2_6 = kp;
      rtP.ANG_S_I_CH2_6 = ki;
      rtP.ANG_S_D_CH2_6 = kd;
      break;
    case 7:
      rtP.ANG_S_P_CH2_7 = kp;
      rtP.ANG_S_I_CH2_7 = ki;
      rtP.ANG_S_D_CH2_7 = kd;
      break;
    }
    break;
  }
}

void PID_Angle_A_Para_Init(int channel, int motor, double kp, double ki, double kd)
{
  switch (channel)
  {
  case 1:
    switch (motor)
    {
    case 1:
      rtP.ANG_A_P_CH1_1 = kp;
      rtP.ANG_A_I_CH1_1 = ki;
      rtP.ANG_A_D_CH1_1 = kd;
      break;
    case 2:
      rtP.ANG_A_P_CH1_2 = kp;
      rtP.ANG_A_I_CH1_2 = ki;
      rtP.ANG_A_D_CH1_2 = kd;
      break;
    case 3:
      rtP.ANG_A_P_CH1_3 = kp;
      rtP.ANG_A_I_CH1_3 = ki;
      rtP.ANG_A_D_CH1_3 = kd;
      break;
    case 4:
      rtP.ANG_A_P_CH1_4 = kp;
      rtP.ANG_A_I_CH1_4 = ki;
      rtP.ANG_A_D_CH1_4 = kd;
      break;
    case 5:
      rtP.ANG_A_P_CH1_5 = kp;
      rtP.ANG_A_I_CH1_5 = ki;
      rtP.ANG_A_D_CH1_5 = kd;
      break;
    case 6:
      rtP.ANG_A_P_CH1_6 = kp;
      rtP.ANG_A_I_CH1_6 = ki;
      rtP.ANG_A_D_CH1_6 = kd;
      break;
    case 7:
      rtP.ANG_A_P_CH1_7 = kp;
      rtP.ANG_A_I_CH1_7 = ki;
      rtP.ANG_A_D_CH1_7 = kd;
      break;
    }
    break;
  case 2:
    switch (motor)
    {
    case 1:
      rtP.ANG_A_P_CH2_1 = kp;
      rtP.ANG_A_I_CH2_1 = ki;
      rtP.ANG_A_D_CH2_1 = kd;
      break;
    case 2:
      rtP.ANG_A_P_CH2_2 = kp;
      rtP.ANG_A_I_CH2_2 = ki;
      rtP.ANG_A_D_CH2_2 = kd;
      break;
    case 3:
      rtP.ANG_A_P_CH2_3 = kp;
      rtP.ANG_A_I_CH2_3 = ki;
      rtP.ANG_A_D_CH2_3 = kd;
      break;
    case 4:
      rtP.ANG_A_P_CH2_4 = kp;
      rtP.ANG_A_I_CH2_4 = ki;
      rtP.ANG_A_D_CH2_4 = kd;
      break;
    case 5:
      rtP.ANG_A_P_CH2_5 = kp;
      rtP.ANG_A_I_CH2_5 = ki;
      rtP.ANG_A_D_CH2_5 = kd;
      break;
    case 6:
      rtP.ANG_A_P_CH2_6 = kp;
      rtP.ANG_A_I_CH2_6 = ki;
      rtP.ANG_A_D_CH2_6 = kd;
      break;
    case 7:
      rtP.ANG_A_P_CH2_7 = kp;
      rtP.ANG_A_I_CH2_7 = ki;
      rtP.ANG_A_D_CH2_7 = kd;
      break;
    }
    break;
  }
}
