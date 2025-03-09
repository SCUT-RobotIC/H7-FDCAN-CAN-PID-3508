/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "fdcan.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "PID_MODEL.h"
#include "rtwtypes.h"
#include <math.h>
#include "bsp_fdcan.h"
#include "motorctrl.h"
#include "stdio.h"
#include "math.h"
#include "dm_motor_drv.h"
#include "dm_motor_ctrl.h"
#include "UPPER_LOCATION.h"
#include "stdio.h"
#include "string.h"
#include "sbus.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern motor_t motor[num];
extern uint8_t CAN_RECEIVE[3];
extern TGT_COOR TC;
extern REAL_COOR RC;
extern double deadband;
extern motor_measure_t *motor_data_can1[8];
extern motor_measure_t *motor_data_can2[8];
extern motor_measure_t *motor_data_can3[8];
#define VEL      1
#define ANG      2

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
vehicle_state vehicle_test={
0,0,0,0
};

static uint8_t index[2] = {0};
static uint8_t buffer[100];
char UART7_TX_BUF[100];
uint8_t UART7_RX_BUF[100];
uint8_t USART2_RX_BUF[100];
uint8_t rx_datatemp[8];
int cnt[10];
int PinState=0;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM6_Init();
  MX_FDCAN2_Init();
  MX_USART2_UART_Init();
  MX_FDCAN3_Init();
  MX_USART3_UART_Init();
  MX_FDCAN1_Init();
  MX_UART7_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_UART_Receive_IT(&huart2, buffer, 1);
	HAL_UART_Receive_IT(&huart7, buffer+1, 1);
  can_filter_init();
	bsp_can_init();
	PID_MODEL_initialize();
	PID_Speed_Para_Init(1, 1, 10 , 3 , 0.01);
	PID_Speed_Para_Init(1, 2, 10 , 3 , 0.01);
	PID_Speed_Para_Init(1, 3, 10 , 3 , 0.01);
	PID_Speed_Para_Init(1, 4, 10 , 3 , 0.01);
	PID_Speed_Para_Init(1, 5, 10 , 3 , 0.01);
	
	PID_Speed_Para_Init(2, 1, 20 , 8 , 0.01);
	PID_Speed_Para_Init(2, 2, 20 , 8 , 0.01);
	PID_Speed_Para_Init(2, 3, 20 , 8 , 0.01);


	
	PID_Speed_Para_Init(3, 1, 10 , 3 , 0.01);
	PID_Speed_Para_Init(3, 2, 10 , 3 , 0.01);
	PID_Speed_Para_Init(3, 3, 10 , 3 , 0.01);
	PID_Speed_Para_Init(3, 4, 10 , 3 , 0.01);
	PID_Speed_Para_Init(3, 5, 10 , 3 , 0.01);
	
	PID_Angle_S_Para_Init(1, 1 , 10 , 3 , 0.01);
  PID_Angle_A_Para_Init(1, 1 , 0.3 , 0 , 0);
	rtP.TRANS_CH1_1=0.5;
	
	
	PID_Angle_S_Para_Init(2, 1 , 10 , 3 , 0.01);
  PID_Angle_A_Para_Init(2, 1 , 0.3 , 0 , 0);
	
	PID_Angle_S_Para_Init(2, 3 , 5 , 3 , 0.01);
  PID_Angle_A_Para_Init(2, 3 , 1.5 , 1 , 0.1);
	
	PID_Angle_S_Para_Init(2, 5 , 100 , 30 , 0.1);
  PID_Angle_A_Para_Init(2, 5 , 1.0 , 0 , 0);
	PID_Angle_S_Para_Init(2, 6 , 100 , 30 , 0.1);
  PID_Angle_A_Para_Init(2, 6 , 1.0 , 0 , 0);
	PID_Angle_S_Para_Init(2, 7 , 100 , 30 , 0.1);
  PID_Angle_A_Para_Init(2, 7 , 1.0 , 0 , 0);
	
	PID_Angle_S_Para_Init(3, 1 , 10 , 3 , 0.01);
  PID_Angle_A_Para_Init(3, 1 , 0.3 , 0 , 0);
	
	Set_6020_Mode( 0 );
	set_mode( VEL, VEL, VEL, VEL, VEL, VEL, VEL,
            VEL, VEL, VEL, VEL, ANG, ANG, ANG,
					  ANG, VEL, VEL, VEL, ANG, ANG, ANG ); 
	dm_motor_init();
	dm_motor_enable(&hfdcan1,&motor[Motor1]);
	memset(UART7_TX_BUF,0,sizeof(UART7_TX_BUF));
	while(motor_data_can2[4]->activate)
		rtU.target_CH2_5=5848;
	while(motor_data_can2[5]->activate)
		rtU.target_CH2_6=2384;
	while(motor_data_can2[6]->activate)
		rtU.target_CH2_7=3055;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//		set_target(1,1,8191*100);
