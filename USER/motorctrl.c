#include "motorctrl.h"
#include "UPPER_LOCATION.h"


#define PI 3.1415926
#define MAXVEL 4000
ang_dir MotorSignal[3];
extern FDCAN_HandleTypeDef hfdcan1; // CAN����1
extern FDCAN_HandleTypeDef hfdcan2;
extern motor_measure_t *motor_data_can1[8];
extern motor_measure_t *motor_data_can2[8];
extern motor_measure_t *motor_data_can3[8];

extern uint8_t mode_6020;
double tor_output[3*8] = {0};
int BrakeAng[4] = {0};
double mult = 1;
int dirflag=0;


void ctrlmotor(double Vx, double Vy, double omega,int brake) {
	if(fabs(Vx)<40)
		Vx=0;
	if(fabs(Vy)<40)
		Vy=0;
	if(fabs(omega)<40)
		omega=0;
	if(brake==1)
	{
		rtU.target_CH2_1=0;
		rtU.target_CH2_2=0;
		rtU.target_CH2_3=0;//驻停必要操作
		set_target(2,5,(-((int)(MotorSignal[0].thetas)/360)*360)*8191/(360)-90*8191/360+5771);
		set_target(2,6,(-((int)(MotorSignal[0].thetas)/360)*360)*8191/(360)-60*8191/360+2346);
		set_target(2,7,(-((int)(MotorSignal[0].thetas)/360)*360)*8191/(360)+60*8191/360+3057);
		return;
	}
	if(Vx==0&&Vy==0&&omega==0){
		set_target(2,1,0);
		set_target(2,2,0);
		set_target(2,3,0);
		return;
	}

	Vx=5000/400*Vx;
	Vy=5000/400*Vy;
	omega=5000/400*omega;
  MotorSignal[0].thetan = atan2(Vy, Vx - omega) * 180 / PI;
  MotorSignal[1].thetan = atan2(Vy - omega * cos(30.0 * PI / 180.0), Vx + omega * sin(30.0 * PI / 180.0)) * 180 / PI;
  MotorSignal[2].thetan = atan2(Vy + omega * cos(30.0 * PI / 180.0), Vx + omega * sin(30.0 * PI / 180.0)) * 180 / PI;
	for(int i=0;i<3;i++){
	if(fabs(MotorSignal[i].thetan-90)<1)
			MotorSignal[i].thetan=90;
	if(fabs(MotorSignal[i].thetan+90)<1)
			MotorSignal[i].thetan=-90;
	}
	
	for(int i=0;i<3;i++){
      cala_d(i);
		  MotorSignal[i].thetal=MotorSignal[i].thetan;				
	 }
	set_target(2,5,-MotorSignal[0].thetas*8191/(360)+5771);
	set_target(2,6,-MotorSignal[1].thetas*8191/(360)+2346);
	set_target(2,7,-MotorSignal[2].thetas*8191/(360)+3097);
	 while( (fabs(sqrt(pow(Vx-omega,2)+pow(Vy,2))*mult)>MAXVEL)||
	 			(fabs(sqrt(pow((Vx+omega*sin(30.0*PI/180.0)),2)+pow((Vy-omega*cos(30.0*PI/180.0)),2))*mult)>MAXVEL)||
	 			(fabs(sqrt(pow((Vx+omega*sin(30.0*PI/180.0)),2)+pow((Vy+omega*cos(30.0*PI/180.0)),2))*mult)>MAXVEL))
	 {
	 	mult=0.98*mult;
	 }
	 rtU.status_CH1_1=1;
	 rtU.status_CH1_2=1;
	 rtU.status_CH1_3=1;
	 if((fabs(motor_data_can2[4]->ecd+motor_data_can2[4]->circle*8191-rtU.target_CH2_5)<45*8191/360&&
		 fabs(motor_data_can2[5]->ecd+motor_data_can2[5]->circle*8191-rtU.target_CH2_6)<45*8191/360&&
		 fabs(motor_data_can2[6]->ecd+motor_data_can2[6]->circle*8191-rtU.target_CH2_7)<45*8191/360)
		 ||omega!=0){
				if(MotorSignal[0].dir==1)
					set_target(2,1,-sqrt(pow(Vx-omega,2)+pow(Vy,2))*mult);
				else
					set_target(2,1,sqrt(pow(Vx-omega,2)+pow(Vy,2))*mult);
		
				if(MotorSignal[1].dir==1)	
					set_target(2,2,-sqrt(pow((Vx+omega*sin(30.0*PI/180.0)),2)+pow((Vy-omega*cos(30.0*PI/180.0)),2))*mult);
				else
					set_target(2,2,sqrt(pow((Vx+omega*sin(30.0*PI/180.0)),2)+pow((Vy-omega*cos(30.0*PI/180.0)),2))*mult);
		
				if(MotorSignal[2].dir==1)
					set_target(2,3,-sqrt(pow((Vx+omega*sin(30.0*PI/180.0)),2)+pow((Vy+omega*cos(30.0*PI/180.0)),2))*mult);	
				else
					set_target(2,3,sqrt(pow((Vx+omega*sin(30.0*PI/180.0)),2)+pow((Vy+omega*cos(30.0*PI/180.0)),2))*mult);	
	
	 	}

	
	 mult=1;
}

