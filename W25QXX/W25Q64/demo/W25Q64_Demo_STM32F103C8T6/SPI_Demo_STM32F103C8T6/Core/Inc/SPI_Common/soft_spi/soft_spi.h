#ifndef SOFT_SPI_H
#define SOFT_SPI_H
#include "SPI_Common/spi_common.h"

#define __ENABLE_SPI_GPIO_CLKS() __HAL_RCC_GPIOA_CLK_ENABLE()



typedef struct __SoftSPI_Protocol {
    SPI_GPIOPack        ss;
    SPI_GPIOPack        clk;
    SPI_GPIOPack        mosi;
    SPI_GPIOPack        miso;
    SPI_Configure       config;
}SOFTSPI_Protocol;

void init_softspi_protocol(
    SOFTSPI_Protocol*       protocol,
    SPI_GPIOPack        ss,
    SPI_GPIOPack        clk,
    SPI_GPIOPack        mosi,
    SPI_GPIOPack        miso,
    SPI_Configure       config
);

void softspi_start_spi(SOFTSPI_Protocol* config);

void softspi_end_spi(SOFTSPI_Protocol* config);

void softspi_send_byte(SOFTSPI_Protocol* config, uint8_t byte);
    
uint8_t softspi_receive_byte(SOFTSPI_Protocol* config);

uint8_t softspi_swap_byte(SOFTSPI_Protocol* config , uint8_t data);

#endif