//		set_target(2,1,vehicle_test.Vx);
//		set_target(2,2,vehicle_test.Vx);
//		set_target(2,3,vehicle_test.Vx);
//		vehicle_test.Vy=rtU.speed_rpm_CH2_1;
//		vehicle_test.omega=rtU.speed_rpm_CH2_2;
//		vehicle_test.Park=rtU.speed_rpm_CH2_3;
		
//		set_target(3,1,8191*100);
		if(SBUS_CH.ConnectState==1){
			vehicle_test.Vx=SBUS_CH.CH1-1002;
			vehicle_test.Vy=SBUS_CH.CH2-1002;
			vehicle_test.omega=SBUS_CH.CH4-1002;
			vehicle_test.Park=(SBUS_CH.CH6>800);
		}
		ctrlmotor(vehicle_test.Vx,vehicle_test.Vy,vehicle_test.omega,vehicle_test.Park);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM6)
  {
    cnt[0]++;
		if(RC.action==1)
		{ 
			int buff_len;
			memset(UART7_TX_BUF,0,buff_len);
			buff_len = sprintf(UART7_TX_BUF,"%f\r\n",(float)deadband);
			HAL_UART_Transmit_DMA(&huart7,(uint8_t *)UART7_TX_BUF,buff_len);
		}
		dm_motor_ctrl_send(&hfdcan1,&motor[Motor1]);
		
		Reach_TGT();
		get_msgn();
		assign_output();
    motor_state_update();
		set_reset_status();
		PID_MODEL_step();

		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,(GPIO_PinState)1);

  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	
		 if (huart->Instance == USART2)
    {
				if(index[0] == 0 && buffer[0]!=0x0F){
					HAL_UART_Receive_IT(&huart2, buffer, 1);
					return;
				}
        USART2_RX_BUF[index[0]++] = buffer[0];

        if (index[0] == 24)
        {
            index[0] = 0;
            if (USART2_RX_BUF[0] == 0x0F && USART2_RX_BUF[23] == 0x00) 
            {
								update_sbus(USART2_RX_BUF);
            }
        }

        HAL_UART_Receive_IT(&huart2, buffer, 1);
    }
		
    if (huart->Instance == UART7)
    {
				if(index[1] == 0 && buffer[1]!=0xA5){
					HAL_UART_Receive_IT(&huart7, buffer+1, 1);
					return;
				}
        UART7_RX_BUF[index[1]++] = buffer[1];

        if (index[1] == 16)
        {
            index[1] = 0;
            if (UART7_RX_BUF[0] == 0xA5 && UART7_RX_BUF[15] == 0x5A) 
            {
								Receive();

								HAL_UART_Transmit_DMA(&huart7,UART7_RX_BUF,16);
            }
        }

        HAL_UART_Receive_IT(&huart7, buffer+1, 1);
    }
}
/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
