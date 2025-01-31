#ifdef USE_HARDSPI_PROTOCOL

#include "Test/OLED_TEST/oled_test.h"
#include "OLED/Driver/hard_spi/hard_spi.h"
#include "spi.h"
/* configs should be in persist way */
OLED_HARD_SPI_Private_Config config;
static OLED_HARDSPIGPIOPack    res = {SPI_PORT_RES, SPI_PIN_RES};
static OLED_HARDSPIGPIOPack    dc = {SPI_PORT_DC, SPI_PIN_DC};
static OLED_HARDSPIGPIOPack    cs = {SPI_PORT_CS, SPI_PIN_CS};


void user_init_hard_spi_oled_handle(OLED_Handle* handle)
{
    oled_bind_hard_spi(&config,&hspi2, &res, &dc, &cs, HAL_MAX_DELAY);
    oled_init_hardspi_handle(handle, &config);
}

#endif