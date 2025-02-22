#include "bsp_fdcan.h"
#include "main.h"
FDCAN_TxHeaderTypeDef can_message;
FDCAN_TxHeaderTypeDef pTxHeader;
uint8_t mode_6020 = CLOSE_6020;

extern FDCAN_HandleTypeDef hfdcan1; // CAN????1
extern FDCAN_HandleTypeDef hfdcan2;
extern FDCAN_HandleTypeDef hfdcan3;

uint8_t CAN_RECEIVE[3];

motor_measure_t can1_motor[8];
motor_measure_t can2_motor[8];
motor_measure_t can3_motor[8];

motor_measure_t *motor_data_can1[8];
motor_measure_t *motor_data_can2[8];
motor_measure_t *motor_data_can3[8];


static uint8_t can_send_data[8]; 


/**
************************************************************************
* @brief:      	bsp_can_init(void)
* @param:       void
* @retval:     	void
* @details:    	open can dev and enable can interrupt 
************************************************************************
**/
void bsp_can_init(void)
{
	can_filter_init();
	HAL_FDCAN_Start(&hfdcan1);                               //open FDCAN
	HAL_FDCAN_Start(&hfdcan2);
	HAL_FDCAN_Start(&hfdcan3);
	HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_WATERMARK, 0);
	HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_WATERMARK, 0);
	HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_WATERMARK, 0);
//	HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_BUFFER_NEW_MESSAGE, 0);
}
/**
************************************************************************
* @brief:      	can_filter_init(void)
* @param:       void
* @retval:     	void
* @details:    	can filter init
************************************************************************
**/
void can_filter_init(void)
{
	FDCAN_FilterTypeDef fdcan_filter;
	
	fdcan_filter.IdType = FDCAN_STANDARD_ID;                       //STD ID
	fdcan_filter.FilterIndex = 0;                                  //filter index                   
	fdcan_filter.FilterType = FDCAN_FILTER_MASK;                   
	fdcan_filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;           // filter0 to FIFO0  
	fdcan_filter.FilterID1 = 0x00;                               
	fdcan_filter.FilterID2 = 0x00;

	HAL_FDCAN_ConfigFilter(&hfdcan1,&fdcan_filter); 		 				
	HAL_FDCAN_ConfigGlobalFilter(&hfdcan1,FDCAN_REJECT,FDCAN_REJECT,FDCAN_REJECT_REMOTE,FDCAN_REJECT_REMOTE);
	HAL_FDCAN_ConfigFifoWatermark(&hfdcan1, FDCAN_CFG_RX_FIFO0, 1);
	
//	HAL_FDCAN_ConfigFifoWatermark(&hfdcan1, FDCAN_CFG_RX_FIFO1, 1);
	
	HAL_FDCAN_ConfigFilter(&hfdcan2,&fdcan_filter); 		 				
	HAL_FDCAN_ConfigGlobalFilter(&hfdcan2,FDCAN_REJECT,FDCAN_REJECT,FDCAN_REJECT_REMOTE,FDCAN_REJECT_REMOTE);
	HAL_FDCAN_ConfigFifoWatermark(&hfdcan2, FDCAN_CFG_RX_FIFO0, 1);

	HAL_FDCAN_ConfigFilter(&hfdcan3,&fdcan_filter); 		 				
	HAL_FDCAN_ConfigGlobalFilter(&hfdcan3,FDCAN_REJECT,FDCAN_REJECT,FDCAN_REJECT_REMOTE,FDCAN_REJECT_REMOTE);
	HAL_FDCAN_ConfigFifoWatermark(&hfdcan3, FDCAN_CFG_RX_FIFO0, 1);
}


