#ifdef USE_SOFTIIC_PROTOCOL

#include "Graphic/fast_setup/fast_setup.h"
#include "OLED/Driver/oled_base_driver.h"
#include "OLED/Driver/soft_iic/soft_iic.h"
#include "Graphic/device_adapter/CCGraphic_device_oled_adapter.h"

OLED_SOFT_IIC_Private_Config pvt_config;
OLED_Handle handle;
CCGraphic_OLED_Config config;
static OLED_IICGPIOPack scl = {PORT_SCL, PIN_SCL};
static OLED_IICGPIOPack sda = {PORT_SDA, PIN_SDA};

void oled_soft_iic_setup(CCDeviceHandler* device)
{
    oled_bind_softiic_handle(
        &pvt_config, &sda, &scl, 0x78, HAL_MAX_DELAY
    );
    config.createType = OLED_SOFT_IIC_DRIVER_TYPE;
    config.related_configs = &pvt_config;
    register_oled_paintdevice(device, &handle, &config);
}

#endif