#ifndef HARD_SPI_H
#define HARD_SPI_H

#include "OLED/Driver/oled_config.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"

typedef struct __oled_spi_hard_tmp_gpio_pack{
    GPIO_TypeDef*   port;
    uint16_t        pin;
}OLED_HARDSPIGPIOPack;

typedef struct __OLED_HARD_SPI_Private_Config{
    OLED_HARDSPIGPIOPack    res;
    OLED_HARDSPIGPIOPack    dc;
    OLED_HARDSPIGPIOPack    cs;
    SPI_HandleTypeDef*      pvt_handle;
    uint32_t                delay_time_out;
    OLED_Operations         operation;
}OLED_HARD_SPI_Private_Config;

void oled_bind_hard_spi(
    OLED_HARD_SPI_Private_Config* blank_config,
    SPI_HandleTypeDef*  pvt_handle,
    OLED_HARDSPIGPIOPack*    res,
    OLED_HARDSPIGPIOPack*    dc,
    OLED_HARDSPIGPIOPack*    cs,
    uint32_t                 delay_time_out
);



#endif