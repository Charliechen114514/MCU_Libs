#include "GraphicTest/graphic_test.h"

#include "Graphic/device_adapter/CCGraphic_device_oled_adapter.h"
#include "OLED/Driver/hard_iic/hard_iic.h"
#include "OLED/Driver/oled_base_driver.h"
#include "i2c.h"

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