void cala_d(int i){
		//second & third quadrants,set direction and target theta		
	if(MotorSignal[i].thetan<-90)
	{
			  MotorSignal[i].thetan=MotorSignal[i].thetan+180;
				MotorSignal[i].dir=1;
	}
	else if(MotorSignal[i].thetan>90)
	{
			 MotorSignal[i].thetan=MotorSignal[i].thetan-180;
			 MotorSignal[i].dir=1;
	}			
	else
				MotorSignal[i].dir=0;

	MotorSignal[i].err=MotorSignal[i].thetan-MotorSignal[i].thetal;
			
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
	//if rotate in reverse to the target angle, reverse the direction
	if(fabs(MotorSignal[i].err1)>=fabs(MotorSignal[i].err2)){
		MotorSignal[i].err=MotorSignal[i].err2;
	}
	else{
		MotorSignal[i].err=MotorSignal[i].err1;
	}
	MotorSignal[i].thetas+=MotorSignal[i].err;
	//thetas on the left half plane means we should have an reverse direction 
			MotorSignal[i].thetan_cal=fabs(fabs((int)MotorSignal[i].thetas%360-MotorSignal[i].thetan)-180);
		MotorSignal[i].thetan_cal_last=fabs(fabs((int)MotorSignal[i].thetas%360-MotorSignal[i].thetan)+180);
	if((fabs(fabs((int)MotorSignal[i].thetas%360-MotorSignal[i].thetan)-180)<=1)||
		fabs(fabs((int)MotorSignal[i].thetas%360-MotorSignal[i].thetan)+180)<=1)
	{

		MotorSignal[i].dir=1-MotorSignal[i].dir;
	}
		


}


