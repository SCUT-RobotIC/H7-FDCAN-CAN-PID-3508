#ifndef __BSP_FDCAN_H__
#define __BSP_FDCAN_H__
#include "main.h"
#include "fdcan.h"

#define hcan_t FDCAN_HandleTypeDef
#define FRONT 0
#define LAST 1
typedef enum
{
    CAN_FRONT_ID = 0x200,
	  CAN_LAST_ID = 0x1FF,
    CAN_M1_ID = 0x201,
    CAN_M2_ID = 0x202,
    CAN_M3_ID = 0x203,
    CAN_M4_ID = 0x204,
    CAN_M5_ID = 0x205,
    CAN_M6_ID = 0x206,
    CAN_M7_ID = 0x207,
    CAN_M8_ID = 0x208,

	  CAN_motor_6020_ALL_ID  = 0x1FF,
		CAN_GIMBAL_6020_ALL_ID = 0x2FF,
		
    CAN_6020_M1_ID = 0x205,
    CAN_6020_M2_ID = 0x206,
    CAN_6020_M3_ID = 0x207,
    CAN_6020_M4_ID = 0x208,
    CAN_6020_M5_ID = 0x209,
    CAN_6020_M6_ID = 0x20A,
    CAN_6020_M7_ID = 0x21B,
		
		

} can_msg_id_e;

// Modify here to control different motors

// rm motor data
typedef struct
{
		uint8_t activate;
    uint16_t ecd;
    int16_t speed_rpm;
    int16_t given_current;
    uint8_t temperate;
    int16_t last_ecd;
    int circle;
} motor_measure_t;
void Set_6020_Mode(uint8_t mode);
void CAN_CMD_MOTOR_DJI(FDCAN_HandleTypeDef *hfdcan,int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4,uint8_t motor_id);
void motor_state_update(void);


void bsp_can_init(void);
void can_filter_init(void);
uint8_t fdcanx_send_data(hcan_t *hfdcan, uint16_t id, uint8_t *data, uint32_t len);
uint8_t fdcanx_receive(hcan_t *hfdcan, uint16_t *rec_id, uint8_t *buf);
void fdcan1_rx_callback(void);
void fdcan2_rx_callback(void);
void fdcan3_rx_callback(void);

#endif /* __BSP_FDCAN_H_ */

