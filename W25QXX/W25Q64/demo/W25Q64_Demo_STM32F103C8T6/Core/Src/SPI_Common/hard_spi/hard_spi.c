#include "SPI_Common/hard_spi/hard_spi.h"
#define write_pin(config, pin_name, _pin)                                         \
    do                                                                            \
    {                                                                             \
        HAL_GPIO_WritePin(config->pin_name.port, config->pin_name.pin, !!(_pin)); \
    } while (0)
#define write_ss_pin(config, pin_state) write_pin(config, ss, pin_state)

void init_hardspi_protocol(
    HARDSPI_Protocol*       protocol,
    SPI_HandleTypeDef*      raw_spi,
    SPI_GPIOPack            ss,
    SPI_Configure           config)
{
    protocol->spi_handle = raw_spi;
    protocol->ss = ss;
    protocol->config = config;
}

void hardspi_start_spi(HARDSPI_Protocol* config)
{
    write_ss_pin(config, 0);
}

void hardspi_end_spi(HARDSPI_Protocol* config)
{
    write_ss_pin(config, 1);
}

void hardspi_send_byte(HARDSPI_Protocol* config, uint8_t byte)
{
    hardspi_send_bytes(config, &byte, 1);
}
    
uint8_t hardspi_receive_byte(HARDSPI_Protocol* config)
{
    uint8_t res = 0x00;
    hardspi_rec_bytes(config, &res, 1);
    return res;
}

uint8_t hardspi_swap_byte(HARDSPI_Protocol* config , uint8_t data){
    hardspi_send_byte(config, data);
    return hardspi_receive_byte(config);
}

void hardspi_send_bytes(
    HARDSPI_Protocol* config, const uint8_t* bytes, uint32_t size)
{
    HAL_SPI_Transmit(
        config->spi_handle, (uint8_t*)bytes, (uint16_t)size, config->config.delay_time);
}

void hardspi_rec_bytes(HARDSPI_Protocol* config, uint8_t* bytes, uint32_t size)
{
    HAL_SPI_Receive(
        config->spi_handle, bytes, (uint16_t)size, config->config.delay_time);
}