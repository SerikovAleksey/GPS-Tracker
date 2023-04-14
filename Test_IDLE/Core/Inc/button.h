#ifndef _BUTTON_
#define _BUTTON_

//---------INCLUDES---------//
#include "stm32f1xx_hal.h"

//---------DEFINES---------//
#define BUT_TYPE GPIOA
#define BUT_ON_OFF GPIO_PIN_10 
#define BUT_TRANSMIT_DATA GPIO_PIN_11 
#define BUT_MAKE_POINT GPIO_PIN_9 

//---------VARIABLES---------//
static uint16_t t1 = 0;

extern TIM_HandleTypeDef htim2;

//---------FUNCTIONS---------//
uint16_t Read_Button_Time_Push(uint16_t but_name, uint16_t t0);

#endif //_BUTTON_