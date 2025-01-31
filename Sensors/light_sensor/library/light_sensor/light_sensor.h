#ifndef Light_sensor_H
#define Light_sensor_H

#ifdef STM32F1
#include "stm32f1xx_hal.h"

typedef struct{
    GPIO_TypeDef*   gpio;
    uint16_t        pin;
}LightSensorGPIOPack;

#endif
typedef struct __light_sensor_type LightSensor;
typedef void (*FetchFromSensor)(LightSensor*, void*);
typedef struct {
    FetchFromSensor     from_remote_dc;
}LightSensorOperation;

typedef struct __light_sensor_type{
    LightSensorGPIOPack     gpio_package;
    LightSensorOperation*   operations;
}LightSensor;


void init_light_sensor(
    LightSensor* blankSensor, LightSensorGPIOPack* package);

#endif