void get_msgn(void)
{
  rtU.speed_rpm_CH1_1 = motor_data_can1[0]->speed_rpm;
  rtU.ecd_CH1_1 = motor_data_can1[0]->ecd;
  rtU.last_ecd_CH1_1 = motor_data_can1[0]->last_ecd;
  rtU.circle_CH1_1 = motor_data_can1[0]->circle;

  rtU.speed_rpm_CH1_2 = motor_data_can1[1]->speed_rpm;
  rtU.ecd_CH1_2 = motor_data_can1[1]->ecd;
  rtU.last_ecd_CH1_2 = motor_data_can1[1]->last_ecd;
  rtU.circle_CH1_2 = motor_data_can1[1]->circle;

  rtU.speed_rpm_CH1_3 = motor_data_can1[2]->speed_rpm;
  rtU.ecd_CH1_3 = motor_data_can1[2]->ecd;
  rtU.last_ecd_CH1_3 = motor_data_can1[2]->last_ecd;
  rtU.circle_CH1_3 = motor_data_can1[2]->circle;

  rtU.speed_rpm_CH1_4 = motor_data_can1[3]->speed_rpm;
  rtU.ecd_CH1_4 = motor_data_can1[3]->ecd;
  rtU.last_ecd_CH1_4 = motor_data_can1[3]->last_ecd;
  rtU.circle_CH1_4 = motor_data_can1[3]->circle;

  rtU.speed_rpm_CH1_5 = motor_data_can1[4]->speed_rpm;
  rtU.ecd_CH1_5 = motor_data_can1[4]->ecd;
  rtU.last_ecd_CH1_5 = motor_data_can1[4]->last_ecd;
  rtU.circle_CH1_5 = motor_data_can1[4]->circle;

  rtU.speed_rpm_CH1_6 = motor_data_can1[5]->speed_rpm;
  rtU.ecd_CH1_6 = motor_data_can1[5]->ecd;
  rtU.last_ecd_CH1_6 = motor_data_can1[5]->last_ecd;
  rtU.circle_CH1_6 = motor_data_can1[5]->circle;

  rtU.speed_rpm_CH1_7 = motor_data_can1[6]->speed_rpm;
  rtU.ecd_CH1_7 = motor_data_can1[6]->ecd;
  rtU.last_ecd_CH1_7 = motor_data_can1[6]->last_ecd;
  rtU.circle_CH1_7 = motor_data_can1[6]->circle;

  rtU.speed_rpm_CH2_1 = motor_data_can2[0]->speed_rpm;
  rtU.ecd_CH2_1 = motor_data_can2[0]->ecd;
  rtU.last_ecd_CH2_1 = motor_data_can2[0]->last_ecd;
  rtU.circle_CH2_1 = motor_data_can2[0]->circle;

  rtU.speed_rpm_CH2_2 = motor_data_can2[1]->speed_rpm;
  rtU.ecd_CH2_2 = motor_data_can2[1]->ecd;
  rtU.last_ecd_CH2_2 = motor_data_can2[1]->last_ecd;
  rtU.circle_CH2_2 = motor_data_can2[1]->circle;

  rtU.speed_rpm_CH2_3 = motor_data_can2[2]->speed_rpm;
  rtU.ecd_CH2_3 = motor_data_can2[2]->ecd;
  rtU.last_ecd_CH2_3 = motor_data_can2[2]->last_ecd;
  rtU.circle_CH2_3 = motor_data_can2[2]->circle;

  rtU.speed_rpm_CH2_4 = motor_data_can2[3]->speed_rpm;
  rtU.ecd_CH2_4 = motor_data_can2[3]->ecd;
  rtU.last_ecd_CH2_4 = motor_data_can2[3]->last_ecd;
  rtU.circle_CH2_4 = motor_data_can2[3]->circle;

  rtU.speed_rpm_CH2_5 = motor_data_can2[4]->speed_rpm;
  rtU.ecd_CH2_5 = motor_data_can2[4]->ecd;
  rtU.last_ecd_CH2_5 = motor_data_can2[4]->last_ecd;
  rtU.circle_CH2_5 = motor_data_can2[4]->circle;

  rtU.speed_rpm_CH2_6 = motor_data_can2[5]->speed_rpm;
  rtU.ecd_CH2_6 = motor_data_can2[5]->ecd;
  rtU.last_ecd_CH2_6 = motor_data_can2[5]->last_ecd;
  rtU.circle_CH2_6 = motor_data_can2[5]->circle;

  rtU.speed_rpm_CH2_7 = motor_data_can2[6]->speed_rpm;
  rtU.ecd_CH2_7 = motor_data_can2[6]->ecd;
  rtU.last_ecd_CH2_7 = motor_data_can2[6]->last_ecd;
  rtU.circle_CH2_7 = motor_data_can2[6]->circle;
	
	  rtU.speed_rpm_CH3_1 = motor_data_can3[0]->speed_rpm;
  rtU.ecd_CH3_1 = motor_data_can3[0]->ecd;
  rtU.last_ecd_CH3_1 = motor_data_can3[0]->last_ecd;
  rtU.circle_CH3_1 = motor_data_can3[0]->circle;

  rtU.speed_rpm_CH3_2 = motor_data_can3[1]->speed_rpm;
  rtU.ecd_CH3_2 = motor_data_can3[1]->ecd;
  rtU.last_ecd_CH3_2 = motor_data_can3[1]->last_ecd;
  rtU.circle_CH3_2 = motor_data_can3[1]->circle;

  rtU.speed_rpm_CH3_3 = motor_data_can3[2]->speed_rpm;
  rtU.ecd_CH3_3 = motor_data_can3[2]->ecd;
  rtU.last_ecd_CH3_3 = motor_data_can3[2]->last_ecd;
  rtU.circle_CH3_3 = motor_data_can3[2]->circle;

  rtU.speed_rpm_CH3_4 = motor_data_can3[3]->speed_rpm;
  rtU.ecd_CH3_4 = motor_data_can3[3]->ecd;
  rtU.last_ecd_CH3_4 = motor_data_can3[3]->last_ecd;
  rtU.circle_CH3_4 = motor_data_can3[3]->circle;

  rtU.speed_rpm_CH3_5 = motor_data_can3[4]->speed_rpm;
  rtU.ecd_CH3_5 = motor_data_can3[4]->ecd;
  rtU.last_ecd_CH3_5 = motor_data_can3[4]->last_ecd;
  rtU.circle_CH3_5 = motor_data_can3[4]->circle;

  rtU.speed_rpm_CH3_6 = motor_data_can3[5]->speed_rpm;
  rtU.ecd_CH3_6 = motor_data_can3[5]->ecd;
  rtU.last_ecd_CH3_6 = motor_data_can3[5]->last_ecd;
  rtU.circle_CH3_6 = motor_data_can3[5]->circle;

  rtU.speed_rpm_CH3_7 = motor_data_can3[6]->speed_rpm;
  rtU.ecd_CH3_7 = motor_data_can3[6]->ecd;
  rtU.last_ecd_CH3_7 = motor_data_can3[6]->last_ecd;
  rtU.circle_CH3_7 = motor_data_can3[6]->circle;
}

