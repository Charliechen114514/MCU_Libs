#include "Graphic/device_adapter/CCGraphic_device_oled_adapter.h"
#include "OLED/Driver/oled_base_driver.h"

void init_device_oled(
    CCDeviceHandler* blank, CCGraphic_OLED_Config* onProvideConfigs)
{
    OLED_Handle* handle = (OLED_Handle*)(blank->handle);
    switch(handle->stored_handle_type)
    {
        case OLED_SOFT_IIC_DRIVER_TYPE:
            oled_init_softiic_handle(
                blank->handle,
                (OLED_HARD_IIC_Private_Config*)(onProvideConfigs->related_configs)
            );
        break;
        case OLED_HARD_IIC_DRIVER_TYPE:
            oled_init_hardiic_handle(
                blank->handle, 
                (OLED_HARD_IIC_Private_Config*)(onProvideConfigs->related_configs));
        break;
    }
}

void update_device_oled(CCDeviceHandler* handler)
{
    OLED_Handle* handle = (OLED_Handle*)handler->handle;
    oled_helper_update(handle);
}

void clear_device_oled(CCDeviceHandler* handler)
{
    OLED_Handle* handle = (OLED_Handle*)handler->handle;
    oled_helper_clear_frame(handle);
}

void setpixel_device_oled(CCDeviceHandler* handler, uint8_t x, uint8_t y)
{
    OLED_Handle* handle = (OLED_Handle*)handler->handle;
    oled_helper_setpixel(handle, x, y);
}