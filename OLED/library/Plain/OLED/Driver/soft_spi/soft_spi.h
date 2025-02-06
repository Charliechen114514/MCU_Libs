#ifndef SOFT_SPI_H
#define SOFT_SPI_H

#include "OLED/Driver/oled_config.h"
#include "stm32f1xx_hal_gpio.h"

typedef struct __spi_oled_tmp_gpio_pack{
    GPIO_TypeDef*   port;
    uint16_t        pin;
}OLED_SPIGPIOPack;

typedef struct __OLED_SOFT_SPI_Private_Config {
    OLED_SPIGPIOPack        sda;
    OLED_SPIGPIOPack        scl;
    OLED_SPIGPIOPack        res;
    OLED_SPIGPIOPack        dc;
    OLED_SPIGPIOPack        cs;
    OLED_Operations         operation;    
}OLED_SOFT_SPI_Private_Config;

void oled_bind_softspi_pack(OLED_SOFT_SPI_Private_Config* config,
    OLED_SPIGPIOPack* sda,
    OLED_SPIGPIOPack* scl,
    OLED_SPIGPIOPack* res,
    OLED_SPIGPIOPack* dc,
    OLED_SPIGPIOPack* cs);




#endif