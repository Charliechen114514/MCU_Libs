#ifndef LED_H
#define LED_H


#include "stm32g4xx_hal.h"

uint16_t __compose_all_led_gpio(void);
void LED_GPIO_Init(void);

void led_set_status(uint8_t states);

/* index is from 0 for the gpio8 */
void led_set_single_status(uint8_t states, uint8_t index);
void led_flip_status(uint8_t index);
#endif
