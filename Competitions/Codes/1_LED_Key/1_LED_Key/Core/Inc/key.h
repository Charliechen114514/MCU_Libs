#ifndef KEY_H
#define KEY_H
#include "stm32g4xx_hal.h"


void key_init(void);
uint8_t key_scanner(uint8_t index);

#endif
