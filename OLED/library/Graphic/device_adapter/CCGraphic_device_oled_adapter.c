#include "Graphic/device_adapter/CCGraphic_device_oled_adapter.h"
#include "OLED/Driver/oled_base_driver.h"

void init_device_oled(
    CCDeviceHandler* blank, CCGraphic_OLED_Config* onProvideConfigs)
{
    OLED_Handle* handle = (OLED_Handle*)(blank->handle);
    OLED_Driver_Type type = onProvideConfigs->createType;
    switch(type)
    {
        case OLED_SOFT_IIC_DRIVER_TYPE:
            oled_init_softiic_handle(
                handle,
                (OLED_SOFT_IIC_Private_Config*)
                (onProvideConfigs->related_configs)
            );
        break;
        case OLED_HARD_IIC_DRIVER_TYPE:
            oled_init_hardiic_handle(
                handle, 
                (OLED_HARD_IIC_Private_Config*)
                (onProvideConfigs->related_configs));
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

void setpixel_device_oled(CCDeviceHandler* handler, uint16_t x, uint16_t y)
{
    OLED_Handle* handle = (OLED_Handle*)handler->handle;
    oled_helper_setpixel(handle, x, y);
}

void clear_area_device_oled(CCDeviceHandler* handler, 
        uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    OLED_Handle* handle = (OLED_Handle*)handler->handle;
    oled_helper_clear_area(
        handle, x, y, width, height
    );
}

void update_area_device_oled(CCDeviceHandler* handler, 
        uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    OLED_Handle* handle = (OLED_Handle*)handler->handle;
    oled_helper_update_area(
        handle, x, y, width, height
    );
}

void reverse_device_oled(CCDeviceHandler* handler)
{
    OLED_Handle* handle = (OLED_Handle*)handler->handle;
    oled_helper_reverse(handle);
}

void reversearea_device_oled(CCDeviceHandler* handler, 
        uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    OLED_Handle* handle = (OLED_Handle*)handler->handle;
    oled_helper_reversearea(
        handle, x, y, width, height
    );
}

void draw_area_device_oled(
    CCDeviceHandler* handler, 
    uint16_t x, uint16_t y, 
    uint16_t width, uint16_t height, uint8_t* sources
){
    OLED_Handle* handle = (OLED_Handle*)handler->handle;
    oled_helper_draw_area(handle, x, y, width, height, sources);
}

void property_fetcher_device_oled(
    CCDeviceHandler* handler, void* getter, CommonProperty p
)
{
    OLED_Handle* handle = (OLED_Handle*)handler->handle;
    switch (p)
    {
    case CommonProperty_HEIGHT:
    {   
        int16_t* pHeight = (int16_t*)getter;
        *pHeight = oled_height(handle);
    }break;
    case CommonProperty_WIDTH:
    {
        int16_t* pWidth = (int16_t*)getter;
        *pWidth = oled_width(handle);
    }break;
    case CommonProperty_SUPPORT_RGB:
    {
        uint8_t* pSupportRGB = (uint8_t*)getter;
        *pSupportRGB = oled_support_rgb(handle);
    }break;
    default:
        break;
    }
}