void assign_output(void)
{
  if (rtU.status_CH1_1 == 1)
    tor_output[CH1_1] = rtY.SPD_OUT_CH1_1;
  else
    tor_output[CH1_1] = rtY.ANG_OUT_CH1_1;

  if (rtU.status_CH1_2 == 1)
    tor_output[CH1_2] = rtY.SPD_OUT_CH1_2;
  else
    tor_output[CH1_2] = rtY.ANG_OUT_CH1_2;

  if (rtU.status_CH1_3 == 1)
    tor_output[CH1_3] = rtY.SPD_OUT_CH1_3;
  else
    tor_output[CH1_3] = rtY.ANG_OUT_CH1_3;

  if (rtU.status_CH1_4 == 1)
    tor_output[CH1_4] = rtY.SPD_OUT_CH1_4;
  else
    tor_output[CH1_4] = rtY.ANG_OUT_CH1_4;

  if (rtU.status_CH1_5 == 1)
    tor_output[CH1_5] = rtY.SPD_OUT_CH1_5;
  else
    tor_output[CH1_5] = rtY.ANG_OUT_CH1_5;

  if (rtU.status_CH1_6 == 1)
    tor_output[CH1_6] = rtY.SPD_OUT_CH1_6;
  else
    tor_output[CH1_6] = rtY.ANG_OUT_CH1_6;

  if (rtU.status_CH1_7 == 1)
    tor_output[CH1_7] = rtY.SPD_OUT_CH1_7;
  else
    tor_output[CH1_7] = rtY.ANG_OUT_CH1_7;

  if (rtU.status_CH2_1 == 1)
    tor_output[CH2_1] = rtY.SPD_OUT_CH2_1;
  else
    tor_output[CH2_1] = rtY.ANG_OUT_CH2_1;

  if (rtU.status_CH2_2 == 1)
    tor_output[CH2_2] = rtY.SPD_OUT_CH2_2;
  else
    tor_output[CH2_2] = rtY.ANG_OUT_CH2_2;

  if (rtU.status_CH2_3 == 1)
    tor_output[CH2_3] = rtY.SPD_OUT_CH2_3;
  else
    tor_output[CH2_3] = rtY.ANG_OUT_CH2_3;

  if (rtU.status_CH2_4 == 1)
    tor_output[CH2_4] = rtY.SPD_OUT_CH2_4;
  else
    tor_output[CH2_4] = rtY.ANG_OUT_CH2_4;

  if (rtU.status_CH2_5 == 1)
    tor_output[CH2_5] = rtY.SPD_OUT_CH2_5;
  else
    tor_output[CH2_5] = rtY.ANG_OUT_CH2_5;

  if (rtU.status_CH2_6 == 1)
    tor_output[CH2_6] = rtY.SPD_OUT_CH2_6;
  else
    tor_output[CH2_6] = rtY.ANG_OUT_CH2_6;

  if (rtU.status_CH2_7 == 1)
    tor_output[CH2_7] = rtY.SPD_OUT_CH2_7;
  else
    tor_output[CH2_7] = rtY.ANG_OUT_CH2_7;
	
	  if (rtU.status_CH3_1 == 1)
    tor_output[CH3_1] = rtY.SPD_OUT_CH3_1;
  else
    tor_output[CH3_1] = rtY.ANG_OUT_CH3_1;

  if (rtU.status_CH3_2 == 1)
    tor_output[CH3_2] = rtY.SPD_OUT_CH3_2;
  else
    tor_output[CH3_2] = rtY.ANG_OUT_CH3_2;

  if (rtU.status_CH3_3 == 1)
    tor_output[CH3_3] = rtY.SPD_OUT_CH3_3;
  else
    tor_output[CH3_3] = rtY.ANG_OUT_CH3_3;

  if (rtU.status_CH3_4 == 1)
    tor_output[CH3_4] = rtY.SPD_OUT_CH3_4;
  else
    tor_output[CH3_4] = rtY.ANG_OUT_CH3_4;

  if (rtU.status_CH3_5 == 1)
    tor_output[CH3_5] = rtY.SPD_OUT_CH3_5;
  else
    tor_output[CH3_5] = rtY.ANG_OUT_CH3_5;

  if (rtU.status_CH3_6 == 1)
    tor_output[CH3_6] = rtY.SPD_OUT_CH3_6;
  else
    tor_output[CH3_6] = rtY.ANG_OUT_CH3_6;

  if (rtU.status_CH3_7 == 1)
    tor_output[CH3_7] = rtY.SPD_OUT_CH3_7;
  else
    tor_output[CH3_7] = rtY.ANG_OUT_CH3_7;
	

		CAN_CMD_MOTOR_DJI(&hfdcan1,tor_output[CH1_1], tor_output[CH1_2], tor_output[CH1_3], tor_output[CH1_4],FRONT);
		CAN_CMD_MOTOR_DJI(&hfdcan1,tor_output[CH1_5], tor_output[CH1_6], tor_output[CH1_7], 0,LAST);

		CAN_CMD_MOTOR_DJI(&hfdcan2,tor_output[CH2_1], tor_output[CH2_2], tor_output[CH2_3], tor_output[CH2_4],FRONT);
		CAN_CMD_MOTOR_DJI(&hfdcan2,tor_output[CH2_5], tor_output[CH2_6], tor_output[CH2_7], 0,LAST);
	
		CAN_CMD_MOTOR_DJI(&hfdcan3,tor_output[CH3_1], tor_output[CH3_2], tor_output[CH3_3], tor_output[CH3_4],FRONT);
		CAN_CMD_MOTOR_DJI(&hfdcan3,tor_output[CH3_5], tor_output[CH3_6], tor_output[CH3_7], 0,LAST);
}
void set_mode(int mode_CH1_1, int mode_CH1_2, int mode_CH1_3, int mode_CH1_4, int mode_CH1_5, int mode_CH1_6, int mode_CH1_7,
              int mode_CH2_1, int mode_CH2_2, int mode_CH2_3, int mode_CH2_4, int mode_CH2_5, int mode_CH2_6, int mode_CH2_7,
							int mode_CH3_1, int mode_CH3_2, int mode_CH3_3, int mode_CH3_4, int mode_CH3_5, int mode_CH3_6, int mode_CH3_7)
{
  rtU.status_CH1_1 = mode_CH1_1;
  rtU.status_CH1_2 = mode_CH1_2;
  rtU.status_CH1_3 = mode_CH1_3;
  rtU.status_CH1_4 = mode_CH1_4;
  rtU.status_CH1_5 = mode_CH1_5;
  rtU.status_CH1_6 = mode_CH1_6;
  rtU.status_CH1_7 = mode_CH1_7;

  rtU.status_CH2_1 = mode_CH2_1;
  rtU.status_CH2_2 = mode_CH2_2;
  rtU.status_CH2_3 = mode_CH2_3;
  rtU.status_CH2_4 = mode_CH2_4;
  rtU.status_CH2_5 = mode_CH2_5;
  rtU.status_CH2_6 = mode_CH2_6;
  rtU.status_CH2_7 = mode_CH2_7;
	
	rtU.status_CH3_1 = mode_CH3_1;
  rtU.status_CH3_2 = mode_CH3_2;
  rtU.status_CH3_3 = mode_CH3_3;
  rtU.status_CH3_4 = mode_CH3_4;
  rtU.status_CH3_5 = mode_CH3_5;
  rtU.status_CH3_6 = mode_CH3_6;
  rtU.status_CH3_7 = mode_CH3_7;
}

