#include "adc_capture.h"
#include <stdio.h>
#include "lcd.h"
#include "adc.h"

static char buf[20];
static double __from_adc(ADC_HandleTypeDef* def){
    HAL_ADC_Start(def);
    return 3.3 * (HAL_ADC_GetValue(def)) / 4096.0;
}


void display_captured_adc(void)
{
    lcd_middledisplay(Line0, "ADC Catured Result");
    
    snprintf(buf, 20, "ADC1: %.2lf", __from_adc(&hadc1));
    lcd_middledisplay(Line1, buf);
    
    snprintf(buf, 20, "ADC2: %.2lf", __from_adc(&hadc2));
    lcd_middledisplay(Line2, buf);
}
