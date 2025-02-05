#ifdef USE_HARDSPI_PROTOCOL

#include "OLED/Driver/hard_spi/hard_spi.h"
#include "OLED/Driver/oled_base_driver.h"

#include "Graphic/device_adapter/CCGraphic_device_oled_adapter.h"
#include "Graphic/fast_setup/fast_setup.h"

#include "spi.h"

OLED_HARD_SPI_Private_Config hard_spi_pvt_config;
OLED_Handle hard_spi_handle;
CCGraphic_OLED_Config hard_spi_config;
static OLED_HARDSPIGPIOPack    _res = {SPI_PORT_RES, SPI_PIN_RES};
static OLED_HARDSPIGPIOPack    _dc = {SPI_PORT_DC, SPI_PIN_DC};
static OLED_HARDSPIGPIOPack    _cs = {SPI_PORT_CS, SPI_PIN_CS};

void oled_hard_spi_setup(CCDeviceHandler* device)
{

    oled_bind_hard_spi(&hard_spi_pvt_config,&hspi2, &_res, &_dc, &_cs, HAL_MAX_DELAY);
    hard_spi_config.createType = OLED_HARD_SPI_DRIVER_TYPE;
    hard_spi_config.related_configs = &hard_spi_pvt_config;
    register_oled_paintdevice(device, &hard_spi_handle, &hard_spi_config);
}

#endif