void set_reset_status(){	
	if((fabs(rtU.target_CH1_1-motor_data_can1[0]->speed_rpm)<200&&rtU.status_CH1_1==1)||
		(fabs(rtU.target_CH1_1-motor_data_can1[0]->circle*8191-motor_data_can1[0]->ecd)<500&&rtU.status_CH1_1==2))
		rtU.reset_status1_1=1-rtU.reset_status1_1;
	
	if((fabs(rtU.target_CH1_2-motor_data_can1[1]->speed_rpm)<200&&rtU.status_CH1_2==1)||
		(fabs(rtU.target_CH1_2-motor_data_can1[1]->circle*8191-motor_data_can1[1]->ecd)<500&&rtU.status_CH1_2==2))
		rtU.reset_status1_2=1-rtU.reset_status1_2;
	
	if((fabs(rtU.target_CH1_3-motor_data_can1[2]->speed_rpm)<200&&rtU.status_CH1_3==1)||
		(fabs(rtU.target_CH1_3-motor_data_can1[2]->circle*8191-motor_data_can1[2]->ecd)<500&&rtU.status_CH1_3==2))
		rtU.reset_status1_3=1-rtU.reset_status1_3;
	
	if((fabs(rtU.target_CH1_4-motor_data_can1[3]->speed_rpm)<200&&rtU.status_CH1_4==1)||
		(fabs(rtU.target_CH1_4-motor_data_can1[3]->circle*8191-motor_data_can1[3]->ecd)<500&&rtU.status_CH1_4==2))
		rtU.reset_status1_4=1-rtU.reset_status1_4;
	
	if((fabs(rtU.target_CH1_5-motor_data_can1[4]->speed_rpm)<200&&rtU.status_CH1_5==1)||
		(fabs(rtU.target_CH1_5-motor_data_can1[4]->circle*8191-motor_data_can1[4]->ecd)<500&&rtU.status_CH1_5==2))
		rtU.reset_status1_5=1-rtU.reset_status1_5;
	
	if((fabs(rtU.target_CH1_6-motor_data_can1[5]->speed_rpm)<200&&rtU.status_CH1_6==1)||
		(fabs(rtU.target_CH1_6-motor_data_can1[5]->circle*8191-motor_data_can1[5]->ecd)<500&&rtU.status_CH1_6==2))
		rtU.reset_status1_6=1-rtU.reset_status1_6;
	
	if((fabs(rtU.target_CH1_7-motor_data_can1[6]->speed_rpm)<200&&rtU.status_CH1_7==1)||
		(fabs(rtU.target_CH1_7-motor_data_can1[6]->circle*8191-motor_data_can1[6]->ecd)<500&&rtU.status_CH1_7==2))
		rtU.reset_status1_7=1-rtU.reset_status1_7;
	
							
							
	if((fabs(rtU.target_CH2_1-motor_data_can2[0]->speed_rpm)<200&&rtU.status_CH2_1==1)||
		(fabs(rtU.target_CH2_1-motor_data_can2[0]->circle*8191-motor_data_can2[0]->ecd)<500&&rtU.status_CH2_1==2))
		rtU.reset_status2_1=1-rtU.reset_status2_1;
	
	if((fabs(rtU.target_CH2_2-motor_data_can2[1]->speed_rpm)<200&&rtU.status_CH2_2==1)||
		(fabs(rtU.target_CH2_2-motor_data_can2[1]->circle*8191-motor_data_can2[1]->ecd)<500&&rtU.status_CH2_2==2))
		rtU.reset_status2_2=1-rtU.reset_status2_2;
	
	if((fabs(rtU.target_CH2_3-motor_data_can2[2]->speed_rpm)<200&&rtU.status_CH2_3==1)||
		(fabs(rtU.target_CH2_3-motor_data_can2[2]->circle*8191-motor_data_can2[2]->ecd)<500&&rtU.status_CH2_3==2))
		rtU.reset_status2_3=1-rtU.reset_status2_3;
	
	if((fabs(rtU.target_CH2_4-motor_data_can2[3]->speed_rpm)<200&&rtU.status_CH2_4==1)||
		(fabs(rtU.target_CH2_4-motor_data_can2[3]->circle*8191-motor_data_can2[3]->ecd)<500&&rtU.status_CH2_4==2))
		rtU.reset_status2_4=1-rtU.reset_status2_4;
	
	if((fabs(rtU.target_CH2_5-motor_data_can2[4]->speed_rpm)<200&&rtU.status_CH2_5==1)||
		(fabs(rtU.target_CH2_5-motor_data_can2[4]->circle*8191-motor_data_can2[4]->ecd)<500&&rtU.status_CH2_5==2))
		rtU.reset_status2_5=1-rtU.reset_status2_5;
	
	if((fabs(rtU.target_CH2_6-motor_data_can2[5]->speed_rpm)<200&&rtU.status_CH2_6==1)||
		(fabs(rtU.target_CH2_6-motor_data_can2[5]->circle*8191-motor_data_can2[5]->ecd)<500&&rtU.status_CH2_6==2))
		rtU.reset_status2_6=1-rtU.reset_status2_6;
	
	if((fabs(rtU.target_CH2_7-motor_data_can2[6]->speed_rpm)<200&&rtU.status_CH2_7==1)||
		(fabs(rtU.target_CH2_7-motor_data_can2[6]->circle*8191-motor_data_can2[6]->ecd)<500&&rtU.status_CH2_7==2))
		rtU.reset_status2_7=1-rtU.reset_status2_7;

	
	if((fabs(rtU.target_CH3_1-motor_data_can3[0]->speed_rpm)<200&&rtU.status_CH3_1==1)||
		(fabs(rtU.target_CH3_1-motor_data_can3[0]->circle*8191-motor_data_can3[0]->ecd)<500&&rtU.status_CH3_1==2))
		rtU.reset_status3_1=1-rtU.reset_status3_1;
	
	if((fabs(rtU.target_CH3_2-motor_data_can3[1]->speed_rpm)<200&&rtU.status_CH3_2==1)||
		(fabs(rtU.target_CH3_2-motor_data_can3[1]->circle*8191-motor_data_can3[1]->ecd)<500&&rtU.status_CH3_2==2))
		rtU.reset_status3_2=1-rtU.reset_status3_2;
	
	if((fabs(rtU.target_CH3_3-motor_data_can3[2]->speed_rpm)<200&&rtU.status_CH3_3==1)||
		(fabs(rtU.target_CH3_3-motor_data_can3[2]->circle*8191-motor_data_can3[2]->ecd)<500&&rtU.status_CH3_3==2))
		rtU.reset_status3_3=1-rtU.reset_status3_3;
	
	if((fabs(rtU.target_CH3_4-motor_data_can3[3]->speed_rpm)<200&&rtU.status_CH3_4==1)||
		(fabs(rtU.target_CH3_4-motor_data_can3[3]->circle*8191-motor_data_can3[3]->ecd)<500&&rtU.status_CH3_4==2))
		rtU.reset_status3_4=1-rtU.reset_status3_4;
	
	if((fabs(rtU.target_CH3_5-motor_data_can3[4]->speed_rpm)<200&&rtU.status_CH3_5==1)||
		(fabs(rtU.target_CH3_5-motor_data_can3[4]->circle*8191-motor_data_can3[4]->ecd)<500&&rtU.status_CH3_5==2))
		rtU.reset_status3_5=1-rtU.reset_status3_5;
	
  if((fabs(rtU.target_CH3_6-motor_data_can3[5]->speed_rpm)<200&&rtU.status_CH3_6==1)||
		(fabs(rtU.target_CH3_6-motor_data_can3[5]->circle*8191-motor_data_can3[5]->ecd)<500&&rtU.status_CH3_6==2))
		rtU.reset_status3_6=1-rtU.reset_status3_6;
	
	if((fabs(rtU.target_CH3_7-motor_data_can3[6]->speed_rpm)<200&&rtU.status_CH3_7==1)||
		(fabs(rtU.target_CH3_7-motor_data_can3[6]->circle*8191-motor_data_can3[6]->ecd)<500&&rtU.status_CH3_7==2))
		rtU.reset_status3_7=1-rtU.reset_status3_7;

}

