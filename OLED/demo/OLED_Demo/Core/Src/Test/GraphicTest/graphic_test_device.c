#include "Test/GraphicTest/graphic_test.h"

#include "Graphic/device_adapter/CCGraphic_device_oled_adapter.h"
#include "OLED/Driver/hard_iic/hard_iic.h"
#include "OLED/Driver/soft_spi/soft_spi.h"
#include "OLED/Driver/hard_spi/hard_spi.h"
#include "OLED/Driver/oled_base_driver.h"
#include "i2c.h"
#include "spi.h"

OLED_HARD_IIC_Private_Config pvt_config;
OLED_Handle handle;
CCGraphic_OLED_Config config;

void on_test_init_hardiic_oled(CCDeviceHandler* device)
{
    bind_hardiic_handle(
        &pvt_config, &hi2c1, 0x78, HAL_MAX_DELAY
    );
    config.createType = OLED_HARD_IIC_DRIVER_TYPE;
    config.related_configs = &pvt_config;
    register_oled_paintdevice(device, &handle, &config);
}


OLED_SOFT_SPI_Private_Config soft_spi_pvt_config;
OLED_Handle soft_spi_handle;
CCGraphic_OLED_Config soft_spi_config;
static OLED_SPIGPIOPack    sda = {SPI_PORT_SDA, SPI_PIN_SDA};
static OLED_SPIGPIOPack    scl = {SPI_PORT_SCL, SPI_PIN_SCL};
static OLED_SPIGPIOPack    res = {SPI_PORT_RES, SPI_PIN_RES};
static OLED_SPIGPIOPack    dc = {SPI_PORT_DC, SPI_PIN_DC};
static OLED_SPIGPIOPack    cs = {SPI_PORT_CS, SPI_PIN_CS};

void on_test_init_softspi_oled(CCDeviceHandler* device)
{
    oled_bind_softspi_pack(&soft_spi_pvt_config, &sda, &scl, &res, &dc, &cs);
    soft_spi_config.createType = OLED_SOFT_SPI_DRIVER_TYPE;
    soft_spi_config.related_configs = &soft_spi_pvt_config;
    register_oled_paintdevice(device, &soft_spi_handle, &soft_spi_config);
}

OLED_HARD_SPI_Private_Config hard_spi_pvt_config;
OLED_Handle hard_spi_handle;
CCGraphic_OLED_Config hard_spi_config;
static OLED_HARDSPIGPIOPack    _res = {SPI_PORT_RES, SPI_PIN_RES};
static OLED_HARDSPIGPIOPack    _dc = {SPI_PORT_DC, SPI_PIN_DC};
static OLED_HARDSPIGPIOPack    _cs = {SPI_PORT_CS, SPI_PIN_CS};
void on_test_init_hardspi_oled(CCDeviceHandler* device)
{
    oled_bind_hard_spi(&hard_spi_pvt_config,&hspi2, &_res, &_dc, &_cs, HAL_MAX_DELAY);
    hard_spi_config.createType = OLED_HARD_SPI_DRIVER_TYPE;
    hard_spi_config.related_configs = &hard_spi_pvt_config;
    register_oled_paintdevice(device, &hard_spi_handle, &hard_spi_config);
}
