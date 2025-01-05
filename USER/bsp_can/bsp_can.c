/**
 *   @brief ������CAN�жϽ��պ��������յ������,CAN���ͺ������͵���������Ƶ��.
 **/
#include "bsp_can.h"
#include "main.h"

uint8_t mode_6020 = CLOSE_6020;

extern FDCAN_HandleTypeDef hfdcan1; // CAN����1
extern FDCAN_HandleTypeDef hfdcan2;
uint8_t CAN_RECEIVE[3];

static motor_measure_t can1_motor[8];
static motor_measure_t can2_motor[8];


FDCAN_RxHeaderTypeDef temp;

motor_measure_t *motor_data_can1[8];
motor_measure_t *motor_data_can2[8];

static FDCAN_TxHeaderTypeDef can1_tx_message_front; // can1前八个
static FDCAN_TxHeaderTypeDef can1_tx_message_last; // can1后八个
static FDCAN_TxHeaderTypeDef can2_tx_message_front; // can2前八个
static FDCAN_TxHeaderTypeDef can2_tx_message_last; // can2后八个


static uint8_t can1_send_front_data[8]; // can1前八个
static uint8_t can1_send_last_data[8]; // can1后八个
static uint8_t can2_send_front_data[8]; // can2前八个
static uint8_t can2_send_last_data[8]; // can2后八个

/// @brief
#define get_motor_measure(ptr, data)                               \
  {                                                                \
    (ptr)->last_ecd = (ptr)->ecd;                                  \
    (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);           \
    (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);     \
    (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); \
    (ptr)->temperate = (data)[6];                                  \
  }

void circle_cc(motor_measure_t *ptr)
{

  if (((ptr)->ecd - (ptr)->last_ecd) > 5000)
  {
    ptr->circle -= 1;
  }
  else if (((ptr)->ecd - (ptr)->last_ecd) < -5000)
  {

    ptr->circle += 1;
  }
}

void Set_6020_Mode(uint8_t mode){
	mode_6020=mode;
}
/*
������ݣ�      0:���̵��1 3508���,              1:���̵��2 3508���,
                2:���̵��3 3508���,              3:���̵��4 3508���;
                4:yaw��̨��� 6020���;            5:pitch��̨��� 6020���;
                6:������� 2006���
*/

/// @brief hal��CAN�ص�����,���յ������
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)//接收回调函数
{

  if (hfdcan == &hfdcan1)
  {
		CAN_RECEIVE[0]=1;
    FDCAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];

    HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_header, rx_data);
		temp=rx_header;

		if ((mode_6020 & 0b100) == 0){
			switch (rx_header.Identifier)
			{
				case CAN_M1_ID:
				case CAN_M2_ID:
				case CAN_M3_ID:
				case CAN_M4_ID:
				case CAN_M5_ID:
				case CAN_M6_ID:
				case CAN_M7_ID:
				case CAN_M8_ID:
				{
		
					static uint8_t i = 0;
					// get motor id
					i = rx_header.Identifier - CAN_M1_ID;
					get_motor_measure(&can1_motor[i], rx_data);
					circle_cc(&can1_motor[i]);
					break;
				}
				default:
				{
					break;
				}
			}
		}
		else{
			switch (rx_header.Identifier)
			{
				case CAN_6020_M1_ID:
				case CAN_6020_M2_ID:
				case CAN_6020_M3_ID:
				case CAN_6020_M4_ID:
				case CAN_6020_M5_ID:
				case CAN_6020_M6_ID:
				case CAN_6020_M7_ID:
				{
		
					static uint8_t i = 0;
					// get motor id
					i = rx_header.Identifier - CAN_6020_M1_ID;
					get_motor_measure(&can1_motor[i], rx_data);
					circle_cc(&can1_motor[i]);
					break;
				}
				default:
				{
					break;
				}
			}
		}
    HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0);



  }
	
	  if (hfdcan == &hfdcan2)
  {
		CAN_RECEIVE[1]=1;
    FDCAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];

    HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_header, rx_data);
		temp=rx_header;
 		if ((mode_6020 & 0b010) == 0){
			switch (rx_header.Identifier)
			{
				case CAN_M1_ID:
				case CAN_M2_ID:
				case CAN_M3_ID:
				case CAN_M4_ID:
				case CAN_M5_ID:
				case CAN_M6_ID:
				case CAN_M7_ID:
				case CAN_M8_ID:
				{
		
					static uint8_t i = 0;
					// get motor id
					i = rx_header.Identifier - CAN_M1_ID;
					get_motor_measure(&can2_motor[i], rx_data);
					circle_cc(&can2_motor[i]);
					break;
				}
				default:
				{
					break;
				}
			}
		}
		else{
			switch (rx_header.Identifier)
			{
				case CAN_6020_M1_ID:
				case CAN_6020_M2_ID:
				case CAN_6020_M3_ID:
				case CAN_6020_M4_ID:
				case CAN_6020_M5_ID:
				case CAN_6020_M6_ID:
				case CAN_6020_M7_ID:
				{
		
					static uint8_t i = 0;
					// get motor id
					i = rx_header.Identifier - CAN_6020_M1_ID;
					
					get_motor_measure(&can2_motor[i], rx_data);
					circle_cc(&can2_motor[i]);
					break;
				}
				default:
				{
					break;
				}
			}
		}
    HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0);



  }

 
}

