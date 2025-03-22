#include "UPPER_LOCATION.h" // Device header
#include "PID_MODEL.h"
#include "rtwtypes.h"
#define PI 3.1415926
TGT_COOR TC;
REAL_COOR RC;
extern uint8_t UART2_RX_BUF[100];
extern motor_measure_t *motor_data[8];
uint8_t data[10];

double factors1 = 2;
double factors2 = 50;
double por=2.5;

double deadband = 50;
double top = 4000;
double a1, a2, a3, a4, a5, a6;
typedef struct {
	double p_pos;
	double i_pos;
	double d_pos;
	double p_ang;
	double i_ang;
	double d_ang;
}PID_PARA;

PID_PARA PID={0.5,0.01,0.00,
0.37,0,0};


void Receive()
{
  RC.x = (UART2_RX_BUF[2] << 8) | UART2_RX_BUF[1];
  RC.y = (UART2_RX_BUF[4] << 8) | UART2_RX_BUF[3];
  RC.theta = (((UART2_RX_BUF[6] << 8) | UART2_RX_BUF[5]));
	
	RC.xll=RC.xlast;
	RC.yll=RC.ylast;
	
  RC.xlast = RC.x;
  RC.ylast = RC.y;
  TC.x = (UART2_RX_BUF[8] << 8) | UART2_RX_BUF[7];
  TC.y = (UART2_RX_BUF[10] << 8) | UART2_RX_BUF[9];
  TC.theta = (UART2_RX_BUF[12] << 8) | UART2_RX_BUF[11];

  RC.action = (UART2_RX_BUF[14] << 8) | UART2_RX_BUF[13];
}
void Reach_TGT()
{
	RC.distll=RC.distlast;
	RC.distlast=RC.dist;
  RC.dist = sqrt(pow(TC.y - RC.y, 2) + pow((TC.x - RC.x), 2));
	rtU.distance=RC.dist;

	rtP.POS_P	=	PID.p_pos;
	rtP.POS_I	=	PID.i_pos;
	rtP.POS_D	=	PID.d_pos;	
	rtP.POS_A_P=PID.p_ang;
	rtP.POS_A_I=PID.i_ang;
	rtP.POS_A_D=PID.d_ang;
  TC.XYtheta = atan2(TC.y - RC.y, TC.x - RC.x) * 1800 / PI;
	deadband=rtP.DEADBAND_POS;
//  if (fabs((double)RC.dist) >= deadband && fabs((double)RC.dist) < 300)
//  {
//		factors1=2;
//    RC.dist = 1300 / factors1;
//  }
//	else if(fabs((double)RC.dist) >300)
//	{
//		factors1=4;
//	}
//  if (fabs((double)RC.dist) > top)
//  {

//    RC.dist = top;
//  }


//  if (fabs((double)RC.RE_theta) < 1)
//  {
//    RC.RE_theta = 0;
//  }
//  if (fabs((double)RC.dist) < deadband)
//  {
//		RC.Vx=0;
//		RC.Vy=0;
//  }else{
  RC.Vx = (rtY.vel_out) *cos(RC.RE_theta * PI / 1800);
  RC.Vy = (rtY.vel_out) *sin(RC.RE_theta * PI / 1800);
//	}
  //  a1=cos(RC.RE_theta*PI/180);
  //	a2=sin(RC.RE_theta*PI/180);
  //	    if(RC.omega!=0)
  //		{
  //			RC.Vx=0;
  //			RC.Vy=0;
  //		}
	if(RC.theta>1800)
		RC.theta-=3600;
  if (TC.theta - RC.theta > 1810)
    TC.theta = TC.theta - 3600;
  if (TC.theta - RC.theta < -1810)
    TC.theta = TC.theta + 3600;
  TC.theta = TC.theta % 3600;
	rtU.ang_err=TC.theta-RC.theta;
	RC.RE_theta = TC.XYtheta - RC.theta;
//  if (fabs((double)TC.theta - RC.theta) > 3)
//    RC.omega = (TC.theta - RC.theta) * factors2;
//  else
//    RC.omega = 0;
	RC.omega=rtY.omega_out;
//  if (fabs((double)RC.omega) > 5000)
//  {
//    if (RC.omega > 0)
//      RC.omega = 5000;
//    else
//      RC.omega = -5000;
//  }
//  else if (fabs((double)RC.omega) < 650)
//  {
//    if (RC.omega > 0)
//      RC.omega = 650;
//    else if (RC.omega < 0)
//      RC.omega = -650;
//    else
//      RC.omega = 0;
//  }
//  RC.omega = -RC.omega;
} // 最后把RC.Vx，RC.Vy，RC.omege三个参数放进main接收就行

