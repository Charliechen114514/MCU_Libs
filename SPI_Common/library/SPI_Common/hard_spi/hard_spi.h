#ifndef __HARD_SPI_H
#define __HARD_SPI_H

#include "SPI_Common/spi_common.h"

typedef struct __HARD_SPI_COMMON{
    SPI_HandleTypeDef*      spi_handle;
    SPI_GPIOPack            ss; 
    SPI_Configure           config;
} HARDSPI_Protocol;

void init_hardspi_protocol(
    HARDSPI_Protocol*       protocol,
    SPI_HandleTypeDef*      raw_spi,
    SPI_GPIOPack            ss,
    SPI_Configure           config
);

void hardspi_start_spi(HARDSPI_Protocol* config);

void hardspi_end_spi(HARDSPI_Protocol* config);

void hardspi_send_byte(HARDSPI_Protocol* config, uint8_t byte);
    
uint8_t hardspi_receive_byte(HARDSPI_Protocol* config);

uint8_t hardspi_swap_byte(HARDSPI_Protocol* config , uint8_t data);

void hardspi_send_bytes(HARDSPI_Protocol* config, const uint8_t* bytes, uint32_t size);

void hardspi_rec_bytes(HARDSPI_Protocol* config, uint8_t* bytes, uint32_t size);



#endif