/**
************************************************************************
* @brief:      	fdcanx_send_data(hcan_t *hfdcan, uint16_t id, uint8_t *data, uint32_t len)
* @param:       hfdcan£ºfdcan struct
* @param:       id£ºCAN ID
* @param:       data
* @param:       len£ºdata length
* @retval:     	0: send successful	1: send fail
* @details:    	send data
************************************************************************
**/
uint8_t fdcanx_send_data(hcan_t *hfdcan, uint16_t id, uint8_t *data, uint32_t len)
{	

    pTxHeader.Identifier=id;
    pTxHeader.IdType=FDCAN_STANDARD_ID;
    pTxHeader.TxFrameType=FDCAN_DATA_FRAME;
	
	/* HAL API*/
	if(len<=8)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_8;
	if(len==12)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_12;
	if(len==16)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_16;
	if(len==20)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_20;
	if(len==24)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_24;
	if(len==32)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_32;
	if(len==48)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_48;
	if(len==64)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_64;
	
    pTxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    pTxHeader.BitRateSwitch=FDCAN_BRS_ON;
    pTxHeader.FDFormat=FDCAN_FD_CAN;
    pTxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    pTxHeader.MessageMarker=0;
	/* HAL API*/
	if(HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &pTxHeader, data)!=HAL_OK) 
		return 1;
	return 0;	
}


/**
************************************************************************
* @brief:      	fdcanx_receive(hcan_t *hfdcan, uint16_t *rec_id, uint8_t *buf)
* @param:       hfdcan£ºfdcan struct
* @param:       rec_id: receive id
* @param:       buf£ºreceive data buffef
* @retval:     	receive data length
* @details:    	receive can data
************************************************************************
**/
uint8_t fdcanx_receive(hcan_t *hfdcan, uint16_t *rec_id, uint8_t *buf)
{	
	FDCAN_RxHeaderTypeDef pRxHeader;
	uint8_t len;
	
	if(HAL_FDCAN_GetRxMessage(hfdcan,FDCAN_RX_FIFO0, &pRxHeader, buf)==HAL_OK)
	{
		*rec_id = pRxHeader.Identifier;
		if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_8)
			len = pRxHeader.DataLength;
		if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_12)
			len = 12;
		if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_16)
			len = 16;
		if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_20)
			len = 20;
		if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_24)
			len = 24;
		if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_32)
			len = 32;
		if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_48)
			len = 48;
		if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_64)
			len = 64;
		
		return len;
	}
	return 0;	
}


/// @brief

void Set_6020_Mode(uint8_t mode){
	mode_6020=mode;
}



void CAN_CMD_MOTOR_DJI(FDCAN_HandleTypeDef *hfdcan,int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4,uint8_t motor_id)
{

	if(motor_id==FRONT)
		can_message.Identifier = CAN_FRONT_ID;
	else if (motor_id==LAST)
		can_message.Identifier = CAN_LAST_ID;
	can_message.IdType = FDCAN_STANDARD_ID;
  can_message.TxFrameType = FDCAN_DATA_FRAME;
  can_message.DataLength = FDCAN_DLC_BYTES_8;
  can_send_data[0] = motor1 >> 8;
  can_send_data[1] = motor1;
  can_send_data[2] = motor2 >> 8;
  can_send_data[3] = motor2;
  can_send_data[4] = motor3 >> 8;
  can_send_data[5] = motor3;
  can_send_data[6] = motor4 >> 8;
  can_send_data[7] = motor4;

  HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &can_message, can_send_data);

}


motor_measure_t *get_can1_motor(uint8_t i)
{
  return &can1_motor[(i)];
}
motor_measure_t *get_can2_motor(uint8_t i)
{
  return &can2_motor[(i)];
}
motor_measure_t *get_can3_motor(uint8_t i)
{
  return &can3_motor[(i)];
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
	
	motor_data_can3[0] = get_can3_motor(0);
  motor_data_can3[1] = get_can3_motor(1);
  motor_data_can3[2] = get_can3_motor(2);
  motor_data_can3[3] = get_can3_motor(3);
  motor_data_can3[4] = get_can3_motor(4);
  motor_data_can3[5] = get_can3_motor(5);
  motor_data_can3[6] = get_can3_motor(6);
  motor_data_can3[7] = get_can3_motor(7);
	
}


// can interrupt callback
__weak void fdcan1_rx_callback(void)
{

}
__weak void fdcan2_rx_callback(void)
{

}
__weak void fdcan3_rx_callback(void)
{

}
// can interrupt callback
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if (hfdcan == &hfdcan1)
    {
		fdcan1_rx_callback();
    }
		if (hfdcan == &hfdcan2)
    {
		fdcan2_rx_callback();
    }
		if (hfdcan == &hfdcan3)
    {
		fdcan3_rx_callback();
    }
}











