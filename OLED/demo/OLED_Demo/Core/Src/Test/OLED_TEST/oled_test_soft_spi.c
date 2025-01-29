#include "Test/OLED_TEST/oled_test.h"
#include "OLED/Driver/soft_spi/soft_spi.h"
/* configs should be in persist way */
OLED_SOFT_SPI_Private_Config config;
static OLED_SPIGPIOPack    sda = {SPI_PORT_SDA, SPI_PIN_SDA};
static OLED_SPIGPIOPack    scl = {SPI_PORT_SCL, SPI_PIN_SCL};
static OLED_SPIGPIOPack    res = {SPI_PORT_RES, SPI_PIN_RES};
static OLED_SPIGPIOPack    dc = {SPI_PORT_DC, SPI_PIN_DC};
static OLED_SPIGPIOPack    cs = {SPI_PORT_CS, SPI_PIN_CS};


void user_init_soft_spi_oled_handle(OLED_Handle* handle)
{
    oled_bind_softspi_pack(&config, &sda, &scl, &res, &dc, &cs);
    oled_init_softspi_handle(handle, &config);
}