/**
 * @brief          ���͵�����Ƶ���(0x201,0x202,0x203,0x204)
 * @param[in]      motor1: (0x201) 3508������Ƶ���, ��Χ [-16384,16384]
 * @param[in]      motor2: (0x202) 3508������Ƶ���, ��Χ [-16384,16384]
 * @param[in]      motor3: (0x203) 3508������Ƶ���, ��Χ [-16384,16384]
 * @param[in]      motor4: (0x204) 3508������Ƶ���, ��Χ [-16384,16384]
 */

void CAN1_cmd_motor(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
  can1_tx_message_front.Identifier = CAN_motor_ALL_ID;
	can1_tx_message_front.IdType = FDCAN_STANDARD_ID;
  can1_tx_message_front.TxFrameType = FDCAN_DATA_FRAME;
  can1_tx_message_front.DataLength = FDCAN_DLC_BYTES_8;
  can1_send_front_data[0] = motor1 >> 8;
  can1_send_front_data[1] = motor1;
  can1_send_front_data[2] = motor2 >> 8;
  can1_send_front_data[3] = motor2;
  can1_send_front_data[4] = motor3 >> 8;
  can1_send_front_data[5] = motor3;
  can1_send_front_data[6] = motor4 >> 8;
  can1_send_front_data[7] = motor4;

  HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &can1_tx_message_front, can1_send_front_data);
}

void CAN1_cmd_motor_last(int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8)
{
  can1_tx_message_last.Identifier = CAN_GIMBAL_ALL_ID;
	can1_tx_message_last.IdType = FDCAN_STANDARD_ID;
  can1_tx_message_last.TxFrameType = FDCAN_DATA_FRAME;
  can1_tx_message_last.DataLength = FDCAN_DLC_BYTES_8;
  can1_send_last_data[0] = motor5 >> 8;
  can1_send_last_data[1] = motor5;
  can1_send_last_data[2] = motor6 >> 8;
  can1_send_last_data[3] = motor6;
  can1_send_last_data[4] = motor7 >> 8;
  can1_send_last_data[5] = motor7;
  can1_send_last_data[6] = motor8 >> 8;
  can1_send_last_data[7] = motor8;

  HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &can1_tx_message_last, can1_send_last_data);
}
void CAN2_cmd_motor(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
  can2_tx_message_front.Identifier = CAN_motor_ALL_ID;
	can2_tx_message_front.IdType = FDCAN_STANDARD_ID;
  can2_tx_message_front.TxFrameType = FDCAN_DATA_FRAME;
  can2_tx_message_front.DataLength = FDCAN_DLC_BYTES_8;
  can2_send_front_data[0] = motor1 >> 8;
  can2_send_front_data[1] = motor1;
  can2_send_front_data[2] = motor2 >> 8;
  can2_send_front_data[3] = motor2;
  can2_send_front_data[4] = motor3 >> 8;
  can2_send_front_data[5] = motor3;
  can2_send_front_data[6] = motor4 >> 8;
  can2_send_front_data[7] = motor4;

  HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &can2_tx_message_front, can2_send_front_data);

}

void CAN2_cmd_motor_last(int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8)
{
  can2_tx_message_last.Identifier = CAN_GIMBAL_ALL_ID;
	can2_tx_message_last.IdType = FDCAN_STANDARD_ID;
  can2_tx_message_last.TxFrameType = FDCAN_DATA_FRAME;
  can2_tx_message_last.DataLength = FDCAN_DLC_BYTES_8;
  can2_send_last_data[0] = motor5 >> 8;
  can2_send_last_data[1] = motor5;
  can2_send_last_data[2] = motor6 >> 8;
  can2_send_last_data[3] = motor6;
  can2_send_last_data[4] = motor7 >> 8;
  can2_send_last_data[5] = motor7;
  can2_send_last_data[6] = motor8 >> 8;
  can2_send_last_data[7] = motor8;

  HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &can2_tx_message_last, can2_send_last_data);

}

