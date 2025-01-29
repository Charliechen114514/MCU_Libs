#ifndef OLED_SOFT_H
#define OLED_SOFT_H

#include "OLED/Driver/oled_config.h"
#include "stm32f1xx_hal_gpio.h"

typedef struct __oled_tmp_gpio_pack{
    GPIO_TypeDef*   port;
    uint16_t        pin;
}OLED_IICGPIOPack;

/* this will make the gpio used for iic */

typedef struct __OLED_SOFT_IIC_Private_Config
{
    /* soft gpio handling */ 
    OLED_IICGPIOPack       sda;
    OLED_IICGPIOPack       scl;
    uint32_t            accepted_time_delay;
    uint16_t            device_address;
    OLED_Operations     operation;
}OLED_SOFT_IIC_Private_Config;


/*
    config: 
        Pointer to an OLED_SOFT_IIC_Private_Config structure that 
        contains the configuration settings for the software I2C communication,
        such as timing, pins, and other relevant parameters.
        config should be blank or uninitialized.
    sda: 
        Pointer to an OLED_GPIOPack structure that 
        represents the GPIO configuration for the Serial Data (SDA) line of 
        the software I2C interface.

    scl: 
        Pointer to an OLED_GPIOPack structure that 
        represents the GPIO configuration for the Serial Clock (SCL) line of 
        the software I2C interface.

    device_address: 
        The 7-bit I2C address of the device that the software I2C 
        communication is targeting, typically used to identify the 
        device on the I2C bus.

    accepted_time_delay: 
        A timeout value in milliseconds, 
        specifying the maximum allowed delay for the software 
        I2C communication process.
*/
void oled_bind_softiic_handle(
    OLED_SOFT_IIC_Private_Config*   config,
    OLED_IICGPIOPack*                  sda,  
    OLED_IICGPIOPack*                  scl,
    uint16_t                        device_address,
    uint32_t                        accepted_time_delay
);




#endif