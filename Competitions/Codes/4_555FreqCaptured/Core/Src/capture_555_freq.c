#include "capture_555_freq.h"
#include "lcd.h"
#include "stm32g4xx_hal_tim.h"
#include <stdio.h>

#define MAKE_SCALAR     (15000)

// frequency that fetch as raw
uint32_t freq1, freq2;
// frequency using in storing the accumulations
uint32_t capture_freq1, capture_freq2;
// frequency that finally using in display
uint32_t display_freq1, display_freq2;
// captures recording
uint16_t capture_time;
static char buffer[20];

static void __make_real_display(void)
{
    snprintf(buffer, 20, "freq1: %d Hz", display_freq1);
    lcd_middledisplay(Line0, buffer);
    snprintf(buffer, 20, "freq2: %d Hz", display_freq2);
    lcd_middledisplay(Line1, buffer);
}

#define BETTER_ALG
void display_captured_frequency555(void)
{
#ifdef BETTER_ALG
    capture_time++;
    capture_freq1 += freq1;
    capture_freq2 += freq2;
    if(capture_time == MAKE_SCALAR){
        display_freq1 = capture_freq1 / MAKE_SCALAR;
        display_freq2 = capture_freq2 / MAKE_SCALAR;
        capture_freq1 = 0;
        capture_freq2 = 0;
        capture_time = 0;
        __make_real_display();
    }
#else
    __make_real_display();    
#endif
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    uint32_t capture_value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
    htim->Instance->CNT = 0;
    if(htim->Instance == TIM2){
        freq2 = HAL_RCC_GetSysClockFreq() / ((htim->Init.Prescaler + 1) * capture_value);
        display_captured_frequency555();	// 直到发生采集了我们才求取
    }
    if(htim->Instance == TIM16)
    {
        freq1 = HAL_RCC_GetSysClockFreq() / ((htim->Init.Prescaler + 1) * capture_value);
        display_captured_frequency555();	// 直到发生采集了我们才求取
    }
}
