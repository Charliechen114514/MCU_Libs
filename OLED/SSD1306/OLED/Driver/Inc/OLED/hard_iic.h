#ifndef HARD_IIC_H
#define HARD_IIC_H

// defines the iic handle
// for f1 series
#ifdef STM32F1
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"

typedef struct __OLED_Handle_HardIIC_Private{
    I2C_HandleTypeDef* handle;
    uint16_t accepted_time_out;
    uint32_t device_address;
    /* 
        prototypes for the send iic 
        1: iic handle
        2: iic send buffer
        3: iic send length requires
        it is sadly that the match between the buffer and
        the valid length should be promised by programers
    */
    void (*sendData)(
        struct __OLED_Handle_HardIIC_Private*, 
        uint8_t*, 
        const uint16_t);
    void (*sendCommand)(
        struct __OLED_Handle_HardIIC_Private*, 
        uint8_t);
}OLED_Handle_HardIIC_Private;
/*
    bind the hard iic handle
    requires a raw iic handle from lower level
*/
void OLED_Handle_HardIIC_Private_bindHandle(
    OLED_Handle_HardIIC_Private* blank_handle, 
    uint16_t device_address,
    I2C_HandleTypeDef* raw, uint32_t accept_time_out);

#else
#error "Current Hard IIC Lib is not support other chips!"
#endif

#endif