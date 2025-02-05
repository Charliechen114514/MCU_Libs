#ifndef OLED_HARD_IIC_H
#define OLED_HARD_IIC_H
#include "OLED/Driver/oled_config.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"

typedef struct __OLED_HARD_IIC_Private_Config{
    I2C_HandleTypeDef*  pvt_handle;
    uint32_t            accepted_time_delay;
    uint16_t            device_address;
    OLED_Operations     operation;
}OLED_HARD_IIC_Private_Config;

/* 
    handle binder, bind the raw data to the oled driver
    
    blank_config: Pointer to an OLED_HARD_IIC_Private_Config structure that 
        holds the configuration settings for the I2C communication, 
        typically initializing the OLED hardware interface.
    
    raw_handle: 
        Pointer to an I2C_HandleTypeDef structure, 
        representing the raw I2C peripheral handle used to 
        configure and manage I2C communication for the device.

    device_address: The 7-bit I2C address of the device to 
        which the communication is being established, 
        typically used for identifying the target device on the I2C bus.

    accepted_time_delay: A timeout value in milliseconds 
        that specifies the maximum allowable 
        delay for the I2C communication process.
*/
void bind_hardiic_handle(
    OLED_HARD_IIC_Private_Config* blank_config,
    I2C_HandleTypeDef* raw_handle,
    uint16_t    device_address,
    uint32_t    accepted_time_delay
);

#endif