void set_target(uint8_t channel,uint8_t id,int target)
{
	  switch (channel)
  {
  case 1:
    switch (id)
    {
    case 1:
			if(motor_data_can1[0]->activate)
				rtU.target_CH1_1=target;
      break;
    case 2:
			if(motor_data_can1[1]->activate)
				rtU.target_CH1_2=target;
      break;
    case 3:
			if(motor_data_can1[2]->activate)
				rtU.target_CH1_3=target;
      break;
    case 4:
			if(motor_data_can1[3]->activate)
				rtU.target_CH1_4=target;
      break;
    case 5:
			if(motor_data_can1[4]->activate)
				rtU.target_CH1_5=target;
      break;
    case 6:
			if(motor_data_can1[5]->activate)
				rtU.target_CH1_6=target;
      break;
    case 7:
			if(motor_data_can1[6]->activate)
				rtU.target_CH1_7=target;
      break;
    }
    break;
  case 2:
		switch (id)
    {
    case 1:
			if(motor_data_can2[0]->activate)
				rtU.target_CH2_1=target;
      break;
    case 2:
			if(motor_data_can2[1]->activate)
				rtU.target_CH2_2=target;
      break;
    case 3:
			if(motor_data_can2[2]->activate)
				rtU.target_CH2_3=target;
      break;
    case 4:
			if(motor_data_can2[3]->activate)
				rtU.target_CH2_4=target;
      break;
    case 5:
			if(motor_data_can2[4]->activate)
				rtU.target_CH2_5=target;
      break;
    case 6:
			if(motor_data_can2[5]->activate)
				rtU.target_CH2_6=target;
      break;
    case 7:
			if(motor_data_can2[6]->activate)
				rtU.target_CH2_7=target;
      break;
    }
    break;
	case 3:
		switch (id)
    {
    case 1:
			if(motor_data_can3[0]->activate)
				rtU.target_CH3_1=target;
      break;
    case 2:
			if(motor_data_can3[1]->activate)
				rtU.target_CH3_2=target;
      break;
    case 3:
			if(motor_data_can3[2]->activate)
				rtU.target_CH3_3=target;
      break;
    case 4:
			if(motor_data_can3[3]->activate)
				rtU.target_CH3_4=target;
      break;
    case 5:
			if(motor_data_can3[4]->activate)
				rtU.target_CH3_5=target;
      break;
    case 6:
			if(motor_data_can3[5]->activate)
				rtU.target_CH3_6=target;
      break;
    case 7:
			if(motor_data_can3[6]->activate)
				rtU.target_CH3_7=target;
      break;
    }
    break;
  }
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
		case 3:
    switch (motor)
    {
    case 1:
      rtP.SPD_D_CH3_1 = kd;
      rtP.SPD_I_CH3_1 = ki;
      rtP.SPD_P_CH3_1 = kp;
      break;
    case 2:
      rtP.SPD_D_CH3_2 = kd;
      rtP.SPD_I_CH3_2 = ki;
      rtP.SPD_P_CH3_2 = kp;
      break;
    case 3:
      rtP.SPD_D_CH3_3 = kd;
      rtP.SPD_I_CH3_3 = ki;
      rtP.SPD_P_CH3_3 = kp;
      break;
    case 4:
      rtP.SPD_D_CH3_4 = kd;
      rtP.SPD_I_CH3_4 = ki;
      rtP.SPD_P_CH3_4 = kp;
      break;
    case 5:
      rtP.SPD_D_CH3_5 = kd;
      rtP.SPD_I_CH3_5 = ki;
      rtP.SPD_P_CH3_5 = kp;
      break;
    case 6:
      rtP.SPD_D_CH3_6 = kd;
      rtP.SPD_I_CH3_6 = ki;
      rtP.SPD_P_CH3_6 = kp;
      break;
    case 7:
      rtP.SPD_D_CH3_7 = kd;
      rtP.SPD_I_CH3_7 = ki;
      rtP.SPD_P_CH3_7 = kp;
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
		case 3:
    switch (motor)
    {
    case 1:
      rtP.ANG_S_P_CH3_1 = kp;
      rtP.ANG_S_I_CH3_1 = ki;
      rtP.ANG_S_D_CH3_1 = kd;
      break;
    case 2:
      rtP.ANG_S_P_CH3_2 = kp;
      rtP.ANG_S_I_CH3_2 = ki;
      rtP.ANG_S_D_CH3_2 = kd;
      break;
    case 3:
      rtP.ANG_S_P_CH3_3 = kp;
      rtP.ANG_S_I_CH3_3 = ki;
      rtP.ANG_S_D_CH3_3 = kd;
      break;
    case 4:
      rtP.ANG_S_P_CH3_4 = kp;
      rtP.ANG_S_I_CH3_4 = ki;
      rtP.ANG_S_D_CH3_4 = kd;
      break;
    case 5:
      rtP.ANG_S_P_CH3_5 = kp;
      rtP.ANG_S_I_CH3_5 = ki;
      rtP.ANG_S_D_CH3_5 = kd;
      break;
    case 6:
      rtP.ANG_S_P_CH3_6 = kp;
      rtP.ANG_S_I_CH3_6 = ki;
      rtP.ANG_S_D_CH3_6 = kd;
      break;
    case 7:
      rtP.ANG_S_P_CH3_7 = kp;
      rtP.ANG_S_I_CH3_7 = ki;
      rtP.ANG_S_D_CH3_7 = kd;
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
	case 3:
    switch (motor)
    {
    case 1:
      rtP.ANG_A_P_CH3_1 = kp;
      rtP.ANG_A_I_CH3_1 = ki;
      rtP.ANG_A_D_CH3_1 = kd;
      break;
    case 2:
      rtP.ANG_A_P_CH3_2 = kp;
      rtP.ANG_A_I_CH3_2 = ki;
      rtP.ANG_A_D_CH3_2 = kd;
      break;
    case 3:
      rtP.ANG_A_P_CH3_3 = kp;
      rtP.ANG_A_I_CH3_3 = ki;
      rtP.ANG_A_D_CH3_3 = kd;
      break;
    case 4:
      rtP.ANG_A_P_CH3_4 = kp;
      rtP.ANG_A_I_CH3_4 = ki;
      rtP.ANG_A_D_CH3_4 = kd;
      break;
    case 5:
      rtP.ANG_A_P_CH3_5 = kp;
      rtP.ANG_A_I_CH3_5 = ki;
      rtP.ANG_A_D_CH3_5 = kd;
      break;
    case 6:
      rtP.ANG_A_P_CH3_6 = kp;
      rtP.ANG_A_I_CH3_6 = ki;
      rtP.ANG_A_D_CH3_6 = kd;
      break;
    case 7:
      rtP.ANG_A_P_CH3_7 = kp;
      rtP.ANG_A_I_CH3_7 = ki;
      rtP.ANG_A_D_CH3_7 = kd;
      break;
    }
    break;
  }
}
