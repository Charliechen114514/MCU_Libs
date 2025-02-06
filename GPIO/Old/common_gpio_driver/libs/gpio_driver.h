#pragma once
/*
    Time:           2024.10.26
    Program File:   LED_Driver.h
    Author:         Charliechen
    Desp:           This is the header file of Common GPIO Driver
*/

#ifdef CCSTMF1
// Currently we support the stm lib for f1 series as test :)
// ------------ Defined for stm f1 series ------------------
#include "stm32f1xx.h"

typedef GPIO_TypeDef* GPIO_Letter;
typedef uint16_t    GPIO_Offset;
typedef uint32_t    Common_configure_type;
typedef Common_configure_type SpeedConfigureType;
typedef Common_configure_type PullPushConfigureType;
typedef Common_configure_type ModeConfigureType;
// ------------ Defined for stm f1 series End ---------------
#else
#error "Current can not support other mcu :("
#endif

// Cummon Defines

typedef struct{ 
    GPIO_Letter letter_case;
    GPIO_Offset offset;
}CCGPIO;

typedef struct{
    SpeedConfigureType      speed;
    PullPushConfigureType   mode;
    ModeConfigureType       pull_or_push;
}CCGPIOConfig;

typedef enum{
    OFF     = 0,
    ON      = 1
}GPIOState;

void createGPIO(CCGPIO* blank, GPIO_Letter gpio_base, GPIO_Offset offset, char letter);
void createGPIOConfig(CCGPIOConfig* config, SpeedConfigureType speed, 
                                        PullPushConfigureType pull_push, 
                                        ModeConfigureType mode);
void setGPIOConfig(CCGPIO* gpio, CCGPIOConfig* config);
void setGPIOState(CCGPIO* gpio, GPIOState state);
void toggleGPIOState(CCGPIO* gpio);
GPIOState gainGPIOState(CCGPIO* gpio);
#define setGPIOOn(GPIO) do{setGPIOState(GPIO, ON);}while(0)
#define setGPIOOff(GPIO) do{setGPIOState(GPIO, OFF);}while(0)
