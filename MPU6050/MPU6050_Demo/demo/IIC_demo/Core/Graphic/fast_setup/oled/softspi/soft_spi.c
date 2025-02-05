#ifdef USE_SOFTSPI_PROTOCOL

#include "Graphic/fast_setup/fast_setup.h"
#include "OLED/Driver/oled_base_driver.h"
#include "OLED/Driver/soft_spi/soft_spi.h"

#include "Graphic/device_adapter/CCGraphic_device_oled_adapter.h"

OLED_SOFT_SPI_Private_Config soft_spi_pvt_config;
OLED_Handle soft_spi_handle;
CCGraphic_OLED_Config soft_spi_config;
static OLED_SPIGPIOPack    sda = {SPI_PORT_SDA, SPI_PIN_SDA};
static OLED_SPIGPIOPack    scl = {SPI_PORT_SCL, SPI_PIN_SCL};
static OLED_SPIGPIOPack    res = {SPI_PORT_RES, SPI_PIN_RES};
static OLED_SPIGPIOPack    dc = {SPI_PORT_DC, SPI_PIN_DC};
static OLED_SPIGPIOPack    cs = {SPI_PORT_CS, SPI_PIN_CS};

void oled_soft_spi_setup(CCDeviceHandler* device)
{
    oled_bind_softspi_pack(&soft_spi_pvt_config, &sda, &scl, &res, &dc, &cs);
    soft_spi_config.createType = OLED_SOFT_SPI_DRIVER_TYPE;
    soft_spi_config.related_configs = &soft_spi_pvt_config;
    register_oled_paintdevice(device, &soft_spi_handle, &soft_spi_config);
}

#endif