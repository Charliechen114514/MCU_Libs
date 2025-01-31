#ifdef USE_HARDIIC_PROTOCOL

#include "Graphic/fast_setup/fast_setup.h"

#include "OLED/Driver/oled_base_driver.h"
#include "OLED/Driver/hard_iic/hard_iic.h"

#include "Graphic/device_adapter/CCGraphic_device_oled_adapter.h"

#include "i2c.h"

OLED_HARD_IIC_Private_Config pvt_config;
OLED_Handle handle;
CCGraphic_OLED_Config config;

void oled_hard_iic_setup(CCDeviceHandler* device)
{
    bind_hardiic_handle(
        &pvt_config, &hi2c1, 0x78, HAL_MAX_DELAY
    );
    config.createType = OLED_HARD_IIC_DRIVER_TYPE;
    config.related_configs = &pvt_config;
    register_oled_paintdevice(device, &handle, &config);
}

#endif