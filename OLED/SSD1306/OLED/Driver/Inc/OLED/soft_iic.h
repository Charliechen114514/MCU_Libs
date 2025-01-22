#ifndef SOFT_IIC_H
#define SOFT_IIC_H

#ifdef STM32F1
#include "stm32f1xx_hal.h"

typedef struct __OLED_Handle_SoftIIC_Handle{
    GPIO_TypeDef*   sda_port;
    uint16_t        sda_pin;
    GPIO_TypeDef*   scl_port;
    uint16_t        scl_pin;
    uint16_t        device_address;
    void (*sendCommand)(
        struct __OLED_Handle_SoftIIC_Handle* who, 
        const uint8_t command);
    void (*sendData)(
        struct __OLED_Handle_SoftIIC_Handle* who, 
        const uint8_t* data, const uint8_t size);
}OLED_Handle_SoftIIC_Handle_Private;

void OLED_Handle_SoftIIC_Private_bindHandle(
    OLED_Handle_SoftIIC_Handle_Private* blank_handle,
    uint16_t        device_address,
    GPIO_TypeDef*   sda_port,
    uint16_t        sda_pin,
    GPIO_TypeDef*   scl_port,
    uint16_t        scl_pin
);

#else
    #error "Current Hard IIC Lib is not support other chips!"
#endif

#endif