#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_tim.h"
#include <stdio.h>
#include "tim.h"
#include "lcd.h"

uint32_t frequency, capture_value;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM17)
    {
        capture_value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
        TIM17->CNT = 0;
        frequency = HAL_RCC_GetSysClockFreq()/((htim->Init.Prescaler + 1) * capture_value);
    }
}

char value[20];
void display_current_captured_freq(void)
{
    snprintf(value, 20, "frequency:%d", frequency);
    lcd_middledisplay(Line0, value);
}



