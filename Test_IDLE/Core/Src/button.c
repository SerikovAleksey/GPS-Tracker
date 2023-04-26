#include "button.h"

uint16_t Read_Button_Time_Push (uint16_t but_name, uint16_t t0)
{
	while (HAL_GPIO_ReadPin(BUT_TYPE, but_name))
		{
			t1 = TIM2->CNT;		
		}
	if (t1 >= t0) return t1 - t0;
	if (t1 < t0) return t1 + 5000 - t0;
} // ReadButton


void Delay(uint16_t time_ms)
{
	uint16_t tt = 0;
		uint16_t t2 = 0;

	while (tt < time_ms)
		{
			t2 = TIM2->CNT;
			if(TIM2->CNT >= t2) tt += TIM2->CNT - t2;
			else tt += TIM2->CNT + 5000 - t2;
		}
}