#include "SPI_Common/soft_spi/soft_spi.h"

#define write_pin(config, pin_name, _pin)                                         \
    do                                                                            \
    {                                                                             \
        HAL_GPIO_WritePin(config->pin_name.port, config->pin_name.pin, !!(_pin)); \
    } while (0)

#define write_ss_pin(config, pin_state) write_pin(config, ss, pin_state)
#define write_mosi_pin(config, pin_state) write_pin(config, mosi, pin_state)

#define write_clk_pin(config, pin_state) write_pin(config, clk, pin_state)

#define read_miso_pin(config) HAL_GPIO_ReadPin(config->miso.port, config->miso.pin)

void softspi_start_spi(SOFTSPI_Protocol *config)
{
    write_ss_pin(config, 0);
}

void softspi_end_spi(SOFTSPI_Protocol *config)
{
    write_ss_pin(config, 1);
}

void softspi_send_byte(SOFTSPI_Protocol *config, const uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        write_mosi_pin(config, byte & (0x80 >> i));
        write_clk_pin(config, 1);
        write_clk_pin(config, 0);
    }
}

uint8_t softspi_receive_byte(SOFTSPI_Protocol *config)
{
    uint8_t recieve = 0x00;
    for (uint8_t i = 0; i < 8; i++)
    {
        write_mosi_pin(config, 0xFF);
        write_clk_pin(config, 1);
        if (read_miso_pin(config))
        {
            recieve |= (0x80 >> i);
        }
        write_clk_pin(config, 0);
    }

    return recieve;
}

uint8_t softspi_swap_byte(SOFTSPI_Protocol *config, uint8_t data)
{
    uint8_t recieve = 0x00;

    for (uint8_t i = 0; i < 8; i++)
    {
        write_mosi_pin(config, data & (0x80 >> i));
        write_clk_pin(config, 1);
        if (read_miso_pin(config))
        {
            recieve |= (0x80 >> i);
        }
        write_clk_pin(config, 0);
    }

    return recieve;
}

#define INIT_OUTPUT(port_name)          \
    init.Pin = protocol->port_name.pin; \
    init.Mode = GPIO_MODE_OUTPUT_PP;    \
    init.Speed = GPIO_SPEED_FREQ_HIGH;  \
    HAL_GPIO_Init(protocol->port_name.port, &init)

#define INIT_INPUT(port_name)           \
    init.Pin = protocol->port_name.pin; \
    init.Mode = GPIO_MODE_INPUT;        \
    init.Speed = GPIO_SPEED_FREQ_HIGH;  \
    HAL_GPIO_Init(protocol->port_name.port, &init)

static void __init_gpios(SOFTSPI_Protocol *protocol)
{
    __ENABLE_SPI_GPIO_CLKS();

    GPIO_InitTypeDef init;
    INIT_OUTPUT(ss);
    INIT_OUTPUT(clk);
    INIT_OUTPUT(mosi);
    INIT_INPUT(miso);

    write_ss_pin(protocol, 1);
    write_clk_pin(protocol, 0);
}

void init_softspi_protocol(
    SOFTSPI_Protocol *protocol,
    SPI_GPIOPack ss,
    SPI_GPIOPack clk,
    SPI_GPIOPack mosi,
    SPI_GPIOPack miso,
    SPI_Configure config)
{
    protocol->clk = clk;
    protocol->miso = miso;
    protocol->ss = ss;
    protocol->mosi = mosi;
    protocol->config = config;
    __init_gpios(protocol);
}