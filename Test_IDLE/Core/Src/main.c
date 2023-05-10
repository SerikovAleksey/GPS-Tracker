/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "nmea.h"
#include "button.h"
#include "flash.h"
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define rx_buffer_size 1000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t rx_buffer[rx_buffer_size] = {0, };
uint16_t rx_buffer_len = 0;
uint8_t push_on_off = 0;
uint8_t push_transmit = 0;
uint8_t push_make_point = 0;
uint16_t t0 = 0;
uint8_t check_power = 0;
uint8_t check_capacity = 0;
//int data_valid = 0;

uint16_t tt = 0;
uint16_t t2 = 0;
uint16_t t = 0;

/*uint8_t buf[2000] = {'3', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '6', '5', '3', '4',
										'3', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',	
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
										'1', '1', '1', '1', '1', '1', '6', '5', '3', '4'};
uint16_t buf_16[1000];
uint16_t ar[1002];*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



void HAL_UART_IDLE_Callback(UART_HandleTypeDef *huart) {
	if (huart == &huart1) {
		__HAL_UART_DISABLE_IT(&huart1, UART_IT_IDLE);
		rx_buffer_len = rx_buffer_size - huart->RxXferCount;


		HAL_UART_AbortReceive_IT(&huart1);
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
		HAL_UART_Receive_IT(&huart1, (uint8_t*)rx_buffer, rx_buffer_size);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart == &huart1) {
		__HAL_UART_DISABLE_IT(&huart1, UART_IT_IDLE);

		HAL_UART_AbortReceive_IT(&huart1);
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
		HAL_UART_Receive_IT(&huart1, (uint8_t*)rx_buffer, rx_buffer_size);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	t0 = TIM2->CNT;
	if (GPIO_Pin == BUT_ON_OFF) // on or off record track
	{
		if (Read_Button_Time_Push(GPIO_Pin, t0) < 200) push_on_off = 1;
		
		if (Read_Button_Time_Push(GPIO_Pin, t0) > 1000) push_on_off = 2;
	}
	
	if (GPIO_Pin == BUT_MAKE_POINT) // make a point
	{
		if (Read_Button_Time_Push(GPIO_Pin, t0) < 400) push_make_point = 1;
	}
	
	if (GPIO_Pin == BUT_TRANSMIT_DATA) // send data
	{
		if (Read_Button_Time_Push(GPIO_Pin, t0) < 400) push_transmit = 1;
	}
	
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
				
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  HAL_Init();

  /* USER CODE BEGIN Init */
	

	//FLASH_Read(ADDR_FLASH_PAGE_127, b);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	HAL_UART_Receive_IT(&huart1, (uint8_t*)rx_buffer, rx_buffer_size);
	HAL_TIM_Base_Start(&htim2);						

	/*if (!check_power)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
		Delay(4000);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
		check_power = 1;
	}*/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
					
	
		/*if (push_on_off)
		{
			//FLASH_Erase(ADDR_FLASH_PAGE_127);
			//FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, ADDR_FLASH_PAGE_127, buf_u8_to_u16(buf, 500), 500/ 2 );
			//FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, ADDR_FLASH_PAGE_127, buf, 1000);

			//uint16_t array[500];
			//buf_u8_to_u16(buf, 2000, buf_16);
			//buf_u8_to_u16(q, 10, qq);
			
			
			Save_Data(buf_u8_to_u16(buf, 2000, buf_16), 1000, ar);
			push_on_off = 0;
			free(buf_16);
			free(ar);
			
		}
		if(push_transmit)
		{
			uint16_t ar2[500];
			//Read_Data(ar2);
			//transmit_data(buf_u16_to_u8(Read_Data(buf_u8_to_u16(buf, 500)), 500 / 2), 500);
			//buf_u16_to_u8(Read_Data(ar2), 1002, new_b);
			transmit_data(&buf_u16_to_u8(Read_Data(ar2), 1000, buf)[0], 2000);
			push_transmit = 0;
		}*/
		
		if (check_valid_data(rx_buffer) == -1 && !check_capacity) 
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
			Delay(300);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
		}
		else if (check_valid_data(rx_buffer) && !push_on_off && !check_capacity)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
			Delay(300);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		}
		
		uint8_t *buffer = get_transmit_buf().buf;
		uint16_t size = get_transmit_buf().size;
		
		uint16_t u16_size = 0;
		if ((size / 2) % 2 != 0)	
		{
			u16_size = size / 2 + 1;
		}
		else u16_size = size / 2;
		
		
		if (size >= 980 && size < 1010)
		{
			Save_Data(buf_u8_to_u16(buffer, size), u16_size + 1);
			Save_Data(&amount_lists, 1);
			set_ind_c(0);
			set_ind_t(0);
			amount_lists++;
		}
		
		if (push_on_off == 1 && !push_make_point)
		{
			get_data_from_GPS(rx_buffer, AVERAGE);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		}
		if (push_on_off == 1 && push_make_point) 
		{
			get_data_from_GPS(rx_buffer, SPECIAL);
			push_make_point = 0;
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		}
		Delay(300);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
		
		if (push_on_off == 2) 
		{
			Save_Data(buf_u8_to_u16(buffer, size), u16_size + 1);
			Save_Data(&amount_lists, 1);
			push_on_off = 0;
			set_ind_c(0);
			set_ind_t(0);
			amount_lists++;
		}
		if (push_on_off == 0) 
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		}
		
		if (push_transmit)
		{
			//if (buffer[6] == AVERAGE || buffer[6] == SPECIAL) 
			{
				//transmit_data(buffer, size);
			}
				//else 
			{
				uint16_t lists = 0;
				if ((*((uint32_t*)(ADDR_AMOUNT_PAGES))) == 0xFF) lists = 0;
				else lists = (*((uint32_t*)(ADDR_AMOUNT_PAGES)));
			  //size = (*((uint32_t*)(ADDR_FLASH_PAGE_127 + 2))- '0');
			  //uint16_t len = (lists - 1)* 512 + size;
				//uint16_t new_buf[len];
				for (uint16_t i = 0; i < lists; i++)
				{
					uint32_t add = ((uint32_t)(ADDR_FLASH_PAGE_126 -((uint32_t)(0x0000400 * (uint32_t)i))));
					uint16_t len = (*((uint32_t*)(ADDR_FLASH_PAGE_126 -((uint32_t)(0x0000400 * (uint32_t)i)))));
					transmit_data(buf_u16_to_u8(Read_Data(add, len), len), len * 2);
				}
				//transmit_data(buf_u16_to_u8(Read_Data(new_buf), len * 2 - 4, buffer), len * 2 - 4);
			}
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
			Delay(1000);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
			push_transmit = 0;
		}
		
		if (address_list_now == ((uint32_t)0x08007800))
		{
			check_capacity = 1;
			push_on_off = 0;
		}
		if (check_capacity)
		{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
		}
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
  /* USER CODE END 3 */
}

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV4;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 2000 - 1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 5000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA9 PA10 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB4 PB5 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