void CAN1_cmd_motor6020(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4, int16_t motor5, int16_t motor6, int16_t motor7)
{
  can1_tx_message_front.Identifier = CAN_motor_6020_ALL_ID;
	can1_tx_message_front.IdType = FDCAN_STANDARD_ID;
  can1_tx_message_front.TxFrameType = FDCAN_DATA_FRAME;
  can1_tx_message_front.DataLength = FDCAN_DLC_BYTES_8;
  can1_send_front_data[0] = motor1 >> 8;
  can1_send_front_data[1] = motor1;
  can1_send_front_data[2] = motor2 >> 8;
  can1_send_front_data[3] = motor2;
  can1_send_front_data[4] = motor3 >> 8;
  can1_send_front_data[5] = motor3;
  can1_send_front_data[6] = motor4 >> 8;
  can1_send_front_data[7] = motor4;

  HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &can1_tx_message_front, can1_send_front_data);

  can1_tx_message_last.Identifier = CAN_GIMBAL_6020_ALL_ID;
	can1_tx_message_last.IdType = FDCAN_STANDARD_ID;
  can1_tx_message_last.TxFrameType = FDCAN_DATA_FRAME;
  can1_tx_message_last.DataLength = FDCAN_DLC_BYTES_8;
  can1_send_last_data[0] = motor5 >> 8;
  can1_send_last_data[1] = motor5;
  can1_send_last_data[2] = motor6 >> 8;
  can1_send_last_data[3] = motor6;
  can1_send_last_data[4] = motor7 >> 8;
  can1_send_last_data[5] = motor7;


  HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &can1_tx_message_last, can1_send_last_data);
}

void CAN2_cmd_motor6020(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4, int16_t motor5, int16_t motor6, int16_t motor7)
{
  can2_tx_message_front.Identifier = CAN_motor_6020_ALL_ID;
	can2_tx_message_front.IdType = FDCAN_STANDARD_ID;
  can2_tx_message_front.TxFrameType = FDCAN_DATA_FRAME;
  can2_tx_message_front.DataLength = FDCAN_DLC_BYTES_8;
  can2_send_front_data[0] = motor1 >> 8;
  can2_send_front_data[1] = motor1;
  can2_send_front_data[2] = motor2 >> 8;
  can2_send_front_data[3] = motor2;
  can2_send_front_data[4] = motor3 >> 8;
  can2_send_front_data[5] = motor3;
  can2_send_front_data[6] = motor4 >> 8;
  can2_send_front_data[7] = motor4;

  HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &can2_tx_message_front, can2_send_front_data);

  can2_tx_message_last.Identifier = CAN_GIMBAL_6020_ALL_ID;
	can2_tx_message_last.IdType = FDCAN_STANDARD_ID;
  can2_tx_message_last.TxFrameType = FDCAN_DATA_FRAME;
  can2_tx_message_last.DataLength = FDCAN_DLC_BYTES_8;
  can2_send_last_data[0] = motor5 >> 8;
  can2_send_last_data[1] = motor5;
  can2_send_last_data[2] = motor6 >> 8;
  can2_send_last_data[3] = motor6;
  can2_send_last_data[4] = motor7 >> 8;
  can2_send_last_data[5] = motor7;

  HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &can2_tx_message_last, can2_send_last_data);
}
// ���� 3508�������ָ��
motor_measure_t *get_can1_motor(uint8_t i)
{
  return &can1_motor[(i)];
}
motor_measure_t *get_can2_motor(uint8_t i)
{
  return &can2_motor[(i)];
}




void can_filter_init(void)
{
   FDCAN_FilterTypeDef filter;                   	//< 声明局部变量 can过滤器结构体
	filter.IdType       = FDCAN_STANDARD_ID;       	//< id设置为标准id
	filter.FilterIndex  = 0;                      	//< 设值筛选器的编号，标准id选择0-127
	filter.FilterType   = FDCAN_FILTER_MASK;       	//< 设置工作模式为掩码模式
	filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0; 	//< 将经过过滤的数据存储到 fifo0
	filter.FilterID1    = 0x000;                   	//< 筛选器的id
	filter.FilterID2    = 0x000;
	
	HAL_FDCAN_ConfigFilter(&hfdcan1, &filter);   //< 配置过滤器	
  HAL_FDCAN_Start(&hfdcan1);                   //< 使能can
    //该check来测试can控制器是否使能，可以把该赋值去掉	
	HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);  // 使能fifo0接收到新信息中断

  HAL_FDCAN_ConfigFilter(&hfdcan2, &filter);
  HAL_FDCAN_Start(&hfdcan2);
  HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
}




void motor_state_update()
{

  motor_data_can1[0] = get_can1_motor(0);
  motor_data_can1[1] = get_can1_motor(1);
  motor_data_can1[2] = get_can1_motor(2);
  motor_data_can1[3] = get_can1_motor(3);
  motor_data_can1[4] = get_can1_motor(4);
  motor_data_can1[5] = get_can1_motor(5);
  motor_data_can1[6] = get_can1_motor(6);
  motor_data_can1[7] = get_can1_motor(7);
	
	motor_data_can2[0] = get_can2_motor(0);
  motor_data_can2[1] = get_can2_motor(1);
  motor_data_can2[2] = get_can2_motor(2);
  motor_data_can2[3] = get_can2_motor(3);
  motor_data_can2[4] = get_can2_motor(4);
  motor_data_can2[5] = get_can2_motor(5);
  motor_data_can2[6] = get_can2_motor(6);
  motor_data_can2[7] = get_can2_motor(7);
	
}


//*******************************************************